#include "Resolution2bar.h"
#include "ResEvent.h"
#include <TFile.h>
#include <TStyle.h>
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TF1.h"
#include "TF2.h"
#include "TF3.h"

ClassImp(Resolution2bar)


using namespace std;


const TObjString _kPmtString[7] = { "", "tl", "tr", "ml", "mr", "bl", "br" };


Resolution2bar::Resolution2bar() {
  _numEvents = 0;

  _cuts = new TList();
  _activeCuts = new TList();
	_hists = new TObjArray();
	_canvases = new TObjArray();

	_currentDesc = new TObjString("Base");

	_twScheme = 0;

	ifstream configFile;
//	cout << "opening configfile" << endl;
	configFile.open("res.config");
	for (Int_t i = 0; i < 6; i++) { _tdcChs[i] = 0; }
	for (Int_t i = 0; i < 6; i++) { _adcChs[i] = 0; }
	for (Int_t i = 0; i < 7; i++) { _adcOffsets[i] = 0; }
	for (Int_t i = 0; i < 4; i++) { _tdcDiffRanges[i] = "(800,199.75,599.75)"; }
	for (Int_t i = 0; i < 4; i++) { _tdcSumRanges[i] = "(2400,-699.75,499.75)"; }
	for (Int_t i = 0; i < 7; i++) { _tdcFitRanges[i][0] = -1000.5; _tdcFitRanges[i][1] = 999.5; }

	_adcTdcRange = "(64,-.5,4095.5,1024,-4096.5,4095.5)";
	_adcTdcDiffRange = "(128,-.5,4095.5,50,-.5,799.5)";

	Int_t id;
	while (configFile.good()) {
//	cout << "configfile is good" << endl;
		configFile >> id;
		switch (id) {

			case _kConfigId_comment :
				configFile.ignore(2048,'\n');
				break;

			case _kConfigId_adcOffsets :
//				cout << "** Using ADC Offsets from res.config:";
				for (Int_t i = 1; i < 7; i++) {
					configFile >> _adcOffsets[i];
//					cout << "  " << _adcOffsets[i];
				}
//				cout << endl;
				id = 0;
				break;

			case _kConfigId_tdcDiffRanges :
//				cout << "** Using TDC Diff Ranges from res.config:" << endl;
				for (Int_t i = 1; i < 4; i++) {
					configFile >> _tdcDiffRanges[i];
//					cout << "  " << _tdcDiffRanges[i] << endl;
				}
				break;

			case _kConfigId_tdcSumRanges :
//				cout << "** Using TDC Sum Ranges from res.config:" << endl;
				for (Int_t i = 1; i < 4; i++) {
					configFile >> _tdcSumRanges[i];
//					cout << "  " << _tdcSumRanges[i] << endl;
				}
				break;

			case _kConfigId_adcTdcRanges :
//				cout << "** Using TDC Sum Ranges from res.config:" << endl;
				configFile >> _adcTdcRange;
				configFile >> _adcTdcDiffRange;
//				cout << "  " << _adcTdcRange << "  " << _adcTdcDiffRange << endl;
				break;

			case _kConfigId_tdcFitRanges :
//				cout << "** Using TDC Fit Ranges from res.config:" << endl;
				for (Int_t i = 1; i < 7; i++) {
					configFile >> _tdcFitRanges[i][0];
					configFile >> _tdcFitRanges[i][1];
//					cout << "  " << _tdcFitRanges[i][0] << ", " << _tdcFitRanges[i][1];
				}
//				cout << endl;
				id = 0;
				break;

			case _kConfigId_tdcChOrder :
//				cout << "** Using TDC Channel Order from res.config:" << endl;
				for (Int_t i = 0; i < 6; i++) {
					configFile >> _tdcChs[i];
//					cout << "  " << _tdcChs[i];
					if (i == _kPmtML-1) { _tdcRefCh = _tdcChs[i]; }
				}
//				cout << endl;
				id = 0;
				break;
						
			case _kConfigId_adcChOrder :
//				cout << "** Using ADC Channel Order from res.config:" << endl;
				for (Int_t i = 0; i < 6; i++) {
					configFile >> _adcChs[i];
//					cout << "  " << _adcChs[i];
				}
//				cout << endl;
				id = 0;
				break;

			case _kConfigId_3barResolution :
//				cout << "** Using 3bar Resolution Range from res.config:";
				configFile >> _3barResRange;
//				cout << "  " << _3barResRange << endl;
				id = 0;
				break;

			case _kConfigId_alias :
				TString aliasName;
				TString aliasStr;
//				cout << "** Adding alias:";
				configFile >> aliasName;
				configFile >> aliasStr;
//				cout << "  " << aliasName << "  -->  " << aliasStr;
//				cout << endl;
				id = 0;
				break;

		}

	}

	PopulateTree();

	_thinData->SetAlias("tdc_tl","t_tl");
	_thinData->SetAlias("tdc_tr","t_tr");
	_thinData->SetAlias("tdc_ml","t_ml");
	_thinData->SetAlias("tdc_mr","t_mr");
	_thinData->SetAlias("tdc_bl","t_bl");
	_thinData->SetAlias("tdc_br","t_br");

//	_thinData->Draw(">>currentEntries","","entrylist");
	_currentEntries = (TEntryList*)gDirectory->FindObject("currentEntries");

}

Resolution2bar::Resolution2bar(const char* fName) {
//  cout << "Resolution2bar(\"" << fName << "\") Not Yet Implemented!" << endl;
}

Resolution2bar::~Resolution2bar() {

	delete _cuts;
	delete _activeCuts;
	delete _canvases;
	delete _thinData;

}

void Resolution2bar::AddAlias(const char* aName, const char* aStr) {
	_thinData->SetAlias(aName, aStr);
}

void Resolution2bar::ListAliases() {
	TCollection* aliases = _thinData->GetListOfAliases();
	aliases->Print();
}

void Resolution2bar::SetTwFactor(Float_t factorPmt1, Float_t factorRef1,
											Float_t factorPmt2, Float_t factorRef2,
											Float_t factorPmt4, Float_t factorRef4,
											Float_t factorPmt5, Float_t factorRef5,
											Float_t factorPmt6, Float_t factorRef6) {

	_thinData->SetAlias("tdc_tl",(const char*)GetTdcStr(1,factorRef1,factorPmt1));
	_thinData->SetAlias("tdc_tr",(const char*)GetTdcStr(2,factorRef2,factorPmt2));
	_thinData->SetAlias("tdc_mr",(const char*)GetTdcStr(4,factorRef4,factorPmt4));
	_thinData->SetAlias("tdc_bl",(const char*)GetTdcStr(5,factorRef5,factorPmt5));
	_thinData->SetAlias("tdc_br",(const char*)GetTdcStr(6,factorRef6,factorPmt6));

	_hists->Delete();
//	Draw();
}

void Resolution2bar::SetTwFactor(Float_t factorRef, Float_t factorPmtMr,
									 Float_t factorPmtTl, Float_t factorPmtTr,
									 Float_t factorPmtBl, Float_t factorPmtBr) {

	SetTwFactor(factorPmtTl, factorRef,
					factorPmtTr, factorRef,
					factorPmtMr, factorRef,
					factorPmtBl, factorRef,
					factorPmtBr, factorRef);
}

void Resolution2bar::PopulateTree(const char* fName) {

   const Int_t numChs = 16;
   Int_t refCh = _tdcRefCh;
   ifstream procfile;

   ResEvent* event = new ResEvent();

	_thinData = new TTree("thinDataOrig","ADC and TDC Measurement for 5mm");
	_thinData->Branch("tna","ResEvent",&event);

   procfile.open(fName);

   Int_t id;
   Int_t ch[numChs];

	Int_t tmp_i = 0;
   while (procfile.good()) // && tmp_i<400)
   {
		tmp_i++;
      procfile >> id;
      for(int j = 0; j < numChs; j++) {
         procfile >> ch[j];
			event->tdc[j] = ch[j];
      }

      for(int j = 1; j < 7; j++) {
			event->t_pmt[j] = ch[_tdcChs[j-1]];
      }

		event->t_electronic_res = ch[6] - ch[refCh];
		event->t_tdc_res = ch[4] - ch[6];
      event->t_tl = ch[_tdcChs[0]] - ch[refCh];
      event->t_tr = ch[_tdcChs[1]] - ch[refCh];
      event->t_ml = ch[_tdcChs[2]] - ch[refCh];
      event->t_mr = ch[_tdcChs[3]] - ch[refCh];
      event->t_bl = ch[_tdcChs[4]] - ch[refCh];
      event->t_br = ch[_tdcChs[5]] - ch[refCh];

      procfile >> id;

      for(int j = 0; j < numChs; j++) {
         procfile >> ch[j];
					event->adc[j] = ch[j];
      }
      event->a_tl = ch[_adcChs[0]] - _adcOffsets[_kPmtTL];
      event->a_tr = ch[_adcChs[1]] - _adcOffsets[_kPmtTR];
      event->a_ml = ch[_adcChs[2]] - _adcOffsets[_kPmtML];
      event->a_mr = ch[_adcChs[3]] - _adcOffsets[_kPmtMR];
      event->a_bl = ch[_adcChs[4]] - _adcOffsets[_kPmtBL];
      event->a_br = ch[_adcChs[5]] - _adcOffsets[_kPmtBR];

      _thinData->Fill();
   }

   procfile.close();

}

TString Resolution2bar::GetTdcStr(Int_t pmtNum) {
	stringstream sstr;
		
	const char* pmtStr = _kPmtString[pmtNum].GetString();
	sstr << "tdc_" << pmtStr << "";
	TString retVal(sstr.str());
	return retVal;
}


TString Resolution2bar::GetTdcStr(Int_t pmtNum, Float_t refCor, Float_t pmtCor) {
	stringstream sstr;
	const char* pmtStr = _kPmtString[pmtNum].GetString();

	switch (_twScheme) {

		case 0 :
			sstr << "(t_" << pmtStr << "-1000.0/sqrt(a_" << pmtStr << ")*" << pmtCor
						<< "+1000.0/sqrt(a_ml)*" << refCor << ")";
			break;

		case 1 :
			sstr << "(t_" << pmtStr << "-sqrt(a_" << pmtStr << ")*" << pmtCor
						<< "+sqrt(a_ml)*" << refCor << ")";
			break;
	}
	TString retVal(sstr.str());
	return retVal;
}

TH1* Resolution2bar::Draw(const char* histName, TCanvas* c,
													Int_t padNum, const char* histOpts) {
	if ( !(_hists->Contains(histName)) ) {
		cout << histName << " does not exist!" << endl;
		return NULL;
	} else {
		c->cd(padNum);
		TH1* h = (TH1*)_hists->FindObject(histName);
		TH1* hCopy = h->DrawCopy(histOpts);
		return hCopy;
	}
}

void Resolution2bar::Draw(TString* histStr, TString* histName,
													TString* histDec, const char* histOpts) {
	if ( !(_hists->Contains(*histName)) ) {
//		cout << "Creating histogram " << *histName
//				 << ": " << *histStr << endl;
		_thinData->Draw(*histStr + ">>" + *histName + *histDec,"",histOpts);
		_hists->Add(gROOT->FindObject(*histName));
	} else {
		TObject* h = _hists->FindObject(*histName);
		h->Draw(histOpts);
	}
}

void Resolution2bar::ForceRefresh() {
	_hists->Delete();
}

void Resolution2bar::DrawTdc(Int_t pmtNum, TCanvas* c) {
	if (pmtNum != 0) {
/*		if (c == NULL) {
			if ( !_cTdc || _cTdc == NULL || !gDirectory->FindObject("cTdc") ) {
//				cout << "Creating Tdc Canvas" << endl;
				_cTdc = new TCanvas("cTdc","TDC Histograms");
				_cTdc->Divide(2,3);
				_canvases->Add(_cTdc);
			}
//		  _cTdc->cd(pmtNum);
		} else {
			c->cd();
		} */
	
		TString histStr = GetTdcStr(pmtNum);
		TString histName = "hist_tdc_" + _kPmtString[pmtNum].GetString();
//						if (!gDirectory->FindObject(histName) ) {
		gDirectory->Delete(histName);
//		};	

		TString histDec = "(3600,-1800.5,1799.5)";
		

														
		Draw(&histStr, &histName, &histDec,"goff");
		
		
	} else {
//		cout << "Redrawing all TDC histograms." << endl;
		for (Int_t i = 1; i <= 6; i++) {
			DrawTdc(i);
		}
	}
}

void Resolution2bar::DrawAdc(Int_t pmtNum, TCanvas* c) {
	if (pmtNum != 0) {
/*		if (c == NULL) {
			if (!_cAdc || _cAdc == NULL || !gDirectory->FindObject("cAdc") ) {
//				cout << "Creating Adc Canvas" << endl;
			  _cAdc = new TCanvas("cAdc","ADC Histograms");
				_cAdc->Divide(2,3);
				_canvases->Add(_cAdc);
			} 
		  _cAdc->cd(pmtNum);
		} else {
//			c->cd();
		}  */
		TString histStr = "a_" + _kPmtString[pmtNum].GetString();
		TString histName = "hist_" + histStr;
		
//		gDirectory->Delete(histName);
		
		TString histDec = "(4096,-.5,4095.5)";
		
		
		Draw(&histStr, &histName, &histDec,"goff");

	} else {
//		cout << "Redrawing all ADC histograms." << endl;
		for (int i = 1; i <= 6; i++) {
			DrawAdc(i);
		}
	}
}

void Resolution2bar::DrawTdcDiff() {
/*	if (!_cTdcAddl || _cTdcAddl == NULL || !gDirectory->FindObject("cTdcAddl") ) {
//		cout << "Creating Tdc Sum/Diff Canvas" << endl;
		_cTdcAddl = new TCanvas("cTdcAddl","TDC Sums and Diffs");
		_cTdcAddl->Divide(2,3);
		_canvases->Add(_cTdcAddl);
	} */
/* currently draw all bars regardless of barNum */
	TString topName = "hist_tdcDiff_top";
	TString midName = "hist_tdcDiff_mid";
	TString btmName = "hist_tdcDiff_btm";
	TString topvsbtm = "hist_topvsbtm";
	TString topvsbtm2 = "hist_topvsbtm2";
	TString topStr = "(" + GetTdcStr(1) + "-" + GetTdcStr(2) + ")/2";
	TString midStr = "(" + GetTdcStr(3) + "-" + GetTdcStr(4) + ")/2";
	TString btmStr = "(" + GetTdcStr(5) + "-" + GetTdcStr(6) + ")/2";
	TString topvsbtmStr = "(" + GetTdcStr(1) + "-" + GetTdcStr(2) + ")/2" + ":" + "(" + GetTdcStr(5) + "-" + GetTdcStr(6) + ")/2";
	TString topvsbtm2Str = "(" + GetTdcStr(1) + "-" + GetTdcStr(2) + "-" + GetTdcStr(5) + "+" + GetTdcStr(6) + ")/2" + ":" + "(" + GetTdcStr(5) + "-" + GetTdcStr(6) + ")/2";
	TString jopa = "(4096,100.,700.,4096,100.,700.)";
	TString jopa2 = "(4096,100.,700.,4096,-300.,300.)";
	//TString decStr = "(800,199.75,599.75)";
//	_cTdcAddl->cd(1);
	Draw(&topStr, &topName, &_tdcDiffRanges[_kBarTop],"goff");
//	_cTdcAddl->cd(3);
	Draw(&midStr, &midName, &_tdcDiffRanges[_kBarMid],"goff");
//	_cTdcAddl->cd(5);
	Draw(&btmStr, &btmName, &_tdcDiffRanges[_kBarBtm],"goff");	
//	TCanvas *c1 = new TCanvas("c1", "(tds_tl-tds_tr)/2 vs (tds_bl-tds_br)/2", 600, 400);
//	_canvases->Add(c1);
	
//        gStyle->SetOptLogz(0);
//        gStyle->SetPalette(1);
//        gStyle->SetOptStat(0);
//        gStyle->SetOptFit(1);	

	Draw(&topvsbtmStr, &topvsbtm, &jopa, "goff");
	
//	TCanvas *c2 = new TCanvas("c2", "(tds_tl-tds_tr)/2 - (tds_bl-tds_br)/2 vs (tds_bl-tds_br)/2", 600, 400);
//	_canvases->Add(c2);
	

	Draw(&topvsbtm2Str, &topvsbtm2, &jopa2, "goff");
	
	

/*        TCanvas *c7 = new TCanvas("c7", "Jopa", 600, 400); 
	_canvases->Add(c7);
	TH2F *pizda;
        pizda = (TH2F*) gDirectory->Get("hist_topvsbtm2");
        pizda->Draw();
*/
//
	
//	TH1D *pyy = hist_topvsbtm2->ProjectionY("projection");
//	hist_topvsbtm2->Draw();
//        py->Fit("gaus");
//        py->GetFunction("gaus")->SetLineColor(kRed);
//        py->GetFunction("gaus")->SetLineWidth(6);
//        c3->Update();
	
	
}

void Resolution2bar::DrawTdcSum() {
/*	if (!_cTdcAddl || _cTdcAddl == NULL || !gDirectory->FindObject("cTdcAddl") ) {
//		cout << "Creating Tdc Sum/Diff Canvas" << endl;
		_cTdcAddl = new TCanvas("cTdcAddl","TDC Sums and Diffs");
		_cTdcAddl->Divide(2,3);
		_canvases->Add(_cTdcAddl);
	} */
/* currently draw all bars regardless of barNum */
	TString topName = "hist_tdcSum_top";
	TString midName = "hist_tdcSum_mid";
	TString btmName = "hist_tdcSum_btm";
	TString topStr = "(" + GetTdcStr(1) + "+" + GetTdcStr(2) + ")/2";
	TString midStr = "(" + GetTdcStr(3) + "+" + GetTdcStr(4) + ")/2";
	TString btmStr = "(" + GetTdcStr(5) + "+" + GetTdcStr(6) + ")/2";

//  _cTdcAddl->cd(2);
	Draw(&topStr, &topName, &_tdcSumRanges[_kBarTop],"goff");
//	_cTdcAddl->cd(4);
	Draw(&midStr, &midName, &_tdcSumRanges[_kBarMid],"goff");
//	_cTdcAddl->cd(6);
	Draw(&btmStr, &btmName, &_tdcSumRanges[_kBarBtm],"goff");
}

void Resolution2bar::DrawAdcVTdc() {
/*	if (!_cAdcVTdc || _cAdcVTdc == NULL || !gDirectory->FindObject("cAdcVTdc") ) {
//		cout << "Creating Adc vs. Tdc Canvas" << endl;
	  _cAdcVTdc = new TCanvas("cAdcVTdc","ADC vs TDC");
		_cAdcVTdc->Divide(3,3);
		_canvases->Add(_cAdcVTdc);
	} */
	TString tlName = "hist_adcTdc_tl";
	TString mlName = "hist_adcTdc_ml";
	TString blName = "hist_adcTdc_bl";
	TString trName = "hist_adcTdc_tr";
	TString mrName = "hist_adcTdc_mr";
	TString brName = "hist_adcTdc_br";
	TString topName = "hist_adcTdcDiff_top";
	TString midName = "hist_adcTdcDiff_mid";
	TString btmName = "hist_adcTdcDiff_btm";
	TString tlStr = GetTdcStr(1) + ":tna.a_tl";
	TString mlStr = GetTdcStr(3) + ":tna.a_ml";
	TString blStr = GetTdcStr(5) + ":tna.a_bl";
	TString trStr = GetTdcStr(2) + ":tna.a_tr";
	TString mrStr = GetTdcStr(4) + ":tna.a_mr";
	TString brStr = GetTdcStr(6) + ":tna.a_br";
	TString topStr = "(" + GetTdcStr(1) + "+" + GetTdcStr(2) + ")/2:tna.a_tr";
	TString midStr = "(" + GetTdcStr(3) + "+" + GetTdcStr(4) + ")/2:tna.a_mr";
	TString btmStr = "(" + GetTdcStr(5) + "+" + GetTdcStr(6) + ")/2:tna.a_br";

//	cout << "Drawing x=tdc, y=adc" << endl;
//  _cAdcVTdc->cd(1);
	Draw(&tlStr, &tlName, &_adcTdcRange, "goff");
//  _cAdcVTdc->cd(2);
	Draw(&trStr, &trName, &_adcTdcRange, "goff");
//  _cAdcVTdc->cd(4);
	Draw(&mlStr, &mlName, &_adcTdcRange, "goff");
//  _cAdcVTdc->cd(5);
	Draw(&mrStr, &mrName, &_adcTdcRange, "goff");
//  _cAdcVTdc->cd(7);
	Draw(&blStr, &blName, &_adcTdcRange, "goff");
//  _cAdcVTdc->cd(8);
	Draw(&brStr, &brName, &_adcTdcRange, "goff");
       
//	cout << "Drawing x=tdcLeft-tdcRight, y=adc" << endl;
//  _cAdcVTdc->cd(3);
	Draw(&topStr, &topName, &_adcTdcDiffRange, "goff");
//  _cAdcVTdc->cd(6);
	Draw(&midStr, &midName, &_adcTdcDiffRange, "goff");
//  _cAdcVTdc->cd(9);
	Draw(&btmStr, &btmName, &_adcTdcDiffRange, "goff");
}

void Resolution2bar::DrawAdcProd() {
/*	if (!_cAdcAddl || _cAdcAddl == NULL || !gDirectory->FindObject("cAdcAddl") ) {
//		cout << "Creating Adc Prod/Ratio Canvas" << endl;
		_cAdcAddl = new TCanvas("cAdcAddl","ADC Products and Ratios");
		_cAdcAddl->Divide(2,3);
		_canvases->Add(_cAdcAddl);
	} */
/* currently draw all bars regardless of barNum */
	TString topName = "hist_adcProd_top";
	TString midName = "hist_adcProd_mid";
	TString btmName = "hist_adcProd_btm";
	TString topStr = "sqrt((tna.a_tl*tna.a_tr))";
	TString midStr = "sqrt((tna.a_ml*tna.a_mr))";
	TString btmStr = "sqrt((tna.a_bl*tna.a_br))";
	TString topDec = "(4096,-.5,4095.5)";
	TString midDec = "(4096,-.5,4095.5)";
	TString btmDec = "(4096,-.5,4095.5)";

//  _cAdcAddl->cd(1);
	Draw(&topStr, &topName, &topDec,"goff");
//	_cAdcAddl->cd(3);
	Draw(&midStr, &midName, &midDec,"goff");
//	_cAdcAddl->cd(5);
	Draw(&btmStr, &btmName, &btmDec,"goff");
}

void Resolution2bar::DrawAdcRatio() {
/*	if (!_cAdcAddl || _cAdcAddl == NULL || !gDirectory->FindObject("cAdcAddl") ) {
//		cout << "Creating Adc Prod/Ratio Canvas" << endl;
		_cAdcAddl = new TCanvas("cAdcAddl","ADC Products and Ratios");
		_cAdcAddl->Divide(2,3);
		_canvases->Add(_cAdcAddl);
	} */
	TString topName = "hist_adcRatio_top";
	TString midName = "hist_adcRatio_mid";
	TString btmName = "hist_adcRatio_btm";
	TString topStr = "log((tna.a_tl/tna.a_tr))";
	TString midStr = "log((tna.a_ml/tna.a_mr))";
	TString btmStr = "log((tna.a_bl/tna.a_br))";
	TString topDec = "(768,-2,2)";
	TString midDec = "(768,-2,2)";
	TString btmDec = "(768,-2,2)";

 // _cAdcAddl->cd(2);
	Draw(&topStr, &topName, &topDec,"goff");
//	_cAdcAddl->cd(4);
	Draw(&midStr, &midName, &midDec,"goff");
//	_cAdcAddl->cd(6);
	Draw(&btmStr, &btmName, &btmDec,"goff");
}

void Resolution2bar::DrawTdcTopBtmDiff(TCanvas* c) {
/*	if (!_cTopBtmDiff || _cTopBtmDiff == NULL || !gDirectory->FindObject("cTopBtmDiff") ) {
//		cout << "Creating Tdc TopBtm Diff Canvas" << endl;
		_cTopBtmDiff = new TCanvas("cTopBtmDiff","Time Between Top and Bottom Bars");
		_canvases->Add(_cTopBtmDiff);
	}  */
	TString histName = "hist_topBtmDiff";
	TString decStr = "(250,-100.5,149.5)";
	TString histStr = "((" + GetTdcStr(5) + "+" + GetTdcStr(6) + ")/2" +
										"-(" + GetTdcStr(1) + "+" + GetTdcStr(2) + ")/2)/2";
//	_cTopBtmDiff->cd();
	Draw(&histStr,&histName,&decStr,"goff");
}

void Resolution2bar::Draw3barResolution(TCanvas* c) {
/*	if (!_c3barRes || _c3barRes == NULL || !gDirectory->FindObject("c3barRes") ) {
//		cout << "Creating 3-bar Final Resolution" << endl;
		_c3barRes = new TCanvas("c3barRes","3-bar Final Resolution");
		_canvases->Add(_c3barRes);
	} */
	TString histName = "hist_c3barRes";
	TString decStr = _3barResRange;
	TString histStr = "(" + GetTdcStr(5) + "+" + GetTdcStr(6) + "+" + GetTdcStr(1) + "+" + GetTdcStr(2) + ")/4"
												+ " - (" + GetTdcStr(3)  + "+" + GetTdcStr(4)  + ")/2";
											
//	_c3barRes->cd();

	Draw(&histStr,&histName,&decStr,"goff");

}

void Resolution2bar::DrawVertDist(TCanvas* c) {
	if (!_cVertDist || _cVertDist == NULL || !gDirectory->FindObject("cVertDist") ) {
//		cout << "Creating Vertical Distribution" << endl;
		_cVertDist = new TCanvas("cVertDist","Vertical-ness");
		_canvases->Add(_cVertDist);
	}
	TString histName = "hist_vertDist";
	TString decStr = "(1200,-500.5,699.5)";
	TString histStr = GetTdcStr(1) + "-" + GetTdcStr(2) + "-" + GetTdcStr(5) + "+" + GetTdcStr(6);
	_cVertDist->cd();
	Draw(&histStr,&histName,&decStr);
}

void Resolution2bar::DrawAdcLvAdcR() {
//	if (!_cAdcLvAdcR || _cAdcLvAdcR == NULL || !gDirectory->FindObject("cAdcLvAdcR") ) {
//		cout << "Creating AdcLvR Canvas" << endl;
//		_cAdcLvAdcR = new TCanvas("cAdcLvAdcR","ADC Left vs Right");
//		_cAdcLvAdcR->Divide(1,3);
//		_canvases->Add(_cAdcLvAdcR);
//	}
	TString topName = "hist_adcLvR_top";
	TString midName = "hist_adcLvR_mid";
	TString btmName = "hist_adcLvR_btm";
	TString topStr = "tna.a_tl:tna.a_tr";
	TString midStr = "tna.a_ml:tna.a_mr";
	TString btmStr = "tna.a_bl:tna.a_br";
	TString decStr = "(200,-.5,3999.5,200,-.5,3999.5)";

//  _cAdcLvAdcR->cd(1);
//	Draw(&topStr, &topName, &decStr,"COLZ");
//  _cAdcLvAdcR->cd(2);
//	Draw(&midStr, &midName, &decStr,"COLZ");
//  _cAdcLvAdcR->cd(3);
//	Draw(&btmStr, &btmName, &decStr,"COLZ");
}

void Resolution2bar::Highlight(const char* histName) {
	if (!_cHighlight || _cHighlight == NULL || !gDirectory->FindObject("cHighlight") ) {
//		cout << "Creating Highlight Canvas" << endl;
	  _cHighlight = new TCanvas("cHighlight","A Closer Look");
		_canvases->Add(_cHighlight);
	}
	if ( !(_hists->Contains(histName)) ) {
		cout << "WARNING! " << histName
				 << " is not the histogram list. Nothing to do." << endl;
	} else {
		_cHighlight->cd();
		TObject* hist = _hists->FindObject(histName);
		hist->Draw();
	}
}

void Resolution2bar::Draw() {
  DrawTdc();
  DrawAdc();
  DrawTdcDiff();
  DrawTdcSum();
  DrawAdcVTdc();
  DrawAdcProd();
  DrawAdcRatio();
  DrawAdcLvAdcR();
  DrawTdcTopBtmDiff();
}

void Resolution2bar::AddCut(const char* aCutName, const char* aCutStr) {
  TCut* tmpCut = new TCut(aCutName, aCutStr);
	_cuts->Remove(_cuts->FindObject(aCutName));  //mem leak?
  _cuts->Add(tmpCut);
//	cout << "Added cut " << aCutName << ": " << aCutStr << endl;
}

void Resolution2bar::ActivateCut(const char* aCutName) {
	_thinData->SetEntryList(0);
	_activeCuts->Remove(_activeCuts->FindObject(aCutName));  //mem leak?
	TCut* tmpCut = (TCut*)_cuts->FindObject(aCutName);
	_activeCuts->Add(tmpCut);
//	cout << "Activated cut " << aCutName << ": " << *tmpCut << endl;
	TIter next(_activeCuts);
	TCut* allCuts = new TCut("");
	while ( TCut* cut = (TCut*)next() ) {
		*allCuts += *cut;
	}
//	cout << "Current total cut: " << *allCuts << endl;

	delete gROOT->FindObject("currentEntries");
	_thinData->Draw(">>currentEntries",*allCuts,"entrylist");
	_currentEntries = (TEntryList*)gDirectory->FindObject("currentEntries");
	_thinData->SetEntryList(_currentEntries);
	_hists->Delete();
	Draw();
}

void Resolution2bar::Revert() {
	_activeCuts->Delete();
	_cuts->Delete();
	ForceRefresh();
	Draw();
}

void Resolution2bar::DeactivateCut(const char* aCutName) {
	TCut* tmpCut = (TCut*)_cuts->FindObject(aCutName);
	_activeCuts->Remove(tmpCut);
	TIter next(_activeCuts);
	TCut* allCuts = new TCut("");
	while ( TCut* cut = (TCut*)next() ) {
		*allCuts += *cut;
	}
	_thinData->Draw(">>currentEntries",*allCuts,"entrylist");
	_thinData->SetEntryList((TEntryList*)gDirectory->FindObject("currentEntries"));
	_hists->Delete();
	Draw();
}

void Resolution2bar::SetAdcMidCut(Float_t slope, Float_t yInt,
																	Int_t tolerance, Int_t minL, Int_t minR) {
  TString left = "tna.a_ml";
  TString right = "tna.a_mr";
//  Float_t m = (y2m-y1m)/(x2m-x1m);
//  Float_t b = y1m-m*x1m;
	stringstream eq_str;
  stringstream adcequal_str;
  adcequal_str << left << "<(" << slope << "*" <<
						right << "+" << yInt << "+" << tolerance << ")";
  adcequal_str << " && " << left << ">(" << slope << "*" <<
						right << "+" << yInt << "-" << tolerance << ")";
  adcequal_str << " && " << left << ">" << minL <<
									" && " << right << ">" << minR;

	eq_str << slope << "*x+" << yInt;
	AddCut("cut_adcMid", adcequal_str.str().c_str());
	
	TCanvas* cTmp;

//	if ( _cAdcLvAdcR && gDirectory->FindObject("cAdcLvAdcR") ) {
//		_cAdcLvAdcR->cd(2);
//	} else {
//		if ( TObject* obj = gDirectory->FindObject("cTmp") ) {
//			delete obj;
//		}
//		cTmp = new TCanvas("cTmp","Temporary Canvas");
//		_canvases->Add(cTmp);
//		cTmp->cd();
//		TString midName = "clone_hist_adcLvR_mid";
//		TString midStr = "tna.a_ml:tna.a_mr";
//		TString decStr = "(200,-.5,3999.5,200,-.5,3999.5)";
//		Draw(&midStr, &midName, &decStr,"COLZ");
//		TObject* hMidAdcVAdc = gROOT->FindObject(midName);
//		_hists->Add(hMidAdcVAdc);
//	}

	delete gROOT->FindObject("adcMidLine");
	_adcMidLine = new TF1("adcMidLine",eq_str.str().c_str(),minR,4000);
//	_adcMidLine->Draw(" SAME ");
}

void Resolution2bar::ActivateAdcMidCut() {
	ActivateCut("cut_adcMid");
}

void Resolution2bar::SetTopBtmDiffCut(Int_t maxDiff, Int_t minDiff) {
  stringstream cut_str;
  TString sel_str = "((" + GetTdcStr(5) + "+" + GetTdcStr(6) + ")/2-(" + GetTdcStr(1) + "+" + GetTdcStr(2) + ")/2)/2";
	cut_str << sel_str << " < " << maxDiff << " && " << sel_str << " > " << minDiff;
	AddCut("cut_topBtmDiff",cut_str.str().c_str());
	ActivateCut("cut_topBtmDiff");
}

void Resolution2bar::SetVertCut(Float_t mean, Float_t pm) {
	Float_t max = mean + pm;
	Float_t min = mean - pm;

  stringstream cut_str;

	TString histStr = GetTdcStr(1) + "-" + GetTdcStr(2) + "-" + GetTdcStr(5) + "+" + GetTdcStr(6);
	cut_str << histStr << " < " << max << " && " << histStr << " > " << min;
	AddCut("cut_vert",cut_str.str().c_str());
	ActivateCut("cut_vert");
}

void Resolution2bar::SetTopBtmPosCut(Int_t top_min, Int_t top_max, Int_t btm_min, Int_t btm_max, Float_t pm, Float_t posFrac) {
	Float_t topCenter = top_min + posFrac*(top_max-top_min);
	Float_t btmCenter = btm_min + posFrac*(btm_max-btm_min);
	stringstream cut_str;
	TString topDiff_str = "(" + GetTdcStr(1) + "-" + GetTdcStr(2) + ")/2";
	TString btmDiff_str = "(" + GetTdcStr(5) + "-" + GetTdcStr(6) + ")/2";
/*	cut_str << topDiff_str << " < " << topCenter << "+" << pm << " && "
				<< topDiff_str << " > " << topCenter << "-" << pm << " && "
				<< btmDiff_str << " < " << btmCenter << "+" << pm << " && "
				<< btmDiff_str << " > " << btmCenter << "-" << pm; 
*/
         cut_str << topDiff_str << " - " << btmDiff_str << "<" << posFrac << "+" << pm << " && " << topDiff_str << " - " << btmDiff_str << ">" << pm << " - "  << posFrac << " && " << btmDiff_str << ">" << btm_min << " && " << btmDiff_str << "<" << btm_max << " && " << topDiff_str << ">" << btm_min << "+" << pm << " && " <<topDiff_str << "<" << btm_max << "+" << pm;
				
	AddCut("cut_topBtmPos",cut_str.str().c_str());
	ActivateCut("cut_topBtmPos");
}




void Resolution2bar::SetTopBtmCenterCut(Int_t top_min, Int_t top_max, Int_t btm_min, Int_t btm_max, Int_t pm) {
	SetTopBtmPosCut(top_min, top_max, btm_min, btm_max, pm, .5);
}

void Resolution2bar::Write(const char* fileName, const char* desc) {
	TFile f(fileName, "CREATE");
	TIterator* cIter = _canvases->MakeIterator();
	TObject* obj;
	while ( obj = cIter->Next() ) {
		if (obj && obj != NULL) {
			obj->Write();
		}
	}

	TIter next(_activeCuts);
	TCut* allCuts = new TCut("");
	while ( TCut* cut = (TCut*)next() ) {
		*allCuts += *cut;
	}

  stringstream description;
	description << desc << endl << endl << *allCuts << endl;

	_currentDesc->SetString(description.str().c_str());
	_currentDesc->Write("description");
	f.Close();
	delete allCuts;
}

void Resolution2bar::Fit() {
	
}

void Resolution2bar::AutoTwCorrect(Float_t parmLow, Float_t parmHigh, Int_t steps, TCanvas* c) {
//	if ( c == NULL ) {
//		if (!_cHighlight || _cHighlight == NULL || !gDirectory->FindObject("cHighlight") ) {
//			cout << "Creating Highlight Canvas" << endl;
//		  _cHighlight = new TCanvas("cHighlight","A Closer Look");
//			_canvases->Add(_cHighlight);
//		}
//		c = _cHighlight;
//	}
//	c->Divide(2,2);
//	TCanvas* cMRtw = new TCanvas("cMRtw","Mid Right Temporary Canvas");
	Float_t stepsize = (parmHigh-parmLow)/steps;
	Float_t sigma;
	ResEvent* evt = new ResEvent();
	TBranch* branch = _thinData->GetBranch("tna");
	branch->SetAddress(&evt);
	Long64_t nEvts = _currentEntries->GetN();
	TH1F* hmr = new TH1F("hist_mr_tmp","hist_mr_tmp",
												(Int_t)(_tdcFitRanges[_kPmtMR][1]-_tdcFitRanges[_kPmtMR][0]),
												_tdcFitRanges[_kPmtMR][0],_tdcFitRanges[_kPmtMR][1]);
	TH1F* htl = new TH1F("hist_tl_tmp","hist_tl_tmp",
												(Int_t)(_tdcFitRanges[_kPmtTL][1]-_tdcFitRanges[_kPmtTL][0]),
												_tdcFitRanges[_kPmtTL][0],_tdcFitRanges[_kPmtTL][1]);
	TH1F* htr = new TH1F("hist_tr_tmp","hist_tr_tmp",
												(Int_t)(_tdcFitRanges[_kPmtTR][1]-_tdcFitRanges[_kPmtTR][0]),
												_tdcFitRanges[_kPmtTR][0],_tdcFitRanges[_kPmtTR][1]);
	TH2F* htwtl = new TH2F("hist_tw_tl","Time Walk Parameterization for TL",
												steps+1,parmLow-.5*stepsize,parmHigh+.5*stepsize,
												steps+1,parmLow-.5*stepsize,parmHigh+.5*stepsize);
	TH2F* htwmr = new TH2F("hist_mtw_mr","Time Walk Parameterization for MR",
												steps+1,parmLow-.5*stepsize,parmHigh+.5*stepsize,
												steps+1,parmLow-.5*stepsize,parmHigh+.5*stepsize);
	TH2F* htwtr = new TH2F("hist_tw_tr","Time Walk Parameterization for TR",
												steps+1,parmLow-.5*stepsize,parmHigh+.5*stepsize,
												steps+1,parmLow-.5*stepsize,parmHigh+.5*stepsize);

	TH1F* hbl = new TH1F("hist_bl_tmp","hist_bl_tmp",
												(Int_t)(_tdcFitRanges[_kPmtBL][1]-_tdcFitRanges[_kPmtBL][0]),
												_tdcFitRanges[_kPmtBL][0],_tdcFitRanges[_kPmtBL][1]);
	TH1F* hbr = new TH1F("hist_br_tmp","hist_br_tmp",
												(Int_t)(_tdcFitRanges[_kPmtBR][1]-_tdcFitRanges[_kPmtBR][0]),
												_tdcFitRanges[_kPmtBR][0],_tdcFitRanges[_kPmtBR][1]);
	TH2F* htwbl = new TH2F("hist_tw_bl","Time Walk Parameterization for BL",
												steps+1,parmLow-.5*stepsize,parmHigh+.5*stepsize,
												steps+1,parmLow-.5*stepsize,parmHigh+.5*stepsize);
	TH2F* htwbr = new TH2F("hist_tw_br","Time Walk Parameterization for BR",
												steps+1,parmLow-.5*stepsize,parmHigh+.5*stepsize,
												steps+1,parmLow-.5*stepsize,parmHigh+.5*stepsize);

	Float_t factorRef;
	Float_t factorPmtTl;
	Float_t factorPmtTr;
	Float_t factorPmtMr;
	Float_t factorPmtBl;
	Float_t factorPmtBr;
	for (Int_t j = 0; j <= steps; j++) {
		for (Int_t k = 0; k <= steps; k++) {
			factorRef = parmLow + stepsize*j;
			factorPmtTl = parmLow + stepsize*k;
			factorPmtTr = parmLow + stepsize*k;
			factorPmtMr = parmLow + stepsize*k;
			factorPmtBl = parmLow + stepsize*k;
			factorPmtBr = parmLow + stepsize*k;
			for(Long64_t i = 1; i <= nEvts; i++) {
				Long64_t treeEntryNum = _thinData->GetEntryNumber(i);
				_thinData->GetEntry(treeEntryNum);
				Float_t tl_corrected = getTwCorrectedVal(evt->t_tl, evt->a_tl, evt->a_ml, factorPmtTl, factorRef);
				Float_t tr_corrected = getTwCorrectedVal(evt->t_tr, evt->a_tr, evt->a_ml, factorPmtTr, factorRef);
				Float_t mr_corrected = getTwCorrectedVal(evt->t_mr, evt->a_mr, evt->a_ml, factorPmtMr, factorRef);
				Float_t bl_corrected = getTwCorrectedVal(evt->t_bl, evt->a_bl, evt->a_ml, factorPmtBl, factorRef);
				Float_t br_corrected = getTwCorrectedVal(evt->t_br, evt->a_br, evt->a_ml, factorPmtBr, factorRef);
				htl->Fill(tl_corrected);
				htr->Fill(tr_corrected);
				hmr->Fill(mr_corrected);
				hbl->Fill(bl_corrected);
				hbr->Fill(br_corrected);
			}
			htl->Fit("gaus","Q0");
			htr->Fit("gaus","Q0");
			hmr->Fit("gaus","Q0");
			hbl->Fit("gaus","Q0");
			hbr->Fit("gaus","Q0");
			TF1* gtl = htl->GetFunction("gaus");
			TF1* gtr = htr->GetFunction("gaus");
			TF1* gmr = hmr->GetFunction("gaus");
			TF1* gbl = hbl->GetFunction("gaus");
			TF1* gbr = hbr->GetFunction("gaus");
			sigma = gtl->GetParameter(2);
			//htwtl->SetBinContent(k+1,j+1,sigma);
			htwtl->Fill(factorPmtTl,factorRef,sigma);
			sigma = gtr->GetParameter(2);
			//htwtr->SetBinContent(k+1,j+1,sigma);
			htwtr->Fill(factorPmtTr,factorRef,sigma);
			sigma = gmr->GetParameter(2);
			//htwmr->SetBinContent(k+1,j+1,sigma);
			htwmr->Fill(factorPmtMr,factorRef,sigma);
			sigma = gbl->GetParameter(2);
			//htwbl->SetBinContent(k+1,j+1,sigma);
			htwbl->Fill(factorPmtBl,factorRef,sigma);
			sigma = gbr->GetParameter(2);
			//htwbr->SetBinContent(k+1,j+1,sigma);
			htwbr->Fill(factorPmtBr,factorRef,sigma);
			htl->Reset();
			htr->Reset();
			hmr->Reset();
			hbl->Reset();
			hbr->Reset();
		}
	}
//	c->cd(1);
//	htwtl->Draw("COLZ ");
//	c->cd(2);
//	htwtr->Draw("COLZ ");
//	cMRtw->cd();
//	htwmr->Draw("COLZ ");
//	c->cd(3);
//	htwbl->Draw("COLZ ");
//	c->cd(4);
//	htwbr->Draw("COLZ ");
        hmr->Delete();
	htl->Delete();
	htr->Delete();
	hbl->Delete();
	hbr->Delete();
}

void Resolution2bar::Summary() {

//	TCanvas* resSummary = new TCanvas("cResSummary","Time Resolution Summary");
//	_canvases->Add(resSummary);
//	resSummary->Divide(4,3);
	
//	TH1* htl = Draw("hist_tdc_tl", resSummary, 1);
//	htl->GetXaxis()->SetRangeUser(460,600);
//	htl->Fit("gaus","Q");
	
//	TH1* htr = Draw("hist_tdc_tr", resSummary, 2);
//	htr->GetXaxis()->SetRangeUser(-350,-210);
//	htr->Fit("gaus","Q");
	
//	TH1* htl_at = Draw("hist_adcTdc_tl", resSummary, 5, "colz");
	TH1F* hbl = new TH1F("hist_bl_tmp","hist_bl_tmp",
												(Int_t)(_tdcFitRanges[_kPmtBL][1]-_tdcFitRanges[_kPmtBL][0]),
												_tdcFitRanges[_kPmtBL][0],_tdcFitRanges[_kPmtBL][1]);
	TH1F* hbr = new TH1F("hist_br_tmp","hist_br_tmp",
												(Int_t)(_tdcFitRanges[_kPmtBR][1]-_tdcFitRanges[_kPmtBR][0]),
												_tdcFitRanges[_kPmtBR][0],_tdcFitRanges[_kPmtBR][1]);
	
//	TH1* htr_at = Draw("hist_adcTdc_tr", resSummary, 6, "colz");
//	htr_at->GetYaxis()->SetRangeUser(-600,0);
	
//	TH1* htd = Draw("hist_tdcDiff_top", resSummary, 9);
//	htd->GetXaxis()->SetRangeUser(350,450);
//	htd->Fit("gaus","Q");
	
//	TH1* hts = Draw("hist_tdcSum_top", resSummary, 10);
//	hts->GetXaxis()->SetRangeUser(60,200);
//	hts->Fit("gaus","Q");
	
//	Draw("hist_tdc_bl", resSummary, 3);
//	hbl->GetXaxis()->SetRangeUser(500,700);
//	hbl->Fit("gaus","Q");
	
//	Draw("hist_tdc_br", resSummary, 4);
//	hbr->GetXaxis()->SetRangeUser(-350,-150);
//	hbr->Fit("gaus","Q");
	
//	TH1* hbl_at = Draw("hist_adcTdc_bl", resSummary, 7, "colz");
//	hbl_at->GetYaxis()->SetRangeUser(200,800);
	
//	TH1* hbr_at = Draw("hist_adcTdc_br", resSummary, 8, "colz");
//	hbr_at->GetYaxis()->SetRangeUser(-600,0);
	
//	TH1* hbd = Draw("hist_tdcDiff_btm", resSummary, 11);
//	hbd->GetXaxis()->SetRangeUser(380,500);
//	hbd->Fit("gaus","Q");
	
//	TH1* hbs = Draw("hist_tdcSum_btm", resSummary, 12);
//	hbs->GetXaxis()->SetRangeUser(100,250);
//	hbs->Fit("gaus","Q");

}

void Resolution2bar::SetTwFunctions(Float_t tlp0, Float_t tlp1, Float_t tlp2,
						  Float_t trp0, Float_t trp1, Float_t trp2,
						  Float_t mlp0, Float_t mlp1, Float_t mlp2,
						  Float_t mrp0, Float_t mrp1, Float_t mrp2,
						  Float_t blp0, Float_t blp1, Float_t blp2,
						  Float_t brp0, Float_t brp1, Float_t brp2) {
	_twParms[_kPmtTL][0] = tlp0;
	_twParms[_kPmtTL][1] = tlp1;
	_twParms[_kPmtTL][2] = tlp2;
	_twParms[_kPmtTR][0] = trp0;
	_twParms[_kPmtTR][1] = trp1;
	_twParms[_kPmtTR][2] = trp2;
	_twParms[_kPmtML][0] = mlp0;
	_twParms[_kPmtML][1] = mlp1;
	_twParms[_kPmtML][2] = mlp2;
	_twParms[_kPmtMR][0] = mrp0;
	_twParms[_kPmtMR][1] = mrp1;
	_twParms[_kPmtMR][2] = mrp2;
	_twParms[_kPmtBL][0] = blp0;
	_twParms[_kPmtBL][1] = blp1;
	_twParms[_kPmtBL][2] = blp2;
	_twParms[_kPmtBR][0] = brp0;
	_twParms[_kPmtBR][1] = brp1;
	_twParms[_kPmtBR][2] = brp2;
}

Float_t Resolution2bar::getTwFactor(Int_t pmt, Float_t tdcDiff) {
	Float_t retVal = 0;
	//cout << _twParms[pmt][0] << "      " << _twParms[pmt][1] << "        " << _twParms[pmt][2] << endl;
	retVal = _twParms[pmt][0] + (_twParms[pmt][1])*tdcDiff + (_twParms[pmt][2])*pow(tdcDiff,2);
	return retVal;
}

Float_t Resolution2bar::getTwCorrectedVal(Float_t tdcVal,
														Float_t adcVal, Float_t adcValRef,
														Float_t factor, Float_t factorRef) {
//cout << "TEST: " << tdcVal << " " << adcVal << " " << adcValRef << " " << factor << " " << factorRef << endl;
	Float_t retVal;
	switch (_twScheme) {
		case 0 :
			retVal = tdcVal-1000.0/sqrt(adcVal)*factor+1000.0/sqrt(adcValRef)*factorRef;
			break;

		case 1 :
			retVal = tdcVal-sqrt(adcVal)*factor+sqrt(adcValRef)*factorRef;
			break;
	}
	return retVal;
}

void Resolution2bar::DrawFullBarRes() {
	SetTwScheme(0);
	ResEvent* evt = new ResEvent();
	TBranch* branch = _thinData->GetBranch("tna");
	branch->SetAddress(&evt);
	Long64_t nEvts = _currentEntries->GetN();
	
	TH1F* hmr = new TH1F("hist_mr_tmp","hist_mr_tmp",
												(Int_t)(_tdcFitRanges[_kPmtMR][1]-_tdcFitRanges[_kPmtMR][0]),
												_tdcFitRanges[_kPmtMR][0],_tdcFitRanges[_kPmtMR][1]);
	TH1F* hml = new TH1F("hist_ml_tmp","hist_ml_tmp",
												(Int_t)(_tdcFitRanges[_kPmtML][1]-_tdcFitRanges[_kPmtML][0]),
												_tdcFitRanges[_kPmtML][0],_tdcFitRanges[_kPmtML][1]);
	TH1F* htl = new TH1F("hist_tl_tmp","hist_tl_tmp",
												(Int_t)(_tdcFitRanges[_kPmtTL][1]-_tdcFitRanges[_kPmtTL][0]),
												_tdcFitRanges[_kPmtTL][0],_tdcFitRanges[_kPmtTL][1]);
	TH1F* htr = new TH1F("hist_tr_tmp","hist_tr_tmp",
												(Int_t)(_tdcFitRanges[_kPmtTR][1]-_tdcFitRanges[_kPmtTR][0]),
												_tdcFitRanges[_kPmtTR][0],_tdcFitRanges[_kPmtTR][1]);

	TH1F* hbl = new TH1F("hist_bl_tmp","hist_bl_tmp",
												(Int_t)(_tdcFitRanges[_kPmtBL][1]-_tdcFitRanges[_kPmtBL][0]),
												_tdcFitRanges[_kPmtBL][0],_tdcFitRanges[_kPmtBL][1]);
	TH1F* hbr = new TH1F("hist_br_tmp","hist_br_tmp",
												(Int_t)(_tdcFitRanges[_kPmtBR][1]-_tdcFitRanges[_kPmtBR][0]),
												_tdcFitRanges[_kPmtBR][0],_tdcFitRanges[_kPmtBR][1]);

	TH1F* htopdiff = new TH1F("hist_topdiff_tmp","hist_topdiff_tmp", 3199,-800.25,799.25);
	TH1F* hmiddiff = new TH1F("hist_middiff_tmp","hist_middiff_tmp", 3199,-800.25,799.25);
	TH1F* hbtmdiff = new TH1F("hist_btmdiff_tmp","hist_btmdiff_tmp", 3199,-800.25,799.25);

	TH1F* fullBarRes = new TH1F("fullBarRes","fullBarRes",3199,-800.25,799.25);

	Float_t factorRef;
	Float_t factorPmtTl;
	Float_t factorPmtTr;
	Float_t factorPmtMl;
	Float_t factorPmtMr;
	Float_t factorPmtBl;
	Float_t factorPmtBr;
	for(Long64_t i = 1; i <= nEvts; i++) {
		Long64_t treeEntryNum = _thinData->GetEntryNumber(i);
		_thinData->GetEntry(treeEntryNum);
		factorRef = getTwFactor(_kPmtML,evt->t_ml-evt->t_mr);
		factorPmtTl = getTwFactor(_kPmtTL,(evt->t_tl-evt->t_tr)/2);
		factorPmtTr = getTwFactor(_kPmtTR,(evt->t_tl-evt->t_tr)/2);
		factorPmtMl = getTwFactor(_kPmtML,(evt->t_ml-evt->t_mr)/2);
		factorPmtMr = getTwFactor(_kPmtMR,(evt->t_ml-evt->t_mr)/2);
		factorPmtBl = getTwFactor(_kPmtBL,(evt->t_bl-evt->t_br)/2);
		factorPmtBr = getTwFactor(_kPmtBR,(evt->t_bl-evt->t_br)/2);

		Float_t tl_corrected = getTwCorrectedVal(evt->t_tl, evt->a_tl, evt->a_ml, factorPmtTl, factorRef);
		Float_t tr_corrected = getTwCorrectedVal(evt->t_tr, evt->a_tr, evt->a_ml, factorPmtTr, factorRef);
		Float_t ml_corrected = getTwCorrectedVal(evt->t_ml, evt->a_ml, evt->a_ml, factorPmtMl, factorRef);
		Float_t mr_corrected = getTwCorrectedVal(evt->t_mr, evt->a_mr, evt->a_ml, factorPmtMr, factorRef);
		Float_t bl_corrected = getTwCorrectedVal(evt->t_bl, evt->a_bl, evt->a_ml, factorPmtBl, factorRef);
		Float_t br_corrected = getTwCorrectedVal(evt->t_br, evt->a_br, evt->a_ml, factorPmtBr, factorRef);
		htl->Fill(tl_corrected);
		htr->Fill(tr_corrected);
		hml->Fill(ml_corrected);
		hmr->Fill(mr_corrected);
		hbl->Fill(bl_corrected);
		hbr->Fill(br_corrected);
		htopdiff->Fill((tl_corrected-tr_corrected)/2);
		hmiddiff->Fill((ml_corrected-mr_corrected)/2);
		hbtmdiff->Fill((bl_corrected-br_corrected)/2);
		fullBarRes->Fill((tl_corrected+tr_corrected+bl_corrected+br_corrected)/4-(ml_corrected+mr_corrected)/2);
	}
//	TCanvas* c = new TCanvas("cFullBarRes","cFullBarRes");
//	c->cd();
//	fullBarRes->Draw();
        hmr->Delete();
	htl->Delete();
	htr->Delete();
	hbl->Delete();
	hbr->Delete();
}

