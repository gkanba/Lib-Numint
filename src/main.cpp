#include <iostream>
#include "Numint.h"
#include "eigen3/Eigen/Dense"

int main(int argc, char** argv) {

      using namespace Numint;

      Math::MultivariateNormal sys_dist = Math::MultivariateNormal(Eigen::MatrixXd::Zero(3, 1), 10.0 * Eigen::MatrixXd::Identity(3, 3));
      Math::MultivariateNormal obs_dist = Math::MultivariateNormal(Eigen::MatrixXd::Zero(3, 1), 10.0 * Eigen::MatrixXd::Identity(3, 3));

      Math::TimeInvariantParameter<Math::MultivariateNormal> dist_r 
            = Math::TimeInvariantParameter(Math::MultivariateNormal(Eigen::MatrixXd::Zero(3,1), 10.0 * Eigen::MatrixXd::Identity(3, 3)));

      Math::Lorenz63 model = Math::Lorenz63(8.0/3.0, 32.0, 10.0);
      Eigen::VectorXd init(3);
      init << 10.0, 10.0, 10.0;

      Container::State state_init = Container::State(0, 0.0, init);
      Container::TimeSeriesState noiseless = Container::TimeSeriesState(state_init, 0.01);
      Container::TimeSeriesState truth = Container::TimeSeriesState(state_init, 0.01);
      Container::TimeSeriesState obs = Container::TimeSeriesState(state_init, 0.01);
      Container::TimeSeriesState enkf = Container::TimeSeriesState(state_init, 0.01);

      Math::generate_trajectory(noiseless, model, Math::IntegrationMethod::RK4, 2500, 1);
      Math::generate_trajectory_normal(truth, model, Math::IntegrationMethod::RK4, 2500, 1, dist_r);
      *obs.ptr = *truth.ptr;
      obs.add_normal(obs_dist);

      Math::EnsembleKalmanFilterPO<3, 3, 100> flt = Math::EnsembleKalmanFilterPO<3, 3, 100>(model, Eigen::MatrixXd::Identity(3, 3), sys_dist, obs_dist, 0.01);

      flt.gen_ensemble(truth.state_initial());
      enkf.resize_allocate(2500);
      for(int i = 0; i < 2499; i++){
            flt.flt_ensemble(obs.state(i), true);
            enkf.set(flt.get_analysis(), i + 1);
      }

      /*
      flt.gen_ensemble(truth.state_initial());
      Container::State before = truth.state_initial();
      enkf.resize_allocate(2500);
      for(int i = 0; i < 2500 - 1; i++){
            if(i % 1 == 0){
                  int step = before.step;
                  double time = before.time;
                  flt.flt_ensemble(obs.state(i), true);
                  before = flt.get_analysis();
                  before.step = step + 1;
                  before.time = time + 0.01;
                  enkf.set(before, i + 1);
            }
            else{
                  before = Math::integrate_forward(before, model, Math::IntegrationMethod::RK4, 1, 1, 0.01);
                  enkf.set(before, i + 1);
            }
      }
      */

      Container::TimeSeriesState norm_m = truth.error_euclid(noiseless);
      Container::TimeSeriesState norm_f = truth.error_euclid(enkf);
      Debug::SaveMatrixObj("main.cpp", "noiseless", "./out/traj_m.tsd", *noiseless.ptr, Debug::IOFMT_STREAMPREC_NOBRACE<1>);
      Debug::SaveMatrixObj("main.cpp", "truth", "./out/traj_t.tsd", *truth.ptr, Debug::IOFMT_STREAMPREC_NOBRACE<1>);
      //Debug::SaveMatrixObj("main.cpp", "obs", "./out/test_obs.tsd", *obs.ptr, Debug::IOFMT_STREAMPREC_NOBRACE<1>);
      Debug::SaveMatrixObj("main.cpp", "enkf", "./out/traj_f.tsd", *enkf.ptr, Debug::IOFMT_STREAMPREC_NOBRACE<1>);

      Debug::SaveMatrixObj("main.cpp", "norm_m", "./out/norm_m.tsd", *norm_m.ptr, Debug::IOFMT_STREAMPREC_NOBRACE<1>);
      Debug::SaveMatrixObj("main.cpp", "norm_f", "./out/norm_f.tsd", *norm_f.ptr, Debug::IOFMT_STREAMPREC_NOBRACE<1>);

}
