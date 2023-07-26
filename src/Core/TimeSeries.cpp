#include "Core/TimeSeries.h"

#include "eigen3/Eigen/Dense"
#include <fstream>
#include <memory>
#include <string>

namespace Numint {

TimeSeriesXd::TimeSeriesXd(const Eigen::VectorXd initializer, const double width, const double time) {
      m_dim = initializer.size();
      m_wdt = width;
      m_itv = Interval<double>(time, time);
      m_dat_p = std::make_shared<Eigen::MatrixXd>(Eigen::MatrixXd::Zero(1, m_dim + 1));
      m_dat_p->topRows(1) << time, initializer.transpose();
}

void TimeSeriesXd::append(const Eigen::VectorXd state) {
      m_itv.last += m_wdt;
      m_dat_p->conservativeResize(m_dat_p->rows(), Eigen::NoChange);
      m_dat_p->bottomRows(1) << m_itv.last, state.transpose();
}

int TimeSeriesXd::dim() { return m_dim; }
int TimeSeriesXd::length() { return m_len; }
double TimeSeriesXd::width() { return m_wdt; }
Interval<double> TimeSeriesXd::interval() { return m_itv; }

Eigen::VectorXd TimeSeriesXd::point_by_index(const int index) {
      assert(m_dat_p->rows() > index);
      return (*m_dat_p)(index, Eigen::seqN(1, Eigen::last));
}

void TimeSeriesXd::save(const char *filename, const Interval<int> index_range, const TimeSeriesFormat format) {
      assert(index_range.last < m_dat_p->rows());

      std::string path(filename);
      path += ".tsd";
      std::ofstream stream(path);
      if(!stream){
            std::cout << "Unable to open file : " << filename << std::endl;
      }
      else {
            switch (format) {
                  case TimeSeriesFormat::INDEX_TIME_STATE:
                        for(int i = index_range.first; i < index_range.last; i++) {
                              stream << i << "\t" << (*m_dat_p)(i, 0) << "\t" << m_dat_p->row(i)(Eigen::seqN(1, Eigen::last)) << std::endl;     
                        }
                        break;
                  default:
                        break;
            }
      }
}

}
