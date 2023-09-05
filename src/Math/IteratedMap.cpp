#include "Math/IteratedMap.hpp"

namespace Numint::Math{

Eigen::MatrixXd IteratedMap::Matrix(){
    return Eigen::MatrixXd::Zero(1, 1);
}

Eigen::VectorXd IteratedMap::next(Eigen::VectorXd state){
    return Eigen::VectorXd::Zero(1);
}

Eigen::MatrixXd ExampleLinearMap::Matrix(){
    Eigen::MatrixXd A(2, 2);
    A << 0.0, 1.0, -1.0, 0;
    return A;
}

Eigen::VectorXd ExampleLinearMap::next(Eigen::VectorXd state){
    Eigen::VectorXd LHS = Eigen::VectorXd::Zero(2);
    LHS = Matrix() * state;
    return LHS;
}

Eigen::MatrixXd ExampleLinearMapSome::Matrix(){
    Eigen::MatrixXd A(2, 2);
    A << 1.0, 2.0, -1.0, 3.0;
    return A;
}

Eigen::VectorXd ExampleLinearMapSome::next(Eigen::VectorXd state){
    Eigen::VectorXd LHS = Eigen::VectorXd::Zero(2);
    LHS = Matrix() * state;
    return LHS;
}

}