#include "graph.hpp"
#include <queue>

void WeightedGraph::CheckNegativeCycle(const vector<int>& distances) {
    for (size_t u = 0; u < vertices_number_; ++u) {
      for (size_t v = 0; v < vertices_number_; ++v) {
        if (table_[u][v] != INF && distances[u] != INF) {
          if (distances[u] + table_[u][v] < distances[v]) {
            throw std::logic_error("Graph contains a negative weight cycle");
          }
        }
      }
    }
  }

  bool WeightedGraph::RelaxEdges(vector<int>& distances) {
    bool updated = false;
    for (size_t u = 0; u < vertices_number_; ++u) {
      for (size_t v = 0; v < vertices_number_; ++v) {
        if (table_[u][v] != INF && distances[u] != INF) {
          if (distances[u] + table_[u][v] < distances[v]) {
            distances[v] = distances[u] + table_[u][v];
            updated = true;
          }
        }
      }
    }
    return updated;
  }

  vector<int> WeightedGraph::BellmanFord(size_t start) {
    vector<int> distances(vertices_number_, INF);
    distances[start] = 0;

    for (size_t i = 0; i < vertices_number_ - 1; ++i) {
      RelaxEdges(distances);
    }

    CheckNegativeCycle(distances);
    return distances;
  }

  vector<int> WeightedGraph::Dijkstra(size_t start) {
    vector<int> distances(vertices_number_, INF);
    distances[start] = 0;

    std::priority_queue<pair<int, int>, vector<pair<int, int>>, std::greater<>>
        pq;
    pq.push({0, start});

    while (!pq.empty()) {
      const int u = pq.top().second;
      const int dist_u = pq.top().first;
      pq.pop();

      if (dist_u > distances[u]) continue;

      for (size_t v = 0; v < vertices_number_; ++v) {
        if (table_[u][v] != INF && distances[u] != INF) {
          const int new_dist = distances[u] + table_[u][v];
          if (new_dist < distances[v]) {
            distances[v] = new_dist;
            pq.push({new_dist, v});
          }
        }
      }
    }
    return distances;
  }

  vector<vector<int>> WeightedGraph::Johnson() {
    vector<int> h(vertices_number_ + 1, 0);

    table_.push_back(vector<int>(vertices_number_, 0));
    try {
      h = BellmanFord(vertices_number_);
    } catch (const std::logic_error&) {
      throw std::logic_error(
          "Graph contains a negative weight cycle, Johnson's algorithm cannot "
          "be applied");
    }
    table_.pop_back();

    for (size_t u = 0; u < vertices_number_; ++u) {
      for (size_t v = 0; v < vertices_number_; ++v) {
        if (table_[u][v] != INF) {
          table_[u][v] += h[u] - h[v];
        }
      }
    }

    vector<vector<int>> distances(vertices_number_);
    for (size_t u = 0; u < vertices_number_; ++u) {
      distances[u] = Dijkstra(u);
      for (size_t v = 0; v < vertices_number_; ++v) {
        if (distances[u][v] != INF) {
          distances[u][v] += h[v] - h[u];
        }
      }
    }

    return distances;
  }

  WeightedGraph::WeightedGraph(vector<vector<int>>&& table)
      : table_(std::move(table)), vertices_number_(table_.size()) {
    if (table_.empty())
      throw std::logic_error(
          "the graph was not created because the input table is empty");
    for (size_t i = 0; i < table_.size(); i++)
      if (table_[i].size() != table_.size())
        throw std::logic_error(
            "the graph was not created because the input table is incorrect");
  }