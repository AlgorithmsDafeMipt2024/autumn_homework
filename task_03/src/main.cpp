#include <iostream>

#include "johnson.hpp"

int main() {
  WeightedGraph<Vertex<int>, int> graph;
  for (int i = 0; i < 4; ++i) graph.AddVertex(i);
  graph.AddDirEdge(0, 1, -5);
  graph.AddDirEdge(0, 2, 2);
  graph.AddDirEdge(0, 3, 3);
  graph.AddDirEdge(1, 2, 4);
  graph.AddDirEdge(2, 3, 1);

  std::vector<std::vector<int>> result = Johnson(graph);

  for (size_t i = 0; i < result.size(); ++i) {
    std::cout << "{ ";
    for (size_t j = 0; j < result[i].size(); ++j) {
      if (result[i][j] != INF)
        std::cout << result[i][j] << " ";
      else
        std::cout << "INF ";
    }
    std::cout << "}" << std::endl;
  }
  return 0;
}
