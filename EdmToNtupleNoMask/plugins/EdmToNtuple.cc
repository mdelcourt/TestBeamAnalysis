// -*- C++ -*-
//
// Package:    EdmToNtupleNoMask
// Class:      EdmToNtupleNoMask
// 
/**\class EdmToNtupleNoMask EdmToNtupleNoMask.cc TestBeamAnalysis/TreeMaker/plugins/EdmToNtupleNoMask.cc
 Description: Main class to process unpacked test beam data 
 Implementation:
     [Notes on implementation]
*/
//
// Author:  Ali Harb, Suvankar Roy Chowdhury, Nicolas Chanon, Kirill Skovpen
// 
//

#include "DataFormats/Common/interface/DetSetVector.h"
#include "DataFormats/Common/interface/DetSetVectorNew.h"
#include "DataFormats/SiPixelDigi/interface/PixelDigiCollection.h"
#include "DataFormats/SiPixelCluster/interface/SiPixelCluster.h"

#include "DataFormats/Phase2TrackerDigi/interface/Phase2TrackerDigi.h"
#include "DataFormats/Phase2TrackerDigi/interface/Phase2TrackerCommissioningDigi.h"
#include "DataFormats/FEDRawData/interface/FEDRawDataCollection.h"
#include "DataFormats/FEDRawData/src/fed_header.h"

#include "EventFilter/Phase2TrackerRawToDigi/interface/Phase2TrackerFEDBuffer.h"
#include "EventFilter/Phase2TrackerRawToDigi/interface/Phase2TrackerFEDHeader.h"

#include "TestBeamAnalysis/EdmToNtupleNoMask/plugins/EdmToNtuple.h"
#include<vector>
#include<algorithm>
#include<iomanip>
using namespace Phase2Tracker;

EdmToNtupleNoMask::EdmToNtupleNoMask(const edm::ParameterSet& iConfig) :
  verbosity_(iConfig.getUntrackedParameter<int>("verbosity", 0))
{
  std::vector<int> detId(iConfig.getParameter< std::vector<int> >("detIdVec"));
  std::vector<std::string> detNames(iConfig.getParameter< std::vector<std::string> >("detNamesVec"));
  if( detId.empty() || detId.size() != detNames.size() ) {
    std::cout << "detId information error!! Please check PSet" << std::endl;
    exit(EXIT_FAILURE);
  } 
  else {
    for( unsigned int i = 0; i<detId.size(); i++ ) {
      detIdNamemap_[detId[i]] = detNames[i];    
    }
  }
  if(verbosity_)
    for( auto& e: detIdNamemap_ )
      std::cout << e.first << "=" << e.second << std::endl;
   
  std::string stemp = iConfig.getParameter<std::string>("tdcAddress");
  tdcAdd_= std::stoul(stemp, nullptr, 16);
  stemp = iConfig.getParameter<std::string>("hvAddress");
  hvAdd_ = std::stoul(stemp, nullptr, 16);
  stemp = iConfig.getParameter<std::string>("dutAngAddress");
  DUTangAdd_ = std::stoul(stemp, nullptr, 16);
  stemp = iConfig.getParameter<std::string>("stubAddress");
  stubAdd_ = std::stoul(stemp, nullptr, 16);
  
  stemp = iConfig.getParameter<std::string>("cwdAddress");
  cwdAdd_ = std::stoul(stemp, nullptr, 16);
  stemp = iConfig.getParameter<std::string>("offsetAddress");
  offsetAdd_ = std::stoul(stemp, nullptr, 16);
  stemp = iConfig.getParameter<std::string>("windowAddress");
  windowAdd_ = std::stoul(stemp, nullptr, 16);
  stemp = iConfig.getParameter<std::string>("tiltAddress");
  tiltAdd_ = std::stoul(stemp, nullptr, 16);

  stemp = iConfig.getParameter<std::string>("vcthAddress");
  vcthAdd_ = std::stoul(stemp, nullptr, 16);

  if(verbosity_) {
    std::cout << "tdcPhase Address=" << tdcAdd_ << std::endl;
    std::cout << "HVsettings Address=" << hvAdd_ << std::endl;
    std::cout << "DUT angle Address=" << DUTangAdd_ << std::endl;
    std::cout << "stub Address=" << stubAdd_ << std::endl;
  }
}

void EdmToNtupleNoMask::beginJob()
{
  edm::Service<TFileService> fs;
  fs->file().cd("/");
  tree_ = fs->make<TTree>("tbeamTree", "AnalysisTree no mask");
  //ev is a dummy variable of type tbeam::Event
  tree_->Branch("run", &ev.run);
  tree_->Branch("lumiSection" , &ev.lumiSection );
  tree_->Branch("event" , &ev.event );
  tree_->Branch("time" , &ev.time, "time/L" );
  tree_->Branch("unixtime" , &ev.unixtime, "unixtime/L" );
  tree_->Branch("tdcPhase", &ev.tdcPhase);
  tree_->Branch("hvSettings", &ev.HVsettings);
  tree_->Branch("dutAngle", &ev.DUTangle);
  tree_->Branch("stubWord", &ev.stubWord);
  tree_->Branch("vcth", &ev.vcth);
  tree_->Branch("offset", &ev.offset);
  tree_->Branch("window", &ev.window);
  tree_->Branch("cwd", &ev.cwd);
  tree_->Branch("tilt", &ev.tilt);
  tree_->Branch("condData", &ev.condData);
  tree_->Branch("glibStatus", &ev.glibStatus);
  for (int i=0; i<16; i++){
      std::stringstream ss;
      ss<<"cbc"<<i<<"Status";
      tree_->Branch(ss.str().c_str(),&ev.cbcStatus[i]);
  }
  tree_->Branch("dut_channel", "std::map< std::string,std::vector<int> >", &ev.dut_channel);
  tree_->Branch("dut_row", "std::map< std::string,std::vector<int> >", &ev.dut_row);
}

void EdmToNtupleNoMask::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  tbeam::Event evtInfo;
  // event info
  evtInfo.run = iEvent.id().run();
  evtInfo.event = iEvent.id().event();  
  evtInfo.lumiSection = iEvent.luminosityBlock();
  edm::Timestamp itime = iEvent.time();
  evtInfo.time = itime.value();
  evtInfo.unixtime = itime.unixTime();

   edm::Handle<FEDRawDataCollection> buffers;
   iEvent.getByLabel("rawDataCollector",buffers);
   
   size_t fedIndex;
   for( fedIndex = Phase2Tracker::FED_ID_MIN; fedIndex < Phase2Tracker::CMS_FED_ID_MAX; ++fedIndex )
     {
	const FEDRawData& fed = buffers->FEDData(fedIndex);
	if(fed.size()!=0)
	  {
	     // construct buffer
	     Phase2Tracker:: Phase2TrackerFEDBuffer* buffer = 0;
	     buffer = new Phase2Tracker::Phase2TrackerFEDBuffer(fed.data(),fed.size());
	     Phase2TrackerFEDHeader tr_header = buffer->trackerHeader();
	     
	     if(verbosity_)
	       {		  
		  std::cout << " buffer size : " << buffer->bufferSize() << std::endl;
		  std::cout << " fed id      : " << fedIndex << std::endl;
		  std::cout << " Version  : " << std::hex << std::setw(2) << (int) tr_header.getDataFormatVersion() << std::endl;
		  std::cout << " Mode     : " << std::hex << std::setw(2) << tr_header.getDebugMode() << std::endl;
		  std::cout << " Type     : " << std::hex << std::setw(2) << (int) tr_header.getEventType() << std::endl;
		  std::cout << " Readout  : " << std::hex << std::setw(2) << tr_header.getReadoutMode() << std::endl;
		  std::cout << " Condition Data : " << ( tr_header.getConditionData() ? "Present" : "Absent") << "\n";
		  std::cout << " Data Type      : " << ( tr_header.getDataType() ? "Real" : "Fake" ) << "\n";
		  std::cout << " Status   : " << std::hex << std::setw(16) << (int) tr_header.getGlibStatusCode() << std::endl;
	       }	     
	     
	     evtInfo.condData = tr_header.getConditionData();
	     evtInfo.glibStatus = (int) tr_header.getGlibStatusCode();

	     if(verbosity_)
	       {		  
		  std::cout << " Nr CBC   : " << std::hex << std::setw(16) << (int) tr_header.getNumberOfCBC() << std::endl;
		  std::cout << " CBC stat : ";
		  for( int i=0;i<tr_header.getNumberOfCBC();i++ )
		    {
		       std::cout << std::hex << std::setw(2) << (int) tr_header.CBCStatus()[i] << " " << std::endl;
		    }	     
	       }	     
	     
	     if( tr_header.getNumberOfCBC() == 2 )
	       {
		  evtInfo.cbcStatus[0] = (int) tr_header.CBCStatus()[0];
		  evtInfo.cbcStatus[1] = (int) tr_header.CBCStatus()[1];
          for(int i = 2 ; i<16; i++){
              evtInfo.cbcStatus[i]=0;
            }
	       }
         else if (tr_header.getNumberOfCBC()==16){
            for (int i=0; i<16; i++){
                evtInfo.cbcStatus[i]=(int) tr_header.CBCStatus()[i];
            }
        }
         else{
             for(int i=0; i<16; i++){
                 evtInfo.cbcStatus[i]=0;
             }
         }
	     
	     delete buffer;
	  }	
     }   
   
   edm::Handle < std::vector<std::vector<Phase2TrackerCommissioningDigi> > > conditions;
   iEvent.getByLabel("Phase2TrackerCommissioningDigiProducer", "ConditionData",  conditions);
   if( !conditions.isValid() ) 
     {
	std::cout << "condition data not found" << std::endl;
	exit(1);
     }   
   std::vector<std::vector<Phase2TrackerCommissioningDigi> >::const_iterator i_detSet;
   std::vector<Phase2TrackerCommissioningDigi>::const_iterator j_detSet;
   
   for(i_detSet = conditions->begin(); i_detSet != conditions->end(); ++i_detSet)
     {
	for(j_detSet = i_detSet->begin(); j_detSet != i_detSet->end(); ++j_detSet)
	  {	
	     uint32_t key = j_detSet->getKey();
	     uint32_t value = j_detSet->getValue();
	   
	     if(verbosity_)
	       {
		  std::cout << "Found key " << std::hex << key << " with value " << std::dec << value << std::endl;
	       }	     
	     
	     if(key == tdcAdd_) 
	       {
		  evtInfo.tdcPhase = value;
		  if(verbosity_) std::cout << "It corresponds to the TDC key" << std::endl;
	       }	     
	     else if(key == hvAdd_) 
	       {
		  evtInfo.HVsettings = value;
		  if(verbosity_) std::cout << "It corresponds to the HV key" << std::endl;
	       }	     
	     else if(key == DUTangAdd_) 
	       {
		  evtInfo.DUTangle = value;
		  if(verbosity_) std::cout << "It corresponds to the DUT angle key" << std::endl;
	       }	     
	     else if(key == tiltAdd_) 
	       {
		  evtInfo.tilt = value;
		  if(verbosity_) std::cout << "It corresponds to the tilt angle key" << std::endl;
	       }	     
	     else if(key == cwdAdd_) 
	       {
		  evtInfo.cwd = value;
		  if(verbosity_) std::cout << "It corresponds to the cluster width discriminator key" << std::endl;
	       }	     
	     else if(key == windowAdd_) 
	       {
		  evtInfo.window = value;
		  if(verbosity_) std::cout << "It corresponds to the stub window size angle key" << std::endl;
	       }	     
	     else if(key == vcthAdd_) 
	       {
		  evtInfo.vcth = value;
		  if(verbosity_) std::cout << "It corresponds to the VCTH key" << std::endl;
	       }	     
	     else if(key == offsetAdd_) 
	       {
		  evtInfo.offset = value;
		  if(verbosity_) std::cout << "It corresponds to the offset parameter key" << std::endl;
	       }	     
	     else if(key == stubAdd_) 
	       {
		  evtInfo.stubWord = value;
		  if(verbosity_) std::cout << "It corresponds to stub word key" << std::endl;
	       }	     
	  }
     }
   edm::Handle< edm::DetSetVector<Phase2TrackerDigi> > input;
   iEvent.getByLabel( "Phase2TrackerDigiProducer", "Unsparsified", input);
   
   if( !input.isValid() )
     {
	std::cout << "Phase2TrackerDigiProducer not found" << std::endl;
	exit(1);	
     }   
   
   edm::DetSetVector<Phase2TrackerDigi>::const_iterator it;
   // loop over modules   
   for(it = input->begin() ; it != input->end(); ++it)
     {
	int detId = it->id;
	if(verbosity_) std::cout << "Module " << std::dec << detId << " ---------- " << std::endl;
	
	// loop over hits in the module
	for(edm::DetSet<Phase2TrackerDigi>::const_iterator hit = it->begin();
	    hit!=it->end(); hit++ )
	  {
	     if(verbosity_) std::cout << "channel=" << hit->channel() << " " << hit->row() << std::endl;

	     evtInfo.dut_channel[detIdNamemap_[detId]].push_back(hit->channel());
	     evtInfo.dut_row[detIdNamemap_[detId]].push_back(hit->row());
	  }	
     }

   edm::Handle< edmNew::DetSetVector<SiPixelCluster> > inputCluster;
   iEvent.getByLabel( "Phase2TrackerDigiProducer", "Sparsified", inputCluster);
   
   if( !inputCluster.isValid() )
     {
	std::cout << "Phase2TrackerDigiProducer not found" << std::endl;
	exit(1);	
     }   

   edmNew::DetSetVector<SiPixelCluster>::const_iterator itc;
   for( itc=inputCluster->begin();itc!=inputCluster->end();itc++ )
     {
//	uint32_t detid = itc->id();
     }   
   
   ev = evtInfo;
   tree_->Fill();
}

void EdmToNtupleNoMask::endJob()
{
}

bool EdmToNtupleNoMask::sortEvent( const tbeam::Event& a,  const tbeam::Event& b) {
  return a.time < b.time;
}
//define this as a plug-in
DEFINE_FWK_MODULE(EdmToNtupleNoMask);

