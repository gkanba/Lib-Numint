#include "Math/Integration.hpp"

#include <iostream>
#include "Debug/Logger.hpp"
#include "Math/Random.hpp"
#include "Math/DA.hpp"

namespace Numint::Math{

void integrate(Container::TimeSeriesState container, ODE& equation, const IntegrationMethod method, const int N){
    double dt = container.width;
    container.resize(N);
    std::cout << "Integration Start : Without Noise" << std::endl;
    for(int i = 0; i < N - 1; i++){
        Container::State current = container.state(i);
        // Integrate forward (with a specified method)
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
        container.set(current, i + 1);
        if(i % 1000 == 0){
            std::cout << "Integration Completed : " << i << std::endl;
        }
    }
    std::cout << "Integration Done : " << N << std::endl;
}

void iterate(Container::TimeSeriesState container, IteratedMap& equation, const int N){
    double dt = container.width;
    container.resize(N);
    std::cout << "Iteration Start : Without Noise" << std::endl;
    for(int i = 0; i < N - 1; i++){
        Container::State current = container.state(i);
        // Iterate forward
        current.state = equation.next(current.state);
        // Forward step and time
        current.timer.step += 1;
        current.timer.time += dt;
        container.set(current, i + 1);
        if(i % 1000 == 0){
            std::cout << "Iteration Completed : " << i << std::endl;
        }
    }
    std::cout << "Iteration Done : " << N << std::endl;
}

void integrate_normaldist(Container::TimeSeriesState container, ODE& equation, const IntegrationMethod method, const int N, const Eigen::VectorXd mean, Eigen::VectorXd sd){
    double dt = container.width;
    container.resize(N);
    std::cout << "Integration Start : With Noise" << std::endl;
    for(int i = 0; i < N - 1; i++){
        Container::State current = container.state(i);
        // Integrate forward (with a specified method)
        switch(method){
        case IntegrationMethod::Euler:
            current.state += equation.RHS(current.state, current.timer.time) * dt + multivariate_normal(container.dim(), mean, sd);
            break;
        case IntegrationMethod::RK4:
            Eigen::VectorXd k_a = dt * equation.RHS(current.state, current.timer.time);
            Eigen::VectorXd k_b = dt * equation.RHS(current.state + 0.5 * k_a, current.timer.time + dt / 2.0);
            Eigen::VectorXd k_c = dt * equation.RHS(current.state + 0.5 * k_b, current.timer.time + dt / 2.0);
            Eigen::VectorXd k_d = dt * equation.RHS(current.state + k_c, current.timer.time + dt);
            current.state += (1.0 / 6.0) * (k_a + 2 * k_b + 2 * k_c + k_d) + multivariate_normal(container.dim(), mean, sd);
            break;
        }
        // Forward step and time
        current.timer.step += 1;
        current.timer.time += dt;
        container.set(current, i + 1);
        if(i % 1000 == 0){
            std::cout << "Integration Completed : " << i << std::endl;
        }
    }
    std::cout << "Integration Done : " << N << std::endl;
}

void iterate_normaldist(Container::TimeSeriesState container, IteratedMap& equation, const int N, const Eigen::VectorXd mean, Eigen::VectorXd sd){
    double dt = container.width;
    container.resize(N);
    std::cout << "Iteration Start : With Noise" << std::endl;
    for(int i = 0; i < N - 1; i++){
        Container::State current = container.state(i);
        // Iterate forward
        current.state = equation.next(current.state) + multivariate_normal(container.dim(), mean, sd);
        // Forward step and time
        current.timer.step += 1;
        current.timer.time += dt;
        container.set(current, i + 1);
        if(i % 1000 == 0){
            std::cout << "Iteration Completed : " << i << std::endl;
        }
    }
    std::cout << "Iteration Done : " << N << std::endl;
}

void iterate_normaldist_kf(Container::TimeSeriesState container, Container::TimeSeriesState container_obs, IteratedMap& equation, const int N, const int skip, Eigen::VectorXd sd_initial, const Eigen::VectorXd mean_sys, Eigen::VectorXd sd_sys, const Eigen::VectorXd mean_obs, Eigen::VectorXd sd_obs){
    double dt = container.width;
    container.resize(N);
    for(int j = 0; j < sd_sys.size(); j++){
            sd_sys[j] = sd_sys[j] * sd_sys[j];
    }
    for(int k = 0; k < sd_obs.size(); k++){
            sd_obs[k] = sd_obs[k] * sd_obs[k];
    }
    for(int l = 0; l < sd_initial.size(); l++){
            sd_initial[l] = sd_initial[l] * sd_initial[l];
    }
    Eigen::MatrixXd cov_base = Eigen::MatrixXd::Zero(container.dim(), container.dim());
    Eigen::MatrixXd Q = Eigen::MatrixXd::Zero(container.dim(), container.dim());
    Eigen::MatrixXd R = Eigen::MatrixXd::Zero(container_obs.dim(), container_obs.dim());
    Eigen::MatrixXd H = Eigen::MatrixXd::Identity(container.dim(), container.dim());
    cov_base.diagonal() = sd_initial;
    Q.diagonal() = sd_sys;
    R.diagonal() = sd_obs;
    std::cout << "Iteration Start : KF" << std::endl;
    for(int i = 0; i < N - 1; i++){
        Container::State current = container.state(i);
        if(i % skip == 0 && i > 0 && i < N - 1){
            // Filter next
            std::cout << "Applying KF : " << i << std::endl;
            Eigen::VectorXd obs = container_obs.state(i + 1).state;
            KalmanFilter KF = KalmanFilter(equation.Matrix(), H, Q, R);
            KF.initalize(current.state, cov_base);
            KF.estimate();
            KF.filter(obs);
            // Calculate next
            current.state = KF.res_mean();
            cov_base = KF.res_cov();
        }
        else{
            // Calculate next
            current.state = equation.next(current.state) + multivariate_normal(container.dim(), mean_sys, sd_sys);
        }
        // Forward step and time
        current.timer.step += 1;
        current.timer.time += dt;
        container.set(current, i + 1);
        if(i % 1000 == 0){
            std::cout << "Integration Completed : " << i << std::endl;
        }
    }
    std::cout << "Integration Done : " << N << std::endl;
}

Container::State integrate_forward(Container::State current_state, ODE& equation, const IntegrationMethod method, const double dt, const int N){
    Container::State analysis = current_state;
    for(int i = 0; i < N - 1; i++){
        // Integrate forward (with a specified method)
        switch(method){
        case IntegrationMethod::Euler:
            analysis.state += equation.RHS(analysis.state, analysis.timer.time) * dt;
            break;
        case IntegrationMethod::RK4:
            Eigen::VectorXd k_a = dt * equation.RHS(analysis.state, analysis.timer.time);
            Eigen::VectorXd k_b = dt * equation.RHS(analysis.state + 0.5 * k_a, analysis.timer.time + dt / 2.0);
            Eigen::VectorXd k_c = dt * equation.RHS(analysis.state + 0.5 * k_b, analysis.timer.time + dt / 2.0);
            Eigen::VectorXd k_d = dt * equation.RHS(analysis.state + k_c, analysis.timer.time + dt);
            analysis.state += (1.0 / 6.0) * (k_a + 2 * k_b + 2 * k_c + k_d);
            break;
        }
        // Forward step and time
        analysis.timer.step += 1;
        analysis.timer.time += dt;
    }
    return analysis;
}
    
}