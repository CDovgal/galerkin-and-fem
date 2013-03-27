#include "stdafx.h"

#include "finite_element\D1Node.h"
#include "finite_element\D1Element.h"

#include "calculus\Derivative.h"
#include "calculus\Integrate.h"
#include "calculus\D1Integrate.h"

#include "algorithm\InverseMatrix.h"

#include "runge-kutta/Runge_Kutta_solver.h"

#include "wave_equation.h"

using namespace std;

void handle_init(Wave_equation& equation)
  {
  double p_square = 1;
  double L = 1;
  double x_step = 0.1;
  double t_step = 0.1;
  size_t t_length = 1;

  equation.init_doubles(p_square,L,x_step,t_step,t_length);

  function_x_t f_x_t = [] (double x, double t) -> double
    {
    return x+t;
    };

  function_x phi = [] (double x) -> double
    {
    return 0.1;//sin(PI*x) + 0.5*sin(2*PI*x) + 0.25*sin(4*PI*x);
    };
  function_x psi = [] (double x) -> double
    {
    return 0.1;//PI*( cos(PI*x) + cos(2*PI*x) + cos(4*PI*x) );
    };

  function_x mu1 = [] (double t) -> double
    {
    return 0;//3*PI*sin(t);
    };
  function_x mu2 = [] (double t) -> double
    {
    return 0;//3*PI*(1-cos(t));
    };

  equation.init_function(f_x_t,phi,psi,mu1,mu2);
  }

void Wave_equation::init_doubles( double i_p_square,
                                 double i_L,
                                 double _x_step,
                                 double _t_step,
                                 size_t _t_length)
  {
  p_square = i_p_square;
  L = i_L;
  x_step = _x_step;
  elements_number = size_t( L/x_step + 1 );
  t_step = _t_step;
  t_length = _t_length;
  }

void Wave_equation::init_function(const function_x_t& i_f_x_t,
                                  const function_x& i_phi,
                                  const function_x& i_psi,
                                  const function_x& i_mu1,
                                  const function_x& i_mu2)
  {
  f_x_t = i_f_x_t;
  phi = i_phi;
  psi = i_psi;
  mu1 = i_mu1;
  mu2 = i_mu2;
  }

matrix Wave_equation::get_C(const vector<shared_ptr<D1Element>>& element_container) const
  {
  matrix C(elements_number,elements_number);

  for(size_t i = 0; i < elements_number; ++i)
    for(size_t j = 0; j < elements_number; ++j)
      {
      C(i,j) = D1Integrate::Integrate_Ni_Nj(element_container[i],element_container[j]);
      };;

  return C;
  }
matrix Wave_equation::get_D(const vector<shared_ptr<D1Element>>& element_container) const
  {
  matrix D(element_container.size(),element_container.size());

  for(size_t i = 0; i < D.size1(); ++i)
    for(size_t j = 0; j < D.size2(); ++j)
      {
      D(i,j) = get_element_D(element_container[i],element_container[j]);
      };;

  return D;
  }
double Wave_equation::get_element_D(const shared_ptr<D1Element> N_i, const shared_ptr<D1Element> N_j) const
  {
  double acc = 0.0;

  double shared_int = intervals_length(N_i->get_shared_interval(N_j));

  if ( N_i == N_j )
    {
    if ( N_i->get_node()->get_x() == 0 )
      acc += -1.0/shared_int;
    else if ( N_i->is_last() )
      acc += 1.0/shared_int;
    }

  return p_square* ( acc - D1Integrate::Integrate_dNi_dNj(N_i,N_j) );
  }
vector<smart_function_x> Wave_equation::get_F(const vector<shared_ptr<D1Element>>& element_container) const
  {
  vector<smart_function_x> F;

  transform( begin(element_container), end(element_container), back_inserter(F),[=] (const shared_ptr<D1Element>& N_j)
    {
    return D1Integrate::Integrate_f_x_t_Nj(f_x_t,N_j);
    });

  return F;
  }
matrix Wave_equation::get_reduce_matrix(const matrix& C) const
  {
  size_t new_size = C.size1()-2;
  matrix reduce_matrix(new_size,new_size);

  for(size_t i = 0; i < new_size; ++i)
    for(size_t j = 0; j < new_size; ++j)
      {
      reduce_matrix(i,j) = C(i+1,j+1);
      };;

  return reduce_matrix;
  }
vector<smart_function_x> Wave_equation::get_P(const vector<smart_function_x>& F, const matrix& C,const matrix& D) const
  {
  vector<smart_function_x> P;

  size_t i = 0;
  size_t N = elements_number;

  transform( begin(F)+1, end(F)-1, back_inserter(P), [&] (const smart_function_x& f_x)
    {
    ++i;
    auto tail = [=] (double t, size_t i, size_t N) -> double
      {
      double d0 = D(i,0)*mu1(t);
      double dN = D(i,N-1)*mu2(t);

      double c0 = C(i,0)*Derivative::get_second_mid_der(mu1)(t);
      double cN = C(i,N-1)*Derivative::get_second_mid_der(mu2)(t);

      return (d0 + dN) - ( c0 + cN );
      };

    auto aaa = bind(tail,placeholders::_1,i,N);

    auto copy = f_x;
    copy.set_tail(aaa);

    return copy;
    });

  return P;
  }
Function_vector Wave_equation::get_P_dash(const vector<smart_function_x>& P, const matrix& inverse_M) const
  {
  Function_vector v_f_t(P, inverse_M);  
  return v_f_t;
  }
vector_t Wave_equation::get_initial_state(const vector<shared_ptr<D1Element>>& element_container, 
  const function_x& phi,
  const function_x& psi,
  const matrix inverse_M) const
  {
  size_t old_size = inverse_M.size1();

  vector_t state_phi(old_size);
  vector_t state_psi(old_size);

  for(size_t i = 0; i < old_size; ++i)
    {
    state_phi(i) = D1Integrate::Integrate_f_x_N_i(phi,element_container[i+1]);
    state_psi(i) = D1Integrate::Integrate_f_x_N_i(psi,element_container[i+1]);
    }

  vector_t init_state_phi = prod(inverse_M,state_phi);
  vector_t init_state_psi = prod(inverse_M,state_psi);

  vector_t init_state(2*old_size);
  for(size_t i = 0; i < old_size; ++i)
    {
    init_state(i) = init_state_phi(i);
    init_state(i+old_size) = init_state_psi(i);
    }

  return init_state;
  }

matrix Wave_equation::get_solution()
  {
  vector<shared_ptr<D1Node>> node_container;
  generate_node_container(0,L,x_step,node_container);

  std::vector<shared_ptr<D1Element>> element_container;
  generate_element_container(node_container,element_container);

  matrix C = get_C(element_container);
  matrix D = get_D(element_container);

  vector<smart_function_x> F = get_F(element_container);

  matrix M = get_reduce_matrix(C);
  matrix N = get_reduce_matrix(D);

  vector<smart_function_x> P = get_P(F,C,D);

  matrix inverse_M(M.size1(),M.size2());
  InvertMatrix(M,inverse_M);

  matrix N_dash = prod(inverse_M,N);
  auto   P_dash = get_P_dash(P,inverse_M);

  auto initial_state = get_initial_state(element_container,phi,psi,inverse_M);

  matrix main_matrix = b_identity_matrix(initial_state.size(),initial_state.size());
  for(size_t i = 0; i < N_dash.size1(); ++i)
    for(size_t j = 0; j < N_dash.size2(); ++j)
      main_matrix(i+N_dash.size1(),j+N_dash.size2()) = N_dash(i,j);

  Runge_Kutta_solver rk_solver(main_matrix,initial_state,P_dash);
  auto result = rk_solver.get_solution(t_step,double(t_length)/t_step);

  return result;
  }