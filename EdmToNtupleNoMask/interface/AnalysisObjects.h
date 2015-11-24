#ifndef __TestBeamAnalysis_EdmToNtupleNoMask_AnalysisObjects_h
#define __TestBeamAnalysis_EdmToNtupleNoMask_AnalysisObjects_h

#include <vector>
#include <map>
#include <string>
#include<stdint.h>
#include "TObject.h"

namespace tbeam {
  class Event :  public TObject {
   public:
    Event();
    virtual ~Event() {}
    unsigned int run;
    unsigned int lumiSection;
    unsigned int event;
    unsigned long long time;
    unsigned long int unixtime;
    unsigned long int dt;
    uint32_t key;
    uint32_t value;
    unsigned int tdcPhase;
    unsigned int HVsettings;
    unsigned int DUTangle;
    uint32_t stubWord;
    uint32_t window;
    uint32_t offset;
    uint32_t cwd;
    uint32_t tilt;
    uint32_t vcth;
    int condData;
    int glibStatus;
    int cbcStatus[16];
    std::map< std::string,std::vector<int> > dut_channel;
    std::map< std::string,std::vector<int> > dut_row;
     
    ClassDef(Event,2)
  };
}
#endif
