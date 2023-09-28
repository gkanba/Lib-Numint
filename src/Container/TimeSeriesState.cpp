#include "Container/TimeSeriesState.hpp"

#include <cassert>
#include <memory>

#include "eigen3/Eigen/Dense"

#include "Debug/Logger.hpp"
#include "Math/Random.hpp"

namespace Numint::Container{

/*
    == Structure of TimeSeriesState Matrix instance (N dim model) ==

    - Step is completely equivalent to row count of the matrix.
    - Matrix size will be ( [MAX STEP SIZE] * [DIM SIZE + 2] ) 
    
    (Step),     (Time),     (state[0]),     (state[1]),     ...,    (state[N-1])
    0,          0.0,        1.0,            2.0,            ...,    3.14    
    1,          0.2,        1.12,           2.01,           ...,    3.21    
    .,          .,          .,              .,              ...,    .
    .,          .,          .,              .,              ...,    .
    100,        0.3,        1.11,           3.21,           ...,    31.31

    ================================================================
*/

TimeSeriesState::TimeSeriesState(const State init_state, const double time_width)
{
    // Store time width 
    width = time_width;
    // Create shared ptr and insert first state (step, time, state[0], ... , state[N - 1])
    ptr = std::make_shared<Eigen::MatrixXd>(Eigen::MatrixXd::Zero(1, init_state.state.size() + 2));
    // Insert first row data
    ptr->row(0) << init_state.step, init_state.time, init_state.state.transpose();

}

int TimeSeriesState::dim() { return ptr->cols() - 2; }

int TimeSeriesState::len() { return ptr->rows(); }

void TimeSeriesState::resize_cutout(const int size){
    // [ASSERTION : resize_cutout only allows you to shorten the row size]
    assert(size < len());
    ptr->conservativeResize(size, Eigen::NoChange);
}

void TimeSeriesState::resize_allocate(const int size){
    // [ASSERTION : resize_allocate only allows you to widen the row size]
    assert(size > len());
    ptr->conservativeResize(size, Eigen::NoChange);
}

void TimeSeriesState::set(const State state, const int index){
    // [ASSERTION : check index out of bound]
    assert(std::abs(index) <= len());
    // When the index is zero or positive   (like data[0], data[2])
    if(index >= 0){
        // Set new state (step, time, state[0], ... , state[N - 1])
        ptr->row(index) << state.step, state.time, state.state.transpose();
    }
    // When the index is negative           (like data[-1], Circular Referencing)
    else{
        // Set new state (step, time, state[0], ... , state[N - 1])
        ptr->row(len() + index) << state.step, state.time, state.state.transpose();
    }
}

void TimeSeriesState::set_initial(const State state)
{
    // Insert new initial state (step, time, state[0], ... , state[N - 1])
    ptr->topRows(1) << state.step, state.time, state.state.transpose();

}

void TimeSeriesState::set_latest(const State state)
{
    // Insert new latest state (step, time, state[0], ... , state[N - 1])
    ptr->bottomRows(1) << state.step, state.time, state.state.transpose();

}

State TimeSeriesState::state(const int index)
{
    // [ASSERTION : check index out of bound]
    assert(std::abs(index) <= len());
    // When the index is zero or positive   (like data[0], data[2])
    if(index >= 0){
        Eigen::VectorXd r = ptr->row(index);
        return State(r[0], r[1], r.tail(dim()));
    }
    // When the index is negative           (like data[-1], Circular Referencing)
    else{
        Eigen::VectorXd r = ptr->row(len() + index);
        return State(r[0], r[1], r.tail(dim()));
    }
}

State TimeSeriesState::state_initial(){
    Eigen::VectorXd r = ptr->row(0);
    return State(r[0], r[1], r.tail(dim()));
}

State TimeSeriesState::state_latest(){
    Eigen::VectorXd r = ptr->bottomRows(1);
    return State(r[0], r[1], r.tail(dim()));
}

void TimeSeriesState::add_normal(Math::MultivariateNormal dist){
    for(int i = 0; i < len(); i++){
        Container::State s = state(i);
        s.state += dist.random();
        set(s, i);
    }
}

// TODO : RECREATE
TimeSeriesState TimeSeriesState::error_euclid(TimeSeriesState target){
    double dt = target.width;
    State tmp_state = State(0, 0.0, Eigen::VectorXd::Zero(1));
    TimeSeriesState error = TimeSeriesState(tmp_state, dt);
    error.resize_allocate(target.len());
    for(int i = 0; i < target.len(); i++){
        Eigen::VectorXd a = state(i).state;
        Eigen::VectorXd b = target.state(i).state;
        tmp_state.step = i;
        tmp_state.time = tmp_state.time + dt;
        tmp_state.state = Eigen::VectorXd::Ones(1) * (a - b).norm();
        error.set(tmp_state, i);
    }
    return error;
}

}