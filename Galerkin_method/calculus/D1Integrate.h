#pragma once

#include "finite_element\D1Element.h"
#include "Derivative.h"
#include "Integrate.h"

class smart_function_x
  {
  public:
    smart_function_x(const function_x_t& _f, const std::shared_ptr<D1Element>& _N_j)
      : f_x_t(_f)
      , N_j(_N_j)
      , tail_f_x([](double t){return 0;})
      {}

    double operator()(double t) const;

    void set_tail(const function_x& tail)
      {
      tail_f_x = tail;
      }
  private:
    function_x_t f_x_t;
    std::shared_ptr<D1Element> N_j;
    function_x tail_f_x;
  };

class D1Integrate
  {
  public:

    static double Integrate_Ni_Nj(const std::shared_ptr<D1Element>& lhv, const std::shared_ptr<D1Element>& rhv);

    static double Integrate_dNi_dNj(const std::shared_ptr<D1Element>& N_i, const std::shared_ptr<D1Element>& N_j)
      {
      double shared_interval_length = intervals_length( N_i->get_shared_interval(N_j) );

      if ( N_i->is_neighbor(N_j) )
        return  -1.0/shared_interval_length ;

      if ( N_i == N_j )
        {
        if ( N_i->get_node()->get_x() == 0 || N_i->is_last() )
          return 1./shared_interval_length;
        else
          return 2./shared_interval_length;
        }
      else
        return 0;
      }

    static double Integrate_f_x_N_i(const function_x& f_x, const std::shared_ptr<D1Element>& lhv)
      {
      auto f_N_x = [=] (double x) -> double
        {
        return f_x(x)*lhv->get_support_function()(x);
        };

      auto area = lhv->get_intervals();

      return std::accumulate( begin(area), end(area), 0.0, [&] (double acc, const interval& in)
        {
        return acc + Integrate::Gaussian_F_x(f_N_x,in.first,in.second);
        });  
      }

    static smart_function_x Integrate_f_x_t_Nj(const function_x_t& f_x_t, const std::shared_ptr<D1Element>& N_j)
      {
      return smart_function_x(f_x_t,N_j);
      }
  };

