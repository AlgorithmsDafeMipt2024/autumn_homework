#include <algorithm>
#include <unordered_map>

#include "graph/graph.hpp"

template <typename T>
void DFSForJointVertices(std::unordered_map<T, int>& d,
                         std::unordered_map<T, int>& h,
                         std::unordered_map<T, bool>& visited,
                         std::vector<T>& joint_vertices, Graph<T>& graph,
                         const T& v, const T& p = T()) {
  visited[v] = true;
  if (p) d[v] = h[v] = h[p] + 1;

  int children_count = 0;

  for (auto u : graph.GetAdjVertices(v)) {
    if (u != p) {
      if (visited[u])
        d[v] = std::min(d[v], h[u]);
      else {
        DFSForJointVertices(d, h, visited, joint_vertices, graph, u, v);

        d[v] = std::min(d[v], d[u]);
        if (h[v] <= d[u] && p)
          if (std::find(joint_vertices.begin(), joint_vertices.end(), v) ==
              joint_vertices.end())
            joint_vertices.push_back(v);

        children_count++;
      }
    }
  }
  // Отдельно проверяем корень
  if (!p && children_count > 1) joint_vertices.push_back(v);
}

template <typename T>
std::vector<T> FindJointVertices(Graph<T> graph) {
  if (graph.IsOriented()) throw std::invalid_argument("Graph is oriented!");

  std::unordered_map<T, int> d, h;
  std::unordered_map<T, bool> visited;
  for (auto v : graph.GetVerticesIds()) {
    d[v] = h[v] = 0;
    visited[v] = false;
  }

  std::vector<T> joint_vertices;
  if (graph.GetVerticesCount())
    DFSForJointVertices(d, h, visited, joint_vertices, graph,
                        graph.GetVerticesIds()[0]);

  return joint_vertices;
}