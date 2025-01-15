#include "task_02.hpp"

#include <algorithm>
#include <vector>

std::pair<std::vector<std::pair<int, int>>, std::vector<int>>
BridgesAndCutPoints(int vertices, int edges,
                    std::vector<std::pair<int, int>> &vecEdges) {
  UUGraph graph;
  graph.UUGReadGraph(vertices, edges, vecEdges);

  for (int i = 1; i <= vertices; i++) {
    if (!graph.used[i]) {
      graph.dfs(i);
    }
  }

  std::pair<std::vector<std::pair<int, int>>, std::vector<int>> ans;
  ans.first = graph.bridges;
  ans.second = graph.cutPoints;
  return ans;
}
