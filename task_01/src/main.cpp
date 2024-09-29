#include "topological_sort.hpp"

int main() {
  auto graph = Graph<size_t, long>::GraphWeighted({{0, 1, 1},
                                                   {0, 2, 2},
                                                   {1, 3, 3},
                                                   {1, 4, 4},
                                                   {2, 5, 5},
                                                   {3, 5, 6},
                                                   {4, 5, 7}});

  // std::cout << graph << std::endl;
  // graph.PrintAdjList();

  auto sorted_verts = TopologicalSort(graph);
  std::cout << sorted_verts << std::endl;

  // auto graph_strs = Graph<std::string, long>::GraphWeighted({{"0", "1", 1},
  //                                                            {"0", "2", 2},
  //                                                            {"1", "3", 3},
  //                                                            {"1", "4", 4},
  //                                                            {"2", "5", 5},
  //                                                            {"3", "5", 6},
  //                                                            {"4", "5", 7}});

  // // std::cout << graph_strs << std::endl;
  // // graph_strs.PrintAdjList();

  // auto sorted_verts = TopologicalSort(graph_strs);
  // std::cout << sorted_verts << std::endl;

  return 0;
}
