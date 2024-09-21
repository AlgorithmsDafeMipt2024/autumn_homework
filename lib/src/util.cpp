#include "util.hpp"

#include <iostream>

template <typename T>
void Graph<T>::AddVertex(const T &data) {
  vertices.push_back(std::make_shared<Vertex<T>>(data));
}

template <typename T>
void Graph<T>::AddDirEdge(std::shared_ptr<Vertex<T>> source,
                          std::shared_ptr<Vertex<T>> reciever) {
  source->adjacent.push_back(reciever);
}

template <typename T>
void Graph<T>::AddEdge(std::shared_ptr<Vertex<T>> vertex_1,
                       std::shared_ptr<Vertex<T>> vertex_2) {
  Graph<T>::AddDirEdge(vertex_1, vertex_2);
  Graph<T>::AddDirEdge(vertex_2, vertex_1);
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