Double_t poly3(Double_t *x, Double_t* par){
  Double_t fitval = par[0] + par[1]*x[0] + par[2]*x[0]*x[0] + par[3]*x[0]*x[0]*x[0]; 
  return fitval;
}
int plotADC(char* inputFile, bool fitSignal = false)
{
gStyle->SetOptStat("nemMrRuoi");
gStyle->SetOptFit(1111); //pcev
TObjArray* hists = GetHistograms(5001, 2, 2048, -0.5, 2048.5, inputFile);
TObjArray* hists_forOffset = GetHistograms(5001, 2, 2048, -0.5, 2048.5, inputFile);
//NOTE: Edit the 4th and 5th arguments to this function
//to set the minimum and maximum values to put into
//the histogram
TObjArray* hists_forSignal = GetHistograms(5001, 2, 2048.5-164.5, 164.5, 2048.5, inputFile);

TCanvas* canvas_ADC0 = new TCanvas("canvas_ADC0", "ADC Channel 0 spectrum");
canvas_ADC0->Divide(1,3);

TCanvas* canvas_ADC1 = new TCanvas("canvas_ADC1", "ADC Channel 1 spectrum");
canvas_ADC1->Divide(1,3);

canvas_ADC0->cd(1);
hists->At(0)->Draw();

canvas_ADC1->cd(1);
hists->At(1)->Draw();


TH1F* hist_offset0 = (*hists_forOffset)[0]->Clone("hist_offset0");
TH1F* hist_offset1 = (*hists_forOffset)[1]->Clone("hist_offset1");
hist_offset0->SetName("hist_offset0");
hist_offset0->SetTitle("offset0");
hist_offset0->GetXaxis()->SetRangeUser(1,74.5);
Float_t meanOffset0 = hist_offset0->GetMean();
hist_offset1->SetName("hist_offset1");
hist_offset1->SetTitle("offset1");
hist_offset1->GetXaxis()->SetRangeUser(1,124.5);
Float_t meanOffset1 = hist_offset1->GetMean();

canvas_ADC0->cd(2);
hist_offset0->Draw();
canvas_ADC1->cd(2);
hist_offset1->Draw();

TH1F* hist_signal0 = (TH1F*)(*hists_forSignal)[0]->Clone("hist_signal0");
TH1F* hist_signal1 = (TH1F*)(*hists_forSignal)[1]->Clone("hist_signal1");
hist_signal0->SetName("hist_signal0");
hist_signal0->SetTitle("offset+signal0");
hist_signal0->GetXaxis()->SetRangeUser(164.5,2048.5);
Float_t meanOffsetSignal0 = hist_signal0->GetMean();
hist_signal1->SetName("hist_signal1");
hist_signal1->SetTitle("offset+signal1");
hist_signal1->GetXaxis()->SetRangeUser(124.5,2048.5);
Float_t meanOffsetSignal1 = hist_signal1->GetMean();

canvas_ADC0->cd(3);
if (fitSignal){
  TF1* f_fit = new TF1("f_poly3", poly3, -164.5, 1200, 4);
  f_fit->SetParNames("p0", "p1", "p2", "p3");
  //hist_signal0->Fit("f_poly3");
  hist_signal0->Fit("f_poly3", "R");
}
hist_signal0->Draw("e1");
canvas_ADC1->cd(3);
hist_signal1->Draw();

cout <<"ADC 0: (Signal+offset)mean - Offset mean = " << meanOffsetSignal0 << " - " << meanOffset0 << " = " << meanOffsetSignal0 - meanOffset0 << endl; 
cout <<"ADC 1: (Signal+offset)mean - Offset mean = " << meanOffsetSignal1 << " - " << meanOffset1 << " = " << meanOffsetSignal1 - meanOffset1 << endl;

canvas_ADC1->Close(); //atrivedi 120512
return 0;

}
