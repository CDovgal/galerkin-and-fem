#include "stdafx.h"

#include "D1Integrate.h"

using namespace std;

double D1Integrate::Integrate_Ni_Nj(const shared_ptr<D1Element>& lhv, const shared_ptr<D1Element>& rhv)
  {
  if ( lhv == rhv )
    return m_step/3;

  if ( lhv->is_neighbor(rhv) )
    return m_step/6;

  return 0;
  }

  std::function<double (double)> Integrate_f_Nj(std::function<std::function<double (double)> (double,double)>& f, const std::shared_ptr<D1Element>& N_j)
  {
  
  return [] (double a){return a;};
  }