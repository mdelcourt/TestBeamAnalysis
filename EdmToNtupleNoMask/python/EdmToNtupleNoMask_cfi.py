import FWCore.ParameterSet.Config as cms

treeMaker = cms.EDAnalyzer("EdmToNtupleNoMask",
   verbosity = cms.untracked.int32(0),
   detIdVec = cms.vint32( 50000,50004,51011,51012 ),
   detNamesVec = cms.vstring( "det0","det1","det2","det3" ),
   tdcAddress = cms.string("0x03000000"),
   hvAddress = cms.string("0x05000000"),
   dutAngAddress = cms.string("0x04000000"),
   stubAddress = cms.string("0x0B0000FF"),
   cwdAddress = cms.string("0x81000000"),
   offsetAddress = cms.string("0x80000000"),
   windowAddress = cms.string("0x82000000"),
   tiltAddress = cms.string("0x83000000"),
   vcthAddress = cms.string("0x08000000")
)

