#pragma once

#include <cmath>
#include <list>
#include <stdexcept>
#include <vector>

using std::vector;

template <typename T>
class Graph {
 private:
  int vertices_number;
  std::list<T>* adjacency_list;

 public:
  Graph(int number) {
    if (number <= 0) throw std::logic_error("number must be positive!");
    vertices_number = number;
    adjacency_list = new std::list<T>[vertices_number + 1];
  }
  void AddEdge(int first_verticle, int second_verticle) {
    if (first_verticle < 0 || first_verticle > vertices_number ||
        second_verticle < 0 || second_verticle > vertices_number)
      throw std::logic_error("such node does not exist");
    if (first_verticle == second_verticle)
      throw std::logic_error("graph must be acyclic!");
    adjacency_list[first_verticle].push_back(second_verticle);
  }
  void TopologySortStep(int current_vertice, bool visited_vertices[],
                        std::list<int>& list) {
    visited_vertices[current_vertice] = true;
    for (typename std::list<T>::iterator i =
             adjacency_list[current_vertice].begin();
         i != adjacency_list[current_vertice].end(); i++) {
      if (!visited_vertices[*i]) TopologySortStep(*i, visited_vertices, list);
    }
    list.push_front(current_vertice);
  }
  std::list<int> TopologySort() {
    std::list<T> list;
    bool* visited_vertices = new bool[vertices_number];
    for (int i = 0; i < vertices_number; i++) {
      if (!visited_vertices[i]) TopologySortStep(i, visited_vertices, list);
    }
    return list;
  }
};

class Weighted_Graph {
 private:
  vector<vector<int>> table;
  int vertices_number;

 public:
  Weighted_Graph(vector<vector<int>> table_) {
    if (table_.empty())
      throw std::logic_error(
          "the graph was not created because the input table is empty");
    for (int i = 0; i < table_.size(); i++)
      if (table_[i].size() != table_.size())
        throw std::logic_error(
            "the graph was not created because the input table is incorrect");
    table = table_;
    vertices_number = table.size();
  }

  int MinDistance(vector<int> distances, bool is_shortest[]) {
    int min_distance = 2 ^ 31 - 1, min_index;
    for (int i = 0; i < vertices_number; i++)
      if (!is_shortest[i] && distances[i] < min_distance)
        min_distance = distances[i], min_index = i;
    return min_index;
  };
  vector<int> Dijkstra_algo(int source) {
    source -= 1;
    vector<int> distances;
    bool is_shortest[vertices_number];
    for (int i = 0; i < vertices_number; i++) {
      distances.push_back(std::pow(2, 31) - 1);
      is_shortest[i] = false;
    }
    distances[source] = 0;
    for (int i = 0; i < vertices_number - 1; i++) {
      int min_distance = MinDistance(distances, is_shortest);
      is_shortest[min_distance] = true;
      for (int j = 0; j < vertices_number; j++)
        if (!is_shortest[j] && table[min_distance][j] &&
            distances[j] != (2 ^ 31 - 1) &&
            distances[min_distance] + table[min_distance][j] < distances[j])
          distances[j] = distances[min_distance] + table[min_distance][j];
    }
    return distances;
  }
  vector<int> BellmanFord_Algorithm(int source) {
    vector<int> dist(source + 1, pow(2, 31));
    dist[source] = 0;

    vector<vector<int>> edges_with_extra(table);
    for (int i = 0; i < source; ++i) {
      edges_with_extra.push_back({source, i, 0});
    }

    for (int i = 0; i < source; ++i) {
      for (const auto& edge : edges_with_extra) {
        if (dist[edge[0]] != pow(2, 31) &&
            dist[edge[0]] + edge[2] < dist[edge[1]]) {
          dist[edge[1]] = dist[edge[0]] + edge[2];
        }
      }
    }
    return vector<int>(dist.begin(), dist.begin() + source);
  }
  vector<vector<int>> JohnsonAlgorithm(const vector<vector<int>>& graph) {
    int V = graph.size();
    vector<vector<int>> edges;

    for (int i = 0; i < V; ++i)
      for (int j = 0; j < V; ++j)
        if (graph[i][j] != 0) edges.push_back({i, j, graph[i][j]});

    vector<int> altered_weights = BellmanFord_Algorithm(V);
    vector<vector<int>> altered_graph(V, vector<int>(V, 0));

    for (int i = 0; i < V; ++i)
      for (int j = 0; j < V; ++j)
        if (graph[i][j] != 0)
          altered_graph[i][j] =
              graph[i][j] + altered_weights[i] - altered_weights[j];

    return altered_graph;
  }
};

template <typename T>
class BridgeGraph {
 private:
  int vertices_number;
  std::list<T>* adjacency_list;
  vector<int> tin, low;
  vector<bool> visited;
  vector<std::pair<int, int>> bridges;
  vector<int> articulation_points;

  void dfs(int v, int p, int& timer) {
    visited[v] = true;
    tin[v] = low[v] = timer++;
    int children = 0;

    for (int to : adjacency_list[v]) {
      if (to == p) continue;
      if (visited[to]) {
        low[v] = std::min(low[v], tin[to]);
      } else {
        dfs(to, v, timer);
        low[v] = std::min(low[v], low[to]);

        if (low[to] > tin[v]) bridges.push_back({v, to});
        if (low[to] >= tin[v] && p != -1) {
          if (articulation_points.empty()) {
            articulation_points.push_back(v);
          } else if (articulation_points.back() != v) {
            articulation_points.push_back(v);
          }
        }
        ++children;
      }
    }

    if (p == -1 && children > 1) articulation_points.push_back(v);
  }

 public:
  BridgeGraph(int number) {
    if (number <= 0) throw std::logic_error("number must be positive!");
    vertices_number = number;
    adjacency_list = new std::list<T>[vertices_number + 1];
  }

  void AddEdge(int first_verticle, int second_verticle) {
    if (first_verticle < 0 || first_verticle > vertices_number ||
        second_verticle < 0 || second_verticle > vertices_number)
      throw std::logic_error("such node does not exist");
    if (first_verticle == second_verticle)
      throw std::logic_error("graph must be acyclic!");
    adjacency_list[first_verticle].push_back(second_verticle);
    adjacency_list[second_verticle].push_back(first_verticle);
  }

  void FindBridgesAndArticulationPoints() {
    int timer = 0;
    tin.assign(vertices_number + 1, -1);
    low.assign(vertices_number + 1, -1);
    visited.assign(vertices_number + 1, false);
    bridges.clear();
    articulation_points.clear();

    for (int i = 0; i <= vertices_number; ++i) {
      if (!visited[i]) dfs(i, -1, timer);
    }
  }

  vector<std::pair<int, int>> GiveBridges() { return bridges; }
  vector<int> GivePoints() { return articulation_points; }
};