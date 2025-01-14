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

  void AddEdge(int, int, int);

  int GetVertexesNum();
  int GetEdgesNum();
  const AdjacencyList GetAdjList();

  std::vector<std::pair<int, int>> GetNeighbours(int);

  bool HasEdge(int, int) const;

  void PrintGraph() const;

  std::vector<int> TopologicalSort(int);

  std::vector<std::pair<int, int>> GetBridges();
  std::vector<int> GetArticulationPoints();

 private:
  int vertexes_num = 0;
  int edges_num = 0;
  bool is_directed = false;

  AdjacencyList adjList;

  void TopSort(int, std::vector<bool>&, std::vector<int>&);

  void DfsBridges(int, int, std::vector<int>&, std::vector<int>&,
                  std::vector<bool>&, int&, std::vector<std::pair<int, int>>&);

  void DfsArticulation(int, int, std::vector<int>&, std::vector<int>&,
                       std::vector<bool>&, int&, std::vector<bool>&);
};
};  // namespace algo

#endif  // GRAPH_HPP
