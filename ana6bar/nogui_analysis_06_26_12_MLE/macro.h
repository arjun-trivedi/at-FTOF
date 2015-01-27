#include <TGFrame.h>
#include <RQ_OBJECT.h>
#include <TRootEmbeddedCanvas.h>
#include <TGNumberEntry.h>
#include <sstream>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <stdio.h>
#include <TGLabel.h>
#include <TGProgressBar.h>
#include <TGComboBox.h>
#include <TH1.h>
#include <TH2.h>
#include <TTree.h>
#include <TMacro.h>
#include <TGraphErrors.h>
#include <TLatex.h>
#include <TCanvas.h>

class macro {
        RQ_OBJECT("macro")
    private:
        public:
	TMacro* TDC_plot(const char* name, Double_t xmin, Double_t xmax, Double_t ymax);
	void TDC_write(const char* name, const char* _out_dir, TH1D *hist, Double_t xmin, Double_t xmax, Double_t ymax, TCanvas* &c1);
	TMacro* PositionCut_plot(char* name, Double_t mean, Double_t sigma);
	void PositionCut_write(char* name, const  char* _out_dir, Double_t mean, Double_t sigma, TH2D *hist_diff1vsdiff6);
	TMacro* resol_cont_plot(char* name);
	void resol_cont_write(char* name,  const char* _out_dir, TH1D* hist[6]);
	TMacro* tw_params_plot();
	void tw_params_write(TH1D* lambda1dn[12], const char* _out_dir);
	TMacro* tw_params_plot_new();
	TMacro* ADC_plot(const char* name, Double_t xmin, Double_t ymax);
	TMacro* att_plot(const char* name);
	void att_write(const char* name, const char* _out_dir, TGraphErrors *Tg_max, TCanvas* &c1, Short_t k, Float_t &twopoints);
	TH1*  Smooth_fun(TH1 *h, Double_t bin_num);
	Double_t myFunction(TH1 *h);
};
