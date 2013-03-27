#include "stdafx.h"

#include "D1Element.h"
#include "algorithm\Build_function.h"

using namespace std;

bool D1Element::is_neighbor(const shared_ptr<D1Element>& is_neighbor) const
  {
  auto _find = find( begin_neighbor(), end_neighbor(), is_neighbor);

  return _find != end_neighbor();
  }

bool operator==(const D1Element& lhv, const D1Element& rhv)
  {
  return *lhv.get_node() == *rhv.get_node();
  }
bool operator==(const shared_ptr<D1Element>& lhv, const shared_ptr<D1Element>& rhv)
  {
  return *lhv == *rhv;
  }

void generate_element_container(const vector<shared_ptr<D1Node>>& node_container, vector<shared_ptr<D1Element>>& io_element_container)
  {
  io_element_container.clear();
  fill_element_container(node_container,io_element_container);
  set_element_neighbor(io_element_container);
  }

void fill_element_container(const vector<shared_ptr<D1Node>>& node_container, vector<shared_ptr<D1Element>>& io_element_container)
  {
  size_t elem_size = node_container.size();
  io_element_container.resize(elem_size);

  transform( begin(node_container), end(node_container), begin(io_element_container), [&] (const shared_ptr<D1Node>& node)
    {
    return make_shared<D1Element>(D1Element(node));
    });

  }

void set_element_neighbor(vector<shared_ptr<D1Element>>& io_element_container)
  {
  size_t con_size = io_element_container.size();
  if ( con_size < 2)
    return;

  // first & last element has only one neighbor
  io_element_container[0]->add_neighbor(io_element_container[1]);
  io_element_container[con_size-1]->add_neighbor(io_element_container[con_size-2]);

  for(size_t i = 1; i < con_size - 1; ++i)
    {
    io_element_container[i]->add_neighbor(io_element_container[i-1]);
    io_element_container[i]->add_neighbor(io_element_container[i+1]);
    }
  }

function_x D1Element::build_test_function(double x0, double f0, double x1, double f1) const
  // out of interval [x0,x1] equal to 0
  {
  if ( x0 > x1 )
    {
    swap(x0,x1);
    swap(f0,f1);
    }

  auto f_x = Build_function::get_linear_f_x(x0,f0,x1,f1);

  return [&] (double x) -> double
    {
    if ( x >= x0 && x1 >= x)
      return f_x(x);
    else
      return 0;
    };
  }

function_x D1Element::get_support_function() const
  {
  return [&](double x) -> double
    {
    vector<function_x> Ni;

    double x0 = get_node()->get_x();
    double f0 = 1;

    transform( begin_neighbor(), end_neighbor(), back_inserter(Ni), [&] (const shared_ptr<D1Element>& neighbor)
      {
      double x1 = neighbor->get_node()->get_x();
      double f1 = 0;

      return build_test_function(x0,f0,x1,f1) ;
      });

    return accumulate( begin(Ni), end(Ni), 0.0, [&] (double acc, const function_x& f)
      {
        return acc + f(x);
      });
    };
  }

intervals D1Element::get_intervals() const
  {
  double this_x = get_node()->get_x();

  intervals area;

  transform( begin_neighbor(), end_neighbor(), back_inserter(area), [&] ( const shared_ptr<D1Element>& neighbor)
    {
    return make_pair(this_x, neighbor->get_node()->get_x());
    });

  //sort interval
  for_each( begin(area), end(area), [] (interval& p)
    {
    if ( p.first > p.second )
      swap(p.first,p.second);
    });
  // maybe should sort area? 
  // but i don't think so...

  return area;
  }

intervals D1Element::get_shared_interval(const std::shared_ptr<D1Element>& N_j) const
  {
  auto N_i_interval =      get_intervals();
  auto N_j_interval = N_j->get_intervals();

  intervals shared;

  set_intersection(begin(N_i_interval),end(N_i_interval),begin(N_j_interval),end(N_j_interval), back_inserter(shared));

  return shared;
  }

double interval_length(const std::pair<double,double>& p)
  {
  return abs(p.second - p.first);
  }

void debug_element_print(const vector<shared_ptr<D1Element>>& io_element_container)
  {
  for_each( begin(io_element_container), end(io_element_container), [&] (const shared_ptr<D1Element>& element)
    {
    cout << "main:\t" << element->get_node()->get_x() << "\tneighbor: ";
    for_each(element->begin_neighbor(), element->end_neighbor(), [&] (const shared_ptr<D1Element>& neighbor)
      {
      cout << neighbor->get_node()->get_x() << ", ";
      });
    cout << endl;
    });
  }