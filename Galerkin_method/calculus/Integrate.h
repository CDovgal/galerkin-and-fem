#pragma once

#include <functional>

class Integrate
  // provides numerical integration
  {
  public:
    inline static double Gaussian_F_x(const std::function<double(double)>& f, double from, double to)
      // using only one interval
      {
      double C1 = ( from + to ) / 2;
      double C2 = ( to - from ) / ( 2 * sqrt(3) );

      return  (( to - from) / 2) * ( f( C1 - C2) + f(C1 + C2)) ;
      }

  };