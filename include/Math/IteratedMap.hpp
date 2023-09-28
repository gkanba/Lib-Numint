#ifndef _IG_ITERATEDMAP_H_
#define _IG_ITERATEDMAP_H_

#include "eigen3/Eigen/Dense"

namespace Numint::Math{

class IteratedMap{
public:
    IteratedMap() = default;
    virtual Eigen::MatrixXd Matrix();
    virtual Eigen::VectorXd next(Eigen::VectorXd state);
    virtual const char* name();
};

class ExampleLinearMap : public IteratedMap{
public:
    ExampleLinearMap() = default;
    Eigen::MatrixXd Matrix();
    Eigen::VectorXd next(Eigen::VectorXd state);
    const char* name();
};

class ExampleLinearMapSome : public IteratedMap{
public:
    ExampleLinearMapSome() = default;
    Eigen::MatrixXd Matrix();
    Eigen::VectorXd next(Eigen::VectorXd state);
    const char* name();
};

}

#endif