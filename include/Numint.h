#ifndef _IG_NUMINT_H_
#define _IG_NUMINT_H_

#include "Debug/Logger.hpp"
#include "Container/TimeSeriesState.hpp"
#include "Math/ODE.hpp"
#include "Math/Integration.hpp"
#include "Math/DA.hpp"
#include "Math/IteratedMap.hpp"
#include "Math/Random.hpp"

namespace Numint {

struct Numint {
      static const int VERSION_YEAR       = 23;
      static const int VERSION_MONTH      = 9;
      static const int VERSION_MAJOR      = 5;
      static const int VERSION_MINOR      = 1;
};

}

#endif  // !_IG_NUMINT_H_
