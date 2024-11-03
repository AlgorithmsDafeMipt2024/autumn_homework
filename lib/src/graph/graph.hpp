#include <map>

#include "vertex.hpp"

template <typename T>
class Graph {
 public:
  Graph(const std::vector<Vertex<T>>& vertices) : vertices(vertices) {}

  Graph(const std::vector<std::pair<T, T>>& edges) {
    std::map<T, std::vector<T>> vertices_to_add;

    for (auto edge : edges) {
      vertices_to_add[edge.first].push_back(edge.second);
      vertices_to_add[edge.second].push_back(edge.first);
    }

    for (auto vertex : vertices_to_add) {
      vertices.push_back(Vertex(vertex.first, vertex.second));
    }
  }

  void PrintAdjacencyList() const {
    for (auto vertex : vertices) {
      vertex.PrintAdjacentVertices();
    }
  }

 private:
  std::vector<Vertex<T>> vertices;
};