#ifndef __TestBeamAnalysis_EdmToNtupleNoMask_AnalysisObjects_h
#define __TestBeamAnalysis_EdmToNtupleNoMask_AnalysisObjects_h

#include <vector>
#include <map>
#include <string>
#include<stdint.h>

namespace tbeam {
  class cluster;
  class stub;
  class cbc;
  class stub{
   public:
     stub();
     tbeam::cluster * seeding;  // Bottom sensor cluster
     tbeam::cluster * matched;  // Top sensor cluster
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
     std::map < std::string, std::vector <tbeam::cluster*> > clusters;
     std::map < std::string, std::vector <int> > hits;
     std::vector <tbeam::stub*> stubs;
     uint32_t stubWord;
     uint32_t stubWordReco;
     bool isGood;
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
}
#endif
