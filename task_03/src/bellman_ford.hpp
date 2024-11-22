#pragma once

#include <algorithm>
#include <map>

#include "dijkstra.hpp"

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

  for (int i = 0; i < graph.GetVerticesCount() - 1; i++) {
    bool is_updated = false;

    for (WeightedEdge<T> w_edge : graph.GetWeightedEdges()) {
      auto v = w_edge.start_vertex;
      auto u = w_edge.end_vertex;

      if (min_paths[v].weight != std::numeric_limits<int>::max() &&
          min_paths[u].weight > min_paths[v].weight + w_edge.weight) {
        // Проверка на наличие в графе цикла с отрицательной весом
        if (min_paths[u].vertices.size() &&
            min_paths[u].vertices[min_paths[u].vertices.size() - 1] == v)
          throw std::invalid_argument(
              "Weighted graph has cicle with negative weight!");
        is_updated = true;

        min_paths[u].weight = min_paths[v].weight + w_edge.weight;
        // Обновляем кратчайший путь
        min_paths[u].vertices = min_paths[v].vertices;
        min_paths[u].vertices.push_back(v);
      }
    }

    // Если кратчайшие пути никак не изменились, то дальше нет смысла
    // продолжать цикл
    if (!is_updated) break;
  }

  // Удаляем вершину, для которой мы находили кратчайшие пути до других вершин
  min_paths.erase(vertex);

  std::vector<MinPath<T>> paths;
  for (auto [v, min_path] : min_paths) {
    min_path.vertices.push_back(v);
    paths.push_back(min_path);
  }

  return paths;
}