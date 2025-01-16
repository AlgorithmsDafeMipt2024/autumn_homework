#include "JonsonAlgorithm.h"

double GetPathLength(const WeightedGraph& graph, const std::vector<int>& path) {
  if (path.size() == 0) return 0;
  double result = 0;
  for (int i = 0; i < path.size() - 1; ++i)
    result += graph[path[i]][path[i + 1]];
  return result;
}

OrientedWeightedGraphWithZeroWeight JonsonAlgorithm(
    const WeightedGraph& graph) {
  int n = graph.GetVerts();
  OrientedWeightedGraphWithZeroWeight new_graph(graph);
  for (int i = 0; i < n; ++i) new_graph.AddEdge(n, i, 0);
  auto h = BellmanFordAlgorithm(new_graph, n);
  if (h.size() == 0) return WeightedGraph();
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j) new_graph.GetWeight(i, j) += h[i] - h[j];
  OrientedWeightedGraphWithZeroWeight resultGraph;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      resultGraph.AddEdge(
          i, j,
          GetPathLength(graph, DeikstraPathAlgorithm(new_graph, i, j).path));
  return resultGraph;
}
