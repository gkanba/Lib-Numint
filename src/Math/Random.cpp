#include "Math/Random.hpp"

#include <random>
#include "eigen3/Eigen/Dense"

namespace Numint::Math{

// Generate pseudo random vector following multivariate normal distribution.
// mean : normal distribution mean.         ( Internally Eigen::MatrixXd of "dim x 1" )
// cov  : normal distribution covariance.   ( Internally Eigen::MatrixXd of "dim x dim" )
Eigen::MatrixXd multivariate_normal(const Eigen::MatrixXd mean, const Eigen::MatrixXd cov){
    int dim = mean.size();
    // Setup RandomNumberGenerator.
    std::random_device rd;
    std::mt19937 gen(rd());
    Eigen::MatrixXd v(dim, 1);
    // Generate random vector following standard multivariate normal distribution.
    for(int i = 0; i < dim; i++){
        std::normal_distribution<double> dist(0.0, 1.0);
        v(i, 0) = dist(gen);
    }
    // Transform this random vector into generalized multivariate normal distribution with designated mean and covariance.
    Eigen::MatrixXd L = cov.llt().matrixL();
    return mean + L * v;
}

}