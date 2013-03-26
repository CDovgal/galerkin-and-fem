#pragma once

#include <functional>

#include "Typedefs.h"

#include "Function_vector.h"


class Runge_Kutta_solver
  /* dx
     -- = A*x + f(x)
     dt

     x = (x1, x2, .. , xn)T

         (a11, a12, .. , a1n)
     A = (..................)
         (an1, an2, .. , ann)
     
  f(x) = f(x1, x2, .. , xn)

         ( f1(x) )
  f(x) = ( ..... )
         ( fn(x) )
  */
  {
  public:
    Runge_Kutta_solver(const Matrix& i_A, const Vector& i_x0);

    inline size_t get_dim(){return x0.size();}

    Matrix get_solution(double step, size_t step_number);

    inline void add_function(const std::function<double (Vector) >& i_function)
      {func_vector.add_function(i_function);}

  private:
    Matrix A;
    Vector x0;
    Function_vector func_vector;
  };