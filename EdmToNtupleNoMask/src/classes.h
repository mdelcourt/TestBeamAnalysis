#include "TestBeamAnalysis/EdmToNtupleNoMask/interface/AnalysisObjects.h"

#include "DataFormats/Common/interface/DetSetVector.h"
#include "DataFormats/Phase2TrackerDigi/interface/Phase2TrackerCommissioningDigi.h"

#include <vector>
namespace {
struct dictionary {

 tbeam::Event rv1;
 std::vector<tbeam::Event> vrv1;
 std::pair < float, int > pfi;
 std::map<std::string, std::vector<std::pair<float,int > > > msvpfi;
 std::vector<int> vrvi;
 std::vector<unsigned short> vrvs;
 std::map< std::string,std::vector<int> >  msvi;
 std::map< std::string,std::vector<unsigned short> > msvs;
 std::vector<std::vector<Phase2TrackerCommissioningDigi> > mdigi;
 edm::Wrapper<std::vector<std::vector<Phase2TrackerCommissioningDigi> > > vdigi;
};
}
