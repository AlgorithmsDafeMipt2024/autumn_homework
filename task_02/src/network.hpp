#pragma once

#include "graph.hpp"

/// @brief Vertex representing a single router
class Router : public Vertex<int>{
  public:
  std::set<std::shared_ptr<Router>> adjacent;
};


/// @brief Graph of routers in cities net
class Network : public Graph<Router, int> {
 public:
  /// @brief Finds bridges and cut vertices in graph using Tarjan's algorithm
  std::pair<std::vector<std::pair<int, int>>, std::vector<int>>
  FindBridgesAndCutVertices();

 private:
  void TarjanVisit(size_t vertex_id, std::vector<int> &disc,
                   std::vector<int> &low, std::vector<int> &parent,
                   std::vector<std::pair<int, int>> &bridges,
                   std::vector<int> &cut_vertices, int &time);
};