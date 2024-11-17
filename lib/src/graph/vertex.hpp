#pragma once
#include <iostream>
#include <stdexcept>
#include <vector>

template <typename T>
class Vertex {
 public:
  Vertex(const T& vertex_id, const std::vector<T>& adj_vertices = {})
      : vertex_id(vertex_id), adjacent_vertices(adj_vertices) {}

  void AddAdjVertex(const T& adj_vertex) {
    if (ContainsAdjVertex(adj_vertex)) return;
    adjacent_vertices.push_back(adj_vertex);
  }

  void DeleteAdjVertex(const T& adj_vertex) {
    for (int i = 0; i < adjacent_vertices.size(); i++) {
      if (adjacent_vertices[i] == adj_vertex) {
        adjacent_vertices.erase(adjacent_vertices.begin() + i);
        return;
      }
    }
    throw std::invalid_argument("Adjacent vertex not found!");
  }

  T GetVertexId() const { return vertex_id; }

  std::vector<T> GetAdjVertices() const { return adjacent_vertices; }

  size_t GetAdjVerticesCount() const { return adjacent_vertices.size(); }

  void PrintAdjVertices() const {
    std::cout << "Adjacent vertices for " << vertex_id << ": {";
    for (int i = 0; i < adjacent_vertices.size(); i++) {
      std::cout << adjacent_vertices[i];
      if (i != adjacent_vertices.size() - 1) std::cout << ", ";
    }
    std::cout << "}\n";
  }

  bool ContainsAdjVertex(const T& adj_vert) const {
    for (auto vertex : adjacent_vertices) {
      if (adj_vert == vertex) return true;
    }
    return false;
  }

 private:
  T vertex_id;
  std::vector<T> adjacent_vertices;
};