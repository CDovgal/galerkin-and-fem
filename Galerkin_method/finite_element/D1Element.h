#pragma once

#include "D1Node.h"

typedef std::pair<double,double> interval;
typedef std::vector<interval> intervals;

class D1Element
  {
  public:
    typedef std::vector<std::shared_ptr<D1Element>> Element_neighbors;
    typedef Element_neighbors::const_iterator Element_neighbor_iter;

    explicit D1Element(const std::shared_ptr<D1Node>& main_node)
      :mp_main_node(main_node)
      {}

    const D1Node* get_node() const
      {
      return mp_main_node.get();
      }

    bool is_neighbor(const std::shared_ptr<D1Element>& is_neighbor) const;
    inline void add_neighbor(const std::shared_ptr<D1Element>& neighbor)
      {
      mp_neighbors.push_back(neighbor);
      }

    inline Element_neighbor_iter begin_neighbor() const
      {
      return std::begin(mp_neighbors);
      }
    inline Element_neighbor_iter end_neighbor() const
      {
      return std::end(mp_neighbors);
      }

    function_x get_support_function() const;
    intervals get_intervals() const;
    intervals get_shared_interval(const std::shared_ptr<D1Element>& N_j) const;
  private:
    function_x build_test_function(double x0, double f0, double x1, double f1) const;

    std::shared_ptr<D1Node> mp_main_node;

    Element_neighbors mp_neighbors;
  };

bool operator==(const D1Element& lhv, const D1Element& rhv);
bool operator==(const std::shared_ptr<D1Element>& lhv, const std::shared_ptr<D1Element>& rhv);

void generate_element_container(const std::vector<std::shared_ptr<D1Node>>& node_container, std::vector<std::shared_ptr<D1Element>>& io_element_container);
void fill_element_container(const std::vector<std::shared_ptr<D1Node>>& node_container, std::vector<std::shared_ptr<D1Element>>& io_element_container);
void set_element_neighbor(std::vector<std::shared_ptr<D1Element>>& io_element_container);

double interval_length(const std::pair<double,double>& p);

void debug_element_print(const std::vector<std::shared_ptr<D1Element>>& io_element_container);