void DynamicExec()
{
   // Example of function called when a mouse event occurs in a pad.
   // When moving the mouse in the canvas, a second canvas shows the
   // projection along X of the bin corresponding to the Y position
   // of the mouse. The resulting histogram is fitted with a gaussian.
   // A "dynamic" line shows the current bin position in Y.
   // This more elaborated example can be used as a starting point
   // to develop more powerful interactive applications exploiting CINT
   // as a development engine.
   //
   // Author:  Rene Brun
   gStyle->SetOptFit();
   TObject *select = gPad->GetSelected();
   if(!select) return;
   if (!select->InheritsFrom("TH2")) {gPad->SetUniqueID(0); return;}
   TH2 *h = (TH2*)select;
   gPad->GetCanvas()->FeedbackMode(kTRUE);

   //erase old position and draw a line at current position
   int pxold = gPad->GetUniqueID();
   int px = gPad->GetEventX();
   int py = gPad->GetEventY();
   float uymin = gPad->GetUymin();
   float uymax = gPad->GetUymax();
   int pymin = gPad->YtoAbsPixel(uymin);
   int pymax = gPad->YtoAbsPixel(uymax);  
   if(pxold) gVirtualX->DrawLine(pxold,pymin,pxold,pymax);
   gVirtualX->DrawLine(px,pymin,px,pymax);
   gPad->SetUniqueID(px);
   Float_t upx = gPad->AbsPixeltoX(px);
   Float_t x = gPad->PadtoX(upx);

   //create or set the new canvas c2
   TVirtualPad *padsav = gPad;
   TCanvas *c2 = (TCanvas*)gROOT->GetListOfCanvases()->FindObject("c2");
   if(c2) delete c2->GetPrimitive("Projection");
   else   c2 = new TCanvas("c2","Projection Canvas",710,10,700,500);
   c2->SetGrid();
   c2->cd();

   //draw slice corresponding to mouse position
   Int_t binx = h->GetXaxis()->FindBin(x);
//   cout << binx << "\n";
   TH1D *hp = h->ProjectionY("",binx,binx);
   hp->SetFillColor(38);
   char title[80];
   sprintf(title,"Projection of biny=%d",binx);
   hp->SetName("Projection");
   hp->SetTitle(title);
   hp->Fit("gaus","ql");
   hp->GetFunction("gaus")->SetLineColor(kRed);
   hp->GetFunction("gaus")->SetLineWidth(6);
   c2->Update();
   padsav->cd();
}
