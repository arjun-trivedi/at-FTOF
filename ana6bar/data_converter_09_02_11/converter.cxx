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
#include <TRint.h>
#include <stdio.h>
#include <dlfcn.h>
#include <TGClient.h>
#include <TCanvas.h>
#include <TRandom.h>
#include <TGButton.h>
#include <TGFrame.h>
#include <TRootEmbeddedCanvas.h>
#include <RQ_OBJECT.h>
#include <iostream>
#include <stdio.h>
#include "MyMainFrame.h"
 using namespace std;      
     
     
     







int main(int argc, char** argv) {
    TApplication *theApp = new TApplication("App", &argc, argv);
    MyMainFrame jopa;
    jopa.MainFrame(gClient->GetRoot(),2000,20000);
    
 //   TCanvas *cresolv = new TCanvas("cresolv", "Resolution", 500, 800);
//    TGMainFrame *fMain = new TGMainFrame(gClient->GetRoot(),200,200);
//    fMain->SetWindowName("Simple Example");
 //   TRootEmbeddedCanvas *fEcanvas = new TRootEmbeddedCanvas("Ecanvas",fMain,200,200); 
//    fMain->AddFrame(fEcanvas, new TGLayoutHints(kLHintsExpandX| kLHintsExpandY,10,10,10,1));
   
 

   
//   theApp.Run();
  theApp->Run(kTRUE); 

 
  
  return 0;
}
