#include "Math/Integration.hpp"

#include <iostream>
#include "Debug/Logger.hpp"
#include "Math/Random.hpp"

namespace Numint::Math{

Container::State integrate_forward(Container::State state, ODE& equation, const IntegrationMethod method, const int steps_forward, const int steps_subdivide, const double dt)
{
    double dt_subdivide = dt / steps_subdivide;
    Container::State state_next = state;
    for(int i = 0; i < steps_forward; i++){
        // Integrate forward (with a specified method)
        for(int k = 0; k < steps_subdivide; k++){
            switch(method){
            case IntegrationMethod::Euler:
                state_next.state += equation.RHS(state_next.state, state_next.time) * dt_subdivide;
                break;
            case IntegrationMethod::RK4:
                Eigen::VectorXd k_a = dt_subdivide * equation.RHS(state_next.state, state_next.time);
                Eigen::VectorXd k_b = dt_subdivide * equation.RHS(state_next.state + 0.5 * k_a, state_next.time + dt_subdivide / 2.0);
                Eigen::VectorXd k_c = dt_subdivide * equation.RHS(state_next.state + 0.5 * k_b, state_next.time + dt_subdivide / 2.0);
                Eigen::VectorXd k_d = dt_subdivide * equation.RHS(state_next.state + k_c, state_next.time + dt_subdivide);
                state_next.state += (1.0 / 6.0) * (k_a + 2 * k_b + 2 * k_c + k_d);
                break;
            }
            // Forward time
            state_next.time += dt_subdivide;
        }
        // Forward step
        state_next.step += 1;
    }
    return state_next;
}

Container::State iterate_forward(Container::State state, IteratedMap& map, const IterationMethod method, const int steps_forward)
{
    Container::State state_next = state;
    for(int i = 0; i < steps_forward - 1; i++){
        // Iterate forward (with a specified method)
        switch(method){
        case IterationMethod::Default:
            state_next.state = map.next(state_next.state);
            break;
        }
        // Forward step and time
        state_next.step += 1;
        state_next.time += 1.0;
    }
    return state_next;
}

Container::State integrate_forward_normal(Container::State state, ODE& equation, const IntegrationMethod method, const int steps_forward, const int steps_subdivide, const double dt, Parameter<MultivariateNormal>& dist)
{
    double dt_subdivide = dt / steps_subdivide;
    Container::State state_next = state;
    for(int i = 0; i < steps_forward; i++){
        // Integrate forward (with a specified method)
        for(int k = 0; k < steps_subdivide; k++){
            switch(method){
            case IntegrationMethod::Euler:
                state_next.state += equation.RHS(state_next.state, state_next.time) * dt_subdivide;
                break;
            case IntegrationMethod::RK4:
                Eigen::VectorXd k_a = dt_subdivide * equation.RHS(state_next.state, state_next.time);
                Eigen::VectorXd k_b = dt_subdivide * equation.RHS(state_next.state + 0.5 * k_a, state_next.time + dt_subdivide / 2.0);
                Eigen::VectorXd k_c = dt_subdivide * equation.RHS(state_next.state + 0.5 * k_b, state_next.time + dt_subdivide / 2.0);
                Eigen::VectorXd k_d = dt_subdivide * equation.RHS(state_next.state + k_c, state_next.time + dt_subdivide);
                state_next.state += (1.0 / 6.0) * (k_a + 2 * k_b + 2 * k_c + k_d);
                break;
            }
            state_next.state += dist.value(state_next.time).random();
            // Forward time
            state_next.time += dt_subdivide;
        }
        // Forward step
        state_next.step += 1;
    }
    return state_next;
}

Container::State iterate_forward_normal(Container::State state, IteratedMap& map, const IterationMethod method, const int steps_forward, Parameter<MultivariateNormal>& dist)
{
    Container::State state_next = state;
    for(int i = 0; i < steps_forward - 1; i++){
        // Iterate forward (with a specified method)
        switch(method){
        case IterationMethod::Default:
            state_next.state = map.next(state_next.state);
            break;
        }
        state_next.state += dist.value(state_next.time).random();
        // Forward step and time
        state_next.step += 1;
        state_next.time += 1.0;
    }
    return state_next;
}


void generate_trajectory(Container::TimeSeriesState container, ODE& equation, const IntegrationMethod method, const int steps_max, const int steps_subdivide)
{
    Numint::Debug::Info("Integration.cpp => generate_trajectory", "Start generating trajectory (Integration)");
    double dt = container.width;
    Container::State state_tmp = container.state_initial();
    container.resize_allocate(steps_max);
    for(int i = 0; i < steps_max - 1; i++){
        state_tmp = integrate_forward(state_tmp, equation, method, 1, steps_subdivide, dt);
        container.set(state_tmp, i + 1);
    }
}

void generate_trajectory(Container::TimeSeriesState container, IteratedMap& map, const IterationMethod method, const int steps_max)
{
    Numint::Debug::Info("Integration.cpp => generate_trajectory", "Start generating trajectory (Iteration)");
    Container::State state_tmp = container.state_initial();
    container.resize_allocate(steps_max);
    for(int i = 0; i < steps_max; i++){
        state_tmp = iterate_forward(state_tmp, map, method, 1);
        container.set(state_tmp, i + 1);
    }
}

void generate_trajectory_normal(Container::TimeSeriesState container, ODE& equation, const IntegrationMethod method, const int steps_max, const int steps_subdivide, Parameter<MultivariateNormal>& dist)
{
    Numint::Debug::Info("Integration.cpp => generate_trajectory", "Start generating trajectory (Integration, SSM)");
    double dt = container.width;
    Container::State state_tmp = container.state_initial();
    container.resize_allocate(steps_max);
    for(int i = 0; i < steps_max - 1; i++){
        state_tmp = integrate_forward(state_tmp, equation, method, 1, steps_subdivide, dt);
        state_tmp.state += dist.value(state_tmp.time).random();
        container.set(state_tmp, i + 1);
    }
}

void generate_trajectory_normal(Container::TimeSeriesState container, IteratedMap& map, const IterationMethod method, const int steps_max, Parameter<MultivariateNormal>& dist)
{
    Numint::Debug::Info("Integration.cpp => generate_trajectory", "Start generating trajectory (Iteration SSM)");
    Container::State state_tmp = container.state_initial();
    container.resize_allocate(steps_max);
    for(int i = 0; i < steps_max; i++){
        state_tmp = iterate_forward(state_tmp, map, method, 1);
        state_tmp.state += dist.value(state_tmp.time).random();
        container.set(state_tmp, i + 1);
    }
}

}