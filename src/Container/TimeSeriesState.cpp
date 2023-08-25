#include "Container/TimeSeriesState.hpp"

#include <memory>
#include "eigen3/Eigen/Dense"
#include "Debug/Logger.hpp"

namespace Numint::Container{

TimeSeriesState::TimeSeriesState(const State init_state, const double time_width)
{
    // Store Time Width
    width = time_width;
    // Create unique ptr and insert first state (step, time, state[0], ... , state[N])
    ptr = std::make_shared<Eigen::MatrixXd>(Eigen::MatrixXd::Zero(1, init_state.state.size() + 2));
    ptr->row(0) << init_state.timer.step, init_state.timer.time, init_state.state.transpose();
}

int TimeSeriesState::dim() { return ptr->cols() - 2; }

int TimeSeriesState::len() { return ptr->rows(); }

double TimeSeriesState::step_width() { return width; }

void TimeSeriesState::resize(const int size){
    // Allocate new rows
    ptr->conservativeResize(size, Eigen::NoChange);
}

void TimeSeriesState::set(const State state, int index){
    // Insert new state (step, time, state[0], ... , state[N])
    ptr->row(index) << state.timer.step, state.timer.time, state.state.transpose();
}

void TimeSeriesState::append(const State state)
{
    // Insert new state (step, time, state[0], ... , state[N])
    ptr->bottomRows(1) << state.timer.step, state.timer.time, state.state.transpose();

}

State TimeSeriesState::state(const int index)
{
    double ts;
    double tt;
    Eigen::VectorXd sv;
    if(index >= 0){
        Eigen::VectorXd r = ptr->row(index);
        //Numint::Debug::PrintVectorObj("TEST", "r", r, Numint::Debug::IOFMT_STREAMPREC<1>);
        ts = r[0];
        tt = r[1];
        sv = r.tail(dim());
    }
    else{
        Eigen::VectorXd r = ptr->row(len() + index);
        //Numint::Debug::PrintVectorObj("TEST", "r", r, Numint::Debug::IOFMT_STREAMPREC<1>);
        ts = r[0];
        tt = r[1];
        sv = r.tail(dim());
    }
    return State(Timer(ts, tt), sv);
}

}