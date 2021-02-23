#include <iostream>
#include <fstream>
#include <vector>

#include "CalcEfficiency/ParticleSelecterTool.h"

#include "xAODMuon/MuonContainer.h"
#include "xAODTracking/TrackParticleContainer.h"
#include "xAODTracking/VertexContainer.h"


using namespace std;

ParticleSelecterTool::ParticleSelecterTool() {
}

ParticleSelecterTool::~ParticleSelecterTool() {
}

int ParticleSelecterTool::getQualityOfTrack( const xAOD::TrackParticle* trk ) {
  if( !trk ) return -5;
  const double trkPt                 = trk->pt(); 
  const double trkEta                = trk->eta(); 
  // Variables for QUality Cut
  uint8_t trkNBLayerHits=0, trkEBLayerHit=0,
          trkNPixelHits=0, trkNPixelDeadSensors=0,
          trkNSCTHits=0, trkNSCTDeadSensors=0,
          trkNPixelHoles=0, trkNSCTHoles=0,
          trkNTRTOutliers=0, trkNTRTHits=0, trkNTRTHighThresholdHits=0;
  trk->summaryValue( trkNBLayerHits, xAOD::numberOfBLayerHits );
  trk->summaryValue( trkEBLayerHit, xAOD::expectBLayerHit );
  trk->summaryValue( trkNPixelHits, xAOD::numberOfPixelHits );
  trk->summaryValue( trkNPixelDeadSensors, xAOD::numberOfPixelDeadSensors );
  trk->summaryValue( trkNSCTHits, xAOD::numberOfSCTHits );
  trk->summaryValue( trkNSCTDeadSensors, xAOD::numberOfSCTDeadSensors );
  trk->summaryValue( trkNPixelHoles, xAOD::numberOfPixelHoles );
  trk->summaryValue( trkNSCTHoles, xAOD::numberOfSCTHoles );
  trk->summaryValue( trkNTRTOutliers, xAOD::numberOfTRTOutliers );
  trk->summaryValue( trkNTRTHits, xAOD::numberOfTRTHits );
  trk->summaryValue( trkNTRTHighThresholdHits, xAOD::numberOfTRTHighThresholdHits );

  if( trkNBLayerHits && trkEBLayerHit <= 0 ) return -4;
  if( trkNPixelHits + trkNPixelDeadSensors <= 1 ) return -4;
  if( trkNSCTHits + trkNSCTDeadSensors <= 4 ) return -4;
  if( trkNPixelHoles + trkNSCTHoles >= 3 ) return -4;
  
  if( fabs(trkEta) < 1.9 && trkNTRTHits + trkNTRTOutliers <= 5 ) return -3;
  if( fabs(trkEta) < 1.9 && (trkNTRTHits + trkNTRTOutliers)*0.9 <= trkNTRTOutliers ) return -3;
  if( fabs(trkEta) >= 1.9 && trkNTRTHits + trkNTRTOutliers > 5 && (trkNTRTHits + trkNTRTOutliers)*0.9 <= trkNTRTOutliers ) return -3;
  
  if( trkNTRTHits == 0 ) return -2;
  if( (double)trkNTRTHighThresholdHits/(double)trkNTRTHits >= 0.2 ) return -2;
  
  if( trkPt < 2500 || fabs(trkEta) > 2.5 ) return -1;
        
  return 0;
}

int ParticleSelecterTool::getQualityOfTrack( const xAOD::Muon* muon ) {
  if( !muon ) return -6;
  const double muPt                 = muon->pt(); 
  const double muEta                = muon->eta(); 
  const double muScat 		        = muon->floatParameter( muon->scatteringCurvatureSignificance );
  const double muBalance            = muon->floatParameter( muon->momentumBalanceSignificance );
  const xAOD::Muon::Author muAuth   = muon->author();
  const xAOD::Muon::MuonType muType = muon->muonType();
  const xAOD::Muon::Quality muQual	= muon->quality();
  const xAOD::TrackParticle* mutrk = muon->trackParticle( xAOD::Muon::InnerDetectorTrackParticle );	
  if( !mutrk ) return -5;
  // Variables for QUality Cut
  uint8_t muNBLayerHits=0, muEBLayerHit=0,
          muNPixelHits=0, muNPixelDeadSensors=0,
          muNSCTHits=0, muNSCTDeadSensors=0,
          muNPixelHoles=0, muNSCTHoles=0,
          muNTRTOutliers=0, muNTRTHits=0, muNTRTHighThresholdHits=0;
  mutrk->summaryValue( muNBLayerHits, xAOD::numberOfBLayerHits );
  mutrk->summaryValue( muEBLayerHit, xAOD::expectBLayerHit );
  mutrk->summaryValue( muNPixelHits, xAOD::numberOfPixelHits );
  mutrk->summaryValue( muNPixelDeadSensors, xAOD::numberOfPixelDeadSensors );
  mutrk->summaryValue( muNSCTHits, xAOD::numberOfSCTHits );
  mutrk->summaryValue( muNSCTDeadSensors, xAOD::numberOfSCTDeadSensors );
  mutrk->summaryValue( muNPixelHoles, xAOD::numberOfPixelHoles );
  mutrk->summaryValue( muNSCTHoles, xAOD::numberOfSCTHoles );
  mutrk->summaryValue( muNTRTOutliers, xAOD::numberOfTRTOutliers );
  mutrk->summaryValue( muNTRTHits, xAOD::numberOfTRTHits );
  mutrk->summaryValue( muNTRTHighThresholdHits, xAOD::numberOfTRTHighThresholdHits );
  
  if( muNBLayerHits && muEBLayerHit <= 0 ) return -4;
  if( muNPixelHits + muNPixelDeadSensors <= 1 ) return -4;
  if( muNSCTHits + muNSCTDeadSensors <= 4 ) return -4;
  if( muNPixelHoles + muNSCTHoles >= 3 ) return -4;
  
  if( fabs(muEta) < 1.9 && muNTRTHits + muNTRTOutliers <= 5 ) return -3;
  if( fabs(muEta) < 1.9 && (muNTRTHits + muNTRTOutliers)*0.9 <= muNTRTOutliers ) return -3;
  if( fabs(muEta) >= 1.9 && muNTRTHits + muNTRTOutliers > 5 && (muNTRTHits + muNTRTOutliers)*0.9 <= muNTRTOutliers ) return -3;
        
  if( muAuth != xAOD::Muon::MuidCo ) return -2;
  if( muType!=xAOD::Muon::Combined && muType!=xAOD::Muon::SegmentTagged ) return -2;
  if( muQual!=xAOD::Muon::Medium && muQual!=xAOD::Muon::Tight) return -2;
  if( muScat >= 5 || muBalance >= 3 ) return -2;
  if( muNTRTHits == 0 ) return -2;
  if( (double)muNTRTHighThresholdHits/(double)muNTRTHits >= 0.35 ) return -2;
  
  //cout << muPt << ":" << muEta << ":" << muAuth << ":" << muType << ":" << muQual << endl;
  if( muPt < 2500 || fabs(muEta) > 2.5 ) return -1;

  return 0;
}

int ParticleSelecterTool::getQualityOfMuon( const xAOD::Muon* muon ) {
  if( !muon ) return -6;
  const double muPt                 = muon->pt(); 
  const double muEta                = muon->eta(); 
  const xAOD::Muon::Author muAuth   = muon->author();
  const xAOD::Muon::MuonType muType = muon->muonType();
  const xAOD::Muon::Quality muQual	= muon->quality();
  
  //cout << muPt << ":" << muEta << ":" << muAuth << ":" << muType << ":" << muQual << endl;

  if( muAuth != xAOD::Muon::MuidCo ) return -2;
  if( muType!=xAOD::Muon::Combined && muType!=xAOD::Muon::SegmentTagged ) return -2;
  if( muQual!=xAOD::Muon::Loose && muQual!=xAOD::Muon::Medium && muQual!=xAOD::Muon::Tight) return -2;
  
  if( muPt < 2500 || fabs(muEta) > 2.5 ) return -1;
  
  return 0;
}

xAOD::Vertex* ParticleSelecterTool::getLargestSumPtPV( const xAOD::VertexContainer* pvs ) {
  
  xAOD::VertexContainer::const_iterator pv_itr = pvs->begin();
  xAOD::VertexContainer::const_iterator pv_end = pvs->end();
  double pv_sumPt = -1; 
  xAOD::Vertex* PV = 0;

  for ( ; pv_itr!=pv_end; ++pv_itr ) {
	double tmp_sumPt = 0;
    const size_t pv_ntrk = (*pv_itr)->nTrackParticles();
	for ( size_t i=0; i<pv_ntrk; i++ ) {
	  const xAOD::TrackParticle* pvtrk = ( (*pv_itr)->trackParticle( i ) );
      double pvtrkpt = (pvtrk)? pvtrk->pt():0;
      tmp_sumPt += pvtrkpt;
    }
    //cout << "PV : " << tmp_sumPt << endl;
    if( pv_sumPt < tmp_sumPt ) {
      pv_sumPt = tmp_sumPt;
      PV = (*pv_itr);
    }
  }
  if( PV==0 ) cout << "WORNING : PV is null" << endl; 
  return PV;
}

