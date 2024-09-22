#include "graph.hpp"

#include <iostream>

template <typename T>
void Graph<T>::AddVertex(const T &data) {
  vertices.push_back(std::make_shared<Vertex<T>>(data));
}

template <typename T>
void Graph<T>::DeleteVertex(std::shared_ptr<Vertex<T>> vertex) {
  // Find the vertex in the graph
  auto it = std::find(vertices.begin(), vertices.end(), vertex);
  if (it == vertices.end()) {
    // Vertex not found
    return;
  }

  // Remove the vertex from the graph
  vertices.erase(it);

  // Remove edges pointing to the vertex
  for (auto &v : vertices) {
    v->adjacent.erase(
        std::remove(v->adjacent.begin(), v->adjacent.end(), vertex),
        v->adjacent.end());
  }
}

template <typename T>
void Graph<T>::AddDirEdge(std::shared_ptr<Vertex<T>> source,
                          std::shared_ptr<Vertex<T>> target) {
  source->adjacent.push_back(target);
}

template <typename T>
void Graph<T>::DeleteDirEdge(std::shared_ptr<Vertex<T>> source,
                             std::shared_ptr<Vertex<T>> target) {
  source->adjacent.erase(
      std::remove(source->adjacent.begin(), source->adjacent.end(), target),
      source->adjacent.end());
}

template <typename T>
void Graph<T>::AddEdge(std::shared_ptr<Vertex<T>> vertex_1,
                       std::shared_ptr<Vertex<T>> vertex_2) {
  AddDirEdge(vertex_1, vertex_2);
  AddDirEdge(vertex_2, vertex_1);
}

template <typename T>
void Graph<T>::DeleteEdge(std::shared_ptr<Vertex<T>> vertex_1,
                          std::shared_ptr<Vertex<T>> vertex_2) {
  DeleteDirEdge(vertex_1, vertex_2);
  DeleteDirEdge(vertex_2, vertex_1);
}

template <typename T>
void Graph<T>::PrintGraph() const {
  for (const auto &vertex : vertices) {
    std::cout << vertex->data << " -> ";
    for (const auto &neighbor : vertex->adjacent) {
      std::cout << neighbor->data << " ";
    }
    std::cout << std::endl;
  }
}