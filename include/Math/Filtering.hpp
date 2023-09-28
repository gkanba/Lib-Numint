#ifndef _IG_FILTERING_H_
#define _IG_FILTERING_H_

#include <iostream>

#include <eigen3/Eigen/Dense>

#include "Debug/Logger.hpp"
#include "Math/Math.hpp"
#include "Math/Random.hpp"
#include "Math/Integration.hpp"
#include "Container/State.hpp"
#include "Container/TimeSeriesState.hpp"

namespace Numint::Math{

template <int sys_dim, int obs_dim, int size_ensemble>
struct EnsembleKalmanFilterPO{
private:
    // Fundamental variables
    int step_loc;
    double time_loc;
    // System model ODEs
    ODE& model;
    // Observation Matrix
    Eigen::MatrixXd H;
    // Handling instance of System Noise
    MultivariateNormal sys_dist;
    // Handling instance of Observation Noise
    MultivariateNormal obs_dist;
    double dt;

    // Temp variables
    Eigen::MatrixXd X;
    Eigen::MatrixXd W;
    Eigen::MatrixXd Y;
public:
    EnsembleKalmanFilterPO() = default;
    EnsembleKalmanFilterPO(ODE& model_, const Eigen::MatrixXd H_, const MultivariateNormal sys_dist_, const MultivariateNormal obs_dist_, double dt_) :
    model(model_),
    H(H_),
    sys_dist(sys_dist_),
    obs_dist(obs_dist_),
    dt(dt_) {}

    void gen_ensemble(Container::State state)
    {
        X = Eigen::MatrixXd(sys_dim, size_ensemble);
        for(int e = 0; e < size_ensemble; e++){
            X.col(e) = state.state + sys_dist.random();
        }
        step_loc = state.step;
        time_loc = state.time;
    }

    void flt_ensemble(Container::State obs, bool obs_sampling)
    {
        // Estimate forward
        for(int e = 0; e < size_ensemble; e++){
            Container::State s = Container::State(step_loc, time_loc, X.col(e));
            X.col(e) = integrate_forward(s, model, IntegrationMethod::RK4, 1, 1, dt).state;
        }

        // Gen delta matrix
        W = Eigen::MatrixXd(obs_dim, size_ensemble);

        for(int e = 0; e < size_ensemble; e++){
            W.col(e) = obs_dist.random();
        }

        Eigen::MatrixXd X_h = X - (1 / size_ensemble) * X * Eigen::MatrixXd::Ones(size_ensemble, size_ensemble);
        Eigen::MatrixXd W_h = W - (1 / size_ensemble) * W * Eigen::MatrixXd::Ones(size_ensemble, size_ensemble);

        // Gen Sampling Covariance
        Eigen::MatrixXd V_h =  X_h * X_h.transpose() / (double)size_ensemble;
        Eigen::MatrixXd R_h;
        if(obs_sampling){
            R_h = X_h * X_h.transpose() / (double)(size_ensemble - 1);
        }
        else{
            R_h = obs_dist.covariance;
        }

        Y = Eigen::MatrixXd(obs_dim, size_ensemble);
        for(int e = 0; e < size_ensemble; e++){
            Y.col(e) = obs.state;
        }

        X = X + V_h * H.transpose() * (H * V_h * H.transpose() + R_h).inverse() * (Y + W_h - H * X);
        step_loc += 1;
        time_loc += dt;
    }

    Container::State get_analysis(){
        Eigen::VectorXd avg = X * Eigen::MatrixXd::Ones(size_ensemble, 1) / (double)size_ensemble;
        return Container::State(step_loc, time_loc, avg);
    }
};

}

#endif