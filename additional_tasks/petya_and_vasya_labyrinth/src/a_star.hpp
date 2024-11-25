#pragma once

#include <functional>
#include <limits>
#include <queue>
#include <set>

#include "graph/graph.hpp"

template <AllowedVertType vert_t, AllowedWeightType weight_t>
weight_t AStar(
    const vert_t& start, const vert_t& goal,
    const Graph<vert_t, weight_t>& graph,
    std::function<weight_t(const vert_t&, const vert_t&)> heuristic_range) {
  if (!graph.ContainsVert(start))
    throw std::invalid_argument(
        "AStar: there is no such start vertice in graph.");

  if (!graph.ContainsVert(goal))
    throw std::invalid_argument(
        "AStar: there is no such goal vertice in graph.");

  std::priority_queue<std::pair<weight_t, vert_t>,
                      std::vector<std::pair<weight_t, vert_t>>,
                      std::greater<std::pair<weight_t, vert_t>>>
      visited_verts;

  std::unordered_map<vert_t, weight_t> cost_from_start;
  std::unordered_map<vert_t, weight_t> range_plus_cost;

  for (const auto& v : graph.Verts())
    cost_from_start[v] = std::numeric_limits<weight_t>::max();

  cost_from_start[start] = 0;
  range_plus_cost[start] =
      cost_from_start[start] + heuristic_range(start, goal);
  visited_verts.push({range_plus_cost[start], start});

  while (!visited_verts.empty()) {
    // посещенная вершина с минимальным значением range_plus_cost
    vert_t current = visited_verts.top().second;
    visited_verts.pop();

    if (current == goal)
      return cost_from_start[goal];  // уже нашли путь до нужной вершины

    for (size_t i = 0; i < graph.GetAdjList()[current].size(); i++) {
      auto neighbor = graph.GetAdjList()[current][i];

      weight_t tentative_score =
          cost_from_start[current] +
          ((graph.IsWeighted()) ? graph.GetWeightOfEdge({current, neighbor})
                                : 1);

      if (tentative_score < cost_from_start[neighbor]) {
        cost_from_start[neighbor] = tentative_score;

        // range_plus_cost для новой вершины (другого соседа)
        range_plus_cost[neighbor] =
            cost_from_start[neighbor] + heuristic_range(neighbor, goal);
        visited_verts.push({range_plus_cost[neighbor], neighbor});
      }
    }
  }

  // путь не был найден
  return std::numeric_limits<weight_t>::max();
}