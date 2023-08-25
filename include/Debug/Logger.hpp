#ifndef __IG_LOGGER_H_
#define __IG_LOGGER_H_

#include "eigen3/Eigen/Dense"
#include "Container/TimeSeriesState.hpp"

namespace Numint::Debug {

    template<int precision, int aligncols>
    static const Eigen::IOFormat IOFMT_VARIABLE(precision, aligncols, ", ", "\n", "[", "]");
    template<int aligncols>
    static const Eigen::IOFormat IOFMT_STREAMPREC(Eigen::StreamPrecision, aligncols, ", ", "\n", "[", "]");
    template<int aligncols>
    static const Eigen::IOFormat IOFMT_FULLPREC(Eigen::FullPrecision, aligncols, ", ", "\n", "[", "]");

    void Info                (const char* invoker, const char* msg);
    void Warning             (const char* invoker, const char* msg);
    void Fatal               (const char* invoker, const char* msg);
    void PrintVectorObj      (const char* invoker, const char* obj_name, Eigen::VectorXd obj, Eigen::IOFormat format);
    void PrintMatrixObj      (const char* invoker, const char* obj_name, Eigen::MatrixXd obj, Eigen::IOFormat format);

    void PrintState          (const char* invoker, const char* obj_name, Container::State state, Eigen::IOFormat format);

}

#endif