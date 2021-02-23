#ifndef _MuonExtUtils
#define _MuonExtUtils

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
#include "xAODTrigMuon/L2StandAloneMuonContainer.h"
#include "xAODTrigMuon/L2StandAloneMuonAuxContainer.h"
#include "xAODTrigMuon/L2CombinedMuonAuxContainer.h"

using namespace std;

namespace Trk { 
  class IExtrapolator; 
}

class MuonExtUtils {
	
  public:
	MuonExtUtils();
	~MuonExtUtils();
    int initialize( ToolHandle<Trk::IExtrapolator> iext );
    pair< double, double > extTrack( const xAOD::TrackParticle* trk );
    pair< double, double > extTrackInner( const xAOD::TrackParticle* trk );
    const Trk::TrackParameters* extTrackToTGC( const xAOD::TrackParticle* trk );
    const Trk::TrackParameters* extTrackToRPC( const xAOD::TrackParticle* trk );
    const Trk::TrackParameters* extTrackToMDTInnerEndcap( const xAOD::TrackParticle* trk );
    const Trk::TrackParameters* extTrackToMDTInnerBarrel( const xAOD::TrackParticle* trk );
    pair<double, double> extTrackMuComb( const xAOD::L2StandAloneMuon* feature );

  private:
    ToolHandle<Trk::IExtrapolator> m_extrapolator;
    double m_endcapPivotPlaneMinimumRadius;
    double m_endcapPivotPlaneMaximumRadius;
    double m_barrelPivotPlaneHalfLength;

};

#endif
