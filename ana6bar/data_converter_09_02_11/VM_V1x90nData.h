#ifndef __VM_V1X90NDATA_H
#define __VM_V1X90NDATA_H

#ifndef __STL_STRING
#include <string>
#endif

/* 

(Shamelessly appropriated from CCAENV1x90Data.h at NSCL.)

2009-02-27
Version 1.0
Evan Phelps

* Replaced all references to the NSCL macro STD(string) with direct reference to
string of std::string.

* Changed default to v1290.

*/

namespace VM_V1x90nData {

  // Definitions of bits that appear in all data words:

  static const unsigned long TYPE_MASK    (0xf8000000); // Data type field
  static const unsigned long GLOBAL_HEADER(0x40000000); // GBL header type fld
  static const unsigned long TDC_HEADER   (0x08000000); // TDC header
  static const unsigned long TDC_TRAILER  (0x18000000); // TDC Trailer
  static const unsigned long MEASUREMENT  (0x00000000); // TDC Measurement
  static const unsigned long TDC_ERROR    (0x20000000); // TDC Error flag.
  static const unsigned long TRIGGER_TIME (0x88000000); // Trigger time tag.
  static const unsigned long GLOBAL_TRAILER(0x80000000);// Global trailer.
  static const unsigned long FILLER_LONG   (0xc0000000); // Filler longs.

  // Definitions in the global header only:

  static const unsigned long EVENTCOUNT_MASK (0x07ffffe0);
  static const unsigned int  EVENT_RSHIFT    (0x5);
  static const unsigned int  GEO_MASK        (0x1f);

  // Definitions in the TDC header longword:

  static const unsigned long TDC_MASK        (0x03000000);
  static const unsigned int  TDC_RSHIFT      (24);
  static const unsigned long EVENTID_MASK    (0x007ff800);
  static const unsigned int  EVENTID_RSHIFT  (12);
  static const unsigned int  BUNCHID_MASK    (0x000007ff);
  static const unsigned int  TDCWORDCOUNT_MASK  (0x000007ff);

  // Definitions in the TDC measurement word:

  static const unsigned int  TRAILING_BIT     (0x04000000);
  static const unsigned long V1190CHANNEL_MASK(0x03f80000);
  static const unsigned long V1290CHANNEL_MASK(0x03e00000);
  static const unsigned int  V1190CHANNEL_RSHIFT(19);
  static const unsigned int  V1290CHANNEL_RSHIFT(21);
  static const unsigned long V1190DATA_MASK     (0x0007ffff);
  static const unsigned long V1290DATA_MASK     (0x001fffff);

  static const unsigned long HITLOST_0_FIFO (0x0001); // hits lost group 0 FIFO overflow
  static const unsigned long HITLOST_0_L1   (0x0002); // hits lost group 0 L1 overflow
  static const unsigned long HITERROR_0     (0x0004); // hit error in group 0.'
  static const unsigned long HITLOST_1_FIFO (0x0008); // hits lost group 1 FIFO overflow
  static const unsigned long HITLOST_1_L1   (0x0010); // hits lost group 1 L1 overflow
  static const unsigned long HITERROR_1     (0x0020); // hit error in group 1.
  static const unsigned long HITLOST_2_FIFO (0x0040); // hits lost group 2 FIFO overflow
  static const unsigned long HITLOST_2_L1   (0x0080); // hits lost group 2 L1 overflow
  static const unsigned long HITERROR_2     (0x0100); // hit error in group 2.
  static const unsigned long HITLOST_3_FIFO (0x0200); // hits lost group 3 FIFO overflow
  static const unsigned long HITLOST_3_L1   (0x0400); // hits lost group 3 L1 overflow
  static const unsigned long HITERROR_3     (0x0800); // hit error in group 3.
  static const unsigned long HITS_EXCEEDED  (0x1000); // Hits lost, size limit exceeded.
  static const unsigned long EVENTLOST_FIFO (0x2000); // Event lost due to trigger fifo overflow.
  static const unsigned long FATALCHIP_ERROR(0x4000); // fatal chip error detected.
  static const unsigned long ERROR_MASK     (0x7fff); // All bits.

  // Extended trigger time:

  static const unsigned long TRIGGERTIME_MASK (0x07ffffff);

  // Global trailer:

  static const unsigned long TRIGGERLOST_MASK (0x04000000);
  static const unsigned long TDCERROR_MASK    (0x02000000);
  static const unsigned long OVERFLOW_MASK    (0x01000000);
  static const unsigned long WORDCOUNT_MASK   (0x001fffe0);
  static const unsigned int  WORDCOUNT_RSHIFT (5);

  static inline bool 
  isGlobalHeader(unsigned long Data) {
    return ((Data & TYPE_MASK) == GLOBAL_HEADER);
  }
  static inline bool
  isGlobalTrailer(unsigned long datum)
  {
    return ((datum & TYPE_MASK) == GLOBAL_TRAILER);
  }
  
  static inline int
  TriggerNumber(unsigned long Header) throw (string)
  {
    if(!isGlobalHeader(Header)) {
      throw string("CCAENV1x90Data::TriggerNumber - given non global header");
    }
    else {
      return ((Header & EVENTCOUNT_MASK) >> EVENT_RSHIFT);
    }
  }
  static inline unsigned int
  BoardNumber(unsigned long Header) throw (string)
  {
    if((!isGlobalHeader(Header)) && (!isGlobalTrailer(Header))) {
      throw string("CCAENV1x90Data::BoardNumber - given non global header");
    }
    else {
      return (Header & GEO_MASK);
    }
  }

  static inline bool
  isTDCHeader(unsigned long Header) 
  {
    return ((Header & TYPE_MASK) == TDC_HEADER);
  }

  static inline bool
  isTDCTrailer(unsigned long header)
  {
    return ((header & TYPE_MASK) == TDC_TRAILER);
  }
  static inline bool
  isTDCError(unsigned long Datum)
  {
    return ((Datum & TYPE_MASK) == TDC_ERROR);
  }
 
  static inline unsigned int
  TDCChip(unsigned long Header) throw (string)
  {
    if(! isTDCHeader(Header) && 
       !isTDCTrailer(Header) &&
       !isTDCError(Header)) {
      throw string("CCAENV1x90Data::TDCChip - not data with chip no.");
    } else {
      return ((Header & TDC_MASK) >> TDC_RSHIFT);
    }
  }

  static inline unsigned int
  EventId(unsigned long Header) throw (string)
  {
    if (!isTDCHeader(Header)  && !isTDCTrailer(Header)) {
      throw string("CAENV1x90Data::EventId - not a tdc header");
    } 
    else {
      return ((Header & EVENTID_MASK) >> EVENTID_RSHIFT);
    }
  }
  static inline unsigned int
  BunchId(unsigned long Header) throw (string)
  {
    if(!isTDCHeader(Header)) {
      throw string("CCAENV1x90Data::Bundhid - not a tdc header");
    }
    else {
      return (Header & BUNCHID_MASK); // Assumes right justified.
    }
  }

  static inline short
  TDCWordCount(unsigned long Header) throw (string)
  {
    if(!isTDCTrailer(Header)) {
      throw string("CCAENV1x90Data::TDCWordCount not a tdc trailer");
    } 
    else {
      return (Header & TDCWORDCOUNT_MASK);
    }

  }
  static inline bool
  isMeasurement(unsigned long data)
  {
    return ((data & TYPE_MASK) == MEASUREMENT);
  }
  static inline bool
  isTrailing(unsigned long datum)  throw (string)
  {
    if(!isMeasurement(datum)) {
      throw string("CCAENV1x90Data::isTrailing not a measurement word");
    } else {
      return ((datum & TRAILING_BIT) != 0);
    }
  }
  static inline int
  ChannelNumber(unsigned long Datum, bool is1190 = false) throw (string)
  {
    if(!isMeasurement(Datum)) {
      throw string("CCAENV1x90Data::ChannelNumber  is not a measurement");
    } 
    else   {
      unsigned long mask = V1190CHANNEL_MASK;
      unsigned long shift= V1190CHANNEL_RSHIFT;
      
      // If the module is actually a 1290, correct the
      // assumptions above.
      
      if(!is1190) {
        mask = V1290CHANNEL_MASK;
        shift= V1290CHANNEL_RSHIFT;
      }

      return ((Datum & mask) >> shift);
    }
  }
  static inline long
  ChannelValue(unsigned long datum, bool is1190=true) throw (string)
  {
    if (!isMeasurement(datum)) {
      throw string("CCAENV1sx90Data::ChannelValue - is not a measurement");
    } else {
      unsigned long mask = is1190 ? V1190DATA_MASK : 
                                    V1290DATA_MASK;
      return (datum & mask);
    }
  }
  static inline unsigned long
  TDCErrorBits(unsigned long datum) throw (string)
  {
    if(!isTDCError(datum)) {
      throw string("CCAENV1x90DATA:: not an error flag word");
    }
    else {
      return datum & ERROR_MASK;
    }
    
  }
  static  inline bool 
  isTriggerTimeTag(unsigned long datum)
  {
    return ((datum & TYPE_MASK) == TRIGGER_TIME);
  }
  static inline unsigned long 
  ExtendedTriggerTime(unsigned long datum) throw (string)
  {
    if(!isTriggerTimeTag(datum)) {
      throw string("CCAENV1x90DATA::ExtendedTriggerTime not a trigger time word");
    } 
    else {
      return (datum & TRIGGERTIME_MASK);
    }
  }

  static inline bool
  Overflow(unsigned long datum) throw (string)
  {
    if(!isGlobalTrailer(datum)) {
      throw string("CCAENV1x90DATA::Overflow - not a global trailer");
    }
    else {
      return ((datum & OVERFLOW_MASK) == OVERFLOW_MASK);
    }
  }

  static inline bool 
  Error(unsigned long datum) throw (string)
  {
    if(!isGlobalTrailer(datum)) {
      throw string("CCAENV1x90DATA::Error - not a global trailer");
    } 
    else {
      return ((datum & TDCERROR_MASK) == TDCERROR_MASK);
    }
  }
  static inline bool 
  Lost(unsigned long datum) throw (string)
  {
    if(!isGlobalTrailer(datum)) {
      throw string("CAENV1x90DATA::Lost - not a trailer long");
    } 
    else {
      return ((datum & TRIGGERLOST_MASK) & TRIGGERLOST_MASK);
    }
  }
  static inline unsigned long
  EventSize(unsigned long datum)
  {
    if(!isGlobalTrailer(datum)) {
      throw string("CAENV1x90DATA::EventSize - not a trailer long");
    }
    else {
      return ((datum & WORDCOUNT_MASK) >> WORDCOUNT_RSHIFT);
    }
  }
  static inline bool isFiller(unsigned long datum)
  {
    return ((datum & TYPE_MASK) == FILLER_LONG);
  }
}

#endif

