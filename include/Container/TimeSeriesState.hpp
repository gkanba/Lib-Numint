#ifndef _IG_TIMESERIESSTATE_H_
#define _IG_TIMESERIESSTATE_H_

#include <memory>
#include "eigen3/Eigen/Dense"

namespace Numint::Container{

struct Timer{
    int     step;
    double  time;
    Timer() = default;
    Timer(const int step_, const double time_) : step(step_), time(time_) {}
};

struct State{
    Timer           timer;
    Eigen::VectorXd state;
    State() = default;
    State(const Timer timer_, const Eigen::VectorXd state_) : timer(timer_), state(state_) {}
};


//
//  Struct : TimeSeriesState [ Contains and manipulate descrete time series data. ]
//
struct TimeSeriesState{
    // Time step width between two adjacent states
    double                              width;
    // Shared pointer to matrix which holds step, time, state vector sequence(so a matrix)
    std::shared_ptr<Eigen::MatrixXd>    ptr = nullptr;
    TimeSeriesState() = default;
    TimeSeriesState(const State init_state, const double time_width);
    int dim();
    int len();
    double step_width();
    void append(const State state);
    State state(const int index);
};

}

#endif