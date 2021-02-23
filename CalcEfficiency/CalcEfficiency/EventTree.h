#ifndef _TrigMuonAnalysis_EventTree
#define _TrigMuonAnalysis_EventTree

#include <iostream>
#include <fstream>
#include <vector>

#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TLorentzVector.h"

#include "CalcEfficiency/TagAndProbe.h"
#include "CalcEfficiency/Utils.h"

using namespace std;

class EventTree {
	
	public:
	EventTree();
	EventTree( TFile* file, TString name );
	~EventTree();

	TFile* m_file; //!
	TTree* m_tree; //!

  //const int SegmentMaxNumber = 10.;
	
	int initialize( TString outfile );
	//int initialize( TFile* outfile, TTree* outtree );
	int clear();
	int filltree( TagAndProbe& tap, int eventNumber, int runNumber, int lumiBlock, float averageInteractionsPerCrossing );
	int finalize();

    int EventNumber;
    int RunNumber;
    int LumiBlock;
    float AverageInteractionsPerCrossing;
    int mes_n;
    vector < string >* mes_name;
    int tag_proc;
    double sumReqdRL1;
    double sumReqdREF;
    double tag_ReqdRL1;
    double tag_ReqdREF;
    double tag_dRL1;
    double tag_dREF;
    double tag_pt;
    double tag_eta;
    double tag_exteta;
    double tag_extinneta;
    double tag_phi;
    double tag_extphi;
    double tag_extinnphi;
    double tag_d0;
    double tag_z0;
    double tag_charge;
    double tag_L1_pt;
    double tag_L1_eta;
    double tag_L1_phi;
    double tag_SA_pt;
    double tag_SA_eta;
    double tag_SA_phi;
    double tag_CB_pt;
    double tag_CB_eta;
    double tag_CB_phi;
    double tag_EF_pt;
    double tag_EF_eta;
    double tag_EF_phi;
    double probe_pt;
    double probe_MSpt;//kayamash
    double probe_eta;
    double probe_exteta;
    double probe_extinneta;
    double probe_phi;
    double probe_extphi;
    double probe_extinnphi;
    double probe_d0;
    double probe_z0;
    double probe_charge;
    //SegmentMaxNumber is defined in Tagandprobe.h .
    double probe_segment_n;
    double probe_segment_x[SegmentMaxNumber];
    double probe_segment_y[SegmentMaxNumber];
    double probe_segment_z[SegmentMaxNumber];
    double probe_segment_px[SegmentMaxNumber];
    double probe_segment_py[SegmentMaxNumber];
    double probe_segment_pz[SegmentMaxNumber];
    double probe_segment_chiSquared[SegmentMaxNumber];
    double probe_segment_numberDoF[SegmentMaxNumber];
    double probe_segment_sector[SegmentMaxNumber];
    double probe_segment_chamberIndex[SegmentMaxNumber];
    double probe_segment_etaIndex[SegmentMaxNumber];
    double probe_segment_nPrecisionHits[SegmentMaxNumber];
    double probe_segment_nPhiLayers[SegmentMaxNumber];
    double probe_segment_nTrigEtaLayers[SegmentMaxNumber];
    //
    double tp_dR;
    double tp_deta;
    double tp_dphi;
    double tp_extdR;
    double tp_extdeta;
    double tp_extdphi;
    double tp_extinndR;
    double tp_extinndeta;
    double tp_extinndphi;
    double tp_mass;
    double tp_vftlxy;
    double tp_vftchi2;
    int tp_vftndof;
    vector < int >* probe_mesEFTAG_pass;
    vector < double >* probe_mesEFTAG_dR;
    vector < double >* probe_mesEFTAG_tpdR;
    vector < double >* probe_mesEFTAG_pt;
    vector < double >* probe_mesEFTAG_eta;
    vector < double >* probe_mesEFTAG_phi;
    vector < int >* probe_mesL1_pass;
    vector < double >* probe_mesL1_dR;
    vector < double >* probe_mesL1_tpdR;
    vector < double >* probe_mesL1_pt;
    vector < double >* probe_mesL1_eta;
    vector < double >* probe_mesL1_phi;
    vector < int >* probe_mesSA_pass;
    vector < double >* probe_mesSA_dR;
    vector < double >* probe_mesSA_tpdR;
    vector < double >* probe_mesSA_pt;
    vector < double >* probe_mesSA_eta;
    vector < double >* probe_mesSA_phi;
    vector < double >* probe_mesSA_etams;
    vector < double >* probe_mesSA_phims;
    vector < double >* probe_mesSA_etabe;
    vector < double >* probe_mesSA_phibe;

    //pT from different algorithms
    vector < double >* probe_mesSA_tgcpt;
    vector < double >* probe_mesSA_ptBarrelRadius;
    vector < double >* probe_mesSA_ptBarrelSagitta;
    vector < double >* probe_mesSA_ptEndcapAlpha;
    vector < double >* probe_mesSA_ptEndcapBeta;
    vector < double >* probe_mesSA_ptEndcapRadius;
    vector < double >* probe_mesSA_ptCSC;
    vector < double >* probe_mesSA_sAddress;

    vector < float >* probe_mesSA_roiEta;
    vector < float >* probe_mesSA_roiPhi;
    vector < int >* probe_mesSA_isRpcFailure;
    vector < int >* probe_mesSA_isTgcFailure;

    //the measured radious of the muon in one particular super point
    vector < double >* probe_mesSA_superPointR_BI;
    vector < double >* probe_mesSA_superPointR_BM;
    vector < double >* probe_mesSA_superPointR_BO;
    vector < double >* probe_mesSA_superPointR_EI;
    vector < double >* probe_mesSA_superPointR_EM;
    vector < double >* probe_mesSA_superPointR_EO;
    vector < double >* probe_mesSA_superPointR_EE;
    vector < double >* probe_mesSA_superPointR_CSC;
    vector < double >* probe_mesSA_superPointR_BEE;
    vector < double >* probe_mesSA_superPointR_BME;
    //the measured Z position of the muon in one particular super point
    vector < double >* probe_mesSA_superPointZ_BI;
    vector < double >* probe_mesSA_superPointZ_BM;
    vector < double >* probe_mesSA_superPointZ_BO;
    vector < double >* probe_mesSA_superPointZ_EI;
    vector < double >* probe_mesSA_superPointZ_EM;
    vector < double >* probe_mesSA_superPointZ_EO;
    vector < double >* probe_mesSA_superPointZ_EE;
    vector < double >* probe_mesSA_superPointZ_CSC;
    vector < double >* probe_mesSA_superPointZ_BEE;
    vector < double >* probe_mesSA_superPointZ_BME;
    //the measured slope of the muon in one particular super point
    vector < double >* probe_mesSA_superPointSlope_BI;
    vector < double >* probe_mesSA_superPointSlope_BM;
    vector < double >* probe_mesSA_superPointSlope_BO;
    vector < double >* probe_mesSA_superPointSlope_EI;
    vector < double >* probe_mesSA_superPointSlope_EM;
    vector < double >* probe_mesSA_superPointSlope_EO;
    vector < double >* probe_mesSA_superPointSlope_EE;
    vector < double >* probe_mesSA_superPointSlope_CSC;
    vector < double >* probe_mesSA_superPointSlope_BEE;
    vector < double >* probe_mesSA_superPointSlope_BME;
    //the measured intercept of the muon in one particular super point
    vector < double >* probe_mesSA_superPointIntercept_BI;
    vector < double >* probe_mesSA_superPointIntercept_BM;
    vector < double >* probe_mesSA_superPointIntercept_BO;
    vector < double >* probe_mesSA_superPointIntercept_EI;
    vector < double >* probe_mesSA_superPointIntercept_EM;
    vector < double >* probe_mesSA_superPointIntercept_EO;
    vector < double >* probe_mesSA_superPointIntercept_EE;
    vector < double >* probe_mesSA_superPointIntercept_CSC;
    vector < double >* probe_mesSA_superPointIntercept_BEE;
    vector < double >* probe_mesSA_superPointIntercept_BME;
    //the chi2 of the fit in one particular super point
    vector < double >* probe_mesSA_superPointChi2_BI;
    vector < double >* probe_mesSA_superPointChi2_BM;
    vector < double >* probe_mesSA_superPointChi2_BO;
    vector < double >* probe_mesSA_superPointChi2_EI;
    vector < double >* probe_mesSA_superPointChi2_EM;
    vector < double >* probe_mesSA_superPointChi2_EO;
    vector < double >* probe_mesSA_superPointChi2_EE;
    vector < double >* probe_mesSA_superPointChi2_CSC;
    vector < double >* probe_mesSA_superPointChi2_BEE;
    vector < double >* probe_mesSA_superPointChi2_BME;
    //RPC hits
    vector < vector < float > >* probe_mesSA_rpcHitX;
    vector < vector < float > >* probe_mesSA_rpcHitY;
    vector < vector < float > >* probe_mesSA_rpcHitZ;
    vector < vector < double > >* probe_mesSA_rpcHitR;
    vector < vector < double > >* probe_mesSA_rpcHitEta;
    vector < vector < double > >* probe_mesSA_rpcHitPhi;
    vector < vector < double > >* probe_mesSA_rpcHitStationNumber;
    vector < vector < string > >* probe_mesSA_rpcHitStationName;

    vector < vector < int > >* probe_mesSA_mdtHitIsOutlier;
    vector < vector < int > >* probe_mesSA_mdtHitChamber;
    vector < vector < float > >* probe_mesSA_mdtHitR;
    vector < vector < float > >* probe_mesSA_mdtHitZ;
    vector < vector < float > >* probe_mesSA_mdtHitPhi;
    vector < vector < float > >* probe_mesSA_mdtHitResidual;


    vector < vector < float > >* probe_mesSA_roadAw;
    vector < vector < float > >* probe_mesSA_roadBw;
    vector < vector < float > >* probe_mesSA_zMin;
    vector < vector < float > >* probe_mesSA_zMax;
    vector < vector < float > >* probe_mesSA_rMin;
    vector < vector < float > >* probe_mesSA_rMax;
    vector < vector < float > >* probe_mesSA_etaMin;
    vector < vector < float > >* probe_mesSA_etaMax;
    //
    vector < int >* probe_mesCB_pass;
    vector < double >* probe_mesCB_dR;
    vector < double >* probe_mesCB_tpdR;
    vector < double >* probe_mesCB_pt;
    vector < double >* probe_mesCB_eta;
    vector < double >* probe_mesCB_phi;
    vector < int >* probe_mesFTF_pass;
    vector < double >* probe_mesFTF_dR;
    vector < double >* probe_mesFTF_pt;
    vector < double >* probe_mesFTF_eta;
    vector < double >* probe_mesFTF_phi;
    vector < int >* probe_mesEF_pass;
    vector < double >* probe_mesEF_dR;
    vector < double >* probe_mesEF_tpdR;
    vector < double >* probe_mesEF_pt;
    vector < double >* probe_mesEF_eta;
    vector < double >* probe_mesEF_phi;

};

#endif

