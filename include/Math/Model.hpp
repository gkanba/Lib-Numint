#ifndef _IG_MODEL_H_
#define _IG_MODEL_H_

#include "eigen3/Eigen/Dense"

namespace Numint::Math{

// Contains StateSpaceModel with Gaussian Additive Error and Nonlinear Sys-Obs Operator
// sys_model_linearity : If you set this true, you have to implement Matrix System Operator.
// obs_model_linearity : If you set this true, you have to implement Matrix Observation Operator.
template <bool sys_model_linearity, bool obs_model_linearity>
struct StateSpaceModelGaussian{
    /*
    // Time width of two adjacent state times in this model.
    double delta_t;
    // Function : System Operator.
    Function<Container::State, Container::State>& operator_sys;
    // Function : Observation Operator.
    Function<Container::State, Container::State>& operator_obs;
    // Parameter : System Model Error Distribution.
    Parameter<MultivariateNormal>& sys_error_dist;
    // Parameter : Observation Model Error Distribution.
    Parameter<MultivariateNormal>& obs_error_dist;
    // Parameter : System Model as a Matrix (if sys_model_linearity is true).
    Parameter<Eigen::MatrixXd>& operator_sys_matrix;
    // Parameter : Observation Model as a Matrix (if obs_model_linearity is true).
    Parameter<Eigen::MatrixXd>& operator_obs_matrix;

    // Default constructor.
    StateSpaceModelGaussian() = default;
    // Default initialization constructor.
    StateSpaceModelGaussian(
        double delta_t_,
        Function<Container::State, Container::State>& operator_sys_,
        Function<Container::State, Container::State>& operator_obs_,
        Parameter<Eigen::MatrixXd>& operator_sys_matrix_ = nullptr,
        Parameter<Eigen::MatrixXd>& operator_obs_matrix_ = nullptr,
        Parameter<MultivariateNormal>& sys_error_dist_, 
        Parameter<MultivariateNormal>& obs_error_dist_,
    ) : delta_t(delta_t),
        operator_sys(operator_sys_),
        operator_obs(operator_obs_),
        sys_error_dist(sys_error_dist_),
        obs_error_dist(obs_error_dist_),
        operator_sys_matrix(operator_sys_matrix_),
        operator_obs_matrix(operator_obs_matrix_) {}
    // Function to get Right Hand Side of System Model.
    // You must make sure that dim of observation is equal to parameter of error distribution. 
    Container::State model_sys(Container::State state)
    {
        //state.state = operator_sys(state).state + multivariate_normal(param_sys.mean(state.time), param_sys.cov(state.time));
        state.state = operator_sys(state).state + sys_error_dist.value(state.time).random();
        state.step += 1;
        state.time += delta_t;
        return state;
    }
    // Function to get Right Hand Side of Observation Model.
    // You must make sure that dim of observation is equal to parameter of error distribution. 
    Container::State model_obs(Container::State state)
    {
        state.state = operator_obs(state).state + obs_error_dist.value(state.time).random();
        return state;
    }

    Parameter<Eigen::MatrixXd> sys_matrix(){
        return operator_sys_matrix;
    }

    Parameter<Eigen::MatrixXd> obs_matrix(){
        return operator_sys_matrix;
    }
    */
};

}
#endif