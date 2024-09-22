#pragma once

#include <algorithm>
#include <iostream>
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
  void AddVertex(const T &data) {
    vertices_.push_back(std::make_shared<Vertex<T>>(data));
  };

  std::shared_ptr<Vertex<T>> operator[](size_t index) {
    return vertices_[index];
  }
  const std::shared_ptr<Vertex<T>> operator[](size_t index) const {
    return vertices_[index];
  }

  /**
   * @brief
   * Remove a vertex from the graph
   * @param vertex
   */
  void RemoveVertex(std::shared_ptr<Vertex<T>> vertex) {
    // Find the vertex in the graph
    auto it = std::find(vertices_.begin(), vertices_.end(), vertex);
    if (it == vertices_.end()) {
      // Vertex not found
      return;
    }

    // Remove edges pointing to the vertex
    for (auto &v : vertices_[it - vertices_.begin()]->adjacent) {
      RemoveEdge(v, vertices_[it - vertices_.begin()]);
    }
    // Remove the vertex from the graph
    vertices_.erase(it);
  }

  /**
   * @brief
   * Returns the number of vertices in the graph
   * @return size_t
   */
  size_t Size() { return vertices_.size(); }

  /**
   * @brief
   * Add a directed edge between two vertices
   * @param source
   * @param target
   */
  void AddDirEdge(std::shared_ptr<Vertex<T>> source,
                  std::shared_ptr<Vertex<T>> target) {
    source->adjacent.insert(target);
  }

  /**
   * @brief
   * Remove a directed edge between two vertices
   * @param source
   * @param target
   */
  void RemoveDirEdge(std::shared_ptr<Vertex<T>> source,
                     std::shared_ptr<Vertex<T>> target) {
    // std::find(source->adjacent.begin(), source->adjacent.end(), target);
    source->adjacent.erase(
        *std::find(source->adjacent.begin(), source->adjacent.end(), target));
  }

  /**
   * @brief
   * Add a non-directed edge between two vertices
   * @param source
   * @param target
   */
  void AddEdge(std::shared_ptr<Vertex<T>> vertex_1,
               std::shared_ptr<Vertex<T>> vertex_2) {
    AddDirEdge(vertex_1, vertex_2);
    AddDirEdge(vertex_2, vertex_1);
  }

  /**
   * @brief
   * Remove a non-directed edge between two vertices
   * @param source
   * @param target
   */
  void RemoveEdge(std::shared_ptr<Vertex<T>> vertex_1,
                  std::shared_ptr<Vertex<T>> vertex_2) {
    RemoveDirEdge(vertex_1, vertex_2);
    RemoveDirEdge(vertex_2, vertex_1);
  }

  /**
   * @brief
   * Print the adjacency list of the graph
   */
  void PrintGraph() const {
    for (const auto &vertex : vertices_) {
      std::cout << vertex->data << " -> ";
      for (const auto &neighbor : vertex->adjacent) {
        std::cout << neighbor->data << " ";
      }
      std::cout << std::endl;
    }
  }

 private:
  std::vector<std::shared_ptr<Vertex<T>>> vertices_;
};
