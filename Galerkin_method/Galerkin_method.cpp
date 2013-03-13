// Galerkin_method.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>

#include "Derivative.h"
#include "Gausian_integration.h"




int _tmain(int argc, _TCHAR* argv[])
  {
  using std::cout;
  using std::endl;

  Derivative D(0.1);

  auto f = [](double x){return x*x;};

  cout << D(f,.5) << endl;

  Gaussian_integration I;
  cout << I(f,-2,2) << endl;

  return 0;
  }

