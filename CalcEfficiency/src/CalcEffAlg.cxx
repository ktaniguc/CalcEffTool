// Gaudi
#include "GaudiKernel/IAlgTool.h"

#include "GaudiKernel/ITHistSvc.h"
#include "TH1.h"
#include "TH2.h"
#include <iostream>
#include <fstream>
#include <vector>

// xAOD
#include "xAODEventInfo/EventInfo.h"
#include "xAODMuon/MuonContainer.h"
#include "xAODMuon/MuonSegmentContainer.h"
#include "xAODTrigMuon/L2StandAloneMuon.h"
#include "xAODTrigMuon/L2StandAloneMuonContainer.h"
#include "xAODTrigMuon/L2CombinedMuon.h"
#include "xAODTrigMuon/L2CombinedMuonContainer.h"
#include "xAODTrigger/MuonRoIContainer.h"
#include "xAODTracking/TrackParticleContainer.h"
#include "xAODTracking/VertexContainer.h"
#include "GoodRunsLists/IGoodRunsListSelectorTool.h"
#include "TrigConfxAOD/xAODConfigTool.h"
#include "TrigConfInterfaces/ITrigConfigTool.h"
#include "TrigDecisionTool/TrigDecisionTool.h"
#include "TrkParameters/TrackParameters.h"
#include "TrkExInterfaces/IExtrapolator.h"
#include "TrkVKalVrtFitter/TrkVKalVrtFitter.h"
#include "TrkVertexFitterInterfaces/IVertexFitter.h"

// My class
#include "CalcEfficiency/CalcEffAlg.h"
#include "CalcEfficiency/TagAndProbe.h"
#include "CalcEfficiency/MuInfoGetter.h"
#include "CalcEfficiency/MuonExtUtils.h"
#include "CalcEfficiency/EventTree.h"
#include "CalcEfficiency/EventTreeFCBM.h"

using namespace std;

///THis function is constructor.
CalcEffAlg::CalcEffAlg(const std::string& name, ISvcLocator* pSvcLocator)
  : AthAlgorithm(name, pSvcLocator),
  m_configSvc( "TrigConf::TrigConfigSvc/TrigConfigSvc", name ),
  m_dsSvc( "TrigConf::DSConfigSvc/DSConfigSvc", name ),
  m_trigDecTool( "Trig::TrigDecisionTool/TrigDecisionTool" ),
  m_grlTool( "GoodRunsListSelectionTool/MyGRLTool" ),
  m_extrapolator("Trk::Extrapolator/AtlasExtrapolator"),
  m_vrtfitter("Trk::TrkVKalVrtFitter")
{
  ///(https://twiki.cern.ch/twiki/bin/view/Sandbox/WritingYourOwnAthenaAlgorithms)Notice the calls of the declareProperty("electron_Et_min_cut", m_electron_Et_min_cut = 20*GeV) in the constructor. This makes the C++ m_electron_Et_min_cut variable configurable from the Python job options. The first argument is a string containing the Python name of the variable. The second is the C++ variable with an optional equals-sign followed by a default value. Configuration from Python will be explained more later when we get to the job options.
  declareProperty( "message", m_message=2);
  declareProperty( "TrigDecToolName", m_trigDecTool );
  declareProperty( "OutputFile", m_etname );
  declareProperty( "TapMethod", m_tapmethod );
  declareProperty( "Extrapolate", m_useExt );
  declareProperty( "GRL", m_useGRL );
  declareProperty( "DataType", m_dataType );
}

StatusCode CalcEffAlg::initialize() {
  ATH_MSG_INFO("initialize()");
  ATH_MSG_INFO("My message: " << m_message);
  m_isFirstEvent = true; 

  //==============================================================
  //==  GRL Tools
  //==============================================================
  ATH_CHECK( m_grlTool.retrieve() );



  //==============================================================
  //==  Trigger Tools
  //==============================================================
  ATH_CHECK(m_configSvc.retrieve());
  ATH_CHECK(m_dsSvc.retrieve());
  ATH_CHECK(m_trigDecTool.retrieve());



  //==============================================================
  //==  Tools
  //==============================================================
  ATH_CHECK(m_extrapolator.retrieve());
  ATH_CHECK(m_vrtfitter.retrieve());



  //==============================================================
  //==  MuonExtrapolatorUtils Class
  //==============================================================
  m_ext.initialize( m_extrapolator );



  //==============================================================
  //==  VrtFitterUtils Class
  //==============================================================
  m_vft.initialize( m_vrtfitter );


  //==  EventTree Class
  //==============================================================
  if( m_tapmethod == "ClosebyMuon" ){
    m_etfcbm.initialize( m_etname );
  } else {
    m_et.initialize( m_etname );
  }


  //==============================================================
  //==  TagAndProbe Class
  //
  ///Check TagAndProbe.h about declare of addMesChain.
  ///int addMesChain( const string& name, const L1Item& mesL1, const string& mesHLT, const string& mesAddTag); 
  ///int initialize( const int& message,const bool& useExt,const std::string method,MuonExtUtils ext,VrtFitUtils vft,ToolHandle<Trig::TrigDecisionTool> tdt,const std::string dataType ); //!
  //==============================================================
  if( m_tapmethod == "ClosebyMuon" ){
    m_mig.initialize( 0, m_useExt, m_tapmethod, m_ext, m_vft, m_trigDecTool, m_dataType, "mu4", MuInfoGetter::L1_MU4, "HLT_mu4", "none" );
  } else {
    m_tap.initialize( 0, m_useExt, m_tapmethod, m_ext, m_vft, m_trigDecTool, m_dataType );
    m_tap.addMesChain( "mu4", TagAndProbe::L1_MU4, "HLT_mu4", "none" );
    m_tap.addMesChain( "mu6", TagAndProbe::L1_MU6, "HLT_mu6", "none" );
    m_tap.addMesChain( "mu6ms", TagAndProbe::L1_MU6, "HLT_mu6_msonly", "none" );
    m_tap.addMesChain( "mu10", TagAndProbe::L1_MU10, "HLT_mu10", "none" );
    m_tap.addMesChain( "mu10nc", TagAndProbe::L1_MU10, "HLT_mu10_nomucomb", "none" );
    m_tap.addMesChain( "mu11", TagAndProbe::L1_MU11, "HLT_mu11", "none" );
    m_tap.addMesChain( "mu11nc", TagAndProbe::L1_MU11, "HLT_mu11_nomucomb", "none" );
    m_tap.addMesChain( "mu14", TagAndProbe::L1_MU10, "HLT_mu14", "none" );
    m_tap.addMesChain( "mu18", TagAndProbe::L1_MU20, "HLT_mu18", "none" );
    m_tap.addMesChain( "mu20", TagAndProbe::L1_MU20, "HLT_mu20", "none" );
    m_tap.addMesChain( "mu20il", TagAndProbe::L1_MU20, "HLT_mu20_iloose_L1MU15", "none" );
    m_tap.addMesChain( "mu20ms", TagAndProbe::L1_MU20, "HLT_mu20_msonly", "none" );
    m_tap.addMesChain( "mu26im", TagAndProbe::L1_MU20, "HLT_mu26_imedium", "none" );
    m_tap.addMesChain( "mu26ivm", TagAndProbe::L1_MU20, "HLT_mu26_ivarmedium", "none" );
    m_tap.addMesChain( "mu50", TagAndProbe::L1_MU20, "HLT_mu50", "none" );
    m_tap.addMesChain( "mu60", TagAndProbe::L1_MU20, "HLT_mu60_0eta105_msonly", "none" );
    m_tap.addMesChain( "mu4FS", TagAndProbe::NOTHING, "HLT_mu4noL1", "none" );
    m_tap.addMesChain( "mu4FSMU6", TagAndProbe::L1_MU6, "HLT_mu20_mu8noL1", "HLT_mu20_mu8noL1" );
    m_tap.addMesChain( "mu6FS", TagAndProbe::NOTHING, "HLT_mu4noL1", "none" );
    m_tap.addMesChain( "mu6FSMU6", TagAndProbe::L1_MU6, "HLT_mu20_mu8noL1", "HLT_mu20_mu8noL1" );
    m_tap.addMesChain( "mu8FS", TagAndProbe::NOTHING, "HLT_mu4noL1", "none" );
    m_tap.addMesChain( "2mu6", TagAndProbe::L1_MU6, "HLT_2mu6", "HLT_mu6" );
    m_tap.addMesChain( "2mu10", TagAndProbe::L1_MU10, "HLT_2mu10", "HLT_mu10" );
    m_tap.addMesChain( "2mu10nocb", TagAndProbe::L1_MU10, "HLT_2mu10_nomucomb", "HLT_mu10" );
    m_tap.addMesChain( "mu11mu6", TagAndProbe::NOTHING, "HLT_mu11_nomucomb_mu6noL1_nscan03_L1MU11_2MU6_bTau", "HLT_mu11");
  }
  return StatusCode::SUCCESS;
}

StatusCode CalcEffAlg::finalize() {
  ATH_MSG_INFO("finalize()");
  if( m_tapmethod == "ClosebyMuon" ){
    m_etfcbm.finalize();
  } else {
    m_et.finalize();
  }
  return StatusCode::SUCCESS;
}

StatusCode CalcEffAlg::execute() {
  ATH_MSG_INFO("execute()");

  ///main function to do "Tag and Probe" .

  //==============================================================
  //=  Event information
  //==============================================================
  const xAOD::EventInfo* eventInfo = 0;
  StatusCode sc = evtStore()->retrieve(eventInfo);
  if(StatusCode::SUCCESS!=sc || !eventInfo) {
    ATH_MSG_WARNING("Could not retrieve EventInfo");
    return StatusCode::SUCCESS;
  }

  uint32_t runNumber = eventInfo->runNumber();
  unsigned long long eventNumber = eventInfo->eventNumber();
  int lumiBlock = eventInfo-> lumiBlock();
  float averageInteractionsPerCrossing =  eventInfo -> averageInteractionsPerCrossing();
  ATH_MSG_INFO("Run = " << runNumber << " : Event = " << eventNumber);
  bool isMC = true;
  if(!eventInfo->eventType(xAOD::EventInfo::IS_SIMULATION ) ){
    isMC = false;
  }

  // GRL
  if( !isMC && m_useGRL ){
    ATH_MSG_INFO("Skip this event via GRL");
    if(!m_grlTool->passRunLB(*eventInfo)) return StatusCode::SUCCESS; //checks the GRL and skips to next event if not passing
  } // end if not MC

  //==============================================================
  //==  Trigger Tools
  //==============================================================
  // retrieve muons
  const xAOD::MuonContainer* mus = 0;
  ATH_CHECK( evtStore()->retrieve( mus, "Muons" ) );
  // retrieve muon rois
  const xAOD::MuonRoIContainer* rois = 0;
  ATH_CHECK( evtStore()->retrieve( rois, "LVL1MuonRoIs" ) );

  // retrieve muon rois
  const xAOD::TrackParticleContainer* ftfs = 0;
  // do tag and probe
  cout << "eventNumber==========" << eventNumber << "========" << endl;
  if( m_tapmethod == "ClosebyMuon" ) {
    m_mig.clear();
  } else {
    m_tap.clear();
  }
  cout << "end m_tap.clear()" << endl;
  int Nquality = 0;
  if( m_tapmethod == "ClosebyMuon" ) {
    Nquality = m_mig.execute(mus, rois);
    cout << "end m_tap.execute()" << endl;
  } else {
    vector< string > passlist;
    bool passany = false;
    auto cgs = m_trigDecTool->getChainGroup( "HLT.*mu.*|L1_.*MU.*|HLT_noalg_L1.*MU.*" );
    //auto cgs = m_trigDecTool->getChainGroup( "HLT.*" );
    for ( auto &trig : cgs->getListOfTriggers() ) {
      auto cg = m_trigDecTool->getChainGroup( trig );
      bool isPassedCurrent = cg->isPassed();
      if( m_isFirstEvent ) cout << trig << " / " << isPassedCurrent << endl;
      //cout << trig << " / " << isPassedCurrent << endl;
      if ( isPassedCurrent ) {
        passlist.push_back( trig );
        //cout << "TRIGGER: " << trig << endl;
        passany = true;
      }
    }
    m_tap.eventTriggerDecision(passlist);
    m_tap.setProbes( mus, rois );
    cout << "end m_tap.setProbes()" << endl;
    m_tap.doProbeMatching( rois, ftfs );
    cout << "end m_tap.doProbeMatching()" << endl;
    //cout << m_tap.tagPhi()[0] << endl;
    m_isFirstEvent = false;
  }
  // fill results
  if(m_tapmethod == "ClosebyMuon" ){
    if( Nquality != 0 ) m_etfcbm.filltree( m_mig, eventNumber, runNumber, lumiBlock, averageInteractionsPerCrossing );
  } else {
    // fill results
    m_et.filltree( m_tap, eventNumber, runNumber, lumiBlock, averageInteractionsPerCrossing );
    cout << "end m_et.filltree()" << endl;
  }
  cout << "end m_et.filltree()" << endl;

  m_isFirstEvent = false;
  return StatusCode::SUCCESS;
}
