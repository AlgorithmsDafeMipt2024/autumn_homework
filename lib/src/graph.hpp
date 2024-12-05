#pragma once

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>

using AdjacencyList = std::vector<std::vector<std::pair<int, int>>>;

namespace algo {
class Graph {
 public:
  Graph(int v, int e);

  Graph(int v, int e, bool directed);

  void addEdge(int, int, int);

  int getVertexesNum();
  int getEdgesNum();
  const AdjacencyList getAdjList();

  std::vector<std::pair<int, int>> getNeighbours(int);

  bool hasEdge(int, int) const;

  void printGraph() const;

  std::vector<int> topological_sort(int);

  std::vector<std::pair<int, int>> getBridges();
  std::vector<int> getArticulationPoints();

 private:
  int vertexes_num = 0;
  int edges_num = 0;
  bool is_directed = false;

  AdjacencyList adjList;

  void top_sort(int, int, std::vector<bool>&, std::vector<int>&);

  void dfsBridges(int, int, std::vector<int>&, std::vector<int>&,
                  std::vector<bool>&, int&, std::vector<std::pair<int, int>>&);

  void dfsArticulation(int, int, std::vector<int>&, std::vector<int>&,
                       std::vector<bool>&, int&, std::vector<bool>&);
};
};  // namespace algo

#endif  // GRAPH_HPP
