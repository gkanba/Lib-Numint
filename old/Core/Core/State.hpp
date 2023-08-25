#ifndef _IG_STATE_H_
#define _IG_STATE_H_

#include <memory>
#include "eigen3/Eigen/Dense"

namespace Numint::Core {

struct Timing {
    int     step;
    double  time;
    Timing();
    Timing(const int step_, const int time_);
};

class State {
    public:
        virtual Timing                              timing()    = 0;
        virtual std::shared_ptr<Eigen::VectorXd>    objptr()    = 0;

        virtual inline double   operator[](int index) const     = 0;
        virtual inline double&  operator[](int index)           = 0;
};

class StateXd : State {
    private:
        int                                 m_Dim;
        Timing                              m_Timing;
        std::shared_ptr<Eigen::VectorXd>    m_ObjPtr;

    public:
        StateXd();
        StateXd(const int dim);
        StateXd(const int dim, const Timing timing);
        
        Timing                              timing();
        std::shared_ptr<Eigen::VectorXd>    objptr();

        inline double   operator[](int index) const {
            if(index >= 0){
                return (*m_ObjPtr)(index);
            }
            else{
                return (*m_ObjPtr)(m_Dim + index);
            }
        }
        inline double&  operator[](int index) {
            if(index >= 0){
                return (*m_ObjPtr)(index);
            }
            else{
                return (*m_ObjPtr)(m_Dim + index);
            }
        }
};
    
}

#endif