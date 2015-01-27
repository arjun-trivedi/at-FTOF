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
#include "TH2F.h"
#include "TH3F.h"
#include "TText.h"
#include "TStyle.h"
#include "TObject.h"
#include "TSystem.h"
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
#include "VM_VmeData.h"
#include "VM_V1x90nData.h"
#include "VM_V792nData.h"


 using namespace std;    
 
    void MyMainFrame::MainFrame(const TGWindow *p,UInt_t w,UInt_t h) {
    
    
    TString progpath(gSystem->pwd());
    path = progpath;


    // Create a main frame
    fMain = new TGMainFrame(p,w,h,kHorizontalFrame);
    fMain->SetWMSize(800,440);
    // Create canvas widget
   // fEcanvas = new TRootEmbeddedCanvas("Ecanvas",fMain,200,200);
   // fMain->AddFrame(fEcanvas, new TGLayoutHints(kLHintsExpandX| kLHintsExpandY,10,10,10,1));
    // Create a horizontal frame widget with buttons
    hframe = new TGHorizontalFrame(fMain,300,200);

     TGFont *font = gClient->GetFontPool()->GetFont("helvetica", -20, kFontWeightNormal, kFontSlantRoman);

     
     
    ostringstream out;
    out<< "TDC channels";
    TGLabel *label_tdcorder = new TGLabel(hframe, "qqqqqqqqqqqqqqqqqqqq");

      label_tdcorder->SetForegroundColor(0xff0000);
      label_tdcorder->SetTextColor(0xff0000);
      label_tdcorder->SetTextFont(font);
 
     label_tdcorder->SetText(out.str().c_str());    
     label_tdcorder->Move(300,5);  
    out.str( std::string() );    
    
    

    out<< "ADC channels";
    TGLabel *label_adcorder = new TGLabel(hframe, "qqqqqqqqqqqqqqqqqqqq");

      label_adcorder->SetForegroundColor(0xff0000);
      label_adcorder->SetTextColor(0xff0000);
      label_adcorder->SetTextFont(font);
 
     label_adcorder->SetText(out.str().c_str());    
     label_adcorder->Move(300,155);  
    out.str( std::string() );   
    
           
    
    
    go = new TGTextButton(hframe,"&Go");
    go->Connect("Clicked()","MyMainFrame",this,"DoDraw()");
    hframe->AddFrame(go, new TGLayoutHints(kLHintsRight,-430,50,410,0));
    exit = new TGTextButton(hframe,"&Exit",
    "gApplication->Terminate(0)");    
    hframe->AddFrame(exit, new TGLayoutHints(kLHintsRight,-760,375,410,0));
    go->SetState(kButtonDisabled);
    //TGVerticalFrame *controls = new TGVerticalFrame(fMain,400,400);
    //controls->AddFrame(controls, new TGLayoutHints(kLHintsRight | kLHintsExpandY, 
//                                        5, 5, 5, 5));
//    TGGroupFrame *margins = new TGGroupFrame(hframe, "TDCs");
//    margins->SetTitlePos(TGGroupFrame::kCenter);



     TGFont *font_tdc = gClient->GetFontPool()->GetFont("helvetica", -12, kFontWeightNormal, kFontSlantRoman);

    TGLabel *label[16];
    TGNumberFormat::ELimit lim;
    short i;
    
    tdc_ch[10] = new TGNumberEntry(hframe,13);
    tdc_ch[8] = new TGNumberEntry(hframe,12);    
    tdc_ch[6] = new TGNumberEntry(hframe,11);
    tdc_ch[4] = new TGNumberEntry(hframe,10);    
    tdc_ch[2] = new TGNumberEntry(hframe,9); 
    tdc_ch[0] = new TGNumberEntry(hframe,8);     
    
    tdc_ch[11] = new TGNumberEntry(hframe,6);
    tdc_ch[9] = new TGNumberEntry(hframe,5);    
    tdc_ch[7] = new TGNumberEntry(hframe,4);
    tdc_ch[5] = new TGNumberEntry(hframe,3);    
    tdc_ch[3] = new TGNumberEntry(hframe,2); 
    tdc_ch[1] = new TGNumberEntry(hframe,1); 
    
    tdc_ch[12] = new TGNumberEntry(hframe,7);    
    tdc_ch[13] = new TGNumberEntry(hframe,15);          
    tdc_ch[14] = new TGNumberEntry(hframe,15);         
    tdc_ch[15] = new TGNumberEntry(hframe,0);    
    
    for (i=0; i<=15; i++) {
   

            
        
    lim = TGNumberFormat::kNELLimitMinMax;
    tdc_ch[i]->SetLimits(lim,0,15);
    tdc_ch[i]->SetLimitValues(0,15);
    tdc_ch[i]->SetFormat(TGNumberFormat::kNESInteger,TGNumberFormat::kNEANonNegative);
 //   hframe->AddFrame(fGEnergy, new TGLayoutHints(kLHintsCenterX,15,5,13,4));
 
    ostringstream out;
    if ( i < 10 ) {
    out<< "PMT0" << i+1;} else {
    out<< "PMT" << i+1;
    };
    label[i] = new TGLabel(hframe, out.str().c_str());
    label[i]->SetTextFont(font_tdc);
    
    if (i % 2 == 0) {
    hframe->AddFrame(tdc_ch[i], new TGLayoutHints(kLHintsLeft | kLHintsTop,15,15,50,0));
    hframe->AddFrame(label[i], new TGLayoutHints(kLHintsLeft, -71,22,30,0));
    } else {
    hframe->AddFrame(tdc_ch[i], new TGLayoutHints(kLHintsLeft | kLHintsTop,-63.5,61.2,105,0));
    hframe->AddFrame(label[i], new TGLayoutHints(kLHintsLeft, -115,22,85,0));    
    };    
    

    };
    
     
    
       
     TGLabel *label_adc[16];


    for (i=0; i<=15; i++) {

     adc_ch[i] = new TGNumberEntry(hframe,i+1);
     
     if ( i == 15) {
     adc_ch[i]->SetNumber(8);
    };
      if ( i == 7) {
     adc_ch[i]->SetNumber(0);
    };   
    
    lim = TGNumberFormat::kNELLimitMinMax;
    adc_ch[i]->SetLimits(lim,0,15);
    adc_ch[i]->SetLimitValues(0,15);
    adc_ch[i]->SetFormat(TGNumberFormat::kNESInteger,TGNumberFormat::kNEANonNegative);
 //   hframe->AddFrame(fGEnergy, new TGLayoutHints(kLHintsCenterX,15,5,13,4));
 
    ostringstream out;
    if ( i < 10 ) {
    out<< "PMT0" << i+1;} else {
    out<< "PMT" << i+1;
    };
    label_adc[i] = new TGLabel(hframe, out.str().c_str());
    label_adc[i]->SetTextFont(font_tdc);
    
    if (i % 2 == 0) {
    hframe->AddFrame(adc_ch[i], new TGLayoutHints(kLHintsLeft | kLHintsTop,-630.5,671,205,0));
    hframe->AddFrame(label_adc[i], new TGLayoutHints(kLHintsLeft, -730,671,185,0));
    } else {
    hframe->AddFrame(adc_ch[i], new TGLayoutHints(kLHintsLeft | kLHintsTop,-710.5,714,260,0));
    hframe->AddFrame(label_adc[i], new TGLayoutHints(kLHintsLeft, -770,670,240,0));    
    };    
    

    };   


    
    
  // a popup menu
  
    TGLayoutHints *fMenuBarLayout = new TGLayoutHints(kLHintsTop | kLHintsExpandX);
    TGLayoutHints *fMenuBarItemLayout = new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 4, 0, 0);
    TGLayoutHints *fMenuBarHelpLayout = new TGLayoutHints(kLHintsTop | kLHintsRight);
  //  TGPopupMenu *fMenuFile = new TGPopupMenu(gClient->GetRoot());


// adding menu entries

    


   
      file_status=0;
      
      input_file = new TGTextButton(hframe,"&Input_file");
    input_file ->Connect("Clicked()","MyMainFrame",this,"OpenFile()");
    hframe->AddFrame(input_file, new TGLayoutHints(kLHintsRight,-1350,1355,350,0));  
     
     
      output_file = new TGTextButton(hframe,"&Outut_file");
    output_file ->Connect("Clicked()","MyMainFrame",this,"OutFile()");
    hframe->AddFrame(output_file, new TGLayoutHints(kLHintsRight,-1285,1290,390,0)); 
    
    data_files = new TGTextButton(hframe,"&Data_files"); 
    data_files ->Connect("Clicked()","MyMainFrame",this,"Browse()");      
    hframe->AddFrame(data_files, new TGLayoutHints(kLHintsRight,-630,600,110,0));
          data_files->ChangeBackground(0x7cfc00);
//      data_files->SetForegroundColor(0x7cfc00);
//      data_files->Resize(40,80);
      data_files->SetText("Open data  \n files web page");	
    
         
        fHProg1 = new TGHProgressBar(hframe,TGProgressBar::kStandard,300);      
        fHProg1->Move(20,300);
	fHProg1->SetBarColor("blue");
	
	fHProg1->SetForegroundColor(0x00ff00);   

	
fMain->AddFrame(hframe, new TGLayoutHints(kLHintsCenterX,0,0,0,0));
    	


	
    // Set a name to the main frame
    fMain->SetWindowName("Data Converter");
    // Map all subwindows of main frame
    hframe->Move(500,0); 
    fMain->MapSubwindows();
    
    // Initialize the layout algorithm
  
   fMain->Resize(fMain->GetDefaultSize());
   
    // Map main frame
    fMain->MapWindow(); 



   
}

void MyMainFrame::DoDraw() {
    // Draws function graphics in randomly choosen interval
  //  TF1 *f1 = new TF1("f1","sin(x)/x",0,gRandom->Rndm()*10);
  //  f1->SetFillColor(19);
  //  f1->SetFillStyle(1);
 //   f1->SetLineWidth(3);
  //  f1->Draw();
 //   TCanvas *fCanvas = fEcanvas->GetCanvas();
 //   fCanvas->cd();
 //   fCanvas->Update();

 go->SetState(kButtonDisabled);
      
 

      
      int tdcnum = (Int_t)tdc_ch[0]->GetNumber();
      if (tdcnum >= 16) {
      tdc_ch[0]->SetNumber(15);
      };  
      int adcnum = (Int_t)adc_ch[0]->GetNumber();
      if (adcnum >= 16) {
      adc_ch[0]->SetNumber(15);
      };      
      short i;

    string line;

    size = 0;      
      // Start reading data
     ifstream size_f;   
 
       for (i=0; i<nfiles; i++) {
          
      size_f.open(_current_file[i].c_str()); 
    while (size_f.good()) { 
    size++;
    getline(size_f, line);
    };
    size_f.close();    
    };
    
    
    
	
    
// 	TROOT troot();
        TFile *outFile = new TFile(_out_file.c_str(),"recreate"); // output file
	TTree *t20 = new TTree("t20","Tree 20");      
	TH1F *double_rate = new TH1F("double_rate", "double_rate",16, 0.5, 16.5);           



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
	Int_t adc13;
	Int_t adc14;
	Int_t adc15;
	Int_t adc16;				
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
	} EVENTN;
    
    static EVENTN eventn;   
     int adc1,adc2,adc3,adc4,adc5,adc6,adc7,adc8,adc9,adc10,adc11,adc12,adc13,adc14,adc15,adc16,tdc1;

        

	
	 t20->Branch("eventn",&eventn,"adc1/I:adc2/I:adc3/I:adc4/I:adc5/I:adc6/I:adc7/I:adc8/I:adc9/I:adc10/I:adc11/I:adc12/I:adc13/I:adc14/I:adc15/I:adc16/I:tdc1/I:tdc2/I:tdc3/I:tdc4/I:tdc5/I:tdc6/I:tdc7/I:tdc8/I:tdc9/I:tdc10/I:tdc11/I:tdc12/I:tdc13/I:tdc14/I:tdc15/I:tdc16/I");
	
     int adc[16],tdc[16];  
     int adcchtmp,adcvaltmp; 
     int tdcchtmp,tdcvaltmp;       
	 
        
   char line_c[9];
   unsigned long val_ul;
   unsigned int buffersCounted_ui = 0;
   unsigned int badTdcs = 0;
   unsigned int tdcs = 0;
   unsigned long eventId = 0; 
   int tdccoin; 
   int rate2[16]; 

     ifstream input_f;

        short ii;
       for (ii=0; ii<nfiles; ii++) {
 
 
 
 

	       
          
      
      //Open data file
      input_f.open(_current_file[ii].c_str());
//      fMain->Resize(fMain->GetDefaultSize());


	

	
	

	
	
    while (input_f.good()) {  
    unsigned int tdcValsCounted_ui = 0;
      input_f >> line_c; 
      // fHProg1->Increment(69./float(size)); 
               
       val_ul = strtoul(line_c,NULL,16);

      
       

	
        while (input_f.good()) {
	
	
         input_f >> line_c;
	  // fHProg1->Increment(69./float(size)); 
         val_ul = strtoul(line_c,NULL,16);
       
             if ( VM_VmeData::isEventMarker(val_ul) ) {
            eventId++;
	     tdccoin = 0;
	                short jj;
	 	       for (jj=0; jj<=11; jj++) {
	       if (tdc[jj] > 0) {
	       tdccoin++;	       
	       };
	       };
	    
	    	       if (tdccoin == 12) {
	       t20->Fill();

               short kk;
	       for (kk=0; kk<=15;kk++) {
	       if (rate2[kk] == 1) {
	       double_rate->Fill(kk+1);
	       };
	       };	       
	       };
	    };
	    
	    
         if (VM_V792nData::isQdcHeader(val_ul)) {
            stringstream qdcPacket;
            qdcPacket << line_c << endl;
            //int eventCnt = GetQdcPacket(input_f, qdcPacket);
            GetQdcPacket(input_f, qdcPacket);
           
            qdcPacket >> line_c;       //bypass header
	     // fHProg1->Increment(69./float(size)); 
            qdcPacket >> line_c;       //get first measurement word
	     // fHProg1->Increment(69./float(size)); 
            val_ul = strtoul(line_c,NULL,16);
            while ( !(VM_V792nData::isQdcFooter(val_ul)) ) {

               adcchtmp = VM_V792nData::getChannelNum(val_ul);
	       adcvaltmp =  VM_V792nData::getValue(val_ul);
	       short hh;
	       for (hh=0; hh<=15; hh++) {
	       if ((Int_t)adc_ch[hh]->GetNumber() == adcchtmp) {
               switch ( hh ) {
               case 0 :
	       eventn.adc1 = adcvaltmp;
	       break;
               case 1 :
	       eventn.adc2 = adcvaltmp;
	       break;
               case 2 :
	       eventn.adc3 = adcvaltmp;
	       break;
               case 3 :
	       eventn.adc4 = adcvaltmp;
	       break;
               case 4 :
	       eventn.adc5 = adcvaltmp;
	       break;
               case 5 :
	       eventn.adc6 = adcvaltmp;
	       break;
               case 6 :
	       eventn.adc7 = adcvaltmp;
	       break;
               case 7 :
	       eventn.adc8 = adcvaltmp;
	       break;
               case 8 :
	       eventn.adc9 = adcvaltmp;
	       break;
               case 9 :
	       eventn.adc10 = adcvaltmp;
	       break;
               case 10 :
	       eventn.adc11 = adcvaltmp;
	       break;
               case 11 :
	       eventn.adc12 = adcvaltmp;
	       break;
               case 12 :
	       eventn.adc13 = adcvaltmp;
	       break;
               case 13 :
	       eventn.adc14 = adcvaltmp;
	       break;
               case 14 :
	       eventn.adc15 = adcvaltmp;
	       break;
               case 15 :
	       eventn.adc16 = adcvaltmp;
	       break;	       	       	       	       
	       };
       
	       };
	       };
               qdcPacket >> line_c;
               val_ul = strtoul(line_c,NULL,16);
	        // fHProg1->Increment(69./float(size)); 
            }
	    
	     
	    

         }
	 
	   
	 	
      
         if (VM_V1x90nData::isGlobalHeader(val_ul)) {
            tdcs++;
            stringstream tdcPacket;
            tdcPacket << line_c << endl;
            int wordCnt = GetTdcPacket(input_f, tdcPacket);


	      
            tdcValsCounted_ui++;
            
            tdcPacket >> line_c;
	     // fHProg1->Increment(69./float(size)); 

            val_ul = strtoul(line_c,NULL,16);

   
            int trigger_i = VM_V1x90nData::TriggerNumber(val_ul);
            eventn.tdc1 = -1000;
            eventn.tdc2 = -1000;
            eventn.tdc3 = -1000;
            eventn.tdc4 = -1000;
            eventn.tdc5 = -1000;
            eventn.tdc6 = -1000;
            eventn.tdc7 = -1000;
            eventn.tdc8 = -1000;
            eventn.tdc9 = -1000;
            eventn.tdc10 = -1000;
            eventn.tdc11 = -1000;
            eventn.tdc12 = -1000;
            eventn.tdc13 = -1000;
            eventn.tdc14 = -1000;
            eventn.tdc15 = -1000;
            eventn.tdc16 = -1000;
	    short ff;
	    	       for (ff=0; ff<=15; ff++) {
		       tdc[ff] = -1000;
		       rate2[ff]= -1000;
		       };
		       
		fHProg1->Increment(100.*67./float(size)); 	    	    	    	    
            while ( !(VM_V1x90nData::isGlobalTrailer(val_ul))
                   && !(VM_V1x90nData::isFiller(val_ul)) ) {
               if ( VM_V1x90nData::isMeasurement(val_ul) ) {
	       tdcchtmp = VM_V1x90nData::ChannelNumber(val_ul);
               tdcvaltmp = VM_V1x90nData::ChannelValue(val_ul);

                       short mm;
	       	       for (mm=0; mm<=15; mm++) {
	       if ((Int_t)tdc_ch[mm]->GetNumber() == tdcchtmp) {
               if (tdc[mm] == -1000) {
	       tdc[mm] = tdcvaltmp;
               switch ( mm ) {
               case 0 :
	       eventn.tdc1 = tdcvaltmp;
	       break;
               case 1 :
	       eventn.tdc2 = tdcvaltmp;
	       break;
               case 2 :
	       eventn.tdc3 = tdcvaltmp;
	       break;
               case 3 :
	       eventn.tdc4 = tdcvaltmp;
	       break;
               case 4 :
	       eventn.tdc5 = tdcvaltmp;
	       break;
               case 5 :
	       eventn.tdc6 = tdcvaltmp;
	       break;
               case 6 :
	       eventn.tdc7 = tdcvaltmp;
	       break;
               case 7 :
	       eventn.tdc8 = tdcvaltmp;
	       break;
               case 8 :
	       eventn.tdc9 = tdcvaltmp;
	       break;
               case 9 :
	       eventn.tdc10 = tdcvaltmp;
	       break;
               case 10 :
	       eventn.tdc11 = tdcvaltmp;
	       break;
               case 11 :
	       eventn.tdc12 = tdcvaltmp;
	       break;
               case 12 :
	       eventn.tdc13 = tdcvaltmp;
	       break;
               case 13 :
	       eventn.tdc14 = tdcvaltmp;
	       break;
               case 14 :
	       eventn.tdc15 = tdcvaltmp;
	       break;
               case 15 :
	       eventn.tdc16 = tdcvaltmp;
	       break;	       	       	       	       
	       };
	       } else {
	       rate2[mm]=1;
	       };      
	       };
	       };
	      
	       


               } else if ( VM_V1x90nData::isTDCHeader(val_ul) ) {
           } else if ( VM_V1x90nData::isTDCTrailer(val_ul) ) {

               } else if ( VM_V1x90nData::isTDCError(val_ul) ) {
                
               }
               
               tdcPacket >> line_c;
	        // fHProg1->Increment(69./float(size)); 
               val_ul = strtoul(line_c,NULL,16);
            }

         } 
	   
 	       


	    };
	    };



   input_f.close();
   
   };

	double_rate->GetXaxis()->SetTitle("tdc number");
	double_rate->GetYaxis()->SetTitle("number of events");

       double_rate->Write();
        t20->Write("", TObject::kOverwrite);
//      outFile->Write(); // write to the output file
      outFile->Close(); // close the output file 
      
      // Close data file
   
//      exit->SetRightMargin(10);
	       for (i=0; i<=15; i++) { 
	       tdc_ch[i]->SetState(0);
	       adc_ch[i]->SetState(0);
	       };     
      exit->ChangeBackground(0xff0000);
      exit->SetForegroundColor(0xf8f8ff);
      exit->Resize(40,exit->GetDefaultHeight());
      exit->SetText("Done");	
      
//      exit->SetForegroundColor(0xff0000);
     
      
}

int MyMainFrame::GetTdcPacket(ifstream& aDataFile, stringstream& aTdcPacket_s) {
   unsigned long val_ul;
   char line_c[9];
   int wordCnt = 0;
   do {
      wordCnt++;
      aDataFile >> line_c;
      // fHProg1->Increment(69./float(size)); 
      val_ul = strtoul(line_c,NULL,16);
      aTdcPacket_s << line_c << endl;
   } while ( !(VM_V1x90nData::isGlobalTrailer(val_ul)) );
   //aTdcPacket_s.str();  // *** I HAVE NO IDEA WHY, BUT THIS LINE PREVENTS ERRORS
/* aTdcPacket_s now contains a TDC Packet including global header and trailers.
   Returns the number of 32-bit words in packet. */
   return wordCnt;
}

int MyMainFrame::GetQdcPacket(ifstream& aDataFile, stringstream& aQdcPacket_s) {
/* NEED TO FIX -- Currently does not include the qdc header in the returned packet. */
/* Assume: aDataFile has its pointer at the beginning of a QDC Header. */
   unsigned long val_ul;
   char line_c[9];
   int wordCnt = 0;
   do {
      wordCnt++;
      aDataFile >> line_c;
      // fHProg1->Increment(69./float(size)); 
      val_ul = strtoul(line_c,NULL,16);
      aQdcPacket_s << line_c << endl;
   } while ( !(VM_V792nData::isQdcFooter(val_ul)) );
   //aQdcPacket_s.str();  // *** I HAVE NO IDEA WHY, BUT THIS LINE PREVENTS ERRORS
/* aQdcPacket_s now contains a QDC Packet including header and trailer.
   Returns the event number of the readings. */
   return (VM_V792nData::getEventCnt(val_ul));
}

void MyMainFrame::OpenFile() {
   static TString dir(".");
 
   const char * k_xml_file_extensions[] =
   {

    "dat files",     "*.dat",
    "All files",     "*",
     0,               0
   };
     TGFileInfo fi;

    fi.fFileTypes = k_xml_file_extensions;
    fi.fIniDir    = StrDup( dir.Data() );
    fi.fMultipleSelection = 1;
    
     nfiles = 0;
     
     ostringstream cmd;
    
 TGFileDialog *jopafile =  new TGFileDialog(gClient->GetRoot(),fMain , kFDOpen, &fi);
     if (fi.fMultipleSelection && fi.fFileNamesList) {
   TObjString *el;
   TIter next(fi.fFileNamesList);
   while ((el = (TObjString *) next())) {
     _current_file[nfiles] = el->GetString(); 

      nfiles++;
//      new TFile(el->GetString(), "update");
   }
    
    ostringstream tochka;
     tochka << _current_file[0].c_str()[strlen(_current_file[0].c_str())-4];
     

     if (strcmp(tochka.str().c_str(),".") == 0)  {

     
      short i;
       
       for (i=0; i<nfiles; i++) {
       
       cmd << _current_file[i] << "\n";
       
       };     
      
      
      if (file_status) {
      go->SetState(kButtonUp);
      go->Released(); } else {
      file_status = 1;
      };
      
      input_file->SetState(kButtonDisabled);
      hframe->RemoveFrame(input_file);
      hframe->RemoveFrame(output_file);
      hframe->RemoveFrame(labelqout);
      hframe->RemoveFrame(data_files); 
      
                
      labelq = new TGLabel(hframe, cmd.str().c_str());
      labelq->SetForegroundColor(0xff0000);
      labelq->SetTextColor(0xff0000);
      hframe->AddFrame(labelq, new TGLayoutHints(kLHintsLeft, -1150,1330-5*_current_file[0].size(),353,0));
      
 //     fMain->AddFrame(hframe, new TGLayoutHints(kLHintsCenterX,0,0,0,0));
    
      
    
    // Set a name to the main frame
 //   fMain->SetWindowName("jopa");
    // Map all subwindows of main frame
  fMain->MapSubwindows();
    // Initialize the layout algorithm
   fMain->Resize(fMain->GetDefaultSize());
    // Map main frame
   fMain->MapWindow(); 
   };     
};   
    
      };   
         
void MyMainFrame::OutFile() {
   static TString dir(".");
   static TString out("output.root");
//       cout << path << "\n";
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
    
    new TGFileDialog(gClient->GetRoot(),fMain , kFDOpen, &fi);
    if( fi.fFilename ) {
     
      _out_file = string( fi.fFilename );
     
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
      hframe->RemoveFrame(data_files);     
           
      labelqout = new TGLabel(hframe, cmd.str().c_str());
      labelqout->SetForegroundColor(0xff0000);
      labelqout->SetTextColor(0xff0000);
      hframe->AddFrame(labelqout, new TGLayoutHints(kLHintsLeft, -1150,1330-5*_out_file.size(),393,0));
      
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


void MyMainFrame::Browse() {
gSystem->Exec("firefox -new-window http://129.252.33.160/vme_data/"); 
	  };  
	  
	  
	   
    void MyMainFrame::MainFrame() {
    // Clean up used widgets: frames, buttons, layouthints
    fMain->Cleanup();
    delete fMain;
}
