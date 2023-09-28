#ifndef _IG_ODE_H_
#define _IG_ODE_H_

#include "eigen3/Eigen/Dense"

namespace Numint::Math{

class ODE{
public:
    ODE();
    virtual Eigen::VectorXd RHS(Eigen::VectorXd state, double t);
    virtual const char* name();
};

class Lorenz63 : public ODE{

private:
    double b;
    double r;
    double s;
public:
    Lorenz63() = default;
    Lorenz63(double beta, double rho, double sigma) : b(beta), r(rho), s(sigma) {};
    Eigen::VectorXd RHS(Eigen::VectorXd state, double t);
    const char* name();

};

class VanDerPol : public ODE{

private:
    double m;
public:
    VanDerPol() = default;
    VanDerPol(double mu) : m(mu) {};
    Eigen::VectorXd RHS(Eigen::VectorXd state, double t);
    const char* name();
};

}

#endif