#include "topology_sort.hpp"

int main() {
  Graph<std::string, long> graph =
      Graph<std::string, long>::GraphWeighted({{"A", "B", 1},
                                               {"A", "C", 2},
                                               {"B", "D", 3},
                                               {"B", "E", 4},
                                               {"C", "F", 5},
                                               {"D", "F", 6},
                                               {"E", "F", 7}});

  auto sorted_verts = TopologySort(graph);
  std::cout << sorted_verts << std::endl;

  return 0;
}
