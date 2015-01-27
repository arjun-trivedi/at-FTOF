{
  TH1F*  h = new TH1F("gaus","gaus",100,-10,10);
  TH1F* hchisq = new TH1F("chisq","chisq",100,-50,50);
  for(int i=0;i<1000;i++){
    h->Reset();
    h->FillRandom("gaus",1000);
    h->Fit("gaus");
    TF1* fitf = (TF1*)h->GetFunction("gaus");
    cout << "chisquare = " << fitf->GetChisquare() << endl;
    hchisq->Fill(fitf->GetChisquare());
  }
  gStyle->SetOptFit(1111);
  c();
  hchisq->Draw();
  c();
  h->Draw();
}
