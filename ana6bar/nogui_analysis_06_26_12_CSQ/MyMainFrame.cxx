#include "TROOT.h"
#include "TFile.h"
#include "TLine.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TF1.h"
#include "TF2.h"
#include "TF3.h"
#include "TMacro.h"
#include "TCanvas.h"
#include "TVirtualFitter.h"
#include "TMath.h"
#include "TGraphErrors.h"
#include "TGraph.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TH2F.h"
#include "TH2D.h"
#include "TH3F.h"
#include "TText.h"
#include "TStyle.h"
#include "TGObject.h"
#include "TObject.h"
#include "TSystem.h"
#include "TMinuit.h"
#include <TRint.h>
#include <stdio.h>
#include <dlfcn.h>
#include <TGClient.h>
#include <TCanvas.h>
#include <TRandom.h>
#include <TGButton.h>
#include <TGFrame.h>
#include <TRootEmbeddedCanvas.h>
#include <TGButtonGroup.h>
#include <RQ_OBJECT.h>
#include <TGNumberEntry.h>
#include <TGProgressBar.h>
#include <TGLabel.h>
#include <stdio.h>
#include <dlfcn.h>
#include "MyMainFrame.h"
#include <sstream>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <TGFileDialog.h>
#include <GuiTypes.h>
#include <TGDoubleSlider.h>
#include <TGComboBox.h>
#include <TLeaf.h>
#include <TBranch.h>
#include <TError.h> 
#include <auto_ptr.h>
#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "TCanvas.h"
#include "RooPlot.h"
#include "TAxis.h"
#include <RooLandau.h> 
#include <RooNumConvPdf.h>
#include <RooDataHist.h>
#include "RooBinning.h"
#include <sys/types.h>
#include <wait.h>
#include <unistd.h>
#include <cstring>
#include <getopt.h>
#include <cstdlib>




 using namespace std; 
 

 
   

   Double_t g2tw(Double_t *x, Double_t *par) {
   Double_t r1 = Double_t((x[0]-par[0])*(x[0]-par[0])/par[1]/par[1]);
   Double_t r2 = Double_t((x[1]-par[2])*(x[1]-par[2])/par[3]/par[3]);
   return par[4]+r1+r2;
   }


 
    void MyMainFrame::MainFrame(const TGWindow *p,UInt_t w,UInt_t h,Int_t setnum_in, Int_t npoints_in, bool langau_in, bool outtree_in, string inpfile_in, string outfile_in) {
        
	setnum_inp = setnum_in;
	npoints_inp = npoints_in;
	langau_inp = langau_in;
	outtree_inp = outtree_in;
	inpfile_inp = inpfile_in;
	outfile_inp = outfile_in;
	
	

	
	if (setnum_inp ==0) {

	RooMsgService::instance().getStream(1).removeTopic(Minimization);
    
	RooMsgService::instance().setGlobalKillBelow(RooFit::ERROR); 
	
	RooMsgService::instance().setSilentMode(1);



    TString progpath(gSystem->pwd());
    path = progpath;

        };

bar_length[0]=17.27;
bar_length[1]=23.62; 
bar_length[2]=30.08;
bar_length[3]=36.43;
bar_length[4]=42.89;
bar_length[5]=49.24; 
bar_length[6]=55.70;
bar_length[7]=62.05;
bar_length[8]=68.51;
bar_length[9]=74.86; 
bar_length[10]=81.32;
bar_length[11]=87.67;
bar_length[12]=94.13;
bar_length[13]=100.48; 
bar_length[14]=106.94;
bar_length[15]=113.29;
bar_length[16]=119.75;
bar_length[17]=126.10; 
bar_length[18]=132.56;
bar_length[19]=138.91;
bar_length[20]=145.37;
bar_length[21]=151.72; 
bar_length[22]=158.17;
bar_length[23]=164.52;
bar_length[24]=170.98;
bar_length[25]=177.33; 
bar_length[26]=183.79;
bar_length[27]=190.14;
bar_length[28]=196.60;
bar_length[29]=202.95; 
bar_length[30]=209.41;
bar_length[31]=215.76;
bar_length[32]=222.22;
bar_length[33]=228.57;
bar_length[34]=235.03;
bar_length[35]=241.38; 
bar_length[36]=247.84;
bar_length[37]=254.19;
bar_length[38]=260.65;
bar_length[39]=267.00; 
bar_length[40]=273.46;
bar_length[41]=279.81;
bar_length[42]=286.27;
bar_length[43]=292.62; 
bar_length[44]=299.08;
bar_length[45]=305.43;
bar_length[46]=311.88;
bar_length[47]=318.23; 
bar_length[48]=324.69;
bar_length[49]=331.04;
bar_length[50]=337.50;
bar_length[51]=343.85; 
bar_length[52]=350.31;
bar_length[53]=356.66; 
bar_length[54]=363.12;
bar_length[55]=369.47;
bar_length[56]=375.93;
bar_length[57]=382.28; 
bar_length[58]=388.74;
bar_length[59]=395.09;
bar_length[60]=401.55;
bar_length[61]=407.90; 





if (setnum_inp ==0) {

   
    // Create a main frame
    fMain = new TGMainFrame(p,w,h,kHorizontalFrame);
    fMain->SetWMSize(720,440); 
    // Create canvas widget
   // fEcanvas = new TRootEmbeddedCanvas("Ecanvas",fMain,200,200);
   // fMain->AddFrame(fEcanvas, new TGLayoutHints(kLHintsExpandX| kLHintsExpandY,10,10,10,1));
    // Create a horizontal frame widget with buttons
    hframe = new TGHorizontalFrame(fMain,720,440);
    go = new TGTextButton(hframe,"&Go");
    go->Connect("Clicked()","MyMainFrame",this,"DoDraw()");
    hframe->AddFrame(go, new TGLayoutHints(kLHintsRight,0,0,410,0));
    exit = new TGTextButton(hframe,"&Exit",
    "gApplication->Terminate(0)");    
    hframe->AddFrame(exit, new TGLayoutHints(kLHintsRight,250,0,410,0));
    go->SetState(kButtonDisabled);
    //TGVerticalFrame *controls = new TGVerticalFrame(fMain,400,400);
    //controls->AddFrame(controls, new TGLayoutHints(kLHintsRight | kLHintsExpandY, 

    
    

    
    
  // a popup menu
  
    TGLayoutHints *fMenuBarLayout = new TGLayoutHints(kLHintsTop | kLHintsExpandX);
    TGLayoutHints *fMenuBarItemLayout = new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 4, 0, 0);
    TGLayoutHints *fMenuBarHelpLayout = new TGLayoutHints(kLHintsTop | kLHintsRight);
  //  TGPopupMenu *fMenuFile = new TGPopupMenu(gClient->GetRoot());


// adding menu entries
 
  


   
      file_status=0;
      
      input_file = new TGTextButton(hframe,"&Input_file");
    input_file ->Connect("Clicked()","MyMainFrame",this,"OpenFile()");
    hframe->AddFrame(input_file, new TGLayoutHints(kLHintsLeft,10,0,310,0));  
     
     
      output_file = new TGTextButton(hframe,"&Outut_file");
    output_file ->Connect("Clicked()","MyMainFrame",this,"OutFile()");
    hframe->AddFrame(output_file, new TGLayoutHints(kLHintsLeft,-58,68,370,0));        

         
        fHProg1 = new TGHProgressBar(hframe,TGProgressBar::kStandard,300);      
        fHProg1->Move(10,250);
	fHProg1->SetBarColor("lightblue");
	
	fHProg1->SetForegroundColor(0xff6633);   
        fHProg1->ShowPosition(kTRUE,kTRUE,"%.5f");

    estat = new TGCheckButton(hframe, " include tree \n to the \n output file",1);
//    estat->SetState(kButtonUp);
    

   
    hframe->AddFrame(estat, new TGLayoutHints(kLHintsRight,-85,180,150,0));



    inc_langau = new TGCheckButton(hframe, " perform \n langau \n fit",1);
//    estat->SetState(kButtonUp);
    

   
    hframe->AddFrame(inc_langau, new TGLayoutHints(kLHintsRight,-85,180,150,0));



  
    ref_pmt = new TGNumberEntry(hframe,5);
    TGNumberFormat::ELimit lim;   
    lim = TGNumberFormat::kNELLimitMinMax;
    ref_pmt->SetLimits(lim,1,12);
    ref_pmt->SetLimitValues(1,12);
       
   hframe->AddFrame(ref_pmt, new TGLayoutHints(kLHintsLeft | kLHintsTop,-43,43,70,0));
   
   

    ref_pmt->SetFormat(TGNumberFormat::kNESInteger,TGNumberFormat::kNEANonNegative);
    
    label_ref_pmt = new TGLabel(hframe, "ref pmt");
    hframe->AddFrame(label_ref_pmt, new TGLayoutHints(kLHintsLeft, -100,105,50,0));
    
    
    
    
    
    
    

    
    
    
    
    
    
    
    
    
    
    
    
    
	    
fMain->AddFrame(hframe, new TGLayoutHints(kLHintsCenterX,0,0,0,0));
    	


    short i;
    char tmp[20];
// combo box layout hints
TGLayoutHints *fLcombo = new TGLayoutHints(kLHintsTop | kLHintsLeft,150,-300,72,0);
TGLayoutHints *fLcombo1 = new TGLayoutHints(kLHintsTop | kLHintsLeft,205,-100,146,0);
// combo box widget
fCombo = new TGComboBox(hframe,100);
for (i = 0; i < 62; i++) {
    ostringstream cmd;
    cmd << "bar #" << i+1 << " (" << bar_length[i] << " cm)";
fCombo->AddEntry(cmd.str().c_str(), i+1);
};
fCombo->Resize(150, 20);
// Entry3 is selected as current
fCombo->Select(17);
hframe->AddFrame(fCombo, fLcombo);


labellength = new TGLabel(hframe, "length of the bars");
    hframe->AddFrame(labellength, new TGLayoutHints(kLHintsLeft, 150,-300,50,0));
    
    
//    n_points = new TGNumberEntry(hframe,25);
//    n_points->SetLimits(lim,5,50);
//    n_points->SetLimitValues(5,50);
       
//   hframe->AddFrame(n_points, new TGLayoutHints(kLHintsLeft | kLHintsTop,203,-265,150,0));
   
   
fNumPoints = new TGComboBox(hframe,200);
for (i = 0; i < 130; i++) {
    ostringstream cmd;
    if ( i == 0 ) {
    cmd << "auto";
    } else {
    cmd << i+4;
    };
fNumPoints->AddEntry(cmd.str().c_str(), i+1);
};
fNumPoints->Resize(50, 20);
fNumPoints->Select(1);
//fNumPoints->Move(300,250);
hframe->AddFrame(fNumPoints, fLcombo1);

//    n_points->SetFormat(TGNumberFormat::kNESInteger,TGNumberFormat::kNEANonNegative);
    
    label_n_points = new TGLabel(hframe, "number of points");
    hframe->AddFrame(label_n_points, new TGLayoutHints(kLHintsLeft, 50,-360,125,0));    



	
    // Set a name to the main frame
    fMain->SetWindowName("6 bars analyser");
    // Map all subwindows of main frame
    hframe->Move(500,0); 
    fMain->MapSubwindows();
    
    // Initialize the layout algorithm
  
   fMain->Resize(fMain->GetDefaultSize());
   
    // Map main frame
    fMain->MapWindow(); 

};

if (setnum_inp !=0) {
DoDraw();
};

   
}

void MyMainFrame::DoDraw() {

 
 
       t20tot21(); 
   
   int i;
   short j; 
   
//TH1I *hist_adc[12];
vector <TH1I*> hist_adc; 
TH1D *hist_tdcdiff[6];
TH1I *hist_tdc[12];
TH1I *histtdc6 = new TH1I("histtdc6","histtdc6",40000, -20000.25, 19999.25);
Double_t tdc6_range;

 TBranch *event = t21->GetBranch("event");
 
    typedef struct {				
	Double_t tdc1_corr;
	Double_t tdc2_corr;
	Double_t tdc3_corr;
	Double_t tdc4_corr;
	Double_t tdc5_corr;
	Double_t tdc6_corr;
	Double_t tdc7_corr;
	Double_t tdc8_corr;
	Double_t tdc9_corr;
	Double_t tdc10_corr;
	Double_t tdc11_corr;
	Double_t tdc12_corr;							
	} EVENT_CORR;
		
    
    static EVENT_CORR event_corr;   
    

 TBranch *newBranch = t21-> Branch("event_corr",&event_corr,"tdc1_corr/D:tdc2_corr/D:tdc3_corr/D:tdc4_corr/D:tdc5_corr/D:tdc6_corr/D:tdc7_corr/D:tdc8_corr/D:tdc9_corr/D:tdc10_corr/D:tdc11_corr/D:tdc12_corr/D");
  ostringstream adc_num;
  ostringstream tdc_left;
  ostringstream tdc_right;  
  ostringstream tdc_num;  

   
  for (j=0; j<12; j++) { 
  adc_num << "adc" << j+1;
//hist_adc[j] = new TH1I(adc_num.str().c_str(),adc_num.str().c_str(),4096, -0.5, 4095.5);
  TH1I *qqq_adc = new TH1I(adc_num.str().c_str(),adc_num.str().c_str(),4096, -0.5, 4095.5); 
  hist_adc.push_back(qqq_adc);
//  qqq_adc->Delete();

  adc_num.str("");
   adc_num << "tdc" << j+1; 
hist_tdc[j] = new TH1I(adc_num.str().c_str(),adc_num.str().c_str(),40000, -20000.25, 19999.25);  
  adc_num.str("");
  if ( j % 2 == 0 ) {
  tdc_left << "(tdc" << j+1 << "-" << "tdc" << j+2 << ")/2";
  tdc_right << "tdc" << j+1 << "_" << "tdc" << j+2;
hist_tdcdiff[j/2] = new TH1D(tdc_right.str().c_str(),tdc_left.str().c_str(),40000, -20000.25, 19999.25);  
  tdc_left.str("");
  tdc_right.str("");
  };   
  };    
      
      cout << "events = " << event->GetEntries() << "\n";
       
  for (i=0; i<event->GetEntries(); i++) { 
  
   if (setnum_inp == 0) {  
   if (i%10 == 0) { 
   fHProg1->Increment(1000./8./Double_t(event->GetEntries()));
   }
   };
 
    event->GetEntry(i);


  for (j=0; j<12; j++) {   
  
  adc_num << "adc" << j+1;    

      hist_adc[j]->Fill(event->GetLeaf(adc_num.str().c_str())->GetValue(),1);
     adc_num.str("");

     
  adc_num << "tdc" << j+1;    
     if ( j != 5 ) {    
     hist_tdc[j]->Fill(event->GetLeaf(adc_num.str().c_str())->GetValue());
     } else {
     hist_tdc[j]->Fill(event->GetLeaf("tdc6")->GetValue()-event->GetLeaf("tdc7")->GetValue());
     histtdc6->Fill(event->GetLeaf("tdc6")->GetValue()-event->GetLeaf("tdc5")->GetValue());
     };     
     
      adc_num.str("");    
   if ( j % 2 == 0 ) {
  tdc_left << "tdc" << j+1;    
  tdc_right << "tdc" << j+2;
hist_tdcdiff[j/2]->Fill((event->GetLeaf(tdc_left.str().c_str())->GetValue()-event->GetLeaf(tdc_right.str().c_str())->GetValue())/2);  
  tdc_left.str(""); 
  tdc_right.str("");   
  };        
   };
    
    
    }; 
    
    TFile *outFile;
    if (setnum_inp == 0) {       
    outFile = new TFile(_out_file.c_str(),"UPDATE"); 
    } else {
    outFile = new TFile(outfile_inp.c_str(),"UPDATE");
    };
    TDirectory *dir =outFile->GetDirectory("full_bar");
//     hist_adc1->SetDirectory(dir);
     outFile->cd("full_bar");

//   vector<TH1I*>::iterator ita = hist_adc.begin();  
  for (j=0; j<12; j++) {  
//   TH1I *qqq_out;
//   qqq_out = hist_adc.at(j);
//   qqq_out->Delete();
     hist_adc[j]->SetDirectory(dir);    
     hist_adc[j]->Write();
//     hist_adc[j]->Delete();
//    hist_adc.erase(ita+j);
     };
     
    hist_adc.clear();

     
     
//     Smooth_fun(hist_tdcdiff[1],20)->Draw();
       
       Double_t tdcleftcut[6];
       Double_t tdcrightcut[6];
        Double_t tdccenter_nodiff[12];
//       Double_t tdcrightcut_nodiff[12];      
       Double_t diff;
       
   TH1 *qqq = Smooth_fun(histtdc6,20);     
  tdc6_range = GetTDCrightcut(qqq);
      qqq->Delete();  
        histtdc6->Delete(); 
	  
  for (j=0; j<12; j++) {       
       TH1 *qqq = Smooth_fun(hist_tdc[j],20);
       if (j%2 != 0) {
       tdccenter_nodiff[j] = GetTDCrightcut(qqq);
       } else {
       tdccenter_nodiff[j] = qqq->GetBinCenter(qqq->GetMaximumBin());
       };
//       tdcrightcut_nodiff[j] = GetTDCrightcut(qqq); 
       qqq->Delete();  
        hist_tdc[j]->Delete();    
       };             

gROOT->SetBatch(true); 


 TCanvas *c1 = new TCanvas("tdc_diff_canvas", "tdc_diff_canvas", 800, 600);
 c1->Divide(3,2);
 c1->cd();
 
  for (j=0; j<6; j++) {   
  c1->cd(j+1);     
       TH1 *qqq = Smooth_fun(hist_tdcdiff[j],20);
       tdcleftcut[j] = GetTDCleftcut(qqq);
       tdcrightcut[j] = GetTDCrightcut(qqq);
       qqq->Delete();
       diff = tdcrightcut[j] - tdcleftcut[j];
       hist_tdcdiff[j]->SetAxisRange(tdcleftcut[j]-diff,tdcrightcut[j]+diff,"X");
       hist_tdcdiff[j]->Draw();
       hist_tdcdiff[j]->Write();
       if ( j == 5 ) {
	TMacro *tdc1112cut;
	tdc1112cut = macros.TDC_plot("tdc11_tdc12",tdcleftcut[5],tdcrightcut[5],hist_tdcdiff[5]->GetMaximum());
	 tdc1112cut->Write();
	 tdc1112cut->Delete();
	 macros.TDC_write("tdc11_tdc12",_out_dir.c_str(),hist_tdcdiff[5],tdcleftcut[5],tdcrightcut[5],hist_tdcdiff[5]->GetMaximum(),c1);
	 };      
//       hist_tdcdiff[j]->Delete();
	};
	
	stringstream ss; 
	ss.str("");
	if (setnum_inp ==0) { 
        ss << _out_dir << "/" << "tdc_diff" << ".png";
	} else {
	ss << "tdc_diff" << ".png";
	};		
	c1->Print(ss.str().c_str());
	c1->Close();
	
	 for (j=0; j<6; j++) {    
	 hist_tdcdiff[j]->Delete();
	 };
	
	Double_t diff5 = int(tdcrightcut[5]-tdcleftcut[5]);
	Double_t diff0 = int(tdcrightcut[0]-tdcleftcut[0]);
  TH2D *hist_diff1vsdiff6 = new TH2D("tdcdiff1vstdcdiff6","(tdc1 - tdc2)/2 : (tdc11 - tdc12)/2",3*diff5, tdcleftcut[5]-0.25-diff5, tdcrightcut[5]-0.25+diff5,3*diff0, tdcleftcut[0]-0.25-diff0, tdcrightcut[0]-0.25+diff0);
  

  
        TH1D *histdiff1minusdiff6 = new TH1D("histdiff1minusdiff6","(tdc1 - tdc2)/2 - (tdc11 - tdc12)/2",3*(diff0+diff5),tdcleftcut[0]-tdcrightcut[5]-0.25-(diff0+diff5),tdcrightcut[0]-tdcleftcut[5]-0.25+(diff0+diff5));
  
  for (i=0; i<event->GetEntries(); i++) { 
   
   if (setnum_inp ==0) {
   if (i%10 == 0) {
   fHProg1->Increment(1000./8./Double_t(event->GetEntries()));
   };
   };
   
    event->GetEntry(i);
    
 hist_diff1vsdiff6->Fill((event->GetLeaf("tdc11")->GetValue()-event->GetLeaf("tdc12")->GetValue())/2.,(event->GetLeaf("tdc1")->GetValue()-event->GetLeaf("tdc2")->GetValue())/2.,1);   

histdiff1minusdiff6->Fill((event->GetLeaf("tdc1")->GetValue()-event->GetLeaf("tdc2")->GetValue()-(event->GetLeaf("tdc11")->GetValue()-event->GetLeaf("tdc12")->GetValue()))/2.,1);    

    
    };   	
    
    
	 histdiff1minusdiff6->Fit("gaus","Q0");
	 TF1 *fit = histdiff1minusdiff6->GetFunction("gaus");
      Double_t mean = fit->GetParameter(1);
      Double_t sigma = fit->GetParameter(2);
      TMacro *poscut_plot;
	poscut_plot = macros.PositionCut_plot("tdcdiff1vstdcdiff6",mean,0.5*sigma);

     
	poscut_plot->Write();
	poscut_plot->Delete(); 
	

//Example of file output
        ss.str("");
        ss << _out_dir << "/";
	
        if (setnum_inp == 0) {
	macros.PositionCut_write("tdcdiff1vstdcdiff6",ss.str().c_str(),mean,0.5*sigma,hist_diff1vsdiff6);
        } else {
	macros.PositionCut_write("tdcdiff1vstdcdiff6","",mean,0.5*sigma,hist_diff1vsdiff6);
	};
	
	
	
//End of output file example        

/* 	
       gROOT->ProcessLine( "gErrorIgnoreLevel = 1; " );
//       gErrorIgnoreLevel = -1;

       gErrorIgnoreLevel = kWarning;
       gROOT->SetBatch(true);
//       gROOT->cd(); 
       TCanvas *c1 = new TCanvas("c1");

//       TPostScript *ps = new TPostScript("file.ps",112);
//       ps->NewPage();
       c1->cd();
       hist_diff1vsdiff6->Draw();
       c1->Print("file.ps","v");
//       ps->Close();
//       gSystem->Exec("gs file.ps");

*/
	 
         hist_diff1vsdiff6->Write();
	 histdiff1minusdiff6->Write();
	 hist_diff1vsdiff6->Delete();
	 histdiff1minusdiff6->Delete();
//       hist_tdcdiff[0]->Draw();


// Starting loop over the bar
        

//	 int npoints = n_points->GetNumber();

         int npoints;
         
	 if (setnum_inp == 0) {
         npoints = fNumPoints->GetSelected()+3;;
	 
	 
         if (npoints == 4) {
	 npoints = (int)(bar_length[fCombo->GetSelected()-1]/3.);  
	 };	 
	 
	 } else {
	 if (npoints_inp == 0) {
	 npoints = (int)(bar_length[setnum_inp-1]/3.);
	 } else {
	 npoints = npoints_inp;
	 };
	 };
	 
	 cout << "npoints = " << npoints << "\n";
	 	 
	 Double_t delta = diff5/npoints;
	 
	 
	 
  TH2I *hist_diff1vsdiff6_point[npoints];  
// Creating ADC histograms
 
  vector<vector<TH1I*> > hist_adc_point;
  TH1 *hist_adc_point_smooth[12][npoints];  
  
  for (i=0; i<npoints; i++) {
  
   adc_num << "tdcdiff1vstdcdiff6" <<  "_point" << i+1; 
hist_diff1vsdiff6_point[i] = new TH2I(adc_num.str().c_str(),"(tdc1 - tdc2)/2 : (tdc11 - tdc12)/2",3*diff5, tdcleftcut[5]-0.25-diff5, tdcrightcut[5]-0.25+diff5,3*diff0, tdcleftcut[0]-0.25-diff0, tdcrightcut[0]-0.25+diff0);  
 adc_num.str("");
 
     adc_num << "point_" << i+1;     
     outFile->mkdir(adc_num.str().c_str()); 
       adc_num.str(""); 
 };
  


  
  for (j=0; j<12; j++) { 

  vector<TH1I*> vec_adc_point;  

  for (i=0; i<npoints; i++) {  
  
  adc_num << "adc" << j+1 << "point" << i+1;
  TH1I *qqq = new TH1I(adc_num.str().c_str(),adc_num.str().c_str(),4096, -0.5, 4095.5); 
  vec_adc_point.push_back(qqq);
  

  
  adc_num.str("");
  
  };
  
     hist_adc_point.push_back(vec_adc_point); 
  
  };  
  
//    hist_adc_point.push_back(vec_adc_point);
  
//     adc_num << "point_" << i+1;     
//     outFile->mkdir(adc_num.str().c_str());
//     TDirectory *dir =outFile->GetDirectory("full_bar");
     
//    double_rate->SetDirectory(dir);

//      adc_num.str("");  
  
//  };  


// Filling ADC histograms
  
  short ii;

  for (i=0; i<event->GetEntries(); i++) { 
  
    if (setnum_inp ==0) {
    if (i%10 == 0 ) {
    fHProg1->Increment(1000./8./Double_t(event->GetEntries()));
     };
     };
     
    event->GetEntry(i);

    Double_t diff_top = (event->GetLeaf("tdc1")->GetValue()-event->GetLeaf("tdc2")->GetValue())/2;
    Double_t diff_btm = (event->GetLeaf("tdc11")->GetValue()-event->GetLeaf("tdc12")->GetValue())/2;    	
    
    for (j=0; j<npoints; j++) {
    

    if (diff_top - diff_btm > mean - sigma) { 
    if (diff_top - diff_btm < mean + sigma) { 

    if (diff_btm > tdcleftcut[5] + j*delta) {
    if (diff_btm <= tdcleftcut[5] + (j+1)*delta) {   
    
    if (diff_top > tdcleftcut[5] + j*delta + mean) {    
    if (diff_top < tdcleftcut[5] + (j+1)*delta + mean) {        




    for (ii=0; ii<12; ii++) {
    
     adc_num << "adc" << ii+1;    
    hist_adc_point[ii][j]->Fill(event->GetLeaf(adc_num.str().c_str())->GetValue(),1);    
      adc_num.str("");     
    };

    };
    };
   
    
    };
    };
    
    
    };
    };
    
    
    

     };   
    
    }; 


// Writing ADC histograms to the file

     TDirectory *dir_out[npoints];  

  Double_t adc_low_cut[12][npoints];
    
  for (i=0; i<npoints; i++) {
  
     adc_num << "point_" << i+1;     
      dir_out[i] =outFile->GetDirectory(adc_num.str().c_str()); 
      outFile->cd(adc_num.str().c_str());
      adc_num.str(""); 

             
  for (j=0; j<12; j++) { 
  
   hist_adc_point_smooth[j][i] = Smooth_fun(hist_adc_point[j][i],30);
     adc_num << "adc" << j+1 << "point_" << i+1 << "_smooth";    
   hist_adc_point_smooth[j][i]->SetName(adc_num.str().c_str());
   hist_adc_point_smooth[j][i]->SetTitle(adc_num.str().c_str()); 
     adc_num.str(""); 
    adc_low_cut[j][i] = myFunction(hist_adc_point_smooth[j][i]); 
    
    TMacro *adcmacro;
     adc_num << "adc" << j+1 << "point" << i+1;    
    adcmacro = macros.ADC_plot(adc_num.str().c_str(),adc_low_cut[j][i],hist_adc_point_smooth[j][i]->GetMaximum());
    adc_num.str("");
   adcmacro->Write();
   adcmacro->Delete();
   
   hist_adc_point[j][i]->SetDirectory(dir_out[i]); 
   hist_adc_point_smooth[j][i]->SetDirectory(dir_out[i]);    
   hist_adc_point[j][i]->Write();
   hist_adc_point_smooth[j][i]->Write();   
   hist_adc_point_smooth[j][i]->Delete();      
  
  };  

  };   
  
   hist_adc_point.clear();      
//   qqq->Delete();

  // Starting time walk determination of time walk parameters
  
  // Booking histogams
  

  
  TH1F *tdc1_tw_1dimm[12][npoints][21][21];
// vector<vector<vector<vector<TH1F*> > > > tdc1_tw_1dimm;
  
  TH2F* tdc1_tw_2dimm[12][npoints];

  	 
    ostringstream tdc1d_num; 
    Bool_t adc_nolow;
    short jj,iii,jjj,kkk;
    Double_t lambda1, lambdaref;
    Double_t tdcfill;
    
//    TH1F *qqqtw;
    
//    int ntdc1dbins = int(tdcrightcut_nodiff[0]-tdcleftcut_nodiff[0]);
    Double_t step = (6.+2.)/20.;
     
 for (iii=0; iii<12; iii++ ) {
 
 
//vector<vector< vector<TH1F*> > >  tdc1_tw_1dimm_iii;
 
   for (j=0; j<npoints; j++ ) { 
   
//   vector< vector<TH1F*> > tdc1_tw_1dimm_j;
   
     for (i=0; i<21; i++ ) { 
     
//      vector<TH1F*> tdc1_tw_1dimm_i; 
     
      for (ii=0; ii<21; ii++) {
       
   tdc1d_num << "tdc" << iii+1 << "_point_" << j+1 << "_" << i << "_" << ii;
   
//   if ((iii != 4) && (iii != 5))  {
   if ((iii != 4))  {   
   if (iii%2 != 0) {
  tdc1_tw_1dimm[iii][j][i][ii] = new TH1F(tdc1d_num.str().c_str(),tdc1d_num.str().c_str(),1500,tdccenter_nodiff[iii]-(2.*j+1.)*delta-750.,tdccenter_nodiff[iii]-(2.*j+1.)*delta+750.);
   } else { tdc1_tw_1dimm[iii][j][i][ii] = new TH1F(tdc1d_num.str().c_str(),tdc1d_num.str().c_str(),1500,tdccenter_nodiff[iii]-3000.,tdccenter_nodiff[iii]+3000.);
   };
//  TH1F *qqqtw = new TH1F(tdc1d_num.str().c_str(),tdc1d_num.str().c_str(),1500,tdccenter_nodiff[iii]-1500.,tdccenter_nodiff[iii]+1500.); 
  
    }; 
     
     
     
//   if (iii == 5)  {
//   tdc1_tw_1dimm[iii][j][i][ii] = new TH1F(tdc1d_num.str().c_str(),tdc1d_num.str().c_str(),2500,-2500.,2500.);
//     };      
     
  
//    tdc1_tw_1dimm_i.push_back(qqqtw);  
    tdc1d_num.str("");   
   
   
   }; 
   
//   tdc1_tw_1dimm_j.push_back(tdc1_tw_1dimm_i);   
     
  
 };
//  tdc1_tw_1dimm_iii.push_back(tdc1_tw_1dimm_j);
 
   };
   
//   tdc1_tw_1dimm.push_back(tdc1_tw_1dimm_iii);
   
   };
 
   

   
   for (j=0; j<npoints; j++) {
   
   for (iii=0; iii<12; iii++) {
   
   if (( iii != 4) && ( iii != 5)) {
   tdc1d_num << "tdc_5_vs_tdc_" << iii+1 << "_point_" << j+1 ;
   tdc1_tw_2dimm[iii][j] = new TH2F(tdc1d_num.str().c_str(),tdc1d_num.str().c_str(),21,-2.-step,6.+step,21,-2.-step,6.+step);
   tdc1d_num.str("");

   tdc1d_num << "tdc_5_vs_tdc_mean" << iii+1 << "_point_" << j+1 ;
   tdc1d_num.str("");   
   };
   
   if (iii == 5) {
   tdc1d_num << "tdc_7_vs_tdc_" << iii+1 << "_point_" << j+1 ;
   tdc1_tw_2dimm[iii][j] = new TH2F(tdc1d_num.str().c_str(),tdc1d_num.str().c_str(),21,-2.-step,6.+step,21,-2.-step,6.+step);
   tdc1d_num.str("");

   tdc1d_num << "tdc_7_vs_tdc_mean" << iii+1 << "_point_" << j+1 ;
   tdc1d_num.str("");   
   };
     
   
   };
   
   

    

   

     };

 
 // loop over the events
adc_num.str("");
 
   for (i=0; i<event->GetEntries(); i++) { 
   
     if (setnum_inp == 0) {
     if (i%10 == 0) {
     fHProg1->Increment(1000./8./Double_t(event->GetEntries()));
     };
     };

    event->GetEntry(i);

    Double_t diff_top = (event->GetLeaf("tdc1")->GetValue()-event->GetLeaf("tdc2")->GetValue())/2.;
    Double_t diff_btm = (event->GetLeaf("tdc11")->GetValue()-event->GetLeaf("tdc12")->GetValue())/2.;    	
  
  // loop over thebar
    
    for (j=0; j<npoints; j++) {
    

  //position cut
  
  

    if ((diff_btm <= tdcleftcut[5] + j*delta) ||     
    (diff_btm > tdcleftcut[5] + (j+1)*delta) ||   
    (diff_top <= tdcleftcut[5] + j*delta + mean ) ||    
    (diff_top >= tdcleftcut[5] + (j+1)*delta + mean) ||
    (diff_top - diff_btm < mean - sigma) || 
    (diff_top - diff_btm > mean + sigma)) {
    

    
  hist_diff1vsdiff6_point[j]->Fill((event->GetLeaf("tdc11")->GetValue()-event->GetLeaf("tdc12")->GetValue())/2.,(event->GetLeaf("tdc1")->GetValue()-event->GetLeaf("tdc2")->GetValue())/2.,1);
     
						   
					       };

    if (diff_top - diff_btm > mean - sigma) { 
    if (diff_top - diff_btm < mean + sigma) { 

    if (diff_btm > tdcleftcut[5] + j*delta) {
    if (diff_btm <= tdcleftcut[5] + (j+1)*delta) {   
    
    if (diff_top > tdcleftcut[5] + j*delta + mean) {    
    if (diff_top < tdcleftcut[5] + (j+1)*delta + mean) {
    

    
  //hist_diff1vsdiff6_point[j]->Fill((event->GetLeaf("tdc11")->GetValue()-event->GetLeaf("tdc12")->GetValue())/2.,(event->GetLeaf("tdc1")->GetValue()-event->GetLeaf("tdc2")->GetValue())/2.,1); 
  
     
 
 // adc no low cut
     adc_nolow = 1;
     for (jj=0; jj<12; jj++) {
     

      
     adc_num << "adc" << jj+1;
     if (event->GetLeaf(adc_num.str().c_str())->GetValue() < adc_low_cut[jj][j]) {
     adc_nolow = 0;
     }; 
     adc_num.str("");   
     };    
     
     if (adc_nolow) {
     

     
     // loop over lambda ref
     
     for (iii=0; iii<21; iii++) {
     
     lambdaref = -2.+step*iii;
     
     // loop over lambda1
     
      for (jjj=0; jjj<21; jjj++) {    
     
      lambda1 = -2.+step*jjj;  
      

      for (kkk=0; kkk<12; kkk++) {  
      

      
      if ((kkk != 4) && (kkk != 5)) {
      adc_num << "tdc" << kkk+1;         

      tdcfill =  event->GetLeaf(adc_num.str().c_str())->GetValue();
      adc_num.str("");
      adc_num << "adc" << kkk+1; 
      
      tdcfill =  tdcfill -1000./sqrt(event->GetLeaf(adc_num.str().c_str())->GetValue())*lambda1;
    
      
      tdcfill =  tdcfill +1000./sqrt(event->GetLeaf("adc5")->GetValue())*lambdaref;
 	
   
      tdc1_tw_1dimm[kkk][j][jjj][iii]->Fill(tdcfill);

      
      adc_num.str(""); 
      };
      
       if (kkk == 5) {
         tdcfill =  event->GetLeaf("tdc6")->GetValue();
 
      tdcfill =  tdcfill -1000./sqrt(event->GetLeaf("adc6")->GetValue())*lambda1;
    
        tdcfill =  tdcfill - event->GetLeaf("tdc7")->GetValue();
      tdcfill =  tdcfill +1000./sqrt(event->GetLeaf("adc7")->GetValue())*lambdaref;
 	
		   
	   
      tdc1_tw_1dimm[kkk][j][jjj][iii]->Fill(tdcfill);
     
           
      };
      
      };
      
      

      

      
     
                                 }; // loop over lambda ref
     
                                 }; // loop over lambda 1     
     
     
     
     
                     }; //adc no low if
 
 
 
 
                                             }; // top diff if
                                                  };  // tp diff if
                                                            };  // btm diff if 
                                                                };  // btm diff if
								}; // top-btm cut
								}; // top-btm cut
                                 }; // loop over the bar for
			                   }; // loop over the events for
       
 



   Double_t sigma_tdc;
   Double_t tdc5avr;
   Double_t tdc5avr_err;

   
   TH1D* lambda1d[12];
   

   
   for (i=0; i<12; i++) {
   adc_num << "lambda_" << i+1;     
   lambda1d[i] = new TH1D(adc_num.str().c_str(),adc_num.str().c_str(),npoints,tdcleftcut[5],tdcrightcut[5]);     
   adc_num.str("");  
   };
   
   
   
   for (i=0; i<npoints; i++) {
  
      cout << "processing point " << i+1 << "\n";


  
     adc_num << "point_" << i+1;      
      outFile->cd(adc_num.str().c_str());    
       adc_num.str("");   
       
        hist_diff1vsdiff6_point[i]->Write();
      hist_diff1vsdiff6_point[i]->Delete();     
          
       // loop over lambda ref
     adc_num.str("");
     for (iii=0; iii<21; iii++) {
     
          lambdaref = -2.+step*iii;
     // loop over lambda1
     
      for (jjj=0; jjj<21; jjj++) { 
      
               lambda1 = -2.+step*jjj; 
     
     if (setnum_inp ==0) { 	
     if (i%10 == 0) { 	       
     fHProg1->Increment(1000./8./Double_t(npoints)/20./20.);	       
     };
     };
     
     
      for (j=0; j<12; j++) {

      if (j != 4) {   
      

     

      TF1 *gtl = new TF1("gtl","gaus",tdc1_tw_1dimm[j][i][jjj][iii]->	GetBinLowEdge(1),tdc1_tw_1dimm[j][i][jjj][iii]->GetBinLowEdge(1500)+tdc1_tw_1dimm[j][i][jjj][iii]->GetBinWidth(1500));
      
      tdc1_tw_1dimm[j][i][jjj][iii]->Fit("gtl","WQ0");
 
      
//      TF1 *gtl = tdc1_tw_1dimm[j][i][jjj][iii]->GetFunction("gaus");

      sigma_tdc = gtl->GetParameter(2);

      tdc1_tw_2dimm[j][i]->Fill(lambda1,lambdaref,sigma_tdc); 
      tdc1_tw_2dimm[j][i]->SetBinError(jjj+1,iii+1,gtl->GetParError(2));
      
      sigma_tdc = gtl->GetParameter(1);


 
 
     
      gtl->Delete();      
      

      tdc1_tw_1dimm[j][i][jjj][iii]->Delete();
      
      
     };

          
      
      };
      

      
      };
      };
      for (j=0; j<12; j++) { 
      if (j != 4) {	           
      tdc1_tw_2dimm[j][i]->Write();
      };
      };
      

      
//      FredMemFn p = &Fred::func3334;
      
//      TF1* fit11 = new TF1("fit1",p,100.,2000.,3);

   const Int_t npar = 5;
   Double_t f2params[npar] = {1.,2.,1.,2.5,6.};
   TF2* f222 = new TF2("f222",&g2tw,-2,6,-2,6, npar);
   tdc5avr = 0.;
   tdc5avr_err = 0.;
   for (kkk=0; kkk<12; kkk++) {
   f222->SetParameters(f2params);
   f222->SetParLimits(0,-2.,6.);
   f222->SetParLimits(1,1.,3.1);
   f222->SetParLimits(2,-2.,6.);  
   f222->SetParLimits(3,1.6,5.); 
   
   
   if (( kkk != 4)) { 
   tdc1_tw_2dimm[kkk][i]->Fit("f222","MLNQR");
   
   lambda1d[kkk]->SetBinContent(i+1,f222->GetParameter(0));
   lambda1d[kkk]->SetBinError(i+1,f222->GetParError(0));
   if (( kkk != 5)) {
   tdc5avr = tdc5avr + f222->GetParameter(2);
   tdc5avr_err = tdc5avr_err  + f222->GetParError(2);
   };
   
   tdc1_tw_2dimm[kkk][i]->Delete();
   
    }; 
  
   


      
      };
    
    lambda1d[4]->SetBinContent(i+1,tdc5avr/10.);  
    lambda1d[4]->SetBinError(i+1,tdc5avr_err/10.);      
      
      };
      
//      tdc1_tw_1dimm.clear(); 
      
     outFile->mkdir("fullbar_tw");
     outFile->cd("fullbar_tw"); 
     
      TMacro *resolcont_plot;
      resolcont_plot= macros.resol_cont_plot("_cont");
      resolcont_plot->Write();
      resolcont_plot->Delete(); 
     
     

  
       for (i=0; i<12; i++) {
     lambda1d[i]->Write();
//     lambda[i]->Write();  

       };
        
  
       
      TMacro *resol_plot;
      resol_plot = macros.resol_cont_plot("");

      resol_plot->Write();
      resol_plot->Delete(); 
      
      ss.str("");
      ss << _out_dir << "/";
      if (setnum_inp ==0) {
      macros.tw_params_write(lambda1d, ss.str().c_str());
      } else {
      macros.tw_params_write(lambda1d, "");
      };
      
      TMacro *tw_params;
      tw_params = macros.tw_params_plot();
      tw_params->Write();
      tw_params->Delete();
    
      
            
       
     
     

   
     
     

     
     // Fitting tw parameters


	double arglist[10];
	arglist[0] = 0;
        Int_t ierr=0;
	gMinuit->SetPrintLevel(-1);
        gMinuit->mnexcm("SET NOWarnings",arglist,1,ierr); 
     
     TF1 *twfit[12];
     
     TH1D *hist_tdcdiff_corr[6];
      for (i=0; i<12; i++) {
   if ( i % 2 == 0 ) {      
      diff = tdcrightcut[i/2] - tdcleftcut[i/2];
  tdc_left << "(tdc" << i+1 << "-" << "tdc" << i+2 << ")/2 corr";
  tdc_right << "tdc" << i+1 << "_" << "tdc" << i+2 << "_corr";      
     hist_tdcdiff_corr[i/2] = new TH1D(tdc_right.str().c_str(),tdc_left.str().c_str(),1000,tdcleftcut[i/2]-diff,tdcrightcut[i/2]+diff);
  tdc_left.str("");
  tdc_right.str(""); 
  };    
     };
     
     
     for (i=0; i<12; i++) {
     tdc_left << twfit << i;
     twfit[i] = new TF1(tdc_left.str().c_str(),"pol2",lambda1d[i]->	GetBinLowEdge(1),lambda1d[i]->GetBinLowEdge(npoints)+lambda1d[i]->GetBinWidth(npoints));
     twfit[i]->SetParLimits(2,0.,10.);
     tdc_left.str("");
     lambda1d[i]->Fit(twfit[i],"QL0");
     };
     
     // starting 3bars resolution calculaton
     
     Double_t tdc_corr[12],tdc_corr_cont[12];
     Double_t t_1_2_3,t_2_3_4,t_3_4_5,t_4_5_6,t_1_3_5,t_2_4_6,t_1_2_3_cont,t_2_3_4_cont,t_3_4_5_cont,t_4_5_6_cont,t_1_3_5_cont,t_2_4_6_cont;
     Double_t center_1_2_3,center_2_3_4,center_3_4_5,center_4_5_6,center_1_3_5,center_2_4_6;
     
 	
			
	
     
     TH1D *hist_1_2_3[npoints],*hist_2_3_4[npoints],*hist_3_4_5[npoints],*hist_4_5_6[npoints],*hist_1_3_5[npoints],*hist_2_4_6[npoints];
     
     TH1D *hist_1_2_3_cont[npoints],*hist_2_3_4_cont[npoints],*hist_3_4_5_cont[npoints],*hist_4_5_6_cont[npoints],*hist_1_3_5_cont[npoints],*hist_2_4_6_cont[npoints];         
     
      Double_t l_d;
      if (setnum_inp ==0) {
      l_d=bar_length[fCombo->GetSelected()-1];
      } else {
      l_d=bar_length[setnum_inp-1];
      };
     
      TH1D *resol_1_2_3 = new TH1D("resol_1_2_3","resol_1_2_3",npoints,0.,l_d);
resol_1_2_3->GetYaxis()->SetTitle("resolution (psec)");  
resol_1_2_3->GetXaxis()->SetTitle("position (cm)");
resol_1_2_3->GetXaxis()->SetTitleSize(0.06);
resol_1_2_3->GetXaxis()->SetTitleOffset(0.9);
resol_1_2_3->GetYaxis()->SetTitleSize(0.06);
resol_1_2_3->GetYaxis()->SetTitleOffset(1.3);        
      TH1D *resol_2_3_4 = new TH1D("resol_2_3_4","resol_2_3_4",npoints,0.,l_d);
resol_2_3_4->GetYaxis()->SetTitle("resolution (psec)");  
resol_2_3_4->GetXaxis()->SetTitle("position (cm)");
resol_2_3_4->GetXaxis()->SetTitleSize(0.06);
resol_2_3_4->GetXaxis()->SetTitleOffset(0.9);
resol_2_3_4->GetYaxis()->SetTitleSize(0.06);
resol_2_3_4->GetYaxis()->SetTitleOffset(1.3);       
      TH1D *resol_3_4_5 = new TH1D("resol_3_4_5","resol_3_4_5",npoints,0.,l_d); 
resol_3_4_5->GetYaxis()->SetTitle("resolution (psec)");  
resol_3_4_5->GetXaxis()->SetTitle("position (cm)");
resol_3_4_5->GetXaxis()->SetTitleSize(0.06);
resol_3_4_5->GetXaxis()->SetTitleOffset(0.9);
resol_3_4_5->GetYaxis()->SetTitleSize(0.06);
resol_3_4_5->GetYaxis()->SetTitleOffset(1.3);       
      TH1D *resol_4_5_6 = new TH1D("resol_4_5_6","resol_4_5_6",npoints,0.,l_d);
resol_4_5_6->GetYaxis()->SetTitle("resolution (psec)");  
resol_4_5_6->GetXaxis()->SetTitle("position (cm)");
resol_4_5_6->GetXaxis()->SetTitleSize(0.06);
resol_4_5_6->GetXaxis()->SetTitleOffset(0.9);
resol_4_5_6->GetYaxis()->SetTitleSize(0.06);
resol_4_5_6->GetYaxis()->SetTitleOffset(1.3);           
      TH1D *resol_1_3_5 = new TH1D("resol_1_3_5","resol_1_3_5",npoints,0.,l_d);
resol_1_3_5->GetYaxis()->SetTitle("resolution (psec)");  
resol_1_3_5->GetXaxis()->SetTitle("position (cm)");
resol_1_3_5->GetXaxis()->SetTitleSize(0.06);
resol_1_3_5->GetXaxis()->SetTitleOffset(0.9);
resol_1_3_5->GetYaxis()->SetTitleSize(0.06);
resol_1_3_5->GetYaxis()->SetTitleOffset(1.3);            
      TH1D *resol_2_4_6 = new TH1D("resol_2_4_6","resol_2_4_6",npoints,0.,l_d); 
resol_2_4_6->GetYaxis()->SetTitle("resolution (psec)");  
resol_2_4_6->GetXaxis()->SetTitle("position (cm)");
resol_2_4_6->GetXaxis()->SetTitleSize(0.06);
resol_2_4_6->GetXaxis()->SetTitleOffset(0.9);
resol_2_4_6->GetYaxis()->SetTitleSize(0.06);
resol_2_4_6->GetYaxis()->SetTitleOffset(1.3);        
      
      TH1D *resol_1_2_3_cont = new TH1D("resol_1_2_3_cont","resol_1_2_3_cont",npoints,0.,l_d);
 resol_1_2_3_cont->GetYaxis()->SetTitle("resolution (psec)");  
resol_1_2_3_cont->GetXaxis()->SetTitle("position (cm)");
resol_1_2_3_cont->GetXaxis()->SetTitleSize(0.06);
resol_1_2_3_cont->GetXaxis()->SetTitleOffset(0.9);
resol_1_2_3_cont->GetYaxis()->SetTitleSize(0.06);
resol_1_2_3_cont->GetYaxis()->SetTitleOffset(1.3);        
      TH1D *resol_2_3_4_cont = new TH1D("resol_2_3_4_cont","resol_2_3_4_cont",npoints,0.,l_d);
resol_2_3_4_cont->GetYaxis()->SetTitle("resolution (psec)");  
resol_2_3_4_cont->GetXaxis()->SetTitle("position (cm)");
resol_2_3_4_cont->GetXaxis()->SetTitleSize(0.06);
resol_2_3_4_cont->GetXaxis()->SetTitleOffset(0.9);
resol_2_3_4_cont->GetYaxis()->SetTitleSize(0.06);
resol_2_3_4_cont->GetYaxis()->SetTitleOffset(1.3);       
      TH1D *resol_3_4_5_cont = new TH1D("resol_3_4_5_cont","resol_3_4_5_cont",npoints,0.,l_d); 
resol_3_4_5_cont->GetYaxis()->SetTitle("resolution (psec)");  
resol_3_4_5_cont->GetXaxis()->SetTitle("position (cm)");
resol_3_4_5_cont->GetXaxis()->SetTitleSize(0.06);
resol_3_4_5_cont->GetXaxis()->SetTitleOffset(0.9);
resol_3_4_5_cont->GetYaxis()->SetTitleSize(0.06);
resol_3_4_5_cont->GetYaxis()->SetTitleOffset(1.3);         
      TH1D *resol_4_5_6_cont = new TH1D("resol_4_5_6_cont","resol_4_5_6_cont",npoints,0.,l_d);
resol_4_5_6_cont->GetYaxis()->SetTitle("resolution (psec)");  
resol_4_5_6_cont->GetXaxis()->SetTitle("position (cm)");
resol_4_5_6_cont->GetXaxis()->SetTitleSize(0.06);
resol_4_5_6_cont->GetXaxis()->SetTitleOffset(0.9);
resol_4_5_6_cont->GetYaxis()->SetTitleSize(0.06);
resol_4_5_6_cont->GetYaxis()->SetTitleOffset(1.3);        
      TH1D *resol_1_3_5_cont = new TH1D("resol_1_3_5_cont","resol_1_3_5_cont",npoints,0.,l_d);
resol_1_3_5_cont->GetYaxis()->SetTitle("resolution (psec)");  
resol_1_3_5_cont->GetXaxis()->SetTitle("position (cm)");
resol_1_3_5_cont->GetXaxis()->SetTitleSize(0.06);
resol_1_3_5_cont->GetXaxis()->SetTitleOffset(0.9);
resol_1_3_5_cont->GetYaxis()->SetTitleSize(0.06);
resol_1_3_5_cont->GetYaxis()->SetTitleOffset(1.3);      
      TH1D *resol_2_4_6_cont = new TH1D("resol_2_4_6_cont","resol_2_4_6_cont",npoints,0.,l_d);       
resol_2_4_6_cont->GetYaxis()->SetTitle("resolution (psec)");  
resol_2_4_6_cont->GetXaxis()->SetTitle("position (cm)");
resol_2_4_6_cont->GetXaxis()->SetTitleSize(0.06);
resol_2_4_6_cont->GetXaxis()->SetTitleOffset(0.9);
resol_2_4_6_cont->GetYaxis()->SetTitleSize(0.06);
resol_2_4_6_cont->GetYaxis()->SetTitleOffset(1.3);               
      
          
       


 center_1_2_3= (tdccenter_nodiff[0]+tdccenter_nodiff[1]+tdc6_range)/4.-(tdccenter_nodiff[2]+tdccenter_nodiff[3])/2.;
        center_2_3_4= (tdccenter_nodiff[2]+tdccenter_nodiff[3]+tdccenter_nodiff[6]+tdccenter_nodiff[7])/4.-tdc6_range/2.;
        center_3_4_5= (tdc6_range+tdccenter_nodiff[8]+tdccenter_nodiff[9])/4.-(tdccenter_nodiff[6]+tdccenter_nodiff[7])/2.;	
        center_4_5_6= (tdccenter_nodiff[6]+tdccenter_nodiff[7]+tdccenter_nodiff[10]+tdccenter_nodiff[11])/4.-(tdccenter_nodiff[8]+tdccenter_nodiff[9])/2.;
        center_1_3_5= (tdccenter_nodiff[0]+tdccenter_nodiff[1]+tdccenter_nodiff[8]+tdccenter_nodiff[9])/4.-(tdc6_range)/2.;
        center_2_4_6= (tdccenter_nodiff[2]+tdccenter_nodiff[3]+tdccenter_nodiff[10]+tdccenter_nodiff[11])/4.-(tdccenter_nodiff[6]+tdccenter_nodiff[7])/2.;	








        for (i=0; i<npoints; i++) {
	
/*
       center_1_2_3= (tdccenter_nodiff[0]+tdccenter_nodiff[1]-delta*(2.*i+1.)+tdccenter_nodiff[4]+tdc6_range)/4.-(tdccenter_nodiff[2]+tdccenter_nodiff[3]-delta*(2.*i+1.))/2.;
        center_2_3_4= (tdccenter_nodiff[2]+tdccenter_nodiff[3]-delta*(2.*i+1.)+tdccenter_nodiff[6]+tdccenter_nodiff[7]-delta*(2.*i+1.))/4.-tdc6_range/2.;
        center_3_4_5= (tdc6_range+tdccenter_nodiff[8]+tdccenter_nodiff[9]-delta*(2.*i+1.))/4.-(tdccenter_nodiff[6]+tdccenter_nodiff[7]-delta*(2.*i+1.))/2.;	
        center_4_5_6= (tdccenter_nodiff[6]+tdccenter_nodiff[7]-delta*(2.*i+1.)+tdccenter_nodiff[10]+tdccenter_nodiff[11]-delta*(2.*i+1.))/4.-(tdccenter_nodiff[8]+tdccenter_nodiff[9]-delta*(2.*i+1.))/2.;
        center_1_3_5= (tdccenter_nodiff[0]+tdccenter_nodiff[1]-delta*(2.*i+1.)+tdccenter_nodiff[8]+tdccenter_nodiff[9]-delta*(2.*i+1.))/4.-(tdccenter_nodiff[4]+tdc6_range)/2.;
        center_2_4_6= (tdccenter_nodiff[2]+tdccenter_nodiff[3]-delta*(2.*i+1.)+tdccenter_nodiff[10]+tdccenter_nodiff[11]-delta*(2.*i+1.))/4.-(tdccenter_nodiff[6]+tdccenter_nodiff[7]-delta*(2.*i+1.))/2.;		
*/	

   adc_num << "res_1_2_3_point" << i+1;     
   hist_1_2_3[i] = new TH1D(adc_num.str().c_str(),adc_num.str().c_str(),1500,center_1_2_3-750.,center_1_2_3+750.);        adc_num.str("");   	
	
   adc_num << "res_2_3_4_point" << i+1;     
   hist_2_3_4[i] = new TH1D(adc_num.str().c_str(),adc_num.str().c_str(),1500,center_2_3_4-750.,center_2_3_4+750.);        adc_num.str("");  
   
   adc_num << "res_3_4_5_point" << i+1;     
   hist_3_4_5[i] = new TH1D(adc_num.str().c_str(),adc_num.str().c_str(),1500,center_3_4_5-750.,center_3_4_5+750.);        adc_num.str("");   
      
   adc_num << "res_4_5_6_point" << i+1;     
   hist_4_5_6[i] = new TH1D(adc_num.str().c_str(),adc_num.str().c_str(),1500,center_4_5_6-750.,center_4_5_6+750.);        adc_num.str(""); 
   
   adc_num << "res_1_3_5_point" << i+1;     
   hist_1_3_5[i] = new TH1D(adc_num.str().c_str(),adc_num.str().c_str(),1500,center_1_3_5-750.,center_1_3_5+750.);        adc_num.str(""); 
      
   adc_num << "res_2_4_6_point" << i+1;     
   hist_2_4_6[i] = new TH1D(adc_num.str().c_str(),adc_num.str().c_str(),1500,center_2_4_6-750.,center_2_4_6+750.);        adc_num.str("");  
   
   
   
    adc_num << "res_1_2_3_point" << i+1 << "_cont";     
   hist_1_2_3_cont[i] = new TH1D(adc_num.str().c_str(),adc_num.str().c_str(),1500,center_1_2_3-750.,center_1_2_3+750.);        adc_num.str("");   	
	
   adc_num << "res_2_3_4_point" << i+1 << "_cont";     
   hist_2_3_4_cont[i] = new TH1D(adc_num.str().c_str(),adc_num.str().c_str(),1500,center_2_3_4-750.,center_2_3_4+750.);        adc_num.str("");  
   
   adc_num << "res_3_4_5_point" << i+1 << "_cont";     
   hist_3_4_5_cont[i] = new TH1D(adc_num.str().c_str(),adc_num.str().c_str(),1500,center_3_4_5-750.,center_3_4_5+750.);        adc_num.str("");   
      
   adc_num << "res_4_5_6_point" << i+1 << "_cont";     
   hist_4_5_6_cont[i] = new TH1D(adc_num.str().c_str(),adc_num.str().c_str(),1500,center_4_5_6-750.,center_4_5_6+750.);        adc_num.str(""); 
   
   adc_num << "res_1_3_5_point" << i+1 << "_cont";     
   hist_1_3_5_cont[i] = new TH1D(adc_num.str().c_str(),adc_num.str().c_str(),1500,center_1_3_5-750.,center_1_3_5+750.);        adc_num.str(""); 
      
   adc_num << "res_2_4_6_point" << i+1 << "_cont";     
   hist_2_4_6_cont[i] = new TH1D(adc_num.str().c_str(),adc_num.str().c_str(),1500,center_2_4_6-750.,center_2_4_6+750.);        adc_num.str("");    
   
   
     
     
      
   };
   

 
   for (i=0; i<event->GetEntries(); i++) { 
   
     if (setnum_inp ==0) {
     if (i%10 == 0) {
     fHProg1->Increment(1000./8./Double_t(event->GetEntries()));
     };
     };

    event->GetEntry(i);

    Double_t diff_top = (event->GetLeaf("tdc1")->GetValue()-event->GetLeaf("tdc2")->GetValue())/2.;
    Double_t diff_btm = (event->GetLeaf("tdc11")->GetValue()-event->GetLeaf("tdc12")->GetValue())/2.;    	
  
  // loop over thebar
  
  
     for (iii=0; iii<12; iii++)  {
     
     adc_num << "adc" << iii+1;

 
 
    tdc1d_num << "tdc" << iii+1;     
     
     
    tdc_corr_cont[iii] = event->GetLeaf(tdc1d_num.str().c_str())->GetValue();
    tdc_corr_cont[iii] = tdc_corr_cont[iii] - 1000.*twfit[iii]->Eval(diff_btm)/sqrt(event->GetLeaf(adc_num.str().c_str())->GetValue()); 
    tdc_corr_cont[iii] = tdc_corr_cont[iii] + 1000.*twfit[4]->Eval(diff_btm)/sqrt(event->GetLeaf("adc5")->GetValue()); 
    
    tdc1d_num.str("");
 
 
   
    adc_num.str("");
      
    
    
    }; 
    
    
    event_corr.tdc1_corr = tdc_corr_cont[0];
    event_corr.tdc2_corr = tdc_corr_cont[1];  
    event_corr.tdc3_corr = tdc_corr_cont[2];
    event_corr.tdc4_corr = tdc_corr_cont[3];
    event_corr.tdc5_corr = tdc_corr_cont[4];
    event_corr.tdc6_corr = tdc_corr_cont[5];  
    event_corr.tdc7_corr = tdc_corr_cont[6];
    event_corr.tdc8_corr = tdc_corr_cont[7];
    event_corr.tdc9_corr = tdc_corr_cont[8];
    event_corr.tdc10_corr = tdc_corr_cont[9];  
    event_corr.tdc11_corr = tdc_corr_cont[10];
    event_corr.tdc12_corr = tdc_corr_cont[11];                
    newBranch->Fill();       
    
     for (iii=0; iii<6; iii++)  {

hist_tdcdiff_corr[iii]->Fill((tdc_corr_cont[2*iii]-tdc_corr_cont[2*iii+1])/2.,1.);  
  

  };     
   
          
    
    
    for (j=0; j<npoints; j++) {
    

  //position cut

    if (diff_top - diff_btm > mean - sigma) { 
    if (diff_top - diff_btm < mean + sigma) { 

    if (diff_btm > tdcleftcut[5] + j*delta) {
    if (diff_btm <= tdcleftcut[5] + (j+1)*delta) {   
    
    if (diff_top > tdcleftcut[5] + j*delta + mean) {    
    if (diff_top < tdcleftcut[5] + (j+1)*delta + mean) {  
    
    
      adc_nolow = 1;
     for (jj=0; jj<12; jj++) {
     

      
     adc_num << "adc" << jj+1;
     if (event->GetLeaf(adc_num.str().c_str())->GetValue() < adc_low_cut[jj][j]) {
     adc_nolow = 0;
     }; 
     adc_num.str("");   
     };    
     
     if (adc_nolow) {        
      
          
    
    for (iii=0; iii<12; iii++)  {
    
    
   
    adc_num << "adc" << iii+1;

 
 
    tdc1d_num << "tdc" << iii+1; 
    
    
    tdc_corr[iii] = event->GetLeaf(tdc1d_num.str().c_str())->GetValue();
    tdc_corr[iii] = tdc_corr[iii] - 1000.*lambda1d[iii]->GetBinContent(j+1)/sqrt(event->GetLeaf(adc_num.str().c_str())->GetValue()); 
    tdc_corr[iii] = tdc_corr[iii] + 1000.*lambda1d[4]->GetBinContent(j+1)/sqrt(event->GetLeaf("adc5")->GetValue()); 
    
//    tdc_corr[iii] = event->GetLeaf(tdc1d_num.str().c_str())->GetValue();


/*    tdc_corr_cont[iii] = event->GetLeaf(tdc1d_num.str().c_str())->GetValue();
    tdc_corr_cont[iii] = tdc_corr_cont[iii] - 1000.*twfit[iii]->Eval(diff_btm)/sqrt(event->GetLeaf(adc_num.str().c_str())->GetValue()); 
    tdc_corr_cont[iii] = tdc_corr_cont[iii] + 1000.*twfit[4]->Eval(diff_btm)/sqrt(event->GetLeaf("adc5")->GetValue()); 
 
 
 */   
    tdc1d_num.str("");
 
 
   
    adc_num.str("");
      
    
    
    }; 
    

   
/*     for (iii=0; iii<6; iii++)  {

hist_tdcdiff_corr[iii]->Fill(tdc_corr_cont[2*iii]-tdc_corr_cont[2*iii+1],1.);  
  

  };        */
    

    
    t_1_2_3 = (tdc_corr[0] + tdc_corr[1] + tdc_corr[4] + tdc_corr[5])/4. - (tdc_corr[2]+tdc_corr[3])/2.;    
    
    t_2_3_4 = (tdc_corr[2] + tdc_corr[3] + tdc_corr[6] + tdc_corr[7])/4. - (tdc_corr[4]+tdc_corr[5])/2.;
    
    t_3_4_5 = (tdc_corr[4] + tdc_corr[5] + tdc_corr[8] + tdc_corr[9])/4. - (tdc_corr[6]+tdc_corr[7])/2.;
    
    t_4_5_6 = (tdc_corr[6] + tdc_corr[7] + tdc_corr[10] + tdc_corr[11])/4. - (tdc_corr[8]+tdc_corr[9])/2.;  
    
    t_1_3_5 = (tdc_corr[0] + tdc_corr[1] + tdc_corr[8] + tdc_corr[9])/4. - (tdc_corr[4]+tdc_corr[5])/2.;  
    
    t_2_4_6 = (tdc_corr[2] + tdc_corr[3] + tdc_corr[10] + tdc_corr[11])/4. - (tdc_corr[6]+tdc_corr[7])/2.;  
    
    
    
    t_1_2_3_cont = (tdc_corr_cont[0] + tdc_corr_cont[1] + tdc_corr_cont[4] + tdc_corr_cont[5])/4. - (tdc_corr_cont[2]+tdc_corr_cont[3])/2.;    
    
    t_2_3_4_cont = (tdc_corr_cont[2] + tdc_corr_cont[3] + tdc_corr_cont[6] + tdc_corr_cont[7])/4. - (tdc_corr_cont[4]+tdc_corr_cont[5])/2.;
    
    t_3_4_5_cont = (tdc_corr_cont[4] + tdc_corr_cont[5] + tdc_corr_cont[8] + tdc_corr_cont[9])/4. - (tdc_corr_cont[6]+tdc_corr_cont[7])/2.;
    
    t_4_5_6_cont = (tdc_corr_cont[6] + tdc_corr_cont[7] + tdc_corr_cont[10] + tdc_corr_cont[11])/4. - (tdc_corr_cont[8]+tdc_corr_cont[9])/2.;  
    
    t_1_3_5_cont = (tdc_corr_cont[0] + tdc_corr_cont[1] + tdc_corr_cont[8] + tdc_corr_cont[9])/4. - (tdc_corr_cont[4]+tdc_corr_cont[5])/2.;  
    
    t_2_4_6_cont = (tdc_corr_cont[2] + tdc_corr_cont[3] + tdc_corr_cont[10] + tdc_corr_cont[11])/4. - (tdc_corr_cont[6]+tdc_corr_cont[7])/2.;    
             
    
         
    
    
    hist_1_2_3[j]->Fill(t_1_2_3);  
    hist_2_3_4[j]->Fill(t_2_3_4);
    hist_3_4_5[j]->Fill(t_3_4_5); 
    hist_4_5_6[j]->Fill(t_4_5_6);  
    hist_1_3_5[j]->Fill(t_1_3_5);
    hist_2_4_6[j]->Fill(t_2_4_6);  
    
    
    hist_1_2_3_cont[j]->Fill(t_1_2_3_cont);  
    hist_2_3_4_cont[j]->Fill(t_2_3_4_cont);
    hist_3_4_5_cont[j]->Fill(t_3_4_5_cont); 
    hist_4_5_6_cont[j]->Fill(t_4_5_6_cont);  
    hist_1_3_5_cont[j]->Fill(t_1_3_5_cont);
    hist_2_4_6_cont[j]->Fill(t_2_4_6_cont);      
    
          

       
                  };
    
                                                                    };
                                                                };
   
    
                                                   };
                                              };
    
   
    
    
                                 };
    
    
                                             };
					     
					     };
					     };
     
    
    
    
    
    
    
     outFile->cd();
    
    if (setnum_inp == 0) {
         if (estat->GetState() == kButtonDown) {
     t21->Write("", TObject::kOverwrite);
     };
     } else {
     if (outtree_inp) {
     t21->Write("", TObject::kOverwrite);
     };
     };
    

    
    for (i=0; i<npoints; i++) {
   

  
     adc_num << "point_" << i+1;      
      outFile->cd(adc_num.str().c_str());    
       adc_num.str("");  
       
       
      // hist_2_3_4[i]->Fit("gaus","WWQ");
   
      // TF1 *gtl = hist_2_3_4[i]->GetFunction("gaus");

      // sigma_tdc = gtl->GetParameter(2);

      // resol_2_3_4->SetBinContent(i+1,25.*sqrt(2./3.)*(gtl->GetParameter(2))); 
      // resol_2_3_4->SetBinError(i+1,25.*sqrt(2./3.)*(gtl->GetParError(2)));
     
      // gtl->Delete();  

      TF1 *gtl=NULL;

      int fr=hist_2_3_4[i]->Fit("gaus","Q");
      if (fr==0){//! i.e. CSQ fit is successful
        gtl = hist_2_3_4[i]->GetFunction("gaus");

        double rel_err=gtl->GetParameter(2)/gtl->GetParError(2);
        if (rel_err<0.5){

          sigma_tdc = gtl->GetParameter(2);

          resol_2_3_4->SetBinContent(i+1,25.*sqrt(2./3.)*(gtl->GetParameter(2))); 
          resol_2_3_4->SetBinError(i+1,25.*sqrt(2./3.)*(gtl->GetParError(2)));
        }else{
          hist_2_3_4[i]->Fit("gaus","WWQ");

          gtl = hist_2_3_4[i]->GetFunction("gaus");

          sigma_tdc = gtl->GetParameter(2);

          resol_2_3_4->SetBinContent(i+1,25.*sqrt(2./3.)*(gtl->GetParameter(2)));
          resol_2_3_4->SetBinError(i+1,0);//To distinguish from error obtain from CSQ, set error from MLE=0, always.
        }
      }else{//! if CSQ fit fails, perform CSQ-WW fit
        hist_2_3_4[i]->Fit("gaus","WWQ");

        gtl = hist_2_3_4[i]->GetFunction("gaus");

        sigma_tdc = gtl->GetParameter(2);

        resol_2_3_4->SetBinContent(i+1,25.*sqrt(2./3.)*(gtl->GetParameter(2))); 
        resol_2_3_4->SetBinError(i+1,0);//To distinguish from error obtain from CSQ, set error from MLE=0, always.
 
      }
      
      
       
      /*hist_1_2_3[i]->Fit("gaus","WWQ");
   
      gtl = hist_1_2_3[i]->GetFunction("gaus");

      sigma_tdc = gtl->GetParameter(2);

      resol_1_2_3->SetBinContent(i+1,25.*sqrt(2./3.)*(gtl->GetParameter(2))); 
      resol_1_2_3->SetBinError(i+1,25.*sqrt(2./3.)*(gtl->GetParError(2)));
     
      gtl->Delete(); */   
      fr=hist_1_2_3[i]->Fit("gaus","Q");
      if (fr==0){//! i.e. CSQ fit is successful
        gtl = hist_1_2_3[i]->GetFunction("gaus");

        double rel_err=gtl->GetParameter(2)/gtl->GetParError(2);
        if (rel_err<0.5){

          sigma_tdc = gtl->GetParameter(2);

          resol_1_2_3->SetBinContent(i+1,25.*sqrt(2./3.)*(gtl->GetParameter(2)));
          resol_1_2_3->SetBinError(i+1,25.*sqrt(2./3.)*(gtl->GetParError(2)));
        }else{
          hist_1_2_3[i]->Fit("gaus","WWQ");

          gtl = hist_1_2_3[i]->GetFunction("gaus");

          sigma_tdc = gtl->GetParameter(2);

          resol_1_2_3->SetBinContent(i+1,25.*sqrt(2./3.)*(gtl->GetParameter(2)));
          resol_1_2_3->SetBinError(i+1,0);//To distinguish from error obtain from CSQ, set error from MLE=0, always.
        }
      }else{//! if CSQ fit fails, perform CSQ-WW fit
        hist_1_2_3[i]->Fit("gaus","WWQ");

        gtl = hist_1_2_3[i]->GetFunction("gaus");

        sigma_tdc = gtl->GetParameter(2);

        resol_1_2_3->SetBinContent(i+1,25.*sqrt(2./3.)*(gtl->GetParameter(2)));
        resol_1_2_3->SetBinError(i+1,0);//To distinguish from error obtain from CSQ, set error from MLE=0, always.

      }
      
      
      // hist_3_4_5[i]->Fit("gaus","WWQ");
   
      // gtl = hist_3_4_5[i]->GetFunction("gaus");

      // sigma_tdc = gtl->GetParameter(2);

      // resol_3_4_5->SetBinContent(i+1,25.*sqrt(2./3.)*(gtl->GetParameter(2))); 
      // resol_3_4_5->SetBinError(i+1,25.*sqrt(2./3.)*(gtl->GetParError(2)));
     
      // gtl->Delete(); 
      fr=hist_3_4_5[i]->Fit("gaus","Q");
      if (fr==0){//! i.e. CSQ fit is successful
        gtl = hist_3_4_5[i]->GetFunction("gaus");

        double rel_err=gtl->GetParameter(2)/gtl->GetParError(2);
        if (rel_err<0.5){

          sigma_tdc = gtl->GetParameter(2);

          resol_3_4_5->SetBinContent(i+1,25.*sqrt(2./3.)*(gtl->GetParameter(2)));
          resol_3_4_5->SetBinError(i+1,25.*sqrt(2./3.)*(gtl->GetParError(2)));
        }else{
          hist_3_4_5[i]->Fit("gaus","WWQ");

          gtl = hist_3_4_5[i]->GetFunction("gaus");

          sigma_tdc = gtl->GetParameter(2);

          resol_3_4_5->SetBinContent(i+1,25.*sqrt(2./3.)*(gtl->GetParameter(2)));
          resol_3_4_5->SetBinError(i+1,0);//To distinguish from error obtain from CSQ, set error from MLE=0, always.
        }
      }else{//! if CSQ fit fails, perform CSQ-WW fit
        hist_3_4_5[i]->Fit("gaus","WWQ");

        gtl = hist_3_4_5[i]->GetFunction("gaus");

        sigma_tdc = gtl->GetParameter(2);

        resol_3_4_5->SetBinContent(i+1,25.*sqrt(2./3.)*(gtl->GetParameter(2)));
        resol_3_4_5->SetBinError(i+1,0);//To distinguish from error obtain from CSQ, set error from MLE=0, always.

      }
      
      
      /*hist_4_5_6[i]->Fit("gaus","WWQ");
   
      gtl = hist_4_5_6[i]->GetFunction("gaus");

      sigma_tdc = gtl->GetParameter(2);

      resol_4_5_6->SetBinContent(i+1,25.*sqrt(2./3.)*(gtl->GetParameter(2))); 
      resol_4_5_6->SetBinError(i+1,25.*sqrt(2./3.)*(gtl->GetParError(2)));
     
      gtl->Delete();*/
      fr=hist_4_5_6[i]->Fit("gaus","Q");
      if (fr==0){//! i.e. CSQ fit is successful
        gtl = hist_4_5_6[i]->GetFunction("gaus");

        double rel_err=gtl->GetParameter(2)/gtl->GetParError(2);
        if (rel_err<0.5){

          sigma_tdc = gtl->GetParameter(2);

          resol_4_5_6->SetBinContent(i+1,25.*sqrt(2./3.)*(gtl->GetParameter(2)));
          resol_4_5_6->SetBinError(i+1,25.*sqrt(2./3.)*(gtl->GetParError(2)));
        }else{
          hist_4_5_6[i]->Fit("gaus","WWQ");

          gtl = hist_4_5_6[i]->GetFunction("gaus");

          sigma_tdc = gtl->GetParameter(2);

          resol_4_5_6->SetBinContent(i+1,25.*sqrt(2./3.)*(gtl->GetParameter(2)));
          resol_4_5_6->SetBinError(i+1,0);//To distinguish from error obtain from CSQ, set error from MLE=0, always.
        }
      }else{//! if CSQ fit fails, perform CSQ-WW fit
        hist_4_5_6[i]->Fit("gaus","WWQ");

        gtl = hist_4_5_6[i]->GetFunction("gaus");

        sigma_tdc = gtl->GetParameter(2);

        resol_4_5_6->SetBinContent(i+1,25.*sqrt(2./3.)*(gtl->GetParameter(2)));
        resol_4_5_6->SetBinError(i+1,0);//To distinguish from error obtain from CSQ, set error from MLE=0, always.

      }
      
                  
      
      /*hist_1_3_5[i]->Fit("gaus","WWQ");
   
      gtl = hist_1_3_5[i]->GetFunction("gaus");

      sigma_tdc = gtl->GetParameter(2);

      resol_1_3_5->SetBinContent(i+1,25.*sqrt(2./3.)*(gtl->GetParameter(2))); 
      resol_1_3_5->SetBinError(i+1,25.*sqrt(2./3.)*(gtl->GetParError(2)));
     
      gtl->Delete();*/
      fr=hist_1_3_5[i]->Fit("gaus","Q");
      if (fr==0){//! i.e. CSQ fit is successful
        gtl = hist_1_3_5[i]->GetFunction("gaus");

        double rel_err=gtl->GetParameter(2)/gtl->GetParError(2);
        if (rel_err<0.5){

          sigma_tdc = gtl->GetParameter(2);

          resol_1_3_5->SetBinContent(i+1,25.*sqrt(2./3.)*(gtl->GetParameter(2)));
          resol_1_3_5->SetBinError(i+1,25.*sqrt(2./3.)*(gtl->GetParError(2)));
        }else{
          hist_1_3_5[i]->Fit("gaus","WWQ");

          gtl = hist_1_3_5[i]->GetFunction("gaus");

          sigma_tdc = gtl->GetParameter(2);

          resol_1_3_5->SetBinContent(i+1,25.*sqrt(2./3.)*(gtl->GetParameter(2)));
          resol_1_3_5->SetBinError(i+1,0);//To distinguish from error obtain from CSQ, set error from MLE=0, always.
        }
      }else{//! if CSQ fit fails, perform CSQ-WW fit
        hist_1_3_5[i]->Fit("gaus","WWQ");

        gtl = hist_1_3_5[i]->GetFunction("gaus");

        sigma_tdc = gtl->GetParameter(2);

        resol_1_3_5->SetBinContent(i+1,25.*sqrt(2./3.)*(gtl->GetParameter(2)));
        resol_1_3_5->SetBinError(i+1,0);//To distinguish from error obtain from CSQ, set error from MLE=0, always.

      }
      
      
      
      /* hist_2_4_6[i]->Fit("gaus","WWQ");
   
      gtl = hist_2_4_6[i]->GetFunction("gaus");

      sigma_tdc = gtl->GetParameter(2);

      resol_2_4_6->SetBinContent(i+1,25.*sqrt(2./3.)*(gtl->GetParameter(2))); 
      resol_2_4_6->SetBinError(i+1,25.*sqrt(2./3.)*(gtl->GetParError(2)));
     
      gtl->Delete();*/  
      fr=hist_2_4_6[i]->Fit("gaus","Q");
      if (fr==0){//! i.e. CSQ fit is successful
        gtl = hist_2_4_6[i]->GetFunction("gaus");

        double rel_err=gtl->GetParameter(2)/gtl->GetParError(2);
        if (rel_err<0.5){

          sigma_tdc = gtl->GetParameter(2);

          resol_2_4_6->SetBinContent(i+1,25.*sqrt(2./3.)*(gtl->GetParameter(2)));
          resol_2_4_6->SetBinError(i+1,25.*sqrt(2./3.)*(gtl->GetParError(2)));
        }else{
          hist_2_4_6[i]->Fit("gaus","WWQ");

          gtl = hist_2_4_6[i]->GetFunction("gaus");

          sigma_tdc = gtl->GetParameter(2);

          resol_2_4_6->SetBinContent(i+1,25.*sqrt(2./3.)*(gtl->GetParameter(2)));
          resol_2_4_6->SetBinError(i+1,0);//To distinguish from error obtain from CSQ, set error from MLE=0, always.
        }
      }else{//! if CSQ fit fails, perform CSQ-WW fit
        hist_2_4_6[i]->Fit("gaus","WWQ");

        gtl = hist_2_4_6[i]->GetFunction("gaus");

        sigma_tdc = gtl->GetParameter(2);

        resol_2_4_6->SetBinContent(i+1,25.*sqrt(2./3.)*(gtl->GetParameter(2)));
        resol_2_4_6->SetBinError(i+1,0);//To distinguish from error obtain from CSQ, set error from MLE=0, always.

      }
      
      
           
 
 
 
 
 
 
 
 
 
      /* hist_2_3_4_cont[i]->Fit("gaus","WWQ");
   
      gtl = hist_2_3_4_cont[i]->GetFunction("gaus");

      sigma_tdc = gtl->GetParameter(2);

      resol_2_3_4_cont->SetBinContent(i+1,25.*sqrt(2./3.)*(gtl->GetParameter(2))); 
      resol_2_3_4_cont->SetBinError(i+1,25.*sqrt(2./3.)*(gtl->GetParError(2)));
     
      gtl->Delete(); */ 
      fr=hist_2_3_4_cont[i]->Fit("gaus","Q");
      if (fr==0){//! i.e. CSQ fit is successful
        gtl = hist_2_3_4_cont[i]->GetFunction("gaus");

        double rel_err=gtl->GetParameter(2)/gtl->GetParError(2);
        if (rel_err<0.5){

          sigma_tdc = gtl->GetParameter(2);

          resol_2_3_4_cont->SetBinContent(i+1,25.*sqrt(2./3.)*(gtl->GetParameter(2)));
          resol_2_3_4_cont->SetBinError(i+1,25.*sqrt(2./3.)*(gtl->GetParError(2)));
        }else{
          hist_2_3_4_cont[i]->Fit("gaus","WWQ");

          gtl = hist_2_3_4_cont[i]->GetFunction("gaus");

          sigma_tdc = gtl->GetParameter(2);

          resol_2_3_4_cont->SetBinContent(i+1,25.*sqrt(2./3.)*(gtl->GetParameter(2)));
          resol_2_3_4_cont->SetBinError(i+1,0);//To distinguish from error obtain from CSQ, set error from MLE=0, always.
        }
      }else{//! if CSQ fit fails, perform CSQ-WW fit
        hist_2_3_4_cont[i]->Fit("gaus","WWQ");

        gtl = hist_2_3_4_cont[i]->GetFunction("gaus");

        sigma_tdc = gtl->GetParameter(2);

        resol_2_3_4_cont->SetBinContent(i+1,25.*sqrt(2./3.)*(gtl->GetParameter(2)));
        resol_2_3_4_cont->SetBinError(i+1,0);//To distinguish from error obtain from CSQ, set error from MLE=0, always.

      }
      
      
       
      /*hist_1_2_3_cont[i]->Fit("gaus","WWQ");
   
      gtl = hist_1_2_3_cont[i]->GetFunction("gaus");

      sigma_tdc = gtl->GetParameter(2);

      resol_1_2_3_cont->SetBinContent(i+1,25.*sqrt(2./3.)*(gtl->GetParameter(2))); 
      resol_1_2_3_cont->SetBinError(i+1,25.*sqrt(2./3.)*(gtl->GetParError(2)));
     
      gtl->Delete(); */   
      fr=hist_1_2_3_cont[i]->Fit("gaus","Q");
      if (fr==0){//! i.e. CSQ fit is successful
        gtl = hist_1_2_3_cont[i]->GetFunction("gaus");

        double rel_err=gtl->GetParameter(2)/gtl->GetParError(2);
        if (rel_err<0.5){

          sigma_tdc = gtl->GetParameter(2);

          resol_1_2_3_cont->SetBinContent(i+1,25.*sqrt(2./3.)*(gtl->GetParameter(2)));
          resol_1_2_3_cont->SetBinError(i+1,25.*sqrt(2./3.)*(gtl->GetParError(2)));
        }else{
          hist_1_2_3_cont[i]->Fit("gaus","WWQ");

          gtl = hist_1_2_3_cont[i]->GetFunction("gaus");

          sigma_tdc = gtl->GetParameter(2);

          resol_1_2_3_cont->SetBinContent(i+1,25.*sqrt(2./3.)*(gtl->GetParameter(2)));
          resol_1_2_3_cont->SetBinError(i+1,0);//To distinguish from error obtain from CSQ, set error from MLE=0, always.
        }
      }else{//! if CSQ fit fails, perform CSQ-WW fit
        hist_1_2_3_cont[i]->Fit("gaus","WWQ");

        gtl = hist_1_2_3_cont[i]->GetFunction("gaus");

        sigma_tdc = gtl->GetParameter(2);

        resol_1_2_3_cont->SetBinContent(i+1,25.*sqrt(2./3.)*(gtl->GetParameter(2)));
        resol_1_2_3_cont->SetBinError(i+1,0);//To distinguish from error obtain from CSQ, set error from MLE=0, always.

      }
      
      
      
      /*hist_3_4_5_cont[i]->Fit("gaus","WWQ");
   
      gtl = hist_3_4_5_cont[i]->GetFunction("gaus");

      sigma_tdc = gtl->GetParameter(2);

      resol_3_4_5_cont->SetBinContent(i+1,25.*sqrt(2./3.)*(gtl->GetParameter(2))); 
      resol_3_4_5_cont->SetBinError(i+1,25.*sqrt(2./3.)*(gtl->GetParError(2)));
     
      gtl->Delete(); */
      fr=hist_3_4_5_cont[i]->Fit("gaus","Q");
      if (fr==0){//! i.e. CSQ fit is successful
        gtl = hist_3_4_5_cont[i]->GetFunction("gaus");

        double rel_err=gtl->GetParameter(2)/gtl->GetParError(2);
        if (rel_err<0.5){

          sigma_tdc = gtl->GetParameter(2);

          resol_3_4_5_cont->SetBinContent(i+1,25.*sqrt(2./3.)*(gtl->GetParameter(2)));
          resol_3_4_5_cont->SetBinError(i+1,25.*sqrt(2./3.)*(gtl->GetParError(2)));
        }else{
          hist_3_4_5_cont[i]->Fit("gaus","WWQ");

          gtl = hist_3_4_5_cont[i]->GetFunction("gaus");

          sigma_tdc = gtl->GetParameter(2);

          resol_3_4_5_cont->SetBinContent(i+1,25.*sqrt(2./3.)*(gtl->GetParameter(2)));
          resol_3_4_5_cont->SetBinError(i+1,0);//To distinguish from error obtain from CSQ, set error from MLE=0, always.
        }
      }else{//! if CSQ fit fails, perform CSQ-WW fit
        hist_3_4_5_cont[i]->Fit("gaus","WWQ");

        gtl = hist_3_4_5_cont[i]->GetFunction("gaus");

        sigma_tdc = gtl->GetParameter(2);

        resol_3_4_5_cont->SetBinContent(i+1,25.*sqrt(2./3.)*(gtl->GetParameter(2)));
        resol_3_4_5_cont->SetBinError(i+1,0);//To distinguish from error obtain from CSQ, set error from MLE=0, always.

      }
      
      
      /*hist_4_5_6_cont[i]->Fit("gaus","WWQ");
   
      gtl = hist_4_5_6_cont[i]->GetFunction("gaus");

      sigma_tdc = gtl->GetParameter(2);

      resol_4_5_6_cont->SetBinContent(i+1,25.*sqrt(2./3.)*(gtl->GetParameter(2))); 
      resol_4_5_6_cont->SetBinError(i+1,25.*sqrt(2./3.)*(gtl->GetParError(2)));
     
      gtl->Delete(); */    
      fr=hist_4_5_6_cont[i]->Fit("gaus","Q");
      if (fr==0){//! i.e. CSQ fit is successful
        gtl = hist_4_5_6_cont[i]->GetFunction("gaus");

        double rel_err=gtl->GetParameter(2)/gtl->GetParError(2);
        if (rel_err<0.5){

          sigma_tdc = gtl->GetParameter(2);

          resol_4_5_6_cont->SetBinContent(i+1,25.*sqrt(2./3.)*(gtl->GetParameter(2)));
          resol_4_5_6_cont->SetBinError(i+1,25.*sqrt(2./3.)*(gtl->GetParError(2)));
        }else{
          hist_4_5_6_cont[i]->Fit("gaus","WWQ");

          gtl = hist_4_5_6_cont[i]->GetFunction("gaus");

          sigma_tdc = gtl->GetParameter(2);

          resol_4_5_6_cont->SetBinContent(i+1,25.*sqrt(2./3.)*(gtl->GetParameter(2)));
          resol_4_5_6_cont->SetBinError(i+1,0);//To distinguish from error obtain from CSQ, set error from MLE=0, always.
        }
      }else{//! if CSQ fit fails, perform CSQ-WW fit
        hist_4_5_6_cont[i]->Fit("gaus","WWQ");

        gtl = hist_4_5_6_cont[i]->GetFunction("gaus");

        sigma_tdc = gtl->GetParameter(2);

        resol_4_5_6_cont->SetBinContent(i+1,25.*sqrt(2./3.)*(gtl->GetParameter(2)));
        resol_4_5_6_cont->SetBinError(i+1,0);//To distinguish from error obtain from CSQ, set error from MLE=0, always.

      }
      
                  
      
      /*hist_1_3_5_cont[i]->Fit("gaus","WWQ");
   
      gtl = hist_1_3_5_cont[i]->GetFunction("gaus");

      sigma_tdc = gtl->GetParameter(2);

      resol_1_3_5_cont->SetBinContent(i+1,25.*sqrt(2./3.)*(gtl->GetParameter(2))); 
      resol_1_3_5_cont->SetBinError(i+1,25.*sqrt(2./3.)*(gtl->GetParError(2)));
     
      gtl->Delete();  */
      fr=hist_1_3_5_cont[i]->Fit("gaus","Q");
      if (fr==0){//! i.e. CSQ fit is successful
        gtl = hist_1_3_5_cont[i]->GetFunction("gaus");

        double rel_err=gtl->GetParameter(2)/gtl->GetParError(2);
        if (rel_err<0.5){

          sigma_tdc = gtl->GetParameter(2);

          resol_1_3_5_cont->SetBinContent(i+1,25.*sqrt(2./3.)*(gtl->GetParameter(2)));
          resol_1_3_5_cont->SetBinError(i+1,25.*sqrt(2./3.)*(gtl->GetParError(2)));
        }else{
          hist_1_3_5_cont[i]->Fit("gaus","WWQ");

          gtl = hist_1_3_5_cont[i]->GetFunction("gaus");

          sigma_tdc = gtl->GetParameter(2);

          resol_1_3_5_cont->SetBinContent(i+1,25.*sqrt(2./3.)*(gtl->GetParameter(2)));
          resol_1_3_5_cont->SetBinError(i+1,0);//To distinguish from error obtain from CSQ, set error from MLE=0, always.
        }
      }else{//! if CSQ fit fails, perform CSQ-WW fit
        hist_1_3_5_cont[i]->Fit("gaus","WWQ");

        gtl = hist_1_3_5_cont[i]->GetFunction("gaus");

        sigma_tdc = gtl->GetParameter(2);

        resol_1_3_5_cont->SetBinContent(i+1,25.*sqrt(2./3.)*(gtl->GetParameter(2)));
        resol_1_3_5_cont->SetBinError(i+1,0);//To distinguish from error obtain from CSQ, set error from MLE=0, always.

      }
      
      
      
      /* hist_2_4_6_cont[i]->Fit("gaus","WWQ");
   
      gtl = hist_2_4_6_cont[i]->GetFunction("gaus");

      sigma_tdc = gtl->GetParameter(2);

      resol_2_4_6_cont->SetBinContent(i+1,25.*sqrt(2./3.)*(gtl->GetParameter(2))); 
      resol_2_4_6_cont->SetBinError(i+1,25.*sqrt(2./3.)*(gtl->GetParError(2)));
     
      gtl->Delete(); */   
      fr=hist_2_4_6_cont[i]->Fit("gaus","Q");
      if (fr==0){//! i.e. CSQ fit is successful
        gtl = hist_2_4_6_cont[i]->GetFunction("gaus");

        double rel_err=gtl->GetParameter(2)/gtl->GetParError(2);
        if (rel_err<0.5){

          sigma_tdc = gtl->GetParameter(2);

          resol_2_4_6_cont->SetBinContent(i+1,25.*sqrt(2./3.)*(gtl->GetParameter(2)));
          resol_2_4_6_cont->SetBinError(i+1,25.*sqrt(2./3.)*(gtl->GetParError(2)));
        }else{
          hist_2_4_6_cont[i]->Fit("gaus","WWQ");

          gtl = hist_2_4_6_cont[i]->GetFunction("gaus");

          sigma_tdc = gtl->GetParameter(2);

          resol_2_4_6_cont->SetBinContent(i+1,25.*sqrt(2./3.)*(gtl->GetParameter(2)));
          resol_2_4_6_cont->SetBinError(i+1,0);//To distinguish from error obtain from CSQ, set error from MLE=0, always.
        }
      }else{//! if CSQ fit fails, perform CSQ-WW fit
        hist_2_4_6_cont[i]->Fit("gaus","WWQ");

        gtl = hist_2_4_6_cont[i]->GetFunction("gaus");

        sigma_tdc = gtl->GetParameter(2);

        resol_2_4_6_cont->SetBinContent(i+1,25.*sqrt(2./3.)*(gtl->GetParameter(2)));
        resol_2_4_6_cont->SetBinError(i+1,0);//To distinguish from error obtain from CSQ, set error from MLE=0, always.

      }
      
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
      
                        
           
        hist_1_2_3[i]->Write();
        hist_1_2_3[i]->Delete();        
        hist_2_3_4[i]->Write();
        hist_2_3_4[i]->Delete(); 
        hist_3_4_5[i]->Write();
        hist_3_4_5[i]->Delete();
        hist_4_5_6[i]->Write();
        hist_4_5_6[i]->Delete();        
        hist_1_3_5[i]->Write();
        hist_1_3_5[i]->Delete(); 
        hist_2_4_6[i]->Write();
        hist_2_4_6[i]->Delete();	
	
        hist_1_2_3_cont[i]->Write();
        hist_1_2_3_cont[i]->Delete();        
        hist_2_3_4_cont[i]->Write();
        hist_2_3_4_cont[i]->Delete(); 
        hist_3_4_5_cont[i]->Write();
        hist_3_4_5_cont[i]->Delete();
        hist_4_5_6_cont[i]->Write();
        hist_4_5_6_cont[i]->Delete();        
        hist_1_3_5_cont[i]->Write();
        hist_1_3_5_cont[i]->Delete(); 
        hist_2_4_6_cont[i]->Write();
        hist_2_4_6_cont[i]->Delete();		    
          
	  };   
    

    
         outFile->cd("fullbar_tw");
	 

	 TH1D *avrg_resol = new TH1D("avrg_resol","avrg_resol",	6,0.5,6.5);
  avrg_resol->SetMarkerStyle(20);
  avrg_resol->SetLabelSize( 0.07, "X" );
  avrg_resol->SetLabelOffset(0.01, "X");
  avrg_resol->SetLabelSize( 0.07, "Y" );
  avrg_resol->SetLabelOffset(0.01, "Y");
  
   Double_t err;	
 
    Int_t nbin = resol_1_2_3->GetNbinsX();  
    avrg_resol->SetBinContent(1,(resol_1_2_3->IntegralAndError(1,nbin,err))/nbin);
   avrg_resol->SetBinError(1,err/nbin);
   
   avrg_resol->SetBinContent(2,(resol_2_3_4->IntegralAndError(1,nbin,err))/nbin);
   avrg_resol->SetBinError(2,err/nbin);  
   
   avrg_resol->SetBinContent(3,(resol_3_4_5->IntegralAndError(1,nbin,err))/nbin);
   avrg_resol->SetBinError(3,err/nbin);     
   
   avrg_resol->SetBinContent(4,(resol_4_5_6->IntegralAndError(1,nbin,err))/nbin);
   avrg_resol->SetBinError(4,err/nbin);  
   
   avrg_resol->SetBinContent(5,(resol_1_3_5->IntegralAndError(1,nbin,err))/nbin);
   avrg_resol->SetBinError(5,err/nbin);
   
   avrg_resol->SetBinContent(6,(resol_2_4_6->IntegralAndError(1,nbin,err))/nbin);
   avrg_resol->SetBinError(6,err/nbin);         
	 
 avrg_resol->GetXaxis()->SetBinLabel(1,"1_2_3");
 avrg_resol->GetXaxis()->SetBinLabel(2,"2_3_4");
 avrg_resol->GetXaxis()->SetBinLabel(3,"3_4_5"); 
 avrg_resol->GetXaxis()->SetBinLabel(4,"4_5_6");
 avrg_resol->GetXaxis()->SetBinLabel(5,"1_3_5");
 avrg_resol->GetXaxis()->SetBinLabel(6,"2_4_6"); 
       
        
        ss.str("");
	c1 = new TCanvas("Average resolution", "Average resolution", 800, 600);
	c1->Divide(2,1);
	c1->cd(1);
	avrg_resol->Draw();

	 
	      TH1D *resol_inp[6];
      resol_inp[0] = resol_1_2_3; 
      resol_inp[1] = resol_2_3_4;       
      resol_inp[2] = resol_3_4_5; 
      resol_inp[3] = resol_4_5_6; 
      resol_inp[4] = resol_1_3_5;       
      resol_inp[5] = resol_2_4_6;      
      
      
      ss.str("");
      ss << _out_dir << "/resol";
      if (setnum_inp ==0) { 
      macros.resol_cont_write("", ss.str().c_str(), resol_inp);
      } else {
      macros.resol_cont_write("resol", "", resol_inp);
      };
/*     for ( i=0; i<6; i++) {
     resol_inp[i]->Delete();
     };  
     
     */           
      	  
         resol_1_2_3->Write();
         resol_1_2_3->Delete();	  
         resol_2_3_4->Write();
         resol_2_3_4->Delete();
         resol_3_4_5->Write();
         resol_3_4_5->Delete();	 
         resol_4_5_6->Write();
         resol_4_5_6->Delete();	  
         resol_1_3_5->Write();
         resol_1_3_5->Delete();
         resol_2_4_6->Write();
         resol_2_4_6->Delete();
	 
	 
	 TH1D *avrg_resol_cont = new TH1D("avrg_resol_cont","avrg_resol_cont",	6,0.5,6.5);
  avrg_resol_cont->SetMarkerStyle(20);
  avrg_resol_cont->SetLabelSize( 0.07, "X" );
  avrg_resol_cont->SetLabelOffset(0.01, "X");
  avrg_resol_cont->SetLabelSize( 0.07, "Y" );
  avrg_resol_cont->SetLabelOffset(0.01, "Y");
  

 
    nbin = resol_1_2_3_cont->GetNbinsX();  
    avrg_resol_cont->SetBinContent(1,(resol_1_2_3_cont->IntegralAndError(1,nbin,err))/nbin);
   avrg_resol_cont->SetBinError(1,err/nbin);
   
   avrg_resol_cont->SetBinContent(2,(resol_2_3_4_cont->IntegralAndError(1,nbin,err))/nbin);
   avrg_resol_cont->SetBinError(2,err/nbin);  
   
   avrg_resol_cont->SetBinContent(3,(resol_3_4_5_cont->IntegralAndError(1,nbin,err))/nbin);
   avrg_resol_cont->SetBinError(3,err/nbin);     
   
   avrg_resol_cont->SetBinContent(4,(resol_4_5_6_cont->IntegralAndError(1,nbin,err))/nbin);
   avrg_resol_cont->SetBinError(4,err/nbin);  
   
   avrg_resol_cont->SetBinContent(5,(resol_1_3_5_cont->IntegralAndError(1,nbin,err))/nbin);
   avrg_resol_cont->SetBinError(5,err/nbin);
   
   avrg_resol_cont->SetBinContent(6,(resol_2_4_6_cont->IntegralAndError(1,nbin,err))/nbin);
   avrg_resol_cont->SetBinError(6,err/nbin);         
	 
 avrg_resol_cont->GetXaxis()->SetBinLabel(1,"1_2_3");
 avrg_resol_cont->GetXaxis()->SetBinLabel(2,"2_3_4");
 avrg_resol_cont->GetXaxis()->SetBinLabel(3,"3_4_5"); 
 avrg_resol_cont->GetXaxis()->SetBinLabel(4,"4_5_6");
 avrg_resol_cont->GetXaxis()->SetBinLabel(5,"1_3_5");
 avrg_resol_cont->GetXaxis()->SetBinLabel(6,"2_4_6"); 
 

	c1->cd(2);
	avrg_resol_cont->Draw();
	
	ss.str("");
	if (setnum_inp ==0) {
        ss << _out_dir << "/" << "avrg_resol" << ".png";
	} else {
	ss << "avrg_resol" << ".png";
	};
       c1->Print(ss.str().c_str());
       c1->Close();
 
      avrg_resol->Write();
    	avrg_resol->Delete();
	  
       avrg_resol_cont->Write();
    	avrg_resol_cont->Delete(); 
	
	
	
      resol_inp[0] = resol_1_2_3_cont; 
      resol_inp[1] = resol_2_3_4_cont;       
      resol_inp[2] = resol_3_4_5_cont; 
      resol_inp[3] = resol_4_5_6_cont; 
      resol_inp[4] = resol_1_3_5_cont;       
      resol_inp[5] = resol_2_4_6_cont;      
      
      ss.str("");
      ss << _out_dir << "/resol";
      if (setnum_inp ==0) {
      macros.resol_cont_write("_cont", ss.str().c_str(), resol_inp);
      } else {
      macros.resol_cont_write("resol_cont", "", resol_inp);
      };
	 
         resol_1_2_3_cont->Write();
         resol_1_2_3_cont->Delete();	  
         resol_2_3_4_cont->Write();
         resol_2_3_4_cont->Delete();
         resol_3_4_5_cont->Write();
         resol_3_4_5_cont->Delete();	 
         resol_4_5_6_cont->Write();
         resol_4_5_6_cont->Delete();	  
         resol_1_3_5_cont->Write();
         resol_1_3_5_cont->Delete();
         resol_2_4_6_cont->Write();
         resol_2_4_6_cont->Delete();	 	    
     
          Double_t tdcleftcut_corr[6],tdcrightcut_corr[6];
     TH1D *c_eff = new TH1D("c_eff", "c_eff",6, 0.5, 6.5); 
    
    if (setnum_inp ==0) {
    l_d=bar_length[fCombo->GetSelected()-1];
    } else {
    l_d=bar_length[setnum_inp-1];
    };
     

           for (i=0; i<6; i++) {
     
	    tdc_left << "tdc" << 2*i+1 << "_" << "tdc" << 2*i+2 << "_corr";	   
          TH1 *qqq = hist_tdcdiff_corr[i]->Rebin(10,"qqq");	   
       tdcleftcut_corr[i] = GetTDCleftcut(qqq);
       tdcrightcut_corr[i] = GetTDCrightcut(qqq);
       qqq->Delete(); 

       
       
        hist_tdcdiff_corr[i]->Write();
       
       TMacro *tdc1112cut;
       tdc1112cut = macros.TDC_plot(tdc_left.str().c_str(),tdcleftcut_corr[i],tdcrightcut_corr[i],hist_tdcdiff_corr[i]->GetMaximum());
	 tdc1112cut->Write();
	 tdc1112cut->Delete();  
       c_eff->SetBinContent(i+1,l_d/(tdcrightcut_corr[i]-tdcleftcut_corr[i])/25.*1000.); 	       
       	tdc_left.str(""); 	  	 
       
	   };

     c_eff->GetXaxis()->SetTitle("bars from top to bottom");
    c_eff->GetYaxis()->SetTitle("c_{eff} (cm/nsec)");
    
     	c1 = new TCanvas("eff speed of light", "eff speed of light", 800, 600);
	c1->cd();
	c_eff->Draw();
	
	ss.str("");
	if (setnum_inp ==0) {
        ss << _out_dir << "/" << "c_eff" << ".png";
	} else {
	ss << "c_eff" << ".png";
	};
       c1->Print(ss.str().c_str());
       c1->Close();
    
     c_eff->Write();
     c_eff->Delete(); 	 
 
 
 
 
   Short_t npoint_att = Int_t(l_d/20) +1; 
   Short_t k;
 
TBranch *event_att = t21->GetBranch("event_corr"); 
  Double_t step_att[6];

  for (i=0; i<6; i++) { 
  step_att[i] = (tdcrightcut_corr[i] - tdcleftcut_corr[i])*10./l_d;
  };
  
  
  TH1I *adc_att[2*npoint_att][12];
  
    for (i=0; i<2*npoint_att; i++) {
    for (j=0; j<12; j++) {    
    adc_num << "adc" << j << "point" << i+1;
  adc_att[i][j] = new TH1I(adc_num.str().c_str(),adc_num.str().c_str(),4096, -0.5, 4095.5); 
  adc_num.str("");
  };
  };
  
/* 
 
  
         TH1D *hist_1_2_3_cont_corr[npoints],*hist_2_3_4_cont_corr[npoints],*hist_3_4_5_cont_corr[npoints],*hist_4_5_6_cont_corr[npoints],*hist_1_3_5_cont_corr[npoints],*hist_2_4_6_cont_corr[npoints];
	
	 
      adc_num.str(""); 	 
       for (i=0; i<npoints; i++) {
       
    adc_num << "res_1_2_3_point" << i+1 << "_cont_corr";     
   hist_1_2_3_cont_corr[i] = new TH1D(adc_num.str().c_str(),adc_num.str().c_str(),8000,center_1_2_3-1000.,center_1_2_3+1000.);   
 
   
   
   adc_num.str("");   	
	
   adc_num << "res_2_3_4_point" << i+1 << "_cont_corr";     
   hist_2_3_4_cont_corr[i] = new TH1D(adc_num.str().c_str(),adc_num.str().c_str(),8000,center_2_3_4-1000.,center_2_3_4+1000.); 
         
   
   adc_num.str("");  
   
   adc_num << "res_3_4_5_point" << i+1 << "_cont_corr";     
   hist_3_4_5_cont_corr[i] = new TH1D(adc_num.str().c_str(),adc_num.str().c_str(),8000,center_3_4_5-1000.,center_3_4_5+1000.);   
  
        
   adc_num.str("");   
      
   adc_num << "res_4_5_6_point" << i+1 << "_cont_corr";     
   hist_4_5_6_cont_corr[i] = new TH1D(adc_num.str().c_str(),adc_num.str().c_str(),8000,center_4_5_6-1000.,center_4_5_6+1000.);   
      
   adc_num.str(""); 
   
   adc_num << "res_1_3_5_point" << i+1 << "_cont_corr";     
   hist_1_3_5_cont_corr[i] = new TH1D(adc_num.str().c_str(),adc_num.str().c_str(),8000,center_1_3_5-1000.,center_1_3_5+1000.);   
    
        
   adc_num.str(""); 
      
   adc_num << "res_2_4_6_point" << i+1 << "_cont_corr";     
   hist_2_4_6_cont_corr[i] = new TH1D(adc_num.str().c_str(),adc_num.str().c_str(),8000,center_2_4_6-1000.,center_2_4_6+1000.);     
        
              
   adc_num.str("");          
       
       
       };	 	   
  
	 Double_t diff5_corr = int(tdcrightcut_corr[5]-tdcleftcut_corr[5]);
	Double_t diff0_corr = int(tdcrightcut_corr[0]-tdcleftcut_corr[0]); 
	Double_t delta_corr = diff5_corr/npoints; 
	

  TH2D *hist_diff1vsdiff6_corr = new TH2D("tdcdiff1vstdcdiff6_corr","(tdc1 - tdc2)/2 : (tdc11 - tdc12)/2",3*l_d,-1*l_d,2*l_d,3*l_d,-1*l_d,2*l_d);
hist_diff1vsdiff6_corr->GetYaxis()->SetTitle("bar length (cm)");  
hist_diff1vsdiff6_corr->GetXaxis()->SetTitle("bar length (cm)");
hist_diff1vsdiff6_corr->GetXaxis()->SetTitleSize(0.06);
hist_diff1vsdiff6_corr->GetXaxis()->SetTitleOffset(0.7);
hist_diff1vsdiff6_corr->GetYaxis()->SetTitleSize(0.06);
hist_diff1vsdiff6_corr->GetYaxis()->SetTitleOffset(0.7);
  
        TH1D *histdiff1minusdiff6_corr = new TH1D("histdiff1minusdiff6_corr","(tdc1 - tdc2)/2 - (tdc11 - tdc12)/2",3*(diff0_corr+diff5_corr),tdcleftcut_corr[0]-tdcrightcut_corr[5]-0.25-(diff0_corr+diff5_corr),tdcrightcut_corr[0]-tdcleftcut_corr[5]-0.25+(diff0_corr+diff5_corr));


  for (i=0; i<event_att->GetEntries(); i++) {    
   event_att->GetEntry(i);
   
 hist_diff1vsdiff6_corr->Fill((((event_att->GetLeaf("tdc11_corr")->GetValue()-event_att->GetLeaf("tdc12_corr")->GetValue())/2.)-tdcleftcut_corr[5])*l_d/diff5_corr,(((event_att->GetLeaf("tdc1_corr")->GetValue()-event_att->GetLeaf("tdc2_corr")->GetValue())/2.)-tdcleftcut_corr[0])*l_d/diff0_corr,1);   

histdiff1minusdiff6_corr->Fill((event_att->GetLeaf("tdc1_corr")->GetValue()-event_att->GetLeaf("tdc2_corr")->GetValue()-(event_att->GetLeaf("tdc11_corr")->GetValue()-event_att->GetLeaf("tdc12_corr")->GetValue()))/2.,1);  
   
   };	

    histdiff1minusdiff6_corr->Fit("gaus","Q0");
	 fit = histdiff1minusdiff6_corr->GetFunction("gaus");	
    mean = fit->GetParameter(1);
   sigma = fit->GetParameter(2);    
   
   
    outFile->cd("full_bar");
    histdiff1minusdiff6_corr->Write();
    hist_diff1vsdiff6_corr->Write();
    histdiff1minusdiff6_corr->Delete();
    hist_diff1vsdiff6_corr->Delete();    
    
    
    // Determin ADC cut
    
    
    TH1I *hist_adc_point_corr[12][npoints];

   adc_num.str("");
  for (j=0; j<12; j++) {  
  
  for (i=0; i<npoints; i++) { 
  
   adc_num << "adc" << j+1 << "point_corr" << i+1; 
  
     hist_adc_point_corr[j][i] = new TH1I(adc_num.str().c_str(),adc_num.str().c_str(),4096, -0.5, 4095.5);
  
  
  };
  };
      
    
    
   for (i=0; i<event_att->GetEntries(); i++) {     
    
   event_att->GetEntry(i);
   event->GetEntry(i); 

 Double_t diff_top_corr = (event_att->GetLeaf("tdc1_corr")->GetValue()-event_att->GetLeaf("tdc2_corr")->GetValue())/2;

Double_t diff_btm_corr = (event_att->GetLeaf("tdc11_corr")->GetValue()-event_att->GetLeaf("tdc12_corr")->GetValue())/2;     
 
       for (j=0; j<npoints; j++) { 
       
       
       
      if ((diff_btm_corr <= tdcleftcut_corr[5] + j*delta_corr) ||     
    (diff_btm_corr > tdcleftcut_corr[5] + (j+1)*delta_corr) ||   
    (diff_top_corr <= tdcleftcut_corr[5] + j*delta_corr + mean ) ||    
    (diff_top_corr >= tdcleftcut_corr[5] + (j+1)*delta_corr + mean) ||
    (diff_top_corr - diff_btm_corr < mean - sigma) || 
    (diff_top_corr - diff_btm_corr > mean + sigma)) {  
    
     
  
    for (ii=0; ii<12; ii++) {
    adc_num.str("");
     adc_num << "adc" << ii+1;
     
hist_adc_point_corr[ii][j]->Fill(event->GetLeaf(adc_num.str().c_str())->GetValue(),1);
   adc_num.str("");
         
    };  
    
    
    
    
    };    
       
       
       
       
       
       
       
       };
   
   
   
   };   
    
    
   Double_t adc_low_cut_corr[12][npoints]; 
   for (i=0; i<npoints; i++) {
   
     for (j=0; j<12; j++) {   
     
     TH1 *temp_hist = Smooth_fun(hist_adc_point_corr[j][i],30);
     
     adc_low_cut_corr[j][i] = myFunction(temp_hist);
     
     temp_hist->Delete();
     
     
     };
     
     };
    
    
  TH2D *hist_diff1vsdiff6_point_corr[npoints];

  for (i=0; i<npoints; i++) {
  
   adc_num << "tdcdiff1vstdcdiff6" <<  "_point" << i+1 << "_corr"; 
hist_diff1vsdiff6_point_corr[i] = new TH2D(adc_num.str().c_str(),"(tdc1 - tdc2)/2 : (tdc11 - tdc12)/2",3*l_d, -1*l_d, 2*l_d, 3*l_d, -1*l_d,2*l_d);  
 adc_num.str("");
hist_diff1vsdiff6_point_corr[i]->GetYaxis()->SetTitle("bar length (cm)");  
hist_diff1vsdiff6_point_corr[i]->GetXaxis()->SetTitle("bar length (cm)");
hist_diff1vsdiff6_point_corr[i]->GetXaxis()->SetTitleSize(0.06);
hist_diff1vsdiff6_point_corr[i]->GetXaxis()->SetTitleOffset(0.7);
hist_diff1vsdiff6_point_corr[i]->GetYaxis()->SetTitleSize(0.06);
hist_diff1vsdiff6_point_corr[i]->GetYaxis()->SetTitleOffset(0.7);
 
 
 };    
    
    
    
    	 
// Gleb
  

   for (i=0; i<12; i++) {
   adc_num << "lambda_" << i+1 << "_new";     
   lambda1d[i] = new TH1D(adc_num.str().c_str(),adc_num.str().c_str(),npoints,tdcleftcut[5],tdcrightcut[5]);     
   adc_num.str("");  
   };





 for (iii=0; iii<12; iii++ ) {
 
 
//vector<vector< vector<TH1F*> > >  tdc1_tw_1dimm_iii;
 
   for (j=0; j<npoints; j++ ) { 
   
//   vector< vector<TH1F*> > tdc1_tw_1dimm_j;
   
     for (i=0; i<21; i++ ) { 
     
//      vector<TH1F*> tdc1_tw_1dimm_i; 
     
      for (ii=0; ii<21; ii++) {
       
   tdc1d_num << "tdc" << iii+1 << "_point_" << j+1 << "_" << i << "_" << ii;
   
//   if ((iii != 4) && (iii != 5))  {
   if ((iii != 4))  {   
   tdc1_tw_1dimm[iii][j][i][ii] = new TH1F(tdc1d_num.str().c_str(),tdc1d_num.str().c_str(),1500,tdccenter_nodiff[iii]-1500.,tdccenter_nodiff[iii]+1500.);
//  TH1F *qqqtw = new TH1F(tdc1d_num.str().c_str(),tdc1d_num.str().c_str(),1500,tdccenter_nodiff[iii]-1500.,tdccenter_nodiff[iii]+1500.); 
  
     }; 
     
     
     
 //  if (iii == 5)  {
//   tdc1_tw_1dimm[iii][j][i][ii] = new //TH1F(tdc1d_num.str().c_str(),tdc1d_num.str().c_str(),2500,-2500.,2500.);
//     };      
     
   
//    tdc1_tw_1dimm_i.push_back(qqqtw);  
   tdc1d_num.str("");   
   
   
   }; 
   
//   tdc1_tw_1dimm_j.push_back(tdc1_tw_1dimm_i);   
     
  
 };
//  tdc1_tw_1dimm_iii.push_back(tdc1_tw_1dimm_j);
 
   };
   
//   tdc1_tw_1dimm.push_back(tdc1_tw_1dimm_iii);
   
   };
  
   	 
	 
   for (i=0; i<event->GetEntries(); i++) { 
   	 
    event->GetEntry(i);
    event_att->GetEntry(i);    

    Double_t diff_top = (event->GetLeaf("tdc1")->GetValue()-event->GetLeaf("tdc2")->GetValue())/2.;
    Double_t diff_btm = (event->GetLeaf("tdc11")->GetValue()-event->GetLeaf("tdc12")->GetValue())/2.;  	
    
 Double_t diff_top_corr = (event_att->GetLeaf("tdc1_corr")->GetValue()-event_att->GetLeaf("tdc2_corr")->GetValue())/2;
Double_t diff_btm_corr = (event_att->GetLeaf("tdc11_corr")->GetValue()-event_att->GetLeaf("tdc12_corr")->GetValue())/2;   

    
     
    
      for (j=0; j<npoints; j++) { 
      
      
         if (diff_top_corr - diff_btm_corr > mean - sigma) { 
    if (diff_top_corr - diff_btm_corr < mean + sigma) { 

    if (diff_btm_corr > tdcleftcut_corr[5] + j*delta_corr) {
    if (diff_btm_corr <= tdcleftcut_corr[5] + (j+1)*delta_corr) {   
    
    if (diff_top_corr > tdcleftcut_corr[5] + j*delta_corr + mean) {    
    if (diff_top_corr < tdcleftcut_corr[5] + (j+1)*delta_corr + mean) {      
      
      
     adc_nolow = 1;
     for (jj=0; jj<12; jj++) {
     

      
     adc_num << "adc" << jj+1;
     if (event->GetLeaf(adc_num.str().c_str())->GetValue() < adc_low_cut[jj][j]) {
     adc_nolow = 0;
     }; 
     adc_num.str("");   
     };         
     
     
     if (adc_nolow) {     
     
      
      // loop over lambda ref
     
     for (iii=0; iii<21; iii++) {
     
     lambdaref = -2.+step*iii;
     
     // loop over lambda1
     
      for (jjj=0; jjj<21; jjj++) {    
     
      lambda1 = -2.+step*jjj;  
      

      for (kkk=0; kkk<12; kkk++) {  
      

      
      if ((kkk != 4) && (kkk != 5)) {
      adc_num << "tdc" << kkk+1;         

      tdcfill =  event->GetLeaf(adc_num.str().c_str())->GetValue();
      adc_num.str("");
      adc_num << "adc" << kkk+1; 
      
      tdcfill =  tdcfill -1000./sqrt(event->GetLeaf(adc_num.str().c_str())->GetValue())*lambda1;
    
      
      tdcfill =  tdcfill +1000./sqrt(event->GetLeaf("adc5")->GetValue())*lambdaref;
 	
  
      tdc1_tw_1dimm[kkk][j][jjj][iii]->Fill(tdcfill);

      
      adc_num.str(""); 
      };
      
       if (kkk == 5) {
         tdcfill =  event->GetLeaf("tdc6")->GetValue();
 
      tdcfill =  tdcfill -1000./sqrt(event->GetLeaf("adc6")->GetValue())*lambda1;
    
        tdcfill =  tdcfill - event->GetLeaf("tdc7")->GetValue();
      tdcfill =  tdcfill +1000./sqrt(event->GetLeaf("adc7")->GetValue())*lambdaref;
 	
		   
	   
      tdc1_tw_1dimm[kkk][j][jjj][iii]->Fill(tdcfill);
     
           
      };
      
      };
      
      

      

      
     
                                 }; // loop over lambda ref
     
                                 }; // loop over lambda 1     
          
      
       
    
    };
    };
    };
};
    };	 
	};
    }; 
};
    };	 
	 
	 
	 
	 
	 
   for (j=0; j<npoints; j++) {
   
   for (iii=0; iii<12; iii++) {
   
   if (( iii != 4) && ( iii != 5)) {
   tdc1d_num << "tdc_5_vs_tdc_" << iii+1 << "_point_" << j+1  << "_new" ;
   tdc1_tw_2dimm[iii][j] = new TH2F(tdc1d_num.str().c_str(),tdc1d_num.str().c_str(),21,-2.-step,6.+step,21,-2.-step,6.+step);
   tdc1d_num.str("");
   };
   
   if (iii == 5) {
   tdc1d_num << "tdc_7_vs_tdc_" << iii+1 << "_point_" << j+1 << "_new" ;
   tdc1_tw_2dimm[iii][j] = new TH2F(tdc1d_num.str().c_str(),tdc1d_num.str().c_str(),21,-2.-step,6.+step,21,-2.-step,6.+step);
   tdc1d_num.str("");
   };
     
   
   };
   
   };	 
	 
	 
	 
   for (i=0; i<npoints; i++) {	 
     adc_num << "point_" << i+1;      
      outFile->cd(adc_num.str().c_str());    
       adc_num.str(""); 	 
	 
	 
       // loop over lambda ref
     adc_num.str("");
     for (iii=0; iii<21; iii++) {
     
          lambdaref = -2.+step*iii;
     // loop over lambda1
     
      for (jjj=0; jjj<21; jjj++) { 
      
               lambda1 = -2.+step*jjj; 	 
	 
	 
      for (j=0; j<12; j++) {

      if (j != 4) {   
      

      
      tdc1_tw_1dimm[j][i][jjj][iii]->Fit("gaus","WQ0");
   
      TF1 *gtl = tdc1_tw_1dimm[j][i][jjj][iii]->GetFunction("gaus");

      sigma_tdc = gtl->GetParameter(2);

      tdc1_tw_2dimm[j][i]->Fill(lambda1,lambdaref,sigma_tdc); 
      tdc1_tw_2dimm[j][i]->SetBinError(jjj+1,iii+1,gtl->GetParError(2));
     
      gtl->Delete();   	 
	 
	 
     };

          
      
      };
      

      
      };
      };	
      
        for (j=0; j<12; j++) { 
      if (j != 4) {	           
      tdc1_tw_2dimm[j][i]->Write();
      };
      };  
       
       
	 
   const Int_t npar = 5;
   Double_t f2params[npar] = {1.,2.,1.,2.5,6.};
   TF2* f222 = new TF2("f222",&g2tw,-2,6,-2,6, npar);
   tdc5avr = 0.;
   tdc5avr_err = 0.;
   for (kkk=0; kkk<12; kkk++) {
   f222->SetParameters(f2params);
   f222->SetParLimits(0,-2.,6.);
   f222->SetParLimits(1,1.,3.1);
   f222->SetParLimits(2,-2.,6.);  
   f222->SetParLimits(3,1.6,5.); 	 
   if (( kkk != 4)) { 
   tdc1_tw_2dimm[kkk][i]->Fit("f222","MLNQR");
   
   lambda1d[kkk]->SetBinContent(i+1,f222->GetParameter(0));
   lambda1d[kkk]->SetBinError(i+1,f222->GetParError(0));
   if (( kkk != 5)) {
   tdc5avr = tdc5avr + f222->GetParameter(2);
   tdc5avr_err = tdc5avr_err  + f222->GetParError(2);
   };
   
    }; 	 
	 
    
      };
    
    lambda1d[4]->SetBinContent(i+1,tdc5avr/10.);  
    lambda1d[4]->SetBinError(i+1,tdc5avr_err/10.);      
      
      };	 
	 
	 
    tdc_left.str("");	 
    for (i=0; i<12; i++) {
     tdc_left << twfit << i;
     twfit[i] = new TF1(tdc_left.str().c_str(),"pol2",lambda1d[i]->	GetBinLowEdge(1),lambda1d[i]->GetBinLowEdge(npoints)+lambda1d[i]->GetBinWidth(npoints));
     twfit[i]->SetParLimits(2,0.,10.);
     tdc_left.str("");
     lambda1d[i]->Fit(twfit[i],"QL0");
     };	 
	 
	 
    outFile->cd("fullbar_tw");	 
    
    for (i=0; i<12; i++) {
     lambda1d[i]->Write();
//     lambda[i]->Write();  
     
     };       
	 
      TMacro *tw_params_new;
      tw_params_new = macros.tw_params_plot_new();
      tw_params_new->Write();
      tw_params_new->Delete();	 
	 
	 
	 
	 
*/	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
//   tdc1_tw_1dimm.clear();	 
	 

   for (i=0; i<event_att->GetEntries(); i++) { 
   
        if (setnum_inp ==0) {
        if (i%10 == 0) {
     fHProg1->Increment(1000./8./Double_t(event_att->GetEntries()));
     };
     };
   
   
   event_att->GetEntry(i);
   event->GetEntry(i);
   
/*   
   // Calculating tw corrected resolution
   
 Double_t diff_top_corr = (event_att->GetLeaf("tdc1_corr")->GetValue()-event_att->GetLeaf("tdc2_corr")->GetValue())/2;
Double_t diff_btm_corr = (event_att->GetLeaf("tdc11_corr")->GetValue()-event_att->GetLeaf("tdc12_corr")->GetValue())/2;  
    Double_t diff_top = (event->GetLeaf("tdc1")->GetValue()-event->GetLeaf("tdc2")->GetValue())/2.;
    Double_t diff_btm = (event->GetLeaf("tdc11")->GetValue()-event->GetLeaf("tdc12")->GetValue())/2.;    	 


     for (j=0; j<npoints; j++) { 
     
   
       
     
     
     if ((diff_btm_corr <= tdcleftcut_corr[5] + j*delta_corr) ||     
    (diff_btm_corr > tdcleftcut_corr[5] + (j+1)*delta_corr) ||   
    (diff_top_corr <= tdcleftcut_corr[5] + j*delta_corr + mean ) ||    
    (diff_top_corr >= tdcleftcut_corr[5] + (j+1)*delta_corr + mean) ||
    (diff_top_corr - diff_btm_corr < mean - sigma) || 
    (diff_top_corr - diff_btm_corr > mean + sigma)) { 
    
 hist_diff1vsdiff6_point_corr[j]->Fill(((event_att->GetLeaf("tdc11_corr")->GetValue()-event_att->GetLeaf("tdc12_corr")->GetValue())/2.-tdcleftcut_corr[5])*l_d/diff5_corr,((event_att->GetLeaf("tdc1_corr")->GetValue()-event_att->GetLeaf("tdc2_corr")->GetValue())/2-tdcleftcut_corr[0])*l_d/diff0_corr,1);   
    
    
    };   
     
     
     
     
     
     
        if (diff_top_corr - diff_btm_corr > mean - sigma) { 
    if (diff_top_corr - diff_btm_corr < mean + sigma) { 

    if (diff_btm_corr > tdcleftcut_corr[5] + j*delta_corr) {
    if (diff_btm_corr <= tdcleftcut_corr[5] + (j+1)*delta_corr) {   
    
    if (diff_top_corr > tdcleftcut_corr[5] + j*delta_corr + mean) {    
    if (diff_top_corr < tdcleftcut_corr[5] + (j+1)*delta_corr + mean) { 

     adc_nolow = 1;
    

   
      adc_num.str("");    
   
         for (jj=0; jj<12; jj++) {
   
     adc_num << "adc" << jj+1;
     if (event->GetLeaf(adc_num.str().c_str())->GetValue() < adc_low_cut_corr[jj][j]) {
     adc_nolow = 0;
     }; 
     adc_num.str("");   
     };        
      

       
      
      

       
      if (adc_nolow) {
    
 
   
    tdc1d_num.str(""); 
       
      for (iii=0; iii<12; iii++)  {       
//          tdc1d_num << "tdc" << iii+1 << "_corr"; 
      
//         tdc_corr[iii] = event_att->GetLeaf(tdc1d_num.str().c_str())->GetValue();


    adc_num << "adc" << iii+1;

 
 
    tdc1d_num << "tdc" << iii+1; 
    
    
    tdc_corr[iii] = event->GetLeaf(tdc1d_num.str().c_str())->GetValue();
    tdc_corr[iii] = tdc_corr[iii] - 1000.*lambda1d[iii]->GetBinContent(j+1)/sqrt(event->GetLeaf(adc_num.str().c_str())->GetValue()); 
    tdc_corr[iii] = tdc_corr[iii] + 1000.*lambda1d[4]->GetBinContent(j+1)/sqrt(event->GetLeaf("adc5")->GetValue());
    tdc1d_num.str("");
 
 
   
    adc_num.str("");


 
    
         tdc1d_num.str("");     
      };

   
      
    t_1_2_3 = (tdc_corr[0] + tdc_corr[1] + tdc_corr[4] + tdc_corr[5])/4. - (tdc_corr[2]+tdc_corr[3])/2.;    
    
    t_2_3_4 = (tdc_corr[2] + tdc_corr[3] + tdc_corr[6] + tdc_corr[7])/4. - (tdc_corr[4]+tdc_corr[5])/2.;
    
    t_3_4_5 = (tdc_corr[4] + tdc_corr[5] + tdc_corr[8] + tdc_corr[9])/4. - (tdc_corr[6]+tdc_corr[7])/2.;
    
    t_4_5_6 = (tdc_corr[6] + tdc_corr[7] + tdc_corr[10] + tdc_corr[11])/4. - (tdc_corr[8]+tdc_corr[9])/2.;  
    
    t_1_3_5 = (tdc_corr[0] + tdc_corr[1] + tdc_corr[8] + tdc_corr[9])/4. - (tdc_corr[4]+tdc_corr[5])/2.;  
    
    t_2_4_6 = (tdc_corr[2] + tdc_corr[3] + tdc_corr[10] + tdc_corr[11])/4. - (tdc_corr[6]+tdc_corr[7])/2.;   

    

    hist_1_2_3_cont_corr[j]->Fill(t_1_2_3);
     
    hist_2_3_4_cont_corr[j]->Fill(t_2_3_4);
        
    hist_3_4_5_cont_corr[j]->Fill(t_3_4_5); 

    hist_4_5_6_cont_corr[j]->Fill(t_4_5_6); 
   
    hist_1_3_5_cont_corr[j]->Fill(t_1_3_5);
  
    hist_2_4_6_cont_corr[j]->Fill(t_2_4_6);
      
            
      
  
      
      
      
      };    
     



                                                                      };
				                                   };
							        };
							    };
							   };
							     };
								       
								       
				};


*/

   
//#include "qqq.cxx";   

  // Calculating att length 
    for (j=0; j<npoint_att; j++) {
    
    for (k=0; k<6; k++) {    

   adc_num.str("");   
   tdc_num.str("");    


    adc_num << "tdc" << 2*k+1 << "_corr"; 
    tdc_num << "tdc" << 2*k+2 << "_corr";        

    if ((event_att->GetLeaf(adc_num.str().c_str())->GetValue()-event_att->GetLeaf(tdc_num.str().c_str())->GetValue())/2. > tdcleftcut_corr[k] + step_att[k]*j) {
    
    if ((event_att->GetLeaf(adc_num.str().c_str())->GetValue()-event_att->GetLeaf(tdc_num.str().c_str())->GetValue())/2. < tdcleftcut_corr[k] + step_att[k]*(j+1)) { 
         
    
   adc_num.str(""); 
   tdc_num.str("");   

    adc_num << "adc" << 2*k+1;    
    tdc_num << "adc" << 2*k+2; 
            
    adc_att[j][2*k]->Fill(event->GetLeaf(adc_num.str().c_str())->GetValue());
    adc_att[j][2*k+1]->Fill(event->GetLeaf(tdc_num.str().c_str())->GetValue());
    
    
   adc_num.str("");   
   tdc_num.str(""); 
         
    };
    
    }; 
    
    };
    
    
     for (k=0; k<6; k++) {  
       
   adc_num.str("");   
   tdc_num.str("");
   
    adc_num << "tdc" << 2*k+1 << "_corr"; 
    tdc_num << "tdc" << 2*k+2 << "_corr";    
    
    
    if ((event_att->GetLeaf(adc_num.str().c_str())->GetValue()-event_att->GetLeaf(tdc_num.str().c_str())->GetValue())/2. < tdcrightcut_corr[k] - step_att[k]*j) {
    
    if ((event_att->GetLeaf(adc_num.str().c_str())->GetValue()-event_att->GetLeaf(tdc_num.str().c_str())->GetValue())/2. > tdcrightcut_corr[k] - step_att[k]*(j+1)) {    
    
   adc_num.str("");   
   tdc_num.str("");   
   
     
    adc_num << "adc" << 2*k+1;    
    tdc_num << "adc" << 2*k+2;  
      
    adc_att[2*npoint_att-j-1][2*k]->Fill(event->GetLeaf(adc_num.str().c_str())->GetValue());
adc_att[2*npoint_att-j-1][2*k+1]->Fill(event->GetLeaf(tdc_num.str().c_str())->GetValue());    

   adc_num.str("");   
   tdc_num.str("");    
        
    };
    
    };  
    
    };   
    
    
    
     
    
    };   
   
   
   }; 
   

   
     outFile->mkdir("att_length");
     outFile->cd("att_length");      
      TDirectory *att_dir =outFile->GetDirectory("att_length");
     TDirectory *att_length_adc[12]; 
     adc_num.str("");     
     for (k=0; k<12; k++) { 
     adc_num << "adc" << k+1; 
     att_dir->mkdir(adc_num.str().c_str()); 
     adc_num.str("");  
      adc_num << "att_length/adc" << k+1;        
     att_length_adc[k] =outFile->GetDirectory(adc_num.str().c_str());
     adc_num.str("");     
     };
     
 
   
     
   Double_t err_att;
   Double_t aat_adc1[2*npoint_att],err_att_adc1[2*npoint_att],position[2*npoint_att],position_err[2*npoint_att];
    Double_t aat_adc1_max[2*npoint_att],err_att_adc1_max[2*npoint_att];

TGraphErrors *Tg[12];
TGraphErrors *Tg_max[12];
    
c1 = new TCanvas("att_length_canvas", "att_length_canvas" , 800, 600);
	c1->cd();
	c1->Divide(4,3);    
TCanvas *c2;

if (setnum_inp ==0) { 
if (inc_langau->GetState() == kButtonDown) {
c2 = new TCanvas("att_length_langau_canvas", "att_length_langau_canvas" , 800, 600);
	c2->cd();
	c2->Divide(4,3);    

};
} else {
if (langau_inp) {
c2 = new TCanvas("att_length_langau_canvas", "att_length_langau_canvas" , 800, 600);
	c2->cd();
	c2->Divide(4,3);
	};
	}; 



Float_t twopoints;
     stringstream out;
     out.str("");
     if (setnum_inp ==0) {
     out << _out_dir << "/" <<  "att_length.dat";
     } else {
     out << "att_length.dat";
     };
ofstream* attoutputfile;
attoutputfile = new ofstream(out.str().c_str());

    for (k=0; k<12; k++) { 

     
     if (setnum_inp ==0) {
     fHProg1->Increment(1000./9./12.);
     };

     adc_num.str("");
     adc_num << "att_length/adc" << k+1;    
     outFile->cd(adc_num.str().c_str());
     adc_num.str("");      
     
    for (j=0; j<2*npoint_att; j++) { 
   
if (setnum_inp ==0) {
if (inc_langau->GetState() == kButtonDown) {
    aat_adc1[j] = landauconvgauss(adc_att[j][k],err_att);
    err_att_adc1[j] = err_att;
    };   
    } else {
    if (langau_inp) {
    aat_adc1[j] = landauconvgauss(adc_att[j][k],err_att);
    err_att_adc1[j] = err_att;    
    };
    };

    position_err[j] = 0.;
    if (j < npoint_att) {
    position[j] = 5 + j*10;
     } else {
     position[j] = l_d - (2*npoint_att - j - 1)*10 -5;
     };
     TH1* qqq = Smooth_fun(adc_att[j][k],10);
     aat_adc1_max[j] = Double_t(qqq->GetBinCenter(qqq->GetMaximumBin()));
     qqq->Delete();
     err_att_adc1_max[j] = 0.;
    adc_att[j][k]->SetDirectory(att_length_adc[k]);
    adc_att[j][k]->Write();
    adc_att[j][k]->Delete();    
    };  
   
if (setnum_inp ==0) {
if (inc_langau->GetState() == kButtonDown) {
    Tg[k] = new TGraphErrors(2*npoint_att,position,aat_adc1,position_err,err_att_adc1);
    Tg[k]->GetXaxis()->SetTitle("position (cm)");
    Tg[k]->GetXaxis()->SetTitleSize(0.06);
    Tg[k]->GetXaxis()->SetTitleOffset(0.7);
    }; 
    } else {
    if (langau_inp) {
    Tg[k] = new TGraphErrors(2*npoint_att,position,aat_adc1,position_err,err_att_adc1);
    Tg[k]->GetXaxis()->SetTitle("position (cm)");
    Tg[k]->GetXaxis()->SetTitleSize(0.06);
    Tg[k]->GetXaxis()->SetTitleOffset(0.7);  
    };
    };     
    
    
    Tg_max[k] = new TGraphErrors(2*npoint_att,position,aat_adc1_max,position_err,err_att_adc1_max);
    Tg_max[k]->GetXaxis()->SetTitle("position (cm)");
    Tg_max[k]->GetXaxis()->SetTitleSize(0.06);
    Tg_max[k]->GetXaxis()->SetTitleOffset(0.7);    

     TMacro *att_adc_plot;
     
     
if (setnum_inp ==0) {     
if (inc_langau->GetState() == kButtonDown) {
     adc_num << "adc" << k+1 << "_att_length"; 
     att_adc_plot = macros.att_plot(adc_num.str().c_str());     
   Tg[k]->SetName(adc_num.str().c_str());  
   Tg[k]->SetMarkerStyle(kFullCircle); 
   Tg[k]->SetTitle(adc_num.str().c_str());    
   macros.att_write(adc_num.str().c_str(), _out_dir.c_str(), Tg[k], c2, k, twopoints);
   att_adc_plot->Write();
   att_adc_plot->Delete();   
   Tg[k]->Write(); 
   adc_num.str("");      
   };
   } else {
   if (langau_inp) {
     adc_num << "adc" << k+1 << "_att_length"; 
     att_adc_plot = macros.att_plot(adc_num.str().c_str());     
   Tg[k]->SetName(adc_num.str().c_str());  
   Tg[k]->SetMarkerStyle(kFullCircle); 
   Tg[k]->SetTitle(adc_num.str().c_str()); 
   macros.att_write(adc_num.str().c_str(), _out_dir.c_str(), Tg[k], c2, k, twopoints);
   att_adc_plot->Write();
   att_adc_plot->Delete();   
   Tg[k]->Write(); 
   adc_num.str("");      
   };
   };   
   
   
   
     adc_num << "adc" << k+1 << "_att_length_max"; 
     att_adc_plot = macros.att_plot(adc_num.str().c_str());
   Tg_max[k]->SetName(adc_num.str().c_str());    
   Tg_max[k]->SetMarkerStyle(kFullCircle); 
   Tg_max[k]->SetTitle(adc_num.str().c_str()); 
   
   macros.att_write(adc_num.str().c_str(), _out_dir.c_str(), Tg_max[k], c1, k, twopoints);
   
//   cout << "\n" << "lambda_twopoints_" << k+1 << " = " << twopoints <<"\n";
    *attoutputfile << twopoints << endl;
    
   att_adc_plot->Write();
   att_adc_plot->Delete();
   Tg_max[k]->Write();
   adc_num.str(""); 
 
 
   };
     
 
     out.str("");
     if (setnum_inp ==0) {
     out << _out_dir << "/" <<  "att_length_max.png";
     } else {
     out << "att_length_max.png";
     };
        c1->Print(out.str().c_str());
	c1->Close();
if (setnum_inp ==0) {  
if (inc_langau->GetState() == kButtonDown) {
     out.str("");
     if (setnum_inp ==0) {
     out << _out_dir << "/" <<  "att_length.png";
     } else {
     out << "att_length.png";
     };
        c2->Print(out.str().c_str());
	c2->Close();
   };
   } else {
   if (langau_inp) {
     out.str("");
     if (setnum_inp ==0) {
     out << _out_dir << "/" <<  "att_length.png";
     } else {
     out << "att_length.png";
     };
        c2->Print(out.str().c_str());
	c2->Close(); 
	};
	};  
   
 attoutputfile->close();
 delete attoutputfile;

/*     TH1D *resol_1_2_3_cont_corr = new TH1D("resol_1_2_3_cont_corr","resol_1_2_3_cont_corr",npoints,0.,l_d);
resol_1_2_3_cont_corr->GetYaxis()->SetTitle("resolution (psec)");  
resol_1_2_3_cont_corr->GetXaxis()->SetTitle("bar length (cm)");
resol_1_2_3_cont_corr->GetXaxis()->SetTitleSize(0.06);
resol_1_2_3_cont_corr->GetXaxis()->SetTitleOffset(0.9);
resol_1_2_3_cont_corr->GetYaxis()->SetTitleSize(0.06);
resol_1_2_3_cont_corr->GetYaxis()->SetTitleOffset(1.3);     
      TH1D *resol_2_3_4_cont_corr = new TH1D("resol_2_3_4_cont_corr","resol_2_3_4_cont_corr",npoints,0.,l_d);
resol_2_3_4_cont_corr->GetYaxis()->SetTitle("resolution (psec)");  
resol_2_3_4_cont_corr->GetXaxis()->SetTitle("bar length (cm)");
resol_2_3_4_cont_corr->GetXaxis()->SetTitleSize(0.06);
resol_2_3_4_cont_corr->GetXaxis()->SetTitleOffset(0.9);
resol_2_3_4_cont_corr->GetYaxis()->SetTitleSize(0.06);
resol_2_3_4_cont_corr->GetYaxis()->SetTitleOffset(1.3);       
      TH1D *resol_3_4_5_cont_corr = new TH1D("resol_3_4_5_cont_corr","resol_3_4_5_cont_corr",npoints,0.,l_d); 
resol_3_4_5_cont_corr->GetYaxis()->SetTitle("resolution (psec)");  
resol_3_4_5_cont_corr->GetXaxis()->SetTitle("bar length (cm)");
resol_3_4_5_cont_corr->GetXaxis()->SetTitleSize(0.06);
resol_3_4_5_cont_corr->GetXaxis()->SetTitleOffset(0.9);
resol_3_4_5_cont_corr->GetYaxis()->SetTitleSize(0.06);
resol_3_4_5_cont_corr->GetYaxis()->SetTitleOffset(1.3);       
      TH1D *resol_4_5_6_cont_corr = new TH1D("resol_4_5_6_cont_corr","resol_4_5_6_cont_corr",npoints,0.,l_d);
resol_4_5_6_cont_corr->GetYaxis()->SetTitle("resolution (psec)");  
resol_4_5_6_cont_corr->GetXaxis()->SetTitle("bar length (cm)");
resol_4_5_6_cont_corr->GetXaxis()->SetTitleSize(0.06);
resol_4_5_6_cont_corr->GetXaxis()->SetTitleOffset(0.9);
resol_4_5_6_cont_corr->GetYaxis()->SetTitleSize(0.06);
resol_4_5_6_cont_corr->GetYaxis()->SetTitleOffset(1.3);       
      TH1D *resol_1_3_5_cont_corr = new TH1D("resol_1_3_5_cont_corr","resol_1_3_5_cont_corr",npoints,0.,l_d);
resol_1_3_5_cont_corr->GetYaxis()->SetTitle("resolution (psec)");  
resol_1_3_5_cont_corr->GetXaxis()->SetTitle("bar length (cm)");
resol_1_3_5_cont_corr->GetXaxis()->SetTitleSize(0.06);
resol_1_3_5_cont_corr->GetXaxis()->SetTitleOffset(0.9);
resol_1_3_5_cont_corr->GetYaxis()->SetTitleSize(0.06);
resol_1_3_5_cont_corr->GetYaxis()->SetTitleOffset(1.3);       
      TH1D *resol_2_4_6_cont_corr = new TH1D("resol_2_4_6_cont_corr","resol_2_4_6_cont_corr",npoints,0.,l_d); 
resol_2_4_6_cont_corr->GetYaxis()->SetTitle("resolution (psec)");  
resol_2_4_6_cont_corr->GetXaxis()->SetTitle("bar length (cm)");
resol_2_4_6_cont_corr->GetXaxis()->SetTitleSize(0.06);
resol_2_4_6_cont_corr->GetXaxis()->SetTitleOffset(0.9);
resol_2_4_6_cont_corr->GetYaxis()->SetTitleSize(0.06);
resol_2_4_6_cont_corr->GetYaxis()->SetTitleOffset(1.3);              

   TF1 *gtl;
   
       adc_num.str(""); 
   for (i=0; i<npoints; i++) {
   
  
       hist_2_3_4_cont_corr[i]->Fit("gaus","WWQ");
   
      gtl = hist_2_3_4_cont_corr[i]->GetFunction("gaus");

      sigma_tdc = gtl->GetParameter(2);

      resol_2_3_4_cont_corr->SetBinContent(i+1,25.*sqrt(2./3.)*(gtl->GetParameter(2))); 
      resol_2_3_4_cont_corr->SetBinError(i+1,25.*sqrt(2./3.)*(gtl->GetParError(2)));
     
      gtl->Delete();  
      
      
       
      hist_1_2_3_cont_corr[i]->Fit("gaus","WWQ");
   
      gtl = hist_1_2_3_cont_corr[i]->GetFunction("gaus");

      sigma_tdc = gtl->GetParameter(2);

      resol_1_2_3_cont_corr->SetBinContent(i+1,25.*sqrt(2./3.)*(gtl->GetParameter(2))); 
      resol_1_2_3_cont_corr->SetBinError(i+1,25.*sqrt(2./3.)*(gtl->GetParError(2)));
     
      gtl->Delete();    
      
      
      
      hist_3_4_5_cont_corr[i]->Fit("gaus","WWQ");
   
      gtl = hist_3_4_5_cont_corr[i]->GetFunction("gaus");

      sigma_tdc = gtl->GetParameter(2);

      resol_3_4_5_cont_corr->SetBinContent(i+1,25.*sqrt(2./3.)*(gtl->GetParameter(2))); 
      resol_3_4_5_cont_corr->SetBinError(i+1,25.*sqrt(2./3.)*(gtl->GetParError(2)));
     
      gtl->Delete(); 
      
      
      hist_4_5_6_cont_corr[i]->Fit("gaus","WWQ");
   
      gtl = hist_4_5_6_cont_corr[i]->GetFunction("gaus");

      sigma_tdc = gtl->GetParameter(2);

      resol_4_5_6_cont_corr->SetBinContent(i+1,25.*sqrt(2./3.)*(gtl->GetParameter(2))); 
      resol_4_5_6_cont_corr->SetBinError(i+1,25.*sqrt(2./3.)*(gtl->GetParError(2)));
     
      gtl->Delete();       
      
                  
      
      hist_1_3_5_cont_corr[i]->Fit("gaus","WWQ");
   
      gtl = hist_1_3_5_cont_corr[i]->GetFunction("gaus");

      sigma_tdc = gtl->GetParameter(2);

      resol_1_3_5_cont_corr->SetBinContent(i+1,25.*sqrt(2./3.)*(gtl->GetParameter(2))); 
      resol_1_3_5_cont_corr->SetBinError(i+1,25.*sqrt(2./3.)*(gtl->GetParError(2)));
     
      gtl->Delete();  
      
      
      
       hist_2_4_6_cont_corr[i]->Fit("gaus","WWQ");
   
      gtl = hist_2_4_6_cont_corr[i]->GetFunction("gaus");

      sigma_tdc = gtl->GetParameter(2);

      resol_2_4_6_cont_corr->SetBinContent(i+1,25.*sqrt(2./3.)*(gtl->GetParameter(2))); 
      resol_2_4_6_cont_corr->SetBinError(i+1,25.*sqrt(2./3.)*(gtl->GetParError(2)));
     
      gtl->Delete();        
   
   
   
      adc_num << "point_" << i+1;      
      outFile->cd(adc_num.str().c_str());    
       adc_num.str("");      
   
   hist_diff1vsdiff6_point_corr[i]->Write();
      hist_diff1vsdiff6_point_corr[i]->Delete();   
   

  
     adc_num << "point_" << i+1;      
      outFile->cd(adc_num.str().c_str());    
       adc_num.str(""); 
       
        hist_1_2_3_cont_corr[i]->Write();
        hist_1_2_3_cont_corr[i]->Delete();        
        hist_2_3_4_cont_corr[i]->Write();
        hist_2_3_4_cont_corr[i]->Delete(); 
        hist_3_4_5_cont_corr[i]->Write();
        hist_3_4_5_cont_corr[i]->Delete();
        hist_4_5_6_cont_corr[i]->Write();
        hist_4_5_6_cont_corr[i]->Delete();        
        hist_1_3_5_cont_corr[i]->Write();
        hist_1_3_5_cont_corr[i]->Delete(); 
        hist_2_4_6_cont_corr[i]->Write();
        hist_2_4_6_cont_corr[i]->Delete();	       
       
       };  
       
       outFile->cd("fullbar_tw");
       
       
	 TH1D *avrg_resol_cont_corr = new TH1D("avrg_resol_cont_corr","avrg_resol_cont_corr",	6,0.5,6.5);
  avrg_resol_cont_corr->SetMarkerStyle(20);
  avrg_resol_cont_corr->SetLabelSize( 0.07, "X" );
  avrg_resol_cont_corr->SetLabelOffset(0.01, "X");
  avrg_resol_cont_corr->SetLabelSize( 0.07, "Y" );
  avrg_resol_cont_corr->SetLabelOffset(0.01, "Y");
  avrg_resol_cont_corr->GetYaxis()->SetTitle("resolution (psec)");  
avrg_resol_cont_corr->GetXaxis()->SetTitle("bar combination");
avrg_resol_cont_corr->GetXaxis()->SetTitleSize(0.05);
avrg_resol_cont_corr->GetXaxis()->SetTitleOffset(0.87);
avrg_resol_cont_corr->GetYaxis()->SetTitleSize(0.05);
avrg_resol_cont_corr->GetYaxis()->SetTitleOffset(0.85); 
  
      nbin = resol_1_2_3_cont_corr->GetNbinsX();  
      
avrg_resol_cont_corr->SetBinContent(1,(resol_1_2_3_cont_corr->IntegralAndError(1,nbin,err))/nbin);
   avrg_resol_cont_corr->SetBinError(1,err/nbin);
   
   avrg_resol_cont_corr->SetBinContent(2,(resol_2_3_4_cont_corr->IntegralAndError(1,nbin,err))/nbin);
   avrg_resol_cont_corr->SetBinError(2,err/nbin);  
   
   avrg_resol_cont_corr->SetBinContent(3,(resol_3_4_5_cont_corr->IntegralAndError(1,nbin,err))/nbin);
   avrg_resol_cont_corr->SetBinError(3,err/nbin);     
   
   avrg_resol_cont_corr->SetBinContent(4,(resol_4_5_6_cont_corr->IntegralAndError(1,nbin,err))/nbin);
   avrg_resol_cont_corr->SetBinError(4,err/nbin);  
   
   avrg_resol_cont_corr->SetBinContent(5,(resol_1_3_5_cont_corr->IntegralAndError(1,nbin,err))/nbin);
   avrg_resol_cont_corr->SetBinError(5,err/nbin);
   
   avrg_resol_cont_corr->SetBinContent(6,(resol_2_4_6_cont_corr->IntegralAndError(1,nbin,err))/nbin);
   avrg_resol_cont_corr->SetBinError(6,err/nbin);         
	 
 avrg_resol_cont_corr->GetXaxis()->SetBinLabel(1,"1_2_3");
 avrg_resol_cont_corr->GetXaxis()->SetBinLabel(2,"2_3_4");
 avrg_resol_cont_corr->GetXaxis()->SetBinLabel(3,"3_4_5"); 
 avrg_resol_cont_corr->GetXaxis()->SetBinLabel(4,"4_5_6");
 avrg_resol_cont_corr->GetXaxis()->SetBinLabel(5,"1_3_5");
 avrg_resol_cont_corr->GetXaxis()->SetBinLabel(6,"2_4_6"); 
 
       avrg_resol_cont_corr->Write();
    	avrg_resol_cont_corr->Delete();       
             
       
       
       
       
       
       
         resol_1_2_3_cont_corr->Write();
         resol_1_2_3_cont_corr->Delete();	  
         resol_2_3_4_cont_corr->Write();
         resol_2_3_4_cont_corr->Delete();
         resol_3_4_5_cont_corr->Write();
         resol_3_4_5_cont_corr->Delete();	 
         resol_4_5_6_cont_corr->Write();
         resol_4_5_6_cont_corr->Delete();	  
         resol_1_3_5_cont_corr->Write();
         resol_1_3_5_cont_corr->Delete();
         resol_2_4_6_cont_corr->Write();      
       
      TMacro *resolcont_plot_corr;
      resolcont_plot_corr= macros.resol_cont_plot("_cont_corr");
      resolcont_plot_corr->Write();
      resolcont_plot_corr->Delete();  
*/
 
         outFile->Close(); 
  
//  pid_t pid = fork(); 
//  Int_t rv;
//  if(pid) {//parent process
//    wait(&rv);
//  }
//  else {//child process  

//char** args = new char*[2];
//args[0] = new char[100];
//args[1] = new char[100]; 
// strcpy(args[0],"touch");
// strcpy(args[1],"/home/gleb/Dropbox/gui_analysis_15_04_12/zzz");
// strcpy(args[1],"-all");
 
// ss.str("");
// ss << "/home/gleb";
 
 //strcpy(args[2],"/home/gleb"); 
 
 
/* ss.str("");
 ss << _out_dir << "/out.tar";
 
 strcpy(args[2],ss.str().c_str());
 
 ss.str("");
 ss << _out_dir << "/att_length_max.png";
 
 strcpy(args[3],ss.str().c_str()); 
 
 
 ss.str("");
 ss << _out_dir << "/avrg_resol.png";
 
 strcpy(args[4],ss.str().c_str());
 
 
 ss.str("");
 ss << _out_dir << "/c_eff.png";
 
 strcpy(args[5],ss.str().c_str());
 
 strcpy(args[6],NULL);
 
 
 

  
  
  */
    
//  execvp(args[0],args);  
    
//};


  pid_t pid = fork(); 
  Int_t rv;
  if(pid) {//parent process
    wait(&rv);
  }
  else {//child process 

  char *p[20] = { NULL };
  char pn[5] = "tar";
  char pa1[5];
  char pa2[150];
  char pa3[150];
  char pa4[150];
  char pa5[150];
  char pa6[150];
  char pa7[150];
  char pa8[150];
  char pa9[150];  
  char pa10[150];
  char pa11[150];  
  char pa12[150]; 
  char pa13[150];
      
  int retval;

     

    p[0] = pn;
    
    if (setnum_inp ==0) {
    chdir(_out_dir.c_str());
    };

    ss.str("");
    ss << "cfP";
    strcpy(pa1,ss.str().c_str());
    p[1] = pa1;

    string str;
    if (setnum_inp ==0) {
    str=_out_file;
    } else {
    str=outfile_inp;
    };
    
    ss.str("");
    str.replace(0,str.rfind("/")+1,"");
    ss << str.replace(str.size()-4,4,"tar");
    strcpy(pa2,ss.str().c_str());
    p[2] = pa2;     


    ss.str("");
    ss << "att_length_max.png";
    strcpy(pa3,ss.str().c_str());
    p[3] = pa3;
    
    
     
    ss.str("");
    ss << "avrg_resol.png";
    strcpy(pa4,ss.str().c_str());
    p[4] = pa4;
    
    
    
    ss.str("");
    ss << "c_eff.png";
    strcpy(pa5,ss.str().c_str());
    p[5] = pa5;
        
    
    
    ss.str("");
    ss << "resol_cont.png";
    strcpy(pa6,ss.str().c_str());
    p[6] = pa6;
            
    
    
    ss.str("");
    ss << "resol.png";
    strcpy(pa7,ss.str().c_str());
    p[7] = pa7;    
    
    
    ss.str("");
    ss << "tdcdiff1vstdcdiff6.png";
    strcpy(pa8,ss.str().c_str());
    p[8] = pa8;     
    
    
    ss.str("");
    ss << "tdc_diff.png";
    strcpy(pa9,ss.str().c_str());
    p[9] = pa9;  
    
    
    
    ss.str("");
    ss << "tw_params.png";
    strcpy(pa10,ss.str().c_str());
    p[10] = pa10;   
    



    ss.str("");
    ss << "att_length.dat";
    strcpy(pa11,ss.str().c_str());
    p[11] = pa11;     


    ss.str("");
    if (setnum_inp ==0) {
    str=_out_file;
    ss << str.replace(0,str.rfind("/")+1,"");
    } else {
    str=outfile_inp;
    ss << str;
    };
    strcpy(pa12,ss.str().c_str());
    p[12] = pa12;        
     
    if ( setnum_inp ==0) {   
    if (inc_langau->GetState() == kButtonDown) {
    ss.str("");
    ss << "att_length.png";
    strcpy(pa13,ss.str().c_str());
    p[13] = pa13;      
    };
    } else {
    if (langau_inp) {
    ss.str("");
    ss << "att_length.png";
    strcpy(pa13,ss.str().c_str());
    p[13] = pa13; 
    };
    };    
    
    
//    str=_out_file;
//    str.replace(0,str.rfind("/")+1,"");
//    cout <<  "\n" << str.replace(str.size()-4,4,"tar") << "\n";

    execvp(p[0], p);
//     printf("%d" "\n", retval); 

};



  pid_t pid2 = fork(); 
  Int_t rv1;
  if(pid2) {//parent process
    wait(&rv1);
  }
  else {//child process 

  char *p[20] = { NULL };
  char pn[5] = "gzip";
  char pa1[5];
  char pa2[150];

  
      
  int retval;
  
  if (setnum_inp ==0) {
  chdir(_out_dir.c_str());
  };   

    p[0] = pn;


    ss.str("");
    ss << "-9f";
    strcpy(pa1,ss.str().c_str());
    p[1] = pa1;
        
  string str;
  if (setnum_inp ==0) {	
        str=_out_file;
	} else {
	str=outfile_inp;	
	};
    ss.str("");
    str.replace(0,str.rfind("/")+1,"");
    ss << str.replace(str.size()-4,4,"tar");
    strcpy(pa2,ss.str().c_str());
    p[2] = pa2;
    
    
    execvp(p[0], p);
    
    };
    
   
    if (setnum_inp ==0) {	   
    chdir(_out_dir.c_str());
    };
   
    remove("att_length_max.png");
    remove("att_length.dat");
    remove("avrg_resol.png");
    remove("resol_cont.png");    
    remove("resol.png");
    remove("c_eff.png");    
    remove("tdcdiff1vstdcdiff6.png");    
    remove("tdc_diff.png");    
    remove("tw_params.png");    
    if (setnum_inp ==0) {
    if (inc_langau->GetState() == kButtonDown) {    
    remove("att_length.png");
    };
    } else {
    if (langau_inp) {
    remove("att_length.png");
    };
    };
    
    if (setnum_inp ==0) {
      fMain->Resize(fMain->GetDefaultSize());	 
	
	

	
	

      exit->ChangeBackground(0xff0000);
      exit->SetForegroundColor(0xf8f8ff);
      exit->Resize(40,exit->GetDefaultHeight());
      exit->SetText("Done");
      } else {
       return;
      };	
      
//      exit->SetForegroundColor(0xff0000);

/*	TCanvas *c1 = new TCanvas("tw param fit", "tw param fit", 700, 700); 
	c1->cd();
        lambda5_1->Draw();   
        c1->Update();
 
 */    
      
}





void MyMainFrame::OpenFile() {
   static TString dir(".");
 
   const char * k_xml_file_extensions[] =
   {

    "dat files",     "*.root",
    "All files",     "*",
     0,               0
   };
     TGFileInfo fi;

    fi.fFileTypes = k_xml_file_extensions;
    fi.fIniDir    = StrDup( dir.Data() );
//    fi.fMultipleSelection = 1;

    
//    nfiles = 0;
  
 TGFileDialog *jopafile =  new TGFileDialog(gClient->GetRoot(),fMain , kFDOpen, &fi);
 
 
//     if (fi.fMultipleSelection && fi.fFileNamesList) {
//   TObjString *el;
//   TIter next(fi.fFileNamesList);
//     
//   while ((el = (TObjString *) next())) {
//    
//    
//       _current_file = el->GetString();
//      nfiles++;
//   
     
//      new TFile(el->GetString(), "update");
//   }
      
    ostringstream cmd;

      
//      short i;
    if( fi.fFilename ) {       
//       for (i=0; i<nfiles; i++) {
       
       _current_file = string( fi.fFilename );
       cmd << _current_file << "\n";
       
//       };     
      
      if (file_status) {
      go->SetState(kButtonUp);
      go->Released(); } else {
      file_status = 1;
      };
      
      input_file->SetState(kButtonDisabled);
      hframe->RemoveFrame(input_file);
      hframe->RemoveFrame(output_file);
      hframe->RemoveFrame(labelqout);
      hframe->RemoveFrame(label_ref_pmt);
      hframe->RemoveFrame(ref_pmt);
      hframe->RemoveFrame(estat);
      hframe->RemoveFrame(inc_langau);      
      hframe->RemoveFrame(fCombo); 
      hframe->RemoveFrame(labellength);  
      hframe->RemoveFrame(fNumPoints); 
      hframe->RemoveFrame(label_n_points);            
           
      labelq = new TGLabel(hframe, cmd.str().c_str());
      labelq->SetForegroundColor(0xff0000);
      labelq->SetTextColor(0xff0000);
      hframe->AddFrame(labelq, new TGLayoutHints(kLHintsLeft, 90,250-5*_current_file.size(),313,0));
      
 //     fMain->AddFrame(hframe, new TGLayoutHints(kLHintsCenterX,0,0,0,0));
    
      
    
    // Set a name to the main frame
 //   fMain->SetWindowName("jopa");
    // Map all subwindows of main frame
    fMain->MapSubwindows();
    // Initialize the layout algorithm
   fMain->Resize(fMain->GetDefaultSize());
    // Map main frame
    fMain->MapWindow();      
      }   
    
      };   
         

void MyMainFrame::OutFile() {

   static TString dir(".");
	char* nomer = new char[500];    
// sprintf(nomer,"bar_%i_npoints_%i.root",fCombo->GetSelected(),int(n_points->GetNumber()));
if ( (fNumPoints->GetSelected()) != 1 ) {
sprintf(nomer,"bar_%i_npoints_%i.root",fCombo->GetSelected(),fNumPoints->GetSelected()+3);
} else {
sprintf(nomer,"bar_%i_npoints_auto.root",fCombo->GetSelected());
};	
  cout << "File=" << nomer << "\n";
   TString out(nomer);   
    
   delete[] nomer;

   const char * k_xml_file_extensions[] =
   {

    "dat files",     "*.root",
    "All files",     "*",
     0,               0
   };
   

   
     TGFileInfo fi;

    fi.fFileTypes = k_xml_file_extensions;
    fi.fIniDir    = StrDup( path.Data() );
    fi.fFilename  = StrDup( out.Data() );


    
TGFileDialog *kuku = new TGFileDialog(gClient->GetRoot(),fMain , kFDOpen, &fi);

    
    if( fi.fFilename ) {
    
  
      _out_file = string( fi.fFilename );
      _out_dir = string( fi.fIniDir );
     
      ostringstream cmd;
      cmd << _out_file.c_str();

      
      if (file_status) {
      go->SetState(kButtonUp);
      go->Released(); } else {
      file_status = 1;
      };
      
      output_file->SetState(kButtonDisabled);
      hframe->RemoveFrame(input_file);
      hframe->RemoveFrame(output_file);
      hframe->RemoveFrame(labelq); 
      hframe->RemoveFrame(label_ref_pmt);
      hframe->RemoveFrame(ref_pmt);
      hframe->RemoveFrame(estat); 
      hframe->RemoveFrame(inc_langau);       
      hframe->RemoveFrame(fCombo); 
      hframe->RemoveFrame(labellength);   
      hframe->RemoveFrame(fNumPoints); 
      hframe->RemoveFrame(label_n_points);       
            
      labelqout = new TGLabel(hframe, cmd.str().c_str());
      labelqout->SetForegroundColor(0xff0000);
      labelqout->SetTextColor(0xff0000);
      hframe->AddFrame(labelqout, new TGLayoutHints(kLHintsLeft, 90,250-5*_out_file.size(),373,0));
      
 //     fMain->AddFrame(hframe, new TGLayoutHints(kLHintsCenterX,0,0,0,0));
    
      
    
    // Set a name to the main frame
 //   fMain->SetWindowName("jopa");
    // Map all subwindows of main frame
    fMain->MapSubwindows();
    // Initialize the layout algorithm
    fMain->Resize(fMain->GetDefaultSize());
    // Map main frame
    fMain->MapWindow();      
          }
    
      }; 
   
   Double_t MyMainFrame::GetADCoffsetcut(TH1 *h) {
   short i,j,a,ib;
   a = h->GetNbinsX();
   Double_t b,bmax,ymax;
   ymax = h->GetBinContent(h->GetMaximumBin());
   TH1D *hmin = new TH1D("min","min",a-h->GetMaximumBin(),h->GetBinLowEdge(h->GetMaximumBin()),301);
   for (i=h->GetMaximumBin(); i<=a; i++)
{
hmin->Fill(h->GetBinCenter(i),fabs(h->GetBinContent(i)-ymax/2.));

}

    b=hmin->GetBinCenter(hmin->GetMinimumBin());
    bmax=h->GetBinCenter(h->GetMaximumBin());
    hmin->Delete();
//    hmin->Draw();
//    pause();
    return bmax+2.*(b-bmax);
 };   
 
 
    Double_t MyMainFrame::GetTDCrightcut(TH1 *h) {
   Int_t i,j,a,ib;
   a = h->GetNbinsX();
   Double_t b,bmax,ymax;
   ymax = h->GetMaximumBin();
   ymax = h->GetBinContent(ymax);
   TH1D *hmin = new TH1D("min","min",a-h->GetMaximumBin(),h->GetBinLowEdge(h->GetMaximumBin()),h->GetBinLowEdge(a));

   for (i=h->GetMaximumBin(); i<=a; i++)
{
hmin->Fill(h->GetBinCenter(i),Double_t(fabs(h->GetBinContent(i)-ymax/2.)));

}

    b=hmin->GetBinCenter(hmin->GetMinimumBin());
//    bmax=h->GetBinCenter(h->GetMaximumBin());
    hmin->Delete();
//    hmin->Draw();
//    pause();
    return b;
 };   
 
    Double_t MyMainFrame::GetTDCleftcut(TH1 *h) {
   Int_t i,j,a,ib;
   a = h->GetNbinsX();
   Double_t b,bmax,ymax;
   ymax = h->GetMaximumBin();
   ymax = h->GetBinContent(ymax);
   TH1D *hmin = new TH1D("min","min",h->GetMaximumBin(),h->GetBinLowEdge(0),h->GetBinLowEdge(h->GetMaximumBin()));

   for (i=0; i<=h->GetMaximumBin(); i++)
{
hmin->Fill(h->GetBinCenter(i), Double_t(fabs(h->GetBinContent(i)-ymax/2.)));

}

    b=hmin->GetBinCenter(hmin->GetMinimumBin());
//    bmax=h->GetBinCenter(h->GetMaximumBin());
    hmin->Delete();
//    hmin->Draw();
//    pause();
    return b;
 };    
 
 
    void MyMainFrame::t20tot21() { 
    

    ostringstream adc_num;
    ostringstream tdc_num;
    ostringstream ref_tdc;
    
    if (setnum_inp != 0) {
    ref_tdc << "tdc5"; } else {
    ref_tdc << "tdc" << ref_pmt->GetNumber();
    };

    
 Double_t * adc_offset;
 adc_offset = new Double_t [12];
 Double_t * adc_cut;
 adc_cut = new Double_t [12]; 

 int i;
 short j;
 
TH1I *hist_adc_off[12]; 

   for (j=0; j<12; j++) {
   
   adc_num << "adc" << j+1;
hist_adc_off[j] = new TH1I(adc_num.str().c_str(),adc_num.str().c_str(),150, 1., 301.);
 adc_num.str("");
  };
 
 TFile *finp;

if (setnum_inp == 0) {
 go->SetState(kButtonDisabled);

 
  finp = new TFile(_current_file.c_str()); 
  } else {
  finp = new TFile(inpfile_inp.c_str()); 
  };
    
  TTree *t20 = (TTree*)finp->Get("t20");
  TBranch *eventn = t20->GetBranch("eventn");
//  TLeaf *adc1 = eventn->GetLeaf("adc1");



  
  cout << "N enteries = " << eventn->GetEntries() << "\n";

  for (i=0; i<eventn->GetEntries(); i++) { 
 
    eventn->GetEntry(i); 
    
     
   for (j=0; j<12; j++) {
  adc_num << "adc" << j+1;
//  
//  adc[j] = eventn->GetLeaf(adc_num.str().c_str())->GetValue();

  hist_adc_off[j]->Fill(eventn->GetLeaf(adc_num.str().c_str())->GetValue(),1);
  adc_num.str("");
  };
  
//  hist_adc[3]->Fill(adc[3],1.);  
  

  
 
  
  };


   for (j=0; j<12; j++) {  
  
  adc_offset[j] = hist_adc_off[j]->GetBinCenter(hist_adc_off[j]->GetMaximumBin());
  adc_cut[j] = GetADCoffsetcut(hist_adc_off[j]);
  
  };
  
  
  
  // Creating and filling new tree
  
  	t21 = new TTree("t21","Tree 21"); 
  t21->SetDirectory(0);
  
   typedef struct {
	Int_t adc1;
	Int_t adc2;
	Int_t adc3;
	Int_t adc4;
	Int_t adc5;
	Int_t adc6;
	Int_t adc7;
	Int_t adc8;
	Int_t adc9;
	Int_t adc10;
	Int_t adc11;
	Int_t adc12;				
	Int_t tdc1;
	Int_t tdc2;
	Int_t tdc3;
	Int_t tdc4;
	Int_t tdc5;
	Int_t tdc6;
	Int_t tdc7;
	Int_t tdc8;
	Int_t tdc9;
	Int_t tdc10;
	Int_t tdc11;
	Int_t tdc12;
	Int_t tdc13;
	Int_t tdc14;
	Int_t tdc15;
	Int_t tdc16;					
	} EVENT;
    
    static EVENT event;   
  
t21->Branch("event",&event,"adc1/I:adc2/I:adc3/I:adc4/I:adc5/I:adc6/I:adc7/I:adc8/I:adc9/I:adc10/I:adc11/I:adc12/I:tdc1/I:tdc2/I:tdc3/I:tdc4/I:tdc5/I:tdc6/I:tdc7/I:tdc8/I:tdc9/I:tdc10/I:tdc11/I:tdc12/I:tdc13/I:tdc14/I:tdc15/I:tdc16/I"); 


// Loop over old tree 
  Bool_t adc_cut_switch,tdc_cut_switch;
  for (i=0; i<eventn->GetEntries(); i++) { 
  adc_cut_switch = 1;
  tdc_cut_switch = 1;  
  
  eventn->GetEntry(i); 
    
     
   for (j=0; j<12; j++) { 
   adc_num << "adc" << j+1;
   tdc_num << "tdc" << j+1;

  if (eventn->GetLeaf(adc_num.str().c_str())->GetValue() <= adc_cut[j]) {
  adc_cut_switch = 0; 
  };
  if (fabs(eventn->GetLeaf(tdc_num.str().c_str())->GetValue()-eventn->GetLeaf(ref_tdc.str().c_str())->GetValue()) > 100000) {
  tdc_cut_switch = 0;
  };
  adc_num.str("");
  tdc_num.str("");  
  };
  
  if (fabs(eventn->GetLeaf("tdc15")->GetValue()-eventn->GetLeaf(ref_tdc.str().c_str())->GetValue()) > 100000) {
  tdc_cut_switch = 0;
  };  
  

   if (adc_cut_switch && tdc_cut_switch) {
   for (j=0; j<12; j++) {
   adc_num << "adc" << j+1;
   tdc_num << "tdc" << j+1;
    
                switch ( j ) {
               case 0 :
	       event.adc1 = eventn->GetLeaf(adc_num.str().c_str())->GetValue()-adc_offset[j];
	       event.tdc1 = eventn->GetLeaf(tdc_num.str().c_str())->GetValue()-eventn->GetLeaf(ref_tdc.str().c_str())->GetValue();
	       break;
               case 1 :
	       event.adc2 = eventn->GetLeaf(adc_num.str().c_str())->GetValue()-adc_offset[j];
	       event.tdc2 = eventn->GetLeaf(tdc_num.str().c_str())->GetValue()-eventn->GetLeaf(ref_tdc.str().c_str())->GetValue();
	       break;
               case 2 :
	       event.adc3 = eventn->GetLeaf(adc_num.str().c_str())->GetValue()-adc_offset[j];
	       event.tdc3 = eventn->GetLeaf(tdc_num.str().c_str())->GetValue()-eventn->GetLeaf(ref_tdc.str().c_str())->GetValue();
	       break;
               case 3 :
	       event.adc4 = eventn->GetLeaf(adc_num.str().c_str())->GetValue()-adc_offset[j];
	       event.tdc4 = eventn->GetLeaf(tdc_num.str().c_str())->GetValue()-eventn->GetLeaf(ref_tdc.str().c_str())->GetValue();
	       break;
               case 4 :
	       event.adc5 = eventn->GetLeaf(adc_num.str().c_str())->GetValue()-adc_offset[j];
	       event.tdc5 = eventn->GetLeaf(tdc_num.str().c_str())->GetValue()-eventn->GetLeaf(ref_tdc.str().c_str())->GetValue();
	       break;
               case 5 :
	       event.adc6 = eventn->GetLeaf(adc_num.str().c_str())->GetValue()-adc_offset[j];
	       event.tdc6 = eventn->GetLeaf(tdc_num.str().c_str())->GetValue()-eventn->GetLeaf(ref_tdc.str().c_str())->GetValue();
	       break;
               case 6 :
	       event.adc7 = eventn->GetLeaf(adc_num.str().c_str())->GetValue()-adc_offset[j];
	       event.tdc7 = eventn->GetLeaf(tdc_num.str().c_str())->GetValue()-eventn->GetLeaf(ref_tdc.str().c_str())->GetValue();
	       break;
               case 7 :
	       event.adc8 = eventn->GetLeaf(adc_num.str().c_str())->GetValue()-adc_offset[j];
	       event.tdc8 = eventn->GetLeaf(tdc_num.str().c_str())->GetValue()-eventn->GetLeaf(ref_tdc.str().c_str())->GetValue();
	       break;
               case 8 :
	       event.adc9 = eventn->GetLeaf(adc_num.str().c_str())->GetValue()-adc_offset[j];
	       event.tdc9 = eventn->GetLeaf(tdc_num.str().c_str())->GetValue()-eventn->GetLeaf(ref_tdc.str().c_str())->GetValue();
	       break;
               case 9 :
	       event.adc10 = eventn->GetLeaf(adc_num.str().c_str())->GetValue()-adc_offset[j];
	       event.tdc10 = eventn->GetLeaf(tdc_num.str().c_str())->GetValue()-eventn->GetLeaf(ref_tdc.str().c_str())->GetValue();
	       break;
               case 10 :
	       event.adc11 = eventn->GetLeaf(adc_num.str().c_str())->GetValue()-adc_offset[j];
	       event.tdc11 = eventn->GetLeaf(tdc_num.str().c_str())->GetValue()-eventn->GetLeaf(ref_tdc.str().c_str())->GetValue();
	       break;
               case 11 :
	       event.adc12 = eventn->GetLeaf(adc_num.str().c_str())->GetValue()-adc_offset[j];
	       event.tdc12 = eventn->GetLeaf(tdc_num.str().c_str())->GetValue()-eventn->GetLeaf(ref_tdc.str().c_str())->GetValue();
	       break;	       	       	       	       
	       };   
	       adc_num.str(""); 
	       tdc_num.str("");
   };
   event.tdc13 = eventn->GetLeaf("tdc13")->GetValue()-eventn->GetLeaf(ref_tdc.str().c_str())->GetValue();
   event.tdc14 = eventn->GetLeaf("tdc14")->GetValue()-eventn->GetLeaf(ref_tdc.str().c_str())->GetValue();
   event.tdc15 = eventn->GetLeaf("tdc15")->GetValue()-eventn->GetLeaf(ref_tdc.str().c_str())->GetValue();
   event.tdc16 = eventn->GetLeaf("tdc16")->GetValue()-eventn->GetLeaf(ref_tdc.str().c_str())->GetValue();
    t21->Fill();
   
   };
 
 
   
  };
  
  
  
  
  
//  eventn->Delete();
  t20->Delete();
  TH1 *double_rate = (TH1*)finp->Get("double_rate");

//  t20->Delete();
     TFile *outFile;
     
     if (setnum_inp == 0) {
     outFile = new TFile(_out_file.c_str(),"recreate");
     } else {
     outFile = new TFile(outfile_inp.c_str(),"recreate");
     };
     
/*     if (estat->GetState() == kButtonDown) {
     t21->Write("", TObject::kOverwrite);
     };
*/      
     outFile->mkdir("full_bar");
     TDirectory *dir =outFile->GetDirectory("full_bar");
     
    double_rate->SetDirectory(dir);
    outFile->Write();
     
 	outFile->Close();
      finp->Close();
       
           
    delete [] adc_offset;
 
    delete [] adc_cut;  
    for (j=0; j<12; j++) {
    hist_adc_off[j]->Delete();
    };
    
    
    
    };

    
     

TH1*  MyMainFrame::Smooth_fun(TH1 *h, Double_t bin_num) {
Int_t i,j,a;
a = h->GetNbinsX();



TH1* h1 = new TH1D("qqq","qqq",a,h->GetBinLowEdge(1),h->GetBinLowEdge(a)+	h->GetBinWidth(a));
Double_t y,width;
width=h->GetBinWidth(a);


for (i=1; i<=a-bin_num; i++)
{
y=0;
for (j=0; j<=bin_num-1; j++)
{
y=y+h->GetBinContent(i+j)/bin_num;

};
h1->Fill(h->GetBinLowEdge(1)+(i-1)*width+width*bin_num/2.,y);
 
};
return h1;
}; 


    Double_t MyMainFrame::myFunction(TH1 *h) {
   Short_t i,j,a,ib;
   a = h->GetNbinsX();
   Double_t y[50000],b,b1;
   for (i=1; i<=a-5; i++)
{
y[i]=h->GetBinContent(i);
if (i % 50 == 0) {
     if (b1 > b) {
          b=b1;
	  ib=i-25;

         }
          b1=0;
   }
else {
    b1=b1+y[i];
    }

}

Double_t yleft=fabs(y[1]-b/80.);
Double_t ileft=0;
for (i=1; i<=ib; i++)
{
if ((fabs(y[i]-b/80.))<yleft) {
yleft=fabs(y[i]-b/80.);
ileft=i;
}
}

Double_t xleft=h->GetXaxis()->GetBinCenter(ileft);

Double_t yright=fabs(y[ib]-b/80.);
Double_t iright=0;
for (i=ib; i<=a; i++)
{

if ((fabs(y[i]-b/80.))<yright) {
yright=fabs(y[i]-b/80.);
iright=i;

}
}
Double_t xright=h->GetXaxis()->GetBinCenter(iright);
Double_t xmed=h->GetXaxis()->GetBinCenter(ib);
Double_t ymax=h->GetYaxis()->GetBinCenter(ib);

    return xmed-0.7*(xright-xleft);
 };




Double_t MyMainFrame::landauconvgauss(TH1I *h, Double_t &err) {


//        gROOT->ProcessLine( "gErrorIgnoreLevel = 3; " );
        
//	gSystem->Load("libMinuit");        
//	gSystem->Load("libRooFit");	
//        using namespace RooFit;
	
	
	RooMsgService::instance().getStream(1).removeTopic(Minimization);
    
	RooMsgService::instance().setGlobalKillBelow(RooFit::ERROR); 
	
	RooRealVar x("x","x",0,4096) ;
        TH1 *qqq1 = Smooth_fun(h,30);
        Double_t Maximum = qqq1->GetBinCenter(qqq1->GetMaximumBin());
	Double_t leftcut = myFunction(qqq1);
	qqq1->Delete();	
	
	//set fitting range of fitting parameters
//	TH1I* h = (TH1I*)gROOT->FindObject("adc1point1");

	RooRealVar meanl("meanl","mean of Landau",Maximum,leftcut,Maximum+1.*(Maximum-leftcut));
	RooRealVar sigmal("sigmal","sigma of Landau",60.,0.,2000.);
	RooLandau landau("landau","landau",x,meanl,sigmal);
	RooRealVar meang("meang","mean of Gaussian",0);
	RooRealVar sigmag("sigmag","sigma of Gaussian",80.,30.,700.);
	RooGaussian gauss("gauss","gauss",x,meang,sigmag);
	//Landau convolute gauss fitting
	RooNumConvPdf model("model","model",x,landau,gauss);
 	model.setConvolutionWindow(meang,sigmag,1);

//	TH1I* h = (TH1I*)gROOT->FindObject("adc1point1");
	RooDataHist* data = new RooDataHist("data","ADC BR, Center +/- 10",x,h);
//	RooBinning bins(400,0,4096);
	
//	RooPlot* frame = x.frame() ;
//	data.plotOn(frame,Binning(bins));
	//data.statOn(frame);
//	RooFitResult* fitResult = model.fitTo(*data,Range(920.412,4000),Verbose(0),PrintLevel(-1),Warnings(0),PrintEvalErrors(-1));
        RooFitResult* fitResult = model.fitTo(*data,Range(leftcut,Maximum+1.*(Maximum-leftcut)),Save(1),Verbose(0),PrintLevel(-1),PrintEvalErrors(-1));
//         fitResult->Print("v");

//	model.plotOn(frame);
//        model.paramOn(frame);
//	landau.plotOn(frame,Range(722.46,4000),LineColor(kRed),LineStyle(kDashed)) ;
	
//	TCanvas c1("c1","ADC Fit Example");
//	c1->cd();
//	frame->SetTitle("L(x)G Fit of Position-restricted ADC Values");
//	frame->Draw() ; 
	RooBinning hbins(4096,-.5,4096.5);
 	TH1F* myHist = (TH1F*)model.createHistogram("myHist",x,Binning(hbins));
  TF1* f1 = model.asTF(RooArgList(x), RooArgList(meang,meanl,sigmag,sigmal));
  Double_t xMax = f1->GetMaximumX();

  myHist->Delete();
  Double_t meanl_e = meanl.getError();
  Double_t sigmag_e = sigmag.getError();
  Double_t sigmal_e = sigmal.getError();
  Double_t meanl2 = meanl.getVal();
  Double_t sigmag2 = sigmag.getVal();
  Double_t sigmal2 = sigmal.getVal();  
  Double_t meang2 = meang.getVal();  

// findMinMax(f1,meanl,meanl_error,sigmag,sigmag_error,sigmal,sigmal_error);  
 
        Short_t i,j,k;
 
 	Double_t x1[3];
	x1[0] = meanl2 - meanl_e;
	x1[1] = meanl2;
	x1[2] = meanl2 + meanl_e;
	Double_t y[3];
	y[0] = sigmag2 - sigmag_e;
	y[1] = sigmag2;
	y[2] = sigmag2 + sigmag_e;
	Double_t z[3];
	z[0] = sigmal2 - sigmal_e;
	z[1] = sigmal2;
	z[2] = sigmal2 + sigmal_e;
	
	f1->SetParameters(meang2, x1[0], y[0], z[0]);
	Double_t minMax = f1->GetMaximumX();
	f1->SetParameters(meang2, x1[0], y[0], z[0]);
	Double_t maxMax = f1->GetMaximumX();
	Double_t currentMax = 0;
	
	for(i = 0; i < 3; i++) {
		for(j = 0; j < 3; j++) {
			for(k = 0; k < 3; k++) {
			        f1->SetParameters(meang2, x1[i], y[j], z[k]);
				currentMax = f1->GetMaximumX();
				if (currentMax < minMax) {
					minMax = currentMax;
				}
				if (currentMax > maxMax) {
					maxMax = currentMax;
				}
			}
		}
	}
	
      err = maxMax-minMax;
      
      

 
 
 
 
 
 
 
 

  return xMax;
  
  


};















    void MyMainFrame::MainFrame() {
    // Clean up used widgets: frames, buttons, layouthints
    fMain->Cleanup();
    delete fMain;
}
