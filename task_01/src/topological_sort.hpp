#include <iostream>
#include <queue>
#include <stack>
#include <unordered_map>

#include "graph/graph.hpp"

template <typename weight_t>
std::vector<size_t> TopologicalSort(const Graph<size_t, weight_t>& graph) {
  std::vector<bool> visited(graph.VertsAmount(), false);
  std::vector<size_t> ans;

  for (const auto& vert : graph.Verts())
    if (!visited[vert]) TopologicalSortStepDFS(graph, vert, visited, ans);

  std::reverse(ans.begin(), ans.end());

  return ans;
}

template <typename weight_t>
static void TopologicalSortStepDFS(const Graph<size_t, weight_t>& graph,
                                   size_t u_vert, std::vector<bool>& visited,
                                   std::vector<size_t>& dfs_stack) {
  visited[u_vert] = true;

  for (size_t i = 0; i < graph.GetAdjList()[u_vert].size(); i++) {
    auto vert = graph.GetAdjList()[u_vert][i];
    if (!visited[vert]) TopologicalSortStepDFS(graph, vert, visited, dfs_stack);
  }

  dfs_stack.push_back(u_vert);
}