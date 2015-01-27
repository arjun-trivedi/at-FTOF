#include <iostream>
#include "sigma6barfunctions.hh"
#include <TMath.h>
#include <TMatrixD.h>
#include <cmath>

//function for calculating coefficient matrix given
//a vector<vector<int> > with each vector<int> being the 3
//bars involved in a 3 bar combo, vector<int>[1] being the
//middle bar
void
GenerateCoefficientMatrix
(TMatrixD& coef,
 const std::vector<std::vector<int> >& combinations)
{
  std::vector<std::vector<double> > coefficients;
  coefficients.resize(combinations.size());
  for(int i = 0; i < coefficients.size(); ++i) {
    coefficients[i].resize(6); //always six bars
    for(int j = 0; j < coefficients[i].size(); ++j) {
      coefficients[i][j]=0;
    }
      coefficients[i][combinations[i][0]-1]
	=coefficients[i][combinations[i][2]-1]=0.25;
      coefficients[i][combinations[i][1]-1]=1;
  }
  coef.ResizeTo(coefficients.size(),coefficients[0].size());
  double coef_array[coefficients.size()*coefficients[0].size()];
  for(int i = 0; i < coefficients.size(); ++i) {//row
    for(int j = 0; j < coefficients[0].size(); ++j) {
      //assuming constant number of columns
      coef_array[i*coefficients[0].size()+j]=coefficients[i][j];
    }
  }
  coef.SetMatrixArray(coef_array);
  return;
}


void calc_sigmabars(const TMatrixD& coef,
		    TMatrixD sigma_ref,
		    TMatrixD& sigma_bars)
{
  TMatrixD transpose(coef);
  transpose.Transpose(transpose);
  TMatrixD inverse = ( transpose * coef );
  inverse.Invert();
  TMatrixD tmpinverse = inverse * transpose;
  //above section can be cut from the efficient variant of this
  //procedure
  const int nrows = sigma_ref.GetNrows();
  double sigma_ref_array[nrows];
  for(int i = 0; i < nrows; ++i) {
    sigma_ref_array[i] = sigma_ref(i,0)*sigma_ref(i,0);
  }
  sigma_ref.SetMatrixArray(sigma_ref_array);
  tmpinverse *= (double) (3./2.);
  sigma_bars.ResizeTo(coef.GetNcols(),1);
  sigma_bars = tmpinverse * sigma_ref;
  sigma_bars.Sqrt();
  return;
}

void calc_sigmabars_efficient(const TMatrixD& reduced_coef,
			      TMatrixD sigma_ref,
			      TMatrixD& sigma_bars)
{
  TMatrixD tmpinverse(reduced_coef);
  const int nrows = sigma_ref.GetNrows();
  double sigma_ref_array[nrows];
  for(int i = 0; i < nrows; ++i) {
    sigma_ref_array[i] = sigma_ref(i,0)*sigma_ref(i,0);
  }
  sigma_ref.SetMatrixArray(sigma_ref_array);
  tmpinverse *= (double) (3./2.);
  sigma_bars.ResizeTo(reduced_coef.GetNcols(),1);
  sigma_bars = tmpinverse * sigma_ref;
  sigma_bars.Sqrt();
  return;
}

//depends on:
//sigma_bars, coef, sigma_ref, sigma(sigma_ref).
//
void calc_sigmabars_error(const TMatrixD& coef,
			  const TMatrixD& sigma_bars,
			  const TMatrixD& sigma_ref,
			  const TMatrixD& sigma_ref_error,
			  TMatrixD& sigma_bars_error)
{
  sigma_bars_error.ResizeTo(sigma_bars);
  TMatrixD transpose(coef);
  transpose.Transpose(transpose);
  TMatrixD inverse = transpose * coef;
  inverse.Invert();
  TMatrixD alpha = inverse*transpose;
  double sum;
  double sum_array[6];
  for(int i = 0; i < sigma_bars.GetNrows(); ++i) {
    sum = 0;
    for(int j = 0; j < sigma_ref.GetNrows(); ++j) {
      sum += pow(3./2.*alpha(i,j)*sigma_ref(j,0)*sigma_ref_error(j,0),2);
    }
    sum_array[i]=sqrt(sum)/sigma_bars(i,0);
  }
  sigma_bars_error.SetMatrixArray(sum_array);
}

void calc_sigmabars_error_efficient(const TMatrixD& alpha, //reduced coef
				    const TMatrixD& sigma_bars,
				    const TMatrixD& sigma_ref,
				    const TMatrixD& sigma_ref_error,
				    TMatrixD& sigma_bars_error)
{
  sigma_bars_error.ResizeTo(sigma_bars);
  double sum;
  double sum_array[6];
  for(int i = 0; i < sigma_bars.GetNrows(); ++i) {
    sum = 0;
    for(int j = 0; j < sigma_ref.GetNrows(); ++j) {
      sum += pow(3./2.*alpha(i,j)*sigma_ref(j,0)*sigma_ref_error(j,0),2);
    }
    sum_array[i]=sqrt(sum)/sigma_bars(i,0);
  }
  sigma_bars_error.SetMatrixArray(sum_array);
}

void
calc_CombinationMean
(double* CombinationMean,
 const TMatrixD& sigma_s_matrix,
 const std::vector<std::vector<int> >& combo3bar_v)
{
  double sum[6], count[6];
  for(int i = 0; i < 6; ++i) {
    sum[i]=0;
    count[i]=0;
    for(int j = 0; j < combo3bar_v.size(); ++j) {
      if(combo3bar_v[j][0] == (i+1)
	 || combo3bar_v[j][1] == (i+1)
	 || combo3bar_v[j][2] == (i+1)) {
	sum[i]+=sigma_s_matrix(j,0);
	++count[i];
      }
    }
    CombinationMean[i]=sum[i]/count[i];
  }
}

void
calc_CombinationMean_Error
(double* combinationmean_error,
 const double* const combination_mean,
 const TMatrixD& sigma_s_matrix,
 const std::vector<std::vector<int> >& combo3bar_v)
{
  double sum[6], count[6];
  for(int i = 0; i < 6; ++i) {
    for(int j = 0; j < combo3bar_v.size(); ++j) {
      if(combo3bar_v[j][0] == (i+1)
	 || combo3bar_v[j][1] == (i+1)
	 || combo3bar_v[j][2] == (i+1)) {
	sum[i]+=pow((sigma_s_matrix(j,0)-combination_mean[i]),2);
	++count[i];
      }
    }
    if(count[i]==1)
      combinationmean_error[i]=-1;
    else
      combinationmean_error[i]=sqrt(sum[i]/(count[i]-1))/sqrt(count[i]);
  }
  return;
}

/*
**************************************************
These functions all need work!  The above hopefully
work already.
*/

//corresponding functions for sigma_bars^2
void calc_sigmabars2(const TMatrixD& coef,
		     TMatrixD sigma_ref,
		     TMatrixD& sigma_bars2)
{
  TMatrixD transpose(coef);
  transpose.Transpose(transpose);
  TMatrixD inverse = transpose * coef;
  inverse.Invert();
  TMatrixD alpha = inverse*transpose;
  alpha *= 3./2.;
  double sigma_ref_array[sigma_ref.GetNrows()];
  for(int i = 0; i < sigma_ref.GetNrows(); ++i) {
    sigma_ref_array[i]=pow(sigma_ref(i,0),2);
  }
  sigma_ref.SetMatrixArray(sigma_ref_array);
  sigma_bars2.ResizeTo(coef.GetNcols(),1);
  sigma_bars2 = alpha * sigma_ref;
  return;
}

void calc_sigmabars2_efficient(const TMatrixD& alpha, //reduced coef
			       TMatrixD sigma_ref,
			       TMatrixD& sigma_bars2)
{
  double sigma_ref_array[sigma_ref.GetNrows()];
  for(int i = 0; i < sigma_ref.GetNrows(); ++i) {
    sigma_ref_array[i]=pow(sigma_ref(i,0),2);
  }
  sigma_ref.SetMatrixArray(sigma_ref_array);
  sigma_bars2.ResizeTo(alpha.GetNrows(),1);
  sigma_bars2 = alpha * sigma_ref;
  sigma_bars2 *= 3./2.;
  return;
}

//last section for work:
void calc_sigmabars2_error(const TMatrixD& coef,
			   const TMatrixD& sigma_bars,
			   const TMatrixD& sigma_ref,
			   const TMatrixD& sigma_ref_error,
			   TMatrixD& sigma_bars_error)
{
  TMatrixD transpose(coef);
  transpose.Transpose(transpose);
  TMatrixD inverse = transpose * coef;
  inverse.Invert();
  TMatrixD alpha = inverse * transpose;
  sigma_bars_error.ResizeTo(sigma_bars);
  double sum_array[sigma_bars_error.GetNrows()];
  for(int i = 0; i < sigma_bars.GetNrows(); ++i) {
    double sum = 0;
    for(int j = 0; j < sigma_ref.GetNrows(); ++j) {
      sum += pow(3.*alpha(i,j)*sigma_ref(j,0)*sigma_ref_error(j,0),2);
    }
    sum_array[i]=sqrt(sum);
  }
  sigma_bars_error.SetMatrixArray(sum_array);
}


void calc_sigmabars2_error_efficient(const TMatrixD& alpha,
				     const TMatrixD& sigma_bars,
				     const TMatrixD& sigma_ref,
				     const TMatrixD& sigma_ref_error,
				     TMatrixD& sigma_bars_error)
{
  sigma_bars_error.ResizeTo(sigma_bars);
  double sum_array[sigma_bars_error.GetNrows()];
  for(int i = 0; i < sigma_bars.GetNrows(); ++i) {
    double sum = 0;
    for(int j = 0; j < sigma_ref.GetNrows(); ++j) {
      sum += pow(3.*alpha(i,j)*sigma_ref(j,0)*sigma_ref_error(j,0),2);
    }
    sum_array[i]=sqrt(sum);
  }
  sigma_bars_error.SetMatrixArray(sum_array);
}
