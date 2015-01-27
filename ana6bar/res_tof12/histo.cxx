void histo(){
TFile *MyFile = new TFile("histo.root","READ");
MyFile->ls();   
c1 = new TCanvas("rose512", "examples of image manipulations", 300, 600);
c1->Divide(1,2);
c1->cd(1);
TH1F *h = (TH1F*)MyFile->Get("hist_tdcDiff_top");
h->Draw();
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

}
