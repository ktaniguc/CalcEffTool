#if 'LocalInputFileList' in locals():
#    print "LocalInputFileList is already set"
#else:
#    LocalInputFileList="Z.list"
##LocalInputFileList="local_valid_r9026.list"
##LocalInputFileList="r9311.list"
##LocalInputFileList="r9539_Zmumu.list"
##LocalInputFileList="r9573.list";
##LocalInputFileList="testData17.list";
##LocalInputFileList="r9193.list"
##LocalInputFileList="inEITrkConfFalsev3.list"
#print "LocalInputFileList is"
#print LocalInputFileList
#f = open( LocalInputFileList, 'r' )
#InputFileList = f.read().splitlines()
#print InputFileList
#-----------------------------------------------------------------------------
# Athena imports
#-----------------------------------------------------------------------------
from AthenaCommon.Constants import *
from AthenaCommon.AppMgr import theApp
from AthenaCommon.AppMgr import ServiceMgr
from AthenaCommon.AppMgr import ToolSvc
import AthenaPoolCnvSvc.ReadAthenaPool
from AthenaCommon.AlgSequence import AlgSequence
job = AlgSequence()

#-----------------------------------------------------------------------------
# Message Service
#-----------------------------------------------------------------------------
# Set output level threshold (2=DEBUG, 3=INFO, 4=WARNING, 5=ERROR, 6=FATAL )
ServiceMgr.MessageSvc.OutputLevel = ERROR
import AthenaServices
AthenaServices.AthenaServicesConf.AthenaEventLoopMgr.OutputLevel = ERROR

#-----------------------------------------------------------------------------
# Input Datasets
#-----------------------------------------------------------------------------
from AthenaCommon.AthenaCommonFlags import athenaCommonFlags as acf
if not acf.EvtMax.is_locked():
  acf.EvtMax=-1
#acf.FilesInput = InputFileList
acf.FilesInput += [
"/gpfs/home/yfukuhar/yazawa-root-file/data15_13TeV.00284484.physics_Main.deriv.DAOD_MUON0.r9264_p3083_p3180/DAOD_MUON0.11515458._000161.pool.root.1"
#"/gpfs/fs6001/yyazawa/data/valid1.424100.Pythia8B_A14_CTEQ6L1_Jpsimu4mu4.recon.AOD.e5112_s3091_r9122_tid10750758_00/AOD.10750758._000194.pool.root.1",
#"/gpfs/fs6001/yyazawa/data/valid1.424100.Pythia8B_A14_CTEQ6L1_Jpsimu4mu4.recon.AOD.e5112_s2887_r9026_tid10522817_00/AOD.10522817._000212.pool.root.1"
]
#-----------------------------------------------------------------------------
# Algorithms
#-----------------------------------------------------------------------------
rec.doCBNT=False
from RecExConfig.RecFlags import rec
rec.doTrigger=True
from RecExConfig.RecAlgsFlags import recAlgs
recAlgs.doTrigger=True
recAlgs.doAtlfast=False
recAlgs.doMonteCarloReact=False
from TriggerJobOpts.TriggerFlags import TriggerFlags
TriggerFlags.doTriggerConfigOnly=True
rec.doWriteAOD=False
rec.doWriteESD=False
rec.doWriteTAG=False
rec.doAOD=False
rec.doDPD=False
rec.doESD=False
doTAG=False
rec.doTruth=False
rec.doRecoTiming=False
rec.doDetStatus=False
rec.doShowSizeStatistics=False
rec.readTAG=False
rec.readRDO=False
rec.doHist=False
rec.doContainerRemapping=False
rec.doJiveXML=False
rec.doEdmMonitor=False
rec.doDumpPoolInputContent=False
rec.doHeavyIon=False
rec.doHIP=False
rec.doWriteBS=False
rec.doPhysValMonHists=False
rec.doVP1=False
rec.doJiveXML=False
rec.doMuon=False
rec.doCheckDictionary=False
rec.doFileMetaData=False
rec.doCalo=False
rec.doAODCaloCells=False
rec.doEgamma=False

#rec.doESD.set_Value_and_Lock(False) # uncomment if do not run ESD making algorithms
#rec.doWriteESD.set_Value_and_Lock(False) # uncomment if do not write ESD
#rec.doAOD.set_Value_and_Lock(False) # uncomment if do not run AOD making algorithms
#rec.doWriteAOD.set_Value_and_Lock(False) # uncomment if do not write AOD
#rec.doWriteTAG.set_Value_and_Lock(False) # uncomment if do not write TAG
#
#include("RecExCommon/RecExCommon_topOptions.py")
#
#ToolSvc.TrigDecisionTool.TrigDecisionKey='xTrigDecision'
#from TrigDecisionTool.TrigDecisionToolConf import Trig__TrigDecisionTool
#from TrigNavigation.TrigNavigationConf import HLT__Navigation
#ToolSvc += CfgMgr.Trig__TrigDecisionTool( "TrigDecisionTool" )
#ToolSvc += CfgMgr.HLT__Navigation( "Navigation" )
#ToolSvc.TrigDecisionTool.Navigation.ReadonlyHolders=True
#ServiceMgr.MessageSvc.setWarning += [ "", "HolderFactory" ]
#ServiceMgr.MessageSvc.infoLimit = 99999999
#ServiceMgr.MessageSvc.debugLimit = 99999999

# GRL
ToolSvc += CfgMgr.GoodRunsListSelectionTool("MyGRLTool",GoodRunsListVec=["current_grl.xml"])

include("RecExCommon/RecExCommon_topOptions.py")

from CalcEfficiency.CalcEfficiencyConf import *

job += CalcEffAlg( message = "2",
                   OutputLevel = ERROR,
                   OutputFile = "test_data15_1220_OnlyOneLine_01.root",
                   TapMethod = "JPZtap",
                   Extrapolate = True,
                   GRL = False,
                   DataType = "data15"
                 )
                   #GRL = True
                   #TapMethod = "NoTag",
                   #TapMethod = "Ztap",
                   #TapMethod = "JPZtap",
                   #OutputFile = "test_inEITrkConfFalsev3.root",
                   #Datatype = "data16"

include("TriggerTest/TriggerTestCommon.py")
                     
print job

#-----------------------------------------------------------------------------
