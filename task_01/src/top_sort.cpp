#include "top_sort.hpp"

#include <algorithm>

std::vector<int> TopologySort(int vertices, int edges,
                              std::vector<std::pair<int, int>> &vecEdges) {
  DUGraph graph;
  graph.DUGReadGraph(vertices, edges, vecEdges);
  bool is_cycle = false;
  for (int i = 1; i < vertices; i++) {
    if (!graph.used[i]) {
      is_cycle = graph.DUGDfsCycle(i);
    }
    if (is_cycle) {
      throw CycleDetectedException(
          "Topological sorting is not possible with cycle graph");
    }
  }
  std::reverse(graph.topSort.begin(), graph.topSort.end());
  return graph.topSort;
}
