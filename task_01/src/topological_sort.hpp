#ifndef __TOPOLOG_SORT_H__
#define __TOPOLOG_SORT_H__

#include <stdexcept>
#include <vector>

#include "../../lib/src/graph.hpp"

template <typename T>
void topological_rec(std::vector<Node<T, int>*>& st, Node<T, int>* n) {
  if (n->name == 0) {
    n->name = 1;
    // 1 - adjacent (as leafs) points

    for (auto i : n->paths) {
      topological_rec(st, i.first);
    }
    n->name = 2;
    st.push_back(n);

  } else if (n->name == 2) {
    return;
  } else {
    throw std::runtime_error("Incorrect graph");
  }
}

template <typename T>
Graph<T, int>& topological_sort(Graph<T, int>& g) {
  std::vector<Node<T, int>*> marked_points;
  for (auto i : g.nodes) {
    i->name = 0;
    // 0 - clear points
  }

  // point_stack.push(g.nodes[0]);
  for (auto i : g.nodes) {
    if (i->name == 0) {
      topological_rec(marked_points, i);
    }
  }
  int stack_size = marked_points.size();
  for (int i = 1; i < stack_size + 1; ++i) {
    marked_points[stack_size - i]->name = i;
  }
  return g;
}

#endif