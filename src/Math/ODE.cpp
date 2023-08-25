#include "Math/ODE.hpp"

namespace Numint::Math{

ODE::ODE() = default;

Eigen::VectorXd ODE::RHS(Eigen::VectorXd state, double t)
{
    return Eigen::VectorXd::Zero(1);
}

Eigen::VectorXd Lorenz63::RHS(Eigen::VectorXd state, double t){
    Eigen::VectorXd LHS = Eigen::VectorXd::Zero(3);
    LHS(0) = s * (state(1) - state(0));
    LHS(1) = state(0) * r - state(1) - state(1) * state(2);
    LHS(2) = state(0) * state(1) - b * state(2);
    return LHS;
}

}