#pragma once

#include <vector>
#include <memory>
#include <algorithm>

class D1Node
  {
  public:
    typedef std::vector<std::shared_ptr<D1Node>> Node_neighbors;
    typedef Node_neighbors::const_iterator Node_neighbor_iter;

    explicit D1Node(double _x)
      :x(_x)
      {}

    inline double get_x() const
      {
      return x;
      }

    inline void add_neighbor(const std::shared_ptr<D1Node>& neighbor)
      {
      mp_neighbors.push_back(neighbor);
      }
    bool  is_neighbor(const std::shared_ptr<D1Node>& neighbor) const
      {
      auto find_neighbour = std::find_if ( neighbor->begin_neighbor(), neighbor->end_neighbor(), [&] (const std::shared_ptr<D1Node>& candidate)
        {
        return this->x == candidate->get_x();
        });

      return find_neighbour != neighbor->end_neighbor();
      }

    inline Node_neighbor_iter begin_neighbor() const
      {
      return std::begin(mp_neighbors);
      }
    inline Node_neighbor_iter end_neighbor() const
      {
      return std::end(mp_neighbors);
      }

  private:
    double x;
    Node_neighbors mp_neighbors;
  };

bool operator==(const D1Node& lhv, const D1Node& rhv);
bool operator==(const std::shared_ptr<D1Node>& lhv, const std::shared_ptr<D1Node>& rhv);

void generate_node_container(double from, double to, double step, std::vector<std::shared_ptr<D1Node>>& io_node_container);
void fill_node_container(double from, double to, double step, std::vector<std::shared_ptr<D1Node>>& io_node_container);
void set_node_neighbors(std::vector<std::shared_ptr<D1Node>>& io_node_container);

void debug_node_print(const std::vector<std::shared_ptr<D1Node>>& io_node_container);