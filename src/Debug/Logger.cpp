#include "Debug/Logger.hpp"

#include <iostream>
#include <fstream>

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
    std::cout << "Step : " << state.step << std::endl;
    std::cout << "Time : " << state.time << std::endl;
    std::cout << state.state.format(format) << std::endl;
}

void SaveMatrixObj(const char* invoker, const char* obj_name, const char* file_name, Eigen::MatrixXd obj, Eigen::IOFormat format){
    std::cout << "[IO] [Numint->" << invoker << "] " << "Trying to save matrix object " << obj_name << " as " << file_name << std::endl;
    std::ofstream stream(file_name);
    if(stream.is_open()){
        stream << obj.format(format) << std::endl;
        std::cout << "[IO] [Numint->" << invoker << "] " << "Saved matrix object " << obj_name << " as " << file_name << std::endl;
    }
    else{
        std::cout << "[IO] [Numint->" << invoker << "] " << "Unable to open file " << file_name << std::endl;
        std::cout << "[IO] [Numint->" << invoker << "] " << "Failed to save matrix object " << obj_name << " as " << file_name << std::endl;
    }
}

}