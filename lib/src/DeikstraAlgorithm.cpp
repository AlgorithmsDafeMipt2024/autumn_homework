#include "DeikstraAlgorithm.h"

#include <cfloat>

double DeikstraAlgorithm(const WeightedGraph& graph, int start_id, int end_id) {
  int n = graph.GetVerts();
  std::vector<bool> ended(n);
  std::vector<double> pathLength(n, DBL_MAX);
  pathLength[start_id] = 0;
  int this_id = start_id;
  int counter = 0;
  for (; true;) {
    if (counter >= n) break;
    for (int i = 0; i < n; ++i) {
      if (graph[this_id][i])
        pathLength[i] =
            std::min(pathLength[i], pathLength[this_id] + graph[this_id][i]);
    }
    ended[this_id] = true;
    double min = DBL_MAX;
    for (int j = 0; j < n; ++j) {
      if (!ended[j])
        if (min > pathLength[j]) {
          min = pathLength[j];
          this_id = j;
        }
    }
    if (this_id == end_id) return pathLength[end_id];
    ++counter;
  }
  return pathLength[end_id];
}

double DeikstraAlgorithm(const OrientedWeightedGraphWithZeroWeight& graph,
                         int start_id, int end_id) {
  int n = graph.GetVerts();
  std::vector<bool> ended(n);
  std::vector<double> pathLength(n, DBL_MAX);
  pathLength[start_id] = 0;
  int this_id = start_id;
  int counter = 0;
  for (; true;) {
    if (counter >= n) break;
    for (int i = 0; i < n; ++i) {
      if (graph[this_id][i])
        pathLength[i] = std::min(
            pathLength[i], pathLength[this_id] + graph.GetWeight(this_id, i));
    }
    ended[this_id] = true;
    double min = DBL_MAX;
    for (int j = 0; j < n; ++j) {
      if (!ended[j])
        if (min > pathLength[j]) {
          min = pathLength[j];
          this_id = j;
        }
    }
    if (this_id == end_id) return pathLength[end_id];
    ++counter;
  }
  return pathLength[end_id];
}

DeikstraReturn DeikstraPathAlgorithm(const WeightedGraph& graph, int start_id,
                                     int end_id) {
  int n = graph.GetVerts();
  std::vector<bool> ended(n);
  std::vector<double> pathLength(n, DBL_MAX);
  std::vector<int> prevs(n, -1);
  pathLength[start_id] = 0;
  int this_id = start_id;
  for (int counter = 0; counter < n && this_id != end_id; ++counter) {
    for (int i = 0; i < n; ++i) {
      if (graph[this_id][i] &&
          pathLength[i] > pathLength[this_id] + graph[this_id][i]) {
        pathLength[i] = pathLength[this_id] + graph[this_id][i];
        prevs[i] = this_id;
      }
    }
    ended[this_id] = true;
    double min = DBL_MAX;
    for (int j = 0; j < n; ++j) {
      if (!ended[j])
        if (min > pathLength[j]) {
          min = pathLength[j];
          this_id = j;
        }
    }
  }
  std::vector<int> path;
  for (int i = end_id; i != start_id; i = prevs[i]) path.push_back(prevs[i]);
  for (int i = 0; i < path.size() / 2; ++i)
    std::swap(path[i], path[path.size() - 1 - i]);
  return DeikstraReturn(path, pathLength[end_id]);
}

DeikstraReturn DeikstraPathAlgorithm(
    const OrientedWeightedGraphWithZeroWeight& graph, int start_id,
    int end_id) {
  if (start_id == end_id) return DeikstraReturn(std::vector<int>(), 0);
  int n = graph.GetVerts();
  std::vector<bool> ended(n);
  std::vector<double> pathLength(n, DBL_MAX);
  std::vector<int> prevs(n, -1);
  pathLength[start_id] = 0;
  int this_id = start_id;
  for (int counter = 0; counter < n && this_id != end_id; ++counter) {
    for (int i = 0; i < n; ++i) {
      if (graph[this_id][i] &&
          pathLength[i] > pathLength[this_id] + graph.GetWeight(this_id, i)) {
        pathLength[i] = pathLength[this_id] + graph.GetWeight(this_id, i);
        prevs[i] = this_id;
      }
    }
    ended[this_id] = true;
    double min = DBL_MAX;
    for (int j = 0; j < n; ++j) {
      if (!ended[j])
        if (min > pathLength[j]) {
          min = pathLength[j];
          this_id = j;
        }
    }
  }
  std::vector<int> path;
  path.push_back(end_id);
  for (int i = end_id; i != start_id; i = prevs[i]) path.push_back(prevs[i]);
  for (int i = 0; i < path.size() / 2; ++i)
    std::swap(path[i], path[path.size() - 1 - i]);
  return DeikstraReturn(path, pathLength[end_id]);
}
