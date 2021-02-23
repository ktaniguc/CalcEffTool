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

#include "CalcEfficiency/MuInfoGetter.h"
#include "CalcEfficiency/ParticleSelecterTool.h"
#include "CalcEfficiency/Utils.h"

#include "TMath.h"
#include "TObjArray.h"
#include "TObjString.h"
#include "TVector3.h"

using namespace std;

MuInfoGetter::MuInfoGetter()
  : m_trigDecTool( "Trig::TrigDecisionTool/TrigDecisionTool" )
{}

MuInfoGetter::~MuInfoGetter() {
}

int MuInfoGetter::initialize( const int& message,
    const bool& useExt,
    const std::string method,
    MuonExtUtils ext,
    VrtFitUtils vft,
    ToolHandle<Trig::TrigDecisionTool> tdt,
    const std::string dataType,
    const string& name,
    const L1Item& mesL1,
    const string& mesHLT,
    const string& mesAddTag
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
  if( m_method == "ClosebyMuon" ){
    unsigned int Length = mesHLT.length();
    unsigned int msonly = mesHLT.find( "msonly", 0 );
    unsigned int nocb   = mesHLT.find( "nomucomb", 0 );
    unsigned int bronly = mesHLT.find( "0eta105", 0 );
    unsigned int nol1   = mesHLT.find( "noL1", 0 );
    m_trigMesName = name;
    m_trigMesL1 = mesL1;
    m_trigMesHLT = mesHLT;
    m_trigMesAddTagReq = mesAddTag;
    m_trigMesMSonly = (msonly<Length)? 1:0 ;
    m_trigMesNoMucomb = (nocb<Length)? 1:0;
    m_trigMesBRonly = (bronly<Length)? 1:0;
    m_trigMesNoL1 = (nol1<Length)? 1:0;

    std::string trigMesName = "";
    getSATEName( mesHLT, trigMesName );
    m_trigMesSATEName = trigMesName;
    std::string trigMesCBTEName = "";
    getCBTEName( mesHLT, trigMesCBTEName );
    m_trigMesCBTEName = trigMesCBTEName;
    m_SAThresholds[0] = 3.38;
    m_SAThresholds[1] = 1.25;
    m_SAThresholds[2] = 3.17;
    m_SAThresholds[3] = 3.41;
    m_SAWeakThresholds[0] = 2.72;
    m_SAWeakThresholds[1] = 1.58;
    m_CBThresholds[0] = 3.38;
    m_CBThresholds[1] = 1.25;
    m_CBThresholds[2] = 3.17;
    m_CBThresholds[3] = 3.41;
    cout << "= " << name << " ( " << mesL1 << ", " << mesHLT << ": MSonly=" << (msonly<Length) << ", BRonly=" << (bronly<Length) << ", noL1=" << (nol1<Length) << ", TagReq=" << mesAddTag << ", SATEName=" << trigMesName.c_str() << ", CBTEName=" << trigMesCBTEName.c_str() << " )" << endl;
  }else {
    cout << "TagAndProbe : ERROR : Sorry, this method has not been implemented yet! " << endl;
    return 1;
  }

  ///cout information about tap process.
  cout << "= Method   : " << method << endl;
  cout << "=== L1 Trigger  : " << m_trigMesL1 << "\n";
  cout << "=== HLT Trigger : " << m_trigMesHLT << endl;

  return 0;
}

void MuInfoGetter::clear() {
  m_muonOfflinePt.clear();
  m_muonOfflineEta.clear();
  m_muonOfflineExtEta.clear();
  m_muonOfflineExtInnEta.clear();
  m_muonOfflinePhi.clear();
  m_muonOfflineExtPhi.clear();
  m_muonOfflineExtInnPhi.clear();
  m_muonOfflineD0.clear();
  m_muonOfflineZ0.clear();
  m_muonOfflineCharge.clear();
  m_muonOfflineSegmentN.clear();
  m_vMuonOfflineSegmentX.clear();
  m_vMuonOfflineSegmentY.clear();
  m_vMuonOfflineSegmentZ.clear();
  m_vMuonOfflineSegmentPx.clear();
  m_vMuonOfflineSegmentPy.clear();
  m_vMuonOfflineSegmentPz.clear();
  m_vMuonOfflineSegmentChiSquared.clear();
  m_vMuonOfflineSegmentNumberDoF.clear();
  m_vMuonOfflineSegmentChamberIndex.clear();
  m_vMuonOfflineSegmentEtaIndex.clear();
  m_vMuonOfflineSegmentNPrecisionHits.clear();
  m_vMuonOfflineSegmentNPhiLayers.clear();
  m_vMuonOfflineSegmentSector.clear();
  m_vMuonOfflineSegmentNTrigEtaLayers.clear();
  m_muonEFTAGPass.clear();
  m_muonEFTAGPt.clear();
  m_muonEFTAGEta.clear();
  m_muonEFTAGPhi.clear();
  m_muonL1Pass.clear();
  m_muonL1Pt.clear();
  m_muonL1Eta.clear();
  m_muonL1Phi.clear();
  m_muonL1roiNumber.clear();
  m_muonL1roiSector.clear();
  m_muonSAHypoPass.clear();
  m_muonSAOvRmPass.clear();
  m_muonSAPt.clear();
  m_muonSAEta.clear();
  m_muonSAPhi.clear();
  m_muonSAEtaMS.clear();
  m_muonSAPhiMS.clear();
  m_muonSAEtaBE.clear();
  m_muonSAPhiBE.clear();
  m_muonSAtgcPt.clear();
  m_muonSAPtBarrelRadius.clear();
  m_muonSAPtBarrelSagitta.clear();
  m_muonSAPtEndcapAlpha.clear();
  m_muonSAPtEndcapBeta.clear();
  m_muonSAPtEndcapRadius.clear();
  m_muonSAcscPt.clear();
  m_muonSAsAddress.clear();
  m_muonSASuperPointRBI.clear();
  m_muonSASuperPointRBM.clear();
  m_muonSASuperPointRBO.clear();
  m_muonSASuperPointREI.clear();
  m_muonSASuperPointREM.clear();
  m_muonSASuperPointREO.clear();
  m_muonSASuperPointREE.clear();
  m_muonSASuperPointRCSC.clear();
  m_muonSASuperPointRBEE.clear();
  m_muonSASuperPointRBME.clear();
  m_muonSASuperPointZBI.clear();
  m_muonSASuperPointZBM.clear();
  m_muonSASuperPointZBO.clear();
  m_muonSASuperPointZEI.clear();
  m_muonSASuperPointZEM.clear();
  m_muonSASuperPointZEO.clear();
  m_muonSASuperPointZEE.clear();
  m_muonSASuperPointZCSC.clear();
  m_muonSASuperPointZBEE.clear();
  m_muonSASuperPointZBME.clear();
  m_muonSASuperPointSlopeBI.clear();
  m_muonSASuperPointSlopeBM.clear();
  m_muonSASuperPointSlopeBO.clear();
  m_muonSASuperPointSlopeEI.clear();
  m_muonSASuperPointSlopeEM.clear();
  m_muonSASuperPointSlopeEO.clear();
  m_muonSASuperPointSlopeEE.clear();
  m_muonSASuperPointSlopeCSC.clear();
  m_muonSASuperPointSlopeBEE.clear();
  m_muonSASuperPointSlopeBME.clear();
  m_muonSASuperPointInterceptBI.clear();
  m_muonSASuperPointInterceptBM.clear();
  m_muonSASuperPointInterceptBO.clear();
  m_muonSASuperPointInterceptEI.clear();
  m_muonSASuperPointInterceptEM.clear();
  m_muonSASuperPointInterceptEO.clear();
  m_muonSASuperPointInterceptEE.clear();
  m_muonSASuperPointInterceptCSC.clear();
  m_muonSASuperPointInterceptBEE.clear();
  m_muonSASuperPointInterceptBME.clear();
  m_muonSASuperPointChi2BI.clear();
  m_muonSASuperPointChi2BM.clear();
  m_muonSASuperPointChi2BO.clear();
  m_muonSASuperPointChi2EI.clear();
  m_muonSASuperPointChi2EM.clear();
  m_muonSASuperPointChi2EO.clear();
  m_muonSASuperPointChi2EE.clear();
  m_muonSASuperPointChi2CSC.clear();
  m_muonSASuperPointChi2BEE.clear();
  m_muonSASuperPointChi2BME.clear();
  m_muonSAroiEta.clear();
  m_muonSAroiPhi.clear();
  m_muonSAisrpcFailure.clear();
  m_muonSAistgcFailure.clear();
  m_muonSABarrelRadius.clear();
  m_muonSABarrelSagitta.clear();
  m_muonSAEtaMap.clear();
  m_muonSAPhiMap.clear();
  m_muonSAroiNumber.clear();
  m_muonSAroiSector.clear();
  m_vMuonSArpcHitX.clear();
  m_vMuonSArpcHitY.clear();
  m_vMuonSArpcHitZ.clear();
  m_vMuonSArpcHitR.clear();
  m_vMuonSArpcHitEta.clear();
  m_vMuonSArpcHitPhi.clear();
  m_vMuonSArpcHitMeasuresPhi.clear();
  m_vMuonSArpcHitStationName.clear();
  m_vMuonSArpcHitStationNumber.clear();
  m_muonSArpcFitInnPhi.clear();
  m_muonSArpcFitInnSlope.clear();
  m_muonSArpcFitInnOffset.clear();
  m_muonSArpcFitMidPhi.clear();
  m_muonSArpcFitMidSlope.clear();
  m_muonSArpcFitMidOffset.clear();
  m_muonSArpcFitOutPhi.clear();
  m_muonSArpcFitOutSlope.clear();
  m_muonSArpcFitOutOffset.clear();
  m_vMuonSARoadAw.clear();
  m_vMuonSARoadBw.clear();
  m_vMuonSAZMin.clear();
  m_vMuonSAZMax.clear();
  m_vMuonSARMin.clear();
  m_vMuonSARMax.clear();
  m_vMuonSAEtaMin.clear();
  m_vMuonSAEtaMax.clear();
  m_vMuonSAmdtHitIsOutlier.clear();
  m_vMuonSAmdtHitChamber.clear();
  m_vMuonSAmdtHitR.clear();
  m_vMuonSAmdtHitZ.clear();
  m_vMuonSAmdtHitPhi.clear();
  m_vMuonSAmdtHitResidual.clear();
  m_vMuonSAmdtHitSpace.clear();
  m_vMuonSAmdtHitSigma.clear();
  m_muonCBHypoPass.clear();
  m_muonCBOvRmPass.clear();
  m_muonCBPt.clear();
  m_muonCBEta.clear();
  m_muonCBPhi.clear();
  m_muonCBEtaMS.clear();
  m_muonCBPhiMS.clear();
  m_muonEFPass.clear();
  m_muonEFPt.clear();
  m_muonEFEta.clear();
  m_muonEFPhi.clear();

  return;
}

int MuInfoGetter::execute(const xAOD::MuonContainer* muons, const xAOD::MuonRoIContainer* rois){
  xAOD::MuonContainer::const_iterator mu_begin = muons->begin();
  xAOD::MuonContainer::const_iterator mu_end = muons->end();
  if( m_message>1 ) cout << "NMuon : " << muons->size() << endl;
  m_nMuon = muons->size();
  int Nquality = 0;//if Nquality = 0, All muon quality < 0
  //muon loop
  for(auto mu_itr = mu_begin; mu_itr != mu_end; ++mu_itr ){
    int mu_quality = m_pst.getQualityOfTrack( (*mu_itr) );
    cout << "muon quality : " << mu_quality << endl;
    if( mu_quality < 0 ) continue;
    Nquality++;
    const xAOD::Muon* muon = *mu_itr;
    const xAOD::TrackParticle* trk = muon->trackParticle( xAOD::Muon::InnerDetectorTrackParticle);
    const xAOD::Vertex* pv = trk->vertex();
    //offline information
    const double muPt  = muon->pt();
    const double muEta = muon->eta();
    const double muPhi = muon->phi();
    const double muD0  = ( trk )? trk->d0() : -99999.;
    const double muZ0  = ( trk )? trk->z0() : -99999.;
    const double muCharge = muon->charge();
    pair< double, double > extTrk    = m_ext.extTrack( trk );
    pair< double, double > extTrkInn = m_ext.extTrackInner( trk );
    const double trkExtEta = ( trk )? extTrk.first:muEta;
    const double trkExtInnEta = ( trk )? extTrkInn.first:muEta;
    const double trkExtPhi = ( trk )? extTrk.second:muPhi;
    const double trkExtInnPhi = ( trk )? extTrkInn.second:muPhi;
    const double dRL1 = dRL1byPt( muPt );

    //offline segmenti information
    int segmentN = muon->nMuonSegments();
    vector< double > segmentX;
    vector< double > segmentY;
    vector< double > segmentZ;
    vector< double > segmentPx;
    vector< double > segmentPy;
    vector< double > segmentPz;
    vector< double > segmentChiSquared;
    vector< double > segmentNumberDoF;
    vector< double > segmentSector;
    vector< double > segmentChamberIndex;
    vector< double > segmentEtaIndex;
    vector< double > segmentNPrecisionHits;
    vector< double > segmentNPhiLayers;
    vector< double > segmentNTrigEtaLayers;
    for( int iSegment = 0; iSegment < segmentN; ++iSegment){
      const xAOD::MuonSegment* segPointer = muon->muonSegment(iSegment);
      segmentX.push_back( segPointer ->              x() );
      segmentY.push_back( segPointer ->              y() );
      segmentZ.push_back( segPointer ->              z() );
      segmentPx.push_back( segPointer ->             px() );
      segmentPy.push_back( segPointer ->             py() );
      segmentPz.push_back( segPointer ->             pz() );
      segmentChiSquared.push_back( segPointer ->     chiSquared() );
      segmentNumberDoF.push_back( segPointer ->      numberDoF() );
      segmentSector.push_back( segPointer ->         sector() );
      segmentChamberIndex.push_back( segPointer ->   chamberIndex() );
      segmentEtaIndex.push_back( segPointer ->       etaIndex() );
      segmentNPrecisionHits.push_back( segPointer -> nPrecisionHits() );
      segmentNPhiLayers.push_back( segPointer ->     nPhiLayers() );
      segmentNTrigEtaLayers.push_back( segPointer -> nTrigEtaLayers() );
    }
    cout << "Muon Status,   Pt : " << muPt << " Eta : " << muEta << " Phi : " << muPhi << endl;

    //parameter preparation
    int L1pass, SAHypopass, CBHypopass, EFpass, EFTAGpass;
    bool SAOvRmpass, CBOvRmpass;
    vector < float > vSArpcHitX, vSArpcHitY, vSArpcHitZ;
    vector < double > vSArpcHitR, vSArpcHitEta, vSArpcHitPhi, vSArpcHitStationNumber;
    vector < uint32_t > vSArpcHitMeasuresPhi;

    //trigger chain
    Trig::FeatureContainer fc = m_trigDecTool->features( m_trigMesHLT, TrigDefs::alsoDeactivateTEs );
    double L1param[5] = {-99999. -99999., -99999., -99999., -99999.};
    //add "For Loop" by kayamash on 2019/07/05.
    //***********************************************************************
    //SAparam[0] ~ SAparam[6] -> SApt, SAeta, SAphi, SAetams, SAphims, SAetabe, SAphibe,
    //SAparam[7] ~ SAparam[14] -> SAtgcPt, SAptBarrelRadius, SAptBarrelSagitta, SAptEndcapAlpha, SAptENdcapBeta, SAptEndcapRadius, SAptCSC, SAsAddress,
    //SAparam[15] ~ SAparam[24] -> SAsuperPointR* ( * = BI, BM, BO, EI, EM, EO, EE, CSC, BEE, BME )
    //SAparam[25] ~ SAparam[34] -> SAsuperPointZ* ( * = BI, BM, BO, EI, EM, EO, EE, CSC, BEE, BME )
    //SAparam[35] ~ SAparam[44] -> SAsuperPointSlope* ( * = BI, BM, BO, EI, EM, EO, EE, CSC, BEE, BME )
    //SAparam[45] ~ SAparam[54] -> SAsuperPointIntercept* ( * = BI, BM, BO, EI, EM, EO, EE, CSC, BEE, BME )
    //SAparam[55] ~ SAparam[64] -> SAsuperPointChi2* ( * = BI, BM, BO, EI, EM, EO, EE, CSC, BEE, BME )
    //SAparam[65] ~ SAparam[74] -> SARoIEta, SARoIPhi, SAisrpcFailure, SAistgcFailure, SABarrelRadius, SABarrelSagitta, SAEtaMap, SAPhiMap, SARoINumber, SASectorNumber
    //***********************************************************************
    const int sizeOfSAparam = 75;
    double SAparam[sizeOfSAparam];
    for(int tmp_SAparam = 0; tmp_SAparam < sizeOfSAparam; ++tmp_SAparam){
      SAparam[tmp_SAparam] = -99999.;
    }

    //************************************************************************
    //SAparamrpcFit[0] ~ SAparamrpcFit[2] -> rpcFitInn* (* = Phi, SlopePhi, OffsetPhi)
    //SAparamrpcFit[3] ~ SAparamrpcFit[5] -> rpcFitMid* (* = Phi, SlopePhi, OffsetPhi)
    //SAparamrpcFit[6] ~ SAparamrpcFit[8] -> rpcFitOut* (* = Phi, SlopePhi, OffsetPhi)
    //************************************************************************
    const int sizeOfrpcFit = 9;
    float SAparamrpcFit[sizeOfrpcFit];
    for( int tmp_rpcFit = 0; tmp_rpcFit < sizeOfrpcFit; ++tmp_rpcFit){
      SAparamrpcFit[tmp_rpcFit] = -99999.;
    }

    vector < vector < int > > vSAparammdtInt;
    vector < vector < float > > vSAparammdtFloat;
    vector< vector < float > > vSAparamRoad;
    vector< string > vSAparamString;

    //double CBparam[6] = { -99999., -99999., -99999., -99999., -99999., -99999.};
    double CBparam[4] = { -99999., -99999., -99999., -99999.};
    double DUMMYparam[4] = { -99999., -99999., -99999., -99999. };
    double EFTAGparam[4] = { -99999., -99999., -99999., -99999. };
    double EFparam[4] = { -99999., -99999., -99999., -99999. };
    double dRCB = 0.02;
    double dREF = ( m_trigMesMSonly == 0 )? 0.02 : dRL1;
    double dREFTAG = dREF;

    if( m_trigMesAddTagReq != "none" ) {
      Trig::FeatureContainer fct = m_trigDecTool->features( m_trigMesAddTagReq, TrigDefs::alsoDeactivateTEs );
      EFTAGpass = matchEFFS( m_trigMesAddTagReq, muon, fct, &dREFTAG, EFTAGparam, DUMMYparam );
      if( EFTAGpass>-1 && m_trigMesNoL1 == 1 ) cout << m_trigMesName << endl;
    } else {
      EFTAGpass = 0;
    }
    if( m_trigMesNoL1 == 1 ) {
      if( m_trigMesL1 != NOTHING ){
        L1pass = matchL1( m_trigMesL1, muon, rois, &dRL1,  L1param);
      } else {
        L1pass = EFTAGpass;
      }
      SAOvRmpass    = EFTAGpass;
      CBOvRmpass    = EFTAGpass;
      EFpass    = matchEFFS( m_trigMesName, muon, fc, &dREF, EFparam, EFTAGparam );
    } else {
      L1pass    = matchL1( m_trigMesL1, muon, rois, &dRL1,  L1param);
      SAOvRmpass    = matchSA( fc, L1pass, SAparam, vSArpcHitX, vSArpcHitY, vSArpcHitZ, vSArpcHitMeasuresPhi, SAparamrpcFit, vSAparamString, m_trigMesSATEName, vSAparamRoad, vSAparammdtInt, vSAparammdtFloat, L1param);
      CBOvRmpass    = matchCB( muon, fc, &dRCB, CBparam, m_trigMesCBTEName );
      EFpass    = matchEF( m_trigMesHLT, muon, fc, &dREF, EFparam );
    }
    cout << "Trigger : " << m_trigMesName << ", " << L1pass << ", " << SAOvRmpass << ", " << CBOvRmpass << ", " << EFpass << "\n"
      << "L1 Status  : " << L1param[0] << ", " << L1param[1] << ", " << L1param[2] << "\n"
      << "SA Status  : " << SAparam[0] << ", " << SAparam[1] << ", " << SAparam[2] << "\n"
      << "CB Status  : " << CBparam[0]*CBparam[3] << ", " << CBparam[1] << ", " << CBparam[2] << "\n"
      << "EF Status  : " << EFparam[0] << ", " << EFparam[1] << ", " << EFparam[2] << endl;

    //SA,CB Hypo check
    int SAWeakRegion = ECWeakRegion( SAparam[1], SAparam[2] );
    int SAEtaRegion = EtaRegion( SAparam[1] );
    SAHypopass = SAHypo( SAparam[0] , SAEtaRegion, SAWeakRegion );
    int CBEtaRegion = EtaRegion( CBparam[1] );
    CBHypopass = CBHypo( CBparam[0], CBEtaRegion );

    cout << "SA etaMS : " << SAparam[3] << " phiMS : " << SAparam[4] << endl;
    //cout << "CB etaMS : " << CBparam[4] << " phiMS : " << CBparam[5] << endl;

    //packing muon parameters
    //offline
    m_muonOfflinePt.push_back( muPt * 0.001 );
    m_muonOfflineEta.push_back( muEta );
    m_muonOfflineExtEta.push_back( trkExtEta );
    m_muonOfflineExtInnEta.push_back( trkExtInnEta );
    m_muonOfflinePhi.push_back( muPhi );
    m_muonOfflineExtPhi.push_back( trkExtPhi );
    m_muonOfflineExtInnPhi.push_back( trkExtInnPhi );
    m_muonOfflineD0.push_back( muD0 );
    m_muonOfflineZ0.push_back( muZ0 );
    m_muonOfflineCharge.push_back( muCharge );
    m_muonOfflineSegmentN.push_back( segmentN );
    m_vMuonOfflineSegmentX.push_back( segmentX );
    m_vMuonOfflineSegmentY.push_back( segmentY );
    m_vMuonOfflineSegmentZ.push_back( segmentZ );
    m_vMuonOfflineSegmentPx.push_back( segmentPx );
    m_vMuonOfflineSegmentPy.push_back( segmentPy );
    m_vMuonOfflineSegmentPz.push_back( segmentPz );
    m_vMuonOfflineSegmentChiSquared.push_back( segmentChiSquared );
    m_vMuonOfflineSegmentNumberDoF.push_back( segmentNumberDoF );
    m_vMuonOfflineSegmentSector.push_back( segmentSector );
    m_vMuonOfflineSegmentChamberIndex.push_back( segmentChamberIndex );
    m_vMuonOfflineSegmentEtaIndex.push_back( segmentEtaIndex );
    m_vMuonOfflineSegmentNPrecisionHits.push_back( segmentNPrecisionHits );
    m_vMuonOfflineSegmentNPhiLayers.push_back( segmentNPhiLayers );
    m_vMuonOfflineSegmentNTrigEtaLayers.push_back( segmentNTrigEtaLayers );
    //eftag
    m_muonEFTAGPass.push_back( EFTAGpass );
    m_muonEFTAGPt.push_back( EFTAGparam[0] );
    m_muonEFTAGEta.push_back( EFTAGparam[1] );
    m_muonEFTAGPhi.push_back( EFTAGparam[2] );
    //L1
    m_muonL1Pass.push_back( L1pass );
    m_muonL1Pt.push_back( L1param[0] * 0.001 );
    m_muonL1Eta.push_back( L1param[1] );
    m_muonL1Phi.push_back( L1param[2] );
    m_muonL1roiNumber.push_back( (int)L1param[3]);
    m_muonL1roiSector.push_back( (int)L1param[4]);
    //SA
    m_muonSAHypoPass.push_back( SAHypopass );
    m_muonSAOvRmPass.push_back( SAOvRmpass );
    m_muonSAPt.push_back( SAparam[0] );
    m_muonSAEta.push_back( SAparam[1] );
    m_muonSAPhi.push_back( SAparam[2] );
    m_muonSAEtaMS.push_back( SAparam[3] );
    m_muonSAPhiMS.push_back( SAparam[4] );
    m_muonSAEtaBE.push_back( SAparam[5] );
    m_muonSAPhiBE.push_back( SAparam[6] );
    m_muonSAtgcPt.push_back( SAparam[7] );
    m_muonSAPtBarrelRadius.push_back( SAparam[8] );
    m_muonSAPtBarrelSagitta.push_back( SAparam[9] );
    m_muonSAPtEndcapAlpha.push_back( SAparam[10] );
    m_muonSAPtEndcapBeta.push_back( SAparam[11] );
    m_muonSAPtEndcapRadius.push_back( SAparam[12] );
    m_muonSAcscPt.push_back( SAparam[13] );
    m_muonSAsAddress.push_back( SAparam[14] );
    //super point
    m_muonSASuperPointRBI.push_back( SAparam[15] );
    m_muonSASuperPointRBM.push_back( SAparam[16] );
    m_muonSASuperPointRBO.push_back( SAparam[17] );
    m_muonSASuperPointREI.push_back( SAparam[18] );
    m_muonSASuperPointREM.push_back( SAparam[19] );
    m_muonSASuperPointREO.push_back( SAparam[20] );
    m_muonSASuperPointREE.push_back( SAparam[21] );
    m_muonSASuperPointRCSC.push_back( SAparam[22] );
    m_muonSASuperPointRBEE.push_back( SAparam[23] );
    m_muonSASuperPointRBME.push_back( SAparam[24] );
    m_muonSASuperPointZBI.push_back( SAparam[25] );
    m_muonSASuperPointZBM.push_back( SAparam[26] );
    m_muonSASuperPointZBO.push_back( SAparam[27] );
    m_muonSASuperPointZEI.push_back( SAparam[28] );
    m_muonSASuperPointZEM.push_back( SAparam[29] );
    m_muonSASuperPointZEO.push_back( SAparam[30] );
    m_muonSASuperPointZEE.push_back( SAparam[31] );
    m_muonSASuperPointZCSC.push_back( SAparam[22] );
    m_muonSASuperPointZBEE.push_back( SAparam[33] );
    m_muonSASuperPointZBME.push_back( SAparam[34] );
    m_muonSASuperPointSlopeBI.push_back( SAparam[35] );
    m_muonSASuperPointSlopeBM.push_back( SAparam[36] );
    m_muonSASuperPointSlopeBO.push_back( SAparam[37] );
    m_muonSASuperPointSlopeEI.push_back( SAparam[38] );
    m_muonSASuperPointSlopeEM.push_back( SAparam[39] );
    m_muonSASuperPointSlopeEO.push_back( SAparam[40] );
    m_muonSASuperPointSlopeEE.push_back( SAparam[41] );
    m_muonSASuperPointSlopeCSC.push_back( SAparam[42] );
    m_muonSASuperPointSlopeBEE.push_back( SAparam[43] );
    m_muonSASuperPointSlopeBME.push_back( SAparam[44] );
    m_muonSASuperPointInterceptBI.push_back( SAparam[45] );
    m_muonSASuperPointInterceptBM.push_back( SAparam[46] );
    m_muonSASuperPointInterceptBO.push_back( SAparam[47] );
    m_muonSASuperPointInterceptBI.push_back( SAparam[48] );
    m_muonSASuperPointInterceptBM.push_back( SAparam[49] );
    m_muonSASuperPointInterceptBO.push_back( SAparam[50] );
    m_muonSASuperPointInterceptEE.push_back( SAparam[51] );
    m_muonSASuperPointInterceptCSC.push_back( SAparam[52] );
    m_muonSASuperPointInterceptBEE.push_back( SAparam[53] );
    m_muonSASuperPointInterceptBME.push_back( SAparam[54] );
    m_muonSASuperPointChi2BI.push_back( SAparam[55] );
    m_muonSASuperPointChi2BM.push_back( SAparam[56] );
    m_muonSASuperPointChi2BO.push_back( SAparam[57] );
    m_muonSASuperPointChi2EI.push_back( SAparam[58] );
    m_muonSASuperPointChi2EM.push_back( SAparam[59] );
    m_muonSASuperPointChi2EO.push_back( SAparam[60] );
    m_muonSASuperPointChi2EE.push_back( SAparam[61] );
    m_muonSASuperPointChi2CSC.push_back( SAparam[62] );
    m_muonSASuperPointChi2BEE.push_back( SAparam[63] );
    m_muonSASuperPointChi2BME.push_back( SAparam[64] );
    m_muonSAroiEta.push_back( SAparam[65] );
    m_muonSAroiPhi.push_back( SAparam[66] );
    m_muonSAisrpcFailure.push_back( SAparam[67] );
    m_muonSAistgcFailure.push_back( SAparam[68] );
    m_muonSABarrelRadius.push_back( SAparam[69] );
    m_muonSABarrelSagitta.push_back( SAparam[70] );
    m_muonSAEtaMap.push_back( SAparam[71] );
    m_muonSAPhiMap.push_back( SAparam[72] );
    m_muonSAroiNumber.push_back( (uint32_t)SAparam[73] );
    m_muonSAroiSector.push_back( (uint32_t)SAparam[74] );
    //RPC
    m_vMuonSArpcHitX.push_back( vSArpcHitX );
    m_vMuonSArpcHitY.push_back( vSArpcHitY );
    m_vMuonSArpcHitZ.push_back( vSArpcHitZ );
    m_vMuonSArpcHitMeasuresPhi.push_back( vSArpcHitMeasuresPhi );
    m_muonSArpcFitInnPhi.push_back( SAparamrpcFit[0] );
    m_muonSArpcFitInnSlope.push_back( SAparamrpcFit[1] );
    m_muonSArpcFitInnOffset.push_back( SAparamrpcFit[2] );
    m_muonSArpcFitMidPhi.push_back( SAparamrpcFit[3] );
    m_muonSArpcFitMidSlope.push_back( SAparamrpcFit[4] );
    m_muonSArpcFitMidOffset.push_back( SAparamrpcFit[5] );
    m_muonSArpcFitOutPhi.push_back( SAparamrpcFit[6] );
    m_muonSArpcFitOutSlope.push_back( SAparamrpcFit[7] );
    m_muonSArpcFitOutOffset.push_back( SAparamrpcFit[8] );
    vector< int > tmp_int;
    vector< float > tmp_float;
    if( vSAparamRoad.size() == 8 ){
      m_vMuonSARoadAw.push_back( vSAparamRoad[0] );
      m_vMuonSARoadBw.push_back( vSAparamRoad[1] );
      m_vMuonSAZMin.push_back( vSAparamRoad[2] );
      m_vMuonSAZMax.push_back( vSAparamRoad[3] );
      m_vMuonSARMin.push_back( vSAparamRoad[4] );
      m_vMuonSARMax.push_back( vSAparamRoad[5] );
      m_vMuonSAEtaMin.push_back( vSAparamRoad[6] );
      m_vMuonSAEtaMax.push_back( vSAparamRoad[7] );
    }else {
      m_vMuonSARoadAw.push_back( tmp_float );
      m_vMuonSARoadBw.push_back( tmp_float );
      m_vMuonSAZMin.push_back(   tmp_float );
      m_vMuonSAZMax.push_back(   tmp_float );
      m_vMuonSARMin.push_back(   tmp_float );
      m_vMuonSARMax.push_back(   tmp_float );
      m_vMuonSAEtaMin.push_back( tmp_float );
      m_vMuonSAEtaMax.push_back( tmp_float );
    }
    //MDT
    if( vSAparammdtInt.size() == 2 ){
      m_vMuonSAmdtHitIsOutlier.push_back( vSAparammdtInt[0] );
      m_vMuonSAmdtHitChamber.push_back( vSAparammdtInt[0] );
      m_vMuonSAmdtHitR.push_back( vSAparammdtFloat[0] );
      m_vMuonSAmdtHitZ.push_back( vSAparammdtFloat[1] );
      m_vMuonSAmdtHitPhi.push_back( vSAparammdtFloat[2] );
      m_vMuonSAmdtHitResidual.push_back( vSAparammdtFloat[3] );
      m_vMuonSAmdtHitSpace.push_back( vSAparammdtFloat[4] );
      m_vMuonSAmdtHitSigma.push_back( vSAparammdtFloat[5] );
    } else{
      m_vMuonSAmdtHitIsOutlier.push_back( tmp_int );
      m_vMuonSAmdtHitChamber.push_back( tmp_int );
      m_vMuonSAmdtHitR.push_back( tmp_float );
      m_vMuonSAmdtHitZ.push_back( tmp_float );
      m_vMuonSAmdtHitPhi.push_back( tmp_float );
      m_vMuonSAmdtHitResidual.push_back( tmp_float );
      m_vMuonSAmdtHitSpace.push_back( tmp_float );
      m_vMuonSAmdtHitSigma.push_back( tmp_float );
    }

    //convert (X,Y,Z) to (R,Eta,Phi)
    std::vector< TVector3 > vSA3param;
    int vNSAparam = vSArpcHitX.size();
    for(int i_vSArpcHit = 0; i_vSArpcHit < vNSAparam; ++i_vSArpcHit ){
      TVector3 i_vSA3param( vSArpcHitX.at(i_vSArpcHit), vSArpcHitY.at(i_vSArpcHit), vSArpcHitZ.at(i_vSArpcHit) );
      vSArpcHitR.push_back( i_vSA3param.Perp() );
      vSArpcHitEta.push_back( i_vSA3param.Eta() );
      vSArpcHitPhi.push_back( i_vSA3param.Phi() );
    }
    m_vMuonSArpcHitR.push_back( vSArpcHitR );
    m_vMuonSArpcHitEta.push_back( vSArpcHitEta );
    m_vMuonSArpcHitPhi.push_back( vSArpcHitPhi );
    m_vMuonSArpcHitStationName.push_back( vSAparamString );
    int n_name = vSAparamString.size();
    for( int i_name = 0; i_name < n_name; ++i_name ){
      if( vSAparamString.at(i_name) == "BML" ){//BML: Barrel Middle Large
        vSArpcHitStationNumber.push_back(1.);
      }else if( vSAparamString.at(i_name) == "BMS" ){// BMS: Barrel Middle Small
        vSArpcHitStationNumber.push_back(2.);
      }else if( vSAparamString.at(i_name) == "BMF" ){//BMF: Barrel Middle Feet
        vSArpcHitStationNumber.push_back(3.);
      }else if( vSAparamString.at(i_name) == "BME" ){//BME: Barrel Middle Extra
        vSArpcHitStationNumber.push_back(4.);
      }else if( vSAparamString.at(i_name) == "BOL" ){//BOL: BarrelOuter Large
        vSArpcHitStationNumber.push_back(5.);
      }else if( vSAparamString.at(i_name) == "BOS" ){//BOS: Barrel Outer Small
        vSArpcHitStationNumber.push_back(6.);
      }else if( vSAparamString.at(i_name) == "BOF" ){//BOF: Barrel Outer Feet
        vSArpcHitStationNumber.push_back(7.);
      }else if( vSAparamString.at(i_name) == "BOE" ){//BOE: Barrel Outer Extra
        vSArpcHitStationNumber.push_back(8.);
      }else if( vSAparamString.at(i_name) == "BOG" ){//BOG: Barrel Outer Ground?
        vSArpcHitStationNumber.push_back(9.);
      }else{                                         //Unknown
        vSArpcHitStationNumber.push_back(10.);
      }
    }
    m_vMuonSArpcHitStationNumber.push_back( vSArpcHitStationNumber );
    //CB
    m_muonCBHypoPass.push_back( CBHypopass );
    m_muonCBOvRmPass.push_back( CBOvRmpass );
    m_muonCBPt.push_back( CBparam[0] * 0.001 );
    m_muonCBEta.push_back( CBparam[1] );
    m_muonCBPhi.push_back( CBparam[2] );
    //m_muonCBEtaMS.push_back( CBparam[4] );
    //m_muonCBPhiMS.push_back( CBparam[5] );
    //EF
    m_muonEFPass.push_back( EFpass );
    m_muonEFPt.push_back( EFparam[0] * 0.001 );
    m_muonEFEta.push_back( EFparam[1] );
    m_muonEFPhi.push_back( EFparam[2] );
  }//muon loop

  int muonSize = (int)m_muonSAHypoPass.size();
  //SA Hypo check
  for( int muon = 0; muon < muonSize; ++muon ){
    int SAWeakRegion = ECWeakRegion( m_muonSAEta.at(muon), m_muonSAPhi.at(muon) );
    int SAEtaRegion = EtaRegion( m_muonSAEta.at(muon) );
    bool SAHypopass = SAHypo( m_muonSAPt.at(muon) , SAEtaRegion, SAWeakRegion );
    m_muonSAHypoPass.at(muon) = SAHypopass;
    m_muonSAOvRmPass.at(muon) = SAHypopass;
  }
  //SA OvRm check
  if( muonSize >= 2 ){
    for( int Fmuon = 0; Fmuon < muonSize -1; ++Fmuon){
      for( int Smuon = Fmuon + 1; Smuon < muonSize; ++Smuon){
        if( m_muonSAOvRmPass.at(Fmuon) && m_muonSAOvRmPass.at(Smuon) )m_muonSAOvRmPass.at(Smuon) = OvRmCut( m_muonSAPt.at(Fmuon), m_muonSAPt.at(Smuon), m_muonSAEtaMS.at(Fmuon), m_muonSAEtaMS.at(Smuon), m_muonSAPhiMS.at(Fmuon), m_muonSAPhiMS.at(Smuon) );
      }
    }
  }
  //CB Hypo check
  for( int muon = 0; muon < muonSize; ++muon){
    m_muonCBHypoPass.at(muon) = m_muonSAOvRmPass.at(muon);
    int CBEtaRegion = EtaRegion( m_muonCBEta.at(muon) );
    if(m_muonCBHypoPass.at(muon))m_muonCBHypoPass.at(muon) = CBHypo( m_muonCBPt.at(muon), CBEtaRegion );
    m_muonCBOvRmPass.at(muon) = m_muonCBHypoPass.at(muon);
  }
  //CB OvRm check
  if( muonSize >= 2){
    for( int Fmuon = 0; Fmuon < muonSize -1; ++Fmuon){
      for( int Smuon = Fmuon + 1; Smuon < muonSize; ++Smuon){
        if( m_muonCBOvRmPass.at(Fmuon) && m_muonCBOvRmPass.at(Smuon) )m_muonCBOvRmPass.at(Smuon) = OvRmCut( m_muonCBPt.at(Fmuon)*1000., m_muonCBPt.at(Smuon)*1000., m_muonCBEta.at(Fmuon), m_muonCBEta.at(Smuon), m_muonCBPhi.at(Fmuon), m_muonCBPhi.at(Smuon), m_muonSAEtaMS.at(Fmuon), m_muonSAEtaMS.at(Smuon), m_muonSAPhiMS.at(Fmuon), m_muonSAPhiMS.at(Smuon) );
      }
    }
  }

  return Nquality;
}

int MuInfoGetter::matchL1( const L1Item& L1, const xAOD::Muon* muon, const xAOD::MuonRoIContainer* rois, const double* reqdR,  double* param) {//kayamash
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
    const int roiThr      = (*rois_itr)->getThrNumber();
    const int roiPt       = (*rois_itr)->thrValue();
    const double roiEta   = (*rois_itr)->eta();
    const double roiPhi   = (*rois_itr)->phi();
    int roiSector   = (*rois_itr)->getSectorAddress();//kayamash
    if( L1 > roiThr ) continue;
    const double roidRof  = m_utils.deltaR( muEta, muPhi, roiEta, roiPhi);
    const double roidRex  = m_utils.deltaR( muExtEta, muExtPhi, roiEta, roiPhi);
    //cout << "DR: " << roidRof << ":" << roidRex << endl;
    if( m_message>1 ) cout << "L1 : " << muPt << ", " << roiThr << endl;
    bool pass = ( m_useExt )? ( *reqdR > roidRex ):( *reqdR > roidRof );
    if( pass ) {
      matchedRoINumber  = roiNum;
      param[0]  = roiPt;
      param[1]  = roiEta;
      param[2]  = roiPhi;
      param[3]  = matchedRoINumber;//
      int tmp_roiSector = roiSector >> 1;//
      (roiSector >= 64) ? (roiSector = tmp_roiSector & 0x3f) : (roiSector = tmp_roiSector & 0x1f);//
      param[4]  = roiSector;//
    }
  }
  return matchedRoINumber;
}

bool MuInfoGetter::matchSA( const Trig::FeatureContainer& fc, int L1num, double* param, std::vector< float >& vec_param_X, std::vector< float >& vec_param_Y, std::vector< float >& vec_param_Z, std::vector< uint32_t >& vec_param_mesPhi, float* param_rpcFit, std::vector< string >& vec_param_string, std::string& mesSATEName, std::vector< std::vector < float> >& vec_param_road, vector < vector < int > >& vec_param_mdtInt, vector < vector < float > >& vec_param_mdtFloat, double* l1param)//kayamash
{
  ///this function is used for SA matching.
  bool isPassedSA = kFALSE;
  //auto fL2SAs = fc.containerFeature<xAOD::L2StandAloneMuonContainer>( "", TrigDefs::alsoDeactivateTEs );
  const std::vector< Trig::Feature<xAOD::L2StandAloneMuonContainer> > fL2SAs = fc.get<xAOD::L2StandAloneMuonContainer>( "", TrigDefs::alsoDeactivateTEs );
  // L2muonSA matching

  if ( dataType == "data17" ){
    Trig::ExpertMethods* expert = m_trigDecTool -> ExperimentalAndExpertMethods();
    expert->enable();
    int tmp_count = 0;
    for(auto fL2SA : fL2SAs){
      const HLT::TriggerElement *trigElement1 = fL2SA.te();
      std::vector<HLT::TriggerElement*> TEsuccessors = expert->getNavigation()->getDirectSuccessors(trigElement1);
      Bool_t isActiveTE = kFALSE;
      for(auto te2 : TEsuccessors){
        if ( te2 -> getActiveState() ){
          TString teName = Trig::getTEName( *te2 );
          cout << " in matchSA, teName : " << teName << endl;
          if ( (teName.Contains( "L2_mu_SAhyp") && teName.Contains( mesSATEName.c_str() ) ) )
            isActiveTE = kTRUE;
        }
        //check active state of te2, and match name to threshold to be sure it is from the right chain
      }
      const xAOD::L2StandAloneMuonContainer* cont = fL2SA.cptr();
      for( const auto& l2sa : *cont ) {
        tmp_count++;
        const int l2saRoINum  = l2sa->roiNumber();
        const int l2saSecNum = l2sa->roiSector();//kayamash
        const int l1RoISectorAddress = (int)l1param[4];//kayamash
        cout << "matchSA muon loop " << L1num << " " << l1RoISectorAddress << endl;
        if( l2saRoINum != L1num || l1RoISectorAddress != l2saSecNum) continue;
        //if( isActiveTE ) isPassedSA = kTRUE;
        pair< double, double > extsa = m_ext.extTrackMuComb( l2sa );
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
        //tsakai insert
        const double l2saBarrelRadius  = l2sa->barrelRadius();
        const double l2saBarrelSagitta  = l2sa->barrelSagitta();

        const double l2saetamap  = l2sa->etaMap();
        const double l2saphimap  = l2sa->phiMap();
        //tsakai end
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
        //ktaniguc insert
        const std::vector < uint32_t > l2saRpcHitMeasuresPhi = l2sa->rpcHitMeasuresPhi();
        const float l2saRpcFitInnPhi = l2sa->rpcFitInnPhi();
        const float l2saRpcFitInnSlope = l2sa->rpcFitInnSlope();
        const float l2saRpcFitInnOffset = l2sa->rpcFitInnOffset();
        const float l2saRpcFitMidPhi = l2sa->rpcFitMidPhi();
        const float l2saRpcFitMidSlope = l2sa->rpcFitMidSlope();
        const float l2saRpcFitMidOffset = l2sa->rpcFitMidOffset();
        const float l2saRpcFitOutPhi = l2sa->rpcFitOutPhi();
        const float l2saRpcFitOutSlope = l2sa->rpcFitOutSlope();
        const float l2saRpcFitOutOffset = l2sa->rpcFitOutOffset();
        //ktaniguc end
        vector < int > l2samdtHitIsOutlier, l2samdtHitChamber;
        vector < float > l2samdtHitR, l2samdtHitZ, l2samdtHitPhi, l2samdtHitResidual,l2samdtHitSpace, l2samdtHitSigma;
        for ( uint32_t i =0; i < l2sa->nMdtHits(); i++){
          l2samdtHitIsOutlier.push_back(l2sa->mdtHitIsOutlier(i));
          l2samdtHitChamber.push_back(l2sa->mdtHitChamber(i));
          l2samdtHitR.push_back(l2sa->mdtHitR(i));
          l2samdtHitZ.push_back(l2sa->mdtHitZ(i));
          l2samdtHitPhi.push_back(l2sa->mdtHitPhi(i));
          l2samdtHitResidual.push_back(l2sa->mdtHitResidual(i));
          //tsakai insert
          l2samdtHitSpace.push_back(l2sa->mdtHitSpace(i));
          l2samdtHitSigma.push_back(l2sa->mdtHitSigma(i));
          //tsakai end
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
        //tsakai insert
        param[69]   = l2saBarrelRadius;
        param[70]   = l2saBarrelSagitta;

        param[71]   = l2saetamap;
        param[72]   = l2saphimap;
        //tsakai end
        //kayamash insert
        param[73]   = l2saRoINum;
        param[74]   = l2saSecNum;
        //kayamash end

        //vec_param is vector < vector < float > >. l2saRpcHitX is vector < float >.
        vec_param_X = l2saRpcHitX;
        vec_param_Y = l2saRpcHitY;
        vec_param_Z = l2saRpcHitZ;
        vec_param_string = l2saRpcHitStationName;
        //ktaniguc insert
        vec_param_mesPhi = l2saRpcHitMeasuresPhi;
        param_rpcFit[0] = l2saRpcFitInnPhi;
        param_rpcFit[1] = l2saRpcFitInnSlope;
        param_rpcFit[2] = l2saRpcFitInnOffset;
        param_rpcFit[3] = l2saRpcFitMidPhi;
        param_rpcFit[4] = l2saRpcFitMidSlope;
        param_rpcFit[5] = l2saRpcFitMidOffset;
        param_rpcFit[6] = l2saRpcFitOutPhi;
        param_rpcFit[7] = l2saRpcFitOutSlope;
        param_rpcFit[8] = l2saRpcFitOutOffset;
        //ktaniguc end
        vec_param_mdtInt.push_back(l2samdtHitIsOutlier);
        vec_param_mdtInt.push_back(l2samdtHitChamber);
        vec_param_mdtFloat.push_back(l2samdtHitR);
        vec_param_mdtFloat.push_back(l2samdtHitZ);
        vec_param_mdtFloat.push_back(l2samdtHitPhi);
        vec_param_mdtFloat.push_back(l2samdtHitResidual);
        //tsakai insert
        vec_param_mdtFloat.push_back(l2samdtHitSpace);
        vec_param_mdtFloat.push_back(l2samdtHitSigma);
        //tsakai end

        vec_param_road.push_back(l2saroadAw);
        vec_param_road.push_back(l2saroadBw);
        vec_param_road.push_back(l2sazMin);
        vec_param_road.push_back(l2sazMax);
        vec_param_road.push_back(l2sarMin);
        vec_param_road.push_back(l2sarMax);
        vec_param_road.push_back(l2saetaMin);
        vec_param_road.push_back(l2saetaMax);
        if( isActiveTE ){
          isPassedSA = kTRUE;
          goto RoIMatchingAndSAPassed;
        } else {
          isPassedSA = kFALSE;
        }
      }
    }
  } else { //// before r9353

    for ( auto& fL2SA : fL2SAs ) {
      const HLT::TriggerElement* l2saTE = ( fL2SA.te() );
      const xAOD::L2StandAloneMuonContainer* cont = fL2SA.cptr();
      for( const auto& l2sa : *cont ) {
        const int l2saRoINum  = l2sa->roiNumber();
        if( l2saRoINum != L1num ) continue; 
        pair< double, double > extsa = m_ext.extTrackMuComb( l2sa );
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
        //tsakai insert
        const double l2saBarrelRadius  = l2sa->barrelRadius();
        const double l2saBarrelSagitta  = l2sa->barrelSagitta();

        const double l2saetamap  = l2sa->etaMap();
        const double l2saphimap  = l2sa->phiMap();
        //tsakai end
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
        //ktaniguc insert
        const std::vector < uint32_t > l2saRpcHitMeasuresPhi = l2sa->rpcHitMeasuresPhi();
        const float l2saRpcFitInnPhi = l2sa->rpcFitInnPhi();
        const float l2saRpcFitInnSlope = l2sa->rpcFitInnSlope();
        const float l2saRpcFitInnOffset = l2sa->rpcFitInnOffset();
        const float l2saRpcFitMidPhi = l2sa->rpcFitMidPhi();
        const float l2saRpcFitMidSlope = l2sa->rpcFitMidSlope();
        const float l2saRpcFitMidOffset = l2sa->rpcFitMidOffset();
        const float l2saRpcFitOutPhi = l2sa->rpcFitOutPhi();
        const float l2saRpcFitOutSlope = l2sa->rpcFitOutSlope();
        const float l2saRpcFitOutOffset = l2sa->rpcFitOutOffset();
        //ktaniguc end

        vector < int > l2samdtHitIsOutlier, l2samdtHitChamber;
        vector < float > l2samdtHitR, l2samdtHitZ, l2samdtHitPhi, l2samdtHitResidual,l2samdtHitSpace,l2samdtHitSigma;
        for ( uint32_t i =0; i < l2sa->nMdtHits(); i++){
          l2samdtHitIsOutlier.push_back(l2sa->mdtHitIsOutlier(i));
          l2samdtHitChamber.push_back(l2sa->mdtHitChamber(i));
          l2samdtHitR.push_back(l2sa->mdtHitR(i));
          l2samdtHitZ.push_back(l2sa->mdtHitZ(i));
          l2samdtHitPhi.push_back(l2sa->mdtHitPhi(i));
          l2samdtHitResidual.push_back(l2sa->mdtHitResidual(i));
          //tsakai insert
          l2samdtHitSpace.push_back(l2sa->mdtHitSpace(i));
          l2samdtHitSigma.push_back(l2sa->mdtHitSigma(i));
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
          //tsakai end
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
        //tsakai insert
        param[69]  = l2saBarrelRadius;
        param[70]  = l2saBarrelSagitta;

        param[71]  = l2saetamap;
        param[72]  = l2saphimap;
        //tsakai end
        // vec_param is vector < vector < float > >. l2saRpcHitX is vector < float >.
        vec_param_X = l2saRpcHitX;
        vec_param_Y = l2saRpcHitY;
        vec_param_Z = l2saRpcHitZ;
        vec_param_string = l2saRpcHitStationName;
        //tsakai insert
        //ktaniguc insert
        vec_param_mesPhi = l2saRpcHitMeasuresPhi;
        param_rpcFit[0] = l2saRpcFitInnPhi;
        param_rpcFit[1] = l2saRpcFitInnSlope;
        param_rpcFit[2] = l2saRpcFitInnOffset;
        param_rpcFit[3] = l2saRpcFitMidPhi;
        param_rpcFit[4] = l2saRpcFitMidSlope;
        param_rpcFit[5] = l2saRpcFitMidOffset;
        param_rpcFit[6] = l2saRpcFitOutPhi;
        param_rpcFit[7] = l2saRpcFitOutSlope;
        param_rpcFit[8] = l2saRpcFitOutOffset;
        //ktaniguc end

        vec_param_mdtInt.push_back(l2samdtHitIsOutlier);
        vec_param_mdtInt.push_back(l2samdtHitChamber);
        vec_param_mdtFloat.push_back(l2samdtHitR);
        vec_param_mdtFloat.push_back(l2samdtHitZ);
        vec_param_mdtFloat.push_back(l2samdtHitPhi);
        vec_param_mdtFloat.push_back(l2samdtHitResidual);
        vec_param_mdtFloat.push_back(l2samdtHitSpace);
        vec_param_mdtFloat.push_back(l2samdtHitSigma);

        vec_param_road.push_back(l2saroadAw);
        vec_param_road.push_back(l2saroadBw);
        vec_param_road.push_back(l2sazMin);
        vec_param_road.push_back(l2sazMax);
        vec_param_road.push_back(l2sarMin);
        vec_param_road.push_back(l2sarMax);
        vec_param_road.push_back(l2saetaMin);
        vec_param_road.push_back(l2saetaMax);
        //tsakai end 
        if( l2saTE->getActiveState() ) {
          isPassedSA = kTRUE;
          goto RoIMatchingAndSAPassed;
        } else {
          isPassedSA = kFALSE;
        }
      }
    }
  }
RoIMatchingAndSAPassed:
  return isPassedSA;
}

bool MuInfoGetter::matchCB( const Trig::FeatureContainer& fc, int L1num, double* param, std::string& cbTEName ) 
{
  bool isPassedCB = kFALSE;
  TString tsCBTEName = cbTEName.c_str();
  //auto fL2CBs = fc.containerFeature<xAOD::L2CombinedMuonContainer>( "", TrigDefs::alsoDeactivateTEs );
  Trig::ExpertMethods* expert = m_trigDecTool -> ExperimentalAndExpertMethods();
  expert->enable();
  const std::vector< Trig::Feature<xAOD::L2CombinedMuonContainer> > fL2CBs = fc.get<xAOD::L2CombinedMuonContainer>( "", TrigDefs::alsoDeactivateTEs );
  // L2muComb matching
  int tmp_count = 0;
  for ( auto& fL2CB : fL2CBs ) {
    const HLT::TriggerElement* trigElement1 = ( fL2CB.te() );
    const xAOD::L2CombinedMuonContainer* cont = fL2CB.cptr();
    std::vector<HLT::TriggerElement*> TEsuccessors = expert->getNavigation()->getDirectSuccessors(trigElement1);
    Bool_t isActiveTE = kFALSE;
    for(auto te2 : TEsuccessors){
      if ( te2 -> getActiveState() ){
        TString teName = Trig::getTEName( *te2 );
        if ( ( teName.Contains( "L2_mucombhyp") && teName.Contains( tsCBTEName.Data() ) ) || teName.Contains( "L2_mu_hypo2" ) )
          isActiveTE = kTRUE;
      }
    }
    for( const auto& l2cb : *cont ) {
      tmp_count++;
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
  cout << "L2CB count : " << tmp_count << endl;
  return isPassedCB;
}

bool MuInfoGetter::matchCB( const xAOD::Muon* muon, const Trig::FeatureContainer& fc, double* reqdR, double* param, std::string& cbTEName ) {
  TString tsCBTEName = cbTEName.c_str();
  cout << "call matchCB " << endl;
  bool isPassedCB = kFALSE;
  const double muPt   = muon->pt();
  const double muEta  = muon->eta();
  const double muPhi  = muon->phi();
  //auto fL2CBs = fc.containerFeature<xAOD::L2CombinedMuonContainer>( "", TrigDefs::alsoDeactivateTEs );
  Trig::ExpertMethods* expert = m_trigDecTool -> ExperimentalAndExpertMethods();
  expert->enable();
  const std::vector< Trig::Feature<xAOD::L2CombinedMuonContainer> > fL2CBs = fc.get<xAOD::L2CombinedMuonContainer>( "", TrigDefs::alsoDeactivateTEs );
  int tmp_count = 0;
  for ( auto& fL2CB : fL2CBs ) {
    const HLT::TriggerElement* trigElement1 = ( fL2CB.te() );
    const xAOD::L2CombinedMuonContainer* cont = fL2CB.cptr();
    std::vector<HLT::TriggerElement*> TEsuccessors = expert->getNavigation()->getDirectSuccessors(trigElement1);
    Bool_t isActiveTE = kFALSE;
    for(auto te2 : TEsuccessors){
      if ( te2 -> getActiveState() ){
        TString teName = Trig::getTEName( *te2 );
        cout << "matchCB teName : " << teName << endl;
        if ( ( teName.Contains( "L2_mucombhyp") && teName.Contains( tsCBTEName.Data() ) ) )
          isActiveTE = kTRUE;
      }
    }

    for( const auto& l2cb : *cont ) {
      tmp_count++;
      const xAOD::L2StandAloneMuon* mf = l2cb->muSATrack();
      //const double l2cbEtaMS = mf->etaMS();
      //const double l2cbPhiMS = mf->phiMS();
      const double l2cbPt   = l2cb->pt();
      const double l2cbEta  = l2cb->eta();
      const double l2cbPhi  = l2cb->phi();
      const double l2cbCharge = l2cb->charge();
      const double l2cbdRmu = m_utils.deltaR( muEta, muPhi, l2cbEta, l2cbPhi);
      bool pass = ( *reqdR > l2cbdRmu );
      if ( !pass ) continue;
      if( isActiveTE ) isPassedCB = kTRUE;
      if ( dataType == "data17" ){
        if ( isActiveTE ){
          *reqdR    = l2cbdRmu;
          param[0]  = l2cbPt;
          param[1]  = l2cbEta;
          param[2]  = l2cbPhi;
          param[3]  = l2cbCharge;
          //param[4]  = l2cbEtaMS;
          //param[5]  = l2cbPhiMS;
        }
      } else {
        //        if ( trigElement1 -> getActiveState() ){
        *reqdR    = l2cbdRmu;
        param[0]  = l2cbPt;
        param[1]  = l2cbEta;
        param[2]  = l2cbPhi;
        param[3]  = l2cbCharge;
        //        }
      }
    }
  }
  cout << "CB : " << muPt << ":" << muEta << ":" << muPhi << ", " << param[0] << ":" << param[1] << ":" << param[2] << ", " << isPassedCB << endl;
  cout << "L2CB count : " << tmp_count << endl;
  return isPassedCB;
}

int MuInfoGetter::matchEF( const string& chain, const xAOD::Muon* muon, const Trig::FeatureContainer& fc, double* reqdR, double* param ) {
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
  return isPassedEF;
}

int MuInfoGetter::matchEFFS( const string& chain, const xAOD::Muon* muon, const Trig::FeatureContainer& fc, double* reqdR, double* param, double* tagparam ) {
  int isPassedEF = -1;
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
  return isPassedEF;
}

double MuInfoGetter::dRL1byPt( double mupt ) {
  double dR = 0.08;
  if( mupt < 10000. ) {
    dR = -0.00001*mupt + 0.18;
  }
  return dR;
}


///Functions below here is used for "int TagAndProbe::addMesChain( const string& name, const L1Item& mesL1, const string& mesHLT, const string& mesAddTag )".
///
Bool_t MuInfoGetter::getSATEName( const std::string& mesHLT, std::string& teName )
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

Bool_t MuInfoGetter::getSATEName( const char* mesHLT, std::string& teName )
{
  std::string s_mesHLT = mesHLT;
  return getSATEName( s_mesHLT, teName );
}

Bool_t MuInfoGetter::getCBTEName( const std::string& mesHLT, std::string& teName )
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

Bool_t MuInfoGetter::getCBTEName( const char* mesHLT, std::string& teName )
{
  ///THis fuction is similar to TagAndProbe::getCBTEName( const std::string& mesHLT, std::string& teName ).
  ///const char* mesHLT --->>> const std::string&.
  std::string s_mesHLT = mesHLT;
  return getCBTEName( s_mesHLT, teName );
}

bool MuInfoGetter::SAHypo( double pt, int EtaRegion, int ECWeakRegion)
{
  cout << "call SAHypo" << endl;
  bool pass = kFALSE;
  double threshold = 0;
  if( ECWeakRegion == 0 ){
    threshold = m_SAThresholds[EtaRegion];
  } else {
    threshold = m_SAWeakThresholds[ECWeakRegion];
  }
  if( pt != -99999. && fabs(pt) > threshold ) pass = kTRUE;
  return pass;
}


bool MuInfoGetter::CBHypo( double pt, int EtaRegion)
{
  cout << "call CBHypo" << endl;
  bool pass = kFALSE;
  double threshold = 0;
  threshold = m_CBThresholds[EtaRegion];
  if( pt != -99.999 && fabs( pt ) > threshold ) pass = kTRUE;
  return pass;
}

int MuInfoGetter::EtaRegion( double eta )
{
  int region = -1;
  if( fabs(eta) < 1.05 ){
    region = 0;
  } else if( fabs(eta) < 1.5 ){
    region = 1;
  } else if( fabs(eta) < 2.0 ){
    region = 2;
  } else {
    region = 3;
  }
  return region;
}

int MuInfoGetter::ECWeakRegion( double eta, double phi )
{
  int region = 0;
  double absEta = fabs( eta );
  double absPhi = fabs( phi );
  if(  ( 1.3 <= absEta && absEta < 1.45) &&
      ( (0  <= absPhi && absPhi < TMath::Pi()/48. )     ||
        (TMath::Pi()*11./48. <= absPhi && absPhi < TMath::Pi()*13./48. ) ||
        (TMath::Pi()*23./48. <= absPhi && absPhi < TMath::Pi()*25./48. ) ||
        (TMath::Pi()*35./48. <= absPhi && absPhi < TMath::Pi()*37./48. ) ||
        (TMath::Pi()*47./48. <= absPhi && absPhi < TMath::Pi() )
      )
    ) region = 1;
  else if( ( 1.5 <= absEta && absEta < 1.65 ) &&
      ( (TMath::Pi()*3./32.  <= absPhi && absPhi < TMath::Pi()*5./32. ) ||
        (TMath::Pi()*11./32. <= absPhi && absPhi < TMath::Pi()*13./32.) ||
        (TMath::Pi()*19./32. <= absPhi && absPhi < TMath::Pi()*21./32.) ||
        (TMath::Pi()*27./32. <= absPhi && absPhi < TMath::Pi()*29./32.)
      )
      ) region = 2;
  return region;
}

double MuInfoGetter::CalcdR( const double& eta1, const double& eta2, const double& phi1, const double& phi2 ){
  double deta = eta1 - eta2;
  double dphi = fabs( phi1 - phi2 );
  if( dphi > TMath::Pi() ) dphi = 2.*TMath::Pi() - dphi;
  double dR = pow( ( deta*deta + dphi*dphi ), 0.5 );
  return dR;
}

double MuInfoGetter::CalcInvMass( const double& pt1, const double& pt2, const double& eta1, const double& eta2, const double& phi1, const double& phi2, const double& m1, const double& m2 ){
  const double ZERO_LIMIT = 1e-12;
  double theta1 = 2.*atan2( (double)exp(-eta1),1.);
  double theta2 = 2.*atan2( (double)exp(-eta2),1.);
  //muon 1
  double fpt1   = fabs(pt1);
  double px1    = fpt1*cos(phi1);
  double py1    = fpt1*sin(phi1);
  double pz1    = fpt1/tan(theta1);
  double e1     = sqrt( px1*px1+py1*py1*pz1*pz1+m1*m1 );

  //muon 2
  double fpt2   = fabs(pt2);
  double px2    = fpt2*cos(phi2);
  double py2    = fpt2*sin(phi2);
  double pz2    = fpt2/tan(theta2);
  double e2     = sqrt( px2*px2+py2*py2*pz2*pz2+m2*m2 );

  double pxsum = px1 + px2;
  double pysum = py1 + py2;
  double pzsum = pz1 + pz2;
  double esum  = e1  + e2;

  double mass = 0;
  double mass2 = esum*esum - pxsum*pxsum - pysum*pysum - pzsum*pzsum;
  if( mass2 > ZERO_LIMIT ) mass = sqrt( mass2 );
  return mass;
}

bool MuInfoGetter::OvRmCut( const double& pt1, const double& pt2, const double& etaMS1, const double& etaMS2, const double& phiMS1, const double& phiMS2 ){
  cout << "call SA OvRmCut" << endl;
  const double MassThr = 1e-3;
  const double dRThr   = 1e-3;
  const double MASS    = 0;
  bool cut = kTRUE;//true : unique TE, false : overlap TE

  double mass = 0;
  mass = CalcInvMass( pt1, pt2, etaMS1, etaMS2, phiMS1, phiMS2, MASS, MASS);
  double dR   = 0;
  dR   = CalcdR( etaMS1, etaMS2, phiMS1, phiMS2 );

  //OvRm cut
  //dR cut
  bool dRpass = ( dR > dRThr )? kTRUE : kFALSE;
  //mass cut
  bool masspass = ( mass > MassThr )? kTRUE : kFALSE;
  //same sign cut
  bool chargepass = ( pt1*pt2 < 0 ) ? kTRUE : kFALSE;

  //total judge
  if( !dRpass && !masspass && !chargepass ) cut = kFALSE;

  return cut;
}

bool MuInfoGetter::OvRmCut( const double& pt1, const double& pt2, const double& eta1, const double& eta2, const double& phi1, const double& phi2, const double& etaMS1, const double& etaMS2, const double& phiMS1, const double& phiMS2 ){
  cout << "call CB OvRmCut" << endl;
  const double MassThr = 1e-3;
  const double dRThr   = 1e-3;
  const double dRmfThr = 0;
  const double MASS    = 0;
  bool cut = kTRUE;//true : unique TE, false : overlap TE

  double mass = 0;
  mass = CalcInvMass( pt1, pt2, eta1, eta2, phi1, phi2, MASS, MASS);
  double dR   = 0;
  dR   = CalcdR( eta1, eta2, phi1, phi2 );
  double dRmf = 0;
  dRmf = CalcdR( etaMS1, etaMS2, phiMS1, phiMS2 );

  //OvRm cut
  //dR cut
  bool dRpass = ( dR > dRThr )? kTRUE : kFALSE;
  //dR MF cut
  bool dRmfpass = ( dRmf > dRmfThr )? kTRUE : kFALSE;
  //mass cut
  bool masspass = ( mass > MassThr )? kTRUE : kFALSE;
  //same sign cut
  bool chargepass = ( pt1*pt2 < 0 ) ? kTRUE : kFALSE;

  //total judge
  if( !dRpass && !dRmfpass && !masspass && !chargepass ) cut = kFALSE;

  return cut;
}

