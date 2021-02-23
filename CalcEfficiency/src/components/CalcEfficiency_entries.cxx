#include "GaudiKernel/DeclareFactoryEntries.h"
#include "CalcEfficiency/CalcEffAlg.h"

DECLARE_ALGORITHM_FACTORY(CalcEffAlg)

DECLARE_FACTORY_ENTRIES(MyNewPackage) {
  DECLARE_ALGORITHM(CalcEffAlg)
}
