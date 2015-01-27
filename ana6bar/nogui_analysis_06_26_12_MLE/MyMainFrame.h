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
#include <TTree.h>
#include <TMacro.h>
#include <TMinuit.h>
#include "macro.h"
#include <RooLandau.h> 
#include <RooNumConvPdf.h>
#include <RooDataHist.h>
#include <RooBinning.h>
#include <RooAbsPdf.h>
#include <RooRealVar.h>
#include <RooArgSet.h>
#include <RooCmdArg.h>
#include <RooGaussian.h>
#include <RooMsgService.h>
#include "RooDataSet.h"
#include "RooRealVar.h"
#include "RooGaussian.h"
#include "RooGlobalFunc.h"
#include "RooFitResult.h"
#include "RooProdPdf.h"
#include "RooCmdArg.h"
#include "RooMsgService.h"



        using namespace RooFit;
        using namespace std;

class MyMainFrame {
        RQ_OBJECT("MyMainFrame")
    private:
        macro macros;
        TGComboBox *fCombo;
        TGComboBox *fNumPoints;	
	TGCheckButton *estat;
	TGCheckButton *inc_langau;	
        TGHProgressBar *fHProg1;
	TGLabel *label_ref_pmt;
	TGNumberEntry *ref_pmt;
        TGTextButton *go;
	TGTextButton *input_file;
	TGTextButton *output_file;
        TGMainFrame *fMain;
	TGTextButton *exit;
	TGHorizontalFrame *hframe;
        TRootEmbeddedCanvas *fEcanvas;
//	TGNumberEntry *n_points;
        TGLabel *label_n_points;
	TString path;	
	Double_t bar_length[62];
	const char* npoints_char[27];
	short nfiles;
	std::string _current_file;
	std::string _out_file;
	std::string _out_dir;
	TGLabel *labelq;
	TGLabel *labelqout;
	TGLabel *labellength;
	Bool_t file_status;
	TTree *t21;
        public:
	Double_t GetADCoffsetcut(TH1 *h);
	Double_t GetTDCrightcut(TH1 *h);
	Double_t GetTDCleftcut(TH1 *h);
	TH1*  Smooth_fun(TH1 *h, Double_t bin_num);
	Double_t landauconvgauss(TH1I *h, Double_t &err);
	Double_t myFunction(TH1 *h);
	Int_t setnum_inp;
	Int_t npoints_inp;
	bool langau_inp;
	bool outtree_inp;
	string inpfile_inp;
	string outfile_inp;
	
        void MainFrame(const TGWindow *p,UInt_t w,UInt_t h,Int_t setnum_in, Int_t npoints_in, bool langau_in, bool outtree_in, string inpfile_in, string outfile_in);
        void MainFrame();
        void DoDraw();
	void OpenFile();
	void OutFile();
	void t20tot21();
};
