#ifndef _IG_INTEGRATION_H_
#define _IG_INTEGRATION_H_

#include "Container/TimeSeriesState.hpp"
#include "Math/ODE.hpp"

namespace Numint::Math{

enum class IntegrationMethod
{
    Euler,      // Traditional Euler Method
    RK4,        // Traditional 4th order Runge-Kutta Method
};

void integrate(Container::TimeSeriesState container, ODE& equation, const IntegrationMethod method, const int N);

}

#endif