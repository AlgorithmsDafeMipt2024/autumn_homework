#include "bridge.hpp"

void weak_edge(std::vector<std::vector<int>> &data, std::vector<bool> &visited,
               std::vector<int> &time_in, std::vector<int> &min_time_in,
               std::vector<std::pair<int, int>> &bridges, int time, int v,
               int p) {
  visited[v] = true;
  time_in[v] = min_time_in[v] = time++;
  for (size_t i = 0; i < data[v].size(); ++i) {
    int const to = data[v][i];
    if (to == p) {
      continue;
    }
    if (visited[to]) {
      min_time_in[v] = std::min(min_time_in[v], time_in[to]);
    } else {
      weak_edge(data, visited, time_in, min_time_in, bridges, time, to, v);
      min_time_in[v] = std::min(min_time_in[v], min_time_in[to]);
      if (min_time_in[to] > time_in[v]) {
        bridges.push_back(std::pair<int, int>({v, to}));
      }
    }
  }
}

std::vector<std::pair<int, int>> cutting_edge(
    std::vector<std::vector<int>> &data) {
  int const time = 0;
  std::vector<int> time_in(data.size(), -1);
  std::vector<int> min_time_in(data.size(), -1);
  std::vector<std::pair<int, int>> bridges;
  std::vector<bool> visited(data.size(), false);
  for (int i = 0; i < data.size(); ++i)
    if (!visited[i]) {
      weak_edge(data, visited, time_in, min_time_in, bridges, time, i);
    }
  return bridges;
}