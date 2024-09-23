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
   * Find vertexes index
   * @param vertex
   * @return size_t
   */
  size_t Find(const std::shared_ptr<Vertex<T>> &vertex) {
    return std::find(vertices_.begin(), vertices_.end(), vertex) -
           vertices_.begin();
  };

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
   * Add a directed edge between two vertices via indices
   * @param source_id
   * @param target_id
   */
  void AddDirEdge(size_t source_id, size_t target_id) {
    operator[](source_id)->adjacent.insert(operator[](target_id));
  }

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
   * Remove a directed edge between two vertices via indices
   * @param source_id
   * @param target_id
   */
  void RemoveDirEdge(size_t source_id, size_t target_id) {
    operator[](source_id)->adjacent.erase(*std::find(
        operator[](source_id)->adjacent.begin(),
        operator[](source_id)->adjacent.end(), operator[](target_id)));
  }

  /**
   * @brief
   * Remove a directed edge between two vertices
   * @param source
   * @param target
   */
  void RemoveDirEdge(std::shared_ptr<Vertex<T>> source,
                     std::shared_ptr<Vertex<T>> target) {
    source->adjacent.erase(
        *std::find(source->adjacent.begin(), source->adjacent.end(), target));
  }

  /**
   * @brief
   * Add a non-directed edge between two vertices via indices
   * @param first_id
   * @param second_id
   */
  void AddEdge(size_t first_id, std::shared_ptr<Vertex<T>> second_id) {
    AddDirEdge(first_id, second_id);
    AddDirEdge(second_id, first_id);
  }

  /**
   * @brief
   * Add a non-directed edge between two vertices
   * @param vertex_1
   * @param vertex_2
   */
  void AddEdge(std::shared_ptr<Vertex<T>> vertex_1,
               std::shared_ptr<Vertex<T>> vertex_2) {
    AddDirEdge(vertex_1, vertex_2);
    AddDirEdge(vertex_2, vertex_1);
  }

  /**
   * @brief
   * Remove a non-directed edge between two vertices via indices
   * @param first_id
   * @param second_id
   */
  void RemoveEdge(size_t first_id, size_t second_id) {
    RemoveDirEdge(first_id, second_id);
    RemoveDirEdge(second_id, first_id);
  }

  /**
   * @brief
   * Remove a non-directed edge between two vertices
   * @param vertex_1
   * @param vertex_2
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
