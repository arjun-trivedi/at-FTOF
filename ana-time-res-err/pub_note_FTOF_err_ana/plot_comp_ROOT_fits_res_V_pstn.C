void plot_comp_ROOT_fits_res_V_pstn(bool plot_N_V_pstn=true){
  char* DATADIR=gSystem->ExpandPathName("$FTOF_DATADIR/analyzed/stat_err_ana/40-day-run-2-day-cycles");
  
  const int NMTHD=2;
  enum {CSQWW,CSQ};
  
  TFile* fin[NMTHD];
  fin[CSQWW]=TFile::Open(TString::Format("%s/MLE/July-02-03-2014-cycle1-1st-article_321654.root",DATADIR));
  fin[CSQ]=  TFile::Open(TString::Format("%s/CSQ/July-02-03-2014-cycle1-1st-article_321654.root",DATADIR));

  TH1F* h_resol_1_2_3_cont[NMTHD];
  h_resol_1_2_3_cont[CSQWW]=(TH1F*)fin[CSQWW]->Get("fullbar_tw/resol_1_2_3_cont");
  h_resol_1_2_3_cont[CSQ]=  (TH1F*)fin[CSQ]->Get("fullbar_tw/resol_1_2_3_cont");
  //! aesthetics
  h_resol_1_2_3_cont[CSQWW]->SetName(TString::Format("%s_CSQWW",h_resol_1_2_3_cont[CSQWW]->GetName()));
  h_resol_1_2_3_cont[CSQ]->SetName(TString::Format("%s_CSQ",h_resol_1_2_3_cont[CSQ]->GetName()));
  h_resol_1_2_3_cont[CSQWW]->SetMarkerColor(kRed);
  h_resol_1_2_3_cont[CSQWW]->SetLineColor(kRed);
  h_resol_1_2_3_cont[CSQ]->SetLineColor(kBlue);
  h_resol_1_2_3_cont[CSQ]->SetMarkerColor(kBlue);

  //! Quadratic fit = pol2 = [2]*x**2 + [1]*x + [0]
  TF1* f[NMTHD];
  f[CSQWW]=new TF1("fCSQWW","pol2"); 
  f[CSQ]=new TF1("fCSQ","pol2");
  //aesthetics
  f[CSQWW]->SetLineColor(kRed);
  f[CSQ]->SetLineColor(kBlue);

  //! Make plot
  TCanvas* c=new TCanvas();
  h_resol_1_2_3_cont[CSQWW]->Draw();
  h_resol_1_2_3_cont[CSQ]->Draw("sames");
  gStyle->SetOptStat("ne");
  //! Fit
  gStyle->SetOptFit(1111);
  h_resol_1_2_3_cont[CSQWW]->Fit(f[CSQWW],"","sames"); 
  h_resol_1_2_3_cont[CSQ]->Fit(f[CSQ],"","sames");
  c->Update();

  //!Make plot of sgma_sgma/sgma
  TH1F* htmp[NMTHD];
  int nbins=h_resol_1_2_3_cont[CSQWW]->GetNbinsX();
  float xmin=h_resol_1_2_3_cont[CSQWW]->GetXaxis()->GetXmin();
  float xmax=h_resol_1_2_3_cont[CSQWW]->GetXaxis()->GetXmax();
  htmp[CSQWW]=new TH1F("CSQ","CSQ",nbins,xmin,xmax);
  htmp[CSQ]=new TH1F("CSQWW","CSQWW",nbins,xmin,xmax);
  for (int ibin=0;ibin<nbins;ibin++){
    float sgma_csqww=h_resol_1_2_3_cont[CSQWW]->GetBinContent(ibin+1);
    float sgma_sgma_csqww=h_resol_1_2_3_cont[CSQWW]->GetBinError(ibin+1);
    htmp[CSQWW]->SetBinContent(ibin+1,(sgma_sgma_csqww/sgma_csqww)*100);
    htmp[CSQWW]->SetBinError(ibin+1,0);
    htmp[CSQWW]->SetMinimum(0.);
    htmp[CSQWW]->SetMaximum(15.);
    float sgma_csq=h_resol_1_2_3_cont[CSQ]->GetBinContent(ibin+1);
    float sgma_sgma_csq=h_resol_1_2_3_cont[CSQ]->GetBinError(ibin+1);
    htmp[CSQ]->SetBinContent(ibin+1,(sgma_sgma_csq/sgma_csq)*100);
    htmp[CSQ]->SetBinError(ibin+1,0);
  }
  htmp[CSQWW]->SetMarkerStyle(kFullCircle);
  htmp[CSQWW]->SetMarkerColor(kRed);
  htmp[CSQWW]->SetLineColor(kRed);
  htmp[CSQ]->SetMarkerStyle(kFullCircle);
  htmp[CSQ]->SetLineColor(kBlue);
  htmp[CSQ]->SetMarkerColor(kBlue);
  TCanvas* c1=new TCanvas();
  htmp[CSQWW]->Draw("E1 P");
  htmp[CSQ]->Draw("E1 P sames");
  

  if (plot_N_V_pstn){
    //! N vs. P
    const int NPNT=69;
    int N[NMTHD][NPNT];
    for (int ipnt=0;ipnt<NPNT;ipnt++){
      TH1F* h_csqww=(TH1F*)fin[CSQWW]->Get(TString::Format("point_%d/res_1_2_3_point%d_cont",ipnt+1,ipnt+1));
      TH1F* h_csq=(TH1F*)fin[CSQ]->Get(TString::Format("point_%d/res_1_2_3_point%d_cont",ipnt+1,ipnt+1));
      N[CSQWW][ipnt]=h_csqww->GetEntries();
      N[CSQ][ipnt]=h_csq->GetEntries();
      //cout<<N[CSQ][ipnt]<<endl;
    }
    TH1F* h=new TH1F("h","h",69,0.5,69.5);
    for (int ipnt=0;ipnt<NPNT;ipnt++){
      //cout<<"binc= "<<N[CSQ][ipnt]<<endl;
      h->SetBinContent(ipnt+1,N[CSQ][ipnt]);
    }
    //! Make plot
    h->SetMinimum(0);
    TCanvas* c2=new TCanvas();
    h->Draw();
  }
  


}
