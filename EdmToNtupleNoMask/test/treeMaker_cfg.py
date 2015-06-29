import FWCore.ParameterSet.Config as cms

process = cms.Process("treeMaker")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.load("TestBeamAnalysis.EdmToNtupleNoMask.EdmToNtupleNoMask_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 10000

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
    'file:/opt/sbg/data/sbgse24/data1/cms/kskovpen/tracker/TB_Jun15/GLIBDAQ/unpacked/USC.00000713.0001.A.storageManager.00.0000.root'
        #'root://eoscms//store/cmst3/user/gauzinge/Data/edmnew/USC.00000478.0001.A.storageManager.00.0000.root'
        #'root://eoscms//store/cmst3/user/gauzinge/Data/edmnew/USC.00000371.0001.A.storageManager.00.0000.root'
    )
)


process.TFileService = cms.Service("TFileService",
  fileName = cms.string('test.root')
)

#process.treeMaker.detIdVec = cms.vint32( 51001,51002,51011,51012, 51013 )                            
process.p = cms.Path(process.treeMaker)
