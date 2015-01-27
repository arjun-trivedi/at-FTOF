
CXX           = g++ -Wno-write-strings -Wno-pragmas
ObjSuf        = o
SrcSuf        = cxx
ExeSuf        =
DllSuf        = so

ROOTCFLAGS   := $(shell root-config --cflags)
ROOTLIBS     := $(shell root-config --libs)
ROOTGLIBS    := $(shell root-config --glibs)
ROOTINCLUDE  := -I$(shell root-config --incdir)



all:
	make Dictationarys
	make analysis6bars

analysis6bars: analysis6bars.$(ObjSuf) MyMainFrame.$(ObjSuf) MyMainFrameDict.$(ObjSuf) macro.$(ObjSuf) macroDict.$(ObjSuf)
	$(CXX) -g -o $@ $^ $(ROOTGLIBS)  -lRooFit -lMinuit -lRooFitCore -lFoam -lMathMore


	
Dictationarys:	
	rootcint -f MyMainFrameDict.cxx -c -I`root-config --incdir` MyMainFrame.h 
	rootcint -f macroDict.cxx -c -I`root-config --incdir` macro.h
#	rootcint -f $(TARGETCINT) -c -I$(ROOTSYS)/include $(TARGET).h

%.$(ObjSuf): %.$(SrcSuf)
	$(CXX) -g -c $(ROOTINCLUDE) -c $<

clean:
	rm -f *.o
	rm -f *Dict.*
	rm -f G__*
	rm analysis6bars
	

