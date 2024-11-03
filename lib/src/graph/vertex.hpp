#include <iostream>
#include <vector>

class Vertex {
 public:
  Vertex(size_t vertex_id, std::vector<size_t> adj_vertices)
      : vertex_id(vertex_id), adjacent_vertices(adj_vertices) {}

  Vertex(size_t vertex_id, std::initializer_list<size_t> adj_vertices)
      : vertex_id(vertex_id) {
    for (size_t adj_vertex_id : adj_vertices)
      adjacent_vertices.push_back(adj_vertex_id);
  }

  void AddAdjacentVertex(size_t adj_vertex) {
    adjacent_vertices.push_back(adj_vertex);
  }

  size_t GetVertexId() const { return vertex_id; }

  std::vector<size_t> GetAdjacentVertices() const { return adjacent_vertices; }

  void PrintAdjacentVertices() const {
    std::cout << "Adjacent vertices for " << vertex_id << " vertex: { ";
    for (size_t vertex : adjacent_vertices) std::cout << vertex << ", ";
    std::cout << "}\n";
  }

 private:
  size_t vertex_id;
  std::vector<size_t> adjacent_vertices;
};