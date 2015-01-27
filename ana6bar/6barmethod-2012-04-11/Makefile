CXXFLAGS =      -O2 -fPIC -w -fmessage-length=0 $(shell root-config --cflags) -Wno-deprecated
INCS =          -I$(CLAS6INC) -I$(HOME)/include -I. -I$(shell root-config --incdir)
LIBS =          $(shell root-config --glibs)

6barmethod: main.o sigma6barfunctions.o
	g++ -o 6barmethod $(CXXFLAGS) main.o sigma6barfunctions.o -o 6barmethod $(INCS) $(LIBS)
main.o : main.cc
	g++ $(INCS) $(CXXFLAGS) -c main.cc -o main.o
sigma6barfunctions.o : sigma6barfunctions.cc
	g++ $(INCS) $(CXXFLAGS) -c sigma6barfunctions.cc -o sigma6barfunctions.o
clean:
	rm -f main.o sigma6barfunctions.o 6barmethod
