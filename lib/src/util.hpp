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
  void AddVertex(const T &data);

  /**
   * @brief
   * Add a directed edge between two vertices
   * @param source
   * @param reciever
   */
  void AddDirEdge(std::shared_ptr<Vertex<T>> source,
                  std::shared_ptr<Vertex<T>> reciever);

  /**
   * @brief
   * Add a non-directed edge between two vertices
   * @param source
   * @param reciever
   */
  void AddEdge(std::shared_ptr<Vertex<T>> vertex_1,
               std::shared_ptr<Vertex<T>> vertex_2);

  /**
   * @brief
   * Print the adjacency list of the graph
   */
  void PrintGraph() const;

 private:
  std::vector<std::shared_ptr<Vertex<T>>> vertices;
};