import FWCore.ParameterSet.Config as cms
import sys

template = "root://eoscms.cern.ch//eos/cms/store/group/upgrade/Tracker/TestBeam/BTMay2016/DataEDM/USC.00000_N_.0001.A.storageManager.00.0000.root"

runNumber="775"
if len(sys.argv[-1])==3 and sys.argv[-1].isdigit():
   runNumber=sys.argv[-1]


process = cms.Process("treeMaker")
process.load("FWCore.MessageService.MessageLogger_cfi")
process.load("TestBeamAnalysis.EdmToNtupleNoMask.EdmToNtupleNoMask_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 10000

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
	      template.replace("_N_",runNumber)
        #'root://eoscms//store/cmst3/user/gauzinge/Data/edmnew/USC.00000478.0001.A.storageManager.00.0000.root'
        #'root://eoscms//store/cmst3/user/gauzinge/Data/edmnew/USC.00000371.0001.A.storageManager.00.0000.root'
    )
)

process.TFileService = cms.Service("TFileService",
  fileName = cms.string('ntuple%s.root'%runNumber)
)

#process.treeMaker.detIdVec = cms.vint32( 51001,51002,51011,51012, 51013 )                            
process.p = cms.Path(process.treeMaker)
