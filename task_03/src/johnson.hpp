#pragma once

#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

#include "dijkstra.hpp"
#include "weighted_graph.hpp"

constexpr int INF = std::numeric_limits<int>::max();

template <typename T>
std::vector<std::vector<int>> Johnson(WeightedGraph<T>& graph) {
  // Step 1: Add a new vertex
  T new_vertex_data;
  graph.AddVertex(new_vertex_data);

  // Step 2: Add edges from the new vertex to all other vertices with weight 0
  for (size_t u = 0; u < graph.Size() - 1; ++u)
    graph.AddDirEdge(graph.Size() - 1, u, 0);

  // Step 3: Run Bellman-Ford algorithm from the new vertex
  std::vector<int> h(graph.Size(), INF);
  h[graph.Size() - 1] = 0;
  for (int i = 0; i < graph.Size() - 1; ++i)  // |V| - 1 relaxation iterations
    for (int u = 0; u < graph.Size(); ++u)
      for (const auto& neighbour : graph[u]->adjacent) {
        size_t v = graph.Find(neighbour->data);
        if (h[u] != INF && h[u] + graph.GetWeight(u, v) < h[v])
          h[v] = h[u] + graph.GetWeight(u, v);
      }

  // Step 4: Check for negative weight cycles
  for (int u = 0; u < graph.Size(); ++u)
    for (const auto& neighbour : graph[u]->adjacent) {
      size_t v = graph.Find(neighbour->data);
      if (h[u] != INF && h[u] + graph.GetWeight(u, v) < h[v]) {
        std::cout << "Graph contains a negative weight cycle" << std::endl;
        graph.RemoveVertex(graph.Size() - 1);
        return {};
      }
    }

  // Step 5: Remove the new vertex
  graph.RemoveVertex(graph.Size() - 1);

  // Step 6: Reweight the edges
  for (int u = 0; u < graph.Size(); ++u)
    for (const auto& neighbour : graph[u]->adjacent) {
      size_t v = graph.Find(neighbour->data);
      if (graph.GetWeight(u, v) != INF)
        graph.Reweight(u, v, graph.GetWeight(u, v) + h[u] - h[v]);
    }

  // Step 7: Run Dijkstra's algorithm for each vertex
  std::vector<std::vector<int>> distances(graph.Size(),
                                          std::vector<int>(graph.Size(), INF));

  for (size_t u = 0; u < graph.Size(); ++u)
    distances[u] = Dijkstra(graph, u).first;

  // Step 8: Restore the original weights
  for (size_t u = 0; u < graph.Size(); ++u)
    for (size_t v = 0; v < graph.Size(); ++v)
      if (distances[u][v] != INF) distances[u][v] += h[v] - h[u];

  return distances;
}