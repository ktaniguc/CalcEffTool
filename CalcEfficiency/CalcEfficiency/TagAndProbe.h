#ifndef _INC_TAGANDPROBE
#define _INC_TAGANDPROBE

// stdlib
#include <iostream>
#include <fstream>
#include <vector>

// ASG Tools
#include "AsgTools/AsgToolsConf.h"
#include "AsgTools/AsgMetadataTool.h"
#include "AsgTools/AsgTool.h"
#include "AsgTools/ToolHandle.h"

// xAOD
#include "TrkExInterfaces/IExtrapolator.h"
#include "TrkVertexFitterInterfaces/IVertexFitter.h"
#include "TrigDecisionTool/TrigDecisionTool.h"
#include "xAODMuon/MuonContainer.h"
#include "xAODMuon/MuonSegmentContainer.h"
#include "xAODTracking/TrackParticleContainer.h"
#include "xAODTrigMuon/L2StandAloneMuon.h"
#include "xAODTrigMuon/L2StandAloneMuonContainer.h"
#include "xAODTrigMuon/L2CombinedMuon.h"
#include "xAODTrigMuon/L2CombinedMuonContainer.h"
#include "xAODTrigger/MuonRoIContainer.h"

// my classes
#include "CalcEfficiency/ParticleSelecterTool.h"
#include "CalcEfficiency/MuonExtUtils.h"
#include "CalcEfficiency/VrtFitUtils.h"
#include "CalcEfficiency/Utils.h"

using namespace std;

class TagAndProbe {
	
	public:
	TagAndProbe();
	~TagAndProbe();
    
    enum L1Item{ NOTHING, L1_MU4, L1_MU6, L1_MU10, L1_MU11, L1_MU20, L1_MU21 };
    //enum L1Item{ NOTHING, L1_MU4, L1_MU6, L1_MU10, L1_MU11, L1_MU15, L1_MU20 };
    enum TapType{ L1, L2, EF, ALL };
    

    int initialize( const int& message, 
                    const bool& useExt,
                    const std::string method,
                    MuonExtUtils ext,
                    VrtFitUtils vft,
                    ToolHandle<Trig::TrigDecisionTool> tdt,
                    const std::string dataType ); //!
    int addMesChain( const string& name, const L1Item& mesL1, const string& mesHLT, const string& mesAddTag ); //!
    void clear( ); //!
    int eventTriggerDecision( const vector< string >& passedtriggers ); //!
    int setProbes( const xAOD::MuonContainer* muons, 
                   const xAOD::MuonRoIContainer* rois ); //!
    int doProbeMatching( const xAOD::MuonRoIContainer* rois, const xAOD::TrackParticleContainer* ftfs ); //!

    int matchL1( const L1Item& L1, const xAOD::Muon* muon, const xAOD::MuonRoIContainer* rois, double* reqdR, int reject, double* param ); //!
    int matchSA( const Trig::FeatureContainer& fc, double* L1param, double* param, std::vector < float >& vec_param_x, std::vector < float >& vec_param_Y, std::vector < float >& vec_param_Z, std::vector< string >& vec_param_string, std::string& mesSATEName, std::vector< std::vector < float > >& vec_param_road, vector < vector < int > >& vec_param_mdtInt, vector < vector < float > >& vec_param_mdtFloat ); //!
    //int matchCB( const Trig::FeatureContainer& fc, int L1num, double* param ); //!
    //int matchCB( const xAOD::Muon* muon, const Trig::FeatureContainer& fc, double* reqdR, double* param ); //!
    int matchCB( const xAOD::Muon* muon, const Trig::FeatureContainer& fc, double* reqdR, double* param, std::string& cbTEName );
    int matchCB( const Trig::FeatureContainer& fc, int L1num, double* param, std::string& cbTEName ) ;
    int matchFTF( const xAOD::Muon* muon, const xAOD::TrackParticleContainer* ftf, double* reqdR, double* param ); //!
    int matchFTF( const xAOD::Muon* muon, const Trig::FeatureContainer& fc, double* reqdR, double* param ); //!
    int matchEF( const string& chain, const xAOD::Muon* muon, const Trig::FeatureContainer& fc, double* reqdR, double* param ); //!
    int matchEFFS( const string& chain, const xAOD::Muon* muon, const Trig::FeatureContainer& fc, double* reqdR, double* param, double* tagparam ); //!
    double dRL1byPt( double mupt ); //!
    Bool_t getSATEName( const std::string& mesHLT, std::string& teName );
    Bool_t getSATEName( const char* mesHLT, std::string& teName );
    Bool_t getCBTEName( const std::string& mesHLT, std::string& teName );
    Bool_t getCBTEName( const char* mesHLT, std::string& teName );
   
    int NMes(){ return m_trigNMes; }
    vector< string > mesName(){ return m_trigMesName; }
    vector< int > tagProc(){ return m_tagProc; }
    vector< double > tpSumReqL1dR(){ return m_tpSumReqL1dR; }
    vector< double > tpSumReqEFdR(){ return m_tpSumReqEFdR; }
    vector< double > tagL1dR(){ return m_tagL1dR; }
    vector< double > tagEFdR(){ return m_tagEFdR; }
    vector< double > tagReqL1dR(){ return m_tagReqL1dR; }
    vector< double > tagReqEFdR(){ return m_tagReqEFdR; }
    vector< double > tagPt(){ return m_tagPt; }
    vector< double > tagEta(){ return m_tagEta; }
    vector< double > tagExtEta(){ return m_tagExtEta; }
    vector< double > tagExtInnEta(){ return m_tagExtInnEta; }
    vector< double > tagPhi(){ return m_tagPhi; }
    vector< double > tagExtPhi(){ return m_tagExtPhi; }
    vector< double > tagExtInnPhi(){ return m_tagExtInnPhi; }
    vector< double > tagd0(){ return m_tagd0; }
    vector< double > tagz0(){ return m_tagz0; }
    vector< double > tagCharge(){ return m_tagCharge; } 
    vector< double > tagL1Pt(){ return m_tagL1Pt; } 
    vector< double > tagL1Eta(){ return m_tagL1Eta; } 
    vector< double > tagL1Phi(){ return m_tagL1Phi; } 
    vector< double > tagSAPt(){ return m_tagSAPt; } 
    vector< double > tagSAEta(){ return m_tagSAEta; } 
    vector< double > tagSAPhi(){ return m_tagSAPhi; } 
    vector< double > tagCBPt(){ return m_tagCBPt; } 
    vector< double > tagCBEta(){ return m_tagCBEta; } 
    vector< double > tagCBPhi(){ return m_tagCBPhi; } 
    vector< double > tagEFPt(){ return m_tagEFPt; } 
    vector< double > tagEFEta(){ return m_tagEFEta; } 
    vector< double > tagEFPhi(){ return m_tagEFPhi; } 
    vector< double > probePt(){ return m_probePt; } 
    vector< double > probeMSPt(){ return m_probeMSPt; } //kayamash
    vector< double > probeEta(){ return m_probeEta; }
    vector< double > probeExtEta(){ return m_probeExtEta; }
    vector< double > probeExtInnEta(){ return m_probeExtInnEta; }
    vector< double > probePhi(){ return m_probePhi; } 
    vector< double > probeExtPhi(){ return m_probeExtPhi; } 
    vector< double > probeExtInnPhi(){ return m_probeExtInnPhi; } 
    vector< double > probed0(){ return m_probed0; } 
    vector< double > probez0(){ return m_probez0; } 
    vector< double > probeCharge(){ return m_probeCharge; }
    //
    vector< double > probeSegmentN(){ return m_probeSegmentN; }
    vector< double > probeSegmentX(int segment_number){ return m_probeSegmentX[segment_number]; }
    vector< double > probeSegmentY(int segment_number){ return m_probeSegmentY[segment_number]; }
    vector< double > probeSegmentZ(int segment_number){ return m_probeSegmentZ[segment_number]; }
    vector< double > probeSegmentPx(int segment_number){ return m_probeSegmentPx[segment_number]; }
    vector< double > probeSegmentPy(int segment_number){ return m_probeSegmentPy[segment_number]; }
    vector< double > probeSegmentPz(int segment_number){ return m_probeSegmentPz[segment_number]; }
    vector< double > probeSegmentChiSquared(int segment_number){ return m_probeSegmentChiSquared[segment_number]; }
    vector< double > probeSegmentNumberDoF(int segment_number){ return m_probeSegmentNumberDoF[segment_number]; }
    vector< double > probeSegmentSector(int segment_number){ return m_probeSegmentSector[segment_number]; }
    vector< double > probeSegmentChamberIndex(int segment_number){ return m_probeSegmentChamberIndex[segment_number]; }
    vector< double > probeSegmentEtaIndex(int segment_number){ return m_probeSegmentEtaIndex[segment_number]; }
    vector< double > probeSegmentNPrecisionHits(int segment_number){ return m_probeSegmentNPrecisionHits[segment_number]; }
    vector< double > probeSegmentNPhiLayers(int segment_number){ return m_probeSegmentNPhiLayers[segment_number]; }
    vector< double > probeSegmentNTrigEtaLayers(int segment_number){ return m_probeSegmentNTrigEtaLayers[segment_number]; }

    //
    vector< double > tpVrtDx(){ return m_tpVrtDx; }
    vector< double > tpVrtDy(){ return m_tpVrtDy; }
    vector< double > tpVrtDz(){ return m_tpVrtDz; }
    vector< double > tpVrtChi2(){ return m_tpVrtChi2; }
    vector< int > tpVrtNdof(){ return m_tpVrtNdof; }
    vector< vector< int > > probePassedEFTAG(){ return m_probePassedEFTAG; }
    vector< vector< double > > probeEFTAGdR(){ return m_probeEFTAGdR; }
    vector< vector< double > > probeEFTAGtpdR(){ return m_probeEFTAGtpdR; }
    vector< vector< double > > probeEFTAGPt(){ return m_probeEFTAGPt; }
    vector< vector< double > > probeEFTAGEta(){ return m_probeEFTAGEta; }
    vector< vector< double > > probeEFTAGPhi(){ return m_probeEFTAGPhi; }
    vector< vector< int > > probePassedL1(){ return m_probePassedL1; }
    vector< vector< double > > probeL1dR(){ return m_probeL1dR; }
    vector< vector< double > > probeL1tpdR(){ return m_probeL1tpdR; }
    vector< vector< double > > probeL1Pt(){ return m_probeL1Pt; }
    vector< vector< double > > probeL1Eta(){ return m_probeL1Eta; }
    vector< vector< double > > probeL1Phi(){ return m_probeL1Phi; }
    vector< vector< int > > probePassedSA(){ return m_probePassedSA; }
    vector< vector< double > > probeSAdR(){ return m_probeSAdR; }
    vector< vector< double > > probeSAtpdR(){ return m_probeSAtpdR; }
    vector< vector< double > > probeSAPt(){ return m_probeSAPt; }
    vector< vector< double > > probeSAEta(){ return m_probeSAEta; }
    vector< vector< double > > probeSAPhi(){ return m_probeSAPhi; }
    vector< vector< double > > probeSAEtaMS(){ return m_probeSAEtaMS; }
    vector< vector< double > > probeSAPhiMS(){ return m_probeSAPhiMS; }
    vector< vector< double > > probeSAEtaBE(){ return m_probeSAEtaBE; }
    vector< vector< double > > probeSAPhiBE(){ return m_probeSAPhiBE; }
    //
    vector< vector< double > > probeSATgcPt(){ return m_probeSATgcPt; }
    vector< vector< double > > probeSAPtBarrelRadius(){ return m_probeSAPtBarrelRadius; }
    vector< vector< double > > probeSAPtBarrelSagitta(){ return m_probeSAPtBarrelSagitta; }
    vector< vector< double > > probeSAPtEndcapAlpha(){ return m_probeSAPtEndcapAlpha; }
    vector< vector< double > > probeSAPtEndcapBeta(){ return m_probeSAPtEndcapBeta; }
    vector< vector< double > > probeSAPtEndcapRadius(){ return m_probeSAPtEndcapRadius; }
    vector< vector< double > > probeSAPtCSC(){ return m_probeSAPtCSC; }
    vector< vector< double > > probeSAsAddress(){ return m_probeSAsAddress; }

    vector< vector< float > > probeSAroiEta(){ return m_probeSAroiEta; }
    vector< vector< float > > probeSAroiPhi(){ return m_probeSAroiPhi; }
    vector< vector< int > > probeSAisRpcFailure(){ return m_probeSAisRpcFailure; }
    vector< vector< int > > probeSAisTgcFailure(){ return m_probeSAisTgcFailure; }
    // 
    vector< vector< double > > probeSAsuperPointRBI(){ return m_probeSAsuperPointRBI; }
    vector< vector< double > > probeSAsuperPointRBM(){ return m_probeSAsuperPointRBM; }
    vector< vector< double > > probeSAsuperPointRBO(){ return m_probeSAsuperPointRBO; }
    vector< vector< double > > probeSAsuperPointREI(){ return m_probeSAsuperPointREI; }
    vector< vector< double > > probeSAsuperPointREM(){ return m_probeSAsuperPointREM; }
    vector< vector< double > > probeSAsuperPointREO(){ return m_probeSAsuperPointREO; }
    vector< vector< double > > probeSAsuperPointREE(){ return m_probeSAsuperPointREE; }
    vector< vector< double > > probeSAsuperPointRCSC(){ return m_probeSAsuperPointRCSC; }
    vector< vector< double > > probeSAsuperPointRBEE(){ return m_probeSAsuperPointRBEE; }
    vector< vector< double > > probeSAsuperPointRBME(){ return m_probeSAsuperPointRBME; } 
    //
    vector< vector< double > > probeSAsuperPointZBI(){ return m_probeSAsuperPointZBI; }
    vector< vector< double > > probeSAsuperPointZBM(){ return m_probeSAsuperPointZBM; }
    vector< vector< double > > probeSAsuperPointZBO(){ return m_probeSAsuperPointZBO; }
    vector< vector< double > > probeSAsuperPointZEI(){ return m_probeSAsuperPointZEI; }
    vector< vector< double > > probeSAsuperPointZEM(){ return m_probeSAsuperPointZEM; }
    vector< vector< double > > probeSAsuperPointZEO(){ return m_probeSAsuperPointZEO; }
    vector< vector< double > > probeSAsuperPointZEE(){ return m_probeSAsuperPointZEE; }
    vector< vector< double > > probeSAsuperPointZCSC(){ return m_probeSAsuperPointZCSC; }
    vector< vector< double > > probeSAsuperPointZBEE(){ return m_probeSAsuperPointZBEE; }
    vector< vector< double > > probeSAsuperPointZBME(){ return m_probeSAsuperPointZBME; } 
    //
    vector< vector< double > > probeSAsuperPointSlopeBI(){ return m_probeSAsuperPointSlopeBI; }
    vector< vector< double > > probeSAsuperPointSlopeBM(){ return m_probeSAsuperPointSlopeBM; }
    vector< vector< double > > probeSAsuperPointSlopeBO(){ return m_probeSAsuperPointSlopeBO; }
    vector< vector< double > > probeSAsuperPointSlopeEI(){ return m_probeSAsuperPointSlopeEI; }
    vector< vector< double > > probeSAsuperPointSlopeEM(){ return m_probeSAsuperPointSlopeEM; }
    vector< vector< double > > probeSAsuperPointSlopeEO(){ return m_probeSAsuperPointSlopeEO; }
    vector< vector< double > > probeSAsuperPointSlopeEE(){ return m_probeSAsuperPointSlopeEE; }
    vector< vector< double > > probeSAsuperPointSlopeCSC(){ return m_probeSAsuperPointSlopeCSC; }
    vector< vector< double > > probeSAsuperPointSlopeBEE(){ return m_probeSAsuperPointSlopeBEE; }
    vector< vector< double > > probeSAsuperPointSlopeBME(){ return m_probeSAsuperPointSlopeBME; } 
    //
    vector< vector< double > > probeSAsuperPointInterceptBI(){ return m_probeSAsuperPointInterceptBI; }
    vector< vector< double > > probeSAsuperPointInterceptBM(){ return m_probeSAsuperPointInterceptBM; }
    vector< vector< double > > probeSAsuperPointInterceptBO(){ return m_probeSAsuperPointInterceptBO; }
    vector< vector< double > > probeSAsuperPointInterceptEI(){ return m_probeSAsuperPointInterceptEI; }
    vector< vector< double > > probeSAsuperPointInterceptEM(){ return m_probeSAsuperPointInterceptEM; }
    vector< vector< double > > probeSAsuperPointInterceptEO(){ return m_probeSAsuperPointInterceptEO; }
    vector< vector< double > > probeSAsuperPointInterceptEE(){ return m_probeSAsuperPointInterceptEE; }
    vector< vector< double > > probeSAsuperPointInterceptCSC(){ return m_probeSAsuperPointInterceptCSC; }
    vector< vector< double > > probeSAsuperPointInterceptBEE(){ return m_probeSAsuperPointInterceptBEE; }
    vector< vector< double > > probeSAsuperPointInterceptBME(){ return m_probeSAsuperPointInterceptBME; } 
    //
    vector< vector< double > > probeSAsuperPointChi2BI(){ return m_probeSAsuperPointChi2BI; }
    vector< vector< double > > probeSAsuperPointChi2BM(){ return m_probeSAsuperPointChi2BM; }
    vector< vector< double > > probeSAsuperPointChi2BO(){ return m_probeSAsuperPointChi2BO; }
    vector< vector< double > > probeSAsuperPointChi2EI(){ return m_probeSAsuperPointChi2EI; }
    vector< vector< double > > probeSAsuperPointChi2EM(){ return m_probeSAsuperPointChi2EM; }
    vector< vector< double > > probeSAsuperPointChi2EO(){ return m_probeSAsuperPointChi2EO; }
    vector< vector< double > > probeSAsuperPointChi2EE(){ return m_probeSAsuperPointChi2EE; }
    vector< vector< double > > probeSAsuperPointChi2CSC(){ return m_probeSAsuperPointChi2CSC; }
    vector< vector< double > > probeSAsuperPointChi2BEE(){ return m_probeSAsuperPointChi2BEE; }
    vector< vector< double > > probeSAsuperPointChi2BME(){ return m_probeSAsuperPointChi2BME; } 
    //
    vector< vector< vector < float > > > probeSArpcHitX(){ return m_probeSArpcHitX; } 
    vector< vector< vector < float > > > probeSArpcHitY(){ return m_probeSArpcHitY; } 
    vector< vector< vector < float > > > probeSArpcHitZ(){ return m_probeSArpcHitZ; } 
    vector< vector< vector < double > > > probeSArpcHitR(){ return m_probeSArpcHitR; } 
    vector< vector< vector < double > > > probeSArpcHitEta(){ return m_probeSArpcHitEta; } 
    vector< vector< vector < double > > > probeSArpcHitPhi(){ return m_probeSArpcHitPhi; } 
    vector< vector< vector < double > > > probeSArpcHitStationNumber(){ return m_probeSArpcHitStationNumber; } 
    vector< vector< vector < string > > > probeSArpcHitStationName(){ return m_probeSArpcHitStationName; } 

    vector< vector< vector < int > > > probeSAmdtHitIsOutlier(){ return m_probeSAmdtHitIsOutlier; } 
    vector< vector< vector < int > > > probeSAmdtHitChamber(){ return m_probeSAmdtHitChamber; } 
    vector< vector< vector < float > > > probeSAmdtHitR(){ return m_probeSAmdtHitR; } 
    vector< vector< vector < float > > > probeSAmdtHitZ(){ return m_probeSAmdtHitZ; } 
    vector< vector< vector < float > > > probeSAmdtHitPhi(){ return m_probeSAmdtHitPhi; } 
    vector< vector< vector < float > > > probeSAmdtHitResidual(){ return m_probeSAmdtHitResidual; } 

    vector< vector< vector < float > > > probeSAroadAw(){ return m_probeSAroadAw; } 
    vector< vector< vector < float > > > probeSAroadBw(){ return m_probeSAroadBw; } 
    vector< vector< vector < float > > > probeSAzMin(){ return m_probeSAzMin;   } 
    vector< vector< vector < float > > > probeSAzMax(){ return m_probeSAzMax;   } 
    vector< vector< vector < float > > > probeSArMin(){ return m_probeSArMin;   } 
    vector< vector< vector < float > > > probeSArMax(){ return m_probeSArMax;   } 
    vector< vector< vector < float > > > probeSAetaMin(){ return m_probeSAetaMin; } 
    vector< vector< vector < float > > > probeSAetaMax(){ return m_probeSAetaMax; } 

    //

    vector< vector< int > > probePassedCB(){ return m_probePassedCB; } 
    vector< vector< double > > probeCBdR(){ return m_probeCBdR; }
    vector< vector< double > > probeCBtpdR(){ return m_probeCBtpdR; }
    vector< vector< double > > probeCBPt(){ return m_probeCBPt; }
    vector< vector< double > > probeCBEta(){ return m_probeCBEta; } 
    vector< vector< double > > probeCBPhi(){ return m_probeCBPhi; }
    vector< vector< int > > probePassedFTF(){ return m_probePassedFTF; } 
    vector< vector< double > > probeFTFdR(){ return m_probeFTFdR; }
    vector< vector< double > > probeFTFPt(){ return m_probeFTFPt; }
    vector< vector< double > > probeFTFEta(){ return m_probeFTFEta; } 
    vector< vector< double > > probeFTFPhi(){ return m_probeFTFPhi; }
    vector< vector< int > > probePassedEF(){ return m_probePassedEF; } 
    vector< vector< double > > probeEFdR(){ return m_probeEFdR; }
    vector< vector< double > > probeEFtpdR(){ return m_probeEFtpdR; }
    vector< vector< double > > probeEFPt(){ return m_probeEFPt; }
    vector< vector< double > > probeEFEta(){ return m_probeEFEta; } 
    vector< vector< double > > probeEFPhi(){ return m_probeEFPhi; }

    
    private:
    ParticleSelecterTool m_pst;
    MuonExtUtils m_ext;
    VrtFitUtils m_vft;
    bool m_useExt;
    dk::Utils m_utils;
    ToolHandle<Trig::TrigDecisionTool> m_trigDecTool; //!
    
    string m_message; //!
    string m_method; //!
    int m_tapNProcess; //!
    string dataType; //!
    vector< vector< string > > m_trigEvent; //!
    vector< L1Item > m_trigTagL1; //!
    vector< string > m_trigTagHLT; //!
    vector< string > m_trigTagSATEName; //!
    vector< string > m_trigTagCBTEName; //!
    vector< double > m_tapMassLowerLimit; //!
    vector< double > m_tapMassHigherLimit; //!
    vector< double > m_tapMatchingdRL1Tag; //!
    vector< double > m_tapMatchingdREFTag; //!
    vector< double > m_tapMatchingdRL1Probe; //!
    vector< double > m_tapMatchingdREFProbe; //!
    vector< double > m_tapMatchingdREFMSProbe; //!
    vector< TapType > m_tapType; //!
    vector< bool > m_isPassedEventTrig; //!
    int m_trigNMes; //!
    vector< string > m_trigMesName; //!
    vector< L1Item > m_trigMesL1; //!
    vector< string > m_trigMesHLT; //!
    vector< string > m_trigMesAddTagReq; //!
    vector< int > m_trigMesMSonly; //!
    vector< int > m_trigMesNoMucomb; //!
    vector< int > m_trigMesBRonly; //!
    vector< int > m_trigMesNoL1; //!
    vector< string > m_trigMesSATEName; //!
    vector< string > m_trigMesCBTEName; //!
   
    vector< pair< const xAOD::Muon*, const xAOD::Muon* > > m_TPpairs; //!
    vector< int > m_TPpairsProcess; //!
    vector< double > m_TPpairsTagdRL1; //!
    vector< double > m_TPpairsTagdREF; //!
    vector< double > m_TPpairsReqTagdRL1; //!
    vector< double > m_TPpairsReqTagdREF; //!
    vector< double > m_TPpairsReqProbedRL1; //!
    vector< double > m_TPpairsReqProbedREF; //!
    vector< double > m_TPpairsReqProbedREFMS; //!
    vector< int > m_TPpairsTagL1num; //!
    vector< double > m_TPpairsTagL1Pt; //!
    vector< double > m_TPpairsTagL1Phi; //!
    vector< double > m_TPpairsTagL1Eta; //!
    vector< double > m_TPpairsTagSAPt; //!
    vector< double > m_TPpairsTagSAPhi; //!
    vector< double > m_TPpairsTagSAEta; //!
    vector< double > m_TPpairsTagCBPt; //!
    vector< double > m_TPpairsTagCBPhi; //!
    vector< double > m_TPpairsTagCBEta; //!
    vector< double > m_TPpairsTagEFPt; //!
    vector< double > m_TPpairsTagEFPhi; //!
    vector< double > m_TPpairsTagEFEta; //!
    
    vector< int > m_tagProc; //!
    vector< double > m_tpSumReqL1dR; //!
    vector< double > m_tpSumReqEFdR; //!
    vector< double > m_tagL1dR; //!
    vector< double > m_tagEFdR; //!
    vector< double > m_tagReqL1dR; //!
    vector< double > m_tagReqEFdR; //!
    vector< double > m_tagPt; //!
    vector< double > m_tagEta; //!
    vector< double > m_tagExtEta; //!
    vector< double > m_tagExtInnEta; //!
    vector< double > m_tagPhi; //!
    vector< double > m_tagExtPhi; //!
    vector< double > m_tagExtInnPhi; //!
    vector< double > m_tagd0; //!
    vector< double > m_tagz0; //!
    vector< double > m_tagCharge; //!
    vector< double > m_tagL1Pt; //!
    vector< double > m_tagL1Eta; //!
    vector< double > m_tagL1Phi; //!
    vector< double > m_tagSAPt; //!
    vector< double > m_tagSAEta; //!
    vector< double > m_tagSAPhi; //!
    vector< double > m_tagCBPt; //!
    vector< double > m_tagCBEta; //!
    vector< double > m_tagCBPhi; //!
    vector< double > m_tagEFPt; //!
    vector< double > m_tagEFEta; //!
    vector< double > m_tagEFPhi; //!
    vector< double > m_probePt; //!
    vector< double > m_probeMSPt; //!kayamash
    vector< double > m_probeEta; //!
    vector< double > m_probeExtEta; //!
    vector< double > m_probeExtInnEta; //!
    vector< double > m_probePhi; //!
    vector< double > m_probeExtPhi; //!
    vector< double > m_probeExtInnPhi; //!
    vector< double > m_probed0; //!
    vector< double > m_probez0; //!
    vector< double > m_probeCharge; //!
    //
    vector< double > m_probeSegmentN; //!
    vector< vector < double > > m_probeSegmentX; //!
    vector< vector < double > > m_probeSegmentY; //!
    vector< vector < double > > m_probeSegmentZ; //!
    vector< vector < double > > m_probeSegmentPx; //!
    vector< vector < double > > m_probeSegmentPy; //!
    vector< vector < double > > m_probeSegmentPz; //!
    vector< vector < double > > m_probeSegmentChiSquared; //!
    vector< vector < double > > m_probeSegmentNumberDoF; //!
    vector< vector < double > > m_probeSegmentSector; //!
    vector< vector < double > > m_probeSegmentChamberIndex; //!
    vector< vector < double > > m_probeSegmentEtaIndex; //!
    vector< vector < double > > m_probeSegmentNPrecisionHits; //!
    vector< vector < double > > m_probeSegmentNPhiLayers; //!
    vector< vector < double > > m_probeSegmentNTrigEtaLayers; //!

    //
    vector< double > m_tpVrtDx; //!
    vector< double > m_tpVrtDy; //!
    vector< double > m_tpVrtDz; //!
    vector< double > m_tpVrtChi2; //!
    vector< int > m_tpVrtNdof; //!
    vector< vector< int > > m_probePassedEFTAG; //!
    vector< vector< double > > m_probeEFTAGPt; //!
    vector< vector< double > > m_probeEFTAGdR; //!
    vector< vector< double > > m_probeEFTAGtpdR; //!
    vector< vector< double > > m_probeEFTAGEta; //!
    vector< vector< double > > m_probeEFTAGPhi; //!
    vector< vector< int > > m_probePassedL1; //!
    vector< vector< double > > m_probeL1Pt; //!
    vector< vector< double > > m_probeL1dR; //!
    vector< vector< double > > m_probeL1tpdR; //!
    vector< vector< double > > m_probeL1Eta; //!
    vector< vector< double > > m_probeL1Phi; //!
    vector< vector< int > > m_probePassedSA; //!
    vector< vector< double > > m_probeSAPt; //!
    vector< vector< double > > m_probeSAdR; //!
    vector< vector< double > > m_probeSAtpdR; //!
    vector< vector< double > > m_probeSAEta; //!
    vector< vector< double > > m_probeSAPhi; //!
    vector< vector< double > > m_probeSAEtaMS; //!
    vector< vector< double > > m_probeSAPhiMS; //!
    vector< vector< double > > m_probeSAEtaBE; //!
    vector< vector< double > > m_probeSAPhiBE; //!
    //
    vector< vector< double > > m_probeSATgcPt; //!
    vector< vector< double > > m_probeSAPtBarrelSagitta; //!
    vector< vector< double > > m_probeSAPtBarrelRadius; //!
    vector< vector< double > > m_probeSAPtEndcapAlpha; //!
    vector< vector< double > > m_probeSAPtEndcapBeta; //!
    vector< vector< double > > m_probeSAPtEndcapRadius; //!
    vector< vector< double > > m_probeSAPtCSC; //!
    vector< vector< double > > m_probeSAsAddress; //!

    vector< vector< float > > m_probeSAroiEta; //!
    vector< vector< float > > m_probeSAroiPhi; //!
    vector< vector< int > > m_probeSAisRpcFailure; //!
    vector< vector< int > > m_probeSAisTgcFailure; //!
    // 
    vector< vector< double > > m_probeSAsuperPointRBI; //!
    vector< vector< double > > m_probeSAsuperPointRBM; //!
    vector< vector< double > > m_probeSAsuperPointRBO; //!
    vector< vector< double > > m_probeSAsuperPointREI; //!
    vector< vector< double > > m_probeSAsuperPointREM; //!
    vector< vector< double > > m_probeSAsuperPointREO; //!
    vector< vector< double > > m_probeSAsuperPointREE; //!
    vector< vector< double > > m_probeSAsuperPointRCSC; //!
    vector< vector< double > > m_probeSAsuperPointRBEE; //!
    vector< vector< double > > m_probeSAsuperPointRBME; //!
    // 
    vector< vector< double > > m_probeSAsuperPointZBI; //!
    vector< vector< double > > m_probeSAsuperPointZBM; //!
    vector< vector< double > > m_probeSAsuperPointZBO; //!
    vector< vector< double > > m_probeSAsuperPointZEI; //!
    vector< vector< double > > m_probeSAsuperPointZEM; //!
    vector< vector< double > > m_probeSAsuperPointZEO; //!
    vector< vector< double > > m_probeSAsuperPointZEE; //!
    vector< vector< double > > m_probeSAsuperPointZCSC; //!
    vector< vector< double > > m_probeSAsuperPointZBEE; //!
    vector< vector< double > > m_probeSAsuperPointZBME; //!
    // 
    vector< vector< double > > m_probeSAsuperPointSlopeBI; //!
    vector< vector< double > > m_probeSAsuperPointSlopeBM; //!
    vector< vector< double > > m_probeSAsuperPointSlopeBO; //!
    vector< vector< double > > m_probeSAsuperPointSlopeEI; //!
    vector< vector< double > > m_probeSAsuperPointSlopeEM; //!
    vector< vector< double > > m_probeSAsuperPointSlopeEO; //!
    vector< vector< double > > m_probeSAsuperPointSlopeEE; //!
    vector< vector< double > > m_probeSAsuperPointSlopeCSC; //!
    vector< vector< double > > m_probeSAsuperPointSlopeBEE; //!
    vector< vector< double > > m_probeSAsuperPointSlopeBME; //!
    // 
    vector< vector< double > > m_probeSAsuperPointInterceptBI; //!
    vector< vector< double > > m_probeSAsuperPointInterceptBM; //!
    vector< vector< double > > m_probeSAsuperPointInterceptBO; //!
    vector< vector< double > > m_probeSAsuperPointInterceptEI; //!
    vector< vector< double > > m_probeSAsuperPointInterceptEM; //!
    vector< vector< double > > m_probeSAsuperPointInterceptEO; //!
    vector< vector< double > > m_probeSAsuperPointInterceptEE; //!
    vector< vector< double > > m_probeSAsuperPointInterceptCSC; //!
    vector< vector< double > > m_probeSAsuperPointInterceptBEE; //!
    vector< vector< double > > m_probeSAsuperPointInterceptBME; //!
    // 
    vector< vector< double > > m_probeSAsuperPointChi2BI; //!
    vector< vector< double > > m_probeSAsuperPointChi2BM; //!
    vector< vector< double > > m_probeSAsuperPointChi2BO; //!
    vector< vector< double > > m_probeSAsuperPointChi2EI; //!
    vector< vector< double > > m_probeSAsuperPointChi2EM; //!
    vector< vector< double > > m_probeSAsuperPointChi2EO; //!
    vector< vector< double > > m_probeSAsuperPointChi2EE; //!
    vector< vector< double > > m_probeSAsuperPointChi2CSC; //!
    vector< vector< double > > m_probeSAsuperPointChi2BEE; //!
    vector< vector< double > > m_probeSAsuperPointChi2BME; //!
    //
    vector< vector< vector < float > > > m_probeSArpcHitX; //! 
    vector< vector< vector < float > > > m_probeSArpcHitY; //! 
    vector< vector< vector < float > > > m_probeSArpcHitZ; //! 
    vector< vector< vector < double > > > m_probeSArpcHitR; //! 
    vector< vector< vector < double > > > m_probeSArpcHitEta; //! 
    vector< vector< vector < double > > > m_probeSArpcHitPhi; //! 
    vector< vector< vector < double > > > m_probeSArpcHitStationNumber; //! 
    vector< vector< vector < string > > > m_probeSArpcHitStationName; //! 


    vector< vector< vector < int > > > m_probeSAmdtHitIsOutlier; //! 
    vector< vector< vector < int > > > m_probeSAmdtHitChamber; //! 
    vector< vector< vector < float > > > m_probeSAmdtHitR; //! 
    vector< vector< vector < float > > > m_probeSAmdtHitZ; //! 
    vector< vector< vector < float > > > m_probeSAmdtHitPhi; //! 
    vector< vector< vector < float > > > m_probeSAmdtHitResidual; //! 

    vector< vector< vector < float > > > m_probeSAroadAw; //! 
    vector< vector< vector < float > > > m_probeSAroadBw; //! 
    vector< vector< vector < float > > > m_probeSAzMin; //! 
    vector< vector< vector < float > > > m_probeSAzMax; //! 
    vector< vector< vector < float > > > m_probeSArMin; //! 
    vector< vector< vector < float > > > m_probeSArMax; //! 
    vector< vector< vector < float > > > m_probeSAetaMin; //! 
    vector< vector< vector < float > > > m_probeSAetaMax; //! 
    //
    vector< vector< int > > m_probePassedCB; //!
    vector< vector< double > > m_probeCBPt; //!
    vector< vector< double > > m_probeCBdR; //!
    vector< vector< double > > m_probeCBtpdR; //!
    vector< vector< double > > m_probeCBEta; //!
    vector< vector< double > > m_probeCBPhi; //!
    vector< vector< int > > m_probePassedFTF; //!
    vector< vector< double > > m_probeFTFPt; //!
    vector< vector< double > > m_probeFTFdR; //!
    vector< vector< double > > m_probeFTFEta; //!
    vector< vector< double > > m_probeFTFPhi; //!
    vector< vector< int > > m_probePassedEF; //!
    vector< vector< double > > m_probeEFPt; //!
    vector< vector< double > > m_probeEFdR; //!
    vector< vector< double > > m_probeEFtpdR; //!
    vector< vector< double > > m_probeEFEta; //!
    vector< vector< double > > m_probeEFPhi; //!

};

#endif
