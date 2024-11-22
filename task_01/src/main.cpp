#include <iostream>

#include "graph/graph.hpp"

int main() {
  int vertexes_num, edges_num;
  std::cin >> vertexes_num >> edges_num;

  Graph graph(vertexes_num, edges_num);

  for (int i = 0; i < edges_num; i++) {
    int a, b, w;

    std::cin >> a >> b >> w;

    graph.addEdge(a, b, w);
  }

  std::cout << "Topsort:" << std::endl;
  for (auto i : graph.topological_sort(0)) {
    std::cout << i + 1 << " ";
  }

  std::cout << std::endl;
}
