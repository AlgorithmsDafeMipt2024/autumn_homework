#include <iostream>
#include <queue>
#include <stack>
#include <unordered_map>

#include "graph/graph.hpp"

template <typename vert_t, typename weight_t>
std::vector<vert_t> TopologicalSort(const Graph<vert_t, weight_t>& graph) {
  std::vector<bool> visited(graph.VertsAmount(), false);
  std::vector<vert_t> ans;

  for (const auto& vert : graph.Verts())
    if (!visited[vert]) TopologicalSortStepDFS(graph, vert, visited, ans);

  std::reverse(ans.begin(), ans.end());

  return ans;
}

template <typename vert_t, typename weight_t>
static void TopologicalSortStepDFS(const Graph<vert_t, weight_t>& graph,
                                   vert_t u_vert, std::vector<bool>& visited,
                                   std::vector<vert_t>& dfs_stack) {
  visited[u_vert] = true;

  for (size_t i = 0; i < graph.GetAdjList()[u_vert].size(); i++) {
    auto vert = graph.GetAdjList()[u_vert][i];
    if (!visited[vert]) TopologicalSortStepDFS(graph, vert, visited, dfs_stack);
  }

  dfs_stack.push_back(u_vert);
}