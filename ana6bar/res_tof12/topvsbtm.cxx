void topvsbtm(){
TFile *MyFile = new TFile("topvsbtm.root","READ");
MyFile->ls();   
c1 = new TCanvas("rose512", "(tl-tr)/2 vs (bl-br)/2", 600, 400);
TH1F *h = (TH1F*)MyFile->Get("hist_topvsbtm");
h->SetMaximum(5);
gStyle->SetOptLogz(0);
gStyle->SetPalette(1);
gStyle->SetOptStat(0);
gStyle->SetOptFit(1);
//h->Fit("pol1","0");
h->Draw("colz");

//TF1 *fit = h->GetFunction("pol1");

//Double_t p1 = fit->GetParameter(0);
Double_t p2 = 1;

//TLine *line1 = new TLine(150.,p2*150+p1,650,p2*650.+p1); 
//line1->SetLineColor(2);
//line1->SetLineWidth(3);
//line1->Draw();   
//h->Fit("pol1","0");
//cout << p1 <<"\n" << p2 << "\n";

short i,j,a,b,ib;
a = h->GetNbinsX();
b = h->GetNbinsY();
cout << a << "\n" << b << "\n";
float cosalph=sqrt(1/(1+p2*p2));
float sinalph=sqrt(1/(1+1/(p2*p2)));
float xmin,ymin;
ymin = h->GetYaxis()->GetBinCenter(0);
xmin = h->GetXaxis()->GetBinCenter(0);
float xminnew=xmin*cosalph+ymin*sinalph;
float yminnew=-1.*xmin*sinalph+ymin*cosalph;
cout << xminnew  << "\n" << yminnew << "\n";
float xmax,ymax;
ymax = h->GetYaxis()->GetBinCenter(b);
xmax = h->GetXaxis()->GetBinCenter(a);
float xmaxnew=xmax*cosalph+ymax*sinalph;
float ymaxnew=-1.*xmax*sinalph+ymax*cosalph;
cout << xmaxnew  << "\n" << ymaxnew << "\n";
TH2D *h2 = new TH2D("h2", "rotated",800, 200, 900, 800, -300., 300.);
TH2D *h3 = new TH2D("h3", "(tl-tr)/2-(bl-br)/2:(bl-br)/2",800, 100, 700, 800, -300., 300.);

for (i=1; i<=a; i++)
{
for (j=1; j<=b; j++)
{
float xold=h->GetXaxis()->GetBinCenter(i);
float yold=h->GetYaxis()->GetBinCenter(j);
float zold=h->GetBinContent(i,j);
float xnew=xold*cosalph+yold*sinalph;
float ynew=-1.*xold*sinalph+yold*cosalph;
h2->SetMaximum(5);
h2->Fill(xnew,ynew,zold);
h3->Fill(xold,yold-xold,zold);
// cout << "x=" << xold << "y=" << yold << "z=" << zold << "\n";
}
}
c1->AddExec("dynamic","DynamicExec()");
c2 = new TCanvas("rose515", "rotated", 600, 400);
c2->AddExec("dynamic","DynamicExec()");
h2->Draw("colz");
c3 = new TCanvas("rose516", "(tl-tr)/2-(bl-br)/2 vs (bl-br)/2", 600, 400);
h3->SetMaximum(5);
c3->AddExec("dynamic","DynamicExec()");
h3->Draw("colz");
TH1D *py = h3->ProjectionY("Y projection");
c4 = new TCanvas("rose517", "Y projection", 600, 400); 
py->Fit("gaus");
py->GetFunction("gaus")->SetLineColor(kRed);
py->GetFunction("gaus")->SetLineWidth(6);
c4->Update();
//MyFile->Close();

TFile *AdcFile = new TFile("adc.root","READ");
AdcFile->ls();   
c5 = new TCanvas("rose518","ADC histograms", 600, 800);
c5->Divide(2,3);
c5->cd(1);
TH1F *adctl = (TH1F*)AdcFile->Get("hist_a_tl");
adctl->Draw();
c5->cd(2);
TH1F *adctr = (TH1F*)AdcFile->Get("hist_a_tr");
adctr->Draw();
c5->cd(3);
TH1F *adcml = (TH1F*)AdcFile->Get("hist_a_ml");
adcml->Draw();
c5->cd(4);
TH1F *adcmr = (TH1F*)AdcFile->Get("hist_a_mr");
adcmr->Draw();
c5->cd(5);
TH1F *adcbl = (TH1F*)AdcFile->Get("hist_a_bl");
adcbl->Draw();
c5->cd(6);
TH1F *adcbr = (TH1F*)AdcFile->Get("hist_a_br");
adcbr->Draw();

/*
c1->cd(2);
TH1F *h = (TH1F*)MyFile->Get("hist_tdcDiff_top");
h->Draw(); 
short i,a,ib;
a = h->GetNbinsX();
//cout << a << "\n";
float y[50000],b,b1;
b=0;
b1=0;
ib=0;
for (i=1; i<=a; i++)
{
y[i]=h->GetBinContent(i);
if (i % 50 == 0) {
     if (b1 > b) {
          b=b1;
	  ib=i-25;
//          cout << "b = " << b << " i = " << i << "\n";
         }
          b1=0;
   }
else {
    b1=b1+y[i];
    }
//cout << "b = " << b/50. << " i = " << i << "\n";
}
gPad->GetCanvas()->Update();
//MyFile->Close();


float yleft=fabs(y[1]-b/100.);
int ileft=0;
for (i=1; i<=ib; i++)
{
if ((fabs(y[i]-b/100.))<yleft) {
yleft=fabs(y[i]-b/100.);
ileft=i;
}
}

float xleft=h->GetXaxis()->GetBinCenter(ileft);

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
float xright=h->GetXaxis()->GetBinCenter(iright);

TLine *line1 = new TLine(xleft,b/50.,xright,b/50.); 
line1->SetLineColor(2);
line1->SetLineWidth(3);
line1->Draw(); 



float xmed=h->GetXaxis()->GetBinCenter(ib);
float ymax=h->GetYaxis()->GetBinCenter(ib);
TLine *line2 = new TLine(xmed,0.,xmed,b/50.);
line2->SetLineColor(3);
line2->SetLineWidth(3);
line2->Draw();; 
//cout << "xmed = " << xmed << "\n";

//cout << xleft << "\n";
TLine *line3 = new TLine(xleft,0.,xleft,b/50.);
line3->SetLineColor(4);
line3->SetLineWidth(3);
line3->Draw(); 

//cout << xright << "\n";
TLine *line4 = new TLine(xright,0.,xright,b/50.);
line4->SetLineColor(4);
line4->SetLineWidth(3);
line4->Draw();;

*/ 

}
