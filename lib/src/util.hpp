#pragma once

#include <list>
#include <memory>
#include <vector>

/// @brief Graphs vertex
/// @tparam T
template <typename T>
struct Vertex {
  T data;
  std::list<std::shared_ptr<Vertex<T>>> adjacent;

  Vertex(const T &d) : data(d) {}
};

/// @brief Basic graph
/// @tparam T
template <typename T>
class Graph {
 public:
  /**
   * @brief
   * Add a new vertex to the graph
   * @param data
   */
  void addVertex(const T &data);

  /**
   * @brief
   * Add an edge between two vertices
   * @param source
   * @param reciever
   */
  void addEdge(std::shared_ptr<Vertex<T>> source,
               std::shared_ptr<Vertex<T>> reciever);

  /**
   * @brief
   * Print the adjacency list of the graph
   */
  void printGraph() const;

 private:
  std::vector<std::shared_ptr<Vertex<T>>> vertices;
};