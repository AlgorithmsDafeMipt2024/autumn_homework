#pragma once

#include <algorithm>
#include <concepts>
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

template <typename T, typename VT>
concept IsVertex = std::derived_from<T, Vertex<VT>>;

/// @brief Basic graph
/// @tparam VertexType
/// @tparam T
template <typename VertexType, typename T>
  requires IsVertex<VertexType, T>
class Graph {
 public:
  /**
   * @brief
   * Add a new vertex to the graph
   * @param data
   */
  virtual void AddVertex(const T &data) {
    vertices_.push_back(std::make_shared<VertexType>(data));
  };

  std::shared_ptr<VertexType> operator[](size_t index) {
    return vertices_[index];
  }

  const std::shared_ptr<VertexType> operator[](size_t index) const {
    return vertices_[index];
  }

  /**
   * @brief
   * Find vertexes index
   * @param vertex
   * @return size_t
   */
  size_t Find(const T &vertex) const {
    size_t index;
    for (index = 0; index < vertices_.size(); ++index)
      if (vertices_[index]->data == vertex) return index;

    return index;
  }

  /**
   * @brief
   * Remove a vertex from the graph via index
   * @param vertex_id
   */
  virtual void RemoveVertex(size_t vertex_id) {
    if (vertex_id >= Size()) {
      // Vertex not found
      return;
    }

    // Remove edges pointing to the vertex
    for (auto &v : vertices_[vertex_id]->adjacent) {
      RemoveDirEdge(v, vertices_[vertex_id]);
    }

    // Remove the vertex from the graph
    vertices_.erase(vertices_.begin() + vertex_id);
  }

  /**
   * @brief
   * Remove a vertex from the graph
   * @param vertex
   */
  virtual void RemoveVertex(std::shared_ptr<VertexType> vertex) {
    // Find the vertex in the graph
    auto it = std::find(vertices_.begin(), vertices_.end(), vertex);
    if (it == vertices_.end()) {
      // Vertex not found
      return;
    }

    RemoveVertex(it - vertices_.begin());
  }

  /**
   * @brief
   * Returns the number of vertices in the graph
   * @return size_t
   */
  size_t Size() const { return vertices_.size(); }

  /**
   * @brief
   * Add a directed edge between two vertices via indices
   * @param source_id
   * @param target_id
   */
  virtual void AddDirEdge(size_t source_id, size_t target_id) {
    operator[](source_id)->adjacent.insert(operator[](target_id));
  }

  /**
   * @brief
   * Add a directed edge between two vertices
   * @param source
   * @param target
   */
  virtual void AddDirEdge(std::shared_ptr<VertexType> source,
                          std::shared_ptr<VertexType> target) {
    source->adjacent.insert(target);
  }

  /**
   * @brief
   * Remove a directed edge between two vertices via indices
   * @param source_id
   * @param target_id
   */
  virtual void RemoveDirEdge(size_t source_id, size_t target_id) {
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
  virtual void RemoveDirEdge(std::shared_ptr<VertexType> source,
                             std::shared_ptr<VertexType> target) {
    source->adjacent.erase(
        *std::find(source->adjacent.begin(), source->adjacent.end(), target));
  }

  /**
   * @brief
   * Add a non-directed edge between two vertices via indices
   * @param first_id
   * @param second_id
   */
  virtual void AddEdge(size_t first_id, size_t second_id) {
    AddDirEdge(first_id, second_id);
    AddDirEdge(second_id, first_id);
  }

  /**
   * @brief
   * Add a non-directed edge between two vertices
   * @param vertex_1
   * @param vertex_2
   */
  virtual void AddEdge(std::shared_ptr<VertexType> vertex_1,
                       std::shared_ptr<VertexType> vertex_2) {
    AddDirEdge(vertex_1, vertex_2);
    AddDirEdge(vertex_2, vertex_1);
  }

  /**
   * @brief
   * Remove a non-directed edge between two vertices via indices
   * @param first_id
   * @param second_id
   */
  virtual void RemoveEdge(size_t first_id, size_t second_id) {
    RemoveDirEdge(first_id, second_id);
    RemoveDirEdge(second_id, first_id);
  }

  /**
   * @brief
   * Remove a non-directed edge between two vertices
   * @param vertex_1
   * @param vertex_2
   */
  virtual void RemoveEdge(std::shared_ptr<VertexType> vertex_1,
                          std::shared_ptr<VertexType> vertex_2) {
    RemoveDirEdge(vertex_1, vertex_2);
    RemoveDirEdge(vertex_2, vertex_1);
  }

  /**
   * @brief
   * Print the adjacency list of the graph
   */
  virtual void PrintGraph() const {
    for (const auto &vertex : vertices_) {
      std::cout << vertex->data << " -> ";
      for (const auto &neighbor : vertex->adjacent) {
        std::cout << neighbor->data << " ";
      }
      std::cout << std::endl;
    }
  }

 protected:
  std::vector<std::shared_ptr<VertexType>> vertices_;
};
