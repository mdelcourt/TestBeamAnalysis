#ifndef __TestBeamAnalysis_EdmToNtupleNoMask_EdmToNtupleNoMask_h
#define __TestBeamAnalysis_EdmToNtupleNoMask_EdmToNtupleNoMask_h

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "TestBeamAnalysis/EdmToNtupleNoMask/interface/AnalysisObjects.h"

#include "TFile.h"
#include "TTree.h"
#include<stdint.h>

class EdmToNtupleNoMask : public edm::EDAnalyzer
{
 public:
  explicit EdmToNtupleNoMask(const edm::ParameterSet& iConfig);
  ~EdmToNtupleNoMask(){}
 private:
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  static bool sortEvent( const tbeam::Event& a,  const tbeam::Event& b);
  const int verbosity_;
  
  TTree* tree_;
  std::vector<tbeam::Event> v_evtInfo_;
  tbeam::Event ev;
  
  std::map<int,std::string> detIdNamemap_;
  uint32_t tdcAdd_;
  uint32_t hvAdd_;
  uint32_t DUTangAdd_;      
  uint32_t stubAdd_;
  uint32_t cwdAdd_;
  uint32_t tiltAdd_;
  uint32_t vcthAdd_;
  uint32_t offsetAdd_;
  uint32_t windowAdd_;
   
  uint32_t stubWord_;
  int condData_;
  int cbc2Status_;
  unsigned int HVsettings_;
  unsigned int DUTangle_;
};

#endif
