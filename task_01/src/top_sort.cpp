#include "top_sort.hpp"

#include <Graph.hpp>

std::vector<int> TopSort(int vertices, int edges,
                         std::vector<std::pair<int, int>>& edge) {
  Graph graph_UDG;
  graph_UDG.read_UDG(vertices, edges, edge);
  bool is_cycle = false;
  for (int i = 1; i <= vertices; i++) {
    if (!graph_UDG.used[i]) {
      is_cycle = graph_UDG.dfs_cycle_directed_U(i);
    }
    if (is_cycle) {
      throw CycleGraph("Cycle found -> Topological sorting is not possible");
    }
  }
  reverse(graph_UDG.topsort.begin(), graph_UDG.topsort.end());
  return graph_UDG.topsort;
}