#pragma once

#include <limits>

#include "graph.hpp"

/// @brief Basic weighted graph
/// @tparam VertexType
/// @tparam T
template <typename VertexType, typename T>
class WeightedGraph : public Graph<VertexType, T> {
 public:
  WeightedGraph() : Graph<VertexType, T>() {
    weights.resize(Graph<VertexType, T>::vertices_.size(),
                   std::vector<int>(Graph<VertexType, T>::vertices_.size(),
                                    std::numeric_limits<int>::max()));
  }

  /**
   * @brief
   * Override AddVertex to handle weights matrix resizing
   * @param data
   */
  void AddVertex(const T& data) override {
    Graph<VertexType, T>::AddVertex(data);
    weights.resize(Graph<VertexType, T>::vertices_.size(),
                   std::vector<int>(Graph<VertexType, T>::vertices_.size(),
                                    std::numeric_limits<int>::max()));
    for (auto& row : weights)
      row.resize(Graph<VertexType, T>::vertices_.size(),
                 std::numeric_limits<int>::max());
  }

  /**
   * @brief
   * Override RemoveVertex via index to handle weights matrix resizing
   * @param vertex_id
   */
  void RemoveVertex(size_t vertex_id) override {
    // Remove the vertex from the base class
    Graph<VertexType, T>::RemoveVertex(vertex_id);

    // Remove the corresponding row and column from the weights matrix
    weights.erase(weights.begin() + vertex_id);  // Remove the row

    for (auto& row : weights)
      row.erase(row.begin() + vertex_id);  // Remove the column
  }

  /**
   * @brief
   * Add a weighted directed edge
   * @param source_id
   * @param target_id
   * @param weight
   */
  void AddDirEdge(size_t source_id, size_t target_id, int weight) {
    Graph<VertexType, T>::AddDirEdge(source_id, target_id);
    weights[source_id][target_id] = weight;
  }

  /**
   * @brief
   * Add a weighted undirected edge
   * @param source_id
   * @param target_id
   * @param weight
   */
  void AddEdge(size_t source_id, size_t target_id, int weight) {
    AddDirEdge(source_id, target_id, weight);
    AddDirEdge(target_id, source_id, weight);
  }

  /**
   * @brief
   * Remove a weighted directed edge
   * @param source_id
   * @param target_id
   */
  void RemoveDirEdge(size_t source_id, size_t target_id) override {
    Graph<VertexType, T>::RemoveDirEdge(source_id, target_id);
    weights[source_id][target_id] = std::numeric_limits<int>::max();
  }

  /**
   * @brief
   * Remove a weighted undirected edge
   * @param source_id
   * @param target_id
   */
  void RemoveEdge(size_t source_id, size_t target_id) override {
    RemoveDirEdge(source_id, target_id);
    RemoveDirEdge(target_id, source_id);
  }

  /**
   * @brief
   * Get the weight of an edge
   * @param source_id
   * @param target_id
   * @return int
   */
  int GetWeight(size_t source_id, size_t target_id) const {
    return weights[source_id][target_id];
  }

  /**
   * @brief
   * Print the weighted graph
   */
  void PrintGraph() const override {
    for (size_t i = 0; i < Graph<VertexType, T>::vertices_.size(); ++i) {
      std::cout << Graph<VertexType, T>::vertices_[i]->data << " -> ";
      for (const auto& neighbor :
           Graph<VertexType, T>::vertices_[i]->adjacent) {
        size_t j = Graph<VertexType, T>::Find(neighbor->data);
        std::cout << "(" << neighbor->data << ", " << weights[i][j] << ") ";
      }
      std::cout << std::endl;
    }
  }

 private:
  std::vector<std::vector<int>> weights;
};