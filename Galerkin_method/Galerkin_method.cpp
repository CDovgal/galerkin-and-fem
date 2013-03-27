// Galerkin_method.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "galerkin_method/wave_equation.h"

#include "calculus/Derivative.h"

double Derivative::m_delta = 0.01;

using std::cout;
using std::endl;

int _tmain(int argc, _TCHAR* argv[])
  {
  Wave_equation equation;
  handle_init(equation);

  cout << equation.get_solution() << endl;
  return 0;
  }
