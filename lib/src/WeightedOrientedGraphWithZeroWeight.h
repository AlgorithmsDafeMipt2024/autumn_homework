#pragma once

#include "WeightedGraph.h"

class OrientedWeightedGraphWithZeroWeight {
 private:
  std::vector<std::vector<bool>> graph;
  std::vector<std::vector<double>> weight_graph;

 public:
  OrientedWeightedGraphWithZeroWeight() = default;
  OrientedWeightedGraphWithZeroWeight(const WeightedGraph& graph);

  const std::vector<bool>& operator[](int i) const { return graph[i]; }
  std::vector<bool>& operator[](int i) { return graph[i]; }
  int GetVerts() const { return graph.size(); }
  void Print();

  bool AddVert(int id);
  bool AddEdge(int id0, int id1, double value);
  bool DeleteVert(int id);
  bool DeleteEdge(int id0, int id1);

  double GetWeight(int i, int j) const { return weight_graph[i][j]; }
  double& GetWeight(int i, int j) { return weight_graph[i][j]; }
};
