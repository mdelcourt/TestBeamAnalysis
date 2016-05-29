#include "TestBeamAnalysis/EdmToNtupleNoMask/interface/AnalysisObjects.h"


tbeam::Event::Event():
  run(999999), 
  lumiSection(999999), 
  event(999999),  
  time(999999), 
  unixtime(999999), 
  dt(999999),
  tdcPhase(999999),
  HVsettings(999999),
  DUTangle(999999),
  stubWord(999999),
  stubLatency(999999),
  triggerLatency(999999)
{
   cbcs=std::vector<tbeam::cbc>();
}


tbeam::cbc::cbc():
   pipelineAdd(0),
   status(0),
   error(0)
{
}

tbeam::cluster::cluster():
   x(0),
   size(0)
{
   stubs=std::vector<tbeam::stub*>();
}

tbeam::cluster::~cluster(){
}

tbeam::stub::stub():
   x(0),
   direction(0)
{
   seeding=0;
   matched=0;
}
tbeam::dutEvent::dutEvent():
   stubWord(0),
   stubWordReco(0),
   isGood(1)
{
   stubs=std::vector<tbeam::stub*>();
}

tbeam::dutEvent::~dutEvent(){
   for (unsigned int i=0; i<stubs.size(); i++){delete stubs.at(i);}
   for(std::map<std::string,std::vector<tbeam::cluster *> >::iterator it = clusters.begin(); it != clusters.end(); ++it) {
      for(std::vector<tbeam::cluster *>::iterator cl = it->second.begin(); cl!=it->second.end(); ++cl){
         delete *cl;
      }
   }
//   for (unsigned int i=0; i<clusters.size(); i++){delete clusters.at(i);}
}
