#ifndef _TrigMuonAnalysis_EventTreeFCBM
#define _TrigMuonAnalysis_EventTreeFCBM

#include <iostream>
#include <fstream>
#include <vector>

#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TLorentzVector.h"

#include "CalcEfficiency/MuInfoGetter.h"
#include "CalcEfficiency/Utils.h"

using namespace std;

class EventTreeFCBM {

	public:
	EventTreeFCBM();
	EventTreeFCBM( TFile* file, TString name );
	~EventTreeFCBM();

	TFile* m_file; //!
	TTree* m_tree; //!

	int initialize( TString outfile );
	//int initialize( TFile* outfile, TTree* outtree );
	int clear();
	int filltree( MuInfoGetter& mig, unsigned long long int eventNumber, int runNumber, int lumiBlock, float averageInteractionsPerCrossing );
	int finalize();

    //branch variable
    unsigned long long int EventNumber;
    int RunNumber;
    int LumiBlock;
    float AverageInteractionsPerCrossing;
    string mes_name;
    uint32_t n_muon;
    vector < double >* muon_offline_pt;
    vector < double >* muon_offline_eta;
    vector < double >* muon_offline_exteta;
    vector < double >* muon_offline_extinneta;
    vector < double >* muon_offline_phi;
    vector < double >* muon_offline_extphi;
    vector < double >* muon_offline_extinnphi;
    vector < double >* muon_offline_d0;
    vector < double >* muon_offline_z0;
    vector < double >* muon_offline_charge;
    vector < int >* muon_n_offlineSegment;
    vector < vector < double > >* muon_offlineSegment_x;
    vector < vector < double > >* muon_offlineSegment_y;
    vector < vector < double > >* muon_offlineSegment_z;
    vector < vector < double > >* muon_offlineSegment_px;
    vector < vector < double > >* muon_offlineSegment_py;
    vector < vector < double > >* muon_offlineSegment_pz;
    vector < vector < double > >* muon_offlineSegment_chiSquared;
    vector < vector < double > >* muon_offlineSegment_NumberDoF;
    vector < vector < double > >* muon_offlineSegment_sector;
    vector < vector < double > >* muon_offlineSegment_chamberIndex;
    vector < vector < double > >* muon_offlineSegment_etaIndex;
    vector < vector < double > >* muon_offlineSegment_nPrecisionHits;
    vector < vector < double > >* muon_offlineSegment_NPhiLayers;
    vector < vector < double > >* muon_offlineSegment_NTrigEtaLayers;
    vector < int >* muon_EFTAG_pass;
    vector < double >* muon_EFTAG_pt;
    vector < double >* muon_EFTAG_eta;
    vector < double >* muon_EFTAG_phi;
    vector < int >* muon_L1_pass;
    vector < double >* muon_L1_pt;
    vector < double >* muon_L1_eta;
    vector < double >* muon_L1_phi;
    vector < int >* muon_L1_RoINumber;
    vector < int >* muon_L1_RoISector;
    vector < int >* muon_SA_HypoPass;
    vector < bool >* muon_SA_OvRmPass;
    vector < double >* muon_SA_pt;
    vector < double >* muon_SA_eta;
    vector < double >* muon_SA_phi;
    vector < double >* muon_SA_etaMS;
    vector < double >* muon_SA_phiMS;
    vector < double >* muon_SA_etaBE;
    vector < double >* muon_SA_phiBE;
    vector < double >* muon_SA_TGCpt;
    vector < double >* muon_SA_ptBarrelRadius;
    vector < double >* muon_SA_ptBarrelSagitta;
    vector < double >* muon_SA_ptEndcapAlpha;
    vector < double >* muon_SA_ptEndcapBeta;
    vector < double >* muon_SA_ptEndcapRadius;
    vector < double >* muon_SA_CSCpt;
    vector < double >* muon_SA_sAddress;
    vector < double >* muon_SA_SP_rBI;
    vector < double >* muon_SA_SP_rBM;
    vector < double >* muon_SA_SP_rBO;
    vector < double >* muon_SA_SP_rEI;
    vector < double >* muon_SA_SP_rEM;
    vector < double >* muon_SA_SP_rEO;
    vector < double >* muon_SA_SP_rEE;
    vector < double >* muon_SA_SP_rCSC;
    vector < double >* muon_SA_SP_rBEE;
    vector < double >* muon_SA_SP_rBME;
    vector < double >* muon_SA_SP_zBI;
    vector < double >* muon_SA_SP_zBM;
    vector < double >* muon_SA_SP_zBO;
    vector < double >* muon_SA_SP_zEI;
    vector < double >* muon_SA_SP_zEM;
    vector < double >* muon_SA_SP_zEO;
    vector < double >* muon_SA_SP_zEE;
    vector < double >* muon_SA_SP_zCSC;
    vector < double >* muon_SA_SP_zBEE;
    vector < double >* muon_SA_SP_zBME;
    vector < double >* muon_SA_SP_slopeBI;
    vector < double >* muon_SA_SP_slopeBM;
    vector < double >* muon_SA_SP_slopeBO;
    vector < double >* muon_SA_SP_slopeEI;
    vector < double >* muon_SA_SP_slopeEM;
    vector < double >* muon_SA_SP_slopeEO;
    vector < double >* muon_SA_SP_slopeEE;
    vector < double >* muon_SA_SP_slopeCSC;
    vector < double >* muon_SA_SP_slopeBEE;
    vector < double >* muon_SA_SP_slopeBME;
    vector < double >* muon_SA_SP_interceptBI;
    vector < double >* muon_SA_SP_interceptBM;
    vector < double >* muon_SA_SP_interceptBO;
    vector < double >* muon_SA_SP_interceptEI;
    vector < double >* muon_SA_SP_interceptEM;
    vector < double >* muon_SA_SP_interceptEO;
    vector < double >* muon_SA_SP_interceptEE;
    vector < double >* muon_SA_SP_interceptCSC;
    vector < double >* muon_SA_SP_interceptBEE;
    vector < double >* muon_SA_SP_interceptBME;
    vector < double >* muon_SA_SP_chi2BI;
    vector < double >* muon_SA_SP_chi2BM;
    vector < double >* muon_SA_SP_chi2BO;
    vector < double >* muon_SA_SP_chi2EI;
    vector < double >* muon_SA_SP_chi2EM;
    vector < double >* muon_SA_SP_chi2EO;
    vector < double >* muon_SA_SP_chi2EE;
    vector < double >* muon_SA_SP_chi2CSC;
    vector < double >* muon_SA_SP_chi2BEE;
    vector < double >* muon_SA_SP_chi2BME;
    vector < float >* muon_SA_RoIEta;
    vector < float >* muon_SA_RoIPhi;
    vector < double >* muon_SA_isRPCFailure;
    vector < double >* muon_SA_isTGCFailure;
    vector < double >* muon_SA_BarrelRadius;
    vector < double >* muon_SA_BarrelSagitta;
    vector < double >* muon_SA_EtaMap;
    vector < double >* muon_SA_PhiMap;
    vector < uint32_t >* muon_SA_RoINumber;
    vector < uint32_t >* muon_SA_RoISector;
    vector < vector < float > >* muon_SA_RPCHit_x;
    vector < vector < float > >* muon_SA_RPCHit_y;
    vector < vector < float > >* muon_SA_RPCHit_z;
    vector < vector < double > >* muon_SA_RPCHit_r;
    vector < vector < double > >* muon_SA_RPCHit_eta;
    vector < vector < double > >* muon_SA_RPCHit_phi;
    vector < vector < uint32_t > >* muon_SA_RPCHit_measuresPhi;
    vector < vector < string > >* muon_SA_RPCHit_stationName;
    vector < vector < double > >* muon_SA_RPCHit_stationNumber;
    vector < float >* muon_SA_RPCFit_innPhi;
    vector < float >* muon_SA_RPCFit_innSlope;
    vector < float >* muon_SA_RPCFit_innOffset;
    vector < float >* muon_SA_RPCFit_midPhi;
    vector < float >* muon_SA_RPCFit_midSlope;
    vector < float >* muon_SA_RPCFit_midOffset;
    vector < float >* muon_SA_RPCFit_outPhi;
    vector < float >* muon_SA_RPCFit_outSlope;
    vector < float >* muon_SA_RPCFit_outOffset;
    vector < vector < float > >* muon_SA_roadAw;
    vector < vector < float > >* muon_SA_roadBw;
    vector < vector < float > >* muon_SA_zMin;
    vector < vector < float > >* muon_SA_zMax;
    vector < vector < float > >* muon_SA_rMin;
    vector < vector < float > >* muon_SA_rMax;
    vector < vector < float > >* muon_SA_etaMin;
    vector < vector < float > >* muon_SA_etaMax;
    vector < vector < int > >* muon_SA_MDTHit_isOutlier;
    vector < vector < int > >* muon_SA_MDTHit_chamber;
    vector < vector < float > >* muon_SA_MDTHit_r;
    vector < vector < float > >* muon_SA_MDTHit_z;
    vector < vector < float > >* muon_SA_MDTHit_phi;
    vector < vector < float > >* muon_SA_MDTHit_residual;
    vector < vector < float > >* muon_SA_MDTHit_space;
    vector < vector < float > >* muon_SA_MDTHit_sigma;
    vector < int >* muon_CB_HypoPass;
    vector < bool >* muon_CB_OvRmPass;
    vector < double >* muon_CB_pt;
    vector < double >* muon_CB_eta;
    vector < double >* muon_CB_phi;
    vector < int >* muon_EF_pass;
    vector < double >* muon_EF_pt;
    vector < double >* muon_EF_eta;
    vector < double >* muon_EF_phi;

};

#endif

