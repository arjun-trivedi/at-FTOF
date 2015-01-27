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

// create an empty vector of strings
    vector<string> args;
    // copy program arguments into vector
    Int_t i;
    Int_t setnum_inp = 0;
    Int_t npoints_inp = 0;
    bool langau_inp = false;
    bool outtree_inp = false;
    string inpfile_inp = "";
    string outfile_inp = "";
    
    for (i=1;i<argc;i++) 
        args.push_back(argv[i]);
    // sort vector
  
   int optind=1;    
     while ((optind < argc) && (argv[optind][0]=='-')) {
        string sw = argv[optind];
	string sw1 = argv[optind];
	string sw2 = argv[optind];
	string sw3 = argv[optind];
	string sw5 = argv[optind];
	
        if (sw=="-h") {
            optind++;
            cout << "Options:" << "\n";
	    cout << "-h or --help print this message;" << "\n";
	    cout << "-s bar set number, must be between 1 and 62;" << "\n";
	    cout << "-p number of points along the bar (auto if not specified), need to be >=5 and <=133;" << "\n";
	    cout << "-L perform Langau fit if present;" << "\n";
	    cout << "-T include tree into output file if present;" << "\n";
	    cout << "-i input file;" << "\n";
	    cout << "-o output file (need to be *.root);" << "\n";
	    return 0;
        }
        else if (sw=="--help") {
            optind++;
            cout << "Options:" << "\n";
	    cout << "-h or --help print this message;" << "\n";
	    cout << "-s bar set number, must be between 1 and 62;" << "\n";
	    cout << "-p number of points along the bar (auto if not specified), need to be >=5 and <=133;" << "\n";
	    cout << "-L perform Langau fit if present;" << "\n";
	    cout << "-T include tree into output file if present;" << "\n";
	    cout << "-i input file;" << "\n";
	    cout << "-o output file (need to be *.root);" << "\n";
	    return 0;
	    
        } 
	else if (sw=="-L") {
        langau_inp = true;
            cout << "Langau fit " << langau_inp << "\n";

        }
        else if (sw=="-T") {
        outtree_inp = true;
            cout << "Output tree " << outtree_inp << "\n";

        }		       
	else if (sw=="-s") {
            optind++;
	    if (!(optind < argc)) 
	    { 
	    cout << "WRONG SET NUMBER" << "\n";
	    return 0;
	    };
	    setnum_inp = atoi(argv[optind]);
            cout << "set number = " << setnum_inp << "\n";
	    if (!((setnum_inp <= 62) && (setnum_inp >= 1))) {
	    cout << "WRONG SET NUMBER" << "\n";
	    return 0;
	    };	

        }
	else if (sw1.replace(sw1.begin()+2,sw1.end(),"")=="-s") {
 //           optind++;
	    sw1 = argv[optind];
	    sw1.replace(sw1.begin(),sw1.begin()+2,"");
	    setnum_inp = atoi(sw1.c_str());
            cout << "set number = " << setnum_inp << "\n";	
	    if (!((setnum_inp <= 62) && (setnum_inp >= 1))) {
	    cout << "WRONG SET NUMBER" << "\n";
	    return 0;
	    };	    
        }
	else if (sw=="-i") {
            optind++;
	    if (!(optind < argc)) 
	    { 
	    cout << "WRONG FILE NAME" << "\n";
	    return 0;
	    };
	    inpfile_inp = argv[optind];
            cout << "input file is " << inpfile_inp << "\n";
	    	

        }
	else if (sw2.replace(sw2.begin()+2,sw2.end(),"")=="-i") {
 //           optind++;
	    sw2 = argv[optind];
	    sw2.replace(sw2.begin(),sw2.begin()+2,"");
	    inpfile_inp = sw2;
            cout << "input file is " << inpfile_inp << "\n";	    
        }
	
	else if (sw=="-o") {
            optind++;
	    if (!(optind < argc)) 
	    { 
	    cout << "WRONG FILE NAME" << "\n";
	    return 0;
	    };
	    sw5 = argv[optind];
	    if (sw5.replace(sw5.begin(),sw5.end()-5,"") != ".root") {
	     cout << "OUTPUT FILE NEED TO BE *.root" << "\n";
	    return 0;
	    };
	    outfile_inp = argv[optind];
            cout << "output file is " << outfile_inp << "\n";
	    	

        }
	else if (sw3.replace(sw3.begin()+2,sw3.end(),"")=="-o") {
 //           optind++;
	    if (sw5.replace(sw5.begin(),sw5.end()-5,"") != ".root") {
	     cout << "OUTPUT FILE NEED TO BE *.root" << "\n";
	    return 0;
	    }; 
	    sw3 = argv[optind];
	    sw3.replace(sw3.begin(),sw3.begin()+2,"");
	    outfile_inp = sw3;
            cout << "output file is " << outfile_inp << "\n";	    
        }	
		
        else if (sw=="-p") {
            optind++;
	    if (!(optind < argc)) 
	    { 
	    cout << "WRONG SET NUMBER" << "\n";
	    return 0;
	    };
	    npoints_inp = atoi(argv[optind]);
            cout << "number of points = " << npoints_inp << "\n";
	    if (!((npoints_inp <= 133) && (npoints_inp >= 5))) {
	    cout << "WRONG NUMBER OF POINTS" << "\n";
	    return 0;
	    };	

        }
	else if (sw.replace(sw.begin()+2,sw.end(),"")=="-p") {
 //           optind++;
	    sw = argv[optind];
	    sw.replace(sw.begin(),sw.begin()+2,"");
	    npoints_inp = atoi(sw.c_str());
            cout << "number of points = " << npoints_inp << "\n";	
	    if (!((npoints_inp <= 133) && (npoints_inp >= 5))) {
	    cout << "WRONG NUMBER OF POINTS" << "\n";
	    return 0;
	    };	    
        }

	
	
        else {
            cout << "Unknown switch: " 
                 << argv[optind] << endl;
		 return 0;
		 }
        optind++;
    }



    if (((setnum_inp == 0) && (npoints_inp != 0)) ||  ((setnum_inp == 0) && (langau_inp != 0))  ||  ((setnum_inp == 0) && (outtree_inp != 0)) ||  ((setnum_inp == 0) && (inpfile_inp != "")) ||  ((setnum_inp == 0) && (outfile_inp != ""))) {
    cout << "BAR SET NUMBER NEED TO BE SPECIFIED" << "\n";
	    return 0;
    };
    
    if (((setnum_inp != 0) && (inpfile_inp == ""))) {
    cout << "NO INPUT FILE" << "\n";
	    return 0;
    };  
    
    if (((setnum_inp != 0) && (outfile_inp == ""))) {
    cout << "NO OUTPUT FILE" << "\n";
	    return 0;
    };       
  
  
    TApplication *theApp = new TApplication("App", &argc, argv);
    MyMainFrame jopa;
    jopa.MainFrame(gClient->GetRoot(),720,440,setnum_inp,npoints_inp,langau_inp,outtree_inp,inpfile_inp,outfile_inp);
    
 //   TCanvas *cresolv = new TCanvas("cresolv", "Resolution", 500, 800);
//    TGMainFrame *fMain = new TGMainFrame(gClient->GetRoot(),200,200);
//    fMain->SetWindowName("Simple Example");
 //   TRootEmbeddedCanvas *fEcanvas = new TRootEmbeddedCanvas("Ecanvas",fMain,200,200); 
//    fMain->AddFrame(fEcanvas, new TGLayoutHints(kLHintsExpandX| kLHintsExpandY,10,10,10,1));
   
 
//   cout << "jopa" << "\n";
   
//   theApp.Run();
  
  if (setnum_inp == 0) { 
  theApp->Run(kTRUE); 
  } else {
  return 0;
  };

 
  
  return 0;
}
