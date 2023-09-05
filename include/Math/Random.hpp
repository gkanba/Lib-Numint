#ifndef _IG_RANDOM_H_
#define _IG_RANDOM_H_

#include "eigen3/Eigen/Dense"
#include "Container/TimeSeriesState.hpp"

namespace Numint::Math{

Eigen::VectorXd multivariate_normal(const int dim, Eigen::VectorXd mean, Eigen::VectorXd sd);

}

#endif 