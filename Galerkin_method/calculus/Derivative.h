#pragma once

#include <functional>

class Derivative
  // provide numerical calculation
  // derivative in point
  {
  public:


    inline static function_x get_mid_der(const function_x& i_func)
      // best formula I know is
      //
      // f(x+delta) - f(x-delta)
      // ----------------------
      //        2*delta
      {
      return [=](double x) -> double
        {
        return ( i_func(x + m_delta) - i_func(x - m_delta) ) / (2 * m_delta);
        };
      }

    inline static function_x get_second_mid_der(const function_x& i_func)
      {
      return [=](double x) -> double
        {
        return ( i_func(x + m_delta) - 2*i_func(x) + i_func(x - m_delta) ) / (m_delta * m_delta);
        };
      }

    inline static function_x get_left_der(const function_x& i_func)
      // f(x-delta) - f(x)
      // ----------------------
      //        -delta
      {
      return [=] (double x) -> double
        {
        return ( i_func( x - m_delta) - i_func( x ) ) / (-m_delta);
        };
      }

    inline static function_x get_right_der(const function_x& i_func)
      // f(x+delta) - f(x)
      // ----------------------
      //        delta
      {
      return [=] (double x) -> double
        {
        return ( i_func( x + m_delta ) - i_func( x ) ) / (m_delta);
        };
      }

    inline static function_x get_der_N_i(const std::shared_ptr<D1Element>& N_i)
      {
      auto N_i_support = N_i->get_support_function();

      if ( N_i->get_node()->get_x() == 0)
        return get_right_der(N_i_support);
      else if ( N_i->is_last() )
        return get_left_der(N_i_support);
      else 
        return get_mid_der(N_i_support);
      }

  private:
    static double m_delta;
    static double m_L;
  };