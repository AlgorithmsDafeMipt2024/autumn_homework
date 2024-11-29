#pragma once

#include <algorithm>
#include <limits>
#include <unordered_map>

#include "graph/weighted_graph.hpp"

#define INF std::numeric_limits<int>::max()

template <typename T>
struct MinPath {
 public:
  MinPath() = default;

  MinPath(const std::vector<T>& vertices, int weight)
      : vertices(vertices), weight(weight) {}

  void PrintMinPath() {
    for (int i = 0; i < vertices.size(); i++) {
      std::cout << vertices[i];
      if (i != vertices.size() - 1) std::cout << "->";
    }
    if (weight != INF)
      std::cout << ": " << weight << '\n';
    else
      std::cout << ": inf\n";
  }

  int weight;
  std::vector<T> vertices;
};

template <typename T>
bool operator==(const MinPath<T>& lhs, const MinPath<T>& rhs) {
  return lhs.vertices == rhs.vertices && lhs.weight == rhs.weight;
}

template <typename T>
void DijkstraStep(WeightedGraph<T>& graph,
                  std::unordered_map<T, MinPath<T>>& min_paths,
                  std::unordered_map<T, bool>& visited) {
  int min_weight = INF;
  std::pair<T, T> edge;

  for (auto [v, is_visited] : visited) {
    if (is_visited) {
      int weight_v = min_paths[v].weight;
      for (auto u : graph.GetAdjVertices(v)) {
        if (!visited[u]) {
          int edge_weight = graph.GetEdgeWeight(v, u);
          if (min_weight > weight_v + edge_weight) {
            min_weight = weight_v + edge_weight;
            edge.first = v;
            edge.second = u;
          }
        }
      }
    }
  }

  // Случай, когда какие-то вершины недостижимы
  if (!edge.first && !edge.second) return;

  if (visited.size() && min_paths.size()) {
    T v = edge.first, u = edge.second;  // v - родитель, u - ребенок
    visited[u] = true;

    // Добавляем минимальный найденный путь для вершины
    for (auto v : min_paths[v].vertices) min_paths[u].vertices.push_back(v);
    min_paths[u].vertices.push_back(v);
    min_paths[u].weight = min_weight;
  }

  for (auto [v, is_visited] : visited)
    if (!is_visited) DijkstraStep(graph, min_paths, visited);
}

template <typename T>
std::vector<MinPath<T>> Dijkstra(const T& vertex, WeightedGraph<T> graph) {
  for (auto w_edge : graph.GetWeightedEdges())
    if (w_edge.weight < 0)
      throw std::invalid_argument(
          "Weighted graph has edges with negative weights!");

  if (!graph.ContainsVertex(vertex))
    throw std::invalid_argument("Root vertex not found!");

  std::unordered_map<T, MinPath<T>> min_paths;
  std::unordered_map<T, bool> visited;
  for (auto v : graph.GetVerticesIds()) {
    if (v == vertex)
      visited[v] = true;
    else {
      min_paths[v].weight = INF;
      visited[v] = false;
    }
  }

  DijkstraStep(graph, min_paths, visited);

  // Удаляем вершину, для которой мы находили кратчайшие пути до других вершин
  min_paths.erase(vertex);

  std::vector<MinPath<T>> paths;
  for (auto [v, min_path] : min_paths) {
    // Добавляем в путь конечную вершину
    min_path.vertices.push_back(v);

    paths.push_back(min_path);
  }

  // Переворачиваем массив, чтобы конечными точками в пути являлись первые
  // добавленные вершины в графе
  reverse(paths.begin(), paths.end());

  return paths;
}