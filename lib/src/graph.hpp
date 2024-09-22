#pragma once

#include <memory>
#include <set>
#include <vector>

/// @brief Graphs vertex
/// @tparam T
template <typename T>
struct Vertex {
  Vertex(const T &d) : data(d) {}

  T data;
  std::set<std::shared_ptr<Vertex<T>>> adjacent;
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
   * Delete a vertex from the graph
   * @param vertex
   */
  void DeleteVertex(std::shared_ptr<Vertex<T>> vertex);

  /**
   * @brief
   * Add a directed edge between two vertices
   * @param source
   * @param target
   */
  void AddDirEdge(std::shared_ptr<Vertex<T>> source,
                  std::shared_ptr<Vertex<T>> target);

  /**
   * @brief
   * Delete a directed edge between two vertices
   * @param source
   * @param target
   */
  void DeleteDirEdge(std::shared_ptr<Vertex<T>> source,
                     std::shared_ptr<Vertex<T>> target);
  /**
   * @brief
   * Add a non-directed edge between two vertices
   * @param source
   * @param target
   */
  void AddEdge(std::shared_ptr<Vertex<T>> vertex_1,
               std::shared_ptr<Vertex<T>> vertex_2);

  /**
   * @brief
   * Delete a non-directed edge between two vertices
   * @param source
   * @param target
   */
  void DeleteEdge(std::shared_ptr<Vertex<T>> vertex_1,
                  std::shared_ptr<Vertex<T>> vertex_2);

  /**
   * @brief
   * Print the adjacency list of the graph
   */
  void PrintGraph() const;

 private:
  std::vector<std::shared_ptr<Vertex<T>>> vertices;
};