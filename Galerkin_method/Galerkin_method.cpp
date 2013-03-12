// Galerkin_method.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Derivative.h"
#include <iostream>




int _tmain(int argc, _TCHAR* argv[])
  {
  using std::cout;
  using std::endl;

  Derivative D(0.1);

  auto f = [](double x){return x*x;};

  cout << D(f,.5) << endl;

  return 0;
  }

