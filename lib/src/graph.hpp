#pragma once

#include <cmath>
#include <limits>
#include <list>
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
    if (number == 0) throw std::logic_error("number must be positive!");
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

  void CheckNegativeCycle(const vector<int>& distances);

  bool RelaxEdges(vector<int>& distances);

  vector<int> BellmanFord(size_t start);

 public:
  WeightedGraph(vector<vector<int>>&& table);

  vector<int> Dijkstra(size_t start);

  vector<vector<int>> Johnson();
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