#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <TH1F.h>
#include <TTree.h>
#include <TCut.h>
#include <TCanvas.h>
#include <TDirectory.h>
#include <TMath.h>
#include <TGraph2D.h>
#include <TRandom.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH2F.h>
#include <TROOT.h>
#include <TSystem.h>
#include <TObjString.h>
#include <TEntryList.h>
#include <TF1.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TF1.h>
#include <TF2.h>
#include <TF3.h>

using namespace std;

class Resolution2bar : public TObject {

private:

	stringstream _history;
	
	static const Int_t _kConfigId_comment = 999;
	static const Int_t _kConfigId_tdcChOrder = 81;
	static const Int_t _kConfigId_adcChOrder = 82;
	static const Int_t _kConfigId_adcOffsets = 1;
	static const Int_t _kConfigId_tdcDiffRanges = 2;
	static const Int_t _kConfigId_tdcSumRanges = 3;
	static const Int_t _kConfigId_adcTdcRanges = 4;
	static const Int_t _kConfigId_tdcFitRanges = 5;
	static const Int_t _kConfigId_3barResolution = 6;
	static const Int_t _kConfigId_alias = 7;

	Int_t _tdcChs[6];
	Int_t _adcChs[6];
	Int_t _adcOffsets[7];
	TString _tdcDiffRanges[4];
	TString _tdcSumRanges[4];
	Float_t _tdcFitRanges[7][2];
	TString _adcTdcRange;
	TString _adcTdcDiffRange;
	TString _3barResRange;
	Float_t _twParms[7][3];

  static const Int_t _kBarAll = 0;
  static const Int_t _kBarTop = 1;
  static const Int_t _kBarMid = 2;
  static const Int_t _kBarBtm = 3;
 
  static const Int_t _kPmtAll = 0;
  static const Int_t _kPmtTL = 1;
  static const Int_t _kPmtTR = 2;
  static const Int_t _kPmtML = 3;
  static const Int_t _kPmtMR = 4;
  static const Int_t _kPmtBL = 5;
  static const Int_t _kPmtBR = 6;

  Int_t _twScheme;	/* 0 = 1/sqrt(adc); 1 = sqrt(adc) */
  Int_t _tdcRefCh;
  
	TObjString* _currentDesc;

	Int_t _numEvents;
	TTree* _thinData;

	TObjArray* _hists;
	TObjArray* _canvases;
  
	TList* _cuts;
	TList* _activeCuts;
	TEntryList* _currentEntries;

	//TString _cTdc_nBase = "cTdc";

  TCanvas* _cTdc;
  TCanvas* _cAdc;
	TCanvas* _cTdcAddl;
  TCanvas* _cAdcAddl;
  TCanvas* _cAdcVTdc;
  TCanvas* _cAdcLvAdcR;
	TCanvas* _cTopBtmDiff;
	TCanvas* _c3barRes;
	TCanvas* _cVertDist;
  TCanvas* _cHighlight;

	TCanvas* _cTimeWalk;
	TH2F* _histTimeWalk;

	TF1* _adcMidLine;

	void PopulateTree(const char* fName = "legacy.dat");
	Float_t getTwCorrectedVal(Float_t tdcVal, Float_t adcVal, Float_t adcValRef,
									  Float_t factor, Float_t factorRef);
	Float_t getTwCorrectedVal(Float_t tdcVal,
							Float_t adcVal, Float_t adcValRef,
		 					Float_t tdcDiff);
	
public:

  Resolution2bar();
  Resolution2bar(const char* suffix);
  ~Resolution2bar();
  
  Float_t getTwFactor(Int_t pmt, Float_t tdcDiff);
  void DrawFullBarRes();
  void AddAlias(const char* aliasName, const char* aliasStr);
  void ListAliases();
	void Summary();
	void SetTwScheme(Int_t twScheme) { _twScheme = twScheme; };
	void SetTwFactor(Float_t factorRef, Float_t factorPmtMr,
									 Float_t factorPmtTl, Float_t factorPmtTr,
									 Float_t factorPmtBl, Float_t factorPmtBr);
	void SetTwFactor(Float_t factorPmt1, Float_t factorRef1,
					Float_t factorPmt2, Float_t factorRef2,
					Float_t factorPmt4, Float_t factorRef4,
					Float_t factorPmt5, Float_t factorRef5,
 					Float_t factorPmt6, Float_t factorRef6);
	void AutoTwCorrect(Float_t parmLow, Float_t parmHigh, Int_t steps, TCanvas* c = NULL);
	void SetTwFunctions(Float_t tlp0, Float_t tlp1, Float_t tlp2,
							  Float_t trp0, Float_t trp1, Float_t trp2,
							  Float_t mlp0, Float_t mlp1, Float_t mlp2,
							  Float_t mrp0, Float_t mrp1, Float_t mrp2,
 							  Float_t blp0, Float_t blp1, Float_t bllp2,
 							  Float_t brp0, Float_t brp1, Float_t brp2);
	void ForceRefresh();
	void Draw();
	TH1* Draw(const char* histName, TCanvas* c, Int_t padNum, const char* histOpts = "");
	void Highlight(const char* histName);
	
	TString GetTdcStr(Int_t pmtNum);
	TString GetTdcStr(Int_t pmtNum, Float_t refCor, Float_t pmtCor);
	
	void Draw(TString* histStr, TString* histName,
						TString* histDec, const char* histOpts = "");
  void DrawTdc(Int_t pmtNum = _kPmtAll, TCanvas* c = NULL);
  void DrawAdc(Int_t pmtNum = _kPmtAll, TCanvas* c = NULL);
  void DrawTdcDiff(); //Int_t barNum = _kBarAll, TCanvas* c = NULL);
  void DrawTdcSum();  //Int_t barNum = _kBarAll, TCanvas* c = NULL);
  void DrawAdcVTdc(); //Int_t pmtNum = _kPmtAll, TCanvas* c = NULL);
  void DrawAdcProd(); //Int_t barNum = _kBarAll, TCanvas* c = NULL);
  void DrawAdcRatio();//Int_t barNum = _kBarAll, TCanvas* c = NULL);
	void DrawAdcLvAdcR();
	void DrawTdcTopBtmDiff(TCanvas* c = NULL);
	void DrawVertDist(TCanvas* c = NULL);
	void Draw3barResolution(TCanvas* c = NULL);
	void Fit();
  
  void AddCut(const char* aCutName, const char* aCutStr);
  void ActivateCut(const char* aCutName);
  void Revert();
  void DeactivateCut(const char* aCutName);
  void SetAdcMidCut(Float_t slope = 1, Float_t yInt = 0,
										Int_t tolerance = 100, Int_t minL = 0, Int_t minR = 0);
  void SetTopBtmCenterCut(Int_t top_min, Int_t top_max, Int_t btm_min, Int_t btm_max, Int_t pm);
  void SetTopBtmPosCut(Int_t top_min, Int_t top_max, Int_t btm_min, Int_t btm_max, Float_t pm, Float_t posFrac);
  void SetTopBtmDiffCut(Int_t maxDiff, Int_t minDiff = 0);
  void SetVertCut(Float_t mean, Float_t pm);
	void ActivateAdcMidCut();
	void Write(const char* fileName, const char* desc = "");

	ClassDef(Resolution2bar,1)

};

