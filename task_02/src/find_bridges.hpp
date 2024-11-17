#include <set>
#include <unordered_map>

#include "graph/graph.hpp"

template <typename T>
struct Edge {
 public:
  T v1;
  T v2;
};

template <typename T>
bool operator==(const Edge<T>& lhs, const Edge<T>& rhs) {
  return (lhs.v1 == rhs.v1 && lhs.v2 == rhs.v2) ||
         (lhs.v1 == rhs.v2 && lhs.v2 == rhs.v1);
}

template <typename T>
void DFSForBridges(std::unordered_map<T, int>& d, std::unordered_map<T, int>& h,
                   std::unordered_map<T, bool>& visited,
                   std::vector<Edge<T>>& bridges, Graph<T>& graph, const T& v,
                   const T& p = T()) {
  visited[v] = true;
  if (p) d[v] = h[v] = h[p] + 1;

  for (auto u : graph.GetAdjVertices(v)) {
    if (u != p) {
      if (visited[u])
        d[v] = std::min(d[v], h[u]);
      else {
        DFSForBridges(d, h, visited, bridges, graph, u, v);

        d[v] = std::min(d[v], d[u]);
        if (h[v] < d[u]) bridges.push_back({v, u});
      }
    }
  }
}

template <typename T>
std::vector<Edge<T>> FindBridges(Graph<T> graph) {
  if (graph.IsOriented()) throw std::invalid_argument("Graph is oriented!");

  std::unordered_map<T, int> d, h;
  std::unordered_map<T, bool> visited;
  for (auto v : graph.GetVerticesIds()) {
    d[v] = h[v] = 0;
    visited[v] = false;
  }

  std::vector<Edge<T>> bridges;
  DFSForBridges(d, h, visited, bridges, graph, graph.GetVerticesIds()[0]);

  return bridges;
}