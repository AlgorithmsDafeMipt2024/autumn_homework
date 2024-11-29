#pragma once

#include "bellman_ford.hpp"
#include "dijkstra.hpp"

template <typename T>
std::map<T, std::map<T, int>> Johnson(WeightedGraph<T> graph) {
  std::unordered_map<T, int> h;
  for (T v : graph.GetVerticesIds()) h[v] = 0;

  // Добавляем новую вершину и ребра до каждой вершины из новой с весом 0
  T new_vertex;
  graph.AddVertex(new_vertex);
  for (T v : graph.GetVerticesIds())
    if (v != new_vertex) graph.AddWeightedEdge(new_vertex, v);

  // Вызываем алгоритм Беллмана-Форда для новой вершины
  auto min_paths_bellman_ford = BellmanFord(new_vertex, graph);

  for (auto min_path : min_paths_bellman_ford) {
    T v = min_path.vertices[min_path.vertices.size() - 1];
    h[v] = min_path.weight;
  }
  graph.DeleteVertex(new_vertex);

  // Перевзвешиваем все ребра, чтобы вес каждого ребра был положительным
  for (WeightedEdge<T> w_edge : graph.GetWeightedEdges()) {
    T v = w_edge.start_vertex;
    T u = w_edge.end_vertex;
    graph.SetEdgeWeight(v, u, w_edge.weight + h[v] - h[u]);
  }

  std::map<T, std::map<T, int>> res;

  for (T v : graph.GetVerticesIds()) {
    // Вызываем алгоритм Дейкстры для каждой вершины
    auto min_paths_dijkstra = Dijkstra(v, graph);

    for (auto min_path : min_paths_dijkstra) {
      auto path = min_path.vertices;
      T u = path[path.size() - 1];
      // Возвращаем истинный вес минимального пути
      res[v][u] = min_path.weight + h[u] - h[v];
    }
    res[v][v] = 0;
  }

  return res;
}
