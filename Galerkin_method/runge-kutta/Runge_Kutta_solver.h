#pragma once

#include "Function_vector.h"

class Runge_Kutta_solver
  /* dx
     -- = A*x + f(x)
     dt

     x = (x1, x2, .. , xn)T

         (a11, a12, .. , a1n)
     A = (..................)
         (an1, an2, .. , ann)

         ( f1(x) )
  f(x) = ( ..... )
         ( fn(x) )
  */
  {
  public:
    Runge_Kutta_solver(const matrix& i_A, const vector_t& i_x0, const Function_vector& f_t);

    inline size_t get_dim(){return x0.size();}

    matrix get_solution(double step, size_t step_number);

  private:
    matrix A;
    vector_t x0;
    Function_vector func_vector;
  };