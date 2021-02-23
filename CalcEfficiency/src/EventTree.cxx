#include <iostream>
#include <fstream>
#include <vector>

#include "CalcEfficiency/EventTree.h"
#include "CalcEfficiency/Utils.h"

#include "TTree.h"
#include "TFile.h"
#include "TString.h"
#include "TLorentzVector.h"

EventTree::EventTree() {
}

EventTree::~EventTree() {
}

int EventTree::initialize( TString outfile = "test.root" ) {
//int EventTree::initialize( TFile* outfile, TTree* outtree ) 

  //initialize the event tree
  m_file	= new TFile( outfile, "recreate" );
  //m_file	= outfile;
  m_tree 	= new TTree( "t_tap", "TrigMuonTagAndProbe" );
  //m_tree    = outtree;
  //m_tree->SetDirectory( m_file );

  //--------------------------------------------------
  // VARIABLE SET UP
  //--------------------------------------------------
	
  // Event variables
  EventNumber = 0;
  RunNumber = 0;
  LumiBlock = 0;
  AverageInteractionsPerCrossing = 0;
  // Tag and probe variables
  mes_n             = 0;
  mes_name          = new vector < string > ();
  sumReqdRL1        = -99999.;
  sumReqdREF        = -99999.;
  tag_proc          = -99999.;
  tag_proc          = -99999.;
  tag_dRL1          = -99999.;
  tag_dREF          = -99999.;
  tag_ReqdRL1       = -99999.;
  tag_ReqdREF       = -99999.;
  tag_pt            = -99999.;
  tag_eta           = -99999.;
  tag_exteta        = -99999.;
  tag_extinneta     = -99999.;
  tag_phi           = -99999.;
  tag_extphi        = -99999.;
  tag_extinnphi     = -99999.;
  tag_d0            = -99999.;
  tag_z0            = -99999.;
  tag_charge        = -99999.;
  tag_L1_pt         = -99999.;
  tag_L1_eta        = -99999.;
  tag_L1_phi        = -99999.;
  tag_SA_pt         = -99999.;
  tag_SA_eta        = -99999.;
  tag_SA_phi        = -99999.;
  tag_CB_pt         = -99999.;
  tag_CB_eta        = -99999.;
  tag_CB_phi        = -99999.;
  tag_EF_pt         = -99999.;
  tag_EF_eta        = -99999.;
  tag_EF_phi        = -99999.;
  probe_pt          = -99999.;
  probe_MSpt          = -99999.;//kayamash
  probe_eta         = -99999.;
  probe_exteta      = -99999.;
  probe_extinneta   = -99999.;
  probe_phi         = -99999.;
  probe_extphi      = -99999.;
  probe_extinnphi   = -99999.;
  probe_d0          = -99999.;
  probe_z0          = -99999.;
  probe_charge      = -99999.;
  //
  probe_segment_n   = -99999.;
  for(int i = 0 ; i < SegmentMaxNumber ; i++ ){
    //SegmentMaxNumber is defined in Tagandprobe.h .
    probe_segment_x[i]              = -99999.;
    probe_segment_y[i]              = -99999.;
    probe_segment_z[i]              = -99999.;
    probe_segment_px[i]             = -99999.;
    probe_segment_py[i]             = -99999.;
    probe_segment_pz[i]             = -99999.;
    probe_segment_chiSquared[i]     = -99999.;
    probe_segment_numberDoF[i]      = -99999.;
    probe_segment_sector[i]         = -99999.;
    probe_segment_chamberIndex[i]   = -99999.;
    probe_segment_etaIndex[i]       = -99999.;
    probe_segment_nPrecisionHits[i] = -99999.;
    probe_segment_nPhiLayers[i]     = -99999.;
    probe_segment_nTrigEtaLayers[i] = -99999.;
  }
  //
  tp_dR             = -99999.;
  tp_deta           = -99999.;
  tp_dphi           = -99999.;
  tp_extdR          = -99999.;
  tp_extdeta        = -99999.;
  tp_extdphi        = -99999.;
  tp_extinndR       = -99999.;
  tp_extinndeta     = -99999.;
  tp_extinndphi     = -99999.;
  tp_mass           = -99999.;
  tp_vftlxy         = -99999.;
  tp_vftchi2        = -99999.;
  tp_vftndof        = -99999.;
  probe_mesEFTAG_pass  = new vector < int > ();
  probe_mesEFTAG_dR    = new vector < double > ();
  probe_mesEFTAG_tpdR  = new vector < double > ();
  probe_mesEFTAG_pt    = new vector < double > ();
  probe_mesEFTAG_eta   = new vector < double > ();
  probe_mesEFTAG_phi   = new vector < double > ();
  probe_mesL1_pass  = new vector < int > ();
  probe_mesL1_dR    = new vector < double > ();
  probe_mesL1_tpdR  = new vector < double > ();
  probe_mesL1_pt    = new vector < double > ();
  probe_mesL1_eta   = new vector < double > ();
  probe_mesL1_phi   = new vector < double > ();
  probe_mesSA_pass  = new vector < int > ();
  probe_mesSA_dR    = new vector < double > ();
  probe_mesSA_tpdR  = new vector < double > ();
  probe_mesSA_pt    = new vector < double > ();
  probe_mesSA_eta   = new vector < double > ();
  probe_mesSA_phi   = new vector < double > ();
  probe_mesSA_etams = new vector < double > ();
  probe_mesSA_phims = new vector < double > ();
  probe_mesSA_etabe = new vector < double > ();
  probe_mesSA_phibe = new vector < double > ();
  //pT from different algorithms
  probe_mesSA_tgcpt = new vector < double > ();
  probe_mesSA_ptBarrelRadius = new vector < double > ();
  probe_mesSA_ptBarrelSagitta = new vector < double > ();
  probe_mesSA_ptEndcapAlpha = new vector < double > ();
  probe_mesSA_ptEndcapBeta = new vector < double > ();
  probe_mesSA_ptEndcapRadius = new vector < double > ();
  probe_mesSA_ptCSC = new vector < double > ();
  probe_mesSA_sAddress = new vector < double > ();

  probe_mesSA_roiEta = new vector < float > ();
  probe_mesSA_roiPhi = new vector < float > ();
  probe_mesSA_isRpcFailure = new vector < int > ();
  probe_mesSA_isTgcFailure = new vector < int > ();

  //the measured radious of the muon in one particular super point
  probe_mesSA_superPointR_BI  = new vector < double > ();
  probe_mesSA_superPointR_BM  = new vector < double > ();
  probe_mesSA_superPointR_BO  = new vector < double > ();
  probe_mesSA_superPointR_EI  = new vector < double > ();
  probe_mesSA_superPointR_EM  = new vector < double > ();
  probe_mesSA_superPointR_EO  = new vector < double > ();
  probe_mesSA_superPointR_EE  = new vector < double > ();
  probe_mesSA_superPointR_CSC = new vector < double > ();
  probe_mesSA_superPointR_BEE = new vector < double > ();
  probe_mesSA_superPointR_BME = new vector < double > ();
  //the measured Z position of the muon in one particular super point
  probe_mesSA_superPointZ_BI  = new vector < double > ();
  probe_mesSA_superPointZ_BM  = new vector < double > ();
  probe_mesSA_superPointZ_BO  = new vector < double > ();
  probe_mesSA_superPointZ_EI  = new vector < double > ();
  probe_mesSA_superPointZ_EM  = new vector < double > ();
  probe_mesSA_superPointZ_EO  = new vector < double > ();
  probe_mesSA_superPointZ_EE  = new vector < double > ();
  probe_mesSA_superPointZ_CSC = new vector < double > ();
  probe_mesSA_superPointZ_BEE = new vector < double > ();
  probe_mesSA_superPointZ_BME = new vector < double > ();
  //the measured slope of the muon in one particular super point
  probe_mesSA_superPointSlope_BI  = new vector < double > ();
  probe_mesSA_superPointSlope_BM  = new vector < double > ();
  probe_mesSA_superPointSlope_BO  = new vector < double > ();
  probe_mesSA_superPointSlope_EI  = new vector < double > ();
  probe_mesSA_superPointSlope_EM  = new vector < double > ();
  probe_mesSA_superPointSlope_EO  = new vector < double > ();
  probe_mesSA_superPointSlope_EE  = new vector < double > ();
  probe_mesSA_superPointSlope_CSC = new vector < double > ();
  probe_mesSA_superPointSlope_BEE = new vector < double > ();
  probe_mesSA_superPointSlope_BME = new vector < double > ();
  //the measured intercept of the muon in one particular super point
  probe_mesSA_superPointIntercept_BI  = new vector < double > ();
  probe_mesSA_superPointIntercept_BM  = new vector < double > ();
  probe_mesSA_superPointIntercept_BO  = new vector < double > ();
  probe_mesSA_superPointIntercept_EI  = new vector < double > ();
  probe_mesSA_superPointIntercept_EM  = new vector < double > ();
  probe_mesSA_superPointIntercept_EO  = new vector < double > ();
  probe_mesSA_superPointIntercept_EE  = new vector < double > ();
  probe_mesSA_superPointIntercept_CSC = new vector < double > ();
  probe_mesSA_superPointIntercept_BEE = new vector < double > ();
  probe_mesSA_superPointIntercept_BME = new vector < double > ();
  //the chi2 of the muon in one particular super point
  probe_mesSA_superPointChi2_BI  = new vector < double > ();
  probe_mesSA_superPointChi2_BM  = new vector < double > ();
  probe_mesSA_superPointChi2_BO  = new vector < double > ();
  probe_mesSA_superPointChi2_EI  = new vector < double > ();
  probe_mesSA_superPointChi2_EM  = new vector < double > ();
  probe_mesSA_superPointChi2_EO  = new vector < double > ();
  probe_mesSA_superPointChi2_EE  = new vector < double > ();
  probe_mesSA_superPointChi2_CSC = new vector < double > ();
  probe_mesSA_superPointChi2_BEE = new vector < double > ();
  probe_mesSA_superPointChi2_BME = new vector < double > ();
  //
  probe_mesSA_rpcHitX   = new vector < vector < float > > ();
  probe_mesSA_rpcHitY   = new vector < vector < float > > ();
  probe_mesSA_rpcHitZ   = new vector < vector < float > > ();
  probe_mesSA_rpcHitR   = new vector < vector < double > > ();
  probe_mesSA_rpcHitEta = new vector < vector < double > > ();
  probe_mesSA_rpcHitPhi = new vector < vector < double > > ();
  probe_mesSA_rpcHitStationNumber = new vector < vector < double > > ();
  probe_mesSA_rpcHitStationName = new vector < vector < string > > ();

  probe_mesSA_mdtHitIsOutlier = new vector < vector < int > > ();
  probe_mesSA_mdtHitChamber   = new vector < vector < int > > ();
  probe_mesSA_mdtHitR         = new vector < vector < float > > ();
  probe_mesSA_mdtHitZ         = new vector < vector < float > > ();
  probe_mesSA_mdtHitPhi       = new vector < vector < float > > ();
  probe_mesSA_mdtHitResidual  = new vector < vector < float > > ();


  probe_mesSA_roadAw = new vector < vector < float > > ();
  probe_mesSA_roadBw = new vector < vector < float > > ();
  probe_mesSA_zMin   = new vector < vector < float > > ();
  probe_mesSA_zMax   = new vector < vector < float > > ();
  probe_mesSA_rMin   = new vector < vector < float > > ();
  probe_mesSA_rMax   = new vector < vector < float > > ();
  probe_mesSA_etaMin = new vector < vector < float > > ();
  probe_mesSA_etaMax = new vector < vector < float > > ();

  //
  probe_mesCB_pass  = new vector < int > ();
  probe_mesCB_dR    = new vector < double > ();
  probe_mesCB_tpdR  = new vector < double > ();
  probe_mesCB_pt    = new vector < double > ();
  probe_mesCB_eta   = new vector < double > ();
  probe_mesCB_phi   = new vector < double > ();
  probe_mesFTF_pass = new vector < int > ();
  probe_mesFTF_dR   = new vector < double > ();
  probe_mesFTF_pt   = new vector < double > ();
  probe_mesFTF_eta  = new vector < double > ();
  probe_mesFTF_phi  = new vector < double > ();
  probe_mesEF_pass  = new vector < int > ();
  probe_mesEF_dR    = new vector < double > ();
  probe_mesEF_tpdR  = new vector < double > ();
  probe_mesEF_pt    = new vector < double > ();
  probe_mesEF_eta   = new vector < double > ();
  probe_mesEF_phi   = new vector < double > ();
    
  //--------------------------------------------------
  // BRANCH SET UP
  //--------------------------------------------------

  m_tree->Branch( "EventNumber",        &EventNumber );
  m_tree->Branch( "RunNumber",        &RunNumber );
  m_tree->Branch( "LumiBlock",        &LumiBlock );
  m_tree->Branch( "AverageInteractionsPerCrossing",        &AverageInteractionsPerCrossing );

  m_tree->Branch( "mes_n",        &mes_n );
  m_tree->Branch( "mes_name",     &mes_name );
  m_tree->Branch( "sumReqdRL1",   &sumReqdRL1 );
  m_tree->Branch( "sumReqdREF",   &sumReqdREF );
  m_tree->Branch( "tag_proc",     &tag_proc );
  m_tree->Branch( "tag_ReqdRL1",  &tag_ReqdRL1 );
  m_tree->Branch( "tag_ReqdREF",  &tag_ReqdREF );
  m_tree->Branch( "tag_dRL1",     &tag_dRL1 );
  m_tree->Branch( "tag_dREF",     &tag_dREF );
  m_tree->Branch( "tag_pt",       &tag_pt );
  m_tree->Branch( "tag_eta",      &tag_eta );
  m_tree->Branch( "tag_exteta",   &tag_exteta );
  m_tree->Branch( "tag_extinneta",&tag_extinneta );
  m_tree->Branch( "tag_phi",      &tag_phi );
  m_tree->Branch( "tag_extphi",   &tag_extphi );
  m_tree->Branch( "tag_extinnphi",&tag_extinnphi );
  m_tree->Branch( "tag_d0",       &tag_d0 );
  m_tree->Branch( "tag_z0",       &tag_z0 );
  m_tree->Branch( "tag_charge",   &tag_charge );
  m_tree->Branch( "tag_L1_pt",    &tag_L1_pt );
  m_tree->Branch( "tag_L1_eta",   &tag_L1_eta );
  m_tree->Branch( "tag_L1_phi",   &tag_L1_phi );
  m_tree->Branch( "tag_SA_pt",    &tag_SA_pt );
  m_tree->Branch( "tag_SA_eta",   &tag_SA_eta );
  m_tree->Branch( "tag_SA_phi",   &tag_SA_phi );
  m_tree->Branch( "tag_CB_pt",    &tag_CB_pt );
  m_tree->Branch( "tag_CB_eta",   &tag_CB_eta );
  m_tree->Branch( "tag_CB_phi",   &tag_CB_phi );
  m_tree->Branch( "tag_EF_pt",    &tag_EF_pt );
  m_tree->Branch( "tag_EF_eta",         &tag_EF_eta );
  m_tree->Branch( "tag_EF_phi",         &tag_EF_phi );
  m_tree->Branch( "probe_pt",           &probe_pt );
  m_tree->Branch( "probe_MSpt",           &probe_MSpt );//kayamash
  m_tree->Branch( "probe_eta",          &probe_eta );
  m_tree->Branch( "probe_exteta",       &probe_exteta );
  m_tree->Branch( "probe_extinneta",    &probe_extinneta );
  m_tree->Branch( "probe_phi",          &probe_phi );
  m_tree->Branch( "probe_extphi",       &probe_extphi );
  m_tree->Branch( "probe_extinnphi",    &probe_extinnphi );
  m_tree->Branch( "probe_d0",           &probe_d0 );
  m_tree->Branch( "probe_z0",           &probe_z0 );
  m_tree->Branch( "probe_charge",       &probe_charge );
  //
  const int Segment_Max_Number = SegmentMaxNumber;
  m_tree->Branch( "probe_segment_n",    &probe_segment_n );
  m_tree->Branch( "probe_segment_x",              probe_segment_x,              Form("probe_segment_x[%d]/D",Segment_Max_Number) );
  m_tree->Branch( "probe_segment_y",              probe_segment_y,              Form("probe_segment_y[%d]/D",Segment_Max_Number) );
  m_tree->Branch( "probe_segment_z",              probe_segment_z,              Form("probe_segment_z[%d]/D",Segment_Max_Number) );
  m_tree->Branch( "probe_segment_px",             probe_segment_px,             Form("probe_segment_px[%d]/D",Segment_Max_Number) );
  m_tree->Branch( "probe_segment_py",             probe_segment_py,             Form("probe_segment_py[%d]/D",Segment_Max_Number) );
  m_tree->Branch( "probe_segment_pz",             probe_segment_pz,             Form("probe_segment_pz[%d]/D",Segment_Max_Number) );
  m_tree->Branch( "probe_segment_chiSquared",     probe_segment_chiSquared,     Form("probe_segment_chiSquared[%d]/D",Segment_Max_Number) );
  m_tree->Branch( "probe_segment_numberDoF",      probe_segment_numberDoF,      Form("probe_segment_numberDoF[%d]/D",Segment_Max_Number) );
  m_tree->Branch( "probe_segment_sector",         probe_segment_sector,         Form("probe_segment_sector[%d]/D",Segment_Max_Number) );
  m_tree->Branch( "probe_segment_chamberIndex",   probe_segment_chamberIndex,   Form("probe_segment_chamberIndex[%d]/D",Segment_Max_Number) );
  m_tree->Branch( "probe_segment_etaIndex",       probe_segment_etaIndex,       Form("probe_segment_etaIndex[%d]/D",Segment_Max_Number) );
  m_tree->Branch( "probe_segment_nPrecisionHits", probe_segment_nPrecisionHits, Form("probe_segment_nPrecisionHits[%d]/D",Segment_Max_Number) );
  m_tree->Branch( "probe_segment_nPhiLayers",     probe_segment_nPhiLayers,     Form("probe_segment_nPhiLayers[%d]/D",Segment_Max_Number) );
  m_tree->Branch( "probe_segment_nTrigEtaLayers", probe_segment_nTrigEtaLayers, Form("probe_segment_nTrigEtaLayers[%d]/D",Segment_Max_Number) );
  //
  m_tree->Branch( "tp_dR",              &tp_dR );
  m_tree->Branch( "tp_deta",            &tp_deta );
  m_tree->Branch( "tp_dphi",            &tp_dphi );
  m_tree->Branch( "tp_extdR",           &tp_extdR );
  m_tree->Branch( "tp_extdeta",         &tp_extdeta );
  m_tree->Branch( "tp_extdphi",         &tp_extdphi );
  m_tree->Branch( "tp_extinndR",        &tp_extinndR );
  m_tree->Branch( "tp_extinndeta",      &tp_extinndeta );
  m_tree->Branch( "tp_extinndphi",      &tp_extinndphi );
  m_tree->Branch( "tp_mass",            &tp_mass );
  m_tree->Branch( "tp_vftlxy",          &tp_vftlxy );
  m_tree->Branch( "tp_vftchi2",         &tp_vftchi2 );
  m_tree->Branch( "tp_vftndof",         &tp_vftndof );
  m_tree->Branch( "probe_mesEFTAG_pass",   &probe_mesEFTAG_pass );
  m_tree->Branch( "probe_mesEFTAG_dR",     &probe_mesEFTAG_dR );
  m_tree->Branch( "probe_mesEFTAG_tpdR",   &probe_mesEFTAG_tpdR );
  m_tree->Branch( "probe_mesEFTAG_pt",     &probe_mesEFTAG_pt );
  m_tree->Branch( "probe_mesEFTAG_eta",    &probe_mesEFTAG_eta );
  m_tree->Branch( "probe_mesEFTAG_phi",    &probe_mesEFTAG_phi );
  m_tree->Branch( "probe_mesL1_pass",   &probe_mesL1_pass );
  m_tree->Branch( "probe_mesL1_dR",     &probe_mesL1_dR );
  m_tree->Branch( "probe_mesL1_tpdR",   &probe_mesL1_tpdR );
  m_tree->Branch( "probe_mesL1_pt",     &probe_mesL1_pt );
  m_tree->Branch( "probe_mesL1_eta",    &probe_mesL1_eta );
  m_tree->Branch( "probe_mesL1_phi",    &probe_mesL1_phi );
  m_tree->Branch( "probe_mesSA_pass",   &probe_mesSA_pass );
  m_tree->Branch( "probe_mesSA_dR",     &probe_mesSA_dR );
  m_tree->Branch( "probe_mesSA_tpdR",   &probe_mesSA_tpdR );
  m_tree->Branch( "probe_mesSA_pt",     &probe_mesSA_pt );
  m_tree->Branch( "probe_mesSA_eta",    &probe_mesSA_eta );
  m_tree->Branch( "probe_mesSA_phi",    &probe_mesSA_phi );
  m_tree->Branch( "probe_mesSA_etams",  &probe_mesSA_etams );
  m_tree->Branch( "probe_mesSA_phims",  &probe_mesSA_phims );
  m_tree->Branch( "probe_mesSA_etabe",  &probe_mesSA_etabe );
  m_tree->Branch( "probe_mesSA_phibe",  &probe_mesSA_phibe );
  //
  m_tree->Branch( "probe_mesSA_tgcpt",  &probe_mesSA_tgcpt );
  m_tree->Branch( "probe_mesSA_ptBarrelRadius",  &probe_mesSA_ptBarrelRadius );
  m_tree->Branch( "probe_mesSA_ptBarrelSagitta",  &probe_mesSA_ptBarrelSagitta );
  m_tree->Branch( "probe_mesSA_ptEndcapAlpha",  &probe_mesSA_ptEndcapAlpha );
  m_tree->Branch( "probe_mesSA_ptEndcapBeta",  &probe_mesSA_ptEndcapBeta );
  m_tree->Branch( "probe_mesSA_ptEndcapRadius",  &probe_mesSA_ptEndcapRadius );
  m_tree->Branch( "probe_mesSA_ptCSC",  &probe_mesSA_ptCSC );
  m_tree->Branch( "probe_mesSA_sAddress",  &probe_mesSA_sAddress );


  m_tree->Branch( "probe_mesSA_roiEta",  &probe_mesSA_roiEta );
  m_tree->Branch( "probe_mesSA_roiPhi",  &probe_mesSA_roiPhi );
  m_tree->Branch( "probe_mesSA_isRpcFailure",  &probe_mesSA_isRpcFailure );
  m_tree->Branch( "probe_mesSA_isTgcFailure",  &probe_mesSA_isTgcFailure );
  //
  m_tree->Branch( "probe_mesSA_superPointR_BI",   &probe_mesSA_superPointR_BI );
  m_tree->Branch( "probe_mesSA_superPointR_BM",   &probe_mesSA_superPointR_BM );
  m_tree->Branch( "probe_mesSA_superPointR_BO",   &probe_mesSA_superPointR_BO );
  m_tree->Branch( "probe_mesSA_superPointR_EI",   &probe_mesSA_superPointR_EI );
  m_tree->Branch( "probe_mesSA_superPointR_EM",   &probe_mesSA_superPointR_EM );
  m_tree->Branch( "probe_mesSA_superPointR_EO",   &probe_mesSA_superPointR_EO );
  m_tree->Branch( "probe_mesSA_superPointR_EE",   &probe_mesSA_superPointR_EE );
  m_tree->Branch( "probe_mesSA_superPointR_CSC",  &probe_mesSA_superPointR_CSC );
  m_tree->Branch( "probe_mesSA_superPointR_BEE",  &probe_mesSA_superPointR_BEE );
  m_tree->Branch( "probe_mesSA_superPointR_BME",  &probe_mesSA_superPointR_BME );
  //
  m_tree->Branch( "probe_mesSA_superPointZ_BI",   &probe_mesSA_superPointZ_BI );
  m_tree->Branch( "probe_mesSA_superPointZ_BM",   &probe_mesSA_superPointZ_BM );
  m_tree->Branch( "probe_mesSA_superPointZ_BO",   &probe_mesSA_superPointZ_BO );
  m_tree->Branch( "probe_mesSA_superPointZ_EI",   &probe_mesSA_superPointZ_EI );
  m_tree->Branch( "probe_mesSA_superPointZ_EM",   &probe_mesSA_superPointZ_EM );
  m_tree->Branch( "probe_mesSA_superPointZ_EO",   &probe_mesSA_superPointZ_EO );
  m_tree->Branch( "probe_mesSA_superPointZ_EE",   &probe_mesSA_superPointZ_EE );
  m_tree->Branch( "probe_mesSA_superPointZ_CSC",  &probe_mesSA_superPointZ_CSC );
  m_tree->Branch( "probe_mesSA_superPointZ_BEE",  &probe_mesSA_superPointZ_BEE );
  m_tree->Branch( "probe_mesSA_superPointZ_BME",  &probe_mesSA_superPointZ_BME );
  //
  m_tree->Branch( "probe_mesSA_superPointSlope_BI",   &probe_mesSA_superPointSlope_BI );
  m_tree->Branch( "probe_mesSA_superPointSlope_BM",   &probe_mesSA_superPointSlope_BM );
  m_tree->Branch( "probe_mesSA_superPointSlope_BO",   &probe_mesSA_superPointSlope_BO );
  m_tree->Branch( "probe_mesSA_superPointSlope_EI",   &probe_mesSA_superPointSlope_EI );
  m_tree->Branch( "probe_mesSA_superPointSlope_EM",   &probe_mesSA_superPointSlope_EM );
  m_tree->Branch( "probe_mesSA_superPointSlope_EO",   &probe_mesSA_superPointSlope_EO );
  m_tree->Branch( "probe_mesSA_superPointSlope_EE",   &probe_mesSA_superPointSlope_EE );
  m_tree->Branch( "probe_mesSA_superPointSlope_CSC",  &probe_mesSA_superPointSlope_CSC );
  m_tree->Branch( "probe_mesSA_superPointSlope_BEE",  &probe_mesSA_superPointSlope_BEE );
  m_tree->Branch( "probe_mesSA_superPointSlope_BME",  &probe_mesSA_superPointSlope_BME );
  //
  m_tree->Branch( "probe_mesSA_superPointIntercept_BI",   &probe_mesSA_superPointIntercept_BI );
  m_tree->Branch( "probe_mesSA_superPointIntercept_BM",   &probe_mesSA_superPointIntercept_BM );
  m_tree->Branch( "probe_mesSA_superPointIntercept_BO",   &probe_mesSA_superPointIntercept_BO );
  m_tree->Branch( "probe_mesSA_superPointIntercept_EI",   &probe_mesSA_superPointIntercept_EI );
  m_tree->Branch( "probe_mesSA_superPointIntercept_EM",   &probe_mesSA_superPointIntercept_EM );
  m_tree->Branch( "probe_mesSA_superPointIntercept_EO",   &probe_mesSA_superPointIntercept_EO );
  m_tree->Branch( "probe_mesSA_superPointIntercept_EE",   &probe_mesSA_superPointIntercept_EE );
  m_tree->Branch( "probe_mesSA_superPointIntercept_CSC",  &probe_mesSA_superPointIntercept_CSC );
  m_tree->Branch( "probe_mesSA_superPointIntercept_BEE",  &probe_mesSA_superPointIntercept_BEE );
  m_tree->Branch( "probe_mesSA_superPointIntercept_BME",  &probe_mesSA_superPointIntercept_BME );
  //
  m_tree->Branch( "probe_mesSA_superPointChi2_BI",   &probe_mesSA_superPointChi2_BI );
  m_tree->Branch( "probe_mesSA_superPointChi2_BM",   &probe_mesSA_superPointChi2_BM );
  m_tree->Branch( "probe_mesSA_superPointChi2_BO",   &probe_mesSA_superPointChi2_BO );
  m_tree->Branch( "probe_mesSA_superPointChi2_EI",   &probe_mesSA_superPointChi2_EI );
  m_tree->Branch( "probe_mesSA_superPointChi2_EM",   &probe_mesSA_superPointChi2_EM );
  m_tree->Branch( "probe_mesSA_superPointChi2_EO",   &probe_mesSA_superPointChi2_EO );
  m_tree->Branch( "probe_mesSA_superPointChi2_EE",   &probe_mesSA_superPointChi2_EE );
  m_tree->Branch( "probe_mesSA_superPointChi2_CSC",  &probe_mesSA_superPointChi2_CSC );
  m_tree->Branch( "probe_mesSA_superPointChi2_BEE",  &probe_mesSA_superPointChi2_BEE );
  m_tree->Branch( "probe_mesSA_superPointChi2_BME",  &probe_mesSA_superPointChi2_BME );
  // 
  m_tree->Branch( "probe_mesSA_rpcHitX",  &probe_mesSA_rpcHitX );
  m_tree->Branch( "probe_mesSA_rpcHitY",  &probe_mesSA_rpcHitY );
  m_tree->Branch( "probe_mesSA_rpcHitZ",  &probe_mesSA_rpcHitZ );
  m_tree->Branch( "probe_mesSA_rpcHitR",  &probe_mesSA_rpcHitR );
  m_tree->Branch( "probe_mesSA_rpcHitEta",  &probe_mesSA_rpcHitEta );
  m_tree->Branch( "probe_mesSA_rpcHitPhi",  &probe_mesSA_rpcHitPhi );
  m_tree->Branch( "probe_mesSA_rpcHitStationNumber",  &probe_mesSA_rpcHitStationNumber );
  m_tree->Branch( "probe_mesSA_rpcHitStationName",  &probe_mesSA_rpcHitStationName );
  //
  m_tree->Branch( "probe_mesSA_mdtHitIsOutlier", &probe_mesSA_mdtHitIsOutlier );
  m_tree->Branch( "probe_mesSA_mdtHitChamber",   &probe_mesSA_mdtHitChamber   );
  m_tree->Branch( "probe_mesSA_mdtHitR",         &probe_mesSA_mdtHitR         );
  m_tree->Branch( "probe_mesSA_mdtHitZ",         &probe_mesSA_mdtHitZ         );
  m_tree->Branch( "probe_mesSA_mdtHitPhi",       &probe_mesSA_mdtHitPhi       );
  m_tree->Branch( "probe_mesSA_mdtHitResidual",  &probe_mesSA_mdtHitResidual  );

  //
  m_tree->Branch( "probe_mesSA_roadAw",  &probe_mesSA_roadAw );
  m_tree->Branch( "probe_mesSA_roadBw",  &probe_mesSA_roadBw );
  m_tree->Branch( "probe_mesSA_zMin",  &probe_mesSA_zMin );
  m_tree->Branch( "probe_mesSA_zMax",  &probe_mesSA_zMax );
  m_tree->Branch( "probe_mesSA_rMin",  &probe_mesSA_rMin );
  m_tree->Branch( "probe_mesSA_rMax",  &probe_mesSA_rMax );
  m_tree->Branch( "probe_mesSA_etaMin",  &probe_mesSA_etaMin );
  m_tree->Branch( "probe_mesSA_etaMax",  &probe_mesSA_etaMax );
  //
  m_tree->Branch( "probe_mesCB_pass",   &probe_mesCB_pass );
  m_tree->Branch( "probe_mesCB_dR",     &probe_mesCB_dR );
  m_tree->Branch( "probe_mesCB_tpdR",   &probe_mesCB_tpdR );
  m_tree->Branch( "probe_mesCB_pt",     &probe_mesCB_pt );
  m_tree->Branch( "probe_mesCB_eta",    &probe_mesCB_eta );
  m_tree->Branch( "probe_mesCB_phi",    &probe_mesCB_phi );
  m_tree->Branch( "probe_mesFTF_pass",  &probe_mesFTF_pass );
  m_tree->Branch( "probe_mesFTF_dR",    &probe_mesFTF_dR );
  m_tree->Branch( "probe_mesFTF_pt",    &probe_mesFTF_pt );
  m_tree->Branch( "probe_mesFTF_eta",   &probe_mesFTF_eta );
  m_tree->Branch( "probe_mesFTF_phi",   &probe_mesFTF_phi );
  m_tree->Branch( "probe_mesEF_pass",   &probe_mesEF_pass );
  m_tree->Branch( "probe_mesEF_dR",     &probe_mesEF_dR );
  m_tree->Branch( "probe_mesEF_tpdR",   &probe_mesEF_tpdR );
  m_tree->Branch( "probe_mesEF_pt",     &probe_mesEF_pt );
  m_tree->Branch( "probe_mesEF_eta",    &probe_mesEF_eta );
  m_tree->Branch( "probe_mesEF_phi",    &probe_mesEF_phi );
  return 1;
}

EventTree::EventTree(TFile *file, TString name )
{
  m_tree=(TTree*)file->Get( name );
	
  //--------------------------------------------------
  // VARIABLE SET UP
  //--------------------------------------------------
  
  // Event variables
  EventNumber = 0;
  RunNumber = 0;
  LumiBlock = 0;
  AverageInteractionsPerCrossing = 0;
  // Tag and probe variables
  mes_n             = 0;
  mes_name          = new vector < string > ();
  sumReqdRL1        = -99999.;
  sumReqdREF        = -99999.;
  tag_proc          = -99999.;
  tag_ReqdRL1       = -99999.;
  tag_ReqdREF       = -99999.;
  tag_dRL1          = -99999.;
  tag_dREF          = -99999.;
  tag_pt            = -99999.;
  tag_eta           = -99999.;
  tag_exteta        = -99999.;
  tag_extinneta     = -99999.;
  tag_phi           = -99999.;
  tag_extphi        = -99999.;
  tag_extinnphi     = -99999.;
  tag_d0            = -99999.;
  tag_z0            = -99999.;
  tag_charge        = -99999.;
  tag_L1_pt         = -99999.;
  tag_L1_eta        = -99999.;
  tag_L1_phi        = -99999.;
  tag_SA_pt         = -99999.;
  tag_SA_eta        = -99999.;
  tag_SA_phi        = -99999.;
  tag_CB_pt         = -99999.;
  tag_CB_eta        = -99999.;
  tag_CB_phi        = -99999.;
  tag_EF_pt         = -99999.;
  tag_EF_eta        = -99999.;
  tag_EF_phi        = -99999.;
  probe_pt          = -99999.;
  probe_MSpt          = -99999.;//kayamash
  probe_eta         = -99999.;
  probe_exteta      = -99999.;
  probe_extinneta   = -99999.;
  probe_phi         = -99999.;
  probe_extphi      = -99999.;
  probe_extinnphi   = -99999.;
  probe_d0          = -99999.;
  probe_z0          = -99999.;
  probe_charge      = -99999.;
  //
  probe_segment_n   = -99999.;

  for(int i = 0 ; i < SegmentMaxNumber ; i++ ){
    probe_segment_x[i]              = -99999.;
    probe_segment_y[i]              = -99999.;
    probe_segment_z[i]              = -99999.;
    probe_segment_px[i]             = -99999.;
    probe_segment_py[i]             = -99999.;
    probe_segment_pz[i]             = -99999.;
    probe_segment_chiSquared[i]     = -99999.;
    probe_segment_numberDoF[i]      = -99999.;
    probe_segment_sector[i]         = -99999.;
    probe_segment_chamberIndex[i]   = -99999.;
    probe_segment_etaIndex[i]       = -99999.;
    probe_segment_nPrecisionHits[i] = -99999.;
    probe_segment_nPhiLayers[i]     = -99999.;
    probe_segment_nTrigEtaLayers[i] = -99999.;
  }
  //
  tp_dR             = -99999.;
  tp_deta           = -99999.;
  tp_dphi           = -99999.;
  tp_extdR          = -99999.;
  tp_extdeta        = -99999.;
  tp_extdphi        = -99999.;
  tp_extinndR       = -99999.;
  tp_extinndeta     = -99999.;
  tp_extinndphi     = -99999.;
  tp_mass           = -99999.;
  tp_vftlxy         = -99999.;
  tp_vftchi2        = -99999.;
  tp_vftndof        = -99999.;
  probe_mesEFTAG_pass  = new vector < int > ();
  probe_mesEFTAG_dR    = new vector < double > ();
  probe_mesEFTAG_tpdR  = new vector < double > ();
  probe_mesEFTAG_pt    = new vector < double > ();
  probe_mesEFTAG_eta   = new vector < double > ();
  probe_mesEFTAG_phi   = new vector < double > ();
  probe_mesL1_pass  = new vector < int > ();
  probe_mesL1_dR    = new vector < double > ();
  probe_mesL1_tpdR  = new vector < double > ();
  probe_mesL1_pt    = new vector < double > ();
  probe_mesL1_eta   = new vector < double > ();
  probe_mesL1_phi   = new vector < double > ();
  probe_mesSA_pass  = new vector < int > ();
  probe_mesSA_dR    = new vector < double > ();
  probe_mesSA_tpdR  = new vector < double > ();
  probe_mesSA_pt    = new vector < double > ();
  probe_mesSA_eta   = new vector < double > ();
  probe_mesSA_phi   = new vector < double > ();
  probe_mesSA_etams = new vector < double > ();
  probe_mesSA_phims = new vector < double > ();
  probe_mesSA_etabe = new vector < double > ();
  probe_mesSA_phibe = new vector < double > ();
  //
  probe_mesSA_tgcpt = new vector < double > ();
  probe_mesSA_ptBarrelRadius = new vector < double > ();
  probe_mesSA_ptBarrelSagitta  = new vector < double > ();
  probe_mesSA_ptEndcapAlpha  = new vector < double > ();
  probe_mesSA_ptEndcapBeta  = new vector < double > ();
  probe_mesSA_ptEndcapRadius  = new vector < double > ();
  probe_mesSA_ptCSC  = new vector < double > ();
  probe_mesSA_sAddress = new vector < double > ();

  probe_mesSA_roiEta = new vector < float > ();
  probe_mesSA_roiPhi = new vector < float > ();
  probe_mesSA_isRpcFailure = new vector < int > ();
  probe_mesSA_isTgcFailure = new vector < int > ();

  //
  probe_mesSA_superPointR_BI  = new vector < double > ();
  probe_mesSA_superPointR_BM  = new vector < double > ();
  probe_mesSA_superPointR_BO  = new vector < double > ();
  probe_mesSA_superPointR_EI  = new vector < double > ();
  probe_mesSA_superPointR_EM  = new vector < double > ();
  probe_mesSA_superPointR_EO  = new vector < double > ();
  probe_mesSA_superPointR_EE  = new vector < double > ();
  probe_mesSA_superPointR_CSC = new vector < double > ();
  probe_mesSA_superPointR_BEE = new vector < double > ();
  probe_mesSA_superPointR_BME = new vector < double > ();
  //
  probe_mesSA_superPointZ_BI  = new vector < double > ();
  probe_mesSA_superPointZ_BM  = new vector < double > ();
  probe_mesSA_superPointZ_BO  = new vector < double > ();
  probe_mesSA_superPointZ_EI  = new vector < double > ();
  probe_mesSA_superPointZ_EM  = new vector < double > ();
  probe_mesSA_superPointZ_EO  = new vector < double > ();
  probe_mesSA_superPointZ_EE  = new vector < double > ();
  probe_mesSA_superPointZ_CSC = new vector < double > ();
  probe_mesSA_superPointZ_BEE = new vector < double > ();
  probe_mesSA_superPointZ_BME = new vector < double > ();
  //
  probe_mesSA_superPointSlope_BI  = new vector < double > ();
  probe_mesSA_superPointSlope_BM  = new vector < double > ();
  probe_mesSA_superPointSlope_BO  = new vector < double > ();
  probe_mesSA_superPointSlope_EI  = new vector < double > ();
  probe_mesSA_superPointSlope_EM  = new vector < double > ();
  probe_mesSA_superPointSlope_EO  = new vector < double > ();
  probe_mesSA_superPointSlope_EE  = new vector < double > ();
  probe_mesSA_superPointSlope_CSC = new vector < double > ();
  probe_mesSA_superPointSlope_BEE = new vector < double > ();
  probe_mesSA_superPointSlope_BME = new vector < double > ();
  //
  probe_mesSA_superPointIntercept_BI  = new vector < double > ();
  probe_mesSA_superPointIntercept_BM  = new vector < double > ();
  probe_mesSA_superPointIntercept_BO  = new vector < double > ();
  probe_mesSA_superPointIntercept_EI  = new vector < double > ();
  probe_mesSA_superPointIntercept_EM  = new vector < double > ();
  probe_mesSA_superPointIntercept_EO  = new vector < double > ();
  probe_mesSA_superPointIntercept_EE  = new vector < double > ();
  probe_mesSA_superPointIntercept_CSC = new vector < double > ();
  probe_mesSA_superPointIntercept_BEE = new vector < double > ();
  probe_mesSA_superPointIntercept_BME = new vector < double > ();
  //
  probe_mesSA_superPointChi2_BI  = new vector < double > ();
  probe_mesSA_superPointChi2_BM  = new vector < double > ();
  probe_mesSA_superPointChi2_BO  = new vector < double > ();
  probe_mesSA_superPointChi2_EI  = new vector < double > ();
  probe_mesSA_superPointChi2_EM  = new vector < double > ();
  probe_mesSA_superPointChi2_EO  = new vector < double > ();
  probe_mesSA_superPointChi2_EE  = new vector < double > ();
  probe_mesSA_superPointChi2_CSC = new vector < double > ();
  probe_mesSA_superPointChi2_BEE = new vector < double > ();
  probe_mesSA_superPointChi2_BME = new vector < double > ();
  // 
  probe_mesSA_rpcHitX = new vector < vector < float > > ();
  probe_mesSA_rpcHitY = new vector < vector < float > > ();
  probe_mesSA_rpcHitZ = new vector < vector < float > > ();
  probe_mesSA_rpcHitR = new vector < vector < double > > ();
  probe_mesSA_rpcHitEta = new vector < vector < double > > ();
  probe_mesSA_rpcHitPhi = new vector < vector < double > > ();
  probe_mesSA_rpcHitStationNumber = new vector < vector < double > > ();
  probe_mesSA_rpcHitStationName = new vector < vector < string > > ();
  //
  probe_mesSA_mdtHitIsOutlier = new vector < vector < int > > ();
  probe_mesSA_mdtHitChamber   = new vector < vector < int > > ();
  probe_mesSA_mdtHitR         = new vector < vector < float > > ();
  probe_mesSA_mdtHitZ         = new vector < vector < float > > ();
  probe_mesSA_mdtHitPhi       = new vector < vector < float > > ();
  probe_mesSA_mdtHitResidual  = new vector < vector < float > > ();

  probe_mesSA_roadAw = new vector < vector < float > > ();
  probe_mesSA_roadBw = new vector < vector < float > > ();
  probe_mesSA_zMin   = new vector < vector < float > > ();
  probe_mesSA_zMax   = new vector < vector < float > > ();
  probe_mesSA_rMin   = new vector < vector < float > > ();
  probe_mesSA_rMax   = new vector < vector < float > > ();
  probe_mesSA_etaMin = new vector < vector < float > > ();
  probe_mesSA_etaMax = new vector < vector < float > > ();
  //
  probe_mesCB_pass  = new vector < int > ();
  probe_mesCB_tpdR  = new vector < double > ();
  probe_mesCB_pt    = new vector < double > ();
  probe_mesCB_eta   = new vector < double > ();
  probe_mesCB_phi   = new vector < double > ();
  probe_mesFTF_pass = new vector < int > ();
  probe_mesFTF_dR   = new vector < double > ();
  probe_mesFTF_pt   = new vector < double > ();
  probe_mesFTF_eta  = new vector < double > ();
  probe_mesFTF_phi  = new vector < double > ();
  probe_mesEF_pass  = new vector < int > ();
  probe_mesEF_tpdR  = new vector < double > ();
  probe_mesEF_pt    = new vector < double > ();
  probe_mesEF_eta   = new vector < double > ();
  probe_mesEF_phi   = new vector < double > ();
    
  //--------------------------------------------------
  // BRANCH SET UP
  //--------------------------------------------------
  m_tree->SetBranchAddress("EventNumber", &EventNumber);
  m_tree->SetBranchAddress("RunNumber", &RunNumber);
  m_tree->SetBranchAddress("LumiBlock", &LumiBlock);
  m_tree->SetBranchAddress("AverageInteractionsPerCrossing", &AverageInteractionsPerCrossing);
	
  m_tree->SetBranchAddress( "mes_n",        &mes_n );
  m_tree->SetBranchAddress( "mes_name",     &mes_name );
  m_tree->SetBranchAddress( "sumReqdRL1",   &sumReqdRL1 );
  m_tree->SetBranchAddress( "sumReqdREF",   &sumReqdREF );
  m_tree->SetBranchAddress( "tag_proc",     &tag_proc );
  m_tree->SetBranchAddress( "tag_ReqdRL1",  &tag_ReqdRL1 );
  m_tree->SetBranchAddress( "tag_ReqdREF",  &tag_ReqdREF );
  m_tree->SetBranchAddress( "tag_dRL1",     &tag_dRL1 );
  m_tree->SetBranchAddress( "tag_dREF",     &tag_dREF );
  m_tree->SetBranchAddress( "tag_pt",       &tag_pt );
  m_tree->SetBranchAddress( "tag_eta",      &tag_eta );
  m_tree->SetBranchAddress( "tag_exteta",   &tag_exteta );
  m_tree->SetBranchAddress( "tag_extinneta",&tag_extinneta );
  m_tree->SetBranchAddress( "tag_phi",      &tag_phi );
  m_tree->SetBranchAddress( "tag_extphi",   &tag_extphi );
  m_tree->SetBranchAddress( "tag_extinnphi",&tag_extinnphi );
  m_tree->SetBranchAddress( "tag_d0",       &tag_d0 );
  m_tree->SetBranchAddress( "tag_z0",       &tag_z0 );
  m_tree->SetBranchAddress( "tag_charge",   &tag_charge );
  m_tree->SetBranchAddress( "tag_L1_pt",    &tag_L1_pt );
  m_tree->SetBranchAddress( "tag_L1_eta",   &tag_L1_eta );
  m_tree->SetBranchAddress( "tag_L1_phi",   &tag_L1_phi );
  m_tree->SetBranchAddress( "tag_SA_pt",    &tag_SA_pt );
  m_tree->SetBranchAddress( "tag_SA_eta",   &tag_SA_eta );
  m_tree->SetBranchAddress( "tag_SA_phi",   &tag_SA_phi );
  m_tree->SetBranchAddress( "tag_CB_pt",    &tag_CB_pt );
  m_tree->SetBranchAddress( "tag_CB_eta",   &tag_CB_eta );
  m_tree->SetBranchAddress( "tag_CB_phi",   &tag_CB_phi );
  m_tree->SetBranchAddress( "tag_EF_pt",    &tag_EF_pt );
  m_tree->SetBranchAddress( "tag_EF_eta",   &tag_EF_eta );
  m_tree->SetBranchAddress( "tag_EF_phi",   &tag_EF_phi );
  m_tree->SetBranchAddress( "probe_pt",     &probe_pt );
  m_tree->SetBranchAddress( "probe_MSpt",     &probe_MSpt );//kayamash
  m_tree->SetBranchAddress( "probe_eta",    &probe_eta );
  m_tree->SetBranchAddress( "probe_exteta",       &probe_exteta );
  m_tree->SetBranchAddress( "probe_extinneta",    &probe_extinneta );
  m_tree->SetBranchAddress( "probe_phi",          &probe_phi );
  m_tree->SetBranchAddress( "probe_extphi",       &probe_extphi );
  m_tree->SetBranchAddress( "probe_extinnphi",    &probe_extinnphi );
  m_tree->SetBranchAddress( "probe_d0",           &probe_d0 );
  m_tree->SetBranchAddress( "probe_z0",           &probe_z0 );
  m_tree->SetBranchAddress( "probe_charge",       &probe_charge );
  //
  m_tree->SetBranchAddress( "probe_segment_n",       &probe_segment_n );
  m_tree->SetBranchAddress( "probe_segment_x",              probe_segment_x );
  m_tree->SetBranchAddress( "probe_segment_y",              probe_segment_y );
  m_tree->SetBranchAddress( "probe_segment_z",              probe_segment_z );
  m_tree->SetBranchAddress( "probe_segment_px",             probe_segment_px );
  m_tree->SetBranchAddress( "probe_segment_py",             probe_segment_py );
  m_tree->SetBranchAddress( "probe_segment_pz",             probe_segment_pz );
  m_tree->SetBranchAddress( "probe_segment_chiSquared",     probe_segment_chiSquared );
  m_tree->SetBranchAddress( "probe_segment_numberDoF",      probe_segment_numberDoF );
  m_tree->SetBranchAddress( "probe_segment_sector",         probe_segment_sector );
  m_tree->SetBranchAddress( "probe_segment_chamberIndex",   probe_segment_chamberIndex );
  m_tree->SetBranchAddress( "probe_segment_etaIndex",       probe_segment_etaIndex );
  m_tree->SetBranchAddress( "probe_segment_nPrecisionHits", probe_segment_nPrecisionHits );
  m_tree->SetBranchAddress( "probe_segment_nPhiLayers",     probe_segment_nPhiLayers );
  m_tree->SetBranchAddress( "probe_segment_nTrigEtaLayers", probe_segment_nTrigEtaLayers );
  //
  m_tree->SetBranchAddress( "tp_dR",              &tp_dR );
  m_tree->SetBranchAddress( "tp_deta",            &tp_deta );
  m_tree->SetBranchAddress( "tp_dphi",            &tp_dphi );
  m_tree->SetBranchAddress( "tp_extdR",           &tp_extdR );
  m_tree->SetBranchAddress( "tp_extdeta",         &tp_extdeta );
  m_tree->SetBranchAddress( "tp_extdphi",         &tp_extdphi );
  m_tree->SetBranchAddress( "tp_extinndR",        &tp_extinndR );
  m_tree->SetBranchAddress( "tp_extinndeta",      &tp_extinndeta );
  m_tree->SetBranchAddress( "tp_extinndphi",      &tp_extinndphi );
  m_tree->SetBranchAddress( "tp_mass",            &tp_mass );
  m_tree->SetBranchAddress( "tp_vftlxy",          &tp_vftlxy );
  m_tree->SetBranchAddress( "tp_vftchi2",         &tp_vftchi2 );
  m_tree->SetBranchAddress( "tp_vftndof",         &tp_vftndof );
  m_tree->SetBranchAddress( "probe_mesEFTAG_pass",   &probe_mesEFTAG_pass );
  m_tree->SetBranchAddress( "probe_mesEFTAG_dR",     &probe_mesEFTAG_dR );
  m_tree->SetBranchAddress( "probe_mesEFTAG_tpdR",   &probe_mesEFTAG_tpdR );
  m_tree->SetBranchAddress( "probe_mesEFTAG_pt",     &probe_mesEFTAG_pt );
  m_tree->SetBranchAddress( "probe_mesEFTAG_eta",    &probe_mesEFTAG_eta );
  m_tree->SetBranchAddress( "probe_mesEFTAG_phi",    &probe_mesEFTAG_phi );
  m_tree->SetBranchAddress( "probe_mesL1_pass",   &probe_mesL1_pass );
  m_tree->SetBranchAddress( "probe_mesL1_dR",     &probe_mesL1_dR );
  m_tree->SetBranchAddress( "probe_mesL1_tpdR",   &probe_mesL1_tpdR );
  m_tree->SetBranchAddress( "probe_mesL1_pt",     &probe_mesL1_pt );
  m_tree->SetBranchAddress( "probe_mesL1_eta",    &probe_mesL1_eta );
  m_tree->SetBranchAddress( "probe_mesL1_phi",    &probe_mesL1_phi );
  m_tree->SetBranchAddress( "probe_mesSA_pass",   &probe_mesSA_pass );
  m_tree->SetBranchAddress( "probe_mesSA_dR",     &probe_mesSA_dR );
  m_tree->SetBranchAddress( "probe_mesSA_tpdR",   &probe_mesSA_tpdR );
  m_tree->SetBranchAddress( "probe_mesSA_pt",     &probe_mesSA_pt );
  m_tree->SetBranchAddress( "probe_mesSA_eta",    &probe_mesSA_eta );
  m_tree->SetBranchAddress( "probe_mesSA_phi",    &probe_mesSA_phi );
  m_tree->SetBranchAddress( "probe_mesSA_etams",  &probe_mesSA_etams );
  m_tree->SetBranchAddress( "probe_mesSA_phims",  &probe_mesSA_phims );
  m_tree->SetBranchAddress( "probe_mesSA_etabe",  &probe_mesSA_etabe );
  m_tree->SetBranchAddress( "probe_mesSA_phibe",  &probe_mesSA_phibe );
  //
  m_tree->SetBranchAddress( "probe_mesSA_tgcpt",  &probe_mesSA_tgcpt );
  m_tree->SetBranchAddress( "probe_mesSA_ptBarrelRadius",  &probe_mesSA_ptBarrelRadius );
  m_tree->SetBranchAddress( "probe_mesSA_ptBarrelSagitta",  &probe_mesSA_ptBarrelSagitta );
  m_tree->SetBranchAddress( "probe_mesSA_ptEndcapAlpha",  &probe_mesSA_ptEndcapAlpha );
  m_tree->SetBranchAddress( "probe_mesSA_ptEndcapBeta",  &probe_mesSA_ptEndcapBeta );
  m_tree->SetBranchAddress( "probe_mesSA_ptEndcapRadius",  &probe_mesSA_ptEndcapRadius );
  m_tree->SetBranchAddress( "probe_mesSA_ptCSC",  &probe_mesSA_ptCSC );
  m_tree->SetBranchAddress( "probe_mesSA_sAddress",  &probe_mesSA_sAddress );

  m_tree->SetBranchAddress( "probe_mesSA_roiEta",  &probe_mesSA_roiEta );
  m_tree->SetBranchAddress( "probe_mesSA_roiPhi",  &probe_mesSA_roiPhi );
  m_tree->SetBranchAddress( "probe_mesSA_isRpcFailure",  &probe_mesSA_isRpcFailure );
  m_tree->SetBranchAddress( "probe_mesSA_isTgcFailure",  &probe_mesSA_isTgcFailure );
  //
  m_tree->SetBranchAddress( "probe_mesSA_superPointR_BI",   &probe_mesSA_superPointR_BI );
  m_tree->SetBranchAddress( "probe_mesSA_superPointR_BM",   &probe_mesSA_superPointR_BM );
  m_tree->SetBranchAddress( "probe_mesSA_superPointR_BO",   &probe_mesSA_superPointR_BO );
  m_tree->SetBranchAddress( "probe_mesSA_superPointR_EI",   &probe_mesSA_superPointR_EI );
  m_tree->SetBranchAddress( "probe_mesSA_superPointR_EM",   &probe_mesSA_superPointR_EM );
  m_tree->SetBranchAddress( "probe_mesSA_superPointR_EO",   &probe_mesSA_superPointR_EO );
  m_tree->SetBranchAddress( "probe_mesSA_superPointR_EE",   &probe_mesSA_superPointR_EE );
  m_tree->SetBranchAddress( "probe_mesSA_superPointR_CSC",  &probe_mesSA_superPointR_CSC );
  m_tree->SetBranchAddress( "probe_mesSA_superPointR_BEE",  &probe_mesSA_superPointR_BEE );
  m_tree->SetBranchAddress( "probe_mesSA_superPointR_BME",  &probe_mesSA_superPointR_BME );
  //
  m_tree->SetBranchAddress( "probe_mesSA_superPointZ_BI",   &probe_mesSA_superPointZ_BI );
  m_tree->SetBranchAddress( "probe_mesSA_superPointZ_BM",   &probe_mesSA_superPointZ_BM );
  m_tree->SetBranchAddress( "probe_mesSA_superPointZ_BO",   &probe_mesSA_superPointZ_BO );
  m_tree->SetBranchAddress( "probe_mesSA_superPointZ_EI",   &probe_mesSA_superPointZ_EI );
  m_tree->SetBranchAddress( "probe_mesSA_superPointZ_EM",   &probe_mesSA_superPointZ_EM );
  m_tree->SetBranchAddress( "probe_mesSA_superPointZ_EO",   &probe_mesSA_superPointZ_EO );
  m_tree->SetBranchAddress( "probe_mesSA_superPointZ_EE",   &probe_mesSA_superPointZ_EE );
  m_tree->SetBranchAddress( "probe_mesSA_superPointZ_CSC",  &probe_mesSA_superPointZ_CSC );
  m_tree->SetBranchAddress( "probe_mesSA_superPointZ_BEE",  &probe_mesSA_superPointZ_BEE );
  m_tree->SetBranchAddress( "probe_mesSA_superPointZ_BME",  &probe_mesSA_superPointZ_BME );
  //
  m_tree->SetBranchAddress( "probe_mesSA_superPointSlope_BI",   &probe_mesSA_superPointSlope_BI );
  m_tree->SetBranchAddress( "probe_mesSA_superPointSlope_BM",   &probe_mesSA_superPointSlope_BM );
  m_tree->SetBranchAddress( "probe_mesSA_superPointSlope_BO",   &probe_mesSA_superPointSlope_BO );
  m_tree->SetBranchAddress( "probe_mesSA_superPointSlope_EI",   &probe_mesSA_superPointSlope_EI );
  m_tree->SetBranchAddress( "probe_mesSA_superPointSlope_EM",   &probe_mesSA_superPointSlope_EM );
  m_tree->SetBranchAddress( "probe_mesSA_superPointSlope_EO",   &probe_mesSA_superPointSlope_EO );
  m_tree->SetBranchAddress( "probe_mesSA_superPointSlope_EE",   &probe_mesSA_superPointSlope_EE );
  m_tree->SetBranchAddress( "probe_mesSA_superPointSlope_CSC",  &probe_mesSA_superPointSlope_CSC );
  m_tree->SetBranchAddress( "probe_mesSA_superPointSlope_BEE",  &probe_mesSA_superPointSlope_BEE );
  m_tree->SetBranchAddress( "probe_mesSA_superPointSlope_BME",  &probe_mesSA_superPointSlope_BME );
  //
  m_tree->SetBranchAddress( "probe_mesSA_superPointIntercept_BI",   &probe_mesSA_superPointIntercept_BI );
  m_tree->SetBranchAddress( "probe_mesSA_superPointIntercept_BM",   &probe_mesSA_superPointIntercept_BM );
  m_tree->SetBranchAddress( "probe_mesSA_superPointIntercept_BO",   &probe_mesSA_superPointIntercept_BO );
  m_tree->SetBranchAddress( "probe_mesSA_superPointIntercept_EI",   &probe_mesSA_superPointIntercept_EI );
  m_tree->SetBranchAddress( "probe_mesSA_superPointIntercept_EM",   &probe_mesSA_superPointIntercept_EM );
  m_tree->SetBranchAddress( "probe_mesSA_superPointIntercept_EO",   &probe_mesSA_superPointIntercept_EO );
  m_tree->SetBranchAddress( "probe_mesSA_superPointIntercept_EE",   &probe_mesSA_superPointIntercept_EE );
  m_tree->SetBranchAddress( "probe_mesSA_superPointIntercept_CSC",  &probe_mesSA_superPointIntercept_CSC );
  m_tree->SetBranchAddress( "probe_mesSA_superPointIntercept_BEE",  &probe_mesSA_superPointIntercept_BEE );
  m_tree->SetBranchAddress( "probe_mesSA_superPointIntercept_BME",  &probe_mesSA_superPointIntercept_BME );
  //
  m_tree->SetBranchAddress( "probe_mesSA_superPointChi2_BI",   &probe_mesSA_superPointChi2_BI );
  m_tree->SetBranchAddress( "probe_mesSA_superPointChi2_BM",   &probe_mesSA_superPointChi2_BM );
  m_tree->SetBranchAddress( "probe_mesSA_superPointChi2_BO",   &probe_mesSA_superPointChi2_BO );
  m_tree->SetBranchAddress( "probe_mesSA_superPointChi2_EI",   &probe_mesSA_superPointChi2_EI );
  m_tree->SetBranchAddress( "probe_mesSA_superPointChi2_EM",   &probe_mesSA_superPointChi2_EM );
  m_tree->SetBranchAddress( "probe_mesSA_superPointChi2_EO",   &probe_mesSA_superPointChi2_EO );
  m_tree->SetBranchAddress( "probe_mesSA_superPointChi2_EE",   &probe_mesSA_superPointChi2_EE );
  m_tree->SetBranchAddress( "probe_mesSA_superPointChi2_CSC",  &probe_mesSA_superPointChi2_CSC );
  m_tree->SetBranchAddress( "probe_mesSA_superPointChi2_BEE",  &probe_mesSA_superPointChi2_BEE );
  m_tree->SetBranchAddress( "probe_mesSA_superPointChi2_BME",  &probe_mesSA_superPointChi2_BME );
  //
  m_tree->SetBranchAddress( "probe_mesSA_rpcHitX",  &probe_mesSA_rpcHitX );
  m_tree->SetBranchAddress( "probe_mesSA_rpcHitY",  &probe_mesSA_rpcHitY );
  m_tree->SetBranchAddress( "probe_mesSA_rpcHitZ",  &probe_mesSA_rpcHitZ );
  m_tree->SetBranchAddress( "probe_mesSA_rpcHitStationNumber",  &probe_mesSA_rpcHitStationNumber );
  m_tree->SetBranchAddress( "probe_mesSA_rpcHitStationName",  &probe_mesSA_rpcHitStationName );

  //
  m_tree->SetBranchAddress( "probe_mesSA_roadAw",  &probe_mesSA_roadAw );
  m_tree->SetBranchAddress( "probe_mesSA_roadBw",  &probe_mesSA_roadBw );
  m_tree->SetBranchAddress( "probe_mesSA_zMin",  &probe_mesSA_zMin );
  m_tree->SetBranchAddress( "probe_mesSA_zMax",  &probe_mesSA_zMax );
  m_tree->SetBranchAddress( "probe_mesSA_rMin",  &probe_mesSA_rMin );
  m_tree->SetBranchAddress( "probe_mesSA_rMax",  &probe_mesSA_rMax );
  m_tree->SetBranchAddress( "probe_mesSA_etaMin",  &probe_mesSA_etaMin );
  m_tree->SetBranchAddress( "probe_mesSA_etaMax",  &probe_mesSA_etaMax );
  //
  m_tree->SetBranchAddress( "probe_mesCB_pass",   &probe_mesCB_pass );
  m_tree->SetBranchAddress( "probe_mesCB_dR",     &probe_mesCB_dR );
  m_tree->SetBranchAddress( "probe_mesCB_tpdR",   &probe_mesCB_tpdR );
  m_tree->SetBranchAddress( "probe_mesCB_pt",     &probe_mesCB_pt );
  m_tree->SetBranchAddress( "probe_mesCB_eta",    &probe_mesCB_eta );
  m_tree->SetBranchAddress( "probe_mesCB_phi",    &probe_mesCB_phi );
  m_tree->SetBranchAddress( "probe_mesFTF_pass",  &probe_mesFTF_pass );
  m_tree->SetBranchAddress( "probe_mesFTF_dR",    &probe_mesFTF_dR );
  m_tree->SetBranchAddress( "probe_mesFTF_pt",    &probe_mesFTF_pt );
  m_tree->SetBranchAddress( "probe_mesFTF_eta",   &probe_mesFTF_eta );
  m_tree->SetBranchAddress( "probe_mesFTF_phi",   &probe_mesFTF_phi );
  m_tree->SetBranchAddress( "probe_mesEF_pass",   &probe_mesEF_pass );
  m_tree->SetBranchAddress( "probe_mesEF_dR",     &probe_mesEF_dR );
  m_tree->SetBranchAddress( "probe_mesEF_tpdR",   &probe_mesEF_tpdR );
  m_tree->SetBranchAddress( "probe_mesEF_pt",     &probe_mesEF_pt );
  m_tree->SetBranchAddress( "probe_mesEF_eta",    &probe_mesEF_eta );
  m_tree->SetBranchAddress( "probe_mesEF_phi",    &probe_mesEF_phi );
}

int EventTree::clear( ) {
	// clear the vector for branch
    //mes_name->clear();
	return 1;
}

int EventTree::filltree( TagAndProbe& tap, int eventNumber, int runNumber, int lumiBlock, float averageInteractionsPerCrossing) {
// fill the variable vectors
  
  vector < string > tmp_mes_name  = tap.mesName();

  mes_n         = tap.NMes();
  mes_name      = &( tmp_mes_name );
  int probe_n   = tap.probePt().size();
  
 
  for( int i=0; i<probe_n; i++ ) {

    EventNumber = eventNumber;
    RunNumber = runNumber;
    LumiBlock = lumiBlock;
    AverageInteractionsPerCrossing = averageInteractionsPerCrossing;
    
    vector < vector < int > > tmp_probe_mesEFTAG_pass    = tap.probePassedEFTAG();
    vector < vector < double > > tmp_probe_mesEFTAG_dR   = tap.probeEFTAGdR();
    vector < vector < double > > tmp_probe_mesEFTAG_tpdR = tap.probeEFTAGtpdR();
    vector < vector < double > > tmp_probe_mesEFTAG_pt   = tap.probeEFTAGPt();
    vector < vector < double > > tmp_probe_mesEFTAG_eta  = tap.probeEFTAGEta();
    vector < vector < double > > tmp_probe_mesEFTAG_phi  = tap.probeEFTAGPhi();
    vector < vector < int > > tmp_probe_mesL1_pass    = tap.probePassedL1();
    vector < vector < double > > tmp_probe_mesL1_dR   = tap.probeL1dR();
    vector < vector < double > > tmp_probe_mesL1_tpdR = tap.probeL1tpdR();
    vector < vector < double > > tmp_probe_mesL1_pt   = tap.probeL1Pt();
    vector < vector < double > > tmp_probe_mesL1_eta  = tap.probeL1Eta();
    vector < vector < double > > tmp_probe_mesL1_phi  = tap.probeL1Phi();
    vector < vector < int > > tmp_probe_mesSA_pass    = tap.probePassedSA();
    vector < vector < double > > tmp_probe_mesSA_dR   = tap.probeSAdR();
    vector < vector < double > > tmp_probe_mesSA_tpdR = tap.probeSAtpdR();
    vector < vector < double > > tmp_probe_mesSA_pt   = tap.probeSAPt();
    vector < vector < double > > tmp_probe_mesSA_eta  = tap.probeSAEta();
    vector < vector < double > > tmp_probe_mesSA_phi  = tap.probeSAPhi();
    vector < vector < double > > tmp_probe_mesSA_etams  = tap.probeSAEtaMS();
    vector < vector < double > > tmp_probe_mesSA_phims  = tap.probeSAPhiMS();
    vector < vector < double > > tmp_probe_mesSA_etabe  = tap.probeSAEtaBE();
    vector < vector < double > > tmp_probe_mesSA_phibe  = tap.probeSAPhiBE();
    //
    vector < vector < double > > tmp_probe_mesSA_tgcpt  = tap.probeSATgcPt();
    vector < vector < double > > tmp_probe_mesSA_ptBarrelRadius  = tap.probeSAPtBarrelRadius();
    vector < vector < double > > tmp_probe_mesSA_ptBarrelSagitta  = tap.probeSAPtBarrelSagitta();
    vector < vector < double > > tmp_probe_mesSA_ptEndcapAlpha  = tap.probeSAPtEndcapAlpha();
    vector < vector < double > > tmp_probe_mesSA_ptEndcapBeta  = tap.probeSAPtEndcapBeta();
    vector < vector < double > > tmp_probe_mesSA_ptEndcapRadius  = tap.probeSAPtEndcapRadius();
    vector < vector < double > > tmp_probe_mesSA_ptCSC  = tap.probeSAPtCSC();
    vector < vector < double > > tmp_probe_mesSA_sAddress  = tap.probeSAsAddress();

    vector < vector < float > > tmp_probe_mesSA_roiEta  = tap.probeSAroiEta();
    vector < vector < float > > tmp_probe_mesSA_roiPhi  = tap.probeSAroiPhi();
    vector < vector < int > > tmp_probe_mesSA_isRpcFailure  = tap.probeSAisRpcFailure();
    vector < vector < int > > tmp_probe_mesSA_isTgcFailure  = tap.probeSAisTgcFailure();
    //
    vector < vector < double > > tmp_probe_mesSA_superPointR_BI  = tap.probeSAsuperPointRBI();  
    vector < vector < double > > tmp_probe_mesSA_superPointR_BM  = tap.probeSAsuperPointRBM();  
    vector < vector < double > > tmp_probe_mesSA_superPointR_BO  = tap.probeSAsuperPointRBO();  
    vector < vector < double > > tmp_probe_mesSA_superPointR_EI  = tap.probeSAsuperPointREI();  
    vector < vector < double > > tmp_probe_mesSA_superPointR_EM  = tap.probeSAsuperPointREM();  
    vector < vector < double > > tmp_probe_mesSA_superPointR_EO  = tap.probeSAsuperPointREO();  
    vector < vector < double > > tmp_probe_mesSA_superPointR_EE  = tap.probeSAsuperPointREE();  
    vector < vector < double > > tmp_probe_mesSA_superPointR_CSC = tap.probeSAsuperPointRCSC(); 
    vector < vector < double > > tmp_probe_mesSA_superPointR_BEE = tap.probeSAsuperPointRBEE(); 
    vector < vector < double > > tmp_probe_mesSA_superPointR_BME = tap.probeSAsuperPointRBME(); 
    //
    vector < vector < double > > tmp_probe_mesSA_superPointZ_BI  = tap.probeSAsuperPointZBI();  
    vector < vector < double > > tmp_probe_mesSA_superPointZ_BM  = tap.probeSAsuperPointZBM();  
    vector < vector < double > > tmp_probe_mesSA_superPointZ_BO  = tap.probeSAsuperPointZBO();  
    vector < vector < double > > tmp_probe_mesSA_superPointZ_EI  = tap.probeSAsuperPointZEI();  
    vector < vector < double > > tmp_probe_mesSA_superPointZ_EM  = tap.probeSAsuperPointZEM();  
    vector < vector < double > > tmp_probe_mesSA_superPointZ_EO  = tap.probeSAsuperPointZEO();  
    vector < vector < double > > tmp_probe_mesSA_superPointZ_EE  = tap.probeSAsuperPointZEE();  
    vector < vector < double > > tmp_probe_mesSA_superPointZ_CSC = tap.probeSAsuperPointZCSC(); 
    vector < vector < double > > tmp_probe_mesSA_superPointZ_BEE = tap.probeSAsuperPointZBEE(); 
    vector < vector < double > > tmp_probe_mesSA_superPointZ_BME = tap.probeSAsuperPointZBME(); 
    //
    vector < vector < double > > tmp_probe_mesSA_superPointSlope_BI  = tap.probeSAsuperPointSlopeBI();  
    vector < vector < double > > tmp_probe_mesSA_superPointSlope_BM  = tap.probeSAsuperPointSlopeBM();  
    vector < vector < double > > tmp_probe_mesSA_superPointSlope_BO  = tap.probeSAsuperPointSlopeBO();  
    vector < vector < double > > tmp_probe_mesSA_superPointSlope_EI  = tap.probeSAsuperPointSlopeEI();  
    vector < vector < double > > tmp_probe_mesSA_superPointSlope_EM  = tap.probeSAsuperPointSlopeEM();  
    vector < vector < double > > tmp_probe_mesSA_superPointSlope_EO  = tap.probeSAsuperPointSlopeEO();  
    vector < vector < double > > tmp_probe_mesSA_superPointSlope_EE  = tap.probeSAsuperPointSlopeEE();  
    vector < vector < double > > tmp_probe_mesSA_superPointSlope_CSC = tap.probeSAsuperPointSlopeCSC(); 
    vector < vector < double > > tmp_probe_mesSA_superPointSlope_BEE = tap.probeSAsuperPointSlopeBEE(); 
    vector < vector < double > > tmp_probe_mesSA_superPointSlope_BME = tap.probeSAsuperPointSlopeBME(); 
    //
    vector < vector < double > > tmp_probe_mesSA_superPointIntercept_BI  = tap.probeSAsuperPointInterceptBI();  
    vector < vector < double > > tmp_probe_mesSA_superPointIntercept_BM  = tap.probeSAsuperPointInterceptBM();  
    vector < vector < double > > tmp_probe_mesSA_superPointIntercept_BO  = tap.probeSAsuperPointInterceptBO();  
    vector < vector < double > > tmp_probe_mesSA_superPointIntercept_EI  = tap.probeSAsuperPointInterceptEI();  
    vector < vector < double > > tmp_probe_mesSA_superPointIntercept_EM  = tap.probeSAsuperPointInterceptEM();  
    vector < vector < double > > tmp_probe_mesSA_superPointIntercept_EO  = tap.probeSAsuperPointInterceptEO();  
    vector < vector < double > > tmp_probe_mesSA_superPointIntercept_EE  = tap.probeSAsuperPointInterceptEE();  
    vector < vector < double > > tmp_probe_mesSA_superPointIntercept_CSC = tap.probeSAsuperPointInterceptCSC(); 
    vector < vector < double > > tmp_probe_mesSA_superPointIntercept_BEE = tap.probeSAsuperPointInterceptBEE(); 
    vector < vector < double > > tmp_probe_mesSA_superPointIntercept_BME = tap.probeSAsuperPointInterceptBME(); 
    //
    vector < vector < double > > tmp_probe_mesSA_superPointChi2_BI  = tap.probeSAsuperPointChi2BI();  
    vector < vector < double > > tmp_probe_mesSA_superPointChi2_BM  = tap.probeSAsuperPointChi2BM();  
    vector < vector < double > > tmp_probe_mesSA_superPointChi2_BO  = tap.probeSAsuperPointChi2BO();  
    vector < vector < double > > tmp_probe_mesSA_superPointChi2_EI  = tap.probeSAsuperPointChi2EI();  
    vector < vector < double > > tmp_probe_mesSA_superPointChi2_EM  = tap.probeSAsuperPointChi2EM();  
    vector < vector < double > > tmp_probe_mesSA_superPointChi2_EO  = tap.probeSAsuperPointChi2EO();  
    vector < vector < double > > tmp_probe_mesSA_superPointChi2_EE  = tap.probeSAsuperPointChi2EE();  
    vector < vector < double > > tmp_probe_mesSA_superPointChi2_CSC = tap.probeSAsuperPointChi2CSC(); 
    vector < vector < double > > tmp_probe_mesSA_superPointChi2_BEE = tap.probeSAsuperPointChi2BEE(); 
    vector < vector < double > > tmp_probe_mesSA_superPointChi2_BME = tap.probeSAsuperPointChi2BME(); 
    //
    vector < vector <  vector < float > > >  tmp_probe_mesSA_rpcHitX   = tap.probeSArpcHitX(); 
    vector < vector <  vector < float > > >  tmp_probe_mesSA_rpcHitY   = tap.probeSArpcHitY(); 
    vector < vector <  vector < float > > >  tmp_probe_mesSA_rpcHitZ   = tap.probeSArpcHitZ(); 
    vector < vector <  vector < double > > > tmp_probe_mesSA_rpcHitR   = tap.probeSArpcHitR(); 
    vector < vector <  vector < double > > > tmp_probe_mesSA_rpcHitEta = tap.probeSArpcHitEta(); 
    vector < vector <  vector < double > > > tmp_probe_mesSA_rpcHitPhi = tap.probeSArpcHitPhi(); 
    vector < vector <  vector < double > > > tmp_probe_mesSA_rpcHitStationNumber = tap.probeSArpcHitStationNumber(); 
    vector < vector <  vector < string > > > tmp_probe_mesSA_rpcHitStationName = tap.probeSArpcHitStationName(); 
    //
    vector < vector <  vector < int > > >  tmp_probe_mesSA_mdtHitIsOutlier  = tap.probeSAmdtHitIsOutlier();
    vector < vector <  vector < int > > >  tmp_probe_mesSA_mdtHitChamber    = tap.probeSAmdtHitChamber(); 
    vector < vector <  vector < float > > >  tmp_probe_mesSA_mdtHitR          = tap.probeSAmdtHitR(); 
    vector < vector <  vector < float > > >  tmp_probe_mesSA_mdtHitZ          = tap.probeSAmdtHitZ(); 
    vector < vector <  vector < float > > >  tmp_probe_mesSA_mdtHitPhi        = tap.probeSAmdtHitPhi(); 
    vector < vector <  vector < float > > >  tmp_probe_mesSA_mdtHitResidual   = tap.probeSAmdtHitResidual(); 

    vector < vector <  vector < float > > >  tmp_probe_mesSA_roadAw   = tap.probeSAroadAw(); 
    vector < vector <  vector < float > > >  tmp_probe_mesSA_roadBw   = tap.probeSAroadBw(); 
    vector < vector <  vector < float > > >  tmp_probe_mesSA_zMin   = tap.probeSAzMin(); 
    vector < vector <  vector < float > > > tmp_probe_mesSA_zMax   = tap.probeSAzMax(); 
    vector < vector <  vector < float > > > tmp_probe_mesSA_rMin = tap.probeSArMin(); 
    vector < vector <  vector < float > > > tmp_probe_mesSA_rMax = tap.probeSArMax(); 
    vector < vector <  vector < float > > > tmp_probe_mesSA_etaMin = tap.probeSAetaMin(); 
    vector < vector <  vector < float > > > tmp_probe_mesSA_etaMax = tap.probeSAetaMax(); 
    //
    vector < vector < int > > tmp_probe_mesCB_pass    = tap.probePassedCB();
    vector < vector < double > > tmp_probe_mesCB_dR   = tap.probeCBdR();
    vector < vector < double > > tmp_probe_mesCB_tpdR = tap.probeCBtpdR();
    vector < vector < double > > tmp_probe_mesCB_pt   = tap.probeCBPt();
    vector < vector < double > > tmp_probe_mesCB_eta  = tap.probeCBEta();
    vector < vector < double > > tmp_probe_mesCB_phi  = tap.probeCBPhi();
    vector < vector < int > > tmp_probe_mesFTF_pass   = tap.probePassedFTF();
    vector < vector < double > > tmp_probe_mesFTF_dR  = tap.probeFTFdR();
    vector < vector < double > > tmp_probe_mesFTF_pt  = tap.probeFTFPt();
    vector < vector < double > > tmp_probe_mesFTF_eta = tap.probeFTFEta();
    vector < vector < double > > tmp_probe_mesFTF_phi = tap.probeFTFPhi();
    vector < vector < int > > tmp_probe_mesEF_pass    = tap.probePassedEF();
    vector < vector < double > > tmp_probe_mesEF_dR   = tap.probeEFdR();
    vector < vector < double > > tmp_probe_mesEF_tpdR = tap.probeEFtpdR();
    vector < vector < double > > tmp_probe_mesEF_pt   = tap.probeEFPt();
    vector < vector < double > > tmp_probe_mesEF_eta  = tap.probeEFEta();
    vector < vector < double > > tmp_probe_mesEF_phi  = tap.probeEFPhi();
    
    TLorentzVector lvtag, lvprobe, lvtap, lvexttag, lvextprobe, lvexttaginn, lvextprobeinn;
    TLorentzVector lvtl1, lvtsa, lvtcb, lvtef;
    TLorentzVector lvpl1, lvpsa, lvpcb, lvpef;
    sumReqdRL1        = tap.tpSumReqL1dR()[i];
    sumReqdREF        = tap.tpSumReqEFdR()[i];
    tag_proc          = tap.tagProc()[i];
    tag_proc          = tap.tagProc()[i];
    tag_ReqdRL1       = tap.tagReqL1dR()[i];
    tag_ReqdREF       = tap.tagReqEFdR()[i];
    tag_dRL1          = tap.tagL1dR()[i];
    tag_dREF          = tap.tagEFdR()[i];
    tag_pt            = tap.tagPt()[i];
    tag_eta           = tap.tagEta()[i];
    tag_exteta        = tap.tagExtEta()[i];
    tag_extinneta     = tap.tagExtInnEta()[i];
    tag_phi           = tap.tagPhi()[i];
    tag_extphi        = tap.tagExtPhi()[i];
    tag_extinnphi     = tap.tagExtInnPhi()[i];
    tag_d0            = tap.tagd0()[i];
    tag_z0            = tap.tagz0()[i];
    tag_charge        = tap.tagCharge()[i];
    tag_L1_pt         = tap.tagL1Pt()[i];
    tag_L1_eta        = tap.tagL1Eta()[i];
    tag_L1_phi        = tap.tagL1Phi()[i];
    tag_SA_pt         = tap.tagSAPt()[i];
    tag_SA_eta        = tap.tagSAEta()[i];
    tag_SA_phi        = tap.tagSAPhi()[i];
    tag_CB_pt         = tap.tagCBPt()[i];
    tag_CB_eta        = tap.tagCBEta()[i];
    tag_CB_phi        = tap.tagCBPhi()[i];
    tag_EF_pt         = tap.tagEFPt()[i];
    tag_EF_eta        = tap.tagEFEta()[i];
    tag_EF_phi        = tap.tagEFPhi()[i];
    probe_pt          = tap.probePt()[i];
    probe_MSpt          = tap.probeMSPt()[i];//kayamash
    probe_eta         = tap.probeEta()[i];
    probe_exteta      = tap.probeExtEta()[i];
    probe_extinneta   = tap.probeExtInnEta()[i];
    probe_phi         = tap.probePhi()[i];
    probe_extphi      = tap.probeExtPhi()[i];
    probe_extinnphi   = tap.probeExtInnPhi()[i];
    probe_d0          = tap.probed0()[i];
    probe_z0          = tap.probez0()[i];
    probe_charge      = tap.probeCharge()[i];
    //
    probe_segment_n   = tap.probeSegmentN()[i];
    for(int nSeg = 0 ; nSeg < SegmentMaxNumber ; nSeg++ ){
      probe_segment_x[nSeg]              = tap.probeSegmentX(nSeg)[i];
      probe_segment_y[nSeg]              = tap.probeSegmentY(nSeg)[i];
      probe_segment_z[nSeg]              = tap.probeSegmentZ(nSeg)[i];
      probe_segment_px[nSeg]             = tap.probeSegmentPx(nSeg)[i];
      probe_segment_py[nSeg]             = tap.probeSegmentPy(nSeg)[i];
      probe_segment_pz[nSeg]             = tap.probeSegmentPz(nSeg)[i];
      probe_segment_chiSquared[nSeg]     = tap.probeSegmentChiSquared(nSeg)[i];
      probe_segment_numberDoF[nSeg]      = tap.probeSegmentNumberDoF(nSeg)[i];
      probe_segment_sector[nSeg]         = tap.probeSegmentSector(nSeg)[i];
      probe_segment_chamberIndex[nSeg]   = tap.probeSegmentChamberIndex(nSeg)[i];
      probe_segment_etaIndex[nSeg]       = tap.probeSegmentEtaIndex(nSeg)[i];
      probe_segment_nPrecisionHits[nSeg] = tap.probeSegmentNPrecisionHits(nSeg)[i];
      probe_segment_nPhiLayers[nSeg]     = tap.probeSegmentNPhiLayers(nSeg)[i];
      probe_segment_nTrigEtaLayers[nSeg] = tap.probeSegmentNTrigEtaLayers(nSeg)[i];
    }
    //
    
    lvtag.SetPtEtaPhiM( tag_pt, tag_eta, tag_phi, 105.6 ); 
    lvprobe.SetPtEtaPhiM( probe_pt, probe_eta, probe_phi, 105.6 ); 
    lvtap = lvtag+lvprobe;
    tp_dR             = lvtag.DeltaR( lvprobe );
    tp_deta           = fabs( tag_eta - probe_eta );
    tp_dphi           = fabs( lvtag.DeltaPhi( lvprobe ) );
    tp_mass           = lvtap.M();
    lvexttag.SetPtEtaPhiM( tag_pt, tag_exteta, tag_extphi, 105.6 ); 
    lvextprobe.SetPtEtaPhiM( probe_pt, probe_exteta, probe_extphi, 105.6 ); 
    tp_extdR          = lvexttag.DeltaR( lvextprobe );
    tp_extdeta        = fabs( tag_exteta - probe_exteta );
    tp_extdphi        = fabs( lvexttag.DeltaPhi( lvextprobe ) );
    lvexttaginn.SetPtEtaPhiM( tag_pt, tag_extinneta, tag_extinnphi, 105.6 ); 
    lvextprobeinn.SetPtEtaPhiM( probe_pt, probe_extinneta, probe_extinnphi, 105.6 ); 
    tp_extinndR       = lvexttaginn.DeltaR( lvextprobeinn );
    tp_extinndeta     = fabs( tag_extinneta - probe_extinneta );
    tp_extinndphi     = fabs( lvexttaginn.DeltaPhi( lvextprobeinn ) );
    double tp_vftdx   = tap.tpVrtDx()[i]; 
    double tp_vftdy   = tap.tpVrtDy()[i]; 
    tp_vftlxy         = ( tp_vftdx*lvtap.Px() + tp_vftdy*lvtap.Py() )/lvtap.Pt();
    tp_vftchi2        = tap.tpVrtChi2()[i]; 
    tp_vftndof        = tap.tpVrtNdof()[i]; 

    probe_mesEFTAG_pass  = &( tmp_probe_mesEFTAG_pass[i] );
    probe_mesEFTAG_dR    = &( tmp_probe_mesEFTAG_dR[i] );
    probe_mesEFTAG_tpdR  = &( tmp_probe_mesEFTAG_tpdR[i] );
    probe_mesEFTAG_pt    = &( tmp_probe_mesEFTAG_pt[i] );
    probe_mesEFTAG_eta   = &( tmp_probe_mesEFTAG_eta[i] );
    probe_mesEFTAG_phi   = &( tmp_probe_mesEFTAG_phi[i] );
    probe_mesL1_pass  = &( tmp_probe_mesL1_pass[i] );
    probe_mesL1_dR    = &( tmp_probe_mesL1_dR[i] );
    probe_mesL1_tpdR  = &( tmp_probe_mesL1_tpdR[i] );
    probe_mesL1_pt    = &( tmp_probe_mesL1_pt[i] );
    probe_mesL1_eta   = &( tmp_probe_mesL1_eta[i] );
    probe_mesL1_phi   = &( tmp_probe_mesL1_phi[i] );
    probe_mesSA_pass  = &( tmp_probe_mesSA_pass[i] );
    probe_mesSA_dR    = &( tmp_probe_mesSA_dR[i] );
    probe_mesSA_tpdR  = &( tmp_probe_mesSA_tpdR[i] );
    probe_mesSA_pt    = &( tmp_probe_mesSA_pt[i] );
    probe_mesSA_eta   = &( tmp_probe_mesSA_eta[i] );
    probe_mesSA_phi   = &( tmp_probe_mesSA_phi[i] );
    probe_mesSA_etams = &( tmp_probe_mesSA_etams[i] );
    probe_mesSA_phims = &( tmp_probe_mesSA_phims[i] );
    probe_mesSA_etabe = &( tmp_probe_mesSA_etabe[i] );
    probe_mesSA_phibe = &( tmp_probe_mesSA_phibe[i] );
    //
    probe_mesSA_tgcpt = &( tmp_probe_mesSA_tgcpt[i] );
    probe_mesSA_ptBarrelRadius = &( tmp_probe_mesSA_ptBarrelRadius[i] );
    probe_mesSA_ptBarrelSagitta = &( tmp_probe_mesSA_ptBarrelSagitta[i] );
    probe_mesSA_ptEndcapAlpha = &( tmp_probe_mesSA_ptEndcapAlpha[i] );
    probe_mesSA_ptEndcapBeta = &( tmp_probe_mesSA_ptEndcapBeta[i] );
    probe_mesSA_ptEndcapRadius = &( tmp_probe_mesSA_ptEndcapRadius[i] );
    probe_mesSA_ptCSC = &( tmp_probe_mesSA_ptCSC[i] );
    probe_mesSA_sAddress = &( tmp_probe_mesSA_sAddress[i] );

    probe_mesSA_roiEta = &( tmp_probe_mesSA_roiEta[i] );
    probe_mesSA_roiPhi = &( tmp_probe_mesSA_roiPhi[i] );
    probe_mesSA_isRpcFailure = &( tmp_probe_mesSA_isRpcFailure[i] );
    probe_mesSA_isTgcFailure = &( tmp_probe_mesSA_isTgcFailure[i] );
    //
    probe_mesSA_superPointR_BI  = &( tmp_probe_mesSA_superPointR_BI[i] );  
    probe_mesSA_superPointR_BM  = &( tmp_probe_mesSA_superPointR_BM[i] );  
    probe_mesSA_superPointR_BO  = &( tmp_probe_mesSA_superPointR_BO[i] );  
    probe_mesSA_superPointR_EI  = &( tmp_probe_mesSA_superPointR_EI[i] );  
    probe_mesSA_superPointR_EM  = &( tmp_probe_mesSA_superPointR_EM[i] );  
    probe_mesSA_superPointR_EO  = &( tmp_probe_mesSA_superPointR_EO[i] );  
    probe_mesSA_superPointR_EE  = &( tmp_probe_mesSA_superPointR_EE[i] );  
    probe_mesSA_superPointR_CSC = &( tmp_probe_mesSA_superPointR_CSC[i] ); 
    probe_mesSA_superPointR_BEE = &( tmp_probe_mesSA_superPointR_BEE[i] ); 
    probe_mesSA_superPointR_BME = &( tmp_probe_mesSA_superPointR_BME[i] ); 
    //
    probe_mesSA_superPointZ_BI  = &( tmp_probe_mesSA_superPointZ_BI[i] );  
    probe_mesSA_superPointZ_BM  = &( tmp_probe_mesSA_superPointZ_BM[i] );  
    probe_mesSA_superPointZ_BO  = &( tmp_probe_mesSA_superPointZ_BO[i] );  
    probe_mesSA_superPointZ_EI  = &( tmp_probe_mesSA_superPointZ_EI[i] );  
    probe_mesSA_superPointZ_EM  = &( tmp_probe_mesSA_superPointZ_EM[i] );  
    probe_mesSA_superPointZ_EO  = &( tmp_probe_mesSA_superPointZ_EO[i] );  
    probe_mesSA_superPointZ_EE  = &( tmp_probe_mesSA_superPointZ_EE[i] );  
    probe_mesSA_superPointZ_CSC = &( tmp_probe_mesSA_superPointZ_CSC[i] ); 
    probe_mesSA_superPointZ_BEE = &( tmp_probe_mesSA_superPointZ_BEE[i] ); 
    probe_mesSA_superPointZ_BME = &( tmp_probe_mesSA_superPointZ_BME[i] ); 
    //
    probe_mesSA_superPointSlope_BI  = &( tmp_probe_mesSA_superPointSlope_BI[i] );  
    probe_mesSA_superPointSlope_BM  = &( tmp_probe_mesSA_superPointSlope_BM[i] );  
    probe_mesSA_superPointSlope_BO  = &( tmp_probe_mesSA_superPointSlope_BO[i] );  
    probe_mesSA_superPointSlope_EI  = &( tmp_probe_mesSA_superPointSlope_EI[i] );  
    probe_mesSA_superPointSlope_EM  = &( tmp_probe_mesSA_superPointSlope_EM[i] );  
    probe_mesSA_superPointSlope_EO  = &( tmp_probe_mesSA_superPointSlope_EO[i] );  
    probe_mesSA_superPointSlope_EE  = &( tmp_probe_mesSA_superPointSlope_EE[i] );  
    probe_mesSA_superPointSlope_CSC = &( tmp_probe_mesSA_superPointSlope_CSC[i] ); 
    probe_mesSA_superPointSlope_BEE = &( tmp_probe_mesSA_superPointSlope_BEE[i] ); 
    probe_mesSA_superPointSlope_BME = &( tmp_probe_mesSA_superPointSlope_BME[i] ); 
    //
    probe_mesSA_superPointIntercept_BI  = &( tmp_probe_mesSA_superPointIntercept_BI[i] );  
    probe_mesSA_superPointIntercept_BM  = &( tmp_probe_mesSA_superPointIntercept_BM[i] );  
    probe_mesSA_superPointIntercept_BO  = &( tmp_probe_mesSA_superPointIntercept_BO[i] );  
    probe_mesSA_superPointIntercept_EI  = &( tmp_probe_mesSA_superPointIntercept_EI[i] );  
    probe_mesSA_superPointIntercept_EM  = &( tmp_probe_mesSA_superPointIntercept_EM[i] );  
    probe_mesSA_superPointIntercept_EO  = &( tmp_probe_mesSA_superPointIntercept_EO[i] );  
    probe_mesSA_superPointIntercept_EE  = &( tmp_probe_mesSA_superPointIntercept_EE[i] );  
    probe_mesSA_superPointIntercept_CSC = &( tmp_probe_mesSA_superPointIntercept_CSC[i] ); 
    probe_mesSA_superPointIntercept_BEE = &( tmp_probe_mesSA_superPointIntercept_BEE[i] ); 
    probe_mesSA_superPointIntercept_BME = &( tmp_probe_mesSA_superPointIntercept_BME[i] ); 
    //
    probe_mesSA_superPointChi2_BI  = &( tmp_probe_mesSA_superPointChi2_BI[i] );  
    probe_mesSA_superPointChi2_BM  = &( tmp_probe_mesSA_superPointChi2_BM[i] );  
    probe_mesSA_superPointChi2_BO  = &( tmp_probe_mesSA_superPointChi2_BO[i] );  
    probe_mesSA_superPointChi2_EI  = &( tmp_probe_mesSA_superPointChi2_EI[i] );  
    probe_mesSA_superPointChi2_EM  = &( tmp_probe_mesSA_superPointChi2_EM[i] );  
    probe_mesSA_superPointChi2_EO  = &( tmp_probe_mesSA_superPointChi2_EO[i] );  
    probe_mesSA_superPointChi2_EE  = &( tmp_probe_mesSA_superPointChi2_EE[i] );  
    probe_mesSA_superPointChi2_CSC = &( tmp_probe_mesSA_superPointChi2_CSC[i] ); 
    probe_mesSA_superPointChi2_BEE = &( tmp_probe_mesSA_superPointChi2_BEE[i] ); 
    probe_mesSA_superPointChi2_BME = &( tmp_probe_mesSA_superPointChi2_BME[i] ); 
    //
    probe_mesSA_rpcHitX   = &( tmp_probe_mesSA_rpcHitX[i] );
    probe_mesSA_rpcHitY   = &( tmp_probe_mesSA_rpcHitY[i] );
    probe_mesSA_rpcHitZ   = &( tmp_probe_mesSA_rpcHitZ[i] );
    probe_mesSA_rpcHitR   = &( tmp_probe_mesSA_rpcHitR[i] );
    probe_mesSA_rpcHitEta = &( tmp_probe_mesSA_rpcHitEta[i] );
    probe_mesSA_rpcHitPhi = &( tmp_probe_mesSA_rpcHitPhi[i] );
    probe_mesSA_rpcHitStationNumber = &( tmp_probe_mesSA_rpcHitStationNumber[i] );
    probe_mesSA_rpcHitStationName = &( tmp_probe_mesSA_rpcHitStationName[i] );

    probe_mesSA_mdtHitIsOutlier = &( tmp_probe_mesSA_mdtHitIsOutlier[i] );
    probe_mesSA_mdtHitChamber   = &( tmp_probe_mesSA_mdtHitChamber[i] );
    probe_mesSA_mdtHitR         = &( tmp_probe_mesSA_mdtHitR[i] );
    probe_mesSA_mdtHitZ         = &( tmp_probe_mesSA_mdtHitZ[i] );
    probe_mesSA_mdtHitPhi       = &( tmp_probe_mesSA_mdtHitPhi[i] );
    probe_mesSA_mdtHitResidual  = &( tmp_probe_mesSA_mdtHitResidual[i] );

    probe_mesSA_roadAw   = &( tmp_probe_mesSA_roadAw[i] );
    probe_mesSA_roadBw   = &( tmp_probe_mesSA_roadBw[i] );
    probe_mesSA_zMin   = &( tmp_probe_mesSA_zMin[i] );
    probe_mesSA_zMax   = &( tmp_probe_mesSA_zMax[i] );
    probe_mesSA_rMin   = &( tmp_probe_mesSA_rMin[i] );
    probe_mesSA_rMax   = &( tmp_probe_mesSA_rMax[i] );
    probe_mesSA_etaMin   = &( tmp_probe_mesSA_etaMin[i] );
    probe_mesSA_etaMax   = &( tmp_probe_mesSA_etaMax[i] );

    //
    probe_mesCB_pass  = &( tmp_probe_mesCB_pass[i] );
    probe_mesCB_dR    = &( tmp_probe_mesCB_dR[i] );
    probe_mesCB_tpdR  = &( tmp_probe_mesCB_tpdR[i] );
    probe_mesCB_pt    = &( tmp_probe_mesCB_pt[i] );
    probe_mesCB_eta   = &( tmp_probe_mesCB_eta[i] );
    probe_mesCB_phi   = &( tmp_probe_mesCB_phi[i] );
    probe_mesFTF_pass = &( tmp_probe_mesFTF_pass[i] );
    probe_mesFTF_dR   = &( tmp_probe_mesFTF_dR[i] );
    probe_mesFTF_pt   = &( tmp_probe_mesFTF_pt[i] );
    probe_mesFTF_eta  = &( tmp_probe_mesFTF_eta[i] );
    probe_mesFTF_phi  = &( tmp_probe_mesFTF_phi[i] );
    probe_mesEF_pass  = &( tmp_probe_mesEF_pass[i] );
    probe_mesEF_dR    = &( tmp_probe_mesEF_dR[i] );
    probe_mesEF_tpdR  = &( tmp_probe_mesEF_tpdR[i] );
    probe_mesEF_pt    = &( tmp_probe_mesEF_pt[i] );
    probe_mesEF_eta   = &( tmp_probe_mesEF_eta[i] );
    probe_mesEF_phi   = &( tmp_probe_mesEF_phi[i] );
    
    m_tree->Fill();
  }

  return 1;
}

int EventTree::finalize() {
	// write into file and close
	
	m_file->Write();	

	return 1;
}
	
// eof
