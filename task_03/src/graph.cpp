#include "graph.hpp"

Graph::Graph(const std::vector<std::vector<int>>& adj_matr)
    : adj_matr_(adj_matr), v_num_(adj_matr.size()) {}

bool Graph::BellmanFord(std::vector<int>& h) {
  std::vector<int> distances(v_num_, kInf);
  distances[v_num_ - 1] = 0;
  for (size_t i = 0; i < v_num_ - 1; ++i) RelaxEdges(distances);
  h = distances;
  return HasNegativeCycle(distances);
}

bool Graph::HasNegativeCycle(const std::vector<int>& distances) {
  for (size_t u = 0; u < v_num_; ++u)
    for (size_t v = 0; v < v_num_; ++v)
      if (adj_matr_[u][v] != kInf && distances[u] != kInf)
        if (distances[u] + adj_matr_[u][v] < distances[v]) return true;
  return false;
}

void Graph::RelaxEdges(std::vector<int>& distances) {
  for (size_t u = 0; u < v_num_; ++u)
    for (size_t v = 0; v < v_num_; ++v)
      if (adj_matr_[u][v] != kInf && distances[u] != kInf)
        if (distances[u] + adj_matr_[u][v] < distances[v])
          distances[v] = distances[u] + adj_matr_[u][v];
}

std::vector<std::vector<int>> Graph::Johnson() {
  std::vector<int> h(v_num_, 0);
  if (BellmanFord(h)) exit(1);
  for (size_t u = 0; u < v_num_; ++u)
    for (size_t v = 0; v < v_num_; ++v)
      if (adj_matr_[u][v] != kInf) adj_matr_[u][v] += h[u] - h[v];
  std::vector<std::vector<int>> dist(v_num_);
  for (size_t u = 0; u < v_num_; ++u) {
    dist[u] = Dijkstra(u);
    for (size_t v = 0; v < v_num_; ++v)
      if (dist[u][v] != kInf) dist[u][v] += h[v] - h[u];
  }
  return dist;
}

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
