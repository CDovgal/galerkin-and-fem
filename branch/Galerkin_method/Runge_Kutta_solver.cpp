#include "Runge_Kutta_solver.h"

Runge_Kutta_solver::Runge_Kutta_solver(const Matrix& i_A, const Vector& i_x0)
  : A(i_A)
  , x0(i_x0)
  {
  for(size_t i = 0; i < x0.size(); ++i)
    func_vector.add_function([] ( Vector ) {return 0;});
  }

Matrix Runge_Kutta_solver::get_solution(double step, size_t step_number)
  {
  using std::cout;
  using std::endl;

  Matrix solution = boost::numeric::ublas::zero_matrix<double>(x0.size(),step_number+1);
  // given conditions
  std::copy(begin(x0),end(x0),solution.begin1());
  
  //cout << "Solution matrix : " << solution << endl;
  //cout << "A = " << A << endl;

  for(size_t round = 1; round <= step_number; ++round)
    {
    Vector temp(solution.size1());
    for(size_t i = 0; i < temp.size(); ++i)
      temp(i) = solution(i,round-1);
    cout << A.size1() << " " << A.size2() << " " << temp.size() << endl;
    Vector k1 = prod(A,temp)             + func_vector(temp);
    Vector k2 = prod(A,temp + step*k1/2) + func_vector(temp + step*k1/2);
    Vector k3 = prod(A,temp + step*k2/2) + func_vector(temp + step*k2/2);
    Vector k4 = prod(A,temp + step*k3)   + func_vector(temp + step*k3);

    temp += (step/6)*( k1 + 2*k2 + 2*k3 + k4);

    for(size_t i = 0; i < temp.size(); ++i)
      solution(i,round) = temp(i);
    //cout << solution << endl;
    }

  //cout << "Solution matrix : " << solution << endl;
  return solution;
  }