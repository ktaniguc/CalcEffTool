# Declare the package name:
atlas_subdir( CalcEfficiency )

atlas_depends_on_subdirs( PUBLIC
  Control/AthToolSupport/AsgTools
  Control/AthenaBaseComps
  DataQuality/GoodRunsLists
  Trigger/TrigConfiguration/TrigConfInterfaces
  Trigger/TrigConfiguration/TrigConfxAOD
  Trigger/TrigConfiguration/TrigDecisionTool
  Event/xAOD/xAODTracking
  Event/xAOD/xAODTrigger
  Event/xAOD/xAODTrigMuon
  Tracking/TrkExtrapolation/TrkExInterfaces
  Tracking/TrkVertexFitter/TrkVertexFitterInterfaces
  PRIVATE
  GaudiKernel
  Event/xAOD/xAODEventInfo
  Event/xAOD/xAODMuon
  Tracking/TrkEvent/TrkParameters
  Tracking/TrkVertexFitter/TrkVKalVrtFitter
  )
# External dependencies:
find_package( CLHEP )
find_package( ROOT COMPONENTS GaudiInterface Core Tree MathCore Hist RIO pthread )

atlas_add_component( CalcEfficiency
  src/*.cxx
  src/components/*.cxx
  INCLUDE_DIRS ${ROOT_INCLUDE_DIRS} ${CLHEP_INCLUDE_DIRS}
  LINK_LIBRARIES AthenaBaseComps ${ROOT_LIBRARIES} ${CLHEP_LIBRARIES} GaudiKernel xAODEventInfo xAODMuon TrkParameters TrkVKalVrtFitter xAODTracking xAODTrigger xAODTrigMuon AsgTools GoodRunsLists TrigConfInterfaces TrigConfxAOD TrigDecisionTool )

atlas_add_library( CalcEfficiencyLib
  src/*.cxx
  PUBLIC_HEADERS CalcEfficiency
  INCLUDE_DIRS ${ROOT_INCLUDE_DIRS} ${CLHEP_INCLUDE_DIRS}
  LINK_LIBRARIES ${ROOT_LIBRARIES} ${CLHEP_LIBRARIES} AthenaBaseComps xAODTrigMuon xAODTrigger StoreGateLib EventInfo GaudiKernel xAODEventInfo xAODMuon TrkParameters TrkVKalVrtFitter AsgTools GoodRunsLists TrigConfInterfaces TrigConfxAOD TrigDecisionTool )

# Install files from the package:
atlas_install_headers( CalcEfficiency )
atlas_install_joboptions( run/CalcEffAlg_options.py )
