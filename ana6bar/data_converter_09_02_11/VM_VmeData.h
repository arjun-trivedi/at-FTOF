#ifndef __VM_VMEDATA_H
#define __VM_VMEDATA_H

#include <sstream>

/*

2009-02-27
Version 1.0
Evan Phelps

*/

using namespace std;

namespace VM_VmeData {

  /* ASSUMES that the 32-bit buffer word is passed into each function. */
  
  /* See VM-USB manual for bit schema */

  /* Note that words 1 and 2 are transposed in the data file, so bit 31 is
     actually bit 15.  Accordingly, a mask of 0x80000000 will become
     0x00008000, and so on. */

  static const unsigned long LAST_BUFFER_MASK         (0x00008000);
  static const unsigned long SCALER_MASK              (0x00004000);
  static const unsigned long CONT_MODE_MASK           (0x00002000);
  static const unsigned long EVT_SPANS_BUFFERS_MASK   (0x00001000);
  static const unsigned long NUM_EVENTS_MASK          (0x00000FFF);
  static const unsigned long NUM_WORDS_MASK           (0x0FFF0000);
  static const int NUM_WORDS_RSHIFT                   (16);
  static const unsigned long TRAILER                  (0xFFFFFFFF);
  static const unsigned long EVENT_MARKER_MASK        (0xFFFF0000);
  static const unsigned int EVENT_MARKER_RSHIFT       (16);
  static const unsigned long EVENT_MARKER             (0x8436);

  static inline bool isEventMarker(unsigned long aData) {
    return (((aData & EVENT_MARKER_MASK) >> EVENT_MARKER_RSHIFT) == EVENT_MARKER);
  }
  
  static inline bool IsLastBuffer(unsigned long aHeader) {
    return !((aHeader & LAST_BUFFER_MASK) == 0);
  }
  
  static inline bool IsScaler(unsigned long aHeader) {
    return !((aHeader & SCALER_MASK) == 0);
  }
  
  static inline bool IsContinuousMode(unsigned long aHeader) {
    return !((aHeader & CONT_MODE_MASK) == 0);
  }
  
  static inline bool IsEventInMultipleBuffers(unsigned long aHeader) {
    return !((aHeader & EVT_SPANS_BUFFERS_MASK) == 0);
  }
  
  static inline unsigned int GetNumEvents(unsigned long aHeader) {
    return (aHeader & NUM_EVENTS_MASK);
  }
  
  static inline unsigned int GetNumWords(unsigned long aHeader) {
    return ((aHeader & NUM_WORDS_MASK) >> NUM_WORDS_RSHIFT);
  }
  
  static inline const char* IsTrue(bool aBool) {
    return ( aBool ? "Yes" : "No" );
  }
  
  static inline bool IsBufferTrailer(unsigned long aWord) {
    return (aWord == TRAILER);
  }
  
  static inline const char* DecodeHeader(unsigned long aHeader) {
    std::ostringstream decodedHdr;
    decodedHdr << "*******************" << endl;
    decodedHdr << "     " << hex << aHeader << endl << "     ========" << endl;
    decodedHdr << " Last Buffer: " << IsTrue(IsLastBuffer(aHeader)) << endl;
    decodedHdr << " Scaler Data: " << IsTrue(IsScaler(aHeader)) << endl;
    decodedHdr << "  Continuous: " << IsTrue(IsContinuousMode(aHeader)) << endl;
    decodedHdr << " Multibuffer: " << IsTrue(IsEventInMultipleBuffers(aHeader)) << endl;
    decodedHdr << "  Num Events: " << dec << GetNumEvents(aHeader) << endl;
    decodedHdr << "   Num Words: " << GetNumWords(aHeader) << endl;
    decodedHdr << "*******************";
    return decodedHdr.str().c_str();
  }

}

#endif

