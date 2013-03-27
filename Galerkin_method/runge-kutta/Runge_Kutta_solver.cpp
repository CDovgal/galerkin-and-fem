#include "stdafx.h"

#include "Runge_Kutta_solver.h"

Runge_Kutta_solver::Runge_Kutta_solver(const matrix& i_A, const vector_t& i_x0, const Function_vector& f_t)
  : A(i_A)
  , x0(i_x0)
  , func_vector(f_t)
  {}

matrix Runge_Kutta_solver::get_solution(double t_step, size_t step_number)
  {
  using std::cout;
  using std::endl;

  matrix solution = b_zero_matrix(x0.size(),step_number+1);

  std::copy( begin(x0), end(x0), solution.begin1() );

  for(size_t round = 1; round <= step_number; ++round)
    {
    vector_t temp(solution.size1());
    for(size_t i = 0; i < temp.size(); ++i)
      temp(i) = solution(i,round-1);
    cout << A.size1() << " " << A.size2() << " " << temp.size() << endl;
    vector_t k1 = prod(A,temp)               + func_vector(temp);
    vector_t k2 = prod(A,temp + t_step*k1/2) + func_vector(temp + t_step*k1/2);
    vector_t k3 = prod(A,temp + t_step*k2/2) + func_vector(temp + t_step*k2/2);
    vector_t k4 = prod(A,temp + t_step*k3)   + func_vector(temp + t_step*k3);

    temp += (t_step/6)*( k1 + 2*k2 + 2*k3 + k4);

    for(size_t i = 0; i < temp.size(); ++i)
      solution(i,round) = temp(i);
    }

  return solution;
  }