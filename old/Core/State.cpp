#include "Core/State.hpp"

namespace Numint::Core
{

Timing::Timing() = default;
Timing::Timing(const int step_, const int time_) : step(step_), time(time_) {};

StateXd::StateXd() = default;

StateXd::StateXd(const int dim) {
    m_Dim    = dim;
    m_Timing = Timing(0, 0.0);
    m_ObjPtr = std::make_shared<Eigen::VectorXd>(Eigen::VectorXd::Zero(dim));
}

StateXd::StateXd(const int dim, const Timing timing) {
    m_Dim    = dim;
    m_Timing = timing;
    m_ObjPtr = std::make_shared<Eigen::VectorXd>(Eigen::VectorXd::Zero(dim));
}

Timing StateXd::timing() { return m_Timing; }
std::shared_ptr<Eigen::VectorXd> StateXd::objptr(){ return m_ObjPtr; }
    
}
