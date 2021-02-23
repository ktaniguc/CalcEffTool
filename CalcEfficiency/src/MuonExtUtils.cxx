
#include "GaudiKernel/IAlgTool.h"

#include <iostream>
#include <fstream>
#include <vector>

#include "CalcEfficiency/MuonExtUtils.h"

#include "xAODTracking/TrackParticleContainer.h"
#include "xAODTracking/VertexContainer.h"
#include "xAODTrigMuon/TrigMuonDefs.h"
#include "xAODTrigMuon/L2StandAloneMuonContainer.h"
#include "xAODTrigMuon/L2StandAloneMuonAuxContainer.h"
#include "xAODTrigMuon/L2CombinedMuonAuxContainer.h"
#include "TrkParameters/TrackParameters.h"
#include "TrkExInterfaces/IExtrapolator.h"

using namespace std;
using Amg::Transform3D;
using CLHEP::HepRotation;
using CLHEP::Hep3Vector;

MuonExtUtils::MuonExtUtils()
: m_extrapolator("Trk::Extrapolator/AtlasExtrapolator"),
  m_endcapPivotPlaneMinimumRadius(0.), // minimum radius of pivot plane in endcap region
  m_endcapPivotPlaneMaximumRadius(13000.), // maximum radius of pivot plane in endcap region
  m_barrelPivotPlaneHalfLength(13000.) // half length of pivot plane in barrel region
{}

MuonExtUtils::~MuonExtUtils() {}

int MuonExtUtils::initialize( ToolHandle<Trk::IExtrapolator> exttool ) {
  m_extrapolator = exttool;
  return 0;
}

pair< double, double > MuonExtUtils::extTrack( const xAOD::TrackParticle* trk ) {
  ///this function is used for extrapolating offline track to MS plane, considering magnetic field.
  ///return make_pair( ExtEta, ExtPhi )
  //
  //
  double ExtEta=trk->eta(), ExtPhi=trk->phi();
  if( !trk ) return make_pair( ExtEta, ExtPhi );

  if( fabs(trk->eta()) < 1.05 ) {
    const Trk::TrackParameters* extRPC = extTrackToRPC( trk );
    if( !extRPC ) {
      const Trk::TrackParameters* extTGC = extTrackToTGC( trk );
      if( !extTGC ) {
        cout << "MuonExtUtils: both extrapolated track parameters on RPC and TGC is null!" << endl;
        return make_pair( ExtEta, ExtPhi );
      }
      ExtEta = extTGC->position().eta();
      ExtPhi = extTGC->position().phi();
    }
    else {
      ExtEta = extRPC->position().eta();
      ExtPhi = extRPC->position().phi();
      if( fabs(ExtEta) > 1.05 ) {
        const Trk::TrackParameters* extTGC = extTrackToTGC( trk );
        if( !extTGC ) {
          cout << "MuonExtUtils: extrapolated eta is on TGC but cannot be extrapolated on TGC." << endl;
          return make_pair( ExtEta, ExtPhi );
        }
        ExtEta = extTGC->position().eta();
        ExtPhi = extTGC->position().phi();
      }
    }
  }
  else if( fabs(trk->eta()) < 2.7 ) {
    const Trk::TrackParameters* extTGC = extTrackToTGC( trk );
    if( !extTGC ) {
      const Trk::TrackParameters* extRPC = extTrackToRPC( trk );
      if( !extRPC ) {
        cout << "MuonExtUtils: both extrapolated track parameters on RPC and TGC is null!" << endl;
        return make_pair( ExtEta, ExtPhi );
      }
      ExtEta = extRPC->position().eta();
      ExtPhi = extRPC->position().phi();
    }
    else {
      ExtEta = extTGC->position().eta();
      ExtPhi = extTGC->position().phi();
      if( fabs(ExtEta) < 1.05 ) {
        const Trk::TrackParameters* extRPC = extTrackToRPC( trk );
        if( !extRPC ) {
          cout << "MuonExtUtils: extrapolated eta is on RPC but cannot be extrapolated on RPC." << endl;
          return make_pair( ExtEta, ExtPhi );
        }
        ExtEta = extRPC->position().eta();
        ExtPhi = extRPC->position().phi();
      }
    }
  }
  else return make_pair( ExtEta, ExtPhi );
                                                                 
  return make_pair( ExtEta, ExtPhi );
}

pair< double, double > MuonExtUtils::extTrackInner( const xAOD::TrackParticle* trk ) {
  double ExtEta=trk->eta(), ExtPhi=trk->phi();
  if( !trk ) return make_pair( ExtEta, ExtPhi );

  if( fabs(trk->eta()) < 1.05 ) {
    const Trk::TrackParameters* extMDTInnBR = extTrackToMDTInnerBarrel( trk );
    if( !extMDTInnBR ) {
      const Trk::TrackParameters* extMDTInnEC = extTrackToMDTInnerEndcap( trk );
      if( !extMDTInnEC ) {
        cout << "MuonExtUtils: both extrapolated track parameters on MDT at barrel and endcap is null!" << endl;
        return make_pair( ExtEta, ExtPhi );
      }
      ExtEta = extMDTInnEC->position().eta();
      ExtPhi = extMDTInnEC->position().phi();
    }
    else {
      ExtEta = extMDTInnBR->position().eta();
      ExtPhi = extMDTInnBR->position().phi();
      if( fabs(ExtEta) > 1.05 ) {
        const Trk::TrackParameters* extMDTInnEC = extTrackToMDTInnerEndcap( trk );
        if( !extMDTInnEC ) {
          cout << "MuonExtUtils: extrapolated eta is on Endcap Inner but cannot be extrapolated on the plane." << endl;
          return make_pair( ExtEta, ExtPhi );
        }
        ExtEta = extMDTInnEC->position().eta();
        ExtPhi = extMDTInnEC->position().phi();
      }
    }
  }
  else if( fabs(trk->eta()) < 2.7 ) {
    const Trk::TrackParameters* extMDTInnEC = extTrackToMDTInnerEndcap( trk );
    if( !extMDTInnEC ) {
      const Trk::TrackParameters* extMDTInnBR = extTrackToMDTInnerBarrel( trk );
      if( !extMDTInnBR ) {
        cout << "MuonExtUtils: both extrapolated track parameters on MDT at barrel and endcap is null!" << endl;
        return make_pair( ExtEta, ExtPhi );
      }
      ExtEta = extMDTInnBR->position().eta();
      ExtPhi = extMDTInnBR->position().phi();
    }
    else {
      ExtEta = extMDTInnEC->position().eta();
      ExtPhi = extMDTInnEC->position().phi();
      if( fabs(ExtEta) < 1.05 ) {
        const Trk::TrackParameters* extMDTInnBR = extTrackToMDTInnerBarrel( trk );
        if( !extMDTInnBR ) {
          cout << "MuonExtUtils: extrapolated eta is on Barrel Inner but cannot be extrapolated on the plane." << endl;
          return make_pair( ExtEta, ExtPhi );
        }
        ExtEta = extMDTInnBR->position().eta();
        ExtPhi = extMDTInnBR->position().phi();
      }
    }
  }
  else return make_pair( ExtEta, ExtPhi );
                                                                 
  return make_pair( ExtEta, ExtPhi );
}

const Trk::TrackParameters* MuonExtUtils::extTrackToTGC( const xAOD::TrackParticle* trk ) {
  
  //const double D3PD::L1TgcTrkExtrapolationFillerTool::M3_Z = 15280.0;
  double TGC_Z = ( trk->eta()>0 )? 15280.0:-15280.0;
  Transform3D* matrix = new Transform3D( Amg::Vector3D( 0.,0.,TGC_Z ) );
  
  Trk::DiscSurface* disc = new Trk::DiscSurface( matrix,
                                                 m_endcapPivotPlaneMinimumRadius,
                                                 m_endcapPivotPlaneMaximumRadius );
  const bool boundaryCheck = true;
  const Trk::Surface* surface = disc;
  const Trk::TrackParameters* param = m_extrapolator->extrapolate(*trk,
                                                                  *surface,
                                                                  Trk::anyDirection,
                                                                  boundaryCheck,
                                                                  Trk::muon);
  delete disc;
  disc = 0;
  surface = 0;
  matrix = 0;
  return param;
}

const Trk::TrackParameters* MuonExtUtils::extTrackToRPC( const xAOD::TrackParticle* trk ) {
  
  //const double D3PD::L1TgcTrkExtrapolationFillerTool::RPC2_R_SMALL = 7478;
  //const double D3PD::L1TgcTrkExtrapolationFillerTool::RPC2_R_LARGE = 8365;
  Trk::CylinderSurface* barrel = new Trk::CylinderSurface( m_barrelPivotPlaneHalfLength, 
                                                           8365. );
  const bool boundaryCheck = true;
  const Trk::Surface* surface = barrel;
  const Trk::TrackParameters* param = m_extrapolator->extrapolate(*trk,
                                                                  *surface,
                                                                  Trk::anyDirection,
                                                                  boundaryCheck,
                                                                  Trk::muon);
  delete barrel;
  barrel = 0;
  surface = 0;
  return param;
}

const Trk::TrackParameters* MuonExtUtils::extTrackToMDTInnerEndcap( const xAOD::TrackParticle* trk ) {
  
  double MDTInnEC_Z = ( trk->eta()>0 )? 7000.0:-7000.0;
  Transform3D* matrix = new Transform3D( Amg::Vector3D( 0.,0.,MDTInnEC_Z ) );
  
  Trk::DiscSurface* disc = new Trk::DiscSurface( matrix,
                                                 m_endcapPivotPlaneMinimumRadius,
                                                 m_endcapPivotPlaneMaximumRadius );
  const bool boundaryCheck = true;
  const Trk::Surface* surface = disc;
  const Trk::TrackParameters* param = m_extrapolator->extrapolate(*trk,
                                                                  *surface,
                                                                  Trk::anyDirection,
                                                                  boundaryCheck,
                                                                  Trk::muon);
  delete disc;
  disc = 0;
  surface = 0;
  matrix = 0;
  return param;
}

const Trk::TrackParameters* MuonExtUtils::extTrackToMDTInnerBarrel( const xAOD::TrackParticle* trk ) {
  
  Trk::CylinderSurface* MDTInnBR = new Trk::CylinderSurface( m_barrelPivotPlaneHalfLength, 
                                                             4500. );
  const bool boundaryCheck = true;
  const Trk::Surface* surface = MDTInnBR;
  const Trk::TrackParameters* param = m_extrapolator->extrapolate(*trk,
                                                                  *surface,
                                                                  Trk::anyDirection,
                                                                  boundaryCheck,
                                                                  Trk::muon);
  delete MDTInnBR;
  MDTInnBR = 0;
  surface = 0;
  return param;
}

pair<double, double> MuonExtUtils::extTrackMuComb( const xAOD::L2StandAloneMuon* feature ) {
  const int nTP = feature->nTrackPositions();
  bool   isBarrel = ((feature->sAddress() != -1) ? true : false);
  //cout << "nTrack: " << nTP << endl;
  // if nTP==1, only middle SP is available.
  //if( nTP<1 ) return make_pair( feature->eta(), feature->phi() );
  double eta    = (isBarrel||nTP<1)? feature->etaMS():feature->trackPositionEta(0); 
  double phi    = (isBarrel||nTP<1)? feature->phiMS():feature->trackPositionPhi(0);
  double theta  = 2.*atan(exp(-eta));

  double p      = 0.0;
  if (sin(theta) != 0) {
    p = (feature->pt())*1000. / sin(theta);
  }
  else {
    return make_pair( -99999, -99999 );
  } 
  double charge = 1.0;
  double q_over_p = 0.;
  if (p != 0.)  {
    q_over_p = 1. / p;
    charge = p / fabs(p);
  } else {
    return make_pair( -99999, -99999 );
  }
  double pt     = feature->pt()*1000.;

  //if( !isBarrel && nTP==1 && pt!=0 ) theta  = theta + charge * 0.15 / feature->pt() - charge * 3.6 / feature->pt() / cos(theta);

  //Superpoints
  int inner  = (feature->sAddress() == -1) ? xAOD::L2MuonParameters::Chamber::EndcapInner : xAOD::L2MuonParameters::Chamber::BarrelInner;
  int middle = (feature->sAddress() == -1) ? xAOD::L2MuonParameters::Chamber::EndcapMiddle : xAOD::L2MuonParameters::Chamber::BarrelMiddle;
  
  double sp1_z = feature->superPointZ(inner);
  double sp1_R = feature->superPointR(inner);
  //double sp2_z = feature->superPointZ(middle);
  //double sp2_R = feature->superPointR(middle);

  double R     = (nTP<2)? sp1_R:feature->trackPositionR(0);
  double z     = (nTP<2)? sp1_z:feature->trackPositionZ(0);
///*
  if ( R == 0. && z == 0. && nTP<2 ) { //Middle
     if (isBarrel) {
        R = 5000;
        //theta  = theta - charge * 0.05 / feature->pt();
        //if( theta<0 ) theta = -theta;
        //else if( theta>3.14 ) theta = 3.14 - (theta-3.14);
        z = R / tan(theta);
     }
     else {
        z = 7600;
        theta  = theta - charge * 0.05 / feature->pt();
        if( theta<0 ) theta = -theta;
        else if( theta>3.14 ) theta = 3.14 - (theta-3.14);
        R = z * tan(theta);
     }
  }
//*/
  double x     = R * cos(phi);
  double y     = R * sin(phi);

  Amg::Vector3D vertex(x, y, z);
  Amg::Vector3D IP(0, 0, 0);
  Trk::PerigeeSurface beamSurface(IP);
  Trk::PerigeeSurface pgsf(vertex);
  Trk::Perigee perigeeMS(0., 0., phi, theta, q_over_p, pgsf);
  
  const Trk::Perigee* muonPerigee = (Trk::Perigee*) m_extrapolator->extrapolate(perigeeMS, beamSurface, Trk::oppositeMomentum, Trk::muon);

  //Protection against failing extrapolation
  double extr_eta;
  double extr_phi;
  double extr_pt;
  if (!muonPerigee) { //G4 probably failed, getting LUT extrapolated values
     extr_eta    = feature->eta();
     extr_phi    = feature->phi();
     extr_pt     = pt;
  } else {
     double extr_theta    = muonPerigee -> parameters()[Trk::theta];
     extr_phi      = muonPerigee -> parameters()[Trk::phi0];
     double extr_q_over_p = muonPerigee -> parameters()[Trk::qOverP];
     extr_eta      = -log(tan(extr_theta / 2.));
     int    extr_q        = (extr_q_over_p > 0 ? 1 : -1);
     extr_pt       = extr_q * 1.0e33;
     if (extr_q_over_p != 0.) {
        extr_pt = (1. / extr_q_over_p) * sin(extr_theta);
     }
  }
  return make_pair( extr_eta, extr_phi );
}

