#include "fit2_var.h"


   Double_t g2(Double_t *x, Double_t *par) {
   Double_t r1 = Double_t((x[0]-par[0])*(x[0]-par[0])/par[1]/par[1]);
   Double_t r2 = Double_t((x[1]-par[2])*(x[1]-par[2])/par[3]/par[3]);
   return par[4]+r1+r2;
   }
 

void fit2_var::fiti( TH2F *a1, TH2F *a2, TH2F *a3, TH2F *a4, TH2F *a5, Float_t param[] ) 
{


   
   const Int_t npar = 5;
   Double_t f2params[npar] = {1,1,1,1,1};
   TF2* f2 = new TF2("f2",&g2,-2,6,-2,6, npar);
   f2->SetParameters(f2params);

   a1->Fit("f2","WNQR");
   
   Double_t x1 = f2->GetParameter(0);
   Double_t y1 = f2->GetParameter(2);
   param[1]=x1; 


   a2->Fit("f2","WNQR");

   Double_t x2 = f2->GetParameter(0);
   Double_t y2 = f2->GetParameter(2);
   param[2]=x2;

   a3->Fit("f2","WNQR");

   Double_t x3 = f2->GetParameter(0);
   Double_t y3 = f2->GetParameter(2);
   param[5]=x3;

   a4->Fit("f2","WNQR");
  
   Double_t x4 = f2->GetParameter(0);
   Double_t y4 = f2->GetParameter(2);
   param[6]=x4;
   
    
float yavr;
yavr = ((y1+y2+y3+y4)/4.);

    param[3]=yavr;

short i,j,a,b,ib;
a = a5->GetNbinsX();
b = a5->GetNbinsY();
float xnew;
float ynew;

TH1F *hhh;
TH1F *h5 = new TH1F("h5", "eprst",21, -2., 6.);
TH1F *h55 = new TH1F("h55","inverted",21, -2., 6.);
for (i=0; i<a; i++){
hhh = (TH1F*) a5->ProjectionY(" ",i,i);
int minbin = hhh->GetMinimumBin();
float xmin = hhh->GetXaxis()->GetBinCenter(minbin);

xnew = hhh->GetXaxis()->GetBinCenter(i);
ynew= xmin;
h55->Fill(xnew,xmin);
} 

TF1 *func33 = new TF1("func33","pol1",-2,6);

h55->Fit("func33","NQW");

Double_t p1 = func33->GetParameter(0);
Double_t p2 = func33->GetParameter(1);

	param[4]=(yavr-p1)/p2;	
	h5->Delete();
	h55->Delete();

}

