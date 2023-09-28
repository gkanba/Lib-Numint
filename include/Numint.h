#ifndef _IG_NUMINT_H_
#define _IG_NUMINT_H_

#include "Utility.hpp"

#include "Debug/Logger.hpp"

#include "Math/Math.hpp"
#include "Math/Model.hpp"
#include "Math/ODE.hpp"
#include "Math/IteratedMap.hpp"
#include "Math/Random.hpp"
#include "Math/Integration.hpp"
#include "Math/Filtering.hpp"

#include "Container/State.hpp"
#include "Container/TimeSeriesState.hpp"
#include "Container/History.hpp"

namespace Numint {

struct Numint {
      static const int VERSION_YEAR       = 23;
      static const int VERSION_MONTH      = 9;
      static const int VERSION_MAJOR      = 27;
      static const int VERSION_MINOR      = 1;
};

}

#endif  // !_IG_NUMINT_H_
