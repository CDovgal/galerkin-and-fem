// Galerkin_method.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Typedefs.h"

#include "Derivative.h"
#include "Gausian_integration.h"
#include "Runge_Kutta_solver.h"
#include "InverseMatrix.h"

#include "D1Node.h"
#include "D1Element.h"
#include "D1Integrate.h"

#include "dislin\discpp.h"

using namespace std;

double L = 10;
double step = 0.5;
double D1Integrate::m_step = step;

int _tmain(int argc, _TCHAR* argv[])
  {
  using boost::numeric::ublas::zero_matrix;

  std::vector<shared_ptr<D1Node>> node_container;
  generate_node_container(0,L,0.5,node_container);

  std::vector<shared_ptr<D1Element>> element_container;
  generate_element_container(node_container,element_container);


  debug_node_print(node_container);
  debug_element_print(element_container);

  cout << D1Integrate::Integrate_Ni_Nj(element_container[0], element_container[0]) << endl;



  return 0;
  }
