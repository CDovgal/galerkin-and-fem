#include "stdafx.h"

#include "D1Integrate.h"

#include "finite_element/D1Element.h"
#include "calculus/integrate.h"
#include "calculus/Derivative.h"

using namespace std;

double D1Integrate::Integrate_Ni_Nj(const shared_ptr<D1Element>& N_i, const shared_ptr<D1Element>& N_j)
  {
  auto shared_interval = N_i->get_shared_interval(N_j);

  double step = accumulate(begin(shared_interval),end(shared_interval),0.0,[] (double acc, const interval& in)
    {
    return acc + interval_length(in);
    });

  if ( N_i == N_j )
    return step/3;
  else if (N_i->is_neighbor(N_j))
    return step/6;
  else
    return 0;    
  }

/*
static double Integrate_dNi_dNj(const std::shared_ptr<D1Element>& N_i, const std::shared_ptr<D1Element>& N_j)
  {
  auto dN_i_dN_j = [&] (double x) -> double 
    {
    return Derivative::get_right_der(N_i->get_support_function())(N_i->get_node()->get_x()) +
      Derivative::get_right_der(N_j->get_support_function())(N_j->get_node()->get_x()) ;
    };

  auto area = N_i->get_shared_interval(N_j);

  return accumulate( begin(area), end(area), 0.0, [&] (double acc, const interval& in) 
    {
    return acc + Integrate::Gaussian_F_x(dN_i_dN_j,in.first,in.second);
    });
  }
  */
/*
double Integrate_f_x_N_i(const function_x& f_x, const std::shared_ptr<D1Element>& lhv)
{
auto f_N_x = [&] (double x) -> double
{
return f_x(x)*lhv->get_support_function()(x);
};

auto area = lhv->get_intervals();

return accumulate( begin(area), end(area), 0.0, [&] (double acc, const interval& in)
{
return acc + Integrate::Gaussian_F_x(f_N_x,in.first,in.second);
});  
}
*/
/*
smart_function_x Integrate_f_x_t_Nj(const function_x_t& f_x_t, const std::shared_ptr<D1Element>& N_j);
{
return smart_function_x(f_x_t,N_j);
}
*/
double smart_function_x::operator() (double t) const
  {
  auto f_x = std::bind(f_x_t,std::placeholders::_1,t);
  return D1Integrate::Integrate_f_x_N_i(f_x,N_j) + tail_f_x(t);
  }