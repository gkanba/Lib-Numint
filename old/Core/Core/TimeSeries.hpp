#ifndef _IG_TIMESERIES_H_
#define _IG_TIMESERIES_H_

#include <memory>
#include "eigen3/Eigen/Dense"

#include "Core/State.hpp"

namespace Numint::Core {

template<typename T>
struct Interval {
    T begin;
    T end;
    Interval() = default;
    Interval(T begin_, T end_) : begin(begin_), end(end_) {};
    T width(){ return end - begin; }
};

class TimeSeries {
    public:
        virtual int                 dim()           = 0;
        virtual int                 len()           = 0;
        virtual double              time_width()    = 0;
        virtual Interval<double>    interval()      = 0;

};

class TimeSeriesXd : TimeSeries {
    private:
        int                                 m_Dim;
        int                                 m_Len;
        Interval<double>                    m_Interval;
        std::shared_ptr<Eigen::MatrixXd>    m_ObjPtr;
    public:
        TimeSeriesXd();
        TimeSeriesXd(const Eigen::VectorXd begin_row, const double begin_time, const double time_width);
        TimeSeriesXd(const int dim,                   const double begin_time, const double time_width);

        int                 dim();
        int                 len();
        double              time_width();
        Interval<double>    interval();
        StateXd             state(int index);
};

}

#endif