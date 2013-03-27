#include "stdafx.h"

#include "D1Node.h"

using namespace std;

bool operator==(const D1Node& lhv, const D1Node& rhv)
  {
  return lhv.get_x() == rhv.get_x();
  }
bool operator==(const shared_ptr<D1Node>& lhv, const shared_ptr<D1Node>& rhv)
  {
  return *lhv== *rhv;
  }

void generate_node_container(double from, double to, double step, vector<shared_ptr<D1Node>>& io_node_container)
  {
  io_node_container.clear();
  fill_node_container(from,to,step,io_node_container);
  set_node_neighbors(io_node_container);
  }

void fill_node_container(double from, double to, double step, vector<shared_ptr<D1Node>>& io_node_container)
  {
  size_t amount = size_t( (to - from)/step + 1);
  io_node_container.resize(amount);

  for(size_t i = 0; i < amount; ++i)
    io_node_container[i] = make_shared<D1Node>( D1Node(from + i*step ) );

  }

void set_node_neighbors( vector<shared_ptr<D1Node>>& io_node_container )
  {
  size_t con_size = io_node_container.size();
  // there is no neighbor
  if ( con_size < 2)
    return;

  // first & last element has only one neighbor
  io_node_container[0]->add_neighbor(io_node_container[1]);
  io_node_container[con_size-1]->add_neighbor(io_node_container[con_size-2]);

  for(size_t i = 1; i < con_size - 1; ++i)
    {
    io_node_container[i]->add_neighbor(io_node_container[i-1]);
    io_node_container[i]->add_neighbor(io_node_container[i+1]);
    }

  }

void debug_node_print(const vector<shared_ptr<D1Node>>& io_node_container)
  {
  for(size_t i = 0; i < io_node_container.size(); ++i)
    {
    cout << "coordinate:\t" << io_node_container[i]->get_x() << ";\tneighbor: ";
    for_each( io_node_container[i]->begin_neighbor(), io_node_container[i]->end_neighbor(), [&] ( const shared_ptr<D1Node>& neighbor)
      {
      cout << neighbor->get_x() << "\t";
      });
    cout << endl;
    }
  }