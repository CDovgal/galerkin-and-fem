#pragma once

#include "util/Typedefs.h"
#include "finite_element/D1Node.h"
#include "finite_element/D1Element.h"

#include "calculus/D1Integrate.h"

#include "runge-kutta/Function_vector.h"
#include "runge-kutta/Runge_Kutta_solver.h"

class Wave_equation
  /* 

  Utt = p^2 * Uxx + f(x,t)
  U=U(x,t), 0 < x < L, t > 0

  U (x,0) = phi(x)
  U'(x,0) = psi(x)

  U (0,t) = mu1(t)
  U (L,t) = mu2(t)

  */
  {
  public:
    Wave_equation()
      {}

    void handle_init();

    void init_doubles( double i_p_square,
                       double i_L,
                       double x_step,
                       double t_step,
                       size_t t_length);

    void init_function(const function_x_t& i_f_x_t,
                       const function_x& i_phi,
                       const function_x& i_psi,
                       const function_x& i_mu1,
                       const function_x& i_mu2);


    // one row - one evolution
    matrix get_solution();

  private:
    matrix get_C(const std::vector<std::shared_ptr<D1Element>>& element_container) const;
    double get_element_D(const std::shared_ptr<D1Element> N_i, const std::shared_ptr<D1Element> N_j) const;
    matrix get_D(const std::vector<std::shared_ptr<D1Element>>& element_container) const;
    std::vector<smart_function_x> get_F(const std::vector<std::shared_ptr<D1Element>>& element_container) const;
    matrix get_reduce_matrix(const matrix& C) const;
    std::vector<smart_function_x> get_P(const std::vector<smart_function_x>& F, const matrix& C,const matrix& D) const;
    Function_vector get_P_dash(const std::vector<smart_function_x>& P, const matrix& inverse_M) const;
    vector_t get_initial_state(const std::vector<std::shared_ptr<D1Element>>& element_container, 
                               const function_x& phi,
                               const function_x& psi,
                               const matrix inverse_M) const;
    double p_square;
    double L;
    double x_step;
    double t_step;
    size_t t_length;
    size_t elements_number;

    function_x_t f_x_t;

    function_x phi;
    function_x psi;

    function_x mu1;
    function_x mu2;
  };

void handle_init(Wave_equation& equation);