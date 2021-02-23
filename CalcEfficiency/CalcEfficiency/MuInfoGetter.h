#ifndef _INC_MUINFOGETTER
#define _INC_MUINFOGETTER

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

class MuInfoGetter {

	public:
	MuInfoGetter();
	~MuInfoGetter();

    enum L1Item{ NOTHING, L1_MU4, L1_MU6, L1_MU10, L1_MU11, L1_MU20, L1_MU21 };//for data17
    //enum L1Item{ NOTHING, L1_MU4, L1_MU6, L1_MU10, L1_MU11, L1_MU15, L1_MU20 };//for data16
    enum TapType{ L1, L2, EF, ALL };


    int initialize( const int& message,
                    const bool& useExt,
                    const std::string method,
                    MuonExtUtils ext,
                    VrtFitUtils vft,
                    ToolHandle<Trig::TrigDecisionTool> tdt,
                    const std::string dataType,
                    const string& name,
                    const L1Item& mesL1,
                    const string& mesHLT,
                    const string& mesAddTag ); //!
    void clear( ); //!
    int doProbeMatching( const xAOD::MuonRoIContainer* rois, const xAOD::TrackParticleContainer* ftfs ); //!
    int execute(const xAOD::MuonContainer* muons, const xAOD::MuonRoIContainer* rois);

    int matchL1( const L1Item& L1, const xAOD::Muon* muon, const xAOD::MuonRoIContainer* rois, const double* reqdR, double* param); //!
    bool matchSA( const Trig::FeatureContainer& fc, int L1num, double* param, std::vector< float >& vec_param_X, std::vector< float >& vec_param_Y, std::vector< float >& vec_param_Z, std::vector< uint32_t >& vec_param_mesPhi, float* param_rpcFit, std::vector< string >& vec_param_string, std::string& mesSATEName, std::vector< std::vector < float> >& vec_param_road, vector < vector < int > >& vec_param_mdtInt, vector < vector < float > >& vec_param_mdtFloat, double* l1param); //kayamash  //ktaniguc
    bool matchCB( const xAOD::Muon* muon, const Trig::FeatureContainer& fc, double* reqdR, double* param, std::string& cbTEName );
    bool matchCB( const Trig::FeatureContainer& fc, int L1num, double* param, std::string& cbTEName ) ;
    int matchEF( const string& chain, const xAOD::Muon* muon, const Trig::FeatureContainer& fc, double* reqdR, double* param ); //!
    int matchEFFS( const string& chain, const xAOD::Muon* muon, const Trig::FeatureContainer& fc, double* reqdR, double* param, double* tagparam ); //!
    double dRL1byPt( double mupt ); //!
    Bool_t getSATEName( const std::string& mesHLT, std::string& teName );
    Bool_t getSATEName( const char* mesHLT, std::string& teName );
    Bool_t getCBTEName( const std::string& mesHLT, std::string& teName );
    Bool_t getCBTEName( const char* mesHLT, std::string& teName );

    bool SAHypo( double pt, int EtaRegion, int ECWeakRegion );
    bool CBHypo( double pt, int EtaRegion );
    int ECWeakRegion( double eta, double phi );
    int EtaRegion( double eta );
    double CalcdR( const double& eta1, const double& eta2, const double& phi1, const double& phi2 );
    double CalcInvMass( const double& pt1, const double& pt2, const double& eta1, const double& eta2, const double& phi1, const double& phi2, const double& m1, const double& m2 );
    bool OvRmCut( const double& pt1, const double& pt2, const double& etaMS1, const double& etaMS2, const double& phiMS1, const double& phiMS2 );//for L2MuonSA
    bool OvRmCut( const double& pt1, const double& pt2, const double& eta1, const double& eta2, const double& phi1, const double& phi2, const double& etaMS1, const double& etaMS2, const double& phiMS1, const double& phiMS2 );//for L2MuComb


    string mesName(){ return m_trigMesName; }
    uint32_t nMuon(){ return m_nMuon; }
    vector < double > muonOfflinePt(){ return m_muonOfflinePt; }
    vector < double > muonOfflineEta(){ return m_muonOfflineEta; }
    vector < double > muonOfflineExtEta(){ return m_muonOfflineExtEta; }
    vector < double > muonOfflineExtInnEta(){ return m_muonOfflineExtInnEta; }
    vector < double > muonOfflinePhi(){ return m_muonOfflinePhi; }
    vector < double > muonOfflineExtPhi(){ return m_muonOfflineExtPhi; }
    vector < double > muonOfflineExtInnPhi(){ return m_muonOfflineExtInnPhi; }
    vector < double > muonOfflineD0(){ return m_muonOfflineD0; }
    vector < double > muonOfflineZ0(){ return m_muonOfflineZ0; }
    vector < double > muonOfflineCharge(){ return m_muonOfflineCharge; }
    vector < int > muonOfflineSegmentN(){ return m_muonOfflineSegmentN; }
    vector < vector < double > > muonOfflineSegmentX(){ return m_vMuonOfflineSegmentX; }
    vector < vector < double > > muonOfflineSegmentY(){ return m_vMuonOfflineSegmentY; }
    vector < vector < double > > muonOfflineSegmentZ(){ return m_vMuonOfflineSegmentZ; }
    vector < vector < double > > muonOfflineSegmentPx(){ return m_vMuonOfflineSegmentPx; }
    vector < vector < double > > muonOfflineSegmentPy(){ return m_vMuonOfflineSegmentPy; }
    vector < vector < double > > muonOfflineSegmentPz(){ return m_vMuonOfflineSegmentPz; }
    vector < vector < double > > muonOfflineSegmentChiSquared(){ return m_vMuonOfflineSegmentChiSquared; }
    vector < vector < double > > muonOfflineSegmentNumberDoF(){ return m_vMuonOfflineSegmentNumberDoF; }
    vector < vector < double > > muonOfflineSegmentSector(){ return m_vMuonOfflineSegmentSector; }
    vector < vector < double > > muonOfflineSegmentChamberIndex(){ return m_vMuonOfflineSegmentChamberIndex; }
    vector < vector < double > > muonOfflineSegmentEtaIndex(){ return m_vMuonOfflineSegmentEtaIndex; }
    vector < vector < double > > muonOfflineSegmentNPrecisionHits(){ return m_vMuonOfflineSegmentNPrecisionHits; }
    vector < vector < double > > muonOfflineSegmentNPhiLayers(){ return m_vMuonOfflineSegmentNPhiLayers; }
    vector < vector < double > > muonOfflineSegmentNTrigEtaLayers(){ return m_vMuonOfflineSegmentNTrigEtaLayers; }
    vector < int > muonEFTAGPass(){ return m_muonEFTAGPass; }
    vector < double > muonEFTAGPt(){ return m_muonEFTAGPt; }
    vector < double > muonEFTAGEta(){ return m_muonEFTAGEta; }
    vector < double > muonEFTAGPhi(){ return m_muonEFTAGPhi; }
    vector < int > muonL1Pass(){ return m_muonL1Pass; }
    vector < double > muonL1Pt(){ return m_muonL1Pt; }
    vector < double > muonL1Eta(){ return m_muonL1Eta; }
    vector < double > muonL1Phi(){ return m_muonL1Phi; }
    vector < int > muonL1roiNumber(){ return m_muonL1roiNumber; }
    vector < int > muonL1roiSector(){ return m_muonL1roiSector; }
    vector < int > muonSAHypoPass(){ return m_muonSAHypoPass; }
    vector < bool > muonSAOvRmPass(){ return m_muonSAOvRmPass; }
    vector < double > muonSAPt(){ return m_muonSAPt; }
    vector < double > muonSAEta(){ return m_muonSAEta; }
    vector < double > muonSAPhi(){ return m_muonSAPhi; }
    vector < double > muonSAEtaMS(){ return m_muonSAEtaMS; }
    vector < double > muonSAPhiMS(){ return m_muonSAPhiMS; }
    vector < double > muonSAEtaBE(){ return m_muonSAEtaBE; }
    vector < double > muonSAPhiBE(){ return m_muonSAPhiBE; }
    vector < double > muonSAtgcPt(){ return m_muonSAtgcPt; }
    vector < double > muonSAPtBarrelRadius(){ return m_muonSAPtBarrelRadius; }
    vector < double > muonSAPtBarrelSagitta(){ return m_muonSAPtBarrelSagitta; }
    vector < double > muonSAPtEndcapAlpha(){ return m_muonSAPtEndcapAlpha; }
    vector < double > muonSAPtEndcapBeta(){ return m_muonSAPtEndcapBeta; }
    vector < double > muonSAPtEndcapRadius(){ return m_muonSAPtEndcapRadius; }
    vector < double > muonSAcscPt(){ return m_muonSAcscPt; }
    vector < double > muonSAsAddress(){ return m_muonSAsAddress; }
    vector < double > muonSASuperPointRBI(){ return m_muonSASuperPointRBI; }
    vector < double > muonSASuperPointRBM(){ return m_muonSASuperPointRBM; }
    vector < double > muonSASuperPointRBO(){ return m_muonSASuperPointRBO; }
    vector < double > muonSASuperPointREI(){ return m_muonSASuperPointREI; }
    vector < double > muonSASuperPointREM(){ return m_muonSASuperPointREM; }
    vector < double > muonSASuperPointREO(){ return m_muonSASuperPointREO; }
    vector < double > muonSASuperPointREE(){ return m_muonSASuperPointREE; }
    vector < double > muonSASuperPointRCSC(){ return m_muonSASuperPointRCSC; }
    vector < double > muonSASuperPointRBEE(){ return m_muonSASuperPointRBEE; }
    vector < double > muonSASuperPointRBME(){ return m_muonSASuperPointRBME; }
    vector < double > muonSASuperPointZBI(){ return m_muonSASuperPointZBI; }
    vector < double > muonSASuperPointZBM(){ return m_muonSASuperPointZBM; }
    vector < double > muonSASuperPointZBO(){ return m_muonSASuperPointZBO; }
    vector < double > muonSASuperPointZEI(){ return m_muonSASuperPointZEI; }
    vector < double > muonSASuperPointZEM(){ return m_muonSASuperPointZEM; }
    vector < double > muonSASuperPointZEO(){ return m_muonSASuperPointZEO; }
    vector < double > muonSASuperPointZEE(){ return m_muonSASuperPointZEE; }
    vector < double > muonSASuperPointZCSC(){ return m_muonSASuperPointZCSC; }
    vector < double > muonSASuperPointZBEE(){ return m_muonSASuperPointZBEE; }
    vector < double > muonSASuperPointZBME(){ return m_muonSASuperPointZBME; }
    vector < double > muonSASuperPointSlopeBI(){ return m_muonSASuperPointSlopeBI; }
    vector < double > muonSASuperPointSlopeBM(){ return m_muonSASuperPointSlopeBM; }
    vector < double > muonSASuperPointSlopeBO(){ return m_muonSASuperPointSlopeBO; }
    vector < double > muonSASuperPointSlopeEI(){ return m_muonSASuperPointSlopeEI; }
    vector < double > muonSASuperPointSlopeEM(){ return m_muonSASuperPointSlopeEM; }
    vector < double > muonSASuperPointSlopeEO(){ return m_muonSASuperPointSlopeEO; }
    vector < double > muonSASuperPointSlopeEE(){ return m_muonSASuperPointSlopeEE; }
    vector < double > muonSASuperPointSlopeCSC(){ return m_muonSASuperPointSlopeCSC; }
    vector < double > muonSASuperPointSlopeBEE(){ return m_muonSASuperPointSlopeBEE; }
    vector < double > muonSASuperPointSlopeBME(){ return m_muonSASuperPointSlopeBME; }
    vector < double > muonSASuperPointInterceptBI(){ return m_muonSASuperPointInterceptBI; }
    vector < double > muonSASuperPointInterceptBM(){ return m_muonSASuperPointInterceptBM; }
    vector < double > muonSASuperPointInterceptBO(){ return m_muonSASuperPointInterceptBO; }
    vector < double > muonSASuperPointInterceptEI(){ return m_muonSASuperPointInterceptEI; }
    vector < double > muonSASuperPointInterceptEM(){ return m_muonSASuperPointInterceptEM; }
    vector < double > muonSASuperPointInterceptEO(){ return m_muonSASuperPointInterceptEO; }
    vector < double > muonSASuperPointInterceptEE(){ return m_muonSASuperPointInterceptEE; }
    vector < double > muonSASuperPointInterceptCSC(){ return m_muonSASuperPointInterceptCSC; }
    vector < double > muonSASuperPointInterceptBEE(){ return m_muonSASuperPointInterceptBEE; }
    vector < double > muonSASuperPointInterceptBME(){ return m_muonSASuperPointInterceptBME; }
    vector < double > muonSASuperPointChi2BI(){ return m_muonSASuperPointChi2BI; }
    vector < double > muonSASuperPointChi2BM(){ return m_muonSASuperPointChi2BM; }
    vector < double > muonSASuperPointChi2BO(){ return m_muonSASuperPointChi2BO; }
    vector < double > muonSASuperPointChi2EI(){ return m_muonSASuperPointChi2EI; }
    vector < double > muonSASuperPointChi2EM(){ return m_muonSASuperPointChi2EM; }
    vector < double > muonSASuperPointChi2EO(){ return m_muonSASuperPointChi2EO; }
    vector < double > muonSASuperPointChi2EE(){ return m_muonSASuperPointChi2EE; }
    vector < double > muonSASuperPointChi2CSC(){ return m_muonSASuperPointChi2CSC; }
    vector < double > muonSASuperPointChi2BEE(){ return m_muonSASuperPointChi2BEE; }
    vector < double > muonSASuperPointChi2BME(){ return m_muonSASuperPointChi2BME; }
    vector < float > muonSAroiEta(){ return m_muonSAroiEta; }
    vector < float > muonSAroiPhi(){ return m_muonSAroiPhi; }
    vector < double > muonSAisrpcFailure(){ return m_muonSAisrpcFailure; }
    vector < double > muonSAistgcFailure(){ return m_muonSAistgcFailure; }
    vector < double > muonSABarrelRadius(){ return m_muonSABarrelRadius; }
    vector < double > muonSABarrelSagitta(){ return m_muonSABarrelSagitta; }
    vector < double > muonSAEtaMap(){ return m_muonSAEtaMap; }
    vector < double > muonSAPhiMap(){ return m_muonSAPhiMap; }
    vector < uint32_t > muonSAroiNumber(){ return m_muonSAroiNumber; }
    vector < uint32_t > muonSAroiSector(){ return m_muonSAroiSector; }
    vector < vector < float > > muonSArpcHitX(){ return m_vMuonSArpcHitX; }
    vector < vector < float > > muonSArpcHitY(){ return m_vMuonSArpcHitY; }
    vector < vector < float > > muonSArpcHitZ(){ return m_vMuonSArpcHitZ; }
    vector < vector < double > > muonSArpcHitR(){ return m_vMuonSArpcHitR; }
    vector < vector < double > > muonSArpcHitEta(){ return m_vMuonSArpcHitEta; }
    vector < vector < double > > muonSArpcHitPhi(){ return m_vMuonSArpcHitPhi; }
    vector < vector < uint32_t > > muonSArpcHitMeasuresPhi(){ return m_vMuonSArpcHitMeasuresPhi; }
    vector < vector < string > > muonSArpcHitStationName(){ return m_vMuonSArpcHitStationName; }
    vector < vector < double > > muonSArpcHitStationNumber(){ return m_vMuonSArpcHitStationNumber; }
    vector < float > muonSArpcFitInnPhi(){ return m_muonSArpcFitInnPhi; }
    vector < float > muonSArpcFitInnSlope(){ return m_muonSArpcFitInnSlope; }
    vector < float > muonSArpcFitInnOffset(){ return m_muonSArpcFitInnOffset; }
    vector < float > muonSArpcFitMidPhi(){ return m_muonSArpcFitMidPhi; }
    vector < float > muonSArpcFitMidSlope(){ return m_muonSArpcFitMidSlope; }
    vector < float > muonSArpcFitMidOffset(){ return m_muonSArpcFitMidOffset; }
    vector < float > muonSArpcFitOutPhi(){ return m_muonSArpcFitOutPhi; }
    vector < float > muonSArpcFitOutSlope(){ return m_muonSArpcFitOutSlope; }
    vector < float > muonSArpcFitOutOffset(){ return m_muonSArpcFitOutOffset; }
    vector < vector < float > > muonSARoadAw(){ return m_vMuonSARoadAw; }
    vector < vector < float > > muonSARoadBw(){ return m_vMuonSARoadBw; }
    vector < vector < float > > muonSAZMin(){ return m_vMuonSAZMin; }
    vector < vector < float > > muonSAZMax(){ return m_vMuonSAZMax; }
    vector < vector < float > > muonSARMin(){ return m_vMuonSARMin; }
    vector < vector < float > > muonSARMax(){ return m_vMuonSARMax; }
    vector < vector < float > > muonSAEtaMin(){ return m_vMuonSAEtaMin; }
    vector < vector < float > > muonSAEtaMax(){ return m_vMuonSAEtaMax; }
    vector < vector < int > > muonSAmdtHitIsOutlier(){ return m_vMuonSAmdtHitIsOutlier; }
    vector < vector < int > > muonSAmdtHitChamber(){ return m_vMuonSAmdtHitChamber; }
    vector < vector < float > > muonSAmdtHitR(){ return m_vMuonSAmdtHitR; }
    vector < vector < float > > muonSAmdtHitZ(){ return m_vMuonSAmdtHitZ; }
    vector < vector < float > > muonSAmdtHitPhi(){ return m_vMuonSAmdtHitPhi; }
    vector < vector < float > > muonSAmdtHitResidual(){ return m_vMuonSAmdtHitResidual; }
    vector < vector < float > > muonSAmdtHitSpace(){ return m_vMuonSAmdtHitSpace; }
    vector < vector < float > > muonSAmdtHitSigma(){ return m_vMuonSAmdtHitSigma; }
    vector < int > muonCBHypoPass(){ return m_muonCBHypoPass; }
    vector < bool > muonCBOvRmPass(){ return m_muonCBOvRmPass; }
    vector < double > muonCBPt(){ return m_muonCBPt; }
    vector < double > muonCBEta(){ return m_muonCBEta; }
    vector < double > muonCBPhi(){ return m_muonCBPhi; }
    vector < int > muonEFPass(){ return m_muonEFPass; }
    vector < double > muonEFPt(){ return m_muonEFPt; }
    vector < double > muonEFEta(){ return m_muonEFEta; }
    vector < double > muonEFPhi(){ return m_muonEFPhi; }

    private:
    ParticleSelecterTool m_pst;
    MuonExtUtils m_ext;
    VrtFitUtils m_vft;
    bool m_useExt;
    dk::Utils m_utils;
    ToolHandle<Trig::TrigDecisionTool> m_trigDecTool;

    string m_message;
    string m_method;
    string dataType;
    string m_trigMesName;
    L1Item m_trigMesL1;
    string m_trigMesHLT;
    string m_trigMesAddTagReq;
    int m_trigMesMSonly;
    int m_trigMesNoMucomb;
    int m_trigMesBRonly;
    int m_trigMesNoL1;
    string m_trigMesSATEName;
    string m_trigMesCBTEName;
    double m_SAThresholds[4];
    double m_SAWeakThresholds[2];
    double m_CBThresholds[4];

    //For Tree
    uint32_t m_nMuon;
    vector < double > m_muonOfflinePt;
    vector < double > m_muonOfflineEta;
    vector < double > m_muonOfflineExtEta;
    vector < double > m_muonOfflineExtInnEta;
    vector < double > m_muonOfflinePhi;
    vector < double > m_muonOfflineExtPhi;
    vector < double > m_muonOfflineExtInnPhi;
    vector < double > m_muonOfflineD0;
    vector < double > m_muonOfflineZ0;
    vector < double > m_muonOfflineCharge;
    vector < int > m_muonOfflineSegmentN;
    vector < vector < double > > m_vMuonOfflineSegmentX;
    vector < vector < double > > m_vMuonOfflineSegmentY;
    vector < vector < double > > m_vMuonOfflineSegmentZ;
    vector < vector < double > > m_vMuonOfflineSegmentPx;
    vector < vector < double > > m_vMuonOfflineSegmentPy;
    vector < vector < double > > m_vMuonOfflineSegmentPz;
    vector < vector < double > > m_vMuonOfflineSegmentChiSquared;
    vector < vector < double > > m_vMuonOfflineSegmentNumberDoF;
    vector < vector < double > > m_vMuonOfflineSegmentSector;
    vector < vector < double > > m_vMuonOfflineSegmentChamberIndex;
    vector < vector < double > > m_vMuonOfflineSegmentEtaIndex;
    vector < vector < double > > m_vMuonOfflineSegmentNPrecisionHits;
    vector < vector < double > > m_vMuonOfflineSegmentNPhiLayers;
    vector < vector < double > > m_vMuonOfflineSegmentNTrigEtaLayers;
    vector < int > m_muonEFTAGPass;
    vector < double > m_muonEFTAGPt;
    vector < double > m_muonEFTAGEta;
    vector < double > m_muonEFTAGPhi;
    vector < int > m_muonL1Pass;
    vector < double > m_muonL1Pt;
    vector < double > m_muonL1Eta;
    vector < double > m_muonL1Phi;
    vector < int > m_muonL1roiNumber;
    vector < int > m_muonL1roiSector;
    vector < int > m_muonSAHypoPass;
    vector < bool > m_muonSAOvRmPass;
    vector < double > m_muonSAPt;
    vector < double > m_muonSAEta;
    vector < double > m_muonSAPhi;
    vector < double > m_muonSAEtaMS;
    vector < double > m_muonSAPhiMS;
    vector < double > m_muonSAEtaBE;
    vector < double > m_muonSAPhiBE;
    vector < double > m_muonSAtgcPt;
    vector < double > m_muonSAPtBarrelRadius;
    vector < double > m_muonSAPtBarrelSagitta;
    vector < double > m_muonSAPtEndcapAlpha;
    vector < double > m_muonSAPtEndcapBeta;
    vector < double > m_muonSAPtEndcapRadius;
    vector < double > m_muonSAcscPt;
    vector < double > m_muonSAsAddress;
    vector < double > m_muonSASuperPointRBI;
    vector < double > m_muonSASuperPointRBM;
    vector < double > m_muonSASuperPointRBO;
    vector < double > m_muonSASuperPointREI;
    vector < double > m_muonSASuperPointREM;
    vector < double > m_muonSASuperPointREO;
    vector < double > m_muonSASuperPointREE;
    vector < double > m_muonSASuperPointRCSC;
    vector < double > m_muonSASuperPointRBEE;
    vector < double > m_muonSASuperPointRBME;
    vector < double > m_muonSASuperPointZBI;
    vector < double > m_muonSASuperPointZBM;
    vector < double > m_muonSASuperPointZBO;
    vector < double > m_muonSASuperPointZEI;
    vector < double > m_muonSASuperPointZEM;
    vector < double > m_muonSASuperPointZEO;
    vector < double > m_muonSASuperPointZEE;
    vector < double > m_muonSASuperPointZCSC;
    vector < double > m_muonSASuperPointZBEE;
    vector < double > m_muonSASuperPointZBME;
    vector < double > m_muonSASuperPointSlopeBI;
    vector < double > m_muonSASuperPointSlopeBM;
    vector < double > m_muonSASuperPointSlopeBO;
    vector < double > m_muonSASuperPointSlopeEI;
    vector < double > m_muonSASuperPointSlopeEM;
    vector < double > m_muonSASuperPointSlopeEO;
    vector < double > m_muonSASuperPointSlopeEE;
    vector < double > m_muonSASuperPointSlopeCSC;
    vector < double > m_muonSASuperPointSlopeBEE;
    vector < double > m_muonSASuperPointSlopeBME;
    vector < double > m_muonSASuperPointInterceptBI;
    vector < double > m_muonSASuperPointInterceptBM;
    vector < double > m_muonSASuperPointInterceptBO;
    vector < double > m_muonSASuperPointInterceptEI;
    vector < double > m_muonSASuperPointInterceptEM;
    vector < double > m_muonSASuperPointInterceptEO;
    vector < double > m_muonSASuperPointInterceptEE;
    vector < double > m_muonSASuperPointInterceptCSC;
    vector < double > m_muonSASuperPointInterceptBEE;
    vector < double > m_muonSASuperPointInterceptBME;
    vector < double > m_muonSASuperPointChi2BI;
    vector < double > m_muonSASuperPointChi2BM;
    vector < double > m_muonSASuperPointChi2BO;
    vector < double > m_muonSASuperPointChi2EI;
    vector < double > m_muonSASuperPointChi2EM;
    vector < double > m_muonSASuperPointChi2EO;
    vector < double > m_muonSASuperPointChi2EE;
    vector < double > m_muonSASuperPointChi2CSC;
    vector < double > m_muonSASuperPointChi2BEE;
    vector < double > m_muonSASuperPointChi2BME;
    vector < float > m_muonSAroiEta;
    vector < float > m_muonSAroiPhi;
    vector < double > m_muonSAisrpcFailure;
    vector < double > m_muonSAistgcFailure;
    vector < double > m_muonSABarrelRadius;
    vector < double > m_muonSABarrelSagitta;
    vector < double > m_muonSAEtaMap;
    vector < double > m_muonSAPhiMap;
    vector < uint32_t > m_muonSAroiNumber;
    vector < uint32_t > m_muonSAroiSector;
    vector < vector < float > > m_vMuonSArpcHitX;
    vector < vector < float > > m_vMuonSArpcHitY;
    vector < vector < float > > m_vMuonSArpcHitZ;
    vector < vector < double > > m_vMuonSArpcHitR;
    vector < vector < double > > m_vMuonSArpcHitEta;
    vector < vector < double > > m_vMuonSArpcHitPhi;
    vector < vector < uint32_t > > m_vMuonSArpcHitMeasuresPhi;
    vector < vector < string > > m_vMuonSArpcHitStationName;
    vector < vector < double > > m_vMuonSArpcHitStationNumber;
    vector < float > m_muonSArpcFitInnPhi;
    vector < float > m_muonSArpcFitInnSlope;
    vector < float > m_muonSArpcFitInnOffset;
    vector < float > m_muonSArpcFitMidPhi;
    vector < float > m_muonSArpcFitMidSlope;
    vector < float > m_muonSArpcFitMidOffset;
    vector < float > m_muonSArpcFitOutPhi;
    vector < float > m_muonSArpcFitOutSlope;
    vector < float > m_muonSArpcFitOutOffset;
    vector < vector < float > > m_vMuonSARoadAw;
    vector < vector < float > > m_vMuonSARoadBw;
    vector < vector < float > > m_vMuonSAZMin;
    vector < vector < float > > m_vMuonSAZMax;
    vector < vector < float > > m_vMuonSARMin;
    vector < vector < float > > m_vMuonSARMax;
    vector < vector < float > > m_vMuonSAEtaMin;
    vector < vector < float > > m_vMuonSAEtaMax;
    vector < vector < int > > m_vMuonSAmdtHitIsOutlier;
    vector < vector < int > > m_vMuonSAmdtHitChamber;
    vector < vector < float > > m_vMuonSAmdtHitR;
    vector < vector < float > > m_vMuonSAmdtHitZ;
    vector < vector < float > > m_vMuonSAmdtHitPhi;
    vector < vector < float > > m_vMuonSAmdtHitResidual;
    vector < vector < float > > m_vMuonSAmdtHitSpace;
    vector < vector < float > > m_vMuonSAmdtHitSigma;
    vector < int > m_muonCBHypoPass;
    vector < bool > m_muonCBOvRmPass;
    vector < int > m_muonCBPass;
    vector < double > m_muonCBPt;
    vector < double > m_muonCBEta;
    vector < double > m_muonCBPhi;
    vector < double > m_muonCBEtaMS;
    vector < double > m_muonCBPhiMS;
    vector < int > m_muonEFPass;
    vector < double > m_muonEFPt;
    vector < double > m_muonEFEta;
    vector < double > m_muonEFPhi;
};

#endif
