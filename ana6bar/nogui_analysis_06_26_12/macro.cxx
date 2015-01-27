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
#include "macro.h"
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
#include <TGraphErrors.h>
#include <TLatex.h>
#include <TCanvas.h>

 using namespace std; 
 

    
TMacro* macro::ADC_plot(const char* name, Double_t xmin, Double_t ymax) {
//TMacro* bb = new TMacro(name);
std::stringstream out[15];
out[14]<< name<< "_plot";
TMacro* bb = new TMacro(out[14].str().c_str());
out[11] << "void " << out[14].str().c_str() << "() {";
bb->AddLine(out[11].str().c_str()); 
out[0] << "TCanvas *" << name << "_canvas" << " = new TCanvas(\"" << name << "_canvas"<< "\",\""<< name << "_canvas"<<"\",600,600);";
bb->AddLine(out[0].str().c_str());
out[1] << name << "_canvas" << "->cd();";
bb->AddLine(out[1].str().c_str());
out[2] << name << "->Draw();";
bb->AddLine(out[2].str().c_str());
out[3] << "TLine *line_left = new TLine(" << xmin << ",0.," << xmin << "," << ymax << ");"; 
bb->AddLine(out[3].str().c_str());
out[4] << "line_left->SetLineColor(2);";
bb->AddLine(out[4].str().c_str());
out[5] << "line_left->SetLineWidth(3);";
bb->AddLine(out[5].str().c_str());
out[6] << "line_left->Draw();";
bb->AddLine(out[6].str().c_str());
out[12] << "};";
bb->AddLine(out[12].str().c_str());
return bb;
};         
     

TH1*  macro::Smooth_fun(TH1 *h, Double_t bin_num) {
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


    Double_t macro::myFunction(TH1 *h) {
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

TMacro* macro::TDC_plot(const char* name, Double_t xmin, Double_t xmax, Double_t ymax) {
//TMacro* bb = new TMacro(name);
std::stringstream out[15];
out[14]<< name<< "_plot";
TMacro* bb = new TMacro(out[14].str().c_str());
out[11] << "void " << out[14].str().c_str() << "() {";
bb->AddLine(out[11].str().c_str()); 
out[0] << "TCanvas *" << name << "_canvas" << " = new TCanvas(\"" << name << "_canvas"<< "\",\""<< name << "_canvas"<<"\",600,600);";
bb->AddLine(out[0].str().c_str());

out[11].str("");
out[11] << "gStyle->Reset();";
bb->AddLine(out[11].str().c_str());
out[11].str("");

out[1] << name << "_canvas" << "->cd();";
bb->AddLine(out[1].str().c_str());
out[2] << name << "->Draw();";
bb->AddLine(out[2].str().c_str());
out[3] << "TLine *line_left = new TLine(" << xmin << ",0.," << xmin << "," << ymax << ");"; 
bb->AddLine(out[3].str().c_str());
out[4] << "line_left->SetLineColor(2);";
bb->AddLine(out[4].str().c_str());
out[5] << "line_left->SetLineWidth(3);";
bb->AddLine(out[5].str().c_str());
out[6] << "line_left->Draw();";
bb->AddLine(out[6].str().c_str());
out[7] << "TLine *line_right = new TLine(" << xmax << ",0.," << xmax << "," << ymax << ");"; 
bb->AddLine(out[7].str().c_str());
out[8] << "line_right->SetLineColor(2);";
bb->AddLine(out[8].str().c_str());
out[9] << "line_right->SetLineWidth(3);";
bb->AddLine(out[9].str().c_str());
out[10] << "line_right->Draw();";
bb->AddLine(out[10].str().c_str());
out[12] << "};";
bb->AddLine(out[12].str().c_str());
return bb;
};     
void macro::TDC_write(const char* name, const char* _out_dir, TH1D *hist, Double_t xmin, Double_t xmax, Double_t ymax, TCanvas* &c1) {

c1->cd(6);

gStyle->Reset();
hist->Draw();
TLine *line_left = new TLine(xmin,0.,xmin,ymax);
line_left->SetLineColor(2);
line_left->SetLineWidth(3);
line_left->Draw();
TLine *line_right = new TLine(xmax,0.,xmax,ymax);
line_right->SetLineColor(2);
line_right->SetLineWidth(3);
line_right->Draw();


//	line_left->Delete();
//	line_right->Delete();	
};

TMacro* macro::PositionCut_plot(char* name, Double_t mean, Double_t sigma) {
std::stringstream out[15];
out[14]<< name<< "_plot";
TMacro* bb = new TMacro(out[14].str().c_str());
out[11] << "void " << out[14].str().c_str() << "() {";
bb->AddLine(out[11].str().c_str());
out[11].str("");

out[11] << "gStyle->Reset();";
bb->AddLine(out[11].str().c_str());
out[11].str("");
 
out[0] << "TCanvas *" << name << "_canvas" << " = new TCanvas(\"" << name << "_canvas"<< "\",\""<< name << "_canvas"<<"\",600,600);";
bb->AddLine(out[0].str().c_str());
out[1] << name << "_canvas" << "->cd();";
bb->AddLine(out[1].str().c_str());
out[2] << name << "->Draw(\"colz\");";

bb->AddLine(out[2].str().c_str());

out[3] << "gStyle->SetPalette(1);";
bb->AddLine(out[3].str().c_str());

out[4] << "int xmin = " << name << "->GetBinLowEdge(1);";
bb->AddLine(out[4].str().c_str());



out[6] << "int xmax_bin = " <<  name << "->GetNbinsX();";
bb->AddLine(out[6].str().c_str());

out[7] << "int xmax = " << name << "->GetBinLowEdge(xmax_bin);";
bb->AddLine(out[7].str().c_str());

out[7] << "int diff = (xmax - xmin)/6;";
bb->AddLine(out[7].str().c_str());
out[7].str( std::string() );
out[7].clear();

out[7] << "xmin = xmin + diff;";
bb->AddLine(out[7].str().c_str());
out[7].str( std::string() );
out[7].clear();

out[7] << "xmax = xmax - diff;";
bb->AddLine(out[7].str().c_str());
out[7].str( std::string() );
out[7].clear();



out[8] << "TLine *line_left = new TLine(" << "xmin" << ",xmin+" << mean+sigma << "," << "xmax" << ",xmax+" << mean+sigma << ");"; 
bb->AddLine(out[8].str().c_str());
out[9] << "line_left->SetLineColor(2);";
bb->AddLine(out[9].str().c_str());
out[10] << "line_left->SetLineWidth(3);";
bb->AddLine(out[10].str().c_str());

out[11].str( std::string() );
out[11].clear();
out[11] << "line_left->Draw();";
bb->AddLine(out[11].str().c_str());

out[11].str( std::string() );
out[11].clear();
out[11] << "TLine *line_right = new TLine(" << "xmin" << ",xmin+" << mean-sigma << "," << "xmax" << ",xmax+" << mean-sigma << ");"; 
bb->AddLine(out[11].str().c_str());


out[11].str( std::string() );
out[11].clear();
out[11] << "line_right->SetLineColor(2);";
bb->AddLine(out[11].str().c_str());


out[11].str( std::string() );
out[11].clear();
out[11] << "line_right->SetLineWidth(3);";
bb->AddLine(out[11].str().c_str());


out[11].str( std::string() );
out[11].clear();
out[11] << "line_right->Draw();";
bb->AddLine(out[11].str().c_str());


/*
out[7] << "TLine *line_right = new TLine(" << xmax << ",0.," << xmax << "," << ymax << ");"; 
bb->AddLine(out[7].str().c_str());
out[8] << "line_right->SetLineColor(2);";
bb->AddLine(out[8].str().c_str());
out[9] << "line_right->SetLineWidth(3);";
bb->AddLine(out[9].str().c_str());
out[10] << "line_right->Draw();";
bb->AddLine(out[10].str().c_str()); */
out[12] << "};";
bb->AddLine(out[12].str().c_str()); 
return bb; 
};     

void macro::PositionCut_write(char* name, const char* _out_dir, Double_t mean, Double_t sigma, TH2D *hist_diff1vsdiff6) {
stringstream ss; ss.str("");
ss << name << "_canvas";       
	TCanvas *c1 = new TCanvas(ss.str().c_str(), ss.str().c_str(), 600, 600);
	c1->cd();	
hist_diff1vsdiff6->Draw("colz");
	gStyle->SetPalette(1);
	int xmin = hist_diff1vsdiff6->GetBinLowEdge(1);
	int xmax_bin = hist_diff1vsdiff6->GetNbinsX();
	int xmax = hist_diff1vsdiff6->GetBinLowEdge(xmax_bin);
	int diffn = (xmax - xmin)/6;
	xmin = xmin + diffn;
	xmax = xmax - diffn;
	TLine *line_left = new TLine(xmin,xmin+mean+sigma,xmax,xmax+mean+sigma);
	line_left->SetLineColor(2);
	line_left->SetLineWidth(3);
	line_left->Draw();
	TLine *line_right = new TLine(xmin,xmin+mean-sigma,xmax,xmax+mean-sigma);
	line_right->SetLineColor(2);
	line_right->SetLineWidth(3);
	line_right->Draw();
	
	
	ss.str("");
        ss << _out_dir << name << ".png";		
	c1->Print(ss.str().c_str());
	c1->Close();
	line_right->Delete();
	line_left->Delete();
	
	
	
	
	
	
	
	
	
};

TMacro* macro::resol_cont_plot(char* name) {
std::stringstream out;


out<< "resol" << name << "_plot";
TMacro* bb = new TMacro(out.str().c_str());
out.str("");

out << "void resol" << name << "_plot() {";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "gStyle->Reset();";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "gStyle->SetHistLineWidth(3);";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "gStyle->SetHistLineWidth(3);";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "gStyle->SetLineWidth(3);";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "gStyle->SetFrameLineWidth(3);";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "gPad->SetLineWidth(3);";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "gStyle->SetTitleH(0.09);";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "gStyle->SetTitleW(0.65);";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "gStyle->SetOptStat(0);";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "TCanvas *resol" << name << "_canvas = new TCanvas(\"resol" << name << "_canvas\",\"resol" << name << "_canvas\",800,600);";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "resol" << name << "_canvas->Divide(3,2);";
bb->AddLine(out.str().c_str()); 
out.str("");


char* histname[6];
histname[0] = "_1_2_3";
histname[1] = "_2_3_4";
histname[2] = "_3_4_5";
histname[3] = "_4_5_6";
histname[4] = "_1_3_5";
histname[5] = "_2_4_6";

short i;

for ( i=0; i<6; i++) {

out << "resol" << name << "_canvas->cd(" << i+1 << ");";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "resol" << name << "_canvas->cd(" << i+1 << ")" << "->SetLeftMargin(0.15);";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "resol" << name << "_canvas->cd(" << i+1 << ")" << "->SetRightMargin(0.05);";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "resol" << name << "_canvas->cd(" << i+1 << ")" << "->SetBottomMargin(0.14);";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "resol" << histname[i] << name << "->GetXaxis()->SetNdivisions(5);";
bb->AddLine(out.str().c_str()); 
out.str("");



out << "resol" << histname[i] << name << "->Draw(\"e1p\");";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "resol" << histname[i] << name << "->SetMarkerStyle(20);";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "resol" << histname[i] << name << "->SetLabelSize( 0.07, \"X\" );";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "resol" << histname[i] << name << "->SetLabelOffset(0.01, \"X\");";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "resol" << histname[i] << name << "->SetLabelSize( 0.07, \"Y\" );";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "resol" << histname[i] << name << "->SetLabelOffset(0.01, \"Y\");";
bb->AddLine(out.str().c_str()); 
out.str("");

};

out << "};";
bb->AddLine(out.str().c_str()); 
out.str("");


return bb; 
};     

void macro::resol_cont_write(char* name,  const char* _out_dir, TH1D* hist[6]) {
std::stringstream ss;
ss << name << "_canvas";       
	TCanvas *c1 = new TCanvas(ss.str().c_str(), ss.str().c_str(), 800, 600);
	c1->cd();
	
gStyle->Reset();
gStyle->SetHistLineWidth(3);
gStyle->SetHistLineWidth(3);
gStyle->SetLineWidth(3);
gStyle->SetTitleH(0.09);
gStyle->SetTitleW(0.65);
gStyle->SetOptStat(0);
	
c1->Divide(3,2);	


short i;

for ( i=0; i<6; i++) {
	
c1->cd(i+1)->SetFrameLineWidth(3);

c1->cd(i+1)->SetLineWidth(3);
c1->cd(i+1);
c1->cd(i+1)->SetLeftMargin(0.15);
c1->cd(i+1)->SetRightMargin(0.05);
c1->cd(i+1)->SetBottomMargin(0.14);
hist[i]->GetXaxis()->SetNdivisions(5);
hist[i]->Draw("e1p");
hist[i]->SetMarkerStyle(20);
hist[i]->SetLabelSize( 0.07, "X" );
hist[i]->SetLabelOffset(0.01, "X");
hist[i]->SetLabelSize( 0.07, "Y" );
hist[i]->SetLabelOffset(0.01, "Y");

	
	
};	


	ss.str("");
        ss << _out_dir << name << ".png";		
	c1->Print(ss.str().c_str());
	c1->Close();
	
	
			
	
	
};

TMacro* macro::tw_params_plot() {
std::stringstream out;


out<< "tw" <<  "_params";
TMacro* bb = new TMacro(out.str().c_str());
out.str("");

out << "void tw" <<  "_params() {";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "gStyle->Reset();";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "gStyle->SetHistLineWidth(3);";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "gStyle->SetHistLineWidth(3);";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "gStyle->SetLineWidth(3);";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "gStyle->SetFrameLineWidth(3);";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "gPad->SetLineWidth(3);";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "gStyle->SetTitleH(0.09);";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "gStyle->SetTitleW(0.65);";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "gStyle->SetOptStat(0);";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "gStyle->SetOptFit(0);";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "TCanvas *tw_params" << "_canvas = new TCanvas(\"tw_params" <<  "_canvas\",\"tw_params" << "_canvas\",800,600);";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "tw" << "_params_canvas->Divide(4,3);";
bb->AddLine(out.str().c_str()); 
out.str("");




short i;

for ( i=0; i<=11; i++) {

out << "tw" <<  "_params_canvas->cd(" << i+1 << ");";
bb->AddLine(out.str().c_str()); 
out.str("");



out << "lambda_" << i+1 << "->Draw(\"e1p\");";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "Int_t nbins = lambda_" << i+1 << "->GetNbinsX();";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "TF1 *twfit" << i+1 << "= new TF1(\"twfit" << i+1 << "\",\"pol2\",lambda_" << i+1 << "->GetBinLowEdge(1),lambda_" << i+1 << "->GetBinLowEdge(nbins)+lambda_" << i+1 << "->GetBinWidth(nbins));";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "twfit" << i+1 << "->SetParLimits(2,0.,10.);"; 
bb->AddLine(out.str().c_str()); 
out.str("");

out << "lambda_" << i+1 << "->Fit(twfit" << i+1 << ",\"QL\");";
bb->AddLine(out.str().c_str()); 
out.str("");

out <<  "lambda_" << i+1 << "->SetMarkerStyle(20);";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "lambda_" << i+1 <<  "->SetLabelSize( 0.07, \"X\" );";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "lambda_" << i+1 <<  "->SetLabelOffset(0.01, \"X\");";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "lambda_" << i+1 <<  "->SetLabelSize( 0.07, \"Y\" );";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "lambda_" << i+1 <<  "->SetLabelOffset(0.01, \"Y\");";
bb->AddLine(out.str().c_str()); 
out.str("");

};

out << "};";
bb->AddLine(out.str().c_str()); 
out.str("");


return bb; 
};    


void macro::tw_params_write(TH1D* lambda1dn[12], const char* _out_dir) {
stringstream ss; 
ss.str("");


gStyle->Reset();
gStyle->SetHistLineWidth(3);
gStyle->SetHistLineWidth(3);
gStyle->SetLineWidth(3);
gStyle->SetFrameLineWidth(3);

gStyle->SetTitleH(0.09);
gStyle->SetTitleW(0.65);
gStyle->SetOptStat(0);
gStyle->SetOptFit(0);

TF1 *twfit[12];


ss <<  "tw_params_canvas";       
	TCanvas *c1 = new TCanvas(ss.str().c_str(), ss.str().c_str(), 800, 600);
	c1->cd();
	c1->Divide(4,3);
	short i;


	
for ( i=0; i<=11; i++) {



c1->cd(i+1);
c1->GetPad(i+1)->SetLineWidth(3);
c1->cd(i+1)->SetLineWidth(3);
lambda1dn[i]->Draw("e1p");

Int_t nbins = lambda1dn[i]->GetNbinsX();
ss.str("");
ss <<  "twfit" << i; 
twfit[i] = new TF1(ss.str().c_str(),"pol2",lambda1dn[i]->GetBinLowEdge(1),lambda1dn[i]->GetBinLowEdge(nbins)+lambda1dn[i]->GetBinWidth(nbins));
twfit[i]->SetParLimits(2,0.,10.);
lambda1dn[i]->Fit(twfit[i],"QL");
lambda1dn[i]->SetMarkerStyle(20);
lambda1dn[i]->SetLabelSize( 0.07, "X" );
lambda1dn[i]->SetLabelOffset(0.01, "X");
lambda1dn[i]->SetLabelSize( 0.07, "Y" );
lambda1dn[i]->SetLabelOffset(0.01, "Y");
};	
	
	
	ss.str("");
        ss << _out_dir << "tw_params" << ".png";		
	c1->Print(ss.str().c_str());
	c1->Close();
for ( i=0; i<=11; i++) {	
	twfit[i]->Delete();
	};	

};
 

TMacro* macro::tw_params_plot_new() {
std::stringstream out;


out<< "tw" <<  "_params_new";
TMacro* bb = new TMacro(out.str().c_str());
out.str("");

out << "void tw" <<  "_params_new() {";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "gStyle->Reset();";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "gStyle->SetHistLineWidth(3);";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "gStyle->SetHistLineWidth(3);";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "gStyle->SetLineWidth(3);";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "gStyle->SetFrameLineWidth(3);";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "gPad->SetLineWidth(3);";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "gStyle->SetTitleH(0.09);";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "gStyle->SetTitleW(0.65);";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "gStyle->SetOptStat(0);";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "gStyle->SetOptFit(0);";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "TCanvas *tw_params_new" << "_canvas = new TCanvas(\"tw_params_new" <<  "_canvas\",\"tw_params_new" << "_canvas\",800,600);";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "tw" << "_params_new_canvas->Divide(4,3);";
bb->AddLine(out.str().c_str()); 
out.str("");




short i;

for ( i=0; i<=11; i++) {

out << "tw" <<  "_params_new_canvas->cd(" << i+1 << ");";
bb->AddLine(out.str().c_str()); 
out.str("");



out << "lambda_" << i+1 << "_new->Draw(\"e1p\");";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "Int_t nbins = lambda_" << i+1 << "_new->GetNbinsX();";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "TF1 *twfit" << i+1 << "= new TF1(\"twfit" << i+1 << "\",\"pol2\",lambda_" << i+1 << "_new->GetBinLowEdge(1),lambda_" << i+1 << "_new->GetBinLowEdge(nbins)+lambda_" << i+1 << "_new->GetBinWidth(nbins));";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "twfit" << i+1 << "->SetParLimits(2,0.,10.);"; 
bb->AddLine(out.str().c_str()); 
out.str("");

out << "lambda_" << i+1 << "_new->Fit(twfit" << i+1 << ",\"QL\");";
bb->AddLine(out.str().c_str()); 
out.str("");

out <<  "lambda_" << i+1 << "_new->SetMarkerStyle(20);";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "lambda_" << i+1 <<  "_new->SetLabelSize( 0.07, \"X\" );";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "lambda_" << i+1 <<  "_new->SetLabelOffset(0.01, \"X\");";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "lambda_" << i+1 <<  "_new->SetLabelSize( 0.07, \"Y\" );";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "lambda_" << i+1 <<  "_new->SetLabelOffset(0.01, \"Y\");";
bb->AddLine(out.str().c_str()); 
out.str("");

};

out << "};";
bb->AddLine(out.str().c_str()); 
out.str("");


return bb; 
};     

TMacro* macro::att_plot(const char* name) {
std::stringstream out;


out<<  name << "_plot";
TMacro* bb = new TMacro(out.str().c_str());
out.str("");

out << "void " << name <<  "_plot() {";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "ostringstream out;";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "gStyle->SetOptFit(0);";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "gStyle->SetOptStat(0);";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "Double_t par[8];";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "short npoints = " << name << "->GetN();";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "Double_t *yval, *xval;";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "yval = " << name << "->GetY();";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "xval = " << name << "->GetX();";
bb->AddLine(out.str().c_str()); 
out.str("");


out << "TF1 *g1    = new TF1(\"g1\",\"expo\",xval[0]-5.,xval[npoints-1]+5.);";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "TF1 *g2    = new TF1(\"g2\",\"expo+[2]\",xval[0]-5.,xval[npoints-1]+5.);";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "TF1 *g3 = new TF1(\"g3\",\"expo(0)+expo(2)\",xval[0]-5.,xval[npoints-1]+5.);";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "g2->SetLineColor(3);";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "g3->SetLineColor(2);";
bb->AddLine(out.str().c_str()); 
out.str("");

out << name << "->Draw(\"AP\");";
bb->AddLine(out.str().c_str()); 
out.str("");

out << name << "->Fit(g1,\"S0QWR\");";
bb->AddLine(out.str().c_str()); 
out.str("");

out << name << "->Fit(g2,\"S0QWR+\");";
bb->AddLine(out.str().c_str()); 
out.str("");

out << name << "->Fit(g3,\"S0QWR+\");";
bb->AddLine(out.str().c_str()); 
out.str("");

out << name << "->Fit(g3,\"SQWR+\");";
bb->AddLine(out.str().c_str()); 
out.str("");


out << "out << \"#lambda_{fit} = \" << fabs(1./(g3->GetParameter(1))) << \" cm\" << \"\n\";";
bb->AddLine(out.str().c_str()); 
out.str("");




out << "Float_t max,min;";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "if (yval[npoints-1]>yval[0]) {";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "max = yval[npoints-1];";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "min = yval[0];";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "} else {";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "max =yval[0];";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "min =yval[npoints-1];";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "};";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "TLatex text;";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "text.SetTextSize(0.07);";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "if (npoints > 4) {";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "text.DrawLatex((xval[npoints-1])/4.,max,out.str().c_str());";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "out.str(\"\");";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "out << \"#lambda_{th} = \" << fabs(1./(g3->GetParameter(3))) << \" cm\" << \"\n\";";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "text.DrawLatex((xval[npoints-1])/4.,max-(max-min)*0.09,out.str().c_str());";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "out.str(\"\");";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "out << \"#lambda_{2 points} = \" << fabs((xval[npoints-2]-xval[1])/(log(fabs(yval[1]/yval[npoints-2])))) <<  \" cm\" << \"\n\";";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "text.DrawLatex((xval[npoints-1])/4.,max-(max-min)*0.18,out.str().c_str());";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "out.str(\"\");";
bb->AddLine(out.str().c_str()); 
out.str("");



out << "out.str(\"\");";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "} else {;";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "out.str(\"\");";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "out << \"#lambda_{2 points} = \" << fabs((xval[npoints-1]-xval[0])/(log(fabs(yval[0]/yval[npoints-1])))) <<  \" cm\" << \"\n\";";
bb->AddLine(out.str().c_str()); 
out.str("");

out << "text.DrawLatex((xval[npoints-1])/2.,max-(max-min)*0.18,out.str().c_str());";
bb->AddLine(out.str().c_str()); 
out.str("");








out << "};";
bb->AddLine(out.str().c_str()); 
out.str("");


out << "};";
bb->AddLine(out.str().c_str()); 
out.str("");

return bb; 
};     

void macro::att_write(const char* name, const char* _out_dir, TGraphErrors *Tg_max, TCanvas* &c1, Short_t k, Float_t &twopoints) {

stringstream ss; 
stringstream out;
ss.str("");
out.str("");

// ss << name <<  "_canvas";       
//	TCanvas *c1 = new TCanvas(ss.str().c_str(), ss.str().c_str(), 800, 600);
	c1->cd(k+1);

gStyle->SetOptFit(0);
gStyle->SetOptStat(0);
Double_t par[8];

short npoints = Tg_max->GetN();
Double_t *yval, *xval;

yval = Tg_max->GetY();
xval = Tg_max->GetX();

TF1 *g1    = new TF1("g1","expo",xval[0]-5.,xval[npoints-1]+5.);

TF1 *g2    = new TF1("g2","expo+[2]",xval[0]-5.,xval[npoints-1]+5.);

TF1 *g3 = new TF1("g3","expo(0)+expo(2)",xval[0]-5.,xval[npoints-1]+5.);

g2->SetLineColor(3);

g3->SetLineColor(2);





Tg_max->Draw("AP");

Tg_max->Fit(g1,"S0QWR");

Tg_max->Fit(g2,"S0QWR+");

Tg_max->Fit(g3,"S0QWR+");

Tg_max->Fit(g3,"SQWR+");


out << "#lambda_{fit} = " << fabs(1./(g3->GetParameter(1))) << " cm" << "\n";TLatex text;



Float_t max,min;

if (yval[npoints-1]>yval[0]) {

max = yval[npoints-1];

min = yval[0];

} else {

max =yval[0];

min =yval[npoints-1];

};


text.SetTextSize(0.07);

if (npoints > 4) {

text.DrawLatex((xval[npoints-1])/4.,max,out.str().c_str());

out.str("");

out << "#lambda_{th} = " << fabs(1./(g3->GetParameter(3))) << " cm" << "\n";

text.DrawLatex((xval[npoints-1])/4.,max-(max-min)*0.09,out.str().c_str());

out.str("");


out << "#lambda_{2 points} = " << fabs((xval[npoints-2]-xval[1])/(log(fabs(yval[1]/yval[npoints-2])))) <<  " cm" << "\n";

twopoints = fabs((xval[npoints-2]-xval[1])/(log(fabs(yval[1]/yval[npoints-2]))));

text.DrawLatex((xval[npoints-1])/4.,max-(max-min)*0.18,out.str().c_str());

out.str("");

} else {
out.str("");
out << "#lambda_{2 points} = " << fabs((xval[npoints-1]-xval[0])/(log(fabs(yval[0]/yval[npoints-1])))) <<  " cm" << "\n";

twopoints = fabs((xval[npoints-1]-xval[0])/(log(fabs(yval[0]/yval[npoints-1]))));
text.DrawLatex((xval[npoints-1])/2.,max-(max-min)*0.18,out.str().c_str());

out.str("");
};


/*out.str("");

	ss.str("");
        ss << _out_dir << "/" << name << ".png";		
	c1->Print(ss.str().c_str());
	c1->Close();
*/

};
