#include "graph.hpp"

#include <iostream>
#include <stdexcept>

#define UNREACHABLE (-1)

using namespace algo;

Graph::Graph(int v, int e) {
  if (v <= 0)
    throw std::invalid_argument(
        "Number of vertices must be greater than zero.");

  vertexes_num = v;
  edges_num = e;
  adjList.resize(v);
}

Graph::Graph(int v, int e, bool directed) {
  if (v <= 0)
    throw std::invalid_argument(
        "Number of vertices must be greater than zero.");

  vertexes_num = v;
  edges_num = e;
  is_directed = directed;
  adjList.resize(v);
}

void Graph::AddEdge(int u, int v, int weight) {
  if (u < 1 || u > vertexes_num || v < 1 || v > vertexes_num) {
    throw std::out_of_range("Vertex out of bounds in addEdge.");
  }

  adjList[u - 1].emplace_back(v - 1, weight);
  if (!is_directed) adjList[v - 1].emplace_back(u - 1, weight);

  edges_num++;
}

int Graph::GetVertexesNum() {
  if (vertexes_num <= 0)
    throw std::runtime_error("Graph is not properly initialized.");
  return vertexes_num;
}

int Graph::GetEdgesNum() { return edges_num; }

const AdjacencyList Graph::GetAdjList() { return adjList; }

void Graph::PrintGraph() const {
  if (vertexes_num == 0) {
    std::cerr << "Error: Graph is empty." << std::endl;
    return;
  }

  for (int i = 0; i < vertexes_num; i++) {
    if (adjList[i].empty()) continue;

    std::cout << "Node " << i + 1 << ": ";

    for (const auto& [neighbor, weight] : adjList[i]) {
      std::cout << "(" << neighbor + 1 << ", " << weight << ") ";
    }
    std::cout << std::endl;
  }
}

std::vector<std::pair<int, int>> Graph::GetNeighbours(int v) {
  if (v < 0 || v >= vertexes_num) {
    throw std::out_of_range("Vertex index out of bounds in getNeighbours.");
  }
  return adjList[v];
}

void Graph::TopSort(int v, std::vector<bool>& visited, std::vector<int>& way) {
  if (visited[v]) return;
  visited[v] = true;
  way.push_back(v);

  for (auto [u, w] : GetNeighbours(v)) {
    if (!visited[u]) {
      TopSort(u, visited, way);
    }
  }
}

std::vector<int> Graph::TopologicalSort(int start) {
  if (vertexes_num == 0) {
    std::cerr
        << "Error: Graph is empty, topological sort cannot be performed.\n";
    return {};
  }

  std::vector<int> way;
  std::vector<bool> visited(GetVertexesNum(), false);

  TopSort(start, visited, way);

  if (way.size() < vertexes_num)
    throw std::invalid_argument("Graph is disconnected.");

  return way;
}

std::vector<std::pair<int, int>> Graph::GetBridges() {
  std::vector<int> tin(vertexes_num, -1);
  std::vector<int> low(vertexes_num, -1);
  std::vector<bool> visited(vertexes_num, false);
  std::vector<std::pair<int, int>> bridges;
  int timer = 0;

  for (int i = 0; i < vertexes_num; i++) {
    if (!visited[i]) {
      DfsBridges(i, -1, tin, low, visited, timer, bridges);
    }
  }

  return bridges;
}

void Graph::DfsBridges(int v, int parent, std::vector<int>& tin,
                       std::vector<int>& low, std::vector<bool>& visited,
                       int& timer, std::vector<std::pair<int, int>>& bridges) {
  visited[v] = true;
  tin[v] = low[v] = timer++;

  for (auto [u, _] : adjList[v]) {
    if (u == parent) continue;

    if (!visited[u]) {
      DfsBridges(u, v, tin, low, visited, timer, bridges);
      low[v] = std::min(low[v], low[u]);

      if (low[u] > tin[v]) {
        bridges.emplace_back(v + 1, u + 1);  // Добавляем мост (нумерация с 1)
      }
    } else {
      low[v] = std::min(low[v], tin[u]);
    }
  }
}

std::vector<int> Graph::GetArticulationPoints() {
  std::vector<int> tin(vertexes_num, -1);
  std::vector<int> low(vertexes_num, -1);
  std::vector<bool> visited(vertexes_num, false);
  std::vector<bool> isArticulationPoint(vertexes_num, false);
  int timer = 0;

  for (int i = 0; i < vertexes_num; i++) {
    if (!visited[i]) {
      DfsArticulation(i, -1, tin, low, visited, timer, isArticulationPoint);
    }
  }

  std::vector<int> articulationPoints;
  for (int i = 0; i < vertexes_num; i++) {
    if (isArticulationPoint[i]) {
      articulationPoints.push_back(i + 1);  // Нумерация с 1
    }
  }

  return articulationPoints;
}

void Graph::DfsArticulation(int v, int parent, std::vector<int>& tin,
                            std::vector<int>& low, std::vector<bool>& visited,
                            int& timer,
                            std::vector<bool>& isArticulationPoint) {
  visited[v] = true;
  tin[v] = low[v] = timer++;
  int children = 0;

  for (auto [u, _] : adjList[v]) {
    if (u == parent) continue;

    if (!visited[u]) {
      children++;
      DfsArticulation(u, v, tin, low, visited, timer, isArticulationPoint);
      low[v] = std::min(low[v], low[u]);

      // Условие для точки сочленения
      if (parent != -1 && low[u] >= tin[v]) {
        isArticulationPoint[v] = true;
      }
    } else {
      low[v] = std::min(low[v], tin[u]);
    }
  }

  // Отдельное условие для корня
  if (parent == -1 && children > 1) {
    isArticulationPoint[v] = true;
  }
}
