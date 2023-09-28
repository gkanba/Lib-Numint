#ifndef _IG_RANDOM_H_
#define _IG_RANDOM_H_

#include <random>

#include "eigen3/Eigen/Dense"

#include "Math/Math.hpp"

namespace Numint::Math{

// Multivariate Normal Distribution representation.
struct MultivariateNormal{
    // dimension    : dimension.
    int dimension;
    // mean         : Parameter mean vector.
    Eigen::MatrixXd mean;
    // covariance   : Parameter covariance matrix. Must be positive definite.
    Eigen::MatrixXd covariance;
    // Default constructor.
    MultivariateNormal() = default;
    // Default intializing constructor.
    MultivariateNormal(const Eigen::MatrixXd mean_, Eigen::MatrixXd covariance_) : mean(mean_), covariance(covariance_) 
    {
        dimension = mean.rows();
        assert(mean.rows() == covariance.rows());
    }
    // Function to get random vector of this Multivariate Normal Distribution.
    Eigen::MatrixXd random(){
        int dim = mean.size();
        // Setup random device and mersenne twister engine.
        std::random_device rd;
        std::mt19937 gen(rd());
        Eigen::MatrixXd v(dim, 1);
        // Generate random vector following standard multivariate normal distribution.
        for(int i = 0; i < dim; i++){
            std::normal_distribution<double> dist(0.0, 1.0);
            v(i, 0) = dist(gen);
        }
        // Transform generated random vector into generalized multivariate normal distribution with designated mean and covariance.
        Eigen::MatrixXd L = covariance.llt().matrixL();
        return mean + L * v;
    }
    // Static Function to initialize with zero mean distribution.
    static MultivariateNormal zero_mean(const Eigen::MatrixXd covariance_init){
        return MultivariateNormal(Eigen::MatrixXd::Zero(covariance_init.rows(), 1), covariance_init);
    }
    // Static Function to initialize with standard distribution of dim.
    static MultivariateNormal standard(const int dim){
        return MultivariateNormal(Eigen::MatrixXd::Zero(dim, 1), Eigen::MatrixXd::Identity(dim, dim));
    }
};

Eigen::MatrixXd multivariate_normal(const Eigen::MatrixXd mean, const Eigen::MatrixXd cov);

}

#endif 