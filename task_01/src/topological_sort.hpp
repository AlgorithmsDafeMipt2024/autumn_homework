#include "graph/graph.hpp"

template <typename T>
bool IsVisited(const T& vertex, const std::vector<T>& visited) {
  return std::find(visited.begin(), visited.end(), vertex) != visited.end();
}

template <typename T>
void DFS(Graph<T>& graph, std::vector<T>& visited, std::vector<T>& res,
         const T& curr_vertex) {
  if (IsVisited(curr_vertex, visited))
    throw std::invalid_argument("Graph is not acyclic!");

  visited.push_back(curr_vertex);

  for (const T& adj_vertex : graph.GetAdjVertices(curr_vertex))
    if (graph.ContainsVertex(adj_vertex)) DFS(graph, visited, res, adj_vertex);

  graph.DeleteVertex(curr_vertex);
  res.push_back(curr_vertex);
}

template <typename T>
std::vector<T> TopSortWithDFS(Graph<T> graph) {
  std::vector<T> reversed_res;
  std::vector<T> visited;

  while (graph.GetVerticesCount())
    DFS(graph, visited, reversed_res, graph.GetVerticesIds()[0]);

  reverse(reversed_res.begin(), reversed_res.end());

  return reversed_res;
}