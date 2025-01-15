#pragma once

#include <map>

#include "dijkstra.hpp"

template <typename T>
void BellmanFordStep(WeightedGraph<T>& graph,
                     std::map<T, MinPath<T>>& min_paths, bool& is_updated) {
  for (auto w_edge : graph.GetWeightedEdges()) {
    T v = w_edge.start_vertex;
    T u = w_edge.end_vertex;

    if (min_paths[v].weight != std::numeric_limits<int>::max() &&
        min_paths[u].weight > min_paths[v].weight + w_edge.weight) {
      is_updated = true;

      min_paths[u].weight = min_paths[v].weight + w_edge.weight;
      // Обновляем кратчайший путь
      min_paths[u].vertices = min_paths[v].vertices;
      min_paths[u].vertices.push_back(v);
    }
  }
}

template <typename T>
std::vector<MinPath<T>> BellmanFord(const T& vertex, WeightedGraph<T> graph) {
  if (!graph.ContainsVertex(vertex))
    throw std::invalid_argument("Root vertex not found!");

  // Использован map для того, чтобы были отсортированы ключи (легче писать
  // тесты)
  std::map<T, MinPath<T>> min_paths;
  for (auto v : graph.GetVerticesIds()) {
    if (v == vertex)
      min_paths[v].weight = 0;
    else
      min_paths[v].weight = std::numeric_limits<int>::max();
  }

  bool is_updated = false;
  for (int i = 0; i < graph.GetVerticesCount() - 1; i++) {
    is_updated = false;
    BellmanFordStep(graph, min_paths, is_updated);
    if (!is_updated) break;
  }

  // Проверяем на цикл с отрицательным весом
  is_updated = false;
  BellmanFordStep(graph, min_paths, is_updated);
  if (is_updated)
    throw std::invalid_argument("Graph has cicle with negative weight!");

  // Удаляем вершину, для которой мы находили кратчайшие пути до других вершин
  min_paths.erase(vertex);

  std::vector<MinPath<T>> paths;
  for (auto [v, min_path] : min_paths) {
    min_path.vertices.push_back(v);
    paths.push_back(min_path);
  }

  return paths;
}