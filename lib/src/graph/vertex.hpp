#include <iostream>
#include <stdexcept>
#include <vector>

template <typename T>
class Vertex {
 public:
  Vertex(const T& vertex_id, const std::vector<T>& adj_vertices = {})
      : vertex_id(vertex_id), adjacent_vertices(adj_vertices) {}

  void AddAdjacentVertex(const T& adj_vertex) {
    adjacent_vertices.push_back(adj_vertex);
  }

  void DeleteAdjacentVertex(const T& adj_vertex) {
    for (int i = 0; i < adjacent_vertices.size(); i++) {
      if (adjacent_vertices[i] == adj_vertex) {
        adjacent_vertices.erase(adjacent_vertices.begin() + i);
        return;
      }
    }
    throw std::invalid_argument("Adjacent vertex not found!");
  }

  T GetVertexId() const { return vertex_id; }

  std::vector<T> GetAdjacentVertices() const { return adjacent_vertices; }

  void PrintAdjacentVertices() const {
    std::cout << "Adjacent vertices for " << vertex_id << ": {";
    for (int i = 0; i < adjacent_vertices.size(); i++) {
      std::cout << adjacent_vertices[i];
      if (i != adjacent_vertices.size() - 1) std::cout << ", ";
    }
    std::cout << "}\n";
  }

  bool ContainsAdjacentVertex(const T& adj_vert) const {
    for (const T& vertex : adjacent_vertices) {
      if (adj_vert == vertex) return true;
    }
    return false;
  }

 private:
  T vertex_id;
  std::vector<T> adjacent_vertices;
};