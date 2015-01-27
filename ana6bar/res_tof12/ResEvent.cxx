#include <stdio.h>
#include <iostream>
#include "ResEvent.h"

ClassImp(ResEvent)

ResEvent::ResEvent() {
//   std::cout << "ResEvent Constructor" << std::endl;
	for (int i = 0; i < 7; i++) {
		t_pmt[i] = 0;
	}
	for (int i = 0; i < 16; i++) {
		tdc[i] = 0;
	}
}

ResEvent::~ResEvent() {
   std::cout << "ResEvent Destructor" << std::endl;
}
