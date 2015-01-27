{
  TRandom* r1 = new TRandom(100);
  TRandom* r2 = new TRandom(200); 

  TH1F* h1 =  new TH1F("h1", "h1", 100, 50, 150);
  TH1F* h2 =  new TH1F("h2", "h2", 100, 50, 150);
  TH1F* h3 =  new TH1F("h3", "h3", 100, -50, 50);

  for(Int_t i =0;i<100000;i++){
    h1->Fill(r1->Gaus(100, 10));
    h2->Fill(r2->Gaus(100, 10));
    h3->Fill(r1->Gaus(100, 10) - r2->Gaus(100, 10));
  }
  
  THStack* hs = new THStack();
  hs->Add(h1, "e1");
  hs->Add(h2, "e1");
  hs->Add(h3, "e1");
  hs->Draw("pads");
  /*Float_t y[10] = {0};
  Float_t x[10] = {1,2,3,4,5,6,7,8,9,10};

  r->RndmArray(10, y);

  TGraph *gr = new TGraph(10, x,y);
  gr->Draw("ALP");*/
}
