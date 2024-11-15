#pragma once
#include <queue>

#include "weighted_graph.hpp"

template <typename T>
std::pair<std::vector<int>, std::vector<int>> Dijkstra(
    const WeightedGraph<T>& graph, size_t start) {
  const size_t size = graph.Size();

  // Distance array to store shortest distances from start
  std::vector<int> distances(size, std::numeric_limits<int>::max());

  // Previous vertex array to reconstruct the path
  std::vector<int> previous(size, -1);

  // Visited set to keep track of processed vertices
  std::vector<bool> visited(size, false);

  // Priority queue to get vertex with minimum distance
  // pair: (distance, vertex_index)
  std::priority_queue<std::pair<int, size_t>,
                      std::vector<std::pair<int, size_t>>, std::greater<>>
      pq;

  // Initialize distance to start vertex as 0
  distances[start] = 0;
  pq.push({0, start});

  while (!pq.empty()) {
    size_t current = pq.top().second;
    pq.pop();

    // Skip if already visited
    if (visited[current]) continue;

    visited[current] = true;

    // For each adjacent vertex of current vertex
    for (const auto& neighbor : graph[current]->adjacent) {
      size_t next = graph.Find(neighbor->data);
      int weight = graph.GetWeight(current, next);

      // If we found a shorter path to neighbor
      if (!visited[next] &&
          distances[current] != std::numeric_limits<int>::max() &&
          distances[current] + weight < distances[next]) {
        distances[next] = distances[current] + weight;
        previous[next] = current;
        pq.push({distances[next], next});
      }
    }
  }

  return {distances, previous};
}

/**
 * @brief
 * Reconstruct path from start to end vertex
 * @tparam T
 * @param previous
 * @param start
 * @param end
 * @return std::vector<int> path
 */
template <typename T>
std::vector<int> GetPath(const std::vector<int>& previous, size_t start,
                         size_t end) {
  std::vector<int> path;

  // If there's no path to end
  if (previous[end] == -1 && end != start) return path;

  // Reconstruct path by walking backwards from end to start
  for (size_t current = end; current != -1; current = previous[current]) {
    path.push_back(current);
    if (current == start) break;
  }

  // Reverse path to get start->end order
  std::reverse(path.begin(), path.end());
  return path;
}