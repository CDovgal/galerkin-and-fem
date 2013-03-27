#pragma once

#include "calculus/D1Integrate.h"

class Function_vector
  {
  public:
    Function_vector(const std::vector<smart_function_x>& v_f_t, const matrix inv_M)
      : func_vector(v_f_t)
      , inverse_M(inv_M)
      {}

    vector_t operator()(vector_t t)
      {
      vector_t result = b_zero_vector(t.size());

      for(size_t i = 0; i < func_vector.size(); ++i)
        {
        int j = -1;
        result[i] = std::accumulate( begin(func_vector), end(func_vector), 0.0, [&] (double acc, const smart_function_x& f_t)
          {
          ++j;
          return acc + inverse_M(i,j) * f_t(t(j));
          });
        }

      return result;
      }

  private:
    std::vector< smart_function_x > func_vector;
    matrix inverse_M;
  };