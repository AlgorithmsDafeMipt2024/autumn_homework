#pragma once

#include "graph/graph.hpp"

template <AllowedVertType vert_t, AllowedWeightType weight_t>
std::unordered_map<vert_t, weight_t> Dijkstra(
    const Graph<vert_t, weight_t>& graph, const vert_t& start) {
  if (graph.Verts().empty()) return {};

  std::unordered_map<vert_t, weight_t> distances;
  std::unordered_map<vert_t, bool> visited;

  // инициализация расстояний до бесконечности
  for (const auto& vert : graph.Verts()) {
    distances[vert] = std::numeric_limits<weight_t>::infinity();
    visited[vert] = false;
  }

  distances[start] = 0;

  for (size_t i = 0; i < graph.VertsAmount(); i++) {
    vert_t min_vert =
        graph.Verts()[0];  // находим вершину с минимальным расстоянием
    weight_t min_distance = std::numeric_limits<weight_t>::infinity();

    for (const auto& node : graph.Verts())
      if (!visited[node] && distances[node] < min_distance) {
        min_vert = node;
        min_distance = distances[node];
      }

    if (min_distance == std::numeric_limits<weight_t>::infinity())
      break;  // все достижимые вершины обработаны

    visited[min_vert] = true;

    // релаксация ребер
    const auto neighbors = graph.GetAdjList()[min_vert];
    for (const auto& vert : neighbors) {
      auto weight = graph.GetWeightOfEdge({min_vert, vert});
      if (weight < 0)
        throw std::logic_error(
            "Dijkstra: graph contains negative weighted edges.");

      if (distances[min_vert] + weight < distances[vert])
        distances[vert] = distances[min_vert] + weight;
    }
  }

  return distances;
}
