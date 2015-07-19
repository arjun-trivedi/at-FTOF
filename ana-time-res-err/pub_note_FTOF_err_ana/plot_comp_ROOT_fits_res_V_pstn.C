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
    TCanvas* c1=new TCanvas();
    h->Draw();
  }
  


}
