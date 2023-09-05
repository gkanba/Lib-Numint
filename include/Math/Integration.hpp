#ifndef _IG_INTEGRATION_H_
#define _IG_INTEGRATION_H_

#include "Container/TimeSeriesState.hpp"
#include "Math/ODE.hpp"
#include "Math/IteratedMap.hpp"

namespace Numint::Math{

enum class IntegrationMethod
{
    Euler,      // Traditional Euler Method
    RK4,        // Traditional 4th order Runge-Kutta Method
};

void integrate(Container::TimeSeriesState container, ODE& equation, const IntegrationMethod method, const int N);
void iterate(Container::TimeSeriesState container, IteratedMap& equation, const int N);
void integrate_normaldist(Container::TimeSeriesState container, ODE& equation, const IntegrationMethod method, const int N, const Eigen::VectorXd mean, const Eigen::VectorXd var);
void iterate_normaldist(Container::TimeSeriesState container, IteratedMap& equation, const int N, const Eigen::VectorXd mean, const Eigen::VectorXd var);
void iterate_normaldist_kf(Container::TimeSeriesState container, Container::TimeSeriesState container_obs, IteratedMap& equation, const int N, const int skip, Eigen::VectorXd sd_initial, const Eigen::VectorXd mean_sys, const Eigen::VectorXd sd_sys, const Eigen::VectorXd mean_obs, const Eigen::VectorXd sd_obs);

Container::State integrate_forward(Container::State current_state, ODE& equation, const IntegrationMethod method, const double dt, const int N);

}

#endif