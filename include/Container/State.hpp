#ifndef _IG_STATE_H_
#define _IG_STATE_H_

#include <eigen3/Eigen/Dense>

namespace Numint::Container{

// Contains state vector with internal discrete step and time.
// step  : internal step.
// time  : internal time.
// state : state vector.   ( Internally Eigen::VectorXd of "dim x 1" )
struct State{
    int                 step;
    double              time;
    Eigen::VectorXd     state;
    State() = default;
    State(const int step_, const double time_, const Eigen::VectorXd state_) : step(step_), time(time_), state(state_) {}
};

}

#endif