#include "WeightedOrientedGraphWithZeroWeight.h"

OrientedWeightedGraphWithZeroWeight::OrientedWeightedGraphWithZeroWeight(
    const WeightedGraph& graph) {
  int n = graph.GetVerts();
  this->graph.resize(n);
  this->weight_graph.resize(n);
  for (int i = 0; i < n; ++i) {
    this->graph[i].resize(n);
    this->weight_graph[i].resize(n);
    for (int j = 0; j < n; ++j)
      if (graph[i][j]) {
        this->graph[i][j] = 1;
        this->weight_graph[i][j] = graph[i][j];
      }
  }
}

bool OrientedWeightedGraphWithZeroWeight::AddVert(int id) {
  if (id >= graph.size()) {
    graph.resize(id + 1);
    weight_graph.resize(id + 1);
    for (int i = 0; i < graph.size(); ++i) {
      graph[i].resize(id + 1);
      weight_graph[i].resize(id + 1);
      graph[i][i] = 1;
    }
  }
  return false;
}

bool OrientedWeightedGraphWithZeroWeight::AddEdge(int id0, int id1,
                                                  double value) {
  if (id0 == id1) return true;
  AddVert(std::max(id0, id1));
  graph[id0][id1] = 1;
  weight_graph[id0][id1] = value;
  return false;
}

bool OrientedWeightedGraphWithZeroWeight::DeleteVert(int id) {
  if (id >= graph.size()) return true;
  graph.resize(id + 1);
  weight_graph.resize(id + 1);
  for (int i = 0; i < graph.size(); ++i) {
    graph[i].resize(id + 1);
    weight_graph[i].resize(id + 1);
  }
  return false;
}

bool OrientedWeightedGraphWithZeroWeight::DeleteEdge(int id0, int id1) {
  if (id0 == id1 || std::max(id0, id1) >= graph.size()) return true;
  graph[id0][id1] = 0;
  weight_graph[id0][id1] = 0;
  return false;
}

void OrientedWeightedGraphWithZeroWeight::Print() {
  for (int i = 0; i < graph.size(); ++i) {
    for (int j = 0; j < graph.size(); ++j)
      std::cout << "(" << graph[i][j] << ", " << weight_graph[i][j] << "), ";
    std::cout << std::endl;
  }
  std::cout << std::endl;
}
