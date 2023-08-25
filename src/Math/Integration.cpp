#include "Math/Integration.hpp"

#include "Debug/Logger.hpp"

namespace Numint::Math{

void integrate(Container::TimeSeriesState container, ODE& equation, const IntegrationMethod method, const int N){
    double dt = container.width;
    for(int i = 0; i < N; i++){
        Container::State current = container.state(-1);
        // Integrade forward (with a specified method)
        switch(method){
        case IntegrationMethod::Euler:
            current.state += equation.RHS(current.state, current.timer.time) * dt;
            break;
        case IntegrationMethod::RK4:
            Eigen::VectorXd k_a = dt * equation.RHS(current.state, current.timer.time);
            Eigen::VectorXd k_b = dt * equation.RHS(current.state + 0.5 * k_a, current.timer.time + dt / 2.0);
            Eigen::VectorXd k_c = dt * equation.RHS(current.state + 0.5 * k_b, current.timer.time + dt / 2.0);
            Eigen::VectorXd k_d = dt * equation.RHS(current.state + k_c, current.timer.time + dt);
            current.state += (1.0 / 6.0) * (k_a + 2 * k_b + 2 * k_c + k_d);
            break;
        }
        // Forward step and time
        current.timer.step += 1;
        current.timer.time += dt;
        container.append(current);
    }
}

    
}