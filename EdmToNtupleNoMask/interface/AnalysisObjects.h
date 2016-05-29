#ifndef __TestBeamAnalysis_EdmToNtupleNoMask_AnalysisObjects_h
#define __TestBeamAnalysis_EdmToNtupleNoMask_AnalysisObjects_h

#include <vector>
#include <map>
#include <string>
#include<stdint.h>
#include "TObject.h"

namespace tbeam {
  class cluster;
  class stub;
  class cbc;
  class stub{
   public:
     stub();
     tbeam::cluster * cluster0;  // Bottom sensor cluster
     tbeam::cluster * cluster1;  // Top sensor cluster
     uint16_t x;        // Position of the stub (bottom sensor)
     int16_t direction; // Direction of the stub (cl0-cl1)

  };
  class cluster{
   public:
     cluster();
     ~cluster();
     uint16_t x;
     uint16_t size;
     std::vector<tbeam::stub *> stubs;
  };
  class cbc{
   public:
     cbc();
     uint16_t pipelineAdd;
     uint8_t status;
     uint8_t error;
  };
  
  class dutEvent{
   public:
     dutEvent();
     ~dutEvent();
     std::map < std::string, std::vector <cluster> > clusters;
     std::map < std::string, std::vector <int> > hits;
     std::vector <tbeam::stub*> stubs;
     uint32_t stubWord;
     uint32_t stubWordReco;
  };
  class condEvent{
   public:
    unsigned int run;
    unsigned int lumiSection;
    unsigned int event;
    unsigned long long time;
    unsigned long int unixtime;
    unsigned int tdcPhase;
    unsigned int HVsettings;
    unsigned int DUTangle;
    uint32_t window;
    uint32_t offset;
    uint32_t cwd;
    uint32_t tilt;
    uint32_t vcth;
    uint32_t stubLatency;
    uint32_t triggerLatency;
    int glibStatus;
    std::vector<tbeam::cbc> cbcs;
  };

  class Event :  public TObject {
   public:
    Event();
    virtual ~Event(){};
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
    uint32_t stubWordReco;
    uint32_t window;
    uint32_t offset;
    uint32_t cwd;
    uint32_t tilt;
    uint32_t vcth;
    uint32_t stubLatency;
    uint32_t triggerLatency;
    int condData;
    int glibStatus;
    
    condEvent Condition;
    dutEvent DUT;

    std::vector<int> cbcStatus;
    std::vector<cbc> cbcs;
    std::vector<stub *> stubs;
    std::map< std::string,std::vector<int> > dut_channel;
    std::map< std::string,std::vector<int> > dut_row;
    std::map< std::string, std::vector<tbeam::cluster> > clusters;
    ClassDef(Event,3)
  };
}
#endif
