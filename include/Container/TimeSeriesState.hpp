#ifndef _IG_TIMESERIESSTATE_H_
#define _IG_TIMESERIESSTATE_H_

#include <memory>
#include <vector>
#include <string>
#include "eigen3/Eigen/Dense"
#include "Container/State.hpp"
#include "Math/Random.hpp"

namespace Numint::Container{

// Struct : TimeSeriesState [ Contains and manipulate descrete time series data. ]
struct TimeSeriesState{
    // Time step width between two adjacent states
    double                              width;
    // Shared pointer to matrix which holds step, time, state vector sequence(so a matrix)
    std::shared_ptr<Eigen::MatrixXd>    ptr = nullptr;
    // Default constructor.
    TimeSeriesState             () = default;
    // Default initialization constructor
    TimeSeriesState             (const State init_state, const double time_width);
    // Function to get dimension of this class.
    int     dim                 ();
    // Function to get length of this class.
    int     len                 ();
    // Function to resize (Cutout and shrink memories).
    void    resize_cutout       (const int size);
    // Function to resize (Allocate and widen memories).
    void    resize_allocate     (const int size);
    // Function to set state of specified index.
    void    set                 (const State state, const int index);
    // Function to set initial state.
    void    set_initial         (const State state);
    // Function to set latest state.
    void    set_latest          (const State state);
    // Function to get state of specified index.
    State   state               (const int index);
    // Function to get initial state.
    State   state_initial       ();
    // Function to get latest state.
    State   state_latest        ();
    // Function to add noise.
    void    add_normal          (Math::MultivariateNormal dist);

    TimeSeriesState error_euclid(TimeSeriesState target);
};

}

#endif