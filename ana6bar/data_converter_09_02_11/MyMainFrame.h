#include <TGFrame.h>
#include <RQ_OBJECT.h>
#include <TRootEmbeddedCanvas.h>
#include <TGNumberEntry.h>
#include <sstream>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <stdio.h>
#include "VM_VmeData.h"
#include "VM_V1x90nData.h"
#include <TGLabel.h>
#include <TGProgressBar.h>

class MyMainFrame {
        RQ_OBJECT("MyMainFrame")
    private:
        TGHProgressBar *fHProg1;
        TGTextButton *go;
	TGTextButton *input_file;
	TGTextButton *output_file;
	TGTextButton *data_files;
        TGMainFrame *fMain;
	TGTextButton *exit;
	TGHorizontalFrame *hframe;
        TRootEmbeddedCanvas *fEcanvas;
	TGNumberEntry *tdc_ch[16];
	TGNumberEntry *adc_ch[16];
	TString path;
	short nfiles;
	int size;
	std::string _current_file[10];
	std::string _out_file;
	TGLabel *labelq;
	TGLabel *labelqout;
	Bool_t file_status;
        public:
        void MainFrame(const TGWindow *p,UInt_t w,UInt_t h);
        void MainFrame();
        void DoDraw();
	void OpenFile();
	void OutFile();
	void Browse();
	int GetQdcPacket(ifstream& aDataFile, stringstream& aQdcPacket_s);
	int GetTdcPacket(ifstream& aDataFile, stringstream& aTdcPacket_s);
};
