#include "stdafx.h"

#include "Build_function.h"

function_x Build_function::get_linear_f_x(double x0, double f0, double x1, double f1)
  {
  return [&] (double x) -> double
    {
    if ( x0 == x1 )
      return 0;

    auto dx = x1 - x0;
    auto dy = f1 - f0;

    return (x-x0)*(dy/dx) + f0;
    };
  }