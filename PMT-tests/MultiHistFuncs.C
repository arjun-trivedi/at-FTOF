#include <math.h>

TObjArray* GetHistograms(Int_t deviceId = 5002,
			 Int_t numChannels = 8,
			 Int_t numBins = 2250,
			 Double_t histStart = -.5,
			 Double_t histStop = 2249.5,
			 char* fileName = "data.txt",
                         char* prefix = "",
			 int debug = 1)
{

  TObjArray* myHists = new TObjArray();

  if (debug) cout << "numChannels: " << numChannels << endl
                  << "deviceId: " << deviceId << endl
                  << "histStart: " << histStart << endl
                  << "histStop: " << histStop << endl
                  << "numBins: " << numBins << endl;

  for (int i = 0; i < numChannels; i++) {
    strstream histName;
    
    histName << prefix << " CH" << i+1;

    char* hn = histName.str().c_str();
    
    //if (debug) cout << "histName: " << hn << endl;
   
    TH1F *tHist = new TH1F(hn,hn,numBins,histStart,histStop);

    if (debug) cout << "... Created!" << endl;
 
    myHists->Add(tHist);

    //if (debug) cout << "Added " << hn << " to myHists." << endl;
  }

  if (debug) cout << "myHists has " << myHists->GetEntries()
                  << " histograms." << endl;

  ifstream in;

  in.open(fileName);
  if (debug) cout << "Opened " << fileName << endl;

  Int_t maxLineLength = 1024;
  Int_t nlines = 0;
  while (1) {
    Int_t id;
    in >> id;
    if (!in.good()) break;

    //if (debug) cout << "+++++++++ " << id << endl;
    if (id != deviceId) {
      in.ignore(maxLineLength,'\n');
      continue;
    }

    for (int i = 0; i < numChannels; i++) {
      Int_t val;
      in >> val;
      //if (debug) cout << "********* " << val << endl;
      TH1F* tHist2 = (*myHists)[i];
      tHist2->Fill(val);
    }
    //ignore any remaining data on the line
    in.ignore(maxLineLength,'\n');
    nlines++;
  }

  cout << "Total Readings: " << nlines << endl;

  in.close();
 
  if (debug) {
    cout << "Returning myHists:" << endl;
    myHists->Print();
  }

  return myHists;

}

void Draw(TObjArray& hists, Int_t numCols = 4)
{
  TCanvas *c1 = new TCanvas("c1", "c1");
  Int_t numChannels = hists.GetEntries();
  printf("numHists=%i\n",numChannels);
  Int_t leftOver = numChannels%numCols;
  Int_t numRows =  (Int_t)numChannels/numCols + (leftOver > 0);

  c1->Divide(numCols,numRows);

  for (int i = 0; i < numChannels; i++) {
    c1->cd(i+1);
    TH1F* tHist = hists[i];
    tHist->Draw("][");
  }
}

void DrawMore(TH1F& hist, TCanvas& c1, Int_t cellNum, Int_t colorId)
{
  c1.cd(cellNum);
  hist.SetFillColor(colorId);
  hist.Draw("same");
}

void DrawMore(TObjArray& hists, TCanvas& c1, Int_t colorId)
{
  Int_t numChannels = hists.GetEntries();
  for (int i = 0; i < numChannels; i++) {
    TH1F* tHist = hists[i];
    DrawMore(*tHist, c1, i+1, colorId);
  }
}

void DrawSeparate(TObjArray& hists)
{
  Int_t numChannels = hists.GetEntries();

  for (int i = 0; i < numChannels; i++) {
    strstream canvasName;
    canvasName << "Canvas" << i;

    char* cn = canvasName.str().c_str();
    TCanvas *c1 = new TCanvas(cn, cn);
    c1->cd();
    TH1F* tHist = hists[i];
    tHist->Draw("][");
  }
}

void SetAllMaxs(TObjArray& hists, Int_t max) {
  for (int i = 0; i < hists.GetEntries(); i++) {
    TH1F* hist = hists[i];
    hist->SetMaximum(max);
  }
}

void SetAllRanges(TObjArray& hists, Int_t min, Int_t max)
{
  for (int i = 0; i < hists.GetEntries(); i++) {
    TH1F* hist = hists[i];
    TAxis* x = hist->GetXaxis();
    x->SetRange(min,max);
  }
  
}

void ZoomToPeak(TObjArray& hists, Int_t skip = -1)
{
  for (int i = 0; i < hists.GetEntries(); i++) {
    TH1F* hist = hists[i];
    Double_t mean = hist->GetMean();
    if (mean < 4095 && i != skip) {
      TAxis* x = hist->GetXaxis();
      x->SetRange(mean-6,mean+6);
    }
  }
}

/* Currently, Cleanup will fail if one of the elements
   is null. */
void Cleanup(TObjArray& hists)
{
  for (int i = 0; i < hists.GetEntries(); i++) {
    cout << i << endl;
    TH1F* hist = hists[i];
    delete hist;
  }
  hists.Clear();
}

Double_t GetMean(int n, Stat_t vals[]) {
  Double_t sum = 0;
  for (int i = 0; i < n; i++) {
    sum += vals[i];
  }
  return sum/n;
}

Double_t GetSD(int n, Stat_t vals[]) {
  Double_t sd = 0;
  Double_t mean = GetMean(n,vals);
  for (int i = 0; i < n; i++) {
    sd += pow(vals[i]-mean,2);
  }
  return sd;
}

Double_t GetCovariance(int n, Stat_t x[], Stat_t y[]) {
  Double_t covar = 0;
  Double_t xmean = GetMean(n,x);
  Double_t ymean = GetMean(n,y);
  for (int i = 0; i < n; i++) {
    covar += (x[i]-xmean)*(y[i]-ymean);
  }
  return covar;
}

Double_t GetCorrCoeff(int n, Stat_t x[], Stat_t y[]) {
  return GetCovariance(n,x,y)/sqrt(GetSD(n,x)*GetSD(n,y));
}

Stat_t GetTotalDelay(int i, Stat_t clengths[]) {
  Stat_t delay = 10.7173+12.292643; //2.3853443;
  while (i >= 0) {
    delay += clengths[i--];
  }
  return delay;
}

TGraph* GetSimpleLinearityGraph() {

gROOT->Reset();
gStyle->SetOptStat(1110011);
gStyle->SetOptFit(1);

int numPeaks = 10;

  Stat_t meanVals[] = {0,0,0,0,0,0,0,0,0,0};
  Stat_t cableLengths[] = {12.428, 12.415, 12.346, 12.515, 12.540, 12.622, 12.443, 12.403, 12.434,                                   12.243};
  Stat_t delayVals[] = {0,0,0,0,0,0,0,0,0,0};
  
  for (int i = 0; i < numPeaks; i++) {
    delayVals[i] = GetTotalDelay(i,cableLengths);
  }
  
  /* read tdc data */
  TObjArray* hists = GetHistograms(5003,16,4093,1.5,4094.5,"20060808_calibration.dat","PH");
  TH1F* ph1 = (TH1F*)((*hists)[0])->Clone("ph ch1");
  TH1F* ph5 = (TH1F*)((*hists)[4])->Clone("ph ch5");
  TH1F* ph9 = (TH1F*)((*hists)[8])->Clone("ph ch9");
  TH1F* ph13 = (TH1F*)((*hists)[12])->Clone("ph ch13");
  
  // Cleanup(*hists);
  // hists = GetHistograms(5002,4,2049,-.5,2048.5,"20060808_calibration.dat","LC");
  // TH1F* lc_1 = (TH1F*)((*hists)[0])->Clone("lc ch1");
  // TH1F* lc_2 = (TH1F*)((*hists)[1])->Clone("lc ch2");
  // TH1F* lc_3 = (TH1F*)((*hists)[2])->Clone("lc ch3");
  // TH1F* lc_4 = (TH1F*)((*hists)[3])->Clone("lc ch4");
  
  /* the PH tdc began registering on the 4th run */
  Int_t phpeakNumber = 0;
  /* i starts several bins above the underflow and stops several below overflow */
  for ( Int_t i = 5; i < 4090; i++ ) {
    Stat_t val = ph1->GetBinContent(i);
    /* set threshold of 2 */
    if (val > 2) {
      TF1 *f1 = new TF1("f1","gaus",i-10,i+30);
      i += 30;
      ph1->Fit("f1","R");
      /* PH tdc measured bin size = 24.6 ps */
      meanVals[phpeakNumber++] = f1->GetParameter("Mean");
    }
  }
  
  TF1 *f2 = new TF1("f2","pol1",2,4096);
  
  TGraph* gr_ph1 = new TGraph(numPeaks,meanVals,delayVals);
  
  gr_ph1->Fit("f2","R");
  f2->SetParNames("offset","binsize");
  
  cout << GetCorrCoeff(numPeaks,meanVals,delayVals) << endl;
  return gr_ph1;
}
