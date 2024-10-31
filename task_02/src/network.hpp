#pragma once

#include "graph.hpp"

/// @brief Graph of routers in cities net
class Network : public Graph<int> {
 public:
  /// @brief Finds bridges and cut vertices in graph using Tarjan's algorithm
  void FindBridgesAndCutVertices();

 private:
  void TarjanVisit(size_t vertex_id, std::vector<int> &disc,
                   std::vector<int> &low, std::vector<int> &parent,
                   std::vector<std::pair<int, int>> &bridges,
                   std::vector<int> &cut_vertices, int &time);
};