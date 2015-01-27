#ifndef __VM_V792NDATA_H
#define __V792NDATA_H


#ifndef __STL_STRING
#include <string>
#endif

/*

2009-02-27
Version 1.0
Evan Phelps

*/

namespace VM_V792nData {

  /* ASSUMES that the 32-bit buffer header is passed into each function. */
  

  static const unsigned long QDC_HEADER_MASK        (0xFE000000);
  static const unsigned long QDC_HEADER             (0xFA000000);
  static const unsigned long QDC_MEASUREMENT_MASK   (0xFE000000);
  static const unsigned long QDC_MEASUREMENT        (0xF8000000);
  static const unsigned long QDC_FOOTER_MASK        (0xFE000000);
  static const unsigned long QDC_FOOTER             (0xFC000000);
  static const unsigned long QDC_CH_NUM_MASK        (0x001E0000);
  static const unsigned int QDC_CH_NUM_RSHIFT       (17);
  static const unsigned long QDC_CH_VAL_MASK        (0x00000FFF);
  static const unsigned long QDC_EVENT_MASK         (0x00FFFFFF);
  static const unsigned int QDC_NUM_CHS_MASK        (0x00003F00);
  static const unsigned int QDC_NUM_CHS_RSHIFT      (8);
  

  static inline bool isQdcHeader(unsigned long aData) {
    return ((aData & QDC_HEADER_MASK) == QDC_HEADER);
  }
  
  static inline bool isQdcMeasurement(unsigned long aData) {
    return ((aData & QDC_MEASUREMENT_MASK) == QDC_MEASUREMENT);
  }
  
  static inline bool isQdcFooter(unsigned long aData) {
    return ((aData & QDC_FOOTER_MASK) == QDC_FOOTER);
  }
  
  static inline int getNumChannels(unsigned long aData) {
    if ( !isQdcHeader(aData) ) {
       throw string("VM_V792nData::getNumChannels() - given non header word.");
    } else {
       return ((aData & QDC_NUM_CHS_MASK) >> QDC_NUM_CHS_RSHIFT);
    }
  }
  
  static inline int getChannelNum(unsigned long aData) {
    if ( !isQdcMeasurement(aData) ) {
       throw string("VM_V792nData::getChannelNum() - given non measurement word.");
    } else {
       return ((aData & QDC_CH_NUM_MASK) >> QDC_CH_NUM_RSHIFT);
    }
  }
  
  static inline long getValue(unsigned long aData) {
    if ( !isQdcMeasurement(aData) ) {
       throw string("VM_V792nData::getValue() - given non measurement word.");
    } else {
       return (aData & QDC_CH_VAL_MASK);
    }
  }
  
  static inline long getEventCnt(unsigned long aData) {
    if ( !isQdcFooter(aData) ) {
       throw string("VM_V792nData::getEventCnt() - given non trailer word.");
    } else {
       return (aData & QDC_EVENT_MASK);
    }
  }
}

#endif

