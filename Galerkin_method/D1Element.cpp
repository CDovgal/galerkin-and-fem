#include "stdafx.h"

#include "D1Element.h"

using namespace std;

bool operator==(const D1Element& lhv, const D1Element& rhv)
  {
  return lhv.m_main_node == rhv.m_main_node;
  /*
  return equal( begin(lhv.mp_neighbors), end(lhv.mp_neighbors), begin(rhv.mp_neighbors),
  [&] (const shared_ptr<D1Element>& lhv, const shared_ptr<D1Element>& rhv)
  {
  return *lhv == *rhv;
  });
  */
  }
bool operator==(const shared_ptr<D1Element>& lhv, const shared_ptr<D1Element>& rhv)
  {
  return *lhv == *rhv;
  }

bool D1Element::is_neighbor(const shared_ptr<D1Element>& is_neighbor) const
  {
  auto _find = find( begin(mp_neighbors), end(mp_neighbors), is_neighbor);

  return _find != end(mp_neighbors);

  /*
  const shared_ptr<D1Node> p_this_node = this->m_main_node;

  // found this_node as main node in one of neighbors is_neighbor
  auto found = find_if( begin(is_neighbor->mp_neighbors), end(is_neighbor->mp_neighbors), [&] (const shared_ptr<D1Element>& element)
    {
    return p_this_node == element->m_main_node;
    });

  return found != end(is_neighbor->mp_neighbors);
  */
  }

void generate_element_container(const std::vector<shared_ptr<D1Node>>& node_container, std::vector<shared_ptr<D1Element>>& io_element_container)
  {
  io_element_container.clear();
  fill_element_container(node_container,io_element_container);
  set_element_neighbor(io_element_container);
  }

void fill_element_container(const std::vector<shared_ptr<D1Node>>& node_container, std::vector<shared_ptr<D1Element>>& io_element_container)
  {
  size_t elem_size = node_container.size();
  io_element_container.resize(elem_size);

  transform( begin(node_container), end(node_container), begin(io_element_container), [&] (const shared_ptr<D1Node>& node)
    {
    return make_shared<D1Element>(D1Element(node));
    });

  }

void set_element_neighbor(std::vector<shared_ptr<D1Element>>& io_element_container)
  // must be rewrite. algo steal from set_node_neighbor
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

  /*
  for_each( begin(io_element_container), end(io_element_container), [&io_element_container] (shared_ptr<D1Element>& frst_element)
  {
  for_each(begin(io_element_container), end(io_element_container), [&frst_element] (const shared_ptr<D1Element>& scnd_element)
  {
  if ( frst_element->is_neighbor(scnd_element) )
  frst_element->add_neighbor(scnd_element);
  });
  });
  */
  }

void debug_element_print(const std::vector<shared_ptr<D1Element>>& io_element_container)
  {
  for_each( begin(io_element_container), end(io_element_container), [&] (const shared_ptr<D1Element>& element)
    {
    cout << "main:\t" << element->m_main_node->operator()(0) << "\tneighbor: ";
    for_each( begin(element->mp_neighbors), end(element->mp_neighbors), [&] (const shared_ptr<D1Element>& neighbor)
      {
      cout << (*neighbor->m_main_node).operator()(0) << ", ";
      });
    cout << endl;
    });
  }