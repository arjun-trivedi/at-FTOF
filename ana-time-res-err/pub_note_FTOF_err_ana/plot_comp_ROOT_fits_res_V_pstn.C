void plot_comp_ROOT_fits_res_V_pstn(bool plot_N_V_pstn=true){
  char* DATADIR=gSystem->ExpandPathName("$FTOF_DATADIR/analyzed/stat_err_ana/40-day-run-2-day-cycles");
  
  const int NMTHD=3;
  enum {CSQWW,CSQ,MLE};
  
  TFile* fin[NMTHD];
  //! [08-02-15] 
  //! + The following file has been specifically chosen and therein, even bar cmbn 2_4_6
  //!   because the data comes closest to exemplifying the "parabola" shape
  //! + For some reason, which I wish I could investigate, most of the parabolas in the 40dr
  //!   seem to be lopsided: the resolutions on the right side, specifically for bar cmbn 1_2_3
  //!   seem to be lower.
  char* fname="July-06-07-2014-cycle1-1st-article_321654.root";
  fin[CSQWW]=TFile::Open(TString::Format("%s/MLE/%s",DATADIR,fname));
  fin[CSQ]=  TFile::Open(TString::Format("%s/CSQ/%s",DATADIR,fname));
  fin[MLE]=  TFile::Open(TString::Format("%s/MLE-actual/%s",DATADIR,fname));
  

  TH1F* h[NMTHD];
  h[CSQWW]=(TH1F*)fin[CSQWW]->Get("fullbar_tw/resol_2_4_6_cont");
  h[CSQ]=  (TH1F*)fin[CSQ]->Get("fullbar_tw/resol_2_4_6_cont");
  h[MLE]=  (TH1F*)fin[MLE]->Get("fullbar_tw/resol_2_4_6_cont");
  //! aesthetics
  h[CSQWW]->SetName(TString::Format("%s_CSQWW",h[CSQWW]->GetName()));
  h[CSQ]->SetName(TString::Format("%s_CSQ",h[CSQ]->GetName()));
  h[MLE]->SetName(TString::Format("%s_MLE",h[MLE]->GetName()));
  h[CSQWW]->SetTitle("");
  h[CSQ]->SetTitle("");
  h[MLE]->SetTitle("");
  h[CSQWW]->SetMarkerColor(kRed);
  h[CSQWW]->SetLineColor(kRed);
  h[CSQ]->SetLineColor(kBlue);
  h[CSQ]->SetMarkerColor(kBlue);
  h[MLE]->SetLineColor(kBlack);
  h[MLE]->SetMarkerColor(kBlack);
  //! aesthetics common to all plots
  gStyle->Reset() //! Reset any aesthetics already set
  //! + I have borrowed these from Gleb's MyMainFrame.cxx
  //! + The one's that I have tweaked are noted
  gStyle->SetFrameLineWidth(3);
  gStyle->SetLineWidth(3);
  for (int i=0;i<NMTHD;i++){
    h[i]->GetYaxis()->SetTitle("Resolution (ps)");
    h[i]->GetXaxis()->SetTitle("Position (cm)");
    h[i]->GetXaxis()->SetTitleSize(0.05); //! GF 0.06
    h[i]->GetXaxis()->SetTitleOffset(0.9); //! GF 0.9
    h[i]->GetYaxis()->SetTitleSize(0.05); //! GF 0.06
    h[i]->GetYaxis()->SetTitleOffset(0.9);//!GF 1.3
    h[i]->GetXaxis()->SetNdivisions(5);//!GF 1.3
    //! AT reduced size of labels on X and Y axis
    h[i]->GetXaxis()->SetLabelSize(0.05);
    h[i]->GetYaxis()->SetLabelSize(0.05);
  }

  //! Quadratic fit = pol2 = [2]*x**2 + [1]*x + [0]
  TF1* f[NMTHD];
  f[CSQWW]=new TF1("fCSQWW","pol2"); 
  f[CSQ]=new TF1("fCSQ","pol2");
  f[MLE]=new TF1("fMLE","pol2");
  //aesthetics
  f[CSQWW]->SetLineColor(kRed);
  f[CSQ]->SetLineColor(kBlue);
  f[MLE]->SetLineColor(kBlack);

  //! Make plot
  gStyle->SetOptStat(0); //! remove stats box
  TLegend* l=new TLegend(0.7,0.8,0.8,0.9);
  TCanvas* c=new TCanvas();
  //! Set minumim and maximum
  //h[CSQWW]->SetMinimum(0);
  h[CSQWW]->SetMaximum(90);	
  h[CSQWW]->Draw();
  h[CSQ]->Draw("sames");
  h[MLE]->Draw("sames");
  //gStyle->SetOptStat("ne");
  //! Fit
  //gStyle->SetOptFit(1111);
  h[CSQWW]->Fit(f[CSQWW],"","sames"); 
  h[CSQ]->Fit(f[CSQ],"","sames");
  //! Parabola fit does not work for MLE because of "outlier" effect
  //h[MLE]->Fit(f[MLE],"","sames");
  //! Add plots to legend
  l->AddEntry(h[CSQWW],"CSQ-WW","l");
  l->AddEntry(h[CSQ],"CSQ","l");
  l->AddEntry(h[MLE],"MLE","l");
  l->Draw();
  c->Update();
  c->SaveAs("${WORKSPACE}/at-FTOF/ana-time-res-err/pub_note_FTOF_err_ana/comp_ROOT_fits_res_vs_pstn.pdf");

  //!Make plot of sgma_sgma/sgma
  TH1F* htmp[NMTHD];
  int nbins=h[CSQWW]->GetNbinsX();
  float xmin=h[CSQWW]->GetXaxis()->GetXmin();
  float xmax=h[CSQWW]->GetXaxis()->GetXmax();
  htmp[CSQWW]=new TH1F("CSQ","CSQ",nbins,xmin,xmax);
  htmp[CSQ]=new TH1F("CSQWW","CSQWW",nbins,xmin,xmax);
  htmp[MLE]=new TH1F("MLE","MLE",nbins,xmin,xmax);
  for (int ibin=0;ibin<nbins;ibin++){
    float sgma_csqww=h[CSQWW]->GetBinContent(ibin+1);
    float sgma_sgma_csqww=h[CSQWW]->GetBinError(ibin+1);
    htmp[CSQWW]->SetBinContent(ibin+1,(sgma_sgma_csqww/sgma_csqww)*100);
    htmp[CSQWW]->SetBinError(ibin+1,0);
    htmp[CSQWW]->SetMinimum(0.);
    htmp[CSQWW]->SetMaximum(15.);
    float sgma_csq=h[CSQ]->GetBinContent(ibin+1);
    float sgma_sgma_csq=h[CSQ]->GetBinError(ibin+1);
    htmp[CSQ]->SetBinContent(ibin+1,(sgma_sgma_csq/sgma_csq)*100);
    htmp[CSQ]->SetBinError(ibin+1,0);
    float sgma_mle=h[MLE]->GetBinContent(ibin+1);
    float sgma_sgma_mle=h[MLE]->GetBinError(ibin+1);
    htmp[MLE]->SetBinContent(ibin+1,(sgma_sgma_mle/sgma_mle)*100);
    htmp[MLE]->SetBinError(ibin+1,0);
  }
  htmp[CSQWW]->SetMarkerStyle(kFullCircle);
  htmp[CSQWW]->SetMarkerColor(kRed);
  htmp[CSQWW]->SetLineColor(kRed);
  htmp[CSQ]->SetMarkerStyle(kFullCircle);
  htmp[CSQ]->SetLineColor(kBlue);
  htmp[CSQ]->SetMarkerColor(kBlue);
  htmp[MLE]->SetMarkerStyle(kFullCircle);
  htmp[MLE]->SetLineColor(kBlack);
  htmp[MLE]->SetMarkerColor(kBlack);
  TCanvas* c1=new TCanvas();
  htmp[CSQWW]->Draw("E1 P");
  htmp[CSQ]->Draw("E1 P sames");
  htmp[MLE]->Draw("E1 P sames");
  

  if (plot_N_V_pstn){
    //! N vs. P
    const int NPNT=69;
    int N[NMTHD][NPNT];
    for (int ipnt=0;ipnt<NPNT;ipnt++){
      TH1F* h_csqww=(TH1F*)fin[CSQWW]->Get(TString::Format("point_%d/res_2_4_6_point%d_cont",ipnt+1,ipnt+1));
      TH1F* h_csq=(TH1F*)fin[CSQ]->Get(TString::Format("point_%d/res_2_4_6_point%d_cont",ipnt+1,ipnt+1));
      N[CSQWW][ipnt]=h_csqww->GetEntries();
      N[CSQ][ipnt]=h_csq->GetEntries();
      //cout<<N[CSQ][ipnt]<<endl;
    }
    TH1F* h_N_vs_p=new TH1F("h_N_vs_p","h_N_vs_p",69,0.5,69.5);
    for (int ipnt=0;ipnt<NPNT;ipnt++){
      //cout<<"binc= "<<N[CSQ][ipnt]<<endl;
      h_N_vs_p->SetBinContent(ipnt+1,N[CSQ][ipnt]);
    }
    //! Make plot
    h_N_vs_p->SetMinimum(0);
    TCanvas* c2=new TCanvas();
    h_N_vs_p->Draw();
  }
  


}
