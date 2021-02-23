#ifndef _VrtFitUtils
#define _VrtFitUtils

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
#include "xAODTracking/TrackParticleContainer.h"
#include "xAODTracking/VertexContainer.h"

using namespace std;

namespace Trk { 
  class IVertexFitter; 
}

class VrtFitUtils {
	
  public:
	VrtFitUtils();
	~VrtFitUtils();
  int initialize( ToolHandle<Trk::IVertexFitter> ivft );
  xAOD::Vertex* doVrtFit( const vector< const xAOD::TrackParticle* > trks, const xAOD::Vertex* pv );

  private:
    ToolHandle<Trk::IVertexFitter> m_vrtfitter;

};

#endif
