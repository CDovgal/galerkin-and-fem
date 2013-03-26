#include "Gausian_integration.h"

double Gaussian_integration::operator()(const std::function<double (double)>& f, double a, double b)
  {
  double C1 = ( a + b ) / 2;
  double C2 = ( b - a ) / ( 2 * sqrt(3) );

  return ( (b-a) / 2) * ( f( C1 - C2) + f(C1 + C2) );
  }