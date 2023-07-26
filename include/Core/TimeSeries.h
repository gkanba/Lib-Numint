//    Numint - Cross Platform C++ Individual Numerical Computation Library with Eigen3.4 
//    (https://gitlab.com/libeigen/eigen.git)
//    Copyright 2023 Gakuto Kambayashi, and Contributors
//    All rights reserved.

#ifndef _IG_TIMESERIES_H_
#define _IG_TIMESERIES_H_

#include <iostream>
#include <memory>
#include <tuple>
#include "eigen3/Eigen/Dense"
namespace Numint {

template<typename T>
struct Interval {
      Interval() = default;
      Interval(const T first_, const T last_) : first(first_), last(last_) { assert(last >= first); }
      T range() { return last - first; }
      T first;
      T last;
};

enum class TimeSeriesFormat {
      //
      //    Description : .tsd [Only record state sequences.]
      //          (e.g [x_1, x_2, x_3])
      //
      STATE,
      //
      //    Description : .tsd [Only record index-state sequences.]
      //          (e.g [i, t, x_1, x_2, x_3])
      //          (Note that i start from 0, not 1!!!!)
      //
      INDEX_STATE,
      //
      //    Description : .tsd [Only record time-state sequences.]
      //          (e.g [t, x_1, x_2, x_3])
      //
      TIME_STATE,
      //
      //    Description : .tsd [Only record index-time-state sequences.]
      //          (e.g [i, t, x_1, x_2, x_3])
      //          (Note that i start from 0, not 1!!!!)
      //
      INDEX_TIME_STATE
};
//
//    Description : Abstruct class for TSD.
//
class TimeSeries {
 public:
      //    Description : Return a shared pointer <m_dat> for manipulation purposes.
      //          (Note that you must implement field <m_dat> = make_shared(Eigen::MatrixXd) in a child class.)
      //
      virtual std::shared_ptr<Eigen::MatrixXd>  shared_instance();
      //
      //    Description : Return a state vector of given descrete time index.
      //          (e.g point_by_index(2) returns m_dat[2:2, 1:<m_dim>])
      //
      virtual Eigen::VectorXd       point_by_index(const int index) = 0;
      //
      //    Description : Return a state vector of time nearest to given time.
      //
      //virtual Eigen::VectorXd       point_by_time() = 0;
      //
      //    Descirption : Return member fields.
      //
      virtual void                  append(const Eigen::VectorXd state);
      virtual int                   dim() = 0;
      virtual double                width() = 0;
      virtual Interval<double>      interval() = 0;
      virtual int                   length() = 0;
      //
      //    Description : Save sliced data as files with a given record order.
      //
      //virtual void      save(const char* filename,
      //                       const Interval<double> interval,
      //                       const TimeSeriesFormat format) = 0;
      virtual void      save(const char* filename,
                             const Interval<int> index_range,
                             const TimeSeriesFormat format) = 0;
      //
      //    Description : Print sliced data to the standard io.
      //
      //virtual void      print(const Interval<double> interval,
      //                        const TimeSeriesFormat format) = 0;
      //virtual void      print(const Interval<int> index_range,
      //                        const TimeSeriesFormat format) = 0;
};

//
//    Description : Implementation of TimeSeries for X-dim double TSD.
//
class TimeSeriesXd : TimeSeries {
 protected:
      std::shared_ptr<Eigen::MatrixXd>    m_dat_p;
      int                                 m_dim;
      int                                 m_len;
      double                              m_wdt;
      Interval<double>                    m_itv;

 public:
      //
      //    Description : Default constructor;
      //
      TimeSeriesXd();
      //
      //    Description : Constructor (Initialized with first row)
      //
      TimeSeriesXd(const Eigen::VectorXd initializer, const double width, const double time);
      //
      //    Description : Constrcutor (Initialized with multi rows)
      //
      //TimeSeriesXd(const Eigen::MatrixXd initialzier, const Interval<double> interval);
      //
      //    Description : Inherited from TimeSeries, see docs of TimeSeries.
      //
      void                          append(const Eigen::VectorXd state);
      int                           dim();
      double                        width();
      int                           length();
      Interval<double>              interval();
      virtual Eigen::VectorXd       point_by_index(const int index) = 0;
      //virtual Eigen::VectorXd       point_by_time() = 0;
      //virtual void                  save(const char* filename,
      //                                    const Interval<double> interval,
      //                                    const TimeSeriesFormat format) = 0;
      virtual void                  save(const char* filename,
                                          const Interval<int> index_range,
                                          const TimeSeriesFormat format) = 0;
      //virtual void                  print(const Interval<double> interval,
      //                                    const TimeSeriesFormat format) = 0;
      //virtual void                  print(const Interval<int> index_range,
      //                                    const TimeSeriesFormat format) = 0;
};

}  // namespace Numint

#endif  // !_IG_TIMESERIES_H_
