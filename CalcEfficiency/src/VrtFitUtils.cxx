
#include "GaudiKernel/IAlgTool.h"

#include <iostream>
#include <fstream>
#include <vector>

#include "CalcEfficiency/VrtFitUtils.h"

#include "xAODTracking/TrackParticleContainer.h"
#include "xAODTracking/VertexContainer.h"
#include "TrkParameters/TrackParameters.h"
#include "TrkExInterfaces/IExtrapolator.h"
#include "TrkVKalVrtFitter/TrkVKalVrtFitter.h"
#include "TrkVertexFitterInterfaces/IVertexFitter.h"

using namespace std;
using Amg::Transform3D;
using CLHEP::HepRotation;
using CLHEP::Hep3Vector;

VrtFitUtils::VrtFitUtils()
{}

VrtFitUtils::~VrtFitUtils() {}

int VrtFitUtils::initialize( ToolHandle<Trk::IVertexFitter> ivft ) {
  m_vrtfitter     = ivft;
  return 0;
}

xAOD::Vertex* VrtFitUtils::doVrtFit( const vector< const xAOD::TrackParticle* > trks, const xAOD::Vertex* pv ) {
  //cout << "VrtFitUtils: " << trks.size() << endl;
  if( trks.size() < 2 ) {
    cout << "Warning:VrtFitUtils: # of tracks is too small( 0 or 1 )." << endl;
    return NULL;
  }
  if( !pv ) {
    cout << "Warning:VrtFitUtils: pv is null." << endl;
    return NULL;
  }
  Amg::Vector3D tmp_pvpos( pv->x(), pv->y(), pv->z() );
  Trk::Vertex pvpos( tmp_pvpos );

  //xAOD::Vertex* sv = m_vrtfitter->fit( trks, pvpos ); 
  xAOD::Vertex* sv = 0;
  if( !sv ) {
    cout << "Warning:VrtFitUtils: fitted vertex is null." << endl;
    return NULL;
  }
  /*
  cout << "Info:VrtFitUtils: x=" << pv->x() << " --> " << sv->x() << "\n" 
       << "                  y=" << pv->y() << " --> " << sv->y() << "\n"
       << "                  z=" << pv->z() << " --> " << sv->z() << "\n"
       << "               ndof=" << sv->numberDoF() << "\n"
       << "               chi2=" << sv->chiSquared() << endl;
  */
  return sv;
}
