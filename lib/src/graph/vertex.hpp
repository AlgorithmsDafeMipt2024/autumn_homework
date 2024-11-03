#include <iostream>
#include <vector>

template <typename T>
class Vertex {
 public:
  Vertex(T vertex_id, std::vector<T> adj_vertices)
      : vertex_id(vertex_id), adjacent_vertices(adj_vertices) {}

  Vertex(T vertex_id, std::initializer_list<T> adj_vertices)
      : vertex_id(vertex_id) {
    for (T adj_vertex_id : adj_vertices)
      adjacent_vertices.push_back(adj_vertex_id);
  }

  void AddAdjacentVertex(T adj_vertex) {
    adjacent_vertices.push_back(adj_vertex);
  }

  T GetVertexId() const { return vertex_id; }

  std::vector<T> GetAdjacentVertices() const { return adjacent_vertices; }

  void PrintAdjacentVertices() const {
    std::cout << "Adjacent vertices for " << vertex_id << ": { ";
    for (T vertex : adjacent_vertices) std::cout << vertex << ", ";
    std::cout << "}\n";
  }

 private:
  T vertex_id;
  std::vector<T> adjacent_vertices;
};