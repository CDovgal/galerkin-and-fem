#pragma once

#include <functional>

class Gaussian_integration
  // provides numerical integration
  // !!!!!
  // using only one interval
  //

  {
  public:

    double operator()(const std::function<double(double)>& i_func, double from, double to);

  private:
    
  };