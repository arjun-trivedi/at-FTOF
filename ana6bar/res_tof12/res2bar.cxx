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
#include "TCanvas.h"
#include "TVirtualFitter.h"
#include "TMath.h"
#include "TGraphErrors.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TText.h"
#include "TStyle.h"
#include "TObject.h"
#include "test_cl.h"
#include "Resolution2bar.h"
#include <TRint.h>
#include <stdio.h>
#include <dlfcn.h>

extern void InitGui();
VoidFuncPtr_t initfuncs[] = { InitGui, 0 };

TROOT root("root_res2bar","Two-bar Resolution Analysis",initfuncs);

int main(int argc, char** argv) {
  TRint theApp("app_res2bar",&argc,argv);
  //Resolution2bar resApp;
  
  // Removing output file left from previouse run
  remove( "output.root" );
  
  // Reading number of points along the bar
  int n_point;
  cout << "Enter number of points" << "\n";
  cin >>  n_point;
  cout << "\n" << "Number of points is " << n_point << "\n";

/*  string file_name;
  cout << "Enter input file name " << "\n";
  cin >> file_name;
  cout << "\n" << "Input file is: " << file_name << "\n";
  
    void* handle = dlopen("./VM_FileProcessor_C.so", RTLD_LAZY);
    typedef void (*processRawData_t)(char* aDataFile);
    processRawData_t processRawData = (processRawData_t) dlsym(handle, "processRawData");

//   processRawData(const_cast<char *>(file_name.c_str()));
     
    processRawData("07-30-10-6x6x120-ref.dat");
    
//   dlclose(handle);

 */
  
     int ii_my;
   ii_my=3;
   
Resolution2bar res;
res.Draw();
res.AddCut("cut_noPed","t_pmt[1]>-1 && t_pmt[2]>-1 && t_pmt[3]>-1 && t_pmt[4]>-1 && t_pmt[5]>-1 && t_pmt[6]>-1");
res.ActivateCut("cut_noPed"); 
int qqq4;

TH1 *eee = (TH1F*) gDirectory->Get("hist_tdcDiff_btm");
short i,a,ib;
a = eee->GetNbinsX();
//cout << a << "\n";
float y[50000],b,b1;
b=0;
b1=0;
ib=0;
for (i=1; i<=a; i++)
{
y[i]=eee->GetBinContent(i);
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
float yleft=fabs(y[1]-b/100.);
int ileft=0;
for (i=1; i<=ib; i++)
{
if ((fabs(y[i]-b/100.))<yleft) {
yleft=fabs(y[i]-b/100.);
ileft=i;
}
}

int xleft=eee->GetXaxis()->GetBinCenter(ileft);

float yright=fabs(y[ib]-b/100.);
int iright=0;
for (i=ib; i<=a; i++)
{
//cout << i << "\n";
if ((fabs(y[i]-b/100.))<yright) {
yright=fabs(y[i]-b/100.);
iright=i;
//cout << i << "\n";
}
}
int xright=eee->GetXaxis()->GetBinCenter(iright);

//cout << xleft << " " << xright << " " << (xright-xleft)/n_bins << "\n";

int diff=(xright-xleft)/n_point;

  
   TH1F *hist_resol = new TH1F("hist_resol", "hist_resol",n_point, xleft, xright);
   TH1F *hist_p1 = new TH1F("hist_p1", "hist_p1",n_point, xleft, xright);
   TH1F *hist_p2 = new TH1F("hist_p2", "hist_p2",n_point, xleft, xright);
   TH1F *hist_p3 = new TH1F("hist_p3", "hist_p3",n_point, xleft, xright);
   TH1F *hist_p4 = new TH1F("hist_p4", "hist_p4",n_point, xleft, xright);   
   TH1F *hist_p5 = new TH1F("hist_p5", "hist_p5",n_point, xleft, xright);
   TH1F *hist_p6 = new TH1F("hist_p6", "hist_p6",n_point, xleft, xright);   
   float sigma[n_point],error[n_point],tdcdiff[n_point],errorx[n_point],p1[n_point],p2[n_point],p3[n_point],p4[n_point],p5[n_point],p6[n_point];
    
    test_cl test_resol;

    TFile *output = new TFile("output.root","NEW");
    TDirectory *full_bar = output->mkdir("full_bar");
    gROOT->cd();
    TH1F *tdcDiff_btm = (TH1F*)eee->Clone("tdcDiff_btm");
    tdcDiff_btm->SetDirectory(full_bar);
    
    TH1 *eee1 = (TH1F*) gDirectory->Get("hist_tdcDiff_top");    
    TH1F *tdcDiff_top = (TH1F*)eee1->Clone("tdcDiff_top");
    tdcDiff_top->SetDirectory(full_bar); 
    
    TH1 *eee2 = (TH1F*) gDirectory->Get("hist_tdcDiff_mid");    
    TH1F *tdcDiff_mid = (TH1F*)eee2->Clone("tdcDiff_mid");
    tdcDiff_mid->SetDirectory(full_bar);    
    
    TH2 *eee3 = (TH2F*) gDirectory->Get("hist_topvsbtm");    
    TH2F *topvsbtm = (TH2F*)eee3->Clone("topvsbtm");
    topvsbtm->SetDirectory(full_bar);       
    
    TH2 *eee4 = (TH2F*) gDirectory->Get("hist_topvsbtm2");    
    TH2F *topvsbtm2 = (TH2F*)eee4->Clone("topvsbtm2");
    topvsbtm2->SetDirectory(full_bar); 
    
   TH1F *qq1;
   qq1 = (TH1F*) gDirectory->Get("hist_a_tl");
   TH1F *a_tl = (TH1F*)qq1->Clone("a_tl");
   a_tl->SetDirectory(full_bar);
   
   TH1F *qq2;
   qq2 = (TH1F*) gDirectory->Get("hist_a_tr");
   TH1F *a_tr = (TH1F*)qq2->Clone("a_tr");
   a_tr->SetDirectory(full_bar);   
   
   TH1F *qq3;
   qq3 = (TH1F*) gDirectory->Get("hist_a_ml");
   TH1F *a_ml = (TH1F*)qq3->Clone("a_ml");
   a_ml->SetDirectory(full_bar);
   
   TH1F *qq4;
   qq4 = (TH1F*) gDirectory->Get("hist_a_mr");
   TH1F *a_mr = (TH1F*)qq4->Clone("a_mr");
   a_mr->SetDirectory(full_bar);    
               
   TH1F *qq5;
   qq5 = (TH1F*) gDirectory->Get("hist_a_bl");
   TH1F *a_bl = (TH1F*)qq5->Clone("a_bl");
   a_bl->SetDirectory(full_bar);
   
   TH1F *qq6;
   qq6 = (TH1F*) gDirectory->Get("hist_a_br");
   TH1F *a_br = (TH1F*)qq6->Clone("a_br");
   a_br->SetDirectory(full_bar);    
               	       
       
    output->Write();
    output->Close();
    
       
       for (ii_my=0; ii_my<n_point; ii_my++)
   {
   Float_t resolv[8];

 cout << "Processing point number " << ii_my+1 << "\n";
  
   test_resol.test(ii_my,n_point,resolv,xleft,xright);
   
   
   tdcdiff[ii_my]=xleft+diff*ii_my+diff/2;
   sigma[ii_my]=resolv[0]*25.*sqrt(2./3.);
   error[ii_my]=resolv[1]*25.*sqrt(2./3.);
   errorx[ii_my]=0;
   
   hist_resol->SetBinContent(ii_my+1,sigma[ii_my]);
   hist_resol->SetBinError(ii_my+1,error[ii_my]);
   
    hist_p1->SetBinContent(ii_my+1,resolv[2]);
    hist_p2->SetBinContent(ii_my+1,resolv[3]); 
    hist_p3->SetBinContent(ii_my+1,resolv[4]);        
    hist_p4->SetBinContent(ii_my+1,resolv[5]);
    hist_p5->SetBinContent(ii_my+1,resolv[6]); 
    hist_p6->SetBinContent(ii_my+1,resolv[7]); 

cout << resolv[2] << " " <<  resolv[3] << " "  << resolv[4] << " " << resolv[5] << " " << resolv[6] << " " << resolv[7] << "\n";
            
   
//   cout << " " << resolv[0] << "\n";
/*   h5->Delete();
   h55->Delete();   
   hist_mr_tmp->Delete();
   hist_tl_tmp->Delete();
   hist_tr_tmp->Delete();
   hist_tw_tl->Delete();
   hist_mtw_mr->Delete();
   hist_tw_tr->Delete();
   hist_bl_tmp->Delete();
   hist_br_tmp->Delete();
   hist_tw_bl->Delete();
   hist_tw_br->Delete(); */
   };    

    TFile *output1 = new TFile("output.root","UPDATE");
    TDirectory *full_bar1 = output1->GetDirectory("full_bar");
    gROOT->cd();
   TH1F *par1 = (TH1F*)hist_p1->Clone("par1");
   par1->SetDirectory(full_bar1);
   TH1F *par2 = (TH1F*)hist_p2->Clone("par2");
   par2->SetDirectory(full_bar1);
   TH1F *par3 = (TH1F*)hist_p3->Clone("par3");
   par3->SetDirectory(full_bar1);
   TH1F *par4 = (TH1F*)hist_p4->Clone("par4");
   par4->SetDirectory(full_bar1); 
   TH1F *par5 = (TH1F*)hist_p5->Clone("par5");
   par5->SetDirectory(full_bar1);
   TH1F *par6 = (TH1F*)hist_p6->Clone("par6");
   par6->SetDirectory(full_bar1);  
   TH1F *resol = (TH1F*)hist_resol->Clone("resol");
   resol->SetDirectory(full_bar1);  
   output1->Write();
   output1->Close();
        
   
   
   
    TCanvas *cresolv = new TCanvas("cresolv", "Resolution", 700, 1000);
    cresolv->Divide(1,2);
    TGraphErrors *Tg = new TGraphErrors(n_point,tdcdiff,sigma,errorx,error);

    std::ostringstream title; 
    title << "Time resolution";
  
   Tg->SetMarkerStyle(kFullCircle);
//   Tg->SetMaximum(1.2);
//   Tg->SetMinimum(0.8);
   Tg->SetTitle(title.str().c_str());
   cresolv->cd(1);
   Tg->Draw("AP");
   
   Tg->GetXaxis()->SetTitle("tdc_diff");
   Tg->GetXaxis()->SetTitleSize(0.06);
   Tg->GetXaxis()->SetTitleOffset(0.7);
   cresolv->cd(2);
   hist_resol->Draw();
   
   TCanvas *cparameters = new TCanvas("parameters", "tw parameters", 700, 1000);   
   cparameters->Divide(2,3);

   cparameters->cd(1);
   hist_p1->Draw();   
   cparameters->cd(2);
   hist_p2->Draw();   
   cparameters->cd(3);      
   hist_p3->Draw();
   cparameters->cd(4);
   hist_p4->Draw();   
   cparameters->cd(5);
   hist_p5->Draw();   
   cparameters->cd(6);      
   hist_p6->Draw();    
  theApp.Run();
  return 0;
}
