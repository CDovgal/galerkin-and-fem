#pragma once

#include <functional>

class Derivative
  // provide numerical calculation
  // derivative in point
  {
  public:
    Derivative(double i_delta)
      :m_delta(i_delta)
      {}

    // best formula I know is
    //
    // f(x+delta) - f(x-delta)
    // ----------------------
    //        2*delta
    inline double operator()(const std::function<double (double)>& i_func, double i_point)
      {
      return ( i_func(i_point + m_delta) - i_func(i_point - m_delta) ) / (2 * m_delta);
      }

    inline void set_delta(double new_step)
      {
      m_delta = new_step;
      }

    inline double get_delta()
      {
      return m_delta;
      }

  private:
    double m_delta;
  };