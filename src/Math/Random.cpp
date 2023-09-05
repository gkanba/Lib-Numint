#include "Math/Random.hpp"

#include <random>
#include "eigen3/Eigen/Dense"

namespace Numint::Math{

Eigen::VectorXd multivariate_normal(const int dim, Eigen::VectorXd mean, Eigen::VectorXd sd){
    std::random_device rd;
    std::mt19937 gen(rd());
    Eigen::VectorXd generated(dim);
    for(int i = 0; i < dim; i++){
        std::normal_distribution<double> dist(mean[i], sd[i]);
        generated[i] = dist(gen);
    }
    return generated;
}

}