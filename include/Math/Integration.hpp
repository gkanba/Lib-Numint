#ifndef _IG_INTEGRATION_H_
#define _IG_INTEGRATION_H_

#include "Container/TimeSeriesState.hpp"
#include "Math/ODE.hpp"
#include "Math/Random.hpp"
#include "Math/IteratedMap.hpp"

namespace Numint::Math{

enum class IntegrationMethod
{
    Euler,      // Traditional Euler Method
    RK4,        // Traditional 4th order Runge-Kutta Method
};

enum class IterationMethod
{
    Default,    // Default Solving DifferenceEquation
};

Container::State integrate_forward(Container::State state, ODE& equation, const IntegrationMethod method, const int steps_forward, const int steps_subdivide, const double dt);
Container::State iterate_forward(Container::State state, IteratedMap& map, const IterationMethod method, const int steps_forward);
Container::State integrate_forward_normal(Container::State state, ODE& equation, const IntegrationMethod method, const int steps_forward, const int steps_subdivide, const double dt, Parameter<MultivariateNormal>& dist);
Container::State iterate_forward_normal(Container::State state, IteratedMap& map, const IterationMethod method, const int steps_forward, Parameter<MultivariateNormal>& dist);


void generate_trajectory(Container::TimeSeriesState container, ODE& equation, const IntegrationMethod method, const int steps_max, const int steps_subdivide);
void generate_trajectory(Container::TimeSeriesState container, IteratedMap& map, const IterationMethod method, const int steps_max);
void generate_trajectory_normal(Container::TimeSeriesState container, ODE& equation, const IntegrationMethod method, const int steps_max, const int steps_subdivide, Parameter<MultivariateNormal>& dist);
void generate_trajectory_normal(Container::TimeSeriesState container, IteratedMap& map, const IterationMethod method, const int steps_max, Parameter<MultivariateNormal>& dist);

}

#endif