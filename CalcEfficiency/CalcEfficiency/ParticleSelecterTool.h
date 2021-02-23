#ifndef _CalcEfficiency_ParticleSelecterTool
#define _CalcEfficiency_ParticleSelecterTool

#include <iostream>
#include <fstream>
#include <vector>

#include "xAODMuon/MuonContainer.h"
#include "xAODTracking/TrackParticleContainer.h"
#include "xAODTracking/VertexContainer.h"


using namespace std;

class ParticleSelecterTool {
	
	public:
	ParticleSelecterTool();
	~ParticleSelecterTool();

    int getQualityOfTrack( const xAOD::TrackParticle* trk );
    int getQualityOfTrack( const xAOD::Muon* muon );
    int getQualityOfMuon( const xAOD::Muon* muon );
    xAOD::Vertex* getLargestSumPtPV( const xAOD::VertexContainer* pvs );

};

#endif
