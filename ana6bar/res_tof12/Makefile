
CXX           = g++
ObjSuf        = o
SrcSuf        = cxx
ExeSuf        =
DllSuf        = so

ROOTCFLAGS   := $(shell root-config --cflags)
ROOTLIBS     := $(shell root-config --libs)
ROOTGLIBS    := $(shell root-config --glibs)
ROOTINCLUDE  := -I$(shell root-config --incdir)

all: res2bar

res2bar: res2bar.$(ObjSuf) test_cl.$(ObjSuf) test_clDict.$(ObjSuf) fit2_var.$(ObjSuf) fit2_varDict.$(ObjSuf)  Resolution2bar.$(ObjSuf) Resolution2barDict.$(ObjSuf) ResEvent.$(ObjSuf) ResEventDict.$(ObjSuf)
	$(CXX) -g -o $@ $^ $(ROOTGLIBS)

vmefile: VM_FileProcessor.$(ObjSuf)
	$(CXX) -g -o $@ $^ $(ROOTGLIBS)
	
adc: adcCal.$(ObjSuf) test_cl.$(ObjSuf) test_clDict.$(ObjSuf) fit2_var.$(ObjSuf) fit2_varDict.$(ObjSuf)  Resolution2bar.$(ObjSuf)  Resolution2barDict.$(ObjSuf) ResEvent.$(ObjSuf) ResEventDict.$(ObjSuf)
	$(CXX) -g -o $@ $^ $(ROOTGLIBS)
	
#	@echo "Generating dictionary $@..."
#	rootcint -f Resolution2barDict.cxx -c Resolution2bar.h LinkDef.h
#	rootcint -f $(TARGETCINT) -c -I$(ROOTSYS)/include $(TARGET).h

%.$(ObjSuf): %.$(SrcSuf)
	$(CXX) -g -c $(ROOTINCLUDE) -c $<

clean:
	rm -f *.o
	rm -f *Dict.*
	rm -f G__*
	rm res2bar

