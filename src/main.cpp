#include <iostream>
#include "Numint.h"
#include "eigen3/Eigen/Dense"

int main(int argc, char** argv) {

      /*
      Numint::Math::Lorenz63 l63fn = Numint::Math::Lorenz63(8.0/3.0, 28.0, 10.0);
      Numint::Math::VanDerPol vdpfn = Numint::Math::VanDerPol(2.0);
      Numint::Math::ExampleLinear exlin = Numint::Math::ExampleLinear();

      Numint::Container::State state_A = Numint::Container::State(Numint::Container::Timer(0, 0.0), Eigen::VectorXd::Ones(3) * 1.0);
      Numint::Container::State state_B = Numint::Container::State(Numint::Container::Timer(0, 0.0), Eigen::VectorXd::Ones(2) * 1.0);
      Numint::Container::State state_C = Numint::Container::State(Numint::Container::Timer(0, 0.0), Eigen::VectorXd::Ones(2) * 1.0);

      Numint::Container::TimeSeriesState test_A = Numint::Container::TimeSeriesState(state_A, 0.001);
      Numint::Container::TimeSeriesState test_B = Numint::Container::TimeSeriesState(state_B, 0.001);
      Numint::Container::TimeSeriesState test_C = Numint::Container::TimeSeriesState(state_C, 0.001);
      Numint::Container::TimeSeriesState test_C_n = Numint::Container::TimeSeriesState(state_C, 0.001);

      //Numint::Math::integrate(test_A, l63fn, Numint::Math::IntegrationMethod::RK4, 10000);
      //Numint::Math::integrate(test_B, vdpfn, Numint::Math::IntegrationMethod::RK4, 10000);
      Numint::Math::integrate(test_C, exlin, Numint::Math::IntegrationMethod::RK4, 10000);
      Numint::Math::integrate_normaldist(test_C_n, exlin, Numint::Math::IntegrationMethod::RK4, 10000, Eigen::VectorXd::Zero(3), Eigen::VectorXd::Ones(3) * 0.001);

      //Numint::Debug::SaveMatrixObj("main", "test_A", "l63.tsd", *test_A.ptr, Numint::Debug::IOFMT_STREAMPREC_NOBRACE<1>);
      //Numint::Debug::SaveMatrixObj("main", "test_B", "vdp.tsd", *test_B.ptr, Numint::Debug::IOFMT_STREAMPREC_NOBRACE<1>);
      Numint::Debug::SaveMatrixObj("main", "test_C", "exlin.tsd", *test_C.ptr, Numint::Debug::IOFMT_STREAMPREC_NOBRACE<1>);
      Numint::Debug::SaveMatrixObj("main", "test_C_n", "exlin_ssm.tsd", *test_C_n.ptr, Numint::Debug::IOFMT_STREAMPREC_NOBRACE<1>);

      //for(int i = 0; i < 100; i++){
      //      Eigen::VectorXd mean = Eigen::VectorXd::Zero(3);
      //      Eigen::VectorXd var = Eigen::VectorXd::Ones(3) * 0.01;
      //      Eigen::VectorXd rand = Numint::Math::multivariate_normal(3, mean, var);
      //      Numint::Debug::PrintVectorObj("main", "rand", rand, Numint::Debug::IOFMT_STREAMPREC_NOBRACE<1>);
      //}
      */

      // Params
      Eigen::VectorXd mean_zero = Eigen::VectorXd::Zero(2);
      Eigen::VectorXd sd_obs = Eigen::VectorXd::Ones(2) * 0.01;
      Eigen::VectorXd sd_est = Eigen::VectorXd::Ones(2) * 0.1;
      Eigen::VectorXd sd_init = Eigen::VectorXd::Ones(2) * 0.1;

      Eigen::VectorXd init(2);
      init << 2.3, 1.4;


      // Map
      Numint::Math::ExampleLinearMap map = Numint::Math::ExampleLinearMap();

      // Generate Obs
      // state_true (next = Ax)
      // state_obs (next = Ax, but noise applied)
      // state_est (next = Ax + v)
      Numint::Container::State state_init = Numint::Container::State(Numint::Container::Timer(0, 0.0), init);
      Numint::Container::TimeSeriesState state_obs = Numint::Container::TimeSeriesState(state_init, 1.0);
      Numint::Container::TimeSeriesState state_est = Numint::Container::TimeSeriesState(state_init, 1.0);
      Numint::Container::TimeSeriesState state_true = Numint::Container::TimeSeriesState(state_init, 1.0);
      Numint::Container::TimeSeriesState state_kf = Numint::Container::TimeSeriesState(state_init, 1.0);
      Numint::Math::iterate(state_obs, map, 100);
      Numint::Math::iterate(state_true, map, 100);
      Numint::Math::iterate_normaldist(state_est, map, 100, mean_zero, sd_est);
      state_obs.add_normalnoise(mean_zero, sd_obs);

      Numint::Math::iterate_normaldist_kf(state_kf, state_obs, map, 100, 10, sd_init, mean_zero, sd_est, mean_zero, sd_obs);

      Numint::Debug::SaveMatrixObj("main", "state_true", "state_t.tsd", *state_true.ptr, Numint::Debug::IOFMT_STREAMPREC_NOBRACE<1>);
      Numint::Debug::SaveMatrixObj("main", "state_obs", "state_o.tsd", *state_obs.ptr, Numint::Debug::IOFMT_STREAMPREC_NOBRACE<1>);
      Numint::Debug::SaveMatrixObj("main", "state_est", "state_e.tsd", *state_est.ptr, Numint::Debug::IOFMT_STREAMPREC_NOBRACE<1>);
      Numint::Debug::SaveMatrixObj("main", "state_kf", "state_kf.tsd", *state_kf.ptr, Numint::Debug::IOFMT_STREAMPREC_NOBRACE<1>);

      Numint::Container::TimeSeriesState norm_to = state_true.error_euclid(state_obs);
      Numint::Container::TimeSeriesState norm_te = state_true.error_euclid(state_est);
      Numint::Container::TimeSeriesState norm_tkf = state_true.error_euclid(state_kf);

      Numint::Debug::SaveMatrixObj("main", "norm", "norm_to.tsd", *norm_to.ptr, Numint::Debug::IOFMT_STREAMPREC_NOBRACE<1>);
      Numint::Debug::SaveMatrixObj("main", "norm", "norm_te.tsd", *norm_te.ptr, Numint::Debug::IOFMT_STREAMPREC_NOBRACE<1>);
      Numint::Debug::SaveMatrixObj("main", "norm", "norm_tkf.tsd", *norm_tkf.ptr, Numint::Debug::IOFMT_STREAMPREC_NOBRACE<1>);
      return 0;
}
