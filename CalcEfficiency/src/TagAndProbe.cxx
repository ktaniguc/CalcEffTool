#include <iostream>
#include <fstream>
#include <vector>

#include "TrigConfxAOD/xAODConfigTool.h"
#include "xAODTrigMuon/L2StandAloneMuon.h"
#include "xAODTrigMuon/L2StandAloneMuonContainer.h"
#include "xAODTrigMuon/L2CombinedMuon.h"
#include "xAODTrigMuon/L2CombinedMuonContainer.h"
#include "xAODTrigger/MuonRoIContainer.h"
#include "xAODTracking/TrackParticleContainer.h"

#include "CalcEfficiency/TagAndProbe.h"
#include "CalcEfficiency/ParticleSelecterTool.h"
#include "CalcEfficiency/Utils.h"

#include "TMath.h"
#include "TObjArray.h"
#include "TObjString.h"
#include "TVector3.h"

using namespace std;

TagAndProbe::TagAndProbe()
: m_trigDecTool( "Trig::TrigDecisionTool/TrigDecisionTool" )
{}

TagAndProbe::~TagAndProbe() {
}

int TagAndProbe::initialize( const int& message, 
                             const bool& useExt,
                             const std::string method,
                             MuonExtUtils ext,
                             VrtFitUtils vft,
                             ToolHandle<Trig::TrigDecisionTool> tdt,
                             const std::string dataType
                           )
{
/// This function depends on message, useExt, method, ext vft, tdt, dataType.
/// vecTrigEvent, m_trigEvent, ... is push_backed for each method.
/// m_tapType is ALL, L2 or EFF. 
  cout << "=== TagAndProbe : initialize ===" << endl;

  m_message     = message;
  m_method      = method;
  m_trigDecTool = tdt;
  m_ext         = ext;
  m_vft         = vft;
  m_useExt      = useExt;
  this -> dataType = dataType;



  if( m_method=="Ztap" ) {
// Z TagAndProbe setup
/// Ztap >> HLT_mu26_ivarmedium (L1_MU20)
    vector< string > vecTrigEvent;
    //vecTrigEvent.push_back( "HLT_mu20_iloose_L1MU15" );
    vecTrigEvent.push_back( "HLT_mu26_ivarmedium" );
    m_trigEvent.push_back( vecTrigEvent );
    m_trigTagL1.push_back( L1_MU20 );
    //m_trigTagHLT.push_back( "HLT_mu20_iloose_L1MU15" );
    m_trigTagHLT.push_back( "HLT_mu26_ivarmedium" );
    std::string tsSATE = "";
    getSATEName( "HLT_mu26_ivarmedium", tsSATE );
    m_trigTagSATEName.push_back( tsSATE );
    std::string tsCBTE = "";
    getCBTEName( "HLT_mu26_ivarmedium", tsCBTE );
    m_trigTagCBTEName.push_back( tsCBTE );
    m_tapMassLowerLimit.push_back( 90000. - 10000. );
    m_tapMassHigherLimit.push_back( 90000. + 10000. );
    m_tapMatchingdRL1Tag.push_back( -1 );
    m_tapMatchingdREFTag.push_back( 0.02 );
    m_tapMatchingdRL1Probe.push_back( -1 );
    m_tapMatchingdREFProbe.push_back( 0.02 );
    m_tapMatchingdREFMSProbe.push_back( 0.1 );
    m_tapType.push_back( ALL );
    m_isPassedEventTrig.push_back( false );
    m_tapNProcess = m_trigEvent.size();
  }
  else if( m_method=="JpsitapMC" ) {
///JpsitapMC TagAndProbe setup
///HLT_mu4 (L1_mu4)
    vector< string > vecTrigEvent;
    vecTrigEvent.push_back( "HLT_mu4" );
    m_trigEvent.push_back( vecTrigEvent );
    m_trigTagL1.push_back( L1_MU4 );
    m_trigTagHLT.push_back( "HLT_mu4" );
    std::string tsSATE = "";
    getSATEName( "HLT_mu4", tsSATE ); ///tsSATE is Stand Alone Trigger EVent.
    m_trigTagSATEName.push_back( tsSATE ); 
    std::string tsCBTE = "";
    getCBTEName( "HLT_mu4", tsCBTE );
    m_trigTagCBTEName.push_back( tsCBTE );
    m_tapMassLowerLimit.push_back( 3099. - 300. ); ///Jpsi mass is about 3000MeV, so LowerLimit is 3000MeV - 300MeV.
    m_tapMassHigherLimit.push_back( 3099. + 300. );
    m_tapMatchingdRL1Tag.push_back( -1 );
    m_tapMatchingdREFTag.push_back( 0.02 );
    m_tapMatchingdRL1Probe.push_back( -1 );
    m_tapMatchingdREFProbe.push_back( 0.02 );
    m_tapMatchingdREFMSProbe.push_back( 0.1 );
    m_tapType.push_back( ALL );
    m_isPassedEventTrig.push_back( false );
    m_tapNProcess = m_trigEvent.size();
  }
  else if( m_method=="JpsitapUB" ) {
    vector< string > vecTrigEvent;
    vecTrigEvent.push_back( "HLT_mu10" );
    vecTrigEvent.push_back( "HLT_mu14" );
    vecTrigEvent.push_back( "HLT_mu20" );
    m_trigEvent.push_back( vecTrigEvent );
    m_trigTagL1.push_back( L1_MU20 );
    m_trigTagHLT.push_back( "HLT_mu20" );
    std::string tsSATE = "";
    getSATEName( "HLT_mu20", tsSATE );
    m_trigTagSATEName.push_back( tsSATE );
    std::string tsCBTE = "";
    getCBTEName( "HLT_mu20", tsCBTE );
    m_trigTagCBTEName.push_back( tsCBTE );
    m_tapMassLowerLimit.push_back( 3099. - 300. );
    m_tapMassHigherLimit.push_back( 3099. + 300. );
    m_tapMatchingdRL1Tag.push_back( -1 );
    m_tapMatchingdREFTag.push_back( 0.02 );
    m_tapMatchingdRL1Probe.push_back( -1 );
    m_tapMatchingdREFProbe.push_back( 0.02 );
    m_tapMatchingdREFMSProbe.push_back( 0.1 );
    m_tapType.push_back( ALL );
    m_isPassedEventTrig.push_back( false );
    m_tapNProcess = m_trigEvent.size();
  }
  else if( m_method=="Jpsitap" ) {
///Jpsitap Tagandprobe setup
///if datatype is data17, vectrigevent1 is HLT_mu20_2mu2noL1_JpsimumuFS.
///else vectrigevent1 is HLT_mu20_2mu0noL1_JpsimumuFS.
// HLT_MU20 ( L1_MU20 )

    ///vecTrigEvent1
    vector< string > vecTrigEvent1;
    if ( dataType == "data17" ){
      vecTrigEvent1.push_back( "HLT_mu20_2mu2noL1_JpsimumuFS" );
    } else {
      vecTrigEvent1.push_back( "HLT_mu20_2mu0noL1_JpsimumuFS" );
    }
    m_trigEvent.push_back( vecTrigEvent1 );
    m_trigTagL1.push_back( L1_MU20 );
    m_trigTagHLT.push_back( "HLT_mu20" );
    std::string tsSATE = "";
    getSATEName( "HLT_mu20", tsSATE );
    m_trigTagSATEName.push_back( tsSATE );
    std::string tsCBTE = "";
    getCBTEName( "HLT_mu20", tsCBTE );
    m_trigTagCBTEName.push_back( tsCBTE );
    m_tapMassLowerLimit.push_back( 3099. - 300. );
    m_tapMassHigherLimit.push_back( 3099. + 300. );
    m_tapMatchingdRL1Tag.push_back( -1 );
    m_tapMatchingdREFTag.push_back( 0.02 );
    m_tapMatchingdRL1Probe.push_back( -1 );
    m_tapMatchingdREFProbe.push_back( 0.02 );
    m_tapMatchingdREFMSProbe.push_back( 0.1 );
    m_tapType.push_back( L2 ); ///L2
    m_isPassedEventTrig.push_back( false );
    m_tapNProcess = m_trigEvent.size();
    ///vecTrigEvent2; trigger is HLT_mu20_2mu4_JpsimumuL2.
    vector< string > vecTrigEvent2;
    vecTrigEvent2.push_back( "HLT_mu20_2mu4_JpsimumuL2" );
    m_trigEvent.push_back( vecTrigEvent2 );
    m_trigTagL1.push_back( L1_MU20 );
    m_trigTagHLT.push_back( "HLT_mu20" );
    tsSATE = "";
    getSATEName( "HLT_mu20", tsSATE );
    m_trigTagSATEName.push_back( tsSATE );
    tsCBTE = "";
    getCBTEName( "HLT_mu20", tsCBTE );
    m_trigTagCBTEName.push_back( tsCBTE );
    m_tapMassLowerLimit.push_back( 3099. - 300. );
    m_tapMassHigherLimit.push_back( 3099. + 300. );
    m_tapMatchingdRL1Tag.push_back( -1 );
    m_tapMatchingdREFTag.push_back( 0.02 );
    m_tapMatchingdRL1Probe.push_back( -1 );
    m_tapMatchingdREFProbe.push_back( 0.02 );
    m_tapMatchingdREFMSProbe.push_back( 0.1 );
    m_tapType.push_back( EF ); ///EF
    m_isPassedEventTrig.push_back( false );
    m_tapNProcess = m_trigEvent.size();
  }
  else if( m_method=="JPZtap" ) {
    ///JPZTAP Tagandprobe 
    ///HLT_mu26_ivarmedium (L1_MU20)

    ///vecTrigEvent1; this is Z tap. 
    vector< string > vecTrigEvent1;
    if( dataType == "data15" ){

      vecTrigEvent1.push_back( "HLT_mu20_iloose_L1MU15" );
      m_trigEvent.push_back( vecTrigEvent1 );
      m_trigTagL1.push_back( L1_MU20 );
      m_trigTagHLT.push_back( "HLT_mu20_iloose_L1MU15" );
      std::string tsSATE = "";
      getSATEName( "HLT_mu20_iloose_L1MU15", tsSATE );
      m_trigTagSATEName.push_back( tsSATE );
      std::string tsCBTE = "";
      getCBTEName( "HLT_mu20_iloose_L1MU15", tsCBTE );
      m_trigTagCBTEName.push_back( tsCBTE );
    }
    if( dataType == "data16" ){

      vecTrigEvent1.push_back( "HLT_mu26_ivarmedium" );
      m_trigEvent.push_back( vecTrigEvent1 );
      m_trigTagL1.push_back( L1_MU20 );
      m_trigTagHLT.push_back( "HLT_mu26_ivarmedium" );
      std::string tsSATE = "";
      getSATEName( "HLT_mu26_ivarmedium", tsSATE );
      m_trigTagSATEName.push_back( tsSATE );
      std::string tsCBTE = "";
      getCBTEName( "HLT_mu26_ivarmedium", tsCBTE );
      m_trigTagCBTEName.push_back( tsCBTE );
    }
    if( dataType == "data17" ){

      vecTrigEvent1.push_back( "HLT_mu26_ivarmedium" );
      m_trigEvent.push_back( vecTrigEvent1 );
      m_trigTagL1.push_back( L1_MU20 );
      m_trigTagHLT.push_back( "HLT_mu26_ivarmedium" );
      std::string tsSATE = "";
      getSATEName( "HLT_mu26_ivarmedium", tsSATE );
      m_trigTagSATEName.push_back( tsSATE );
      std::string tsCBTE = "";
      getCBTEName( "HLT_mu26_ivarmedium", tsCBTE );
      m_trigTagCBTEName.push_back( tsCBTE );
    }
    m_tapMassLowerLimit.push_back( 90000. - 10000. );
    m_tapMassHigherLimit.push_back( 90000. + 10000. );
    m_tapMatchingdRL1Tag.push_back( -1 );
    m_tapMatchingdREFTag.push_back( 0.02 );
    m_tapMatchingdRL1Probe.push_back( -1 );
    m_tapMatchingdREFProbe.push_back( 0.02 );
    m_tapMatchingdREFMSProbe.push_back( 0.1 );
    m_tapType.push_back( ALL );
    m_isPassedEventTrig.push_back( false );
    m_tapNProcess = m_trigEvent.size();

    ///vecTrigEvent2 ; this is JP tap. JP tap is two trrigers
    ///HLT_mu20_2mu0noL1_JpsimumuFS ( or HLT_mu20_2mu2noL1_JpsimumuFS) and HLT_mu20_2mu4_JpsimumuL2.
    vector< string > vecTrigEvent2;
    if ( dataType == "data15" ){

      vecTrigEvent2.push_back( "HLT_mu18_2mu0noL1_JpsimumuFS" );
      m_trigEvent.push_back( vecTrigEvent2 );
      m_trigTagL1.push_back( L1_MU20 );
      m_trigTagHLT.push_back( "HLT_mu18" );
      std::string tsSATE = "";
      getSATEName( "HLT_mu18", tsSATE );
      m_trigTagSATEName.push_back( tsSATE );
      std::string tsCBTE = "";
      getCBTEName( "HLT_mu18", tsCBTE );
      m_trigTagCBTEName.push_back( tsCBTE );
    } else if ( dataType == "data16" ){

      vecTrigEvent2.push_back( "HLT_mu20_2mu0noL1_JpsimumuFS" );
      m_trigEvent.push_back( vecTrigEvent2 );
      m_trigTagL1.push_back( L1_MU20 );
      m_trigTagHLT.push_back( "HLT_mu20" );
      std::string tsSATE = "";
      getSATEName( "HLT_mu20", tsSATE );
      m_trigTagSATEName.push_back( tsSATE );
      std::string tsCBTE = "";
      getCBTEName( "HLT_mu20", tsCBTE );
      m_trigTagCBTEName.push_back( tsCBTE );
    } else if ( dataType == "data17" ) {

      vecTrigEvent2.push_back( "HLT_mu20_2mu2noL1_JpsimumuFS" );
      m_trigEvent.push_back( vecTrigEvent2 );
      m_trigTagL1.push_back( L1_MU20 );
      m_trigTagHLT.push_back( "HLT_mu20" );
      std::string tsSATE = "";
      getSATEName( "HLT_mu20", tsSATE );
      m_trigTagSATEName.push_back( tsSATE );
      std::string tsCBTE = "";
      getCBTEName( "HLT_mu20", tsCBTE );
      m_trigTagCBTEName.push_back( tsCBTE );
    }
    m_tapMassLowerLimit.push_back( 3099. - 300. );
    m_tapMassHigherLimit.push_back( 3099. + 300. );
    m_tapMatchingdRL1Tag.push_back( -1 );
    m_tapMatchingdREFTag.push_back( 0.02 );
    m_tapMatchingdRL1Probe.push_back( -1 );
    m_tapMatchingdREFProbe.push_back( 0.02 );
    m_tapMatchingdREFMSProbe.push_back( 0.1 );
    m_tapType.push_back( L2 ); ///L2
    m_isPassedEventTrig.push_back( false );
    m_tapNProcess = m_trigEvent.size();

    vector< string > vecTrigEvent3;
    if (dataType == "data15"){

      vecTrigEvent3.push_back( "HLT_mu18_2mu4_JpsimumuL2" );
      m_trigEvent.push_back( vecTrigEvent3 );
      m_trigTagL1.push_back( L1_MU20 );
      m_trigTagHLT.push_back( "HLT_mu18" );
      std::string tsSATE = "";
      getSATEName( "HLT_mu18", tsSATE );
      m_trigTagSATEName.push_back( tsSATE );
      std::string tsCBTE = "";
      m_trigTagCBTEName.push_back( tsCBTE );
      getCBTEName( "HLT_mu20", tsCBTE );
    } else if ( dataType == "data16" || dataType == "data17" ){

      vecTrigEvent3.push_back( "HLT_mu20_2mu4_JpsimumuL2" );
      m_trigEvent.push_back( vecTrigEvent3 );
      m_trigTagL1.push_back( L1_MU20 );
      m_trigTagHLT.push_back( "HLT_mu20" );
      std::string tsSATE = "";
      getSATEName( "HLT_mu20", tsSATE );
      m_trigTagSATEName.push_back( tsSATE );
      std::string tsCBTE = "";
      m_trigTagCBTEName.push_back( tsCBTE );
      getCBTEName( "HLT_mu20", tsCBTE );
    }
    m_tapMassLowerLimit.push_back( 3099. - 300. );
    m_tapMassHigherLimit.push_back( 3099. + 300. );
    m_tapMatchingdRL1Tag.push_back( -1 );
    m_tapMatchingdREFTag.push_back( 0.02 );
    m_tapMatchingdRL1Probe.push_back( -1 );
    m_tapMatchingdREFProbe.push_back( 0.02 );
    m_tapMatchingdREFMSProbe.push_back( 0.1 );
    m_tapType.push_back( EF );  ///EF
    m_isPassedEventTrig.push_back( false );
    m_tapNProcess = m_trigEvent.size();
  }
  else if( m_method=="NoMass" ) {
    ///this method has no mass limits ( Lowerlimit is 0 , Higherlimit is 1000000.).
    vector< string > vecTrigEvent;
    //vecTrigEvent.push_back( "HLT_mu20_iloose_L1MU15" );
    vecTrigEvent.push_back( "HLT_mu26_ivarmedium" );
    m_trigEvent.push_back( vecTrigEvent );
    m_trigTagL1.push_back( L1_MU20 );
    //m_trigTagHLT.push_back( "HLT_mu20_iloose_L1MU15" );
    m_trigTagHLT.push_back( "HLT_mu26_ivarmedium" );
    std::string tsSATE = "";
    getSATEName( "HLT_mu26_ivarmedium", tsSATE );
    m_trigTagSATEName.push_back( tsSATE );
    std::string tsCBTE = "";
    getCBTEName( "HLT_mu26_ivarmedium", tsCBTE );
    m_trigTagCBTEName.push_back( tsCBTE );
    m_tapMassLowerLimit.push_back( 0 );
    m_tapMassHigherLimit.push_back( 1000000. );
    m_tapMatchingdRL1Tag.push_back( 0.12 );
    m_tapMatchingdREFTag.push_back( 0.05 );
    m_tapMatchingdRL1Probe.push_back( 0.12 );
    m_tapMatchingdREFProbe.push_back( 0.05 );
    m_tapMatchingdREFMSProbe.push_back( 0.1 );
    m_tapType.push_back( ALL );
    m_isPassedEventTrig.push_back( false );
    m_tapNProcess = m_trigEvent.size();
  }
  else if( m_method=="L1tap" ) {
    vector< string > vecTrigEvent;
    vecTrigEvent.push_back( "No" );
    m_trigEvent.push_back( vecTrigEvent );
    m_trigTagL1.push_back( L1_MU4 );
    m_trigTagHLT.push_back( "No" );
    std::string tsSATE = "No";
    m_trigTagSATEName.push_back( tsSATE );
    std::string tsCBTE = "No";
    m_trigTagCBTEName.push_back( tsCBTE );
    m_tapMassLowerLimit.push_back( 0 );
    m_tapMassHigherLimit.push_back( 1000000. );
    m_tapMatchingdRL1Tag.push_back( -1 );
    m_tapMatchingdREFTag.push_back( 0.02 );
    m_tapMatchingdRL1Probe.push_back( -1 );
    m_tapMatchingdREFProbe.push_back( 0.02 );
    m_tapMatchingdREFMSProbe.push_back( 0.1 );
    m_tapType.push_back( ALL );
    m_isPassedEventTrig.push_back( false );
    m_tapNProcess = m_trigEvent.size();
  }
  else if( m_method=="NoTag" ) {
    vector< string > vecTrigEvent;
    vecTrigEvent.push_back( "No" );
    m_trigEvent.push_back( vecTrigEvent );
    m_trigTagL1.push_back( NOTHING );
    m_trigTagHLT.push_back( "No" );
    std::string tsSATE = "No";
    m_trigTagSATEName.push_back( tsSATE );
    std::string tsCBTE = "No";
    m_trigTagCBTEName.push_back( tsCBTE );
    m_tapMassLowerLimit.push_back( 0 );
    m_tapMassHigherLimit.push_back( 1000000. );
    m_tapMatchingdRL1Tag.push_back( -1 );
    m_tapMatchingdREFTag.push_back( 0.02 );
    m_tapMatchingdRL1Probe.push_back( -1 );
    m_tapMatchingdREFProbe.push_back( 0.02 );
    m_tapMatchingdREFMSProbe.push_back( 0.1 );
    m_tapType.push_back( ALL );
    m_isPassedEventTrig.push_back( false );
    m_tapNProcess = m_trigEvent.size();
  }
  else if( m_method=="Jpsitap5TeV" ) {
    vector< string > vecTrigEvent;
    vecTrigEvent.push_back( "HLT_mu14" );
    m_trigEvent.push_back( vecTrigEvent );
    m_trigTagL1.push_back( L1_MU10 );
    m_trigTagHLT.push_back( "HLT_mu14" );
    std::string tsSATE = "";
    getSATEName( "HLT_mu14", tsSATE );
    m_trigTagSATEName.push_back( tsSATE );
    std::string tsCBTE = "";
    getCBTEName( "HLT_mu14", tsCBTE );
    m_trigTagCBTEName.push_back( tsCBTE );
    m_tapMassLowerLimit.push_back( 3099. - 300. );
    m_tapMassHigherLimit.push_back( 3099. + 300. );
    m_tapMatchingdRL1Tag.push_back( -1 );
    m_tapMatchingdREFTag.push_back( 0.02 );
    m_tapMatchingdRL1Probe.push_back( -1 );
    m_tapMatchingdREFProbe.push_back( 0.02 );
    m_tapMatchingdREFMSProbe.push_back( 0.1 );
    m_tapType.push_back( ALL );
    m_isPassedEventTrig.push_back( false );
    m_tapNProcess = m_trigEvent.size();
  }
  else if( m_method=="JpsitapHIP" ) {
    vector< string > vecTrigEvent;
    vecTrigEvent.push_back( "HLT_mu4" );
    m_trigEvent.push_back( vecTrigEvent );
    m_trigTagL1.push_back( L1_MU4 );
    m_trigTagHLT.push_back( "HLT_mu4" );
    std::string tsSATE = "";
    getSATEName( "HLT_mu4", tsSATE );
    m_trigTagSATEName.push_back( tsSATE );
    std::string tsCBTE = "";
    getCBTEName( "HLT_mu4", tsCBTE );
    m_trigTagCBTEName.push_back( tsCBTE );
    m_tapMassLowerLimit.push_back( 3099. - 300. );
    m_tapMassHigherLimit.push_back( 3099. + 300. );
    m_tapMatchingdRL1Tag.push_back( -1 );
    m_tapMatchingdREFTag.push_back( 0.02 );
    m_tapMatchingdRL1Probe.push_back( -1 );
    m_tapMatchingdREFProbe.push_back( 0.02 );
    m_tapMatchingdREFMSProbe.push_back( 0.1 );
    m_tapType.push_back( ALL );
    m_isPassedEventTrig.push_back( false );
    m_tapNProcess = m_trigEvent.size();
  }
  else {
    cout << "TagAndProbe : ERROR : Method you registered is not implemented ! " << endl;
    return 1;
  }

  ///cout information about tap process.
  cout << "= Method   : " << method << endl;
  cout << "= NProcess : " << m_tapNProcess << endl;
  for( int i=0; i < m_tapNProcess; i++ ) {
    cout << "= " << i << "-th process ( type : " << m_tapType[i] << ")" << "\n";
    const int nTE = m_trigEvent[i].size();
    for( int iTE=0; iTE<nTE; iTE++ ){
      cout << "=== Event Trigger   : " << m_trigEvent[i][iTE] << "\n";
    }
    cout << "=== Tag L1 Trigger  : " << m_trigTagL1[i] << "\n";
    cout << "=== Tag HLT Trigger : " << m_trigTagHLT[i] << endl;
  }
  cout << "================================" << endl;
  
  return 0;  
}

int TagAndProbe::addMesChain( const string& name, const L1Item& mesL1, const string& mesHLT, const string& mesAddTag ) {
  ///name is trriger name. mesL1 is L1 trriger pT. mesHLT is HLT trigger pT. mesAddTag is ??. 
  /// for example  "m_tap.addMesChain( "mu11", TagAndProbe::L1_MU11, "HLT_mu11", "none" )";

  if( m_message > 0 ) cout << "=== TagAndProbe : addChain ===" << endl;
  unsigned int Length = mesHLT.length();
  unsigned int msonly = mesHLT.find( "msonly", 0 );
  unsigned int nocb   = mesHLT.find( "nomucomb", 0 );
  unsigned int bronly = mesHLT.find( "0eta105", 0 );
  unsigned int nol1   = mesHLT.find( "noL1", 0 );
  m_trigMesName.push_back( name );
  m_trigMesL1.push_back( mesL1 );
  m_trigMesHLT.push_back( mesHLT );
  m_trigMesAddTagReq.push_back( mesAddTag );
  m_trigMesMSonly.push_back( (msonly<Length)? 1:0 );
  m_trigMesNoMucomb.push_back( (nocb<Length)? 1:0 );
  m_trigMesBRonly.push_back( (bronly<Length)? 1:0 );
  m_trigMesNoL1.push_back( (nol1<Length)? 1:0 );
  
  m_trigNMes = m_trigMesName.size();

  std::string trigMesName = "";
  getSATEName( mesHLT, trigMesName );
  m_trigMesSATEName . push_back( trigMesName );
  std::string trigMesCBTEName = "";
  getCBTEName( mesHLT, trigMesCBTEName );
  m_trigMesCBTEName . push_back( trigMesCBTEName );
  
  cout << "= " << name << " ( " << mesL1 << ", " << mesHLT << ": MSonly=" << (msonly<Length) << ", BRonly=" << (bronly<Length) << ", noL1=" << (nol1<Length) << ", TagReq=" << mesAddTag << ", SATEName=" << trigMesName.c_str() << ", CBTEName=" << trigMesCBTEName.c_str() << " )" << endl; 
  return 0;  
}

int TagAndProbe::eventTriggerDecision( const vector< string >& passedtriggers ) {
  ///input is passedtriggers.
  const int nTrig = passedtriggers.size();
  for( int iproc=0; iproc<m_tapNProcess; iproc++ ) {
    m_isPassedEventTrig[iproc] = false;
    const int nTE = m_trigEvent[iproc].size();
    for( int iTE=0; iTE<nTE; iTE++ ){
      // only for L1tap mode
      if( m_trigEvent[iproc][iTE] == "No" ) {
        m_isPassedEventTrig[iproc] = true;
        break;
      }
      for( int iTrig=0; iTrig<nTrig; iTrig++ ) {
        if( m_trigEvent[iproc][iTE] == passedtriggers[iTrig] ) {
          m_isPassedEventTrig[iproc] = true;
          if( m_message > 1 ) cout << "=== Event Passed ! ===" << endl;
          break;
        }
      }
    }
  }
  return 0;  
}

void TagAndProbe::clear() {
  m_TPpairs.clear();
  m_TPpairsProcess.clear();
  m_TPpairsTagdRL1.clear();
  m_TPpairsTagdREF.clear();
  m_TPpairsReqTagdRL1.clear();
  m_TPpairsReqTagdREF.clear();
  m_TPpairsReqProbedRL1.clear();
  m_TPpairsReqProbedREF.clear();
  m_TPpairsReqProbedREFMS.clear();
  m_TPpairsTagL1num.clear();
  m_TPpairsTagL1Pt.clear();
  m_TPpairsTagL1Eta.clear();
  m_TPpairsTagL1Phi.clear();
  m_TPpairsTagSAPt.clear();
  m_TPpairsTagSAEta.clear();
  m_TPpairsTagSAPhi.clear();
  m_TPpairsTagCBPt.clear();
  m_TPpairsTagCBEta.clear();
  m_TPpairsTagCBPhi.clear();
  m_TPpairsTagEFPt.clear();
  m_TPpairsTagEFEta.clear();
  m_TPpairsTagEFPhi.clear();

  /// clear variables which is used ttre (t_tap).
  m_tagProc.clear();
  m_tpSumReqL1dR.clear();
  m_tpSumReqEFdR.clear();
  m_tagL1dR.clear();
  m_tagEFdR.clear();
  m_tagReqL1dR.clear();
  m_tagReqEFdR.clear();
  m_tagPt.clear();
  m_tagEta.clear();
  m_tagExtEta.clear();
  m_tagExtInnEta.clear();
  m_tagPhi.clear();
  m_tagExtPhi.clear();
  m_tagExtInnPhi.clear();
  m_tagd0.clear();
  m_tagz0.clear();
  m_tagCharge.clear();
  m_tagL1Pt.clear();
  m_tagL1Eta.clear();
  m_tagL1Phi.clear();
  m_tagSAPt.clear();
  m_tagSAEta.clear();
  m_tagSAPhi.clear();
  m_tagCBPt.clear();
  m_tagCBEta.clear();
  m_tagCBPhi.clear();
  m_tagEFPt.clear();
  m_tagEFEta.clear();
  m_tagEFPhi.clear();
  m_probePt.clear();
  m_probeMSPt.clear();//kayamash
  m_probeEta.clear();
  m_probeExtEta.clear();
  m_probeExtInnEta.clear();
  m_probePhi.clear();
  m_probeExtPhi.clear();
  m_probeExtInnPhi.clear();
  m_probed0.clear();
  m_probez0.clear();
  m_probeCharge.clear();
  //
  m_probeSegmentN.clear();
  m_probeSegmentX.clear();
  m_probeSegmentY.clear();
  m_probeSegmentZ.clear();
  m_probeSegmentPx.clear();
  m_probeSegmentPy.clear();
  m_probeSegmentPz.clear();
  m_probeSegmentChiSquared.clear();
  m_probeSegmentNumberDoF.clear();
  m_probeSegmentSector.clear();
  m_probeSegmentChamberIndex.clear();
  m_probeSegmentEtaIndex.clear();
  m_probeSegmentNPrecisionHits.clear();
  m_probeSegmentNPhiLayers.clear();
  m_probeSegmentNTrigEtaLayers.clear();
  /*for(int nSeg = 0; nSeg < 20; nSeg++){
    m_probeSegmentX[nSeg].clear();
  }*/
  //
  m_tpVrtDx.clear();
  m_tpVrtDy.clear();
  m_tpVrtDz.clear();
  m_tpVrtChi2.clear();
  m_tpVrtNdof.clear();
  m_probePassedEFTAG.clear();
  m_probeEFTAGdR.clear();
  m_probeEFTAGtpdR.clear();
  m_probeEFTAGPt.clear();
  m_probeEFTAGEta.clear();
  m_probeEFTAGPhi.clear();
  m_probePassedL1.clear();
  m_probeL1dR.clear();
  m_probeL1tpdR.clear();
  m_probeL1Pt.clear();
  m_probeL1Eta.clear();
  m_probeL1Phi.clear();
  m_probePassedSA.clear();
  m_probeSAdR.clear();
  m_probeSAtpdR.clear();
  m_probeSAPt.clear();
  m_probeSAEta.clear();
  m_probeSAPhi.clear();
  m_probeSAEtaMS.clear();
  m_probeSAPhiMS.clear();
  m_probeSAEtaBE.clear();
  m_probeSAPhiBE.clear();
  //
  m_probeSATgcPt.clear();
  m_probeSAPtBarrelRadius.clear();
  m_probeSAPtBarrelSagitta.clear();
  m_probeSAPtEndcapAlpha.clear();
  m_probeSAPtEndcapBeta.clear();
  m_probeSAPtEndcapRadius.clear();
  m_probeSAPtCSC.clear();
  m_probeSAsAddress.clear();

  m_probeSAroiEta.clear();
  m_probeSAroiPhi.clear();
  m_probeSAisRpcFailure.clear();
  m_probeSAisTgcFailure.clear();
  //
  m_probeSAsuperPointRBI.clear(); 
  m_probeSAsuperPointRBM.clear(); 
  m_probeSAsuperPointRBO.clear(); 
  m_probeSAsuperPointREI.clear(); 
  m_probeSAsuperPointREM.clear(); 
  m_probeSAsuperPointREO.clear(); 
  m_probeSAsuperPointREE.clear(); 
  m_probeSAsuperPointRCSC.clear();
  m_probeSAsuperPointRBEE.clear();
  m_probeSAsuperPointRBME.clear();
  //
  m_probeSAsuperPointZBI.clear(); 
  m_probeSAsuperPointZBM.clear(); 
  m_probeSAsuperPointZBO.clear(); 
  m_probeSAsuperPointZEI.clear(); 
  m_probeSAsuperPointZEM.clear(); 
  m_probeSAsuperPointZEO.clear(); 
  m_probeSAsuperPointZEE.clear(); 
  m_probeSAsuperPointZCSC.clear();
  m_probeSAsuperPointZBEE.clear();
  m_probeSAsuperPointZBME.clear();
  //
  m_probeSAsuperPointSlopeBI.clear(); 
  m_probeSAsuperPointSlopeBM.clear(); 
  m_probeSAsuperPointSlopeBO.clear(); 
  m_probeSAsuperPointSlopeEI.clear(); 
  m_probeSAsuperPointSlopeEM.clear(); 
  m_probeSAsuperPointSlopeEO.clear(); 
  m_probeSAsuperPointSlopeEE.clear(); 
  m_probeSAsuperPointSlopeCSC.clear();
  m_probeSAsuperPointSlopeBEE.clear();
  m_probeSAsuperPointSlopeBME.clear();
  //
  m_probeSAsuperPointInterceptBI.clear(); 
  m_probeSAsuperPointInterceptBM.clear(); 
  m_probeSAsuperPointInterceptBO.clear(); 
  m_probeSAsuperPointInterceptEI.clear(); 
  m_probeSAsuperPointInterceptEM.clear(); 
  m_probeSAsuperPointInterceptEO.clear(); 
  m_probeSAsuperPointInterceptEE.clear(); 
  m_probeSAsuperPointInterceptCSC.clear();
  m_probeSAsuperPointInterceptBEE.clear();
  m_probeSAsuperPointInterceptBME.clear();
  //
  m_probeSAsuperPointChi2BI.clear(); 
  m_probeSAsuperPointChi2BM.clear(); 
  m_probeSAsuperPointChi2BO.clear(); 
  m_probeSAsuperPointChi2EI.clear(); 
  m_probeSAsuperPointChi2EM.clear(); 
  m_probeSAsuperPointChi2EO.clear(); 
  m_probeSAsuperPointChi2EE.clear(); 
  m_probeSAsuperPointChi2CSC.clear();
  m_probeSAsuperPointChi2BEE.clear();
  m_probeSAsuperPointChi2BME.clear();
  //
  m_probeSArpcHitX.clear();
  m_probeSArpcHitY.clear();
  m_probeSArpcHitZ.clear();
  m_probeSArpcHitR.clear();
  m_probeSArpcHitEta.clear();
  m_probeSArpcHitPhi.clear();
  m_probeSArpcHitStationNumber.clear();
  m_probeSArpcHitStationName.clear();

  m_probeSAmdtHitIsOutlier.clear();
  m_probeSAmdtHitChamber.clear();
  m_probeSAmdtHitR.clear();
  m_probeSAmdtHitZ.clear();
  m_probeSAmdtHitPhi.clear();
  m_probeSAmdtHitResidual.clear();

  m_probeSAroadAw.clear();
  m_probeSAroadBw.clear();
  m_probeSAzMin.clear();
  m_probeSAzMax.clear();
  m_probeSArMin.clear();
  m_probeSArMax.clear();
  m_probeSAetaMin.clear();
  m_probeSAetaMax.clear();
  //
  m_probePassedCB.clear();
  m_probeCBdR.clear();
  m_probeCBtpdR.clear();
  m_probeCBPt.clear();
  m_probeCBEta.clear();
  m_probeCBPhi.clear();
  m_probePassedFTF.clear();
  m_probeFTFdR.clear();
  m_probeFTFPt.clear();
  m_probeFTFEta.clear();
  m_probeFTFPhi.clear();
  m_probePassedEF.clear();
  m_probeEFdR.clear();
  m_probeEFtpdR.clear();
  m_probeEFPt.clear();
  m_probeEFEta.clear();
  m_probeEFPhi.clear();
  return;
}

int TagAndProbe::setProbes( const xAOD::MuonContainer* muons, 
                            const xAOD::MuonRoIContainer* rois ) {
  ///main function for tag and probe.
  ///using xAOD container , loop .
  // first muon loop
  xAOD::MuonContainer::const_iterator mu_itr1 = muons->begin();
  xAOD::MuonContainer::const_iterator mu_end  = muons->end();

  if( m_message>1 ) cout << "NMuon : " << muons->size() << endl;
  cout << "NMuon : " << muons->size() << endl;
  for ( ; mu_itr1!=mu_end; ++mu_itr1 ) {
    int quality = m_pst.getQualityOfTrack( (*mu_itr1) );///Look at Particleselectertool.cxx about getQualityOfTrack.
    //cout << "quality: " << quality << endl;
    if( quality<0 ) continue;
    // second muon loop
    xAOD::MuonContainer::const_iterator mu_itr2 = mu_itr1;
    for ( mu_itr2++; mu_itr2!=mu_end; ++mu_itr2 ) {
      int quality2 = m_pst.getQualityOfTrack( (*mu_itr2) );
    cout << "quality2: " << quality2 << endl;
      if( quality2<0 ) continue;
      // Pair Selection 
      const double mu1Pt     = (*mu_itr1)->pt();
      const double mu1Eta    = (*mu_itr1)->eta();
      const double mu1Phi    = (*mu_itr1)->phi();
      const double mu1Charge = (*mu_itr1)->charge();
      const double mu2Pt     = (*mu_itr2)->pt();
      const double mu2Eta    = (*mu_itr2)->eta();
      const double mu2Phi    = (*mu_itr2)->phi();
      const double mu2Charge = (*mu_itr2)->charge();
      if( mu1Charge*mu2Charge > 0 ) continue;
      TLorentzVector lvmu1, lvmu2, lvdimu;
      lvmu1.SetPtEtaPhiM( mu1Pt, mu1Eta, mu1Phi, 105.6 );
      lvmu2.SetPtEtaPhiM( mu2Pt, mu2Eta, mu2Phi, 105.6 );
      lvdimu = lvmu1 + lvmu2;
      const double dimuMass = lvdimu.M();
      const double dimuDphi = lvmu1.DeltaPhi( lvmu2 );
      cout << "Muon1 : " << mu1Pt << ", Muon2 : " << mu2Pt << endl;
      cout << "Mass:  " << dimuMass << endl;
      if( m_message>1 ) cout << "Muon1 : " << mu1Pt << ", Muon2 : " << mu2Pt << endl;
      if( m_message>1 ) cout << "Mass:  " << dimuMass << endl;
      for( int iproc=0; iproc<m_tapNProcess; iproc++ ) {
        if( m_isPassedEventTrig[iproc] == false ) continue;
        vector< pair< const xAOD::Muon*, const xAOD::Muon* > > TPpair;
        if( m_tapMassLowerLimit[iproc] < dimuMass && dimuMass < m_tapMassHigherLimit[iproc] && fabs( dimuDphi )<3.0 ) {
          cout << "Type" << m_tapType[iproc] << " mass window : pass" << endl;
          

          double tmpdR1L1Tag = ( m_tapMatchingdRL1Tag[iproc]>0 )? m_tapMatchingdRL1Tag[iproc]:dRL1byPt( mu1Pt ); 
          double tmpdR2L1Tag = ( m_tapMatchingdRL1Tag[iproc]>0 )? m_tapMatchingdRL1Tag[iproc]:dRL1byPt( mu2Pt ); 
          double tmpdR1L1Probe = ( m_tapMatchingdRL1Probe[iproc]>0 )? m_tapMatchingdRL1Probe[iproc]:dRL1byPt( mu1Pt ); 
          double tmpdR2L1Probe = ( m_tapMatchingdRL1Probe[iproc]>0 )? m_tapMatchingdRL1Probe[iproc]:dRL1byPt( mu2Pt ); 
          // cout << "TAG: " << tmpdR1L1Tag << "(Pt=" << mu1Pt <<  endl;
          // cout << "PROBE: " << tmpdR2L1Probe << "(Pt=" << mu2Pt << endl;
          
          if( m_trigTagHLT[iproc] == "No" ) {
            // if first muon is tag
            double dR1L1 = tmpdR1L1Tag;
            //double dR1L1 = m_tapMatchingdRL1Tag[iproc];
            double L1param1[5] = { -99999., -99999., -99999., -99999., -99999. };
            int L1num1   = matchL1( m_trigTagL1[iproc], (*mu_itr1), rois, &dR1L1, -1, L1param1 );
            if( m_trigTagL1[iproc]==NOTHING ) L1num1 = -1;
            if( L1num1>=0 || L1num1==-1 ) {
              // cout << "Passed Tag1" << endl;
              pair< const xAOD::Muon*, const xAOD::Muon* > TPpair1 = make_pair( (*mu_itr1), (*mu_itr2) );
              TPpair.push_back( TPpair1 );
              m_TPpairs.push_back( TPpair1 );
              m_TPpairsProcess.push_back( m_tapType[iproc] );
              m_TPpairsTagL1num.push_back( L1num1 );
              m_TPpairsTagdRL1.push_back( dR1L1 );
              m_TPpairsTagdREF.push_back( -99999. );
              m_TPpairsReqTagdRL1.push_back( tmpdR1L1Tag );
              m_TPpairsReqTagdREF.push_back( m_tapMatchingdREFTag[iproc] );
              m_TPpairsReqProbedRL1.push_back( tmpdR2L1Probe );
              m_TPpairsReqProbedREF.push_back( m_tapMatchingdREFProbe[iproc] );
              m_TPpairsReqProbedREFMS.push_back( m_tapMatchingdREFMSProbe[iproc] );
              m_TPpairsTagL1Pt.push_back( L1param1[0] );
              m_TPpairsTagL1Eta.push_back( L1param1[1] );
              m_TPpairsTagL1Phi.push_back( L1param1[2] );
              m_TPpairsTagSAPt.push_back( -2 );
              m_TPpairsTagSAEta.push_back( -2 );
              m_TPpairsTagSAPhi.push_back( -2 );
              m_TPpairsTagCBPt.push_back( -2 );
              m_TPpairsTagCBEta.push_back( -2 );
              m_TPpairsTagCBPhi.push_back( -2 );
              m_TPpairsTagEFPt.push_back( -2 );
              m_TPpairsTagEFEta.push_back( -2 );
              m_TPpairsTagEFPhi.push_back( -2 );
            }
            // if second muon is tag
            double dR2L1 = tmpdR2L1Tag;
            //double dR2L1 = m_tapMatchingdRL1Tag[iproc];
            double L1param2[5] = { -99999., -99999., -99999., -99999., -99999. };
            int L1num2   = matchL1( m_trigTagL1[iproc], (*mu_itr2), rois, &dR2L1, -1, L1param2 );
            if( m_trigTagL1[iproc]==NOTHING ) L1num2 = -1;
            if( L1num2>=0 || L1num2==-1 ) {
              // cout << "Passed Tag2" << endl;
              pair< const xAOD::Muon*, const xAOD::Muon* > TPpair2 = make_pair( (*mu_itr2), (*mu_itr1) );
              m_TPpairs.push_back( TPpair2 );
              m_TPpairsProcess.push_back( m_tapType[iproc] );
              m_TPpairsTagL1num.push_back( L1num2 );
              m_TPpairsTagdRL1.push_back( dR2L1 );
              m_TPpairsTagdREF.push_back( -99999. );
              m_TPpairsReqTagdRL1.push_back( tmpdR2L1Tag );
              m_TPpairsReqTagdREF.push_back( m_tapMatchingdREFTag[iproc] );
              m_TPpairsReqProbedRL1.push_back( tmpdR1L1Probe );
              m_TPpairsReqProbedREF.push_back( m_tapMatchingdREFProbe[iproc] );
              m_TPpairsReqProbedREFMS.push_back( m_tapMatchingdREFMSProbe[iproc] );
              m_TPpairsTagL1Pt.push_back( L1param2[0] );
              m_TPpairsTagL1Eta.push_back( L1param2[1] );
              m_TPpairsTagL1Phi.push_back( L1param2[2] );
              m_TPpairsTagSAPt.push_back( -2 );
              m_TPpairsTagSAEta.push_back( -2 );
              m_TPpairsTagSAPhi.push_back( -2 );
              m_TPpairsTagCBPt.push_back( -2 );
              m_TPpairsTagCBEta.push_back( -2 );
              m_TPpairsTagCBPhi.push_back( -2 );
              m_TPpairsTagEFPt.push_back( -2 );
              m_TPpairsTagEFEta.push_back( -2 );
              m_TPpairsTagEFPhi.push_back( -2 );
            }
          }
          else {
            
            Trig::FeatureContainer fc = m_trigDecTool->features( m_trigTagHLT[iproc], TrigDefs::alsoDeactivateTEs );
            // if first muon is tag
            double dR1L1 = tmpdR1L1Tag;
            //double dR1L1 = m_tapMatchingdRL1Tag[iproc];
            double dR1CB = m_tapMatchingdREFTag[iproc];
            double dR1EF = m_tapMatchingdREFTag[iproc];
            double L1param1[5] = { -99999., -99999., -99999., -99999., -99999. };
            //double SAparam1[17] = { -99999., -99999., -99999., -99999., -99999., -99999., -99999., -99999., -99999., -99999., -99999., -99999., -99999., -99999., -99999., -99999., -99999.};
            //
            const int sizeofSAparam1 = 65;
            double SAparam1[sizeofSAparam1];
            //fill SAparam1[*] with -99999.
            for(int i_SAparam1 = 0 ; i_SAparam1 < sizeofSAparam1 ; i_SAparam1++){
              SAparam1[i_SAparam1] = -99999.;
            }
            //
            std::vector < float > vec_SAparam_X1;
            std::vector < float > vec_SAparam_Y1;
            std::vector < float > vec_SAparam_Z1;
            std::vector < string > vec_SAparam_string1;

            vector < vector < int > > vec_SAparam_mdtInt1;
            vector <  vector <float > > vec_SAparam_mdtFloat1;

            std::vector < std::vector< float > > vec_SAparam_road1;
            //
            double CBparam1[4] = { -99999., -99999., -99999., -99999. };
            double EFparam1[4] = { -99999., -99999., -99999., -99999. };
            int L1num1   = matchL1( m_trigTagL1[iproc], (*mu_itr1), rois, &dR1L1, -1, L1param1 );
            int SApass1  = matchSA( fc, L1param1, SAparam1, vec_SAparam_X1, vec_SAparam_Y1, vec_SAparam_Z1, vec_SAparam_string1, m_trigTagSATEName[iproc], vec_SAparam_road1, vec_SAparam_mdtInt1, vec_SAparam_mdtFloat1);
            //int CBpass1  = matchCB( fc, L1num1, CBparam1 );
            int CBpass1  = matchCB( (*mu_itr1), fc, &dR1CB, CBparam1, m_trigTagCBTEName[iproc] );
            int EFpass1  = matchEF( m_trigTagHLT[iproc], (*mu_itr1), fc, &dR1EF, EFparam1 );
            cout << "mu1Tag : " << L1num1 << ", " << SApass1 << ", " << CBpass1 << ", " << EFpass1 << endl;
            if( m_message>1 ) cout << "mu1Tag : " << L1num1 << ", " << SApass1 << ", " << CBpass1 << ", " << EFpass1 << endl;
            if( L1num1>=0 && SApass1>=0 && CBpass1>=0 && EFpass1>=0 ) {
              cout << "make_pair1: " << endl;
              pair< const xAOD::Muon*, const xAOD::Muon* > TPpair1 = make_pair( (*mu_itr1), (*mu_itr2) );
              TPpair.push_back( TPpair1 );
              m_TPpairs.push_back( TPpair1 );
              m_TPpairsProcess.push_back( m_tapType[iproc] );
              m_TPpairsTagL1num.push_back( L1num1 );
              m_TPpairsTagdRL1.push_back( dR1L1 );
              m_TPpairsTagdREF.push_back( dR1EF );
              m_TPpairsReqTagdRL1.push_back( tmpdR1L1Tag );
              m_TPpairsReqTagdREF.push_back( m_tapMatchingdREFTag[iproc] );
              m_TPpairsReqProbedRL1.push_back( tmpdR2L1Probe );
              m_TPpairsReqProbedREF.push_back( m_tapMatchingdREFProbe[iproc] );
              m_TPpairsReqProbedREFMS.push_back( m_tapMatchingdREFMSProbe[iproc] );
              m_TPpairsTagL1Pt.push_back( L1param1[0] );
              m_TPpairsTagL1Eta.push_back( L1param1[1] );
              m_TPpairsTagL1Phi.push_back( L1param1[2] );
              m_TPpairsTagSAPt.push_back( SAparam1[0] );
              m_TPpairsTagSAEta.push_back( SAparam1[3] );
              m_TPpairsTagSAPhi.push_back( SAparam1[4] );
              m_TPpairsTagCBPt.push_back( CBparam1[0] );
              m_TPpairsTagCBEta.push_back( CBparam1[1] );
              m_TPpairsTagCBPhi.push_back( CBparam1[2] );
              m_TPpairsTagEFPt.push_back( EFparam1[0] );
              m_TPpairsTagEFEta.push_back( EFparam1[1] );
              m_TPpairsTagEFPhi.push_back( EFparam1[2] );
            }

            // if second muon is tag
            double dR2L1 = tmpdR2L1Tag;
            //double dR2L1 = m_tapMatchingdRL1Tag[iproc];
            double dR2CB = m_tapMatchingdREFTag[iproc];
            double dR2EF = m_tapMatchingdREFTag[iproc];
            double L1param2[5] = { -99999., -99999., -99999., -99999., -99999. };
            //double SAparam2[17] = { -99999., -99999., -99999., -99999., -99999., -99999., -99999., -99999., -99999., -99999., -99999., -99999., -99999., -99999., -99999., -99999., -99999. };
            //
            const int sizeofSAparam2 = 69;
            double SAparam2[sizeofSAparam2];
            //fill SAparam1[*] with -99999.
            for(int i_SAparam2 = 0 ; i_SAparam2 < sizeofSAparam2 ; i_SAparam2++){
              SAparam2[i_SAparam2] = -99999.;
            }
            //
            std::vector < float > vec_SAparam_X2;
            std::vector < float > vec_SAparam_Y2;
            std::vector < float > vec_SAparam_Z2;
            std::vector < string > vec_SAparam_string2;


            vector < vector < int > > vec_SAparam_mdtInt2;
            vector < vector < float > > vec_SAparam_mdtFloat2;

            std::vector < std::vector< float > > vec_SAparam_road2;
            //
            double CBparam2[4] = { -99999., -99999., -99999., -99999. };
            double EFparam2[4] = { -99999., -99999., -99999., -99999. };
            int L1num2   = matchL1( m_trigTagL1[iproc], (*mu_itr2), rois, &dR2L1, -1, L1param2 );
            int SApass2  = matchSA( fc, L1param2, SAparam2, vec_SAparam_X2, vec_SAparam_Y2, vec_SAparam_Z2, vec_SAparam_string2, m_trigTagSATEName[iproc], vec_SAparam_road2, vec_SAparam_mdtInt2, vec_SAparam_mdtFloat2 );
            //int CBpass2  = matchCB( fc, L1num2, CBparam2 );
            int CBpass2  = matchCB( (*mu_itr2), fc, &dR2CB, CBparam2, m_trigTagCBTEName[iproc] );
            int EFpass2  = matchEF( m_trigTagHLT[iproc], (*mu_itr2), fc, &dR2EF, EFparam2 );
            cout << "mu2Tag : " << L1num2 << ", " << SApass2 << ", " << CBpass2 << ", " << EFpass2 << endl;
            if( m_message>1 ) cout << "mu2Tag : " << L1num2 << ", " << SApass2 << ", " << CBpass2 << ", " << EFpass2 << endl;
            if( L1num2>=0 && SApass2>=0 && CBpass2>=0 && EFpass2>=0 ) {
              cout << "make_pair2: " << endl;
              pair< const xAOD::Muon*, const xAOD::Muon* > TPpair2 = make_pair( (*mu_itr2), (*mu_itr1) );
              m_TPpairs.push_back( TPpair2 );
              m_TPpairsProcess.push_back( m_tapType[iproc] );
              m_TPpairsTagL1num.push_back( L1num2 );
              m_TPpairsTagdRL1.push_back( dR2L1 );
              m_TPpairsTagdREF.push_back( dR2EF );
              m_TPpairsReqTagdRL1.push_back( tmpdR2L1Tag );
              m_TPpairsReqTagdREF.push_back( m_tapMatchingdREFTag[iproc] );
              m_TPpairsReqProbedRL1.push_back( tmpdR1L1Probe );
              m_TPpairsReqProbedREF.push_back( m_tapMatchingdREFProbe[iproc] );
              m_TPpairsReqProbedREFMS.push_back( m_tapMatchingdREFMSProbe[iproc] );
              m_TPpairsTagL1Pt.push_back( L1param2[0] );
              m_TPpairsTagL1Eta.push_back( L1param2[1] );
              m_TPpairsTagL1Phi.push_back( L1param2[2] );
              m_TPpairsTagSAPt.push_back( SAparam2[0] );
              m_TPpairsTagSAEta.push_back( SAparam2[3] );
              m_TPpairsTagSAPhi.push_back( SAparam2[4] );
              m_TPpairsTagCBPt.push_back( CBparam2[0] );
              m_TPpairsTagCBEta.push_back( CBparam2[1] );
              m_TPpairsTagCBPhi.push_back( CBparam2[2] );
              m_TPpairsTagEFPt.push_back( EFparam2[0] );
              m_TPpairsTagEFEta.push_back( EFparam2[1] );
              m_TPpairsTagEFPhi.push_back( EFparam2[2] );
            }
          }
        }
      }
    }
  }

  return 0;
}

int TagAndProbe::doProbeMatching( const xAOD::MuonRoIContainer* rois, const xAOD::TrackParticleContainer* ftf ) {
  const int nTP = m_TPpairs.size();
  cout << "nTP: " << nTP << endl;
  
  vector< vector< int > > vvL1pass, vvSApass, vvCBpass, vvEFpass;
  for( int iTP=0; iTP<nTP; iTP++ ) {
    
    int iproc               = m_TPpairsProcess[iTP];
    int tagL1num            = m_TPpairsTagL1num[iTP];
    double tpSumReqL1dR     = m_TPpairsReqTagdRL1[iTP] + m_TPpairsReqProbedRL1[iTP];///m_TPpairsReqTagdRL1 is push_backed by tmpdR1L1Tag and tmpdR2L1Tag.
    double tpSumReqEFdR     = m_TPpairsReqTagdREF[iTP] + m_TPpairsReqProbedREF[iTP];
    double tagL1dR          = m_TPpairsTagdRL1[iTP];
    double tagEFdR          = m_TPpairsTagdREF[iTP];
    double probeL1dR        = m_TPpairsReqProbedRL1[iTP];
    double probeEFdR        = m_TPpairsReqProbedREF[iTP];
    double tagL1Pt          = m_TPpairsTagL1Pt[iTP];
    double tagL1Eta         = m_TPpairsTagL1Eta[iTP];
    double tagL1Phi         = m_TPpairsTagL1Phi[iTP];
    double tagSAPt          = m_TPpairsTagSAPt[iTP];
    double tagSAEta         = m_TPpairsTagSAEta[iTP];
    double tagSAPhi         = m_TPpairsTagSAPhi[iTP];
    double tagCBPt          = m_TPpairsTagCBPt[iTP];
    double tagCBEta         = m_TPpairsTagCBEta[iTP];
    double tagCBPhi         = m_TPpairsTagCBPhi[iTP];
    double tagEFPt          = m_TPpairsTagEFPt[iTP];
    double tagEFEta         = m_TPpairsTagEFEta[iTP];
    double tagEFPhi         = m_TPpairsTagEFPhi[iTP];
    const xAOD::Muon* tag   = m_TPpairs[iTP].first;
    const xAOD::TrackParticle* tagtrk = tag->trackParticle( xAOD::Muon::InnerDetectorTrackParticle );	
    const xAOD::Muon* probe = m_TPpairs[iTP].second;
    const xAOD::TrackParticle* probetrk = probe->trackParticle( xAOD::Muon::InnerDetectorTrackParticle );	
    
    vector< const xAOD::TrackParticle* > tppair;
    if( tagtrk ) tppair.push_back( tagtrk );
    if( probetrk ) tppair.push_back( probetrk );
    if( !tagtrk && !probetrk ) continue;
    const xAOD::Vertex* pv = ( tagtrk )? tagtrk->vertex():probetrk->vertex();

    double tagPt        = tag->pt();
    double tagEta       = tag->eta();
    double tagPhi       = tag->phi();
    double tagd0        = ( tagtrk )? tagtrk->d0():-99999.;
    double tagz0        = ( tagtrk )? tagtrk->z0():-99999.;
    double tagCharge    = tag->charge();

    pair< double, double > extTag    = m_ext.extTrack( tagtrk );
    pair< double, double > extTagInn = m_ext.extTrackInner( tagtrk );

    const double tagExtEta    = ( tagtrk )? extTag.first:tagEta;
    const double tagExtInnEta = ( tagtrk )? extTagInn.first:tagEta;
    const double tagExtPhi    = ( tagtrk )? extTag.second:tagPhi;
    const double tagExtInnPhi = ( tagtrk )? extTagInn.second:tagPhi;

    double probePt      = probe->pt();
    //kayamash
    const ElementLink< xAOD::TrackParticleContainer > mslink = probe->muonSpectrometerTrackParticleLink();
    double probeMSPt = 0;
    if(!link == 1){
      const xAOD::TrackParticle *mstrk = *mslink;
      probeMSPt      = mstrk->pt()/1000.;//kayamash
    }
    //kayamash
    double probeEta     = probe->eta();
    double probePhi     = probe->phi();
    double probed0      = ( probetrk )? probetrk->d0():-99999.;
    double probez0      = ( probetrk )? probetrk->z0():-99999.;
    double probeCharge  = probe->charge();
    //
    double probeSegmentN = probe->nMuonSegments(); //nMuonSegments() returns number of muonSegments linked to by this muon.
    double probeSegmentX[SegmentMaxNumber]; //SegmentMaxNumber is defined in Utils.h .
    double probeSegmentY[SegmentMaxNumber];
    double probeSegmentZ[SegmentMaxNumber];
    double probeSegmentPx[SegmentMaxNumber];
    double probeSegmentPy[SegmentMaxNumber];
    double probeSegmentPz[SegmentMaxNumber];
    double probeSegmentChiSquared[SegmentMaxNumber];
    double probeSegmentNumberDoF[SegmentMaxNumber];
    double probeSegmentSector[SegmentMaxNumber];
    double probeSegmentChamberIndex[SegmentMaxNumber];
    double probeSegmentEtaIndex[SegmentMaxNumber];
    double probeSegmentNPrecisionHits[SegmentMaxNumber];
    double probeSegmentNPhiLayers[SegmentMaxNumber];
    double probeSegmentNTrigEtaLayers[SegmentMaxNumber];

    const xAOD::MuonSegment* segment_container_pointer[SegmentMaxNumber] = { 0 };
    for( int iSegment=0 ; iSegment < SegmentMaxNumber ; ++iSegment ){
      if( probeSegmentN == 0 && iSegment == 0 ){
        probeSegmentX[iSegment]              = -88888.;
        probeSegmentY[iSegment]              = -88888.;
        probeSegmentZ[iSegment]              = -88888.;
        probeSegmentPx[iSegment]             = -88888.;
        probeSegmentPy[iSegment]             = -88888.;
        probeSegmentPz[iSegment]             = -88888.;
        probeSegmentChiSquared[iSegment]     = -88888.;
        probeSegmentNumberDoF[iSegment]      = -88888.;
        probeSegmentSector[iSegment]         = -88888.;
        probeSegmentChamberIndex[iSegment]   = -88888.;
        probeSegmentEtaIndex[iSegment]       = -88888.;
        probeSegmentNPrecisionHits[iSegment] = -88888.;
        probeSegmentNPhiLayers[iSegment]     = -88888.;
        probeSegmentNTrigEtaLayers[iSegment] = -88888.;
      }else if( probeSegmentN != 0 && 0 <= iSegment && iSegment < probeSegmentN ){
        segment_container_pointer[iSegment]  = probe -> muonSegment(iSegment); //muonSegment( size_t i ) returns a pointer to the specified muonSegment. Param i is index of the Muonsegment requested. If i is not in range ( 0 <= i < nMuonSegments() ) an exception will be thrown.
        probeSegmentX[iSegment]              = ( segment_container_pointer[iSegment] -> x() );
        probeSegmentY[iSegment]              = ( segment_container_pointer[iSegment] -> y() );
        probeSegmentZ[iSegment]              = ( segment_container_pointer[iSegment] -> z() );
        probeSegmentPx[iSegment]             = ( segment_container_pointer[iSegment] -> px() );
        probeSegmentPy[iSegment]             = ( segment_container_pointer[iSegment] -> py() );
        probeSegmentPz[iSegment]             = ( segment_container_pointer[iSegment] -> pz() );
        probeSegmentChiSquared[iSegment]     = ( segment_container_pointer[iSegment] -> chiSquared() );
        probeSegmentNumberDoF[iSegment]      = ( segment_container_pointer[iSegment] -> numberDoF() );
        probeSegmentSector[iSegment]         = ( segment_container_pointer[iSegment] -> sector() );
        probeSegmentChamberIndex[iSegment]   = ( segment_container_pointer[iSegment] -> chamberIndex() );
        probeSegmentEtaIndex[iSegment]       = ( segment_container_pointer[iSegment] -> etaIndex() );
        probeSegmentNPrecisionHits[iSegment] = ( segment_container_pointer[iSegment] -> nPrecisionHits() );
        probeSegmentNPhiLayers[iSegment]     = ( segment_container_pointer[iSegment] -> nPhiLayers() );
        probeSegmentNTrigEtaLayers[iSegment] = ( segment_container_pointer[iSegment] -> nTrigEtaLayers() );
      }else if( ( probeSegmentN == 0 && iSegment != 0 ) || ( probeSegmentN != 0 && 0 < iSegment && probeSegmentN <= iSegment ) ){
        probeSegmentX[iSegment]              = -77777.;
        probeSegmentY[iSegment]              = -77777.;
        probeSegmentZ[iSegment]              = -77777.;
        probeSegmentPx[iSegment]             = -77777.;
        probeSegmentPy[iSegment]             = -77777.;
        probeSegmentPz[iSegment]             = -77777.;
        probeSegmentChiSquared[iSegment]     = -77777.;
        probeSegmentNumberDoF[iSegment]      = -77777.;
        probeSegmentSector[iSegment]         = -77777.;
        probeSegmentChamberIndex[iSegment]   = -77777.;
        probeSegmentEtaIndex[iSegment]       = -77777.;
        probeSegmentNPrecisionHits[iSegment] = -77777.;
        probeSegmentNPhiLayers[iSegment]     = -77777.;
        probeSegmentNTrigEtaLayers[iSegment] = -77777.;
      }
    }
    //
    pair< double, double > extProbe    = m_ext.extTrack( probetrk );
    pair< double, double > extProbeInn = m_ext.extTrackInner( probetrk );
    const double probeExtEta    = ( probetrk )? extProbe.first:probeEta;

    const double probeExtInnEta = ( probetrk )? extProbeInn.first:probeEta;
    const double probeExtPhi    = ( probetrk )? extProbe.second:probePhi;
    const double probeExtInnPhi = ( probetrk )? extProbeInn.second:probePhi;
    
    xAOD::Vertex* sv = m_vft.doVrtFit( tppair, pv );
    double tpVrtDx      = (sv)? sv->x()-pv->x():-99999;
    double tpVrtDy      = (sv)? sv->y()-pv->y():-99999;
    double tpVrtDz      = (sv)? sv->z()-pv->z():-99999;
    double tpVrtChi2    = (sv)? sv->chiSquared():-99999;
    double tpVrtNdof    = (sv)? sv->numberDoF():-99999; 

    cout << "Tag Status   : " << tagPt << ", " << tagEta << ", " << tagPhi << "( " << iproc << ", " << tagL1num << ", " << tagL1dR << " )" << "\n"
      << "Probe Status : " << probePt << ", " << probeEta << ", " << probePhi << endl;
    
    if( m_message>1 ) {
    //cout << "Tag Status   : " << tagPt << ", " << tagEta << ", " << tagPhi << "( " << iproc << ", " << tagL1num << ", " << tagL1dR << " )" << "\n"
    //     << "Probe Status : " << probePt << ", " << probeEta << ", " << probePhi << endl;
    }
   
    vector< int > vEFTAGpass, vL1pass, vSApass, vCBpass, vFTFpass, vEFpass;
    vector< double > vEFTAGdR, vL1dR, vSAdR, vCBdR, vFTFdR, vEFdR;
    vector< double > vEFTAGtpdR, vL1tpdR, vSAtpdR, vCBtpdR, vEFtpdR;
    vector< double > vEFTAGpt, vL1pt, vSApt, vCBpt, vFTFpt, vEFpt;
    vector< double > vEFTAGeta, vL1eta, vSAeta, vCBeta, vFTFeta, vEFeta;
    vector< double > vEFTAGphi, vL1phi, vSAphi, vCBphi, vFTFphi, vEFphi;
    vector< double > vSAetams, vSAphims, vSAetabe, vSAphibe; 
    //
    vector< double > vSAtgcPt, vSAptBarrelRadius, vSAptBarrelSagitta, vSAptEndcapAlpha, vSAptEndcapBeta, vSAptEndcapRadius, vSAptCSC, vSAsAddress;
    vector < float > vSAroiEta, vSAroiPhi;
    vector < int > vSAisRpcFailure, vSAisTgcFailure;
    //superPointR
    vector< double > vSAsuperPointRBI, vSAsuperPointRBM, vSAsuperPointRBO, vSAsuperPointREI, vSAsuperPointREM, vSAsuperPointREO, vSAsuperPointREE, vSAsuperPointRCSC, vSAsuperPointRBEE, vSAsuperPointRBME; 
    //superPointZ
    vector< double > vSAsuperPointZBI, vSAsuperPointZBM, vSAsuperPointZBO, vSAsuperPointZEI, vSAsuperPointZEM, vSAsuperPointZEO, vSAsuperPointZEE, vSAsuperPointZCSC, vSAsuperPointZBEE, vSAsuperPointZBME; 
    //superpointSlope
    vector< double > vSAsuperPointSlopeBI, vSAsuperPointSlopeBM, vSAsuperPointSlopeBO, vSAsuperPointSlopeEI, vSAsuperPointSlopeEM, vSAsuperPointSlopeEO, vSAsuperPointSlopeEE, vSAsuperPointSlopeCSC, vSAsuperPointSlopeBEE, vSAsuperPointSlopeBME; 
    //superpointIntercept
    vector< double > vSAsuperPointInterceptBI, vSAsuperPointInterceptBM, vSAsuperPointInterceptBO, vSAsuperPointInterceptEI, vSAsuperPointInterceptEM, vSAsuperPointInterceptEO, vSAsuperPointInterceptEE, vSAsuperPointInterceptCSC, vSAsuperPointInterceptBEE, vSAsuperPointInterceptBME; 
    //superpointChi2
    vector< double > vSAsuperPointChi2BI, vSAsuperPointChi2BM, vSAsuperPointChi2BO, vSAsuperPointChi2EI, vSAsuperPointChi2EM, vSAsuperPointChi2EO, vSAsuperPointChi2EE, vSAsuperPointChi2CSC, vSAsuperPointChi2BEE, vSAsuperPointChi2BME; 
    //rpcHit
    vector < vector < float > > vSArpcHitX, vSArpcHitY, vSArpcHitZ;
    //rpcHit
    vector < vector < double > > vSArpcHitR, vSArpcHitEta, vSArpcHitPhi, vSArpcHitStationNumber;
    //rpcHitStationName
    vector < vector < string > > vSArpcHitStationName;

    vector < vector < int > > vSAmdtHitIsOutlier, vSAmdtHitChamber;
    vector < vector < float > > vSAmdtHitR, vSAmdtHitZ, vSAmdtHitPhi, vSAmdtHitResidual;

    vector < vector < float > > vSAroadAw, vSAroadBw, vSAzMin, vSAzMax, vSArMin, vSArMax, vSAetaMin, vSAetaMax;
    //
    //cout << "Probe Status : " << probePt*probeCharge << ":" << probeEta << ":" << probePhi << endl;
    for( int imes=0; imes<m_trigNMes; imes++ ) {
      Trig::FeatureContainer fc = m_trigDecTool->features( m_trigMesHLT[imes], TrigDefs::alsoDeactivateTEs );
      //cout << "HLT[" << imes << "]=" << m_trigMesHLT[imes] << endl;
      
      double dREFTAG  = ( m_trigMesMSonly[imes]==0 )? probeEFdR:probeL1dR;
      double dRL1     = probeL1dR;
      double dRCB     = probeEFdR;
      double dRFTF    = probeEFdR;
      double dRFTF_2  = probeEFdR;
      double dREF     = ( m_trigMesMSonly[imes]==0 )? probeEFdR:probeL1dR;
      //cout << "BEFORE: " << dRL1 << ", " << dRCB << ", " << dREF << " (Pt=" << probePt << ")" << endl;
      double DUMMYparam[4]  = { -99999., -99999., -99999., -99999. };
      double EFTAGparam[4]  = { -99999., -99999., -99999., -99999. };
      double L1param[5] = { -99999., -99999., -99999., -99999., -99999. };
      //double SAparam[17]     = { -99999., -99999., -99999., -99999., -99999., -99999., -99999., -99999., -99999., -99999., -99999., -99999., -99999., -99999., -99999., -99999., -99999. };

      //add "For Loop" by yfukuhara on 2017/11/23.
      //***********************************************************************
      //SAparam[0] ~ SAparam[6] -> SApt, SAeta, SAphi, SAetams, SAphims, SAetabe, SAphibe,
      //SAparam[7] ~ SAparam[14] -> SAtgcPt, SAptBarrelRadius, SAptBarrelSagitta, SAptEndcapAlpha, SAptENdcapBeta, SAptEndcapRadius, SAptCSC, SAsAddress,
      //SAparam[15] ~ SAparam[24] -> SAsuperPointR* ( * = BI, BM, BO, EI, EM, EO, EE, CSC, BEE, BME )
      //SAparam[25] ~ SAparam[34] -> SAsuperPointZ* ( * = BI, BM, BO, EI, EM, EO, EE, CSC, BEE, BME )
      //SAparam[35] ~ SAparam[44] -> SAsuperPointSlope* ( * = BI, BM, BO, EI, EM, EO, EE, CSC, BEE, BME )
      //SAparam[45] ~ SAparam[54] -> SAsuperPointIntercept* ( * = BI, BM, BO, EI, EM, EO, EE, CSC, BEE, BME )
      //SAparam[55] ~ SAparam[64] -> SAsuperPointChi2* ( * = BI, BM, BO, EI, EM, EO, EE, CSC, BEE, BME )
      //***********************************************************************
      const int sizeofSAparam = 69;
      double SAparam[sizeofSAparam];
      //fill SAparam[*] with -99999.
      for(int i_SAparam = 0 ; i_SAparam < sizeofSAparam ; i_SAparam++){
        SAparam[i_SAparam] = -99999.;
      }
      // 
      vector < float > vec_SAparam_X;
      vector < float > vec_SAparam_Y;
      vector < float > vec_SAparam_Z;
      vector < double > vec_SAparam_R;
      vector < double > vec_SAparam_Eta;
      vector < double > vec_SAparam_Phi;
      vector < double > vec_SAparam_StationNumber;
      vector < string > vec_SAparam_string;

      vector < vector < int > > vec_SAparam_mdtInt;
      vector < vector < float > > vec_SAparam_mdtFloat;

      vector < int > vec_SAparam_mdtHitIsOutlier, vec_SAparam_mdtHitChamber;
      vector < float > vec_SAparam_mdtHitR, vec_SAparam_mdtHitZ, vec_SAparam_mdtHitPhi, vec_SAparam_mdtHitResidual;

      vector < vector < float > > vec_SAparam_road;
      //
      
      double CBparam[4]     = { -99999., -99999., -99999., -99999. };
      double FTFparam[4]    = { -99999., -99999., -99999., -99999. };
      double FTFparam_2[4]  = { -99999., -99999., -99999., -99999. };
      double EFparam[4]     = { -99999., -99999., -99999., -99999. };
      /*
      int L1num   = matchL1( m_trigMesL1[imes], probe, rois, &dRL1, tagL1num, L1param );
      int SApass  = matchSA( fc, L1num, SAparam );
      //int CBpass  = matchCB( fc, L1num, CBparam );
      int CBpass  = matchCB( probe, fc, &dRCB, CBparam );
      int EFpass  = matchEF( m_trigMesHLT[imes], probe, fc, &dREF, EFparam );
      */
      int EFTAGpass=-1, L1num=-1, SApass=-1, CBpass=-1, FTFpass=-1, FTFpass_2=-1, EFpass=-1;
      if( m_trigMesAddTagReq[imes]!="none" ) {
        Trig::FeatureContainer fctag = m_trigDecTool->features( m_trigMesAddTagReq[imes], TrigDefs::alsoDeactivateTEs );
        EFTAGpass = matchEFFS( m_trigMesAddTagReq[imes], tag, fctag, &dREFTAG, EFTAGparam, DUMMYparam );
        //if( EFTAGpass>-1 && m_trigMesNoL1[imes]==1 ) cout << m_trigMesName[imes] << endl;
      }
      else {EFTAGpass = 0;}

      if( m_trigMesNoL1[imes]==1 ) {
        if( m_trigMesL1[imes] != NOTHING ) L1num = matchL1( m_trigMesL1[imes], probe, rois, &dRL1, tagL1num, L1param );
        else L1num = EFTAGpass;
        SApass    = EFTAGpass;
        CBpass    = EFTAGpass;
        FTFpass   = EFTAGpass;
        EFpass    = matchEFFS( m_trigMesName[imes], probe, fc, &dREF, EFparam, EFTAGparam );
      }
      else {
        L1num     = matchL1( m_trigMesL1[imes], probe, rois, &dRL1, tagL1num, L1param );
        SApass    = matchSA( fc, L1param, SAparam, vec_SAparam_X, vec_SAparam_Y, vec_SAparam_Z, vec_SAparam_string, m_trigMesSATEName[imes], vec_SAparam_road, vec_SAparam_mdtInt, vec_SAparam_mdtFloat );
        //cout << "CHAIN: " <<  m_trigMesHLT[imes] << ", MUON pT: " << probe->pt() << endl;
        //CBpass  = matchCB( fc, L1num, CBparam );
        CBpass    = matchCB( probe, fc, &dRCB, CBparam, m_trigMesCBTEName[imes] );
        //FTFpass   = matchFTF( probe, ftf, &dRFTF, FTFparam );
        //FTFpass_2 = matchFTF( probe, fc, &dRFTF_2, FTFparam_2 );
        EFpass    = matchEF( m_trigMesHLT[imes], probe, fc, &dREF, EFparam );
      }
      
      if( m_message>1 ) {
        cout << "Trigger : " << m_trigMesName[imes] << ", " << L1num << ", " << SApass << ", " << CBpass << ", " << EFpass << "\n"
             << "L1 Stutas  : " << L1param[0] << ", " << L1param[1] << ", " << L1param[2] << "\n"
             << "SA Stutas  : " << SAparam[0] << ", " << SAparam[1] << ", " << SAparam[2] << "\n"
             << "CB Stutas  : " << CBparam[0]*CBparam[3] << ", " << CBparam[1] << ", " << CBparam[2] << "\n"
             << "FTF Stutas : " << FTFparam[0]*FTFparam[3] << ", " << FTFparam[1] << ", " << FTFparam[2] << "\n"
             << "EF Stutas  : " << EFparam[0]*FTFparam[3] << ", " << EFparam[1] << ", " << EFparam[2] << endl;
      }
      //cout << "AFTER: " << dRL1 << ", " << dRCB << ", " << dREF << " (Pt=" << probePt << ")" << endl;
      vEFTAGpass.push_back( EFTAGpass );
      vEFTAGpt.push_back( EFTAGparam[0] );
      vEFTAGdR.push_back( dREFTAG );
      vEFTAGtpdR.push_back(  m_utils.deltaR( tagEFEta, tagEFPhi, EFTAGparam[1], EFTAGparam[2] ) );
      vEFTAGeta.push_back( EFTAGparam[1] );
      vEFTAGphi.push_back( EFTAGparam[2] );
      vL1pass.push_back( L1num );
      vL1pt.push_back( L1param[0] );
      vL1dR.push_back( dRL1 );
      vL1tpdR.push_back(  m_utils.deltaR( tagL1Eta, tagL1Phi, L1param[1], L1param[2] ) );
      vL1eta.push_back( L1param[1] );
      vL1phi.push_back( L1param[2] );
      vSApass.push_back( SApass );
      vSAdR.push_back( -99999. );
      vSAtpdR.push_back(  m_utils.deltaR( tagSAEta, tagSAPhi, SAparam[3], SAparam[4] ) );
      vSApt.push_back( SAparam[0] );
      vSAeta.push_back( SAparam[1] );
      vSAphi.push_back( SAparam[2] );
      vSAetams.push_back( SAparam[3] );
      vSAphims.push_back( SAparam[4] );
      vSAetabe.push_back( SAparam[5] );
      vSAphibe.push_back( SAparam[6] );
      //
      vSAtgcPt.push_back( SAparam[7] );
      vSAptBarrelRadius.push_back( SAparam[8] );
      vSAptBarrelSagitta.push_back( SAparam[9] );
      vSAptEndcapAlpha.push_back( SAparam[10] );
      vSAptEndcapBeta.push_back( SAparam[11] );
      vSAptEndcapRadius.push_back( SAparam[12] );
      vSAptCSC.push_back( SAparam[13] );
      vSAsAddress.push_back( SAparam[14] );
      //
      vSAsuperPointRBI.push_back( SAparam[15] );   
      vSAsuperPointRBM.push_back( SAparam[16] );
      vSAsuperPointRBO.push_back( SAparam[17] );
      vSAsuperPointREI.push_back( SAparam[18] );
      vSAsuperPointREM.push_back( SAparam[19] );
      vSAsuperPointREO.push_back( SAparam[20] );
      vSAsuperPointREE.push_back( SAparam[21] );
      vSAsuperPointRCSC.push_back( SAparam[22] );
      vSAsuperPointRBEE.push_back( SAparam[23] );
      vSAsuperPointRBME.push_back( SAparam[24] );
      //
      vSAsuperPointZBI.push_back( SAparam[25] );   
      vSAsuperPointZBM.push_back( SAparam[26] );
      vSAsuperPointZBO.push_back( SAparam[27] );
      vSAsuperPointZEI.push_back( SAparam[28] );
      vSAsuperPointZEM.push_back( SAparam[29] );
      vSAsuperPointZEO.push_back( SAparam[30] );
      vSAsuperPointZEE.push_back( SAparam[31] );
      vSAsuperPointZCSC.push_back( SAparam[32] );
      vSAsuperPointZBEE.push_back( SAparam[33] );
      vSAsuperPointZBME.push_back( SAparam[34] );
      //
      vSAsuperPointSlopeBI.push_back( SAparam[35] );   
      vSAsuperPointSlopeBM.push_back( SAparam[36] );
      vSAsuperPointSlopeBO.push_back( SAparam[37] );
      vSAsuperPointSlopeEI.push_back( SAparam[38] );
      vSAsuperPointSlopeEM.push_back( SAparam[39] );
      vSAsuperPointSlopeEO.push_back( SAparam[40] );
      vSAsuperPointSlopeEE.push_back( SAparam[41] );
      vSAsuperPointSlopeCSC.push_back( SAparam[42] );
      vSAsuperPointSlopeBEE.push_back( SAparam[43] );
      vSAsuperPointSlopeBME.push_back( SAparam[44] );
      //
      vSAsuperPointInterceptBI.push_back( SAparam[45] );   
      vSAsuperPointInterceptBM.push_back( SAparam[46] );
      vSAsuperPointInterceptBO.push_back( SAparam[47] );
      vSAsuperPointInterceptEI.push_back( SAparam[48] );
      vSAsuperPointInterceptEM.push_back( SAparam[49] );
      vSAsuperPointInterceptEO.push_back( SAparam[50] );
      vSAsuperPointInterceptEE.push_back( SAparam[51] );
      vSAsuperPointInterceptCSC.push_back( SAparam[52] );
      vSAsuperPointInterceptBEE.push_back( SAparam[53] );
      vSAsuperPointInterceptBME.push_back( SAparam[54] );
      //
      vSAsuperPointChi2BI.push_back( SAparam[55] );   
      vSAsuperPointChi2BM.push_back( SAparam[56] );
      vSAsuperPointChi2BO.push_back( SAparam[57] );
      vSAsuperPointChi2EI.push_back( SAparam[58] );
      vSAsuperPointChi2EM.push_back( SAparam[59] );
      vSAsuperPointChi2EO.push_back( SAparam[60] );
      vSAsuperPointChi2EE.push_back( SAparam[61] );
      vSAsuperPointChi2CSC.push_back( SAparam[62] );
      vSAsuperPointChi2BEE.push_back( SAparam[63] );
      vSAsuperPointChi2BME.push_back( SAparam[64] );

      vSAroiEta.push_back( SAparam[65]);
      vSAroiPhi.push_back( SAparam[66]);
      vSAisRpcFailure.push_back( SAparam[67]);
      vSAisTgcFailure.push_back( SAparam[68]);

      //vSArpcHitX is vector < vector < float > >, vec_saparam is vector < vector < float > >.
      //vSArpcHitX.push_back( vec_SAparam[0] );
      //vSArpcHitY.push_back( vec_SAparam[1] );
      //vSArpcHitZ.push_back( vec_SAparam[2] );
      //vSArpcHitStationName.push_back( vec_SAparam_string );
      //
      //int n_vec_SAparam_0 = vec_SAparam[0].size();
      //int n_vec_SAparam_1 = vec_SAparam[1].size();
      //int n_vec_SAparam_2 = vec_SAparam[2].size();
      //cout << "imes" << imes << endl;
      //cout << "0vec" << n_vec_SAparam_0 << endl;
      //cout << "1vec" << n_vec_SAparam_1 << endl;
      //cout << "2vec" << n_vec_SAparam_2 << endl;

      //cout << "2vec" << n_vec_SAparam_2 << endl;
      //cout << "2vec" << n_vec_SAparam_2 << endl;

      //vSArpcHitX.resize(n_vec_SAparam_0);
      //vSArpcHitY.resize(n_vec_SAparam_1);
      //vSArpcHitZ.resize(n_vec_SAparam_2);

      /*for ( int a = 0; a < n_vec_SAparam_0; ++a ){
        //int b = 0;
        vSArpcHitX[a].push_back( vec_SAparam[0][a] );
        //cout << "vec_SAparam[1]" << a << ":" << vec_SAparam[0][a] << endl;
        vSArpcHitY[a].push_back( vec_SAparam[1][a] );
        //cout << "vec_SAparam[2]" << a << ":" << vec_SAparam[1][a] << endl;
        vSArpcHitZ[a].push_back( vec_SAparam[2][a] );
        //cout << "vec_SAparam[3]" << a << ":" << vec_SAparam[2][a] << endl;
        //cout << "(x,y,z) = " <<  ": (" << vec_SAparam[0][a] << "," << vec_SAparam[1][a] << "," << vec_SAparam[2][a] << ")" << endl;
        //cout << "(x,y,z) = " <<  ": (" << vSArpcHitX[a][b] << "," << vSArpcHitY[a][b] << "," << vSArpcHitZ[a][b] << ")" << endl;
        //b++;
      }*/
      vSArpcHitX.push_back(vec_SAparam_X);
      vSArpcHitY.push_back(vec_SAparam_Y);
      vSArpcHitZ.push_back(vec_SAparam_Z);

      vector < int > tmp_int;
      vector < float > tmp_float;
      if ( vec_SAparam_road.size() == 8 ){
        vSAroadAw.push_back(vec_SAparam_road[0]);
        vSAroadBw.push_back(vec_SAparam_road[1]);
        vSAzMin.push_back(vec_SAparam_road[2]);
        vSAzMax.push_back(vec_SAparam_road[3]);
        vSArMin.push_back(vec_SAparam_road[4]);
        vSArMax.push_back(vec_SAparam_road[5]);
        vSAetaMin.push_back(vec_SAparam_road[6]);
        vSAetaMax.push_back(vec_SAparam_road[7]);
      } else {
        vSAroadAw.push_back(tmp_float);
        vSAroadBw.push_back(tmp_float);
        vSAzMin.push_back(tmp_float);
        vSAzMax.push_back(tmp_float);
        vSArMin.push_back(tmp_float);
        vSArMax.push_back(tmp_float);
        vSAetaMin.push_back(tmp_float);
        vSAetaMax.push_back(tmp_float);
      }
      if ( vec_SAparam_mdtInt.size() == 2 ){
        vSAmdtHitIsOutlier.push_back(vec_SAparam_mdtInt[0]);
        vSAmdtHitChamber.push_back(vec_SAparam_mdtInt[1]);
        vSAmdtHitR.push_back(vec_SAparam_mdtFloat[0]);
        vSAmdtHitZ.push_back(vec_SAparam_mdtFloat[1]);
        vSAmdtHitPhi.push_back(vec_SAparam_mdtFloat[2]);
        vSAmdtHitResidual.push_back(vec_SAparam_mdtFloat[3]);
      } else {
        vSAmdtHitIsOutlier.push_back(tmp_int);
        vSAmdtHitChamber.push_back(tmp_int);
        vSAmdtHitR.push_back(tmp_float);
        vSAmdtHitZ.push_back(tmp_float);
        vSAmdtHitPhi.push_back(tmp_float);
        vSAmdtHitResidual.push_back(tmp_float);
      }
      //convert (X,Y,Z) to (R,Eta,Phi)
      std::vector < TVector3 > vec3_SAparam;
      int n_vec_SAparam = vec_SAparam_X.size();
      for(int i_vec_SAparam = 0; i_vec_SAparam < n_vec_SAparam; ++i_vec_SAparam){
        TVector3 i_vec3_SAparam( vec_SAparam_X.at(i_vec_SAparam), vec_SAparam_Y.at(i_vec_SAparam), vec_SAparam_Z.at(i_vec_SAparam) );
        vec_SAparam_R.push_back(i_vec3_SAparam.Perp());
        vec_SAparam_Eta.push_back(i_vec3_SAparam.Eta());
        vec_SAparam_Phi.push_back(i_vec3_SAparam.Phi());
        //vec3_SAparam.push_back( i_vec3_SAparam );
      }
      vSArpcHitR.push_back(vec_SAparam_R);
      vSArpcHitEta.push_back(vec_SAparam_Eta);
      vSArpcHitPhi.push_back(vec_SAparam_Phi);
      
      vSArpcHitStationName.push_back(vec_SAparam_string);

      int n_name = vec_SAparam_string.size();
      for(int i_name = 0; i_name < n_name; ++i_name){
        if(vec_SAparam_string.at(i_name) == "BML" ){
          //BML; Barrel Middle Large
          vec_SAparam_StationNumber.push_back(1.);
        }
        else if(vec_SAparam_string.at(i_name) == "BMS" ){
          //BMS; Barrel Middle Small
          vec_SAparam_StationNumber.push_back(2.);
        }
        else if(vec_SAparam_string.at(i_name) == "BMF" ){
          //BMF; Barrel Middle Feet
          vec_SAparam_StationNumber.push_back(3.);
        }
        else if(vec_SAparam_string.at(i_name) == "BME" ){
          //BME; Barrel Middle Extra
          vec_SAparam_StationNumber.push_back(4.);
        }
        else if(vec_SAparam_string.at(i_name) == "BOL" ){
          //BOL; Barrel Outer Large
          vec_SAparam_StationNumber.push_back(5.);
        }
        else if(vec_SAparam_string.at(i_name) == "BOS" ){
          //BOL; Barrel Outer Small
          vec_SAparam_StationNumber.push_back(6.);
        }
        else if(vec_SAparam_string.at(i_name) == "BOF" ){
          //BOF; Barrel Outer Feet
          vec_SAparam_StationNumber.push_back(7.);
        }
        else if(vec_SAparam_string.at(i_name) == "BOE" ){
          //BOF; Barrel Outer Extra
          vec_SAparam_StationNumber.push_back(8.);
        }
        else if(vec_SAparam_string.at(i_name) == "BOG" ){
          //BOG; Barrel Outer G?
          vec_SAparam_StationNumber.push_back(9.);
        }
        else {
          //unknown;
          vec_SAparam_StationNumber.push_back(10.);
        }
      }
      vSArpcHitStationNumber.push_back(vec_SAparam_StationNumber);

      //
      vCBpass.push_back( CBpass );
      vCBdR.push_back( dRCB );
      vCBtpdR.push_back(  m_utils.deltaR( tagCBEta, tagCBPhi, CBparam[1], CBparam[2] ) );
      vCBpt.push_back( CBparam[0] );
      vCBeta.push_back( CBparam[1] );
      vCBphi.push_back( CBparam[2] );
      vFTFpass.push_back( FTFpass );
      vFTFdR.push_back( dRFTF );
      vFTFpt.push_back( FTFparam[0] );
      vFTFeta.push_back( FTFparam[1] );
      vFTFphi.push_back( FTFparam[2] );
      vEFpass.push_back( EFpass );
      vEFdR.push_back( dREF );
      vEFtpdR.push_back(  m_utils.deltaR( tagEFEta, tagEFPhi, EFparam[1], EFparam[2] ) );
      vEFpt.push_back( EFparam[0] );
      vEFeta.push_back( EFparam[1] );
      vEFphi.push_back( EFparam[2] );
    }
    m_tagProc.push_back( iproc );
    m_tpSumReqL1dR.push_back( tpSumReqL1dR );
    m_tpSumReqEFdR.push_back( tpSumReqEFdR );
    m_tagL1dR.push_back( tagL1dR );
    m_tagEFdR.push_back( tagEFdR );
    m_tagReqL1dR.push_back( m_TPpairsReqTagdRL1[iTP] );
    m_tagReqEFdR.push_back( m_TPpairsReqTagdREF[iTP] );
    m_tagPt.push_back( tagPt );
    m_tagEta.push_back( tagEta );
    m_tagExtEta.push_back( tagExtEta );
    m_tagExtInnEta.push_back( tagExtInnEta );
    m_tagPhi.push_back( tagPhi );
    m_tagExtPhi.push_back( tagExtPhi );
    m_tagExtInnPhi.push_back( tagExtInnPhi );
    m_tagd0.push_back( tagd0 );
    m_tagz0.push_back( tagz0 );
    m_tagCharge.push_back( tagCharge );
    m_tagL1Pt.push_back( tagL1Pt );
    m_tagL1Eta.push_back( tagL1Eta );
    m_tagL1Phi.push_back( tagL1Phi );
    m_tagSAPt.push_back( tagSAPt );
    m_tagSAEta.push_back( tagSAEta );
    m_tagSAPhi.push_back( tagSAPhi );
    m_tagCBPt.push_back( tagCBPt );
    m_tagCBEta.push_back( tagCBEta );
    m_tagCBPhi.push_back( tagCBPhi );
    m_tagEFPt.push_back( tagEFPt );
    m_tagEFEta.push_back( tagEFEta );
    m_tagEFPhi.push_back( tagEFPhi );
    m_probePt.push_back( probePt );
    m_probeMSPt.push_back( probeMSPt );
    m_probeEta.push_back( probeEta );
    m_probeExtEta.push_back( probeExtEta );
    m_probeExtInnEta.push_back( probeExtInnEta );
    m_probePhi.push_back( probePhi );
    m_probeExtPhi.push_back( probeExtPhi );
    m_probeExtInnPhi.push_back( probeExtInnPhi );
    m_probed0.push_back( probed0 );
    m_probez0.push_back( probez0 );
    m_probeCharge.push_back( probeCharge );
    //
    m_probeSegmentN.push_back( probeSegmentN );
    //m_probeSegmentX.resize( SegmentMaxNumber );
    m_probeSegmentX.resize( SegmentMaxNumber );
    m_probeSegmentY.resize( SegmentMaxNumber );
    m_probeSegmentZ.resize( SegmentMaxNumber );
    m_probeSegmentPx.resize( SegmentMaxNumber );
    m_probeSegmentPy.resize( SegmentMaxNumber );
    m_probeSegmentPz.resize( SegmentMaxNumber );
    m_probeSegmentChiSquared.resize( SegmentMaxNumber );
    m_probeSegmentNumberDoF.resize( SegmentMaxNumber );
    m_probeSegmentSector.resize( SegmentMaxNumber );
    m_probeSegmentChamberIndex.resize( SegmentMaxNumber );
    m_probeSegmentEtaIndex.resize( SegmentMaxNumber );
    m_probeSegmentNPrecisionHits.resize( SegmentMaxNumber );
    m_probeSegmentNPhiLayers.resize( SegmentMaxNumber );
    m_probeSegmentNTrigEtaLayers.resize( SegmentMaxNumber );
    for( int iSegment = 0; iSegment < SegmentMaxNumber; iSegment++ ){
      //m_probeSegmentX[k].resize(10);
      m_probeSegmentX[iSegment].push_back( probeSegmentX[iSegment] );
      m_probeSegmentY[iSegment].push_back( probeSegmentY[iSegment] );
      m_probeSegmentZ[iSegment].push_back( probeSegmentZ[iSegment] );
      m_probeSegmentPx[iSegment].push_back( probeSegmentPx[iSegment] );
      m_probeSegmentPy[iSegment].push_back( probeSegmentPy[iSegment] );
      m_probeSegmentPz[iSegment].push_back( probeSegmentPz[iSegment] );
      m_probeSegmentChiSquared[iSegment].push_back( probeSegmentChiSquared[iSegment] );
      m_probeSegmentNumberDoF[iSegment].push_back( probeSegmentNumberDoF[iSegment] );
      m_probeSegmentSector[iSegment].push_back( probeSegmentSector[iSegment] );
      m_probeSegmentChamberIndex[iSegment].push_back( probeSegmentChamberIndex[iSegment] );
      m_probeSegmentEtaIndex[iSegment].push_back( probeSegmentEtaIndex[iSegment] );
      m_probeSegmentNPrecisionHits[iSegment].push_back( probeSegmentNPrecisionHits[iSegment] );
      m_probeSegmentNPhiLayers[iSegment].push_back( probeSegmentNPhiLayers[iSegment] );
      m_probeSegmentNTrigEtaLayers[iSegment].push_back( probeSegmentNTrigEtaLayers[iSegment] );
    }
    //
    //cout << "Hello5.1" << endl;
    //cout << "vSAroadAw: " << vSAroadAw.size() << endl;
    m_tpVrtDx.push_back( tpVrtDx );
    m_tpVrtDy.push_back( tpVrtDy );
    m_tpVrtDz.push_back( tpVrtDz );
    m_tpVrtChi2.push_back( tpVrtChi2 );
    m_tpVrtNdof.push_back( tpVrtNdof );
    
    m_probePassedEFTAG.push_back( vEFTAGpass );
    m_probeEFTAGPt.push_back( vEFTAGpt );
    m_probeEFTAGdR.push_back( vEFTAGdR );
    m_probeEFTAGtpdR.push_back( vEFTAGtpdR );
    m_probeEFTAGEta.push_back( vEFTAGeta );
    m_probeEFTAGPhi.push_back( vEFTAGphi );
    m_probePassedL1.push_back( vL1pass );
    m_probeL1Pt.push_back( vL1pt );
    m_probeL1dR.push_back( vL1dR );
    m_probeL1tpdR.push_back( vL1tpdR );
    m_probeL1Eta.push_back( vL1eta );
    m_probeL1Phi.push_back( vL1phi );
    m_probePassedSA.push_back( vSApass );
    m_probeSAdR.push_back( vSAdR );
    m_probeSAtpdR.push_back( vSAtpdR );
    m_probeSAPt.push_back( vSApt );
    m_probeSAEta.push_back( vSAeta );
    m_probeSAPhi.push_back( vSAphi );
    m_probeSAEtaMS.push_back( vSAetams );
    m_probeSAPhiMS.push_back( vSAphims );
    m_probeSAEtaBE.push_back( vSAetabe );
    m_probeSAPhiBE.push_back( vSAphibe );

    //
    m_probeSATgcPt.push_back( vSAtgcPt ); 
    m_probeSAPtBarrelRadius.push_back( vSAptBarrelRadius );
    m_probeSAPtBarrelSagitta.push_back( vSAptBarrelSagitta );
    m_probeSAPtEndcapAlpha.push_back( vSAptEndcapAlpha );
    m_probeSAPtEndcapBeta.push_back( vSAptEndcapBeta );
    m_probeSAPtEndcapRadius.push_back( vSAptEndcapRadius );
    m_probeSAPtCSC.push_back( vSAptCSC );
    m_probeSAsAddress.push_back( vSAsAddress );

    m_probeSAroiEta.push_back( vSAroiEta );
    m_probeSAroiPhi.push_back( vSAroiPhi );
    m_probeSAisRpcFailure.push_back( vSAisRpcFailure );
    m_probeSAisTgcFailure.push_back( vSAisTgcFailure );
    //
    m_probeSAsuperPointRBI.push_back( vSAsuperPointRBI ); 
    m_probeSAsuperPointRBM.push_back( vSAsuperPointRBM ); 
    m_probeSAsuperPointRBO.push_back( vSAsuperPointRBO ); 
    m_probeSAsuperPointREI.push_back( vSAsuperPointREI ); 
    m_probeSAsuperPointREM.push_back( vSAsuperPointREM ); 
    m_probeSAsuperPointREO.push_back( vSAsuperPointREO ); 
    m_probeSAsuperPointREE.push_back( vSAsuperPointREE ); 
    m_probeSAsuperPointRCSC.push_back( vSAsuperPointRCSC );
    m_probeSAsuperPointRBEE.push_back( vSAsuperPointRBEE );
    m_probeSAsuperPointRBME.push_back( vSAsuperPointRBME );
    //
    m_probeSAsuperPointZBI.push_back( vSAsuperPointZBI ); 
    m_probeSAsuperPointZBM.push_back( vSAsuperPointZBM ); 
    m_probeSAsuperPointZBO.push_back( vSAsuperPointZBO ); 
    m_probeSAsuperPointZEI.push_back( vSAsuperPointZEI ); 
    m_probeSAsuperPointZEM.push_back( vSAsuperPointZEM ); 
    m_probeSAsuperPointZEO.push_back( vSAsuperPointZEO ); 
    m_probeSAsuperPointZEE.push_back( vSAsuperPointZEE ); 
    m_probeSAsuperPointZCSC.push_back( vSAsuperPointZCSC );
    m_probeSAsuperPointZBEE.push_back( vSAsuperPointZBEE );
    m_probeSAsuperPointZBME.push_back( vSAsuperPointZBME );
    //
    m_probeSAsuperPointSlopeBI.push_back( vSAsuperPointSlopeBI ); 
    m_probeSAsuperPointSlopeBM.push_back( vSAsuperPointSlopeBM ); 
    m_probeSAsuperPointSlopeBO.push_back( vSAsuperPointSlopeBO ); 
    m_probeSAsuperPointSlopeEI.push_back( vSAsuperPointSlopeEI ); 
    m_probeSAsuperPointSlopeEM.push_back( vSAsuperPointSlopeEM ); 
    m_probeSAsuperPointSlopeEO.push_back( vSAsuperPointSlopeEO ); 
    m_probeSAsuperPointSlopeEE.push_back( vSAsuperPointSlopeEE ); 
    m_probeSAsuperPointSlopeCSC.push_back( vSAsuperPointSlopeCSC );
    m_probeSAsuperPointSlopeBEE.push_back( vSAsuperPointSlopeBEE );
    m_probeSAsuperPointSlopeBME.push_back( vSAsuperPointSlopeBME );
    //
    m_probeSAsuperPointInterceptBI.push_back( vSAsuperPointInterceptBI ); 
    m_probeSAsuperPointInterceptBM.push_back( vSAsuperPointInterceptBM ); 
    m_probeSAsuperPointInterceptBO.push_back( vSAsuperPointInterceptBO ); 
    m_probeSAsuperPointInterceptEI.push_back( vSAsuperPointInterceptEI ); 
    m_probeSAsuperPointInterceptEM.push_back( vSAsuperPointInterceptEM ); 
    m_probeSAsuperPointInterceptEO.push_back( vSAsuperPointInterceptEO ); 
    m_probeSAsuperPointInterceptEE.push_back( vSAsuperPointInterceptEE ); 
    m_probeSAsuperPointInterceptCSC.push_back( vSAsuperPointInterceptCSC );
    m_probeSAsuperPointInterceptBEE.push_back( vSAsuperPointInterceptBEE );
    m_probeSAsuperPointInterceptBME.push_back( vSAsuperPointInterceptBME );
    //
    m_probeSAsuperPointChi2BI.push_back( vSAsuperPointChi2BI ); 
    m_probeSAsuperPointChi2BM.push_back( vSAsuperPointChi2BM ); 
    m_probeSAsuperPointChi2BO.push_back( vSAsuperPointChi2BO ); 
    m_probeSAsuperPointChi2EI.push_back( vSAsuperPointChi2EI ); 
    m_probeSAsuperPointChi2EM.push_back( vSAsuperPointChi2EM ); 
    m_probeSAsuperPointChi2EO.push_back( vSAsuperPointChi2EO ); 
    m_probeSAsuperPointChi2EE.push_back( vSAsuperPointChi2EE ); 
    m_probeSAsuperPointChi2CSC.push_back( vSAsuperPointChi2CSC );
    m_probeSAsuperPointChi2BEE.push_back( vSAsuperPointChi2BEE );
    m_probeSAsuperPointChi2BME.push_back( vSAsuperPointChi2BME );
    //
    //cout << "Hello5.2" << endl;
    m_probeSArpcHitX.push_back( vSArpcHitX );
    m_probeSArpcHitY.push_back( vSArpcHitY );
    m_probeSArpcHitZ.push_back( vSArpcHitZ );
    m_probeSArpcHitR.push_back( vSArpcHitR );
    m_probeSArpcHitEta.push_back( vSArpcHitEta );
    m_probeSArpcHitPhi.push_back( vSArpcHitPhi );
    m_probeSArpcHitStationNumber.push_back( vSArpcHitStationNumber );
    m_probeSArpcHitStationName.push_back( vSArpcHitStationName );


    //cout << "Hello6" << endl;
    m_probeSAroadAw.push_back( vSAroadAw );
    m_probeSAroadBw.push_back( vSAroadBw );
    m_probeSAzMin.push_back( vSAzMin );
    m_probeSAzMax.push_back( vSAzMax );
    m_probeSArMin.push_back( vSArMin );
    m_probeSArMax.push_back( vSArMax );
    m_probeSAetaMin.push_back( vSAetaMin );
    m_probeSAetaMax.push_back( vSAetaMax );
    //cout << "Hello7" << endl;

    m_probeSAmdtHitIsOutlier.push_back( vSAmdtHitIsOutlier );
    m_probeSAmdtHitChamber.push_back( vSAmdtHitChamber );
    m_probeSAmdtHitR.push_back( vSAmdtHitR );
    m_probeSAmdtHitZ.push_back( vSAmdtHitZ );
    m_probeSAmdtHitPhi.push_back( vSAmdtHitPhi );
    m_probeSAmdtHitResidual.push_back( vSAmdtHitResidual );
    //
    //m_probeSArpcHitX.resize(25);
    //for(int i = 0; i < 25; ++i){
    //  m_probeSArpcHitX.at(i) .push_back( vSArpcHitX[i] );
    //}
    
    m_probePassedCB.push_back( vCBpass );
    m_probeCBdR.push_back( vCBdR );
    m_probeCBtpdR.push_back( vCBtpdR );
    m_probeCBPt.push_back( vCBpt );
    m_probeCBEta.push_back( vCBeta );
    m_probeCBPhi.push_back( vCBphi );
    m_probePassedFTF.push_back( vFTFpass );
    m_probeFTFdR.push_back( vFTFdR );
    m_probeFTFPt.push_back( vFTFpt );
    m_probeFTFEta.push_back( vFTFeta );
    m_probeFTFPhi.push_back( vFTFphi );
    m_probePassedEF.push_back( vEFpass );
    m_probeEFdR.push_back( vEFdR );
    m_probeEFtpdR.push_back( vEFtpdR );
    m_probeEFPt.push_back( vEFpt );
    m_probeEFEta.push_back( vEFeta );
    m_probeEFPhi.push_back( vEFphi );

  }
  
  //cout << "Hello8" << endl;
  return 0;
}

int TagAndProbe::matchL1( const L1Item& L1, const xAOD::Muon* muon, const xAOD::MuonRoIContainer* rois, double* reqdR, int reject, double* param ) {
///this function is used for Roi matching in L1. 
///return is matchedroinumber.
  int matchedRoINumber = -1;
  const double muPt   = muon->pt();
  const double muEta  = muon->eta();
  const double muPhi  = muon->phi();
  const xAOD::TrackParticle* mutrk = muon->trackParticle( xAOD::Muon::InnerDetectorTrackParticle );
  pair< double, double > extEtaAndPhi = m_ext.extTrack( mutrk );
  const double muExtEta = ( mutrk )? extEtaAndPhi.first:muEta;
  const double muExtPhi = ( mutrk )? extEtaAndPhi.second:muPhi;
  //cout << "ETA : " << muEta << "=>" << muExtEta << "( Pt=" << muPt << " )"<< endl;
  //cout << "PHI : " << muPhi << "=>" << muExtPhi << "( Pt=" << muPt << " )"<< endl;
  xAOD::MuonRoIContainer::const_iterator rois_itr = rois->begin();
  xAOD::MuonRoIContainer::const_iterator rois_end = rois->end();
  for ( ; rois_itr!=rois_end; ++rois_itr ) {
    const int roiNum      = (*rois_itr)->getRoI();
    int roiSector   = (*rois_itr)->getSectorAddress();
    const int roiThr      = (*rois_itr)->getThrNumber();
    const int roiPt       = (*rois_itr)->thrValue();
    const double roiEta   = (*rois_itr)->eta();
    const double roiPhi   = (*rois_itr)->phi();
    if( L1 > roiThr ) continue;
    if( roiNum == reject ) continue;
    const double roidRof  = m_utils.deltaR( muEta, muPhi, roiEta, roiPhi);
    const double roidRex  = m_utils.deltaR( muExtEta, muExtPhi, roiEta, roiPhi);
    //cout << "DR: " << roidRof << ":" << roidRex << endl;
    if( m_message>1 ) cout << "L1 : " << muPt << ", " << roiThr << endl;
    bool pass = ( m_useExt )? ( *reqdR > roidRex ):( *reqdR > roidRof );
    if( pass ) {
      matchedRoINumber  = roiNum;
      *reqdR            = ( m_useExt )? roidRex:roidRof;
      param[0]  = roiPt;
      param[1]  = roiEta;
      param[2]  = roiPhi;
      param[3]  = matchedRoINumber;
      // intro of bit meaning : https://twiki.cern.ch/twiki/bin/view/Main/L1TGCNtuple#sectorAddress_8_bit_information
      int tmp_roiSector = roiSector >> 1;//
      (roiSector >= 64) ? (roiSector = tmp_roiSector & 0x3f) : (roiSector = tmp_roiSector & 0x1f);//
      param[4]  = roiSector;//
    }
  }
  return matchedRoINumber;
}

int TagAndProbe::matchSA( const Trig::FeatureContainer& fc, double* L1param, double* param, std::vector< float >& vec_param_X, std::vector< float >& vec_param_Y, std::vector< float >& vec_param_Z, std::vector< string >& vec_param_string, std::string& mesSATEName, std::vector< std::vector < float> >& vec_param_road, vector < vector < int > >& vec_param_mdtInt, vector < vector < float > >& vec_param_mdtFloat ) 
{
  ///this function is used for SA matching. 
  int isPassedSA = -1;
  //auto fL2SAs = fc.containerFeature<xAOD::L2StandAloneMuonContainer>( "", TrigDefs::alsoDeactivateTEs );
  const std::vector< Trig::Feature<xAOD::L2StandAloneMuonContainer> > fL2SAs = fc.get<xAOD::L2StandAloneMuonContainer>( "", TrigDefs::alsoDeactivateTEs );
  // L2muonSA matching

  if ( dataType == "data17" ){
    Trig::ExpertMethods* expert = m_trigDecTool -> ExperimentalAndExpertMethods();
    expert->enable();
    for(auto fL2SA : fL2SAs){
      const HLT::TriggerElement *trigElement1 = fL2SA.te();
      std::vector<HLT::TriggerElement*> TEsuccessors = expert->getNavigation()->getDirectSuccessors(trigElement1);
      //cout << "teName=" << Trig::getTEName( *trigElement1 ) << endl;
      Bool_t isActiveTE = kFALSE;
      for(auto te2 : TEsuccessors){
        //cout << "teName=" << Trig::getTEName( *te2 ) << " as=" << te2 -> getActiveState() << endl;
        if ( te2 -> getActiveState() ){
          TString teName = Trig::getTEName( *te2 );
          if ( (teName.Contains( "L2_mu_SAhyp") && teName.Contains( mesSATEName.c_str() ) )|| ( teName.Contains("L2_mu_hypo1" ) ) )
            isActiveTE = kTRUE;
        }
        //check active state of te2, and match name to threshold to be sure it is from the right chain
      }
      const xAOD::L2StandAloneMuonContainer* cont = fL2SA.cptr();
      for( const auto& l2sa : *cont ) {
        const int l2saRoINum  = l2sa->roiNumber();
        const int l2saRoISec  = l2sa->roiSector();
        //cout << "MyCheck: saRoi=" << l2saRoINum << " L1Roi=" << L1num << " idte=" << l2saTE -> getId() << " nameTE=" << Trig::getTEName( *l2saTE ) . c_str() << endl;
        if( l2saRoINum != L1param[3] || l2saRoISec != L1param[4] ) continue; 
        pair< double, double > extsa = m_ext.extTrackMuComb( l2sa );
        const int nTP = l2sa->nTrackPositions();
        const double l2saPt     = l2sa->pt();
        const double l2saEtaIP  = l2sa->eta();
        const double l2saPhiIP  = l2sa->phi();
        const double l2saEtaMS  = l2sa->etaMS();
        const double l2saPhiMS  = l2sa->phiMS();
        const double l2saEtaBE  = extsa.first;
        const double l2saPhiBE  = extsa.second;
        //
        const double l2saTgcPt  = l2sa->tgcPt();
        const double l2saPtBarrelRadius  = l2sa->ptBarrelRadius();
        const double l2saPtBarrelSagitta  = l2sa->ptBarrelSagitta();
        const double l2saPtEndcapAlpha  = l2sa->ptEndcapAlpha();
        const double l2saPtEndcapBeta  = l2sa->ptEndcapBeta();
        const double l2saPtEndcapRadius  = l2sa->ptEndcapRadius();
        const double l2saPtCSC = l2sa->ptCSC();
        const double l2saSAddress  = l2sa->sAddress();

        const double l2saroiEta  = l2sa->roiEta();
        const double l2saroiPhi  = l2sa->roiPhi();
        const double l2saisRpcFailure  = l2sa->isRpcFailure();
        const double l2saisTgcFailure  = l2sa->isTgcFailure();
        //
        //float superPointR( int chamber ) const; ( defined in L2StandAloneMuon.h )
        //enum Chamber {BarrelInner = 0, BarrelMiddle = 1, BarrelOuter =2, EndcapInner =3, EndcapMiddle = 4, EndcapOuter = 5,EndcapExtra =6, CSC = 7, BEE = 8, BME = 9, Backup = 10, MaxChamber = 11} ( defined in TrigMuonDefs.h )
        const double l2saSuperPointRBI  = l2sa->superPointR(0);
        const double l2saSuperPointRBM  = l2sa->superPointR(1);
        const double l2saSuperPointRBO  = l2sa->superPointR(2);
        const double l2saSuperPointREI  = l2sa->superPointR(3);
        const double l2saSuperPointREM  = l2sa->superPointR(4);
        const double l2saSuperPointREO  = l2sa->superPointR(5);
        const double l2saSuperPointREE  = l2sa->superPointR(6);
        const double l2saSuperPointRCSC = l2sa->superPointR(7);
        const double l2saSuperPointRBEE = l2sa->superPointR(8);
        const double l2saSuperPointRBME = l2sa->superPointR(9);
        //float superPointZ( int chamber ) const; ( defined in L2StandAloneMuon.h )
        const double l2saSuperPointZBI  = l2sa->superPointZ(0);
        const double l2saSuperPointZBM  = l2sa->superPointZ(1);
        const double l2saSuperPointZBO  = l2sa->superPointZ(2);
        const double l2saSuperPointZEI  = l2sa->superPointZ(3);
        const double l2saSuperPointZEM  = l2sa->superPointZ(4);
        const double l2saSuperPointZEO  = l2sa->superPointZ(5);
        const double l2saSuperPointZEE  = l2sa->superPointZ(6);
        const double l2saSuperPointZCSC = l2sa->superPointZ(7);
        const double l2saSuperPointZBEE = l2sa->superPointZ(8);
        const double l2saSuperPointZBME = l2sa->superPointZ(9);
        //float superPointSlope( int chamber ) const; ( defined in L2StandAloneMuon.h )
        const double l2saSuperPointSlopeBI  = l2sa->superPointSlope(0);
        const double l2saSuperPointSlopeBM  = l2sa->superPointSlope(1);
        const double l2saSuperPointSlopeBO  = l2sa->superPointSlope(2);
        const double l2saSuperPointSlopeEI  = l2sa->superPointSlope(3);
        const double l2saSuperPointSlopeEM  = l2sa->superPointSlope(4);
        const double l2saSuperPointSlopeEO  = l2sa->superPointSlope(5);
        const double l2saSuperPointSlopeEE  = l2sa->superPointSlope(6);
        const double l2saSuperPointSlopeCSC = l2sa->superPointSlope(7);
        const double l2saSuperPointSlopeBEE = l2sa->superPointSlope(8);
        const double l2saSuperPointSlopeBME = l2sa->superPointSlope(9);
        //float superPointIntercept( int chamber ) const; ( defined in L2StandAloneMuon.h )
        const double l2saSuperPointInterceptBI  = l2sa->superPointIntercept(0);
        const double l2saSuperPointInterceptBM  = l2sa->superPointIntercept(1);
        const double l2saSuperPointInterceptBO  = l2sa->superPointIntercept(2);
        const double l2saSuperPointInterceptEI  = l2sa->superPointIntercept(3);
        const double l2saSuperPointInterceptEM  = l2sa->superPointIntercept(4);
        const double l2saSuperPointInterceptEO  = l2sa->superPointIntercept(5);
        const double l2saSuperPointInterceptEE  = l2sa->superPointIntercept(6);
        const double l2saSuperPointInterceptCSC = l2sa->superPointIntercept(7);
        const double l2saSuperPointInterceptBEE = l2sa->superPointIntercept(8);
        const double l2saSuperPointInterceptBME = l2sa->superPointIntercept(9);
        //float superPointChi2( int chamber ) const; ( defined in L2StandAloneMuon.h )
        const double l2saSuperPointChi2BI  = l2sa->superPointChi2(0);
        const double l2saSuperPointChi2BM  = l2sa->superPointChi2(1);
        const double l2saSuperPointChi2BO  = l2sa->superPointChi2(2);
        const double l2saSuperPointChi2EI  = l2sa->superPointChi2(3);
        const double l2saSuperPointChi2EM  = l2sa->superPointChi2(4);
        const double l2saSuperPointChi2EO  = l2sa->superPointChi2(5);
        const double l2saSuperPointChi2EE  = l2sa->superPointChi2(6);
        const double l2saSuperPointChi2CSC = l2sa->superPointChi2(7);
        const double l2saSuperPointChi2BEE = l2sa->superPointChi2(8);
        const double l2saSuperPointChi2BME = l2sa->superPointChi2(9);
        //
        const std::vector < float > l2saRpcHitX = l2sa->rpcHitX();
        const std::vector < float > l2saRpcHitY = l2sa->rpcHitY();
        const std::vector < float > l2saRpcHitZ = l2sa->rpcHitZ();
        const std::vector < string > l2saRpcHitStationName = l2sa->rpcHitStationName();
        //
        vector < int > l2samdtHitIsOutlier, l2samdtHitChamber;
        vector < float > l2samdtHitR, l2samdtHitZ, l2samdtHitPhi, l2samdtHitResidual;
        for ( uint32_t i =0; i < l2sa->nMdtHits(); i++){
          l2samdtHitIsOutlier.push_back(l2sa->mdtHitIsOutlier(i));
          l2samdtHitChamber.push_back(l2sa->mdtHitChamber(i));
          l2samdtHitR.push_back(l2sa->mdtHitR(i));
          l2samdtHitZ.push_back(l2sa->mdtHitZ(i));
          l2samdtHitPhi.push_back(l2sa->mdtHitPhi(i));
          l2samdtHitResidual.push_back(l2sa->mdtHitResidual(i));
        }
        std::vector < float > l2saroadAw;
        std::vector < float > l2saroadBw;
        std::vector < float > l2sazMin;
        std::vector < float > l2sazMax;
        std::vector < float > l2sarMin;
        std::vector < float > l2sarMax;
        std::vector < float > l2saetaMin;
        std::vector < float > l2saetaMax;
        for ( int i = 0; i < 9; i++){
          l2saroadAw.push_back(l2sa->roadAw(i,0));
          l2saroadBw.push_back(l2sa->roadBw(i,0));
          l2sazMin.push_back(l2sa->zMin(i,0));
          l2sazMax.push_back(l2sa->zMax(i,0));
          l2sarMin.push_back(l2sa->rMin(i,0));
          l2sarMax.push_back(l2sa->rMax(i,0));
          l2saetaMin.push_back(l2sa->etaMin(i,0));
          l2saetaMax.push_back(l2sa->etaMax(i,0));
        }
        //
        if( m_message>1 ) cout << "SA : " << l2saPt << endl;

        param[0]   = l2saPt;
        param[1]   = l2saEtaIP;
        param[2]   = l2saPhiIP;
        param[3]   = l2saEtaMS;
        param[4]   = l2saPhiMS;
        param[5]   = l2saEtaBE;
        param[6]   = l2saPhiBE;
        //
        param[7]   = l2saTgcPt;
        param[8]   = l2saPtBarrelRadius;
        param[9]   = l2saPtBarrelSagitta;
        param[10]  = l2saPtEndcapAlpha;
        param[11]  = l2saPtEndcapBeta;
        param[12]  = l2saPtEndcapRadius;
        param[13]  = l2saPtCSC;
        param[14]  = l2saSAddress;
        //
        param[15]  = l2saSuperPointRBI; 
        param[16]  = l2saSuperPointRBM; 
        param[17]  = l2saSuperPointRBO; 
        param[18]  = l2saSuperPointREI; 
        param[19]  = l2saSuperPointREM; 
        param[20]  = l2saSuperPointREO; 
        param[21]  = l2saSuperPointREE; 
        param[22]  = l2saSuperPointRCSC;
        param[23]  = l2saSuperPointRBEE;
        param[24]  = l2saSuperPointRBME;
        //
        param[25]  = l2saSuperPointZBI; 
        param[26]  = l2saSuperPointZBM; 
        param[27]  = l2saSuperPointZBO; 
        param[28]  = l2saSuperPointZEI; 
        param[29]  = l2saSuperPointZEM; 
        param[30]  = l2saSuperPointZEO; 
        param[31]  = l2saSuperPointZEE; 
        param[32]  = l2saSuperPointZCSC;
        param[33]  = l2saSuperPointZBEE;
        param[34]  = l2saSuperPointZBME;
        //
        param[35]  = l2saSuperPointSlopeBI; 
        param[36]  = l2saSuperPointSlopeBM; 
        param[37]  = l2saSuperPointSlopeBO; 
        param[38]  = l2saSuperPointSlopeEI; 
        param[39]  = l2saSuperPointSlopeEM; 
        param[40]  = l2saSuperPointSlopeEO; 
        param[41]  = l2saSuperPointSlopeEE; 
        param[42]  = l2saSuperPointSlopeCSC;
        param[43]  = l2saSuperPointSlopeBEE;
        param[44]  = l2saSuperPointSlopeBME;
        //
        param[45]  = l2saSuperPointInterceptBI; 
        param[46]  = l2saSuperPointInterceptBM; 
        param[47]  = l2saSuperPointInterceptBO; 
        param[48]  = l2saSuperPointInterceptEI; 
        param[49]  = l2saSuperPointInterceptEM; 
        param[50]  = l2saSuperPointInterceptEO; 
        param[51]  = l2saSuperPointInterceptEE; 
        param[52]  = l2saSuperPointInterceptCSC;
        param[53]  = l2saSuperPointInterceptBEE;
        param[54]  = l2saSuperPointInterceptBME;
        //
        param[55]  = l2saSuperPointChi2BI; 
        param[56]  = l2saSuperPointChi2BM; 
        param[57]  = l2saSuperPointChi2BO; 
        param[58]  = l2saSuperPointChi2EI; 
        param[59]  = l2saSuperPointChi2EM; 
        param[60]  = l2saSuperPointChi2EO; 
        param[61]  = l2saSuperPointChi2EE; 
        param[62]  = l2saSuperPointChi2CSC;
        param[63]  = l2saSuperPointChi2BEE;
        param[64]  = l2saSuperPointChi2BME;

        param[65] = l2saroiEta;
        param[66] = l2saroiPhi;
        param[67] = l2saisRpcFailure;
        param[68] = l2saisTgcFailure;

        //vec_param is vector < vector < float > >. l2saRpcHitX is vector < float >.
        vec_param_X = l2saRpcHitX;
        vec_param_Y = l2saRpcHitY;
        vec_param_Z = l2saRpcHitZ;
        vec_param_string = l2saRpcHitStationName;

        vec_param_mdtInt.push_back(l2samdtHitIsOutlier);
        vec_param_mdtInt.push_back(l2samdtHitChamber);
        vec_param_mdtFloat.push_back(l2samdtHitR);
        vec_param_mdtFloat.push_back(l2samdtHitZ);
        vec_param_mdtFloat.push_back(l2samdtHitPhi);
        vec_param_mdtFloat.push_back(l2samdtHitResidual);


        vec_param_road.push_back(l2saroadAw);
        vec_param_road.push_back(l2saroadBw);
        vec_param_road.push_back(l2sazMin);
        vec_param_road.push_back(l2sazMax);
        vec_param_road.push_back(l2sarMin);
        vec_param_road.push_back(l2sarMax);
        vec_param_road.push_back(l2saetaMin);
        vec_param_road.push_back(l2saetaMax);

        if ( isActiveTE ){
          isPassedSA = 1;
          goto RoIMatchingAndSAPassed;
        } else {
          isPassedSA = -2;
        }

      }
    }
  } else { //// before r9353

    for ( auto& fL2SA : fL2SAs ) {
      const HLT::TriggerElement* l2saTE = ( fL2SA.te() );
      const xAOD::L2StandAloneMuonContainer* cont = fL2SA.cptr();
      for( const auto& l2sa : *cont ) {
        const int l2saRoINum  = l2sa->roiNumber();
        const int l2saRoISec  = l2sa->roiSector();
        if( l2saRoINum != L1param[3] || l2saRoISec != L1param[4] ) continue; 
        pair< double, double > extsa = m_ext.extTrackMuComb( l2sa );
        const int nTP = l2sa->nTrackPositions();
        const double l2saPt     = l2sa->pt();
        const double l2saEtaIP  = l2sa->eta();
        const double l2saPhiIP  = l2sa->phi();
        const double l2saEtaMS  = l2sa->etaMS();
        const double l2saPhiMS  = l2sa->phiMS();
        const double l2saEtaBE  = extsa.first;
        const double l2saPhiBE  = extsa.second;
        //
        const double l2saTgcPt  = l2sa->tgcPt();
        const double l2saPtBarrelRadius  = l2sa->ptBarrelRadius();
        const double l2saPtBarrelSagitta  = l2sa->ptBarrelSagitta();
        const double l2saPtEndcapAlpha  = l2sa->ptEndcapAlpha();
        const double l2saPtEndcapBeta  = l2sa->ptEndcapBeta();
        const double l2saPtEndcapRadius  = l2sa->ptEndcapRadius();
        const double l2saPtCSC = l2sa->ptCSC();
        const double l2saSAddress  = l2sa->sAddress();

        const float l2saroiEta  = l2sa->roiEta();
        const float l2saroiPhi  = l2sa->roiPhi();
        const int l2saisRpcFailure  = l2sa->isRpcFailure();
        const int l2saisTgcFailure  = l2sa->isTgcFailure();
        //float superPointR( int chamber ) const; ( defined in L2StandAloneMuon.h )
        //enum Chamber {BarrelInner = 0, BarrelMiddle = 1, BarrelOuter = 2, EndcapInner = 3, EndcapMiddle = 4, EndcapOuter = 5, EndcapExtra = 6, CSC = 7, BEE = 8, BME = 9, Backup = 10, MaxChamber = 11} ( defined in TrigMuonDefs.h )
        const double l2saSuperPointRBI  = l2sa->superPointR(0);
        const double l2saSuperPointRBM  = l2sa->superPointR(1);
        const double l2saSuperPointRBO  = l2sa->superPointR(2);
        const double l2saSuperPointREI  = l2sa->superPointR(3);
        const double l2saSuperPointREM  = l2sa->superPointR(4);
        const double l2saSuperPointREO  = l2sa->superPointR(5);
        const double l2saSuperPointREE  = l2sa->superPointR(6);
        const double l2saSuperPointRCSC = l2sa->superPointR(7);
        const double l2saSuperPointRBEE = l2sa->superPointR(8);
        const double l2saSuperPointRBME = l2sa->superPointR(9);
        //float superPointZ( int chamber ) const; ( defined in L2StandAloneMuon.h )
        const double l2saSuperPointZBI  = l2sa->superPointZ(0);
        const double l2saSuperPointZBM  = l2sa->superPointZ(1);
        const double l2saSuperPointZBO  = l2sa->superPointZ(2);
        const double l2saSuperPointZEI  = l2sa->superPointZ(3);
        const double l2saSuperPointZEM  = l2sa->superPointZ(4);
        const double l2saSuperPointZEO  = l2sa->superPointZ(5);
        const double l2saSuperPointZEE  = l2sa->superPointZ(6);
        const double l2saSuperPointZCSC = l2sa->superPointZ(7);
        const double l2saSuperPointZBEE = l2sa->superPointZ(8);
        const double l2saSuperPointZBME = l2sa->superPointZ(9);
        //float superPointSlope( int chamber ) const; ( defined in L2StandAloneMuon.h )
        const double l2saSuperPointSlopeBI  = l2sa->superPointSlope(0);
        const double l2saSuperPointSlopeBM  = l2sa->superPointSlope(1);
        const double l2saSuperPointSlopeBO  = l2sa->superPointSlope(2);
        const double l2saSuperPointSlopeEI  = l2sa->superPointSlope(3);
        const double l2saSuperPointSlopeEM  = l2sa->superPointSlope(4);
        const double l2saSuperPointSlopeEO  = l2sa->superPointSlope(5);
        const double l2saSuperPointSlopeEE  = l2sa->superPointSlope(6);
        const double l2saSuperPointSlopeCSC = l2sa->superPointSlope(7);
        const double l2saSuperPointSlopeBEE = l2sa->superPointSlope(8);
        const double l2saSuperPointSlopeBME = l2sa->superPointSlope(9);
        //float superPointIntercept( int chamber ) const; ( defined in L2StandAloneMuon.h )
        const double l2saSuperPointInterceptBI  = l2sa->superPointIntercept(0);
        const double l2saSuperPointInterceptBM  = l2sa->superPointIntercept(1);
        const double l2saSuperPointInterceptBO  = l2sa->superPointIntercept(2);
        const double l2saSuperPointInterceptEI  = l2sa->superPointIntercept(3);
        const double l2saSuperPointInterceptEM  = l2sa->superPointIntercept(4);
        const double l2saSuperPointInterceptEO  = l2sa->superPointIntercept(5);
        const double l2saSuperPointInterceptEE  = l2sa->superPointIntercept(6);
        const double l2saSuperPointInterceptCSC = l2sa->superPointIntercept(7);
        const double l2saSuperPointInterceptBEE = l2sa->superPointIntercept(8);
        const double l2saSuperPointInterceptBME = l2sa->superPointIntercept(9);
        //float superPointChi2( int chamber ) const; ( defined in L2StandAloneMuon.h )
        const double l2saSuperPointChi2BI  = l2sa->superPointChi2(0);
        const double l2saSuperPointChi2BM  = l2sa->superPointChi2(1);
        const double l2saSuperPointChi2BO  = l2sa->superPointChi2(2);
        const double l2saSuperPointChi2EI  = l2sa->superPointChi2(3);
        const double l2saSuperPointChi2EM  = l2sa->superPointChi2(4);
        const double l2saSuperPointChi2EO  = l2sa->superPointChi2(5);
        const double l2saSuperPointChi2EE  = l2sa->superPointChi2(6);
        const double l2saSuperPointChi2CSC = l2sa->superPointChi2(7);
        const double l2saSuperPointChi2BEE = l2sa->superPointChi2(8);
        const double l2saSuperPointChi2BME = l2sa->superPointChi2(9);
        //
        const std::vector < float > l2saRpcHitX = l2sa->rpcHitX();
        const std::vector < float > l2saRpcHitY = l2sa->rpcHitY();
        const std::vector < float > l2saRpcHitZ = l2sa->rpcHitZ();
        const std::vector < string > l2saRpcHitStationName = l2sa->rpcHitStationName();

        vector < int > l2samdtHitIsOutlier, l2samdtHitChamber;
        vector < float > l2samdtHitR, l2samdtHitZ, l2samdtHitPhi, l2samdtHitResidual;
        for ( uint32_t i =0; i < l2sa->nMdtHits(); i++){
          l2samdtHitIsOutlier.push_back(l2sa->mdtHitIsOutlier(i));
          l2samdtHitChamber.push_back(l2sa->mdtHitChamber(i));
          l2samdtHitR.push_back(l2sa->mdtHitR(i));
          l2samdtHitZ.push_back(l2sa->mdtHitZ(i));
          l2samdtHitPhi.push_back(l2sa->mdtHitPhi(i));
          l2samdtHitResidual.push_back(l2sa->mdtHitResidual(i));
        }
        //
        if( m_message>1 ) cout << "SA : " << l2saPt << endl;
        //if( nTP<2 && l2sa->sAddress()==-1) { 
        //  cout << "L2SA pt: " << l2saPt << endl;
        //  cout << "MS: " << l2saEtaMS << ", " << l2saPhiMS << endl;
        //  cout << "IP: " << l2saEtaIP << ", " << l2saPhiIP << endl;
        //  cout << "BE: " << l2saEtaBE << ", " << l2saPhiBE << endl;
        //}
        param[0]  = l2saPt;
        param[1]  = l2saEtaIP;
        param[2]  = l2saPhiIP;
        param[3]  = l2saEtaMS;
        param[4]  = l2saPhiMS;
        param[5]  = l2saEtaBE;
        param[6]  = l2saPhiBE;
        //
        param[7]  = l2saTgcPt;
        param[8]  = l2saPtBarrelRadius;
        param[9]  = l2saPtBarrelSagitta;
        param[10]  = l2saPtEndcapAlpha;
        param[11]  = l2saPtEndcapBeta;
        param[12]  = l2saPtEndcapRadius;
        param[13]  = l2saPtCSC;
        param[14]  = l2saSAddress;
        //
        param[15]  = l2saSuperPointRBI; 
        param[16]  = l2saSuperPointRBM; 
        param[17]  = l2saSuperPointRBO; 
        param[18]  = l2saSuperPointREI; 
        param[19]  = l2saSuperPointREM; 
        param[20]  = l2saSuperPointREO; 
        param[21]  = l2saSuperPointREE; 
        param[22]  = l2saSuperPointRCSC;
        param[23]  = l2saSuperPointRBEE;
        param[24]  = l2saSuperPointRBME;
        //
        param[25]  = l2saSuperPointZBI; 
        param[26]  = l2saSuperPointZBM; 
        param[27]  = l2saSuperPointZBO; 
        param[28]  = l2saSuperPointZEI; 
        param[29]  = l2saSuperPointZEM; 
        param[30]  = l2saSuperPointZEO; 
        param[31]  = l2saSuperPointZEE; 
        param[32]  = l2saSuperPointZCSC;
        param[33]  = l2saSuperPointZBEE;
        param[34]  = l2saSuperPointZBME;
        //
        param[35]  = l2saSuperPointSlopeBI; 
        param[36]  = l2saSuperPointSlopeBM; 
        param[37]  = l2saSuperPointSlopeBO; 
        param[38]  = l2saSuperPointSlopeEI; 
        param[39]  = l2saSuperPointSlopeEM; 
        param[40]  = l2saSuperPointSlopeEO; 
        param[41]  = l2saSuperPointSlopeEE; 
        param[42]  = l2saSuperPointSlopeCSC;
        param[43]  = l2saSuperPointSlopeBEE;
        param[44]  = l2saSuperPointSlopeBME;
        //
        param[45]  = l2saSuperPointInterceptBI; 
        param[46]  = l2saSuperPointInterceptBM; 
        param[47]  = l2saSuperPointInterceptBO; 
        param[48]  = l2saSuperPointInterceptEI; 
        param[49]  = l2saSuperPointInterceptEM; 
        param[50]  = l2saSuperPointInterceptEO; 
        param[51]  = l2saSuperPointInterceptEE; 
        param[52]  = l2saSuperPointInterceptCSC;
        param[53]  = l2saSuperPointInterceptBEE;
        param[54]  = l2saSuperPointInterceptBME;
        //
        param[55]  = l2saSuperPointChi2BI; 
        param[56]  = l2saSuperPointChi2BM; 
        param[57]  = l2saSuperPointChi2BO; 
        param[58]  = l2saSuperPointChi2EI; 
        param[59]  = l2saSuperPointChi2EM; 
        param[60]  = l2saSuperPointChi2EO; 
        param[61]  = l2saSuperPointChi2EE; 
        param[62]  = l2saSuperPointChi2CSC;
        param[63]  = l2saSuperPointChi2BEE;
        param[64]  = l2saSuperPointChi2BME;

        param[65] = l2saroiEta;
        param[66] = l2saroiPhi;
        param[67] = l2saisRpcFailure;
        param[68] = l2saisTgcFailure;
        // vec_param is vector < vector < float > >. l2saRpcHitX is vector < float >.
        vec_param_X = l2saRpcHitX;
        vec_param_Y = l2saRpcHitY;
        vec_param_Z = l2saRpcHitZ;
        vec_param_string = l2saRpcHitStationName;
        //
        if( l2saTE->getActiveState() ) {
          isPassedSA = 1;
          goto RoIMatchingAndSAPassed;
        } else {
          isPassedSA = -2;
        }
      }
    }
  }
RoIMatchingAndSAPassed:
  return isPassedSA;
}

int TagAndProbe::matchCB( const Trig::FeatureContainer& fc, int L1num, double* param, std::string& cbTEName ) 
{
  int isPassedCB = -1;
  TString tsCBTEName = cbTEName.c_str();
  //auto fL2CBs = fc.containerFeature<xAOD::L2CombinedMuonContainer>( "", TrigDefs::alsoDeactivateTEs );
  Trig::ExpertMethods* expert = m_trigDecTool -> ExperimentalAndExpertMethods();
  expert->enable();
  const std::vector< Trig::Feature<xAOD::L2CombinedMuonContainer> > fL2CBs = fc.get<xAOD::L2CombinedMuonContainer>( "", TrigDefs::alsoDeactivateTEs );
  // L2muComb matching
  for ( auto& fL2CB : fL2CBs ) {
    const HLT::TriggerElement* trigElement1 = ( fL2CB.te() );
    const xAOD::L2CombinedMuonContainer* cont = fL2CB.cptr();
    std::vector<HLT::TriggerElement*> TEsuccessors = expert->getNavigation()->getDirectSuccessors(trigElement1);
    cout << "teName=" << Trig::getTEName( *trigElement1 ) << endl;
    Bool_t isActiveTE = kFALSE;
    for(auto te2 : TEsuccessors){
      cout << "teName=" << Trig::getTEName( *te2 ) << " as=" << te2 -> getActiveState() << endl;
      if ( te2 -> getActiveState() ){
        TString teName = Trig::getTEName( *te2 );
        if ( ( teName.Contains( "L2_mucombhyp") && teName.Contains( tsCBTEName.Data() ) ) || teName.Contains( "L2_mu_hypo2" ) )
          isActiveTE = kTRUE;
      }
    }
    for( const auto& l2cb : *cont ) {
      const int l2cbRoINum  = l2cb->muSATrack()->roiNumber();
      if( l2cbRoINum != L1num ) continue; 
      const double l2cbPt   = l2cb->pt();
      const double l2cbEta  = l2cb->eta();
      const double l2cbPhi  = l2cb->phi();
      if( m_message>1 ) cout << "CB : " << l2cbPt << endl;
      //if( l2cbTE->getActiveState() ) {
      if ( dataType == "data17" ){
        if ( isActiveTE ){
          isPassedCB = 1;
          param[0]  = l2cbPt;
          param[1]  = l2cbEta;
          param[2]  = l2cbPhi;
        }
      } else {
        if ( trigElement1 -> getActiveState() ){
          isPassedCB = 1;
          param[0]  = l2cbPt;
          param[1]  = l2cbEta;
          param[2]  = l2cbPhi;
        }
      }
      //}
      //cout << "L2CB: " << l2cbPt << ", " << l2cbEta << ", " << l2cbPhi << "==>" << isPassedCB << "(" << l2cb->errorFlag() << ", " << l2cb->matchFlag() << ", " << l2cb->sigmaPt() << ")" << endl;
    }
  }
  return isPassedCB;
}

int TagAndProbe::matchCB( const xAOD::Muon* muon, const Trig::FeatureContainer& fc, double* reqdR, double* param, std::string& cbTEName ) {
  TString tsCBTEName = cbTEName.c_str();
  int isPassedCB = -1;
  const double muPt   = muon->pt();
  const double muEta  = muon->eta();
  const double muPhi  = muon->phi();
  //auto fL2CBs = fc.containerFeature<xAOD::L2CombinedMuonContainer>( "", TrigDefs::alsoDeactivateTEs );
  Trig::ExpertMethods* expert = m_trigDecTool -> ExperimentalAndExpertMethods();
  expert->enable();
  const std::vector< Trig::Feature<xAOD::L2CombinedMuonContainer> > fL2CBs = fc.get<xAOD::L2CombinedMuonContainer>( "", TrigDefs::alsoDeactivateTEs );
  int l2cbNum = 0;
  for ( auto& fL2CB : fL2CBs ) {
    const HLT::TriggerElement* trigElement1 = ( fL2CB.te() );
    const xAOD::L2CombinedMuonContainer* cont = fL2CB.cptr();
    //cout << "MyCheck: nameTE=" << Trig::getTEName( *l2cbTE ) . c_str() << endl;
    std::vector<HLT::TriggerElement*> TEsuccessors = expert->getNavigation()->getDirectSuccessors(trigElement1);
    //cout << "teName=" << Trig::getTEName( *trigElement1 ) << endl;
    Bool_t isActiveTE = kFALSE;
    for(auto te2 : TEsuccessors){
      //cout << "teName=" << Trig::getTEName( *te2 ) << " as=" << te2 -> getActiveState() << endl;
      if ( te2 -> getActiveState() ){
        TString teName = Trig::getTEName( *te2 );
        if ( ( teName.Contains( "L2_mucombhyp") && teName.Contains( tsCBTEName.Data() ) ) || teName.Contains( "L2_mu_hypo2" ) )
          isActiveTE = kTRUE;
      }
    }
    for( const auto& l2cb : *cont ) {
      l2cbNum++;
      const double l2cbPt   = l2cb->pt();
      const double l2cbEta  = l2cb->eta();
      const double l2cbPhi  = l2cb->phi();
      const double l2cbCharge = l2cb->charge();
      const double l2cbError  = l2cb->errorFlag();
      const double l2cbMatch  = l2cb->matchFlag();
      const double l2cbdRmu = m_utils.deltaR( muEta, muPhi, l2cbEta, l2cbPhi);
      //const double l2cbdRex  = m_utils.deltaR( exmuEta, exmuPhi, l2cbEta, l2cbPhi);
      //cout << "CB matching : " << muPt << ":" << l2cbPt << "( Q=" << l2cbCharge << ") ==> " << l2cbError << ":" << l2cbMatch << ":" << l2cbTE->getActiveState() << ":" << l2cbdRmu << endl;
      bool pass = ( *reqdR > l2cbdRmu );
      if( m_message>1 ) cout << "CB : " << muPt << ", " << l2cbPt << endl;
      
      if ( !pass ) continue;
      /*
      if( pass && isActiveTE ) {
        *reqdR    = l2cbdRmu;
        param[0]  = l2cbPt;
        param[1]  = l2cbEta;
        param[2]  = l2cbPhi;
        param[3]  = l2cbCharge;
        isPassedCB = 1;
      }
      */
      if ( dataType == "data17" ){
        if ( isActiveTE ){
          *reqdR    = l2cbdRmu;
          param[0]  = l2cbPt;
          param[1]  = l2cbEta;
          param[2]  = l2cbPhi;
          param[3]  = l2cbCharge;
          isPassedCB = 1;
        }
      } else {
        if ( trigElement1 -> getActiveState() ){
          *reqdR    = l2cbdRmu;
          param[0]  = l2cbPt;
          param[1]  = l2cbEta;
          param[2]  = l2cbPhi;
          param[3]  = l2cbCharge;
          isPassedCB = 1;
        }
      }
    }
  }
  //cout << "CB : " << muPt << ":" << muEta << ":" << muPhi << ", " << param[0] << ":" << param[1] << ":" << param[2] << ", " << isPassedCB << endl;
  return isPassedCB;
}

int TagAndProbe::matchFTF( const xAOD::Muon* muon, const xAOD::TrackParticleContainer* ftfs, double* reqdR, double* param ) {
  int isPassedFTF = -1;
  const double muPt    = muon->pt();
  const double muEta   = muon->eta();
  const double muPhi   = muon->phi();
  xAOD::TrackParticleContainer::const_iterator ftfs_itr = ftfs->begin();
  xAOD::TrackParticleContainer::const_iterator ftfs_end = ftfs->end();
  for ( ; ftfs_itr!=ftfs_end; ++ftfs_itr ) {
    const double ftfPt      = (*ftfs_itr)->pt();
    const double ftfEta     = (*ftfs_itr)->eta();
    const double ftfPhi     = (*ftfs_itr)->phi();
    const double ftfCharge  = (*ftfs_itr)->charge();
    const double ftfdRmu    = m_utils.deltaR( muEta, muPhi, ftfEta, ftfPhi);
  //const double l2cbdRex  = m_utils.deltaR( exmuEta, exmuPhi, l2cbEta, l2cbPhi);
  
    bool pass = ( *reqdR > ftfdRmu );
    if( m_message>1 ) cout << "FTF : " << muPt << ", " << ftfPt << "( " << ftfdRmu << " )" << endl;
    if( pass  ) {
      *reqdR    = ftfdRmu;
      isPassedFTF = 1;
      param[0]  = ftfPt;
      param[1]  = ftfEta;
      param[2]  = ftfPhi;
      param[3]  = ftfCharge;
    }
  }
  return isPassedFTF;
}

int TagAndProbe::matchFTF( const xAOD::Muon* muon, const Trig::FeatureContainer& fc, double* reqdR, double* param ) {
  int isPassedEF = -1;
  const double muPt   = muon->pt();
  const double muEta  = muon->eta();
  const double muPhi  = muon->phi();
  const std::vector< Trig::Feature<xAOD::TrackParticleContainer> > fEFs = fc.get<xAOD::TrackParticleContainer>( "", TrigDefs::alsoDeactivateTEs );
  double efPt   = -99999;
  double efEta  = -99999;
  double efPhi  = -99999;
  double efCharge  = -99999;
  double efdRmu = *reqdR;
  for ( auto& fEF : fEFs ) {
    const HLT::TriggerElement* efTE = ( fEF.te() );
    const xAOD::TrackParticleContainer* cont = fEF.cptr();
    for( const auto& ef : *cont ) {
      if( *reqdR < m_utils.deltaR( muEta, muPhi, ef->eta(), ef->phi() ) ) continue;
      if( !efTE->getActiveState() ) continue;
      efPt     = ef->pt();
      efEta    = ef->eta();
      efPhi    = ef->phi();
      efCharge = ef->charge();
      efdRmu   = m_utils.deltaR( muEta, muPhi, efEta, efPhi );
    }
  }
  bool pass = efPt>0;
  if( m_message>1 ) cout << "FTF : " << muPt << ", " << efPt << endl;
  if( pass ) {
    isPassedEF = 1;
    *reqdR    = efdRmu;
    param[0]  = efPt;
    param[1]  = efEta;
    param[2]  = efPhi;
    param[3]  = efCharge;
  }
  return isPassedEF;
}

int TagAndProbe::matchEF( const string& chain, const xAOD::Muon* muon, const Trig::FeatureContainer& fc, double* reqdR, double* param ) {
  int isPassedEF = -1;
  const std::vector< Trig::Feature<xAOD::MuonContainer> > fEFs = fc.get<xAOD::MuonContainer>( "", TrigDefs::alsoDeactivateTEs );
  //const std::vector< Trig::Feature<xAOD::MuonContainer> > fEFs = fc.get<xAOD::MuonContainer>( "" );
  for ( auto& fEF : fEFs ) {
    const HLT::TriggerElement* efTE = ( fEF.te() );
    const xAOD::MuonContainer* cont = fEF.cptr();
    for( const auto& ef : *cont ) {
      if( *reqdR > m_utils.deltaR( muon->eta(), muon->phi(), ef->eta(), ef->phi() ) ){
        if(efTE->getActiveState()) isPassedEF = 1;
        param[0]  = ef->pt();
        param[1]  = ef->eta();
        param[2]  = ef->phi();
        param[3]  = ef->charge();
        *reqdR    = m_utils.deltaR( muon->eta(), muon->phi(), ef->eta(), ef->phi() );
      }
    }
  }
//  bool pass = ( m_utils.muonEFThreshold( ef->eta(), ef->pt()*0.001, chain ) );
//  if( pass ) {
//    isPassedEF = 1;
//    *reqdR    = efdRmu;
//     param[0]  = ef->pt();
//     param[1]  = ef->eta();
//     param[2]  = ef->phi();
//     param[3]  = ef->charge();
//  }
  return isPassedEF;
}

int TagAndProbe::matchEFFS( const string& chain, const xAOD::Muon* muon, const Trig::FeatureContainer& fc, double* reqdR, double* param, double* tagparam ) {
  int isPassedEF = -1;
  //auto fEFs = fc.containerFeature<xAOD::MuonContainer>( "", TrigDefs::alsoDeactivateTEs );
  const std::vector< Trig::Feature<xAOD::MuonContainer> > fEFs = fc.get<xAOD::MuonContainer>( "", TrigDefs::alsoDeactivateTEs );
  //cout << "Muon: " << muPt << ":" << muEta << ":" << muPhi << endl;
  for ( auto& fEF : fEFs ) {
    const HLT::TriggerElement* efTE = ( fEF.te() );
    const xAOD::MuonContainer* cont = fEF.cptr();
    for( const auto& ef : *cont ) {
      //if probe candidate's (eta, phi) is too close to tag, skip 
      if( 0.01 > m_utils.deltaR( tagparam[1], tagparam[2], ef->eta(), ef->phi() ) ) continue;
      if( *reqdR > m_utils.deltaR( muon->eta(), muon->phi(), ef->eta(), ef->phi() ) ){
        if( efTE->getActiveState() ) isPassedEF = 1;
        param[0] = ef->pt();
        param[1] = ef->eta();
        param[2] = ef->phi();
        param[3] = ef->charge();
        *reqdR   = m_utils.deltaR( muon->eta(), muon->phi(), ef->eta(), ef->phi() );
      }
    }
  }
//  bool pass = ( m_utils.muonEFThreshold( efEta, efPt*0.001, chain ) );
//  if( pass ) {
//    isPassedEF = 1;
//    *reqdR    = efdRmu;
//    param[0]  = efPt;
//    param[1]  = efEta;
//    param[2]  = efPhi;
//    param[3]  = efCharge;
//  }
  return isPassedEF;
}

double TagAndProbe::dRL1byPt( double mupt ) {
  double dR = 0.08;
  if( mupt < 10000. ) {
    dR = -0.00001*mupt + 0.18;
  }
  return dR;
}


///Functions below here is used for "int TagAndProbe::addMesChain( const string& name, const L1Item& mesL1, const string& mesHLT, const string& mesAddTag )".
///
Bool_t TagAndProbe::getSATEName( const std::string& mesHLT, std::string& teName )
{
  ///This function is used in "int TagAndProbe::addMesChain ".
  ///mesHLT and teName is parameters.

  TString hlt = mesHLT.c_str();
  TObjArray* toa = hlt . Tokenize( "_" );
  Int_t thrValue = 0;
  Bool_t isBarrelOnly = kFALSE;
  for( Int_t i = 0; i < toa -> GetEntries(); i++ ){
    TString tsToken = (static_cast<TObjString*>( toa -> At(i) ) ) -> String();
    if ( tsToken . Contains( "0eta105" ) ){
      isBarrelOnly = kTRUE;
    }
    if ( !tsToken . Contains( "mu" ) )
      continue;
    tsToken = tsToken.ReplaceAll( "noL1", "" );
    tsToken = tsToken.ReplaceAll( "3mu", "" );
    tsToken = tsToken.ReplaceAll( "2mu", "" );
    tsToken = tsToken.ReplaceAll( "mu", "" );
    if ( !tsToken . IsDec() )
      continue;
    thrValue = tsToken . Atoi();
  }
  if ( thrValue == 0 )
    return 1;
  if ( thrValue == 4 || thrValue == 2 || isBarrelOnly ){
  } else {
    thrValue = 6;
  }
  teName = Form( "%dGeV%s_v15a", thrValue, (isBarrelOnly)?("_barrelOnly"):("") );
  //ATH_MSG_DEBUG("TagAndProbe: Derived TESAName=" << teName);
  return 0;
}

Bool_t TagAndProbe::getSATEName( const char* mesHLT, std::string& teName )
{
  ///THis fuction is similar to TagAndProbe::getSATEName( const std::string& mesHLT, std::string& teName ).
  ///const char* mesHLT --->>> const std::string&.
  std::string s_mesHLT = mesHLT;
  return getSATEName( s_mesHLT, teName );
}

Bool_t TagAndProbe::getCBTEName( const std::string& mesHLT, std::string& teName )
{
  TString hlt = mesHLT.c_str();
  TObjArray* toa = hlt . Tokenize( "_" );
  Int_t thrValue = 0;
  for( Int_t i = 0; i < toa -> GetEntries(); i++ ){
    TString tsToken = (static_cast<TObjString*>( toa -> At(i) ) ) -> String();
    if ( !tsToken . Contains( "mu" ) )
      continue;
    tsToken = tsToken.ReplaceAll( "noL1", "" );
    tsToken = tsToken.ReplaceAll( "3mu", "" );
    tsToken = tsToken.ReplaceAll( "2mu", "" );
    tsToken = tsToken.ReplaceAll( "mu", "" );
    if ( !tsToken . IsDec() )
      continue;
    thrValue = tsToken . Atoi();
  }
  if ( thrValue == 0 )
    return 1;
  if ( thrValue >= 24 )
    thrValue = 22;
  teName = Form( "_mu%d_", thrValue );
  //ATH_MSG_DEBUG("TagAndProbe: Derived TECBName=" << teName);
  return 0;
}

Bool_t TagAndProbe::getCBTEName( const char* mesHLT, std::string& teName )
{
  ///THis fuction is similar to TagAndProbe::getCBTEName( const std::string& mesHLT, std::string& teName ).
  ///const char* mesHLT --->>> const std::string&.
  std::string s_mesHLT = mesHLT;
  return getCBTEName( s_mesHLT, teName );
}
