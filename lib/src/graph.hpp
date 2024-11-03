#pragma once

#include <cmath>
#include <limits>
#include <list>
#include <memory>
#include <queue>
#include <stdexcept>
#include <vector>

using std::list;
using std::pair;
using std::vector;

const int INF = std::numeric_limits<int>::max();

template <typename T>
class Graph {
 private:
  size_t vertices_number_;
  vector<vector<T>> adjacency_list_;

 public:
  Graph(size_t number) {
    if (number <= 0) throw std::logic_error("number must be positive!");
    vertices_number_ = number;
    adjacency_list_.resize(vertices_number_ + 1);
  }

  void AddEdge(size_t first_verticle, size_t second_verticle) {
    if (first_verticle < 1 || first_verticle > vertices_number_ ||
        second_verticle < 1 || second_verticle > vertices_number_)
      throw std::logic_error("such node does not exist");
    if (first_verticle == second_verticle)
      throw std::logic_error("graph must be acyclic!");
    adjacency_list_[first_verticle].push_back(second_verticle);
  }

  void TopologySortStep(int current_vertice, vector<bool>& visited_vertices,
                        list<T>& list) {
    visited_vertices[current_vertice] = true;
    for (const auto& neighbor : adjacency_list_[current_vertice]) {
      if (!visited_vertices[neighbor]) {
        TopologySortStep(neighbor, visited_vertices, list);
      }
    }
    list.push_front(current_vertice);
  }

  list<T> TopologySort() {
    list<T> list;
    vector<bool> visited_vertices(vertices_number_ + 1, false);
    for (size_t i = 1; i <= vertices_number_; i++) {
      if (!visited_vertices[i]) {
        TopologySortStep(i, visited_vertices, list);
      }
    }
    return list;
  }
};

class WeightedGraph {
 private:
  vector<vector<int>> table_;
  size_t vertices_number_;

  void CheckNegativeCycle(const vector<int>& distances) {
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

  bool RelaxEdges(vector<int>& distances) {
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

  vector<int> BellmanFord(size_t start) {
    vector<int> distances(vertices_number_, INF);
    distances[start] = 0;

    for (size_t i = 0; i < vertices_number_ - 1; ++i) {
      RelaxEdges(distances);
    }

    CheckNegativeCycle(distances);
    return distances;
  }

 public:
  WeightedGraph(vector<vector<int>>&& table)
      : table_(std::move(table)), vertices_number_(table_.size()) {
    if (table_.empty())
      throw std::logic_error(
          "the graph was not created because the input table is empty");
    for (size_t i = 0; i < table_.size(); i++)
      if (table_[i].size() != table_.size())
        throw std::logic_error(
            "the graph was not created because the input table is incorrect");
  }

  vector<int> Dijkstra(size_t start) {
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

  vector<vector<int>> Johnson() {
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
};

template <typename T>
class BridgeGraph {
 private:
  size_t vertices_number_;
  list<T>* adjacency_list_;
  vector<int> tin_, low_;
  vector<bool> visited_;
  vector<pair<int, int>> bridges_;
  vector<int> articulation_points_;

  void dfs(int v, int p, int& timer) {
    visited_[v] = true;
    tin_[v] = low_[v] = timer++;
    int children = 0;

    for (int to : adjacency_list_[v]) {
      if (to == p) continue;
      if (visited_[to]) {
        low_[v] = std::min(low_[v], tin_[to]);
      } else {
        dfs(to, v, timer);
        low_[v] = std::min(low_[v], low_[to]);

        if (low_[to] > tin_[v]) bridges_.push_back({v, to});
        if (articulation_points_.empty()) {
          if (low_[to] >= tin_[v] && p != -1) {
            if (articulation_points_.empty() ||
                articulation_points_.back() != v) {
              articulation_points_.push_back(v);
            }
          }
        }
        ++children;
      }
    }

    if (p == -1 && children > 1) articulation_points_.push_back(v);
  }

 public:
  BridgeGraph(size_t number) {
    if (number <= 0) throw std::logic_error("number must be positive!");
    vertices_number_ = number;
    adjacency_list_ = new list<T>[vertices_number_ + 1];
  }

  void AddEdge(size_t first_verticle, size_t second_verticle) {
    if (first_verticle < 0 || first_verticle > vertices_number_ ||
        second_verticle < 0 || second_verticle > vertices_number_)
      throw std::logic_error("such node does not exist");
    if (first_verticle == second_verticle)
      throw std::logic_error("graph must be acyclic!");
    adjacency_list_[first_verticle].push_back(second_verticle);
    adjacency_list_[second_verticle].push_back(first_verticle);
  }

  void FindBridgesAndArticulationPoints() {
    int timer = 0;
    tin_.assign(vertices_number_ + 1, -1);
    low_.assign(vertices_number_ + 1, -1);
    visited_.assign(vertices_number_ + 1, false);
    bridges_.clear();
    articulation_points_.clear();

    for (size_t i = 0; i <= vertices_number_; ++i) {
      if (!visited_[i]) dfs(i, -1, timer);
    }
  }

  vector<pair<int, int>> GiveBridges() { return bridges_; }
  vector<int> GivePoints() { return articulation_points_; }
};