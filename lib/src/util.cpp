#include "util.hpp"

#include <iostream>

template <typename T>
void Graph<T>::addVertex(const T &data) {
  vertices.push_back(std::make_shared<Vertex<T>>(data));
}

template <typename T>
void Graph<T>::addEdge(std::shared_ptr<Vertex<T>> source,
                       std::shared_ptr<Vertex<T>> reciever) {
  source->adjacent.push_back(reciever);
}

template <typename T>
void Graph<T>::printGraph() const {
  for (const auto &vertex : vertices) {
    std::cout << vertex->data << " -> ";
    for (const auto &neighbor : vertex->adjacent) {
      std::cout << neighbor->data << " ";
    }
    std::cout << std::endl;
  }
}