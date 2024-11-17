#include <unordered_map>

#include "graph/graph.hpp"

template <typename T>
void DFS(Graph<T>& graph, std::unordered_map<T, bool>& visited,
         std::vector<T>& res, const T& curr_vertex) {
  if (visited[curr_vertex])
    throw std::invalid_argument("Graph is not acyclic!");

  visited[curr_vertex] = true;

  for (auto adj_vertex : graph.GetAdjVertices(curr_vertex))
    if (graph.ContainsVertex(adj_vertex)) DFS(graph, visited, res, adj_vertex);

  graph.DeleteVertex(curr_vertex);
  res.push_back(curr_vertex);
}

template <typename T>
std::vector<T> TopologicalSort(Graph<T> graph) {
  std::vector<T> reversed_res;
  std::unordered_map<T, bool> visited;

  while (graph.GetVerticesCount())
    DFS(graph, visited, reversed_res, graph.GetVerticesIds()[0]);

  reverse(reversed_res.begin(), reversed_res.end());

  return reversed_res;
}