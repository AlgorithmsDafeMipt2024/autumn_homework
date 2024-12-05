#include "graph.hpp"

#include <iostream>
#include <stdexcept>

#define UNREACHABLE -1

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

void Graph::addEdge(int u, int v, int weight) {
  if (u < 1 || u > vertexes_num || v < 1 || v > vertexes_num) {
    throw std::out_of_range("Vertex out of bounds in addEdge.");
  }

  adjList[u - 1].emplace_back(v - 1, weight);
  if (!is_directed) adjList[v - 1].emplace_back(u - 1, weight);

  edges_num++;
}

int Graph::getVertexesNum() {
  if (vertexes_num <= 0)
    throw std::runtime_error("Graph is not properly initialized.");
  return vertexes_num;
}

int Graph::getEdgesNum() { return edges_num; }

void Graph::printGraph() const {
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

std::vector<std::pair<int, int>> Graph::getNeighbours(int v) {
  if (v < 0 || v >= vertexes_num) {
    throw std::out_of_range("Vertex index out of bounds in getNeighbours.");
  }
  return adjList[v];
}

void Graph::top_sort(int v, int from, std::vector<bool>& visited,
                     std::vector<int>& way) {
  if (visited[v]) return;
  visited[v] = true;
  way.push_back(v);

  for (auto [u, w] : getNeighbours(v)) {
    if (!visited[u]) {
      top_sort(u, v, visited, way);
    }
  }
}

std::vector<int> Graph::topological_sort(int start) {
  if (vertexes_num == 0) {
    std::cerr << "Error: Graph is empty, topological sort cannot be performed."
              << std::endl;
    return {};
  }

  std::vector<int> way;
  std::vector<bool> visited(getVertexesNum(), false);

  top_sort(start, UNREACHABLE, visited, way);

  if (way.size() < vertexes_num)
    throw std::invalid_argument("Graph is disconnected.");

  return way;
}