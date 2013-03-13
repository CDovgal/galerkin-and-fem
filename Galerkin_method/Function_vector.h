#pragma once

#include <functional>
#include <vector>

#include "Typedefs.h"

class Function_vector
  {
  public:
    void add_function(const std::function<double (Vector) >& i_function)
      {func_vector.push_back(i_function);}

    Vector operator()(const Vector& i_vector)
      {
      Vector result(func_vector.size());

      std::transform(begin(func_vector), end(func_vector), begin(result),
        [&i_vector] (const std::function<double (Vector)>& func)
        {return func(i_vector);});

      return result;
      }

  private:
    std::vector< std::function<double (Vector) > > func_vector;
  };