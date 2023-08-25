#include <iostream>
#include "Numint.h"
#include "eigen3/Eigen/Dense"

int main(int argc, char** argv) {
      //std::cout << Numint::Numint::VERSION_YEAR << std::endl;

      //Numint::Core::StateXd state = Numint::Core::StateXd(4, Numint::Core::Timing(1, 10.0));

      //state[0] = 0.1;
      //state[1] = 1.2;
      //state[2] = 2.3;
      //state[3] = 3.4;

      //Numint::Debug::PrintVectorObj("Main.cpp 1", "state", *state.objptr(), Numint::Debug::IOFMT_STREAMPREC<0>);

      Numint::Math::Lorenz63 l63fn = Numint::Math::Lorenz63(8.0/3.0, 28.0, 10.0);

      Numint::Container::State state_A = Numint::Container::State(Numint::Container::Timer(0, 0.0), Eigen::VectorXd::Ones(3));
      //Numint::Container::State state_ap = Numint::Container::State(Numint::Container::Timer(1, 0.01), Eigen::VectorXd::Ones(3));
      Numint::Container::TimeSeriesState test = Numint::Container::TimeSeriesState(state_A, 0.01);
      //test.append(state_ap);
      //Numint::Container::State state_B = test.state(-1);

      //Numint::Debug::PrintState("main-23", "state_A", state_A, Numint::Debug::IOFMT_STREAMPREC<1>);
      //Numint::Debug::PrintState("main-24", "state_B", state_B, Numint::Debug::IOFMT_STREAMPREC<1>);

      //Numint::Math::integrate(test, l63fn, Numint::Math::IntegrationMethod::Euler, 99);
      Numint::Math::integrate(test, l63fn, Numint::Math::IntegrationMethod::RK4, 99);

      Numint::Debug::PrintMatrixObj("MAT", "MAT", *test.ptr, Numint::Debug::IOFMT_STREAMPREC<1>);

      return 0;
}
