#pragma once

#include "D1Element.h"

class D1Integrate
  {
  public:
    static double Integrate_Ni_Nj(const std::shared_ptr<D1Element>& lhv, const std::shared_ptr<D1Element>& rhv);

    // Int ( f(x,t)* N(x) ) == F(t)
    // function<  function<double result (double t)> (double x, double t)  >& f
    static std::function<double (double)> Integrate_f_Nj(std::function<std::function<double (double)> (double,double)>& f, const std::shared_ptr<D1Element>& N_j);

    static double m_step;
  };