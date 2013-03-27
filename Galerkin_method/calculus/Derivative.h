#pragma once

#include <functional>

class Derivative
  // provide numerical calculation
  // derivative in point
  {
  public:
    inline static std::function<double(double)> get_mid_der(const std::function<double (double)>& i_func)
      // best formula I know is
      //
      // f(x+delta) - f(x-delta)
      // ----------------------
      //        2*delta
      {
      return [&](double x) -> double
        {
        return ( i_func(x + m_delta) - i_func(x - m_delta) ) / (2 * m_delta);
        };
      }

    inline static std::function<double(double)> get_second_mid_der(const std::function<double (double)>& i_func)
      {
      return [&](double x) -> double
        {
        return ( i_func(x + m_delta) - 2*i_func(x) + i_func(x - m_delta) ) / (m_delta * m_delta);
        };
      }

    inline static std::function<double(double)> get_left_der(const std::function<double (double)>& i_func)
      // f(x-delta) - f(x)
      // ----------------------
      //        -delta
      {
      return [&] (double x) -> double
        {
        return ( i_func( x - m_delta) - i_func( x ) ) / (-m_delta);
        };
      }

    inline static std::function<double(double)> get_right_der(const std::function<double (double)>& i_func)
      // f(x+delta) - f(x)
      // ----------------------
      //        delta
      {
      return [&] (double x) -> double
        {
        return ( i_func( x + m_delta ) - i_func( x ) ) / (m_delta);
        };
      }

  private:
    static double m_delta;
  };