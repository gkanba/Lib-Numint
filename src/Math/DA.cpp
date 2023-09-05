#include "Math/DA.hpp"

namespace Numint::Math{

KalmanFilter::KalmanFilter(const Eigen::MatrixXd model_M, const Eigen::MatrixXd model_H, const Eigen::MatrixXd cov_estimate, const Eigen::MatrixXd cov_observation)
 : M(model_M), H(model_H), Q(cov_estimate), R(cov_observation){}


void KalmanFilter::initalize(const Eigen::VectorXd current_mean, const Eigen::MatrixXd current_cov){
    mean_c = current_mean;
    cov_c = current_cov;
}

void KalmanFilter::estimate(){
    mean_t = M * mean_c;
    cov_t = M * cov_c * M.transpose() + Q;
}

void KalmanFilter::filter(const Eigen::VectorXd obs){
    Eigen::MatrixXd K = cov_t * H.transpose() * (H * cov_t * H.transpose() + R).inverse();
    mean_a = mean_t + K * (obs - H * mean_t);
    cov_a = cov_t - K * H * cov_t;
}

Eigen::VectorXd KalmanFilter::res_mean(){
    return mean_a;
}
Eigen::MatrixXd KalmanFilter::res_cov(){
    return cov_a;
}

}