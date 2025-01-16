#include <cfloat>

#include "BellmanForlAlgorithm.h"

std::vector<double> BellmanFordAlgorithm(const WeightedGraph& graph,
                                         int start_id) {
  int n = graph.GetVerts();
  std::vector<double> pathLength(n, DBL_MAX);
  pathLength[start_id] = 0;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      for (int k = 0; k < n; ++k)
        if (graph[j][k] && pathLength[j] != DBL_MAX &&
            pathLength[j] + graph[j][k] < pathLength[k]) {
          if (i == n - 1) return std::vector<double>(0);
          pathLength[k] = pathLength[j] + graph[j][k];
        }
  return pathLength;
}

std::vector<double> BellmanFordAlgorithm(
    const OrientedWeightedGraphWithZeroWeight& graph, int start_id) {
  int n = graph.GetVerts();
  std::vector<double> pathLength(n, DBL_MAX);
  pathLength[start_id] = 0;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      for (int k = 0; k < n; ++k)
        if (graph[j][k] && pathLength[j] != DBL_MAX &&
            pathLength[j] + graph.GetWeight(j, k) < pathLength[k]) {
          if (i == n - 1) return std::vector<double>(0);
          pathLength[k] = pathLength[j] + graph.GetWeight(j, k);
        }
  return pathLength;
}
