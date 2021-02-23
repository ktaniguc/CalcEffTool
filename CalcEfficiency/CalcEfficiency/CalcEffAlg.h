#ifndef CALCEFFALG_H // Include gu2ard
#define CALCEFFALG_H

// Base
#include "AthenaBaseComps/AthAlgorithm.h"

class ITHistSvc;

// ASG Tools
#include "AsgTools/AsgToolsConf.h"
#include "AsgTools/AsgMetadataTool.h"
#include "AsgTools/AsgTool.h"
#include "AsgTools/ToolHandle.h"

// Official Tools
#include "TrigConfxAOD/xAODConfigTool.h"
#include "TrigConfInterfaces/ITrigConfigSvc.h"
#include "TrigDecisionTool/TrigDecisionTool.h"
#include "GoodRunsLists/IGoodRunsListSelectionTool.h"

// ROOT

// My class
#include "CalcEfficiency/ParticleSelecterTool.h"
#include "CalcEfficiency/TagAndProbe.h"
#include "CalcEfficiency/MuInfoGetter.h"
#include "CalcEfficiency/MuonExtUtils.h"
#include "CalcEfficiency/VrtFitUtils.h"
#include "CalcEfficiency/EventTree.h"
#include "CalcEfficiency/EventTreeFCBM.h"

// forward
class GoodRunsListSelectionTool;
namespace CP {
  class MuonCalibrationAndSmearingTool;
}
namespace TrigConf {
  class xAODConfigTool;
  class ITrigConfigTool;
}
namespace Trig {
  class TrigDecisionTool;
}
namespace Trk {
  class IExtrapolator;
  class IVertexFitter;
}


class CalcEffAlg:public AthAlgorithm
{

  public:
    CalcEffAlg(const std::string& name, ISvcLocator* pSvcLocator); // Constructor

    StatusCode initialize();
    StatusCode finalize();
    StatusCode execute();

  private:
    std::string m_message;
    std::string m_etname;
    std::string m_dataType;
    bool m_isFirstEvent; //!

    // GRL tool
    ToolHandle<IGoodRunsListSelectionTool> m_grlTool;
    bool m_useGRL; //!

    // The decision tool
    ServiceHandle< TrigConf::ITrigConfigSvc> m_configSvc; //!
    ServiceHandle< TrigConf::ITrigConfigSvc> m_dsSvc; //!
    ToolHandle<Trig::TrigDecisionTool> m_trigDecTool; //!

    // Extrapolator Class
    ToolHandle<Trk::IExtrapolator> m_extrapolator;

    // ParticleSelecter Class
    ParticleSelecterTool m_pst; //!

    // MuonExtUtils Class
    MuonExtUtils m_ext; //!
    bool m_useExt; //!

    // VertexFitter Tool
    ToolHandle<Trk::IVertexFitter> m_vrtfitter;

    // VrtFitUtils Class
    VrtFitUtils m_vft; //!

    // TagAndProbe Class
    TagAndProbe m_tap; //!
    std::string m_tapmethod; //!

    //MuInfoGetter Class
    MuInfoGetter m_mig;

    //EventTree
    EventTree m_et;
    EventTreeFCBM m_etfcbm; //!

    dk::Utils m_utils;
};

#endif // CALCALG_H
