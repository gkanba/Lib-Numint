#ifndef _IG_DA_H_
#define _IG_DA_H_

#include "eigen3/Eigen/Dense"
#include "Container/TimeSeriesState.hpp"

namespace Numint::Math{

class KalmanFilter{

private:
    // SystemModel
    Eigen::MatrixXd M;
    // ObservationModel
    Eigen::MatrixXd H;
    // SystemModel Error Cov
    Eigen::MatrixXd Q;
    // ObservationModel Error Cov
    Eigen::MatrixXd R;
    // Current Mean Cov
    Eigen::VectorXd mean_c;
    Eigen::MatrixXd cov_c;
    // Analysis Mean Cov
    Eigen::VectorXd mean_a;
    Eigen::MatrixXd cov_a;
    // Estimate(temp) Mean Cov
    Eigen::VectorXd mean_t;
    Eigen::MatrixXd cov_t;
public:
    KalmanFilter() = default;
    KalmanFilter(const Eigen::MatrixXd model_M, const Eigen::MatrixXd model_H, const Eigen::MatrixXd cov_estimate, const Eigen::MatrixXd cov_observation);
    void initalize(const Eigen::VectorXd current_mean, const Eigen::MatrixXd current_cov);
    void estimate();
    void filter(const Eigen::VectorXd obs);
    Eigen::VectorXd res_mean();
    Eigen::MatrixXd res_cov();
};

}

#endif