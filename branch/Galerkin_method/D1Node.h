#pragma once

#include <vector>
#include <memory>

class D1Node
  {
  public:
    explicit D1Node(double _x)
      :x(_x)
      {}

    inline double& operator()(size_t index)
      {
      return x;
      }
    inline const double& operator()(size_t index) const
      {
      return x;
      }

    void add_neighbor(const std::shared_ptr<D1Node>& neighbour)
      {
//      if (!is_neighbor(neighbour))
        mp_neighbors.push_back(neighbour);
      }
    void del_neighbor(const std::shared_ptr<D1Node>& neighbour)
      {
      std::remove( begin(mp_neighbors), end(mp_neighbors), neighbour);
      }
    bool  is_neighbor(const std::shared_ptr<D1Node>& neighbour) const;
//  private:
    double x;

    std::vector<std::shared_ptr<D1Node>> mp_neighbors;
  };

bool operator==(const D1Node& lhv, const D1Node& rhv); 
bool operator==(const std::shared_ptr<D1Node>& lhv, const std::shared_ptr<D1Node>& rhv);

void generate_node_container(double from, double to, double step, std::vector<std::shared_ptr<D1Node>>& io_node_container);
void fill_node_container(double from, double to, double step, std::vector<std::shared_ptr<D1Node>>& io_node_container);
void set_node_neighbors(std::vector<std::shared_ptr<D1Node>>& io_node_container);

void debug_node_print(const std::vector<std::shared_ptr<D1Node>>& io_node_container);