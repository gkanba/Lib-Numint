#include "Debug/Logger.hpp"

#include <iostream>

namespace Numint::Debug {

void Info       (const char* invoker, const char* msg) {
    std::cout << "[INFO] [Numint->" << invoker << "] " << msg << std::endl;
}
void Warning    (const char* invoker, const char* msg) {
    std::cout << "[WARN] [Numint->" << invoker << "] " << msg << std::endl;
}
void Fatal      (const char* invoker, const char* msg) {
    std::cout << "[FTAL] [Numint->" << invoker << "] " << msg << std::endl;
}

void PrintVectorObj (const char* invoker, const char* obj_name, Eigen::VectorXd obj, Eigen::IOFormat format) {
    std::cout << "[VECT] [Numint->" << invoker << "] " << obj_name << " =" << std::endl;
    std::cout << obj.format(format) << std::endl;
}

void PrintMatrixObj (const char* invoker, const char* obj_name, Eigen::MatrixXd obj, Eigen::IOFormat format) {
    std::cout << "[MATX] [Numint->" << invoker << "] " << obj_name << " =" << std::endl;
    std::cout << obj.format(format) << std::endl;
}

void PrintState (const char* invoker, const char* obj_name, Container::State state, Eigen::IOFormat format){
    std::cout << "[STATE] [Numint->" << invoker << "] " << obj_name << " =" << std::endl;
    std::cout << "Step : " << state.timer.step << std::endl;
    std::cout << "Time : " << state.timer.time << std::endl;
    std::cout << state.state.format(format) << std::endl;
}

}