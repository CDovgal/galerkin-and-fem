#pragma once

#include "boost/numeric/ublas/matrix.hpp"
#include "boost/numeric/ublas/vector.hpp"
#include "boost/numeric/ublas/io.hpp"

typedef boost::numeric::ublas::vector<double> vector_t;
typedef boost::numeric::ublas::vector<double> point;
typedef boost::numeric::ublas::matrix<double> matrix;
typedef boost::numeric::ublas::identity_matrix<double> b_identity_matrix;
typedef boost::numeric::ublas::zero_matrix<double>     b_zero_matrix;
typedef boost::numeric::ublas::zero_vector<double>     b_zero_vector;

typedef std::function<double (double x)> function_x;
typedef std::function<double (double x, double t)> function_x_t;

const double PI = 3.14159265358979323846;
