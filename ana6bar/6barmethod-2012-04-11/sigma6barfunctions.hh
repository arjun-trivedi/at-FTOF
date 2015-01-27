#ifndef SIGMA6BARFUNCTIONS_HH
#define SIGMA6BARFUNCTIONS_HH
#include <TMath.h>
#include <TMatrixD.h>
#include <vector>
//functions to either solve for the individual bar
//resolutions exactly or use the linear least squares method
//to find the most likely result.

//function for calculating coefficient matrix given
//a vector<vector<int> > with each vector<int> being the 3
//bars involved in a 3 bar combo, vector<int>[1] being the
//middle bar
void
GenerateCoefficientMatrix
(TMatrixD& coef,
 const std::vector<std::vector<int> >& combinations);

void calc_sigmabars(const TMatrixD& coef,
		    TMatrixD sigma_ref,
		    TMatrixD& sigma_bars);

void calc_sigmabars_efficient(const TMatrixD& reduced_coef,
			      TMatrixD sigma_ref,
			      TMatrixD& sigma_bars);

//depends on:
//sigma_bars, coef, sigma_ref, sigma(sigma_ref).
void calc_sigmabars_error(const TMatrixD& coef,
			  const TMatrixD& sigma_bars,
			  const TMatrixD& sigma_ref,
			  const TMatrixD& sigma_ref_error,
			  TMatrixD& sigma_bars_error);

void calc_sigmabars_error_efficient(const TMatrixD& alpha, //reduced coef
				    const TMatrixD& sigma_bars,
				    const TMatrixD& sigma_ref,
				    const TMatrixD& sigma_ref_error,
				    TMatrixD& sigma_bars_error);

//corresponding functions for sigma_bars^2
void calc_sigmabars2(const TMatrixD& coef,
		     TMatrixD sigma_ref,
		     TMatrixD& sigma_bars2);

void calc_sigmabars2_efficient(const TMatrixD& alpha, //reduced coef
			       TMatrixD sigma_ref,
			       TMatrixD& sigma_bars2);

void calc_sigmabars2_error(const TMatrixD& coef,
			   const TMatrixD& sigma_bars,
			   const TMatrixD& sigma_ref,
			   const TMatrixD& sigma_ref_error,
			   TMatrixD& sigma_bars_error);

void calc_sigmabars2_error_efficient(const TMatrixD& reduced_coef,
				     const TMatrixD& sigma_bars,
				     const TMatrixD& sigma_ref,
				     TMatrixD& sigma_bars_error);

void
calc_CombinationMean
(double* CombinationMean,
 const TMatrixD& sigma_s_matrix,
 const std::vector<std::vector<int> >& combo3bar_v);

void
calc_CombinationMean_Error
(double* combinationmean_error,
 const double* const combination_mean,
 const TMatrixD& sigma_s_matrix,
 const std::vector<std::vector<int> >& combo3bar_v);
#endif
