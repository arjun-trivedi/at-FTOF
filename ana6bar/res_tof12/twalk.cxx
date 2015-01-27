void twalk(){
TFile *MyFile = new TFile("out_all.root","READ");
MyFile->ls();   
c1 = new TCanvas("rose512", "tw_tl", 800, 400);
c1->Divide(2,2);
c1->cd(1);

TH2F *h1 = (TH2F*)MyFile->Get("hist_tw_tl");
int minbin = h1->GetMinimumBin();
int nbinx = h1->GetNbinsX();
int nbiny = h1->GetNbinsY();
int minbinx = minbin%(nbinx+2);
int minbiny1 = ((minbin-minbinx)/(nbinx+2))%(nbiny+2);
float ymin1 = h1->GetYaxis()->GetBinCenter(minbiny1);
float xmin1 = h1->GetXaxis()->GetBinCenter(minbinx);

//cout << "ymin1 = " << ymin1 << "\n";
cout << "p1 = " << xmin1 << "\n";
// h->SetMaximum(5);
gStyle->SetPalette(1);
gStyle->SetOptStat(0);
gStyle->SetOptFit(1);
c1->cd(1)->SetLogz(0);
//h->Fit("pol1","0");

h1->Draw("colz");
TLine *line1 = new TLine(-2.,ymin1,6.,ymin1); 
TLine *line11 = new TLine(xmin1,-2.,xmin1,6.); 
        line1->SetLineColor(2);
        line1->SetLineWidth(3);
        line11->SetLineColor(2);
        line11->SetLineWidth(3);	
        line1->Draw();
	line11->Draw();


	
	


c1->cd(2);	
TH2F *h2 = (TH2F*)MyFile->Get("hist_tw_tr");
int minbin = h2->GetMinimumBin();
int nbinx = h2->GetNbinsX();
int nbiny = h2->GetNbinsY();
int minbinx = minbin%(nbinx+2);
int minbiny2 = ((minbin-minbinx)/(nbinx+2))%(nbiny+2);
float ymin2 = h2->GetYaxis()->GetBinCenter(minbiny2);
float xmin2 = h2->GetXaxis()->GetBinCenter(minbinx);

//cout << "ymin2 = " << ymin2 << "\n";
cout << "p2 = " << xmin2 << "\n";

h2->Draw("colz");
TLine *line2 = new TLine(-2.,ymin2,6.,ymin2);
TLine *line22 = new TLine(xmin2,-2.,xmin2,6.); 
        line2->SetLineColor(2);
        line2->SetLineWidth(3);
        line22->SetLineColor(2);
        line22->SetLineWidth(3);	
        line2->Draw();	
        line22->Draw();


	
	
c1->cd(3);	
TH2F *h3 = (TH2F*)MyFile->Get("hist_tw_bl");
int minbin = h3->GetMinimumBin();
int nbinx = h3->GetNbinsX();
int nbiny = h3->GetNbinsY();
int minbinx = minbin%(nbinx+2);
int minbiny3 = ((minbin-minbinx)/(nbinx+2))%(nbiny+2);
float ymin3 = h3->GetYaxis()->GetBinCenter(minbiny3);
float xmin3 = h3->GetXaxis()->GetBinCenter(minbinx);

//cout << "ymin3 = " << ymin3 << "\n";
cout << "p5 = " << xmin3 << "\n";

h3->Draw("colz");
TLine *line3 = new TLine(-2.,ymin3,6.,ymin3); 
TLine *line33 = new TLine(xmin3,-2.,xmin3,6.);
        line3->SetLineColor(2);
        line3->SetLineWidth(3);
        line33->SetLineColor(2);
        line33->SetLineWidth(3);	
        line3->Draw();
	line33->Draw();	
	
	
	

c1->cd(4);	
TH2F *h4 = (TH2F*)MyFile->Get("hist_tw_br");
int minbin = h4->GetMinimumBin();
int nbinx = h4->GetNbinsX();
int nbiny = h4->GetNbinsY();
int minbinx = minbin%(nbinx+2);
int minbiny4 = ((minbin-minbinx)/(nbinx+2))%(nbiny+2);
float ymin4 = h4->GetYaxis()->GetBinCenter(minbiny4);
float xmin4 = h4->GetXaxis()->GetBinCenter(minbinx);

//cout << "ymin4 = " << ymin4 << "\n";
cout << "p6 = " << xmin4 << "\n";


h4->Draw("colz");
TLine *line4 = new TLine(-2.,ymin4,6.,ymin4);
TLine *line44 = new TLine(xmin4,-2.,xmin4,6.); 
        line4->SetLineColor(2);
        line4->SetLineWidth(3);
	line44->SetLineColor(2);
        line44->SetLineWidth(3);
        line4->Draw();
	line44->Draw();	


float yavr = (ymin1+ymin2+ymin3+ymin4)/4.;
cout << "p3 = " << yavr << "\n";
TLine *line5 = new TLine(-2.,yavr,6.,yavr); 
        line5->SetLineColor(5);
        line5->SetLineWidth(3);
	c1->cd(1);
        line5->Draw();
	c1->cd(2);
        line5->Draw();
	c1->cd(3);
        line5->Draw();
	c1->cd(4);
        line5->Draw();
	
Int_t ybinavr = (minbiny1+minbiny2+minbiny3+minbiny4)/4.;
cout << "ybinavr = " << ybinavr << "\n";

c2 = new TCanvas("rose513", "tw_mdl", 800, 400);
c2->Divide(2,1);
c2->cd(1);
TH2F *h5 = (TH2F*)MyFile->Get("hist_mtw_mr");
h5->Draw("colz");
line5->Draw();

TH1F *h6 = (TH1F*) h5->ProjectionX("",ybinavr,ybinavr);
c2->cd(2);
h6->Draw();
int minbin = h6->GetMinimumBin();
float xmin6 = h6->GetXaxis()->GetBinCenter(minbin);
float ymax6 = h6->GetMaximum();
float ymin6 = h6->GetMinimum();
TLine *line6 = new TLine(xmin6,ymin6,xmin6,ymax6); 
        line6->SetLineColor(2);
        line6->SetLineWidth(3);
	line6->Draw();
	
c2->cd(1);
TLine *line7 = new TLine(xmin6,-2.,xmin6,6.); 
        line7->SetLineColor(2);
        line7->SetLineWidth(3);
	line7->Draw();	
cout << "p4 = " << xmin6 << "\n";

TFile *MyFile1 = new TFile("out_all_resolution.root","READ");
MyFile1->ls();   
c3 = new TCanvas("rose514", "resolution", 800, 400);			
TH2F *h7 = (TH2F*)MyFile1->Get("hist_c3barRes");

h7->Draw();










/*

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
TH2F *adctl = (TH2F*)AdcFile->Get("hist_a_tl");
adctl->Draw();
c5->cd(2);
TH2F *adctr = (TH2F*)AdcFile->Get("hist_a_tr");
adctr->Draw();
c5->cd(3);
TH2F *adcml = (TH2F*)AdcFile->Get("hist_a_ml");
adcml->Draw();
c5->cd(4);
TH2F *adcmr = (TH2F*)AdcFile->Get("hist_a_mr");
adcmr->Draw();
c5->cd(5);
TH2F *adcbl = (TH2F*)AdcFile->Get("hist_a_bl");
adcbl->Draw();
c5->cd(6);
TH2F *adcbr = (TH2F*)AdcFile->Get("hist_a_br");
adcbr->Draw();


c1->cd(2);
TH2F *h = (TH2F*)MyFile->Get("hist_tdcDiff_top");
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

