
CXX           = g++ -Wno-write-strings
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
	make converter

converter: converter.$(ObjSuf) MyMainFrame.$(ObjSuf) MyMainFrameDict.$(ObjSuf)
	$(CXX) -g -o $@ $^ $(ROOTGLIBS)


	
Dictationarys:	
	rootcint -f MyMainFrameDict.cxx -c -I`root-config --incdir` MyMainFrame.h 
#	rootcint -f $(TARGETCINT) -c -I$(ROOTSYS)/include $(TARGET).h

%.$(ObjSuf): %.$(SrcSuf)
	$(CXX) -g -c $(ROOTINCLUDE) -c $<

clean:
	rm -f *.o
	rm -f *Dict.*
	rm -f G__*
	rm converter
	

