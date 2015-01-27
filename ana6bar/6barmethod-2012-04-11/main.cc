/*
  This is the monolithic program for calculating the 6 bar individual
  resolution by the matrix and mean methods, and finding the means of
  each averaging over position.

  The input arguments should be a sequence of output files from Gleb's
  analysis program; each filename should be preceded by an argument
  flag specifying the logical bar ordering (the physical bar ordering
  is the order in which the bars were positioned while the data run
  was in progress; the logical bar ordering keeps track of the bar
  labels after we permute the physical ordering so as to have data for
  the complementary run).  There should be 2 shortcut flags: -n for
  normal ordering, and -c for complementary; -p will allow the user to
  specify a custom bar ordering by typing in a permutation of the
  integers 1-6 without spaces.

  The output of the program will be two files: a .root file containing
  histograms and TGraphErrors of the resolutions of the 3-bar
  combinations, the 6 individual bars as found via the matrix method,
  and as found via the mean method.  (The mean method calculates the
  resolution of each bar by taking the mean of all the 3-bar
  combinations which involve the bar.)  The output file name prefix
  must be specified via the -o flag.
 */

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstring>
#include <getopt.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <TFile.h>
#include <TH1D.h>
#include <TF1.h>
#include <TDirectory.h>
#include <TMatrixD.h>
#include <TCanvas.h>
#include "sigma6barfunctions.hh"

using namespace std;

char glebnew_histogram_prefix[] = "resol";
char glebnew_directory_name[] = "fullbar_tw";

void printhelpmsg()
{
  cout
    << "Options:" << endl;
  cout
    << "-h, --help:\t\tShow this help message" << endl
    << "-n, --normal:\t\tSpecify an input file with normal bar ordering" << endl
    << "-c, complementary:\tSpecify an input file with complementary bar ordering" << endl
    << "-p, --permutation:\tSpecify a custom bar permutation" << endl
    << "-o, --outputfile:\tSpecify the output file prefix (without .tar.gz)" << endl << endl
    << "This program takes any number of Gleb's analysis program's output"
    << endl
    << "files as input.  Each input filename must be preceded by a -n, -c,"
    << endl
    << "or -p flag.  When using the -p flag, the custom permutation should"
    << endl
    << "be given first as a sequence of 6 integers 1-6 without spacing"
    << endl
    << "(with a space between the sequence and the input filename)"
    << endl
    << "and then the filename should be given." << endl;
}

void histconfig(TH1* h)
{
  const char xaxistitle[] = "Position (cm)";
  const char yaxistitle[] = "Resolution (ps)";
  h->GetXaxis()->SetTitleSize(0.04);
  h->GetYaxis()->SetTitleSize(0.04);
  h->GetXaxis()->SetTitle(xaxistitle);
  h->GetYaxis()->SetTitle(yaxistitle);
}

//Calculate the error of a fit
double calcerror(TF1* f, TH1D* h)
{
  const double nfree = f->GetNpar(); //degrees of freedom
  const double npoints = h->GetNbinsX();
  double ss = 0;
  for(int i = 1; i <= npoints; ++i) {
    double x = h->GetBinLowEdge(i)+(h->GetBinWidth(i)/2.);
    double delta = h->GetBinContent(i)-f->Eval(x);
    ss += delta*delta;
  }
  return sqrt(ss/(npoints-nfree));
}

struct GlebAnaFile {
  TFile* file;
  string permutation;
  GlebAnaFile(const string& name, const string& perm)
  {
    file = new TFile(name.c_str(),"READ");
    permutation = perm;
  }
  ~GlebAnaFile()
  {
    file->Close();
    delete file;
  }
  static const string normorder;
  static const string comporder;
};
const string GlebAnaFile::normorder = "123456";
const string GlebAnaFile::comporder = "321654";

struct Combo3Bar {
  TH1D* hist;
  vector<int> bars; //top, middle, bottom bars are [0], [1], and [2]
  //respectively
  Combo3Bar(TDirectory* dir, const vector<int>& v)
    : bars(v)
  {
    stringstream ss;
    ss << glebnew_histogram_prefix << "_" << bars[0] << "_" << bars[1] << "_" << bars[2] << "_cont";
    //to change back to non-continuous version, just remove the _cont
    //from ss
    hist = (TH1D*) dir->Get(ss.str().c_str());
  }
  ~Combo3Bar() {};

  double GetBin(int bin)
  {
    return this->hist->GetBinContent(bin);
    //make sure that bin is between 1 and hist->GetNbinsX()
  }
};

double calc_hist_mean(TH1* hist)
{
  double sum = 0;
  double count = hist->GetNbinsX();
  for(int bin = 1; bin <= count; ++bin) {
    sum += hist->GetBinContent(bin);
  }
  return sum/count;
}

int main(int argc, char** argv)
{
  if(argc == 1) {
    printhelpmsg();
    return 1;
  }

  list<string> outputfiles;
  list<TH1*> normal3barhists; //normal order 3-bar combo hists
  list<TH1*> comp3barhists; //complementary order 3-bar combo hists

  string outputfileprefix;
  vector<GlebAnaFile*> inputfiles;
  TFile* masteroutputfile;
  ofstream* meanoutputfile;
  //arg parsing
  const int numopts=5;
  option longopts[numopts];
  char shortopts[] = "hn:c:p:o:";
  for(int i = 0; i < numopts; ++i) {
    longopts[i].flag=0;
  }
  longopts[0].name = "help";
  longopts[0].has_arg = no_argument;
  longopts[0].val = 'h';
  
  longopts[1].name = "normal";
  longopts[1].has_arg = required_argument;
  longopts[1].val = 'n';

  longopts[2].name = "complementary";
  longopts[2].has_arg = required_argument;
  longopts[2].val = 'c';

  longopts[3].name = "permutation";
  longopts[3].has_arg = required_argument;
  longopts[3].val = 'p';

  longopts[4].name = "outputfile";
  longopts[4].has_arg = required_argument;
  longopts[4].val = 'o';

  //process arguments:
  char optchar;
  while( (optchar = getopt_long(argc,argv,shortopts,longopts,0)) != -1 && optchar != '?') {
    switch(optchar) {
    case 'h':
      printhelpmsg();
      return 1;
      break;
    case 'n':
      inputfiles.push_back(new GlebAnaFile(optarg, GlebAnaFile::normorder));
      break;
    case 'c':
      inputfiles.push_back(new GlebAnaFile(optarg, GlebAnaFile::comporder));
      break;
    case 'p':
      inputfiles.push_back(new GlebAnaFile(argv[optind],optarg));
      break;
    case 'o':
      {
	static int numoutfiles = 0;
	if(numoutfiles==0) {
	  outputfileprefix = optarg;
	  //stringstream ss;
	  //ss << optarg;
	  masteroutputfile = new TFile("master.root",
				       "RECREATE");
	  meanoutputfile = new ofstream("means.dat");
	  outputfiles.push_back("master.root");
	  outputfiles.push_back("means.dat");
	}
	++numoutfiles;
      }
      break;
    }
  }
  
  const int numinputfiles = inputfiles.size();
  const int numequations = 6*numinputfiles; //there are 6 equations per file
  //per point along the bar.  Make sure to choose compatible input files;
  //i.e. analyze each file with the same number of points along the bar

  //vector holding Gleb's results  
  vector<Combo3Bar*> combo3barv;
  double possiblecombos[6][3];
  possiblecombos[0][0] = 1;
  possiblecombos[0][1] = 2;
  possiblecombos[0][2] = 3;
  possiblecombos[1][0] = 2;
  possiblecombos[1][1] = 3;
  possiblecombos[1][2] = 4;
  possiblecombos[2][0] = 3;
  possiblecombos[2][1] = 4;
  possiblecombos[2][2] = 5;
  possiblecombos[3][0] = 4;
  possiblecombos[3][1] = 5;
  possiblecombos[3][2] = 6;
  possiblecombos[4][0] = 1;
  possiblecombos[4][1] = 3;
  possiblecombos[4][2] = 5;
  possiblecombos[5][0] = 2;
  possiblecombos[5][1] = 4;
  possiblecombos[5][2] = 6;
  for(int fileno = 0; fileno < numinputfiles; ++fileno) {
    bool normfile=false;
    bool compfile=false;
    if(inputfiles[fileno]->permutation==GlebAnaFile::normorder)
      normfile=true;
    else if(inputfiles[fileno]->permutation==GlebAnaFile::comporder)
      compfile=true;
    TDirectory* d = (TDirectory*) inputfiles[fileno]
      ->file->Get(glebnew_directory_name);
    for(int combo = 0; combo < 6; ++combo) {
      vector<int> combov(3);
      vector<int> physcombov(3);
      for(int i = 0; i < 3; ++i) {
	stringstream sstmp;
	sstmp << inputfiles[fileno]->permutation[possiblecombos[combo][i]-1];
	physcombov[i]=possiblecombos[combo][i];
	int tmp;
	sstmp >> tmp;
	combov[i] = tmp;
      }
      combo3barv.push_back(new Combo3Bar(d,physcombov));
      combo3barv[combo3barv.size()-1]->bars=combov;
      if(normfile)
	normal3barhists.push_back(combo3barv[combo3barv.size()-1]->hist);
      else if(compfile)
	comp3barhists.push_back(combo3barv[combo3barv.size()-1]->hist);
    }
  }
  //combination mean method and matrix method result vectors:
  vector<TH1D*> meanmethodv(6);
  vector<TH1D*> matrixmethodv(6);
  const int numbins = combo3barv[0]->hist->GetNbinsX();
  const int topbin = numbins;
  const double loedge = combo3barv[0]->hist->GetBinLowEdge(1);
  const double hiedge = combo3barv[0]->hist->GetBinLowEdge(topbin)+combo3barv[0]->hist->GetBinWidth(topbin);
  for(int i = 0; i < 6; ++i) {
    stringstream combomeanname, matrixname, combomeantitle, matrixtitle;
    combomeanname << "combinationmeanmethod_hist_" << i+1;
    matrixname << "matrixmethod_hist_" << i+1;
    combomeantitle << "Histogram for Combination Mean Method for Bar " << i+1;
    matrixtitle << "Histogram for Matrix Method for Bar " << i+1;
    meanmethodv[i] = new TH1D(combomeanname.str().c_str(),
			      combomeantitle.str().c_str(),
			      numbins,
			      loedge,
			      hiedge);
    matrixmethodv[i] = new TH1D(matrixname.str().c_str(),
				matrixtitle.str().c_str(),
				numbins,
				loedge,
				hiedge);
  }

  //generate coefficient matrix:
  TMatrixD coef;
  vector<vector<int> > combos;
  for(int i = 0; i < numequations; ++i) {
    combos.push_back(combo3barv[i]->bars);
  }
  GenerateCoefficientMatrix(coef,combos);

  //Analysis Section:
  double* combomean = new double[6];
  double* combomean_error = new double[6];
  for(int point = 1; point <= numbins; ++point) {
    //matrix method:
    TMatrixD sigma_s(numequations,1);
    double sigma_s_array[numequations];
    for(int i = 0; i < numequations; ++i) {
      sigma_s_array[i] = combo3barv[i]->GetBin(point);
    }
    sigma_s.SetMatrixArray(sigma_s_array);
    TMatrixD matrixmethodm;
    calc_sigmabars(coef,sigma_s,matrixmethodm);
    double sigma_s_error[numequations];
    for(int ierr = 0; ierr < numequations; ++ierr) {
      sigma_s_error[ierr] = combo3barv[ierr]->hist->GetBinError(point);
    }
    TMatrixD sigma_s_error_matrix(numequations,1);
    sigma_s_error_matrix.SetMatrixArray(sigma_s_error);
    TMatrixD matrixmethoderrorm(6,1);
    calc_sigmabars_error(coef,
			 matrixmethodm,
			 sigma_s,
			 sigma_s_error_matrix,
			 matrixmethoderrorm);
    for(int bar = 0; bar < 6; ++bar) {
      matrixmethodv[bar]->SetBinContent(point,matrixmethodm(bar,0));
      matrixmethodv[bar]->SetBinError(point,matrixmethoderrorm(bar,0));
    }
    //mean method:
    calc_CombinationMean(combomean, sigma_s, combos);
    calc_CombinationMean_Error(combomean_error,
			       combomean,
			       sigma_s,
			       combos);
    for(int bar = 0; bar < 6; ++bar) {
      meanmethodv[bar]->SetBinContent(point,combomean[bar]);
      meanmethodv[bar]->SetBinError(point,combomean_error[bar]);
    }
  }
  //  delete[] combomean;
  //delete[] combomean_error;

  //Calculate means:
  TH1D matrixmeanhist("matrixmeanhist","Histogram of matrix method means",
		      6,0.5,6.5);
  TH1D meanmeanhist("meanmeanhist","Histogram of mean method means",
		    6,0.5,6.5);
  TH1D altmatrixmeanhist("altmatrixmeanhist","Histogram of alternative matrix mean method means",6,0.5,6.5);
  for(int bar = 1; bar <= 6; ++bar) {
    matrixmeanhist.SetBinContent
      (bar,
       calc_hist_mean(matrixmethodv[bar-1]));
    meanmeanhist.SetBinContent
      (bar,
       calc_hist_mean(meanmethodv[bar-1]));
  }
  TMatrixD sigma_s_mean(numequations,1);
  double sigma_s_mean_array[numequations];
  TMatrixD altmatrixmeanm(6,1); //alternative mean calculation
  for(int i = 0; i < numequations; ++i) {
    sigma_s_mean_array[i] = calc_hist_mean(combo3barv[i]->hist);
  }
  sigma_s_mean.SetMatrixArray(sigma_s_mean_array);
  calc_sigmabars(coef,sigma_s_mean,altmatrixmeanm);
  for(int bar = 1; bar <= 6; ++bar) {
    altmatrixmeanhist.SetBinContent(bar,altmatrixmeanm(bar-1,0));
  }
  //Form position-dependent mean histogram of all 3-bar combos
  TH1D* posmeanhist = new TH1D("posmeanhist","Position-dependent 3-bar combination mean",numbins,loedge,hiedge);
  const int numcombos = combo3barv.size();
  for(int bin = 1; bin <= numbins; ++bin) {
    double val=0;
    for(int combo = 0; combo < numcombos; ++combo) {
      val+=combo3barv[combo]->hist->GetBinContent(bin);
    }
    posmeanhist->SetBinContent(bin,(double) val/(double) numcombos);
  }
  //Fit all histograms and show error bars
  //posmeanhist, matrixmethodv, meanmethodv,combo3barv
  //Fit:
  posmeanhist->Fit("pol2");
  for(int i = 0; i < matrixmethodv.size(); ++i) {
    matrixmethodv[i]->Fit("pol2");
  }
  for(int i = 0; i < meanmethodv.size(); ++i) {
    meanmethodv[i]->Fit("pol2");
  }
  for(int i = 0; i < numcombos; ++i) {
    combo3barv[i]->hist->Fit("pol2");
  }
  //Error Bars:
  TF1* posmeanfit = posmeanhist->GetFunction("pol2");
  vector<TF1*> matrixmethodfits(matrixmethodv.size());
  for(int i = 0; i < matrixmethodfits.size(); ++i) {
    matrixmethodfits[i]=matrixmethodv[i]->GetFunction("pol2");
  }
  vector<TF1*> meanmethodfits(meanmethodv.size());
  for(int i = 0; i < meanmethodv.size(); i++) {
    meanmethodfits[i]=meanmethodv[i]->GetFunction("pol2");
  }
  vector<TF1*> combo3barfits(numcombos);
  for(int i = 0; i < numcombos; ++i) {
    combo3barfits[i]=combo3barv[i]->hist->GetFunction("pol2");
  }
  const double posmeanerror = calcerror(posmeanfit,posmeanhist);
  vector<double> matrixmethoderror(matrixmethodv.size());
  for(int i = 0; i < matrixmethodv.size(); ++i) {
    matrixmethoderror[i]=calcerror(matrixmethodfits[i],matrixmethodv[i]);
  }
  vector<double> meanmethoderror(meanmethodv.size());
  for(int i = 0; i < meanmethodv.size(); ++i) {
    meanmethoderror[i]=calcerror(meanmethodfits[i],meanmethodv[i]);
  }
  vector<double> combo3barerror(numcombos);
  for(int i = 0; i < numcombos; ++i) {
    combo3barerror[i]=calcerror(combo3barfits[i],combo3barv[i]->hist);
  }
  //Set errors in histograms:
  for(int bin = 1; bin <= posmeanhist->GetNbinsX(); ++bin) {
    posmeanhist->SetBinError(bin,posmeanerror);
  }
  for(int i = 0; i < matrixmethodv.size(); ++i) {
    for(int bin = 1; bin <= matrixmethodv[i]->GetNbinsX(); ++bin) {
      matrixmethodv[i]->SetBinError(bin,matrixmethoderror[i]);
    }
  }
  for(int i = 0; i < meanmethodv.size(); ++i) {
    for(int bin = 1; bin <= meanmethodv[i]->GetNbinsX(); ++bin) {
      meanmethodv[i]->SetBinError(bin,meanmethoderror[i]);
    }
  }
  for(int i = 0; i < numcombos; ++i) {
    for(int bin = 1; bin <= combo3barv[i]->hist->GetNbinsX(); ++bin) {
      combo3barv[i]->hist->SetBinError(bin,combo3barerror[i]);
    }
  }
  //Draw canvases of all histograms
  TCanvas *posmeancanvas = new TCanvas("posmeancanvas");
  posmeancanvas->cd();
  histconfig(posmeanhist);
  posmeanhist->Draw();
  {
    stringstream ss;
    ss << "PosDepMeanHist.png";
    outputfiles.push_back(ss.str());
    posmeancanvas->Print(ss.str().c_str());
  }
  vector<TCanvas*> matrixcanvas(matrixmethodv.size());
  vector<TCanvas*> meancanvas(meanmethodv.size());
  vector<TCanvas*> combo3barcanvas(numcombos);
  for(int i = 0; i < matrixcanvas.size(); ++i) {
    stringstream ss;
    ss << "matrixcanvas" << i;
    matrixcanvas[i] = new TCanvas(ss.str().c_str());
    matrixcanvas[i]->cd();
    histconfig(matrixmethodv[i]);
    matrixmethodv[i]->Draw();
    stringstream s;
    s << "MatrixMethodHist_" << i+1 << ".png";
    outputfiles.push_back(s.str());
    matrixcanvas[i]->Print(s.str().c_str());
  }
  for(int i = 0; i < meancanvas.size(); ++i) {
    stringstream ss;
    ss << "meancanvas" << i;
    meancanvas[i] = new TCanvas(ss.str().c_str());
    meancanvas[i]->cd();
    histconfig(meanmethodv[i]);
    meanmethodv[i]->Draw();
    stringstream s;
    s << "MeanMethodHist_" <<  i+1 << ".png";
    outputfiles.push_back(s.str());
    meancanvas[i]->Print(s.str().c_str());
  }
  for(int i = 0; i < numcombos; ++i) {
    stringstream ss;
    ss << "combo3barcanvas" << i;
    combo3barcanvas[i] = new TCanvas(ss.str().c_str());
    combo3barcanvas[i]->cd();
    histconfig(combo3barv[i]->hist);
    combo3barv[i]->hist->Draw();
    stringstream s;
    s << "3BarCombo_" << combo3barv[i]->bars[0] << combo3barv[i]->bars[1] << combo3barv[i]->bars[2] << ".png";
    outputfiles.push_back(s.str());
    combo3barcanvas[i]->Print(s.str().c_str());
  }
  //Write all histograms to file:
  masteroutputfile->cd();
  posmeanhist->Write();
  for(int i = 0; i<numequations; ++i) {
    combo3barv[i]->hist->Write();
  }
  for(int i = 0; i<6; ++i) {
    matrixmethodv[i]->Write();
    meanmethodv[i]->Write();
  }
  matrixmeanhist.Write();
  meanmeanhist.Write();
  altmatrixmeanhist.Write();
  for(int i = 0; i < 6; ++i) {
    *meanoutputfile << matrixmeanhist.GetBinContent(i+1) << endl;
  }
  for(int i = 0; i < 6; ++i) {
    *meanoutputfile << meanmeanhist.GetBinContent(i+1) << endl;
  }
  *meanoutputfile << calc_hist_mean(&matrixmeanhist) << endl; //matrix method

  //*meanoutputfile << calc_hist_mean(&meanmeanhist) << endl;  
  /* mean method mean not needed, Dr. Gothe wants mean of normal and
     mean of complementary separately */
  list<double> normmeans;
  list<double> compmeans;
  for(list<TH1*>::iterator i = normal3barhists.begin();
      i != normal3barhists.end();
      ++i) {
    normmeans.push_back(calc_hist_mean(*i));
  }
  for(list<TH1*>::iterator i = comp3barhists.begin();
      i != comp3barhists.end();
      ++i) {
    compmeans.push_back(calc_hist_mean(*i));
  }
  double normmean = 0;
  double compmean = 0;
  double count = 0;
  for(list<double>::iterator i = normmeans.begin();
      i != normmeans.end();
      ++i) {
    normmean += *i;
    ++count;
  }
  normmean /= count;
  count = 0;
  for(list<double>::iterator i = compmeans.begin();
      i != compmeans.end();
      ++i) {
    compmean += *i;
    ++count;
  }
  compmean /= count;

  if(normmeans.size())
    *meanoutputfile << normmean << endl;
  if(compmeans.size())
    *meanoutputfile << compmean << endl;
  
  *meanoutputfile << calc_hist_mean(posmeanhist) << endl; //3-bar combos
  //must delete histograms before closing file
  delete posmeanhist;
  for(int i = 0; i < meanmethodv.size(); ++i) {
    delete meanmethodv[i];
  }
  for(int i = 0; i < matrixmethodv.size(); ++i) {
    delete matrixmethodv[i];
  }
  masteroutputfile->Close();
  meanoutputfile->close();
  //CLEANUP:
  for(int i = 0; i < inputfiles.size(); ++i) {
    delete inputfiles[i];
  }
  delete masteroutputfile;
  delete meanoutputfile;
  for(int i = 0; i < combo3barv.size(); ++i) {
    delete combo3barv[i];
  }
  //Apparently, ROOT auto-magically deletes histograms associated with
  //a file when the file is closed, so since these two are associated
  //with masteroutputfile, they're already gone at this point:
  //delete meanmethodv[i];
  //delete matrixmethodv[i];

  //Create gzipped-tarball of the results instead of filling the
  //directory with files

  //Fork process, parent waits for child to return, child process
  //creates tarball
  //uses tar -cfz outputfileprefix.tar.gz <list of files>
  pid_t pid = fork();
  int rv;
  if(pid) {//parent process
    wait(&rv);
  }
  else {//child process
    //create array of arguments:
    const int numtarfiles = outputfiles.size();
    const int numtarargs = numtarfiles+4; //tar, -cfz, .tar.gz, files, null
    char** tarargs = new char*[numtarargs];
    for(int i = 0; i < numtarargs-1; ++i) {
      tarargs[i] = new char[100]; //100 chars should suit about anyone
    }
    tarargs[numtarargs-1] = 0;
    strcpy(tarargs[0],"tar");
    strcpy(tarargs[1],"-czf");
    string tarfilename = outputfileprefix;
    tarfilename=tarfilename+".tar.gz";
    strcpy(tarargs[2],tarfilename.c_str());
    int argi = 3;
    for(list<string>::iterator i = outputfiles.begin();
	i != outputfiles.end();
	++i) {
      strcpy(tarargs[argi],(*i).c_str());
      ++argi;
    }
    execvp("tar",tarargs);
  }
  //delete files other than tarball
  for(list<string>::iterator i = outputfiles.begin();
      i != outputfiles.end();
      ++i) {
    unlink((*i).c_str()); //deletes files, proceed with caution
  }
  return 0;
}
