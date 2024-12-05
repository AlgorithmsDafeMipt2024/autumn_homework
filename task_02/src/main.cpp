#include <iostream>

#include "graph.hpp"

using namespace algo;

int main() {
  Graph graph(5, 5, false);
  graph.addEdge(1, 2, 0);
  graph.addEdge(1, 3, 0);
  graph.addEdge(3, 4, 0);
  graph.addEdge(4, 5, 0);
  graph.addEdge(4, 2, 0);

  auto bridges = graph.getBridges();
  auto articulationPoints = graph.getArticulationPoints();

  std::cout << "Bridges:\n";
  for (auto [u, v] : bridges) {
    std::cout << u << " - " << v << '\n';
  }

  std::cout << "Articulation Points:\n";
  for (int v : articulationPoints) {
    std::cout << v << '\n';
  }

  return 0;
}