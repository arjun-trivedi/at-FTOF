#include <TROOT.h>

class ResEvent : public TObject {

public:

	ResEvent();
	~ResEvent();

	Int_t t_pmt[7];
	Int_t tdc[16];
	Int_t adc[16];

	Int_t t_electronic_res;
	Int_t t_tdc_res;
	Int_t t_tl;
	Int_t t_tr;
	Int_t t_ml;
	Int_t t_mr;
	Int_t t_bl;
	Int_t t_br;
	Int_t a_tl;
	Int_t a_tr;
	Int_t a_ml;
	Int_t a_mr;
	Int_t a_bl;
	Int_t a_br;

	ClassDef(ResEvent,1)

};
