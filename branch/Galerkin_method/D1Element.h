#pragma once

#include <vector>
#include <memory>

#include "D1Node.h"

class D1Element
  {
  public:
    explicit D1Element(const std::shared_ptr<D1Node>& main_node)
      :m_main_node(main_node)
      {}

    bool is_neighbor(const std::shared_ptr<D1Element>& is_neighbor) const;

    void add_neighbor(const std::shared_ptr<D1Element>& neighbor)
      {
      mp_neighbors.push_back(neighbor);
      }

//  private:
    std::shared_ptr<D1Node> m_main_node;
    std::vector<std::shared_ptr<D1Element>> mp_neighbors;
  };

bool operator==(const D1Element& lhv, const D1Element& rhv);
bool operator==(const std::shared_ptr<D1Element>& lhv, const std::shared_ptr<D1Element>& rhv);

void generate_element_container(const std::vector<std::shared_ptr<D1Node>>& node_container, std::vector<std::shared_ptr<D1Element>>& io_element_container);
void fill_element_container(const std::vector<std::shared_ptr<D1Node>>& node_container, std::vector<std::shared_ptr<D1Element>>& io_element_container);
void set_element_neighbor(std::vector<std::shared_ptr<D1Element>>& io_element_container);

void debug_element_print(const std::vector<std::shared_ptr<D1Element>>& io_element_container);