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

  void AddEdge(const T& vert_1, const T& vert_2) {
    if (!ContainsVertex(vert_1) || !ContainsVertex(vert_2))
      throw std::invalid_argument("Vertex not found!");

    for (int i = 0; i < vertices.size(); i++) {
      if (vertices[i].GetVertexId() == vert_1)
        vertices[i].AddAdjacentVertex(vert_2);
      if (vertices[i].GetVertexId() == vert_2)
        vertices[i].AddAdjacentVertex(vert_1);
    }
  }

  void AddVertex(const Vertex<T>& vertex) {
    for (const T& adj_vertex : vertex.GetAdjacentVertices()) {
      if (!ContainsVertex(adj_vertex))
        throw std::invalid_argument("Adjacent vertex not found!");

      for (int i = 0; i < vertices.size(); i++) {
        if (adj_vertex == vertices[i].GetVertexId()) {
          vertices[i].AddAdjacentVertex(vertex.GetVertexId());
          break;
        }
      }
    }
    vertices.push_back(vertex);
  }

  void AddVertex(const T& vertex) { vertices.push_back(Vertex<T>(vertex)); }

  void DeleteVertex(const T& vertex) {
    if (!ContainsVertex(vertex))
      throw std::invalid_argument("Vertex not found!");

    for (int i = 0; i < vertices.size(); i++) {
      if (vertex == vertices[i].GetVertexId()) {
        vertices.erase(vertices.begin() + i);
        return;
      }
    }
  }

  bool ContainsVertex(const Vertex<T>& vertex) const {
    for (const Vertex<T>& vert : vertices) {
      if (vert.GetVertexId() == vertex.GetVertexId()) {
        auto adj_verts = vertex.GetAdjacentVertices();
        for (int i = 0; i < adj_verts.size(); i++) {
          if (!vertex.ContainsAdjacentVertex(adj_verts[i])) return false;
        }
      }
      return true;
    }
    return false;
  }

  bool ContainsVertex(const T& vertex) const {
    for (const Vertex<T>& vert : vertices) {
      if (vert.GetVertexId() == vertex) return true;
    }
    return false;
  }

 private:
  std::vector<Vertex<T>> vertices;
};