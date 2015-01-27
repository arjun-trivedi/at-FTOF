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
#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TText.h"
#include "TStyle.h"
#include "TObject.h"
#include "test_cl.h"
#include "Resolution2bar.h"

using namespace std;

    float myFunction(TH1F *a) {
    TH1 *anew = a->Rebin(64,"anew");
    int xbinmax = anew->GetMaximumBin();
    float ymax = anew->GetBinContent(xbinmax);
    float sum=anew->GetXaxis()->GetBinCenter(xbinmax)-220;
//    c7->cd();

//    a->Draw();
    Double_t par[6];
    TF1 *g1    = new TF1("g1","gaus",sum,4096);
    TF1 *g2    = new TF1("g2","landau",sum,4096);
    TF1 *g3    = new TF1("g3","gaus(0)+landau(3)",sum,4096);
    float yaxmax = a->GetMaximum();
    TLine *line2 = new TLine(sum,0.,sum,yaxmax);
    line2->SetLineColor(2);
    line2->SetLineWidth(3); 
 
      
    g3->SetLineColor(kRed);
    g3->SetLineWidth(6);
    a->Fit(g1,"QNR");
    a->Fit(g2,"QNR+");
    gStyle->SetOptFit(0);
    g1->GetParameters(&par[0]);
    g2->GetParameters(&par[3]);
    g3->SetParameters(par);
    g2->SetParNames ("P1","P2","P3","P4","P5","P6");
    a->Fit(g3,"QNR+");
    g3->GetParameters(par);

//    c7->Update();
//    line2->Draw();    
    TLine *line3 = new TLine(par[4]-3*par[5],0.,par[4]-3*par[5],yaxmax);
    line3->SetLineColor(3);
    line3->SetLineWidth(3);
//    line3->Draw(); 
    std::stringstream out;
    out << "peak position = " << par[4];


    TText *t1 = new TText(2300,yaxmax*0.9,out.str().c_str());

    std::stringstream out1;
    out1 << "sigma = " <<par[5];

    TText *t2 = new TText(2300,yaxmax*0.8,out1.str().c_str());
     
    t1->SetTextSize(0.05); 
//    t1->Draw();
//    t2->Draw(); 
    anew->Delete();
    return sum;
 }

void test_cl::test(Int_t ii, Int_t n_bins, Float_t resolv[], Int_t xleftt, Int_t xrightt) {
//TFile *fff = new TFile("out_all_resolution.root", "new");

//gROOT->LoadMacro("VM_FileProcessor.C");
//gROOT->LoadMacro("fit2_var.C"); 
Resolution2bar res;
res.Draw();
res.AddCut("cut_noPed","t_pmt[1]>-1 && t_pmt[2]>-1 && t_pmt[3]>-1 && t_pmt[4]>-1 && t_pmt[5]>-1 && t_pmt[6]>-1");
res.ActivateCut("cut_noPed");
//TCanvas *c3 = new TCanvas("c3", "Y projection", 600, 400);
TH2F *py2;
py2 = (TH2F*) gDirectory->Get("hist_topvsbtm2");
TH1 *py = py2->ProjectionY("projection");
      py->Fit("gaus","Q0");
//      py->GetFunction("gaus")->SetLineColor(kRed);
//      py->GetFunction("gaus")->SetLineWidth(6);
//      c3->Update();
      TF1 *fit = py->GetFunction("gaus");
      Float_t mean = fit->GetParameter(1);
      Float_t sigma = fit->GetParameter(2);
   

//      c2->cd();
// TCanvas *c2 = new TCanvas("c2", "(tds_tl-tds_tr)/2 - (tds_bl-tds_br)/2 vs (tds_bl-tds_br)/2", 600, 400);   
//	hist_topvsbtm2->Draw("colz");
        TLine *line1 = new TLine(100.,mean,700,mean); 
        line1->SetLineColor(2);
        line1->SetLineWidth(3);
//        line1->Draw();


int diff=(xrightt-xleftt)/n_bins; 
 

//	TH1F *hist_resol = new TH1F("hist_resol", "hist_resol",100, 200., 600.);
//	for (ii=2; ii<4; ii++)
//	{
	

res.SetTopBtmPosCut(226,562,xleftt+diff*ii,xleftt+diff*(ii+1),mean,sigma);

//	res.SetTopBtmPosCut(226,562,300,340,mean,sigma); 
	 
//	c2->cd();
//        line1->Draw();
	
     
//    TCanvas *c14 = new TCanvas("c14", "ADC cuts", 700, 1000);
//   c14->Divide(2,3);
   
//    TCanvas *c7 = new TCanvas("c7", "Jopa", 600, 400);
   
    TFile *output = new TFile("output.root","UPDATE");
     std::stringstream out;
    out << "point_" << ii+1;
   TDirectory *dir = output->mkdir(out.str().c_str());
   gROOT->cd(); 
   
   
   TH1F *qq2;
   qq2 = (TH1F*) gDirectory->Get("hist_a_tr");  
   TH1F *qq3;
   qq3 = (TH1F*) gDirectory->Get("hist_a_ml"); 
   TH1F *qq4;
   qq4 = (TH1F*) gDirectory->Get("hist_a_mr");   
   TH1F *qq5;
   qq5 = (TH1F*) gDirectory->Get("hist_a_bl");  
   TH1F *qq6;
   qq6 = (TH1F*) gDirectory->Get("hist_a_br");
   TH1F *qq1;
   qq1 = (TH1F*) gDirectory->Get("hist_a_tl");

   TH1F *a_tl = (TH1F*)qq1->Clone("a_tl");
   a_tl->SetDirectory(dir);  

   TH1F *a_tr = (TH1F*)qq2->Clone("a_tr");
   a_tr->SetDirectory(dir);    

   TH1F *a_ml = (TH1F*)qq3->Clone("a_ml");
   a_ml->SetDirectory(dir); 
   
   TH1F *a_mr = (TH1F*)qq4->Clone("a_mr");
   a_mr->SetDirectory(dir);
   
   TH1F *a_bl = (TH1F*)qq5->Clone("a_bl");
   a_bl->SetDirectory(dir);  
   
   TH1F *a_br = (TH1F*)qq6->Clone("a_br");
   a_br->SetDirectory(dir);     
   
    TH1 *eee = (TH1F*) gDirectory->Get("hist_tdcDiff_btm");
    TH1F *tdcDiff_btm = (TH1F*)eee->Clone("tdcDiff_btm");
    tdcDiff_btm->SetDirectory(dir);
    
    TH1 *eee1 = (TH1F*) gDirectory->Get("hist_tdcDiff_top");    
    TH1F *tdcDiff_top = (TH1F*)eee1->Clone("tdcDiff_top");
    tdcDiff_top->SetDirectory(dir); 
    
    TH1 *eee2 = (TH1F*) gDirectory->Get("hist_tdcDiff_mid");    
    TH1F *tdcDiff_mid = (TH1F*)eee2->Clone("tdcDiff_mid");
    tdcDiff_mid->SetDirectory(dir);    
    
    TH2 *eee3 = (TH2F*) gDirectory->Get("hist_topvsbtm");    
    TH2F *topvsbtm = (TH2F*)eee3->Clone("topvsbtm");
    topvsbtm->SetDirectory(dir);       
    
    TH2 *eee4 = (TH2F*) gDirectory->Get("hist_topvsbtm2");    
    TH2F *topvsbtm2 = (TH2F*)eee4->Clone("topvsbtm2");
    topvsbtm2->SetDirectory(dir);    
    
//   qq1->Rebin(1,"qq1copy");
//   TH1F* qq1copy;
//   qq1copy = (TH1F*) qq1->Clone();  
//   qq1copy->SetName("qq1copy"); 
//  c14->cd(1);      
  float z1; 
  z1 = myFunction(qq1);

//  c14->cd(1);
//  c7->DrawClonePad();  

//   TCanvas *c8 = new TCanvas("c8", "Jopa1", 600, 400);
//   c7->cd();
//   c14->cd(2);
  float z2; 
  z2 = myFunction(qq2);

//  c14->cd(2);
//  c7->DrawClonePad(); 
  
//  c14->cd(3); 

  float z3; 
  z3 = myFunction(qq3);

//  c14->cd(3);
//  c7->DrawClonePad(); 
  
//  c14->cd(4);
  float z4; 
  z4 = myFunction(qq4);

//  c14->cd(4);
//  c7->DrawClonePad();  

//  c14->cd(5);
  float z5; 
  z5 = myFunction(qq5);

//  c14->cd(5);
//  c7->DrawClonePad();  

//  c14->cd(6);
  float z6; 
  z6 = myFunction(qq6);

//  c14->cd(6);
//  c7->DrawClonePad(); 
 




 
stringstream cut_str;

cut_str << "a_tl>" << z1 << " && " << "a_tr>" << z2 << " && " << "a_ml>" << z3 << " && " << "a_mr>" << z4 << " && " << "a_bl>" << z5 << " && " << "a_br>" << z6;

res.AddCut("cut_adc_noLow",cut_str.str().c_str());


//   c14->Modified();
//   c14->Update();

       
//  cin.get();
  
//  c15->Close();
  
//  cin.get();  
  
 
res.ActivateCut("cut_adc_noLow");
res.AutoTwCorrect(-2.0,6.0,20);

   TH2F *a11;
   a11 = (TH2F*)gDirectory->Get("hist_tw_tl");
   TH2F *a21;
   a21 = (TH2F*)gDirectory->Get("hist_tw_tr"); 
   TH2F *a31;
   a31 = (TH2F*)gDirectory->Get("hist_tw_bl");
   TH2F *a41;
   a41 = (TH2F*)gDirectory->Get("hist_tw_br");
   TH2F *a51;
   a51 = (TH2F*)gDirectory->Get("hist_mtw_mr"); 
   
   
   TH2F *tw_tl = (TH2F*)a11->Clone("tw_tl");
   tw_tl->SetDirectory(dir);  

   TH2F *tw_tr = (TH2F*)a21->Clone("tw_tr");
   tw_tr->SetDirectory(dir);    

   
   TH2F *tw_mr = (TH2F*)a51->Clone("tw_mr");
   tw_mr->SetDirectory(dir);
   
   TH2F *tw_bl = (TH2F*)a31->Clone("tw_bl");
   tw_bl->SetDirectory(dir);  
   
   TH2F *tw_br = (TH2F*)a41->Clone("tw_br");
   tw_br->SetDirectory(dir);        
  
   Float_t p[6];
   
//   gROOT->ProcessLine(".x fit2_var.C(a11,a21,a31,a41,a51,p)");
fit2_var eprst; 
eprst.fiti(a11,a21,a31,a41,a51,p); 

  
   
     
cout << p[1] << " " <<  p[2] << " "  << p[3] << " " << p[4] << " " << p[5] << " " << p[6] << "\n";

 float t1,t2,t3,t4,t5,t6;
  
  t1=p[1];
  t2=p[2];
  t3=p[3];
  t4=p[4];
  t5=p[5];
  t6=p[6];  
  
    
res.SetTwFactor(t3,t4,t1,t2,t5,t6);
res.Draw3barResolution();

TH1F *a6;
a6 = (TH1F*)gDirectory->Get("hist_c3barRes");
a6->Fit("gaus","QW0"); 
TF1 *resolfit = a6->GetFunction("gaus");
Float_t resolution;
Float_t resolution_sigma;
resolution = resolfit->GetParameter(2);

p[6]=t6;

cout << p[1] << " " <<  p[2] << " "  << p[3] << " " << p[4] << " " << p[5] << " " << p[6] << "\n";

resolution_sigma = resolfit->GetParError(2);


resolv[0]=resolution;
resolv[1]=resolution_sigma;
resolv[2]=p[1];
resolv[3]=p[2];
resolv[4]=p[3];
resolv[5]=p[4];
resolv[6]=p[5];
float joppa;
joppa = p[6];
resolv[7]=joppa;

cout << resolv[2] << " " <<  resolv[3] << " "  << resolv[4] << " " << resolv[5] << " " << resolv[6] << " " << resolv[7] << " " << joppa << " " << p[6] << "\n";

//};


//hist_resol->SetBinContent(ii,resolution);
//hist_resol->SetBinError(ii,resolution_sigma);

//};

//hist_resol->Draw();

//fff->Write();
//fff->Close();

//  c7->Close(); 

   output->Write();
   output->Close();  

res.Delete();  
a11->Delete();
a21->Delete();
a31->Delete();
a41->Delete();
a51->Delete();
 
}
