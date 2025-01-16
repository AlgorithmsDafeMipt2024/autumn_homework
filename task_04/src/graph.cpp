#include "graph.hpp"

Graph::Graph(const std::vector<std::vector<int>>& adj_matr)
    : adj_matr_(adj_matr), v_num_(adj_matr.size()) {}

std::vector<int> Graph::Dijkstra(size_t s) {
  std::vector<int> dist_s(v_num_, kInf);
  dist_s[s] = 0;
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                      std::greater<std::pair<int, int>>>
      q;
  q.push({0, s});
  while (!q.empty()) {
    auto [cur_dist, v] = q.top();
    q.pop();
    if (cur_dist > dist_s[v]) continue;
    for (size_t u = 0; u < v_num_; ++u) {
      const int w = adj_matr_[v][u];
      if (w != kInf && dist_s[v] != kInf)
        if (dist_s[v] + w < dist_s[u]) {
          dist_s[u] = dist_s[v] + w;
          q.push({dist_s[v] + w, u});
        }
    }
  }
  return dist_s;
}
