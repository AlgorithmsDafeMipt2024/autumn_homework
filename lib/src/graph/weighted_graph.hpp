#pragma once
#include <limits>

#include "graph.hpp"

template <typename T>
struct WeightedEdge {
 public:
  WeightedEdge(const T& start_vertex, const T& end_vertex, int weight)
      : start_vertex(start_vertex), end_vertex(end_vertex), weight(weight) {}

  T start_vertex;
  T end_vertex;
  int weight;
};

template <typename T>
class WeightedGraph {
 public:
  WeightedGraph() = default;

  WeightedGraph(const std::vector<std::pair<std::pair<T, T>, int>>& w_edges) {
    for (auto w_edge : w_edges) {
      auto edge = w_edge.first;
      graph.AddEdge(edge.first, edge.second);
      weighted_edges.push_back(
          WeightedEdge<T>(edge.first, edge.second, w_edge.second));
    }
  }

  WeightedGraph(const std::vector<std::pair<T, T>>& edges,
                const std::vector<int> weights) {
    if (edges.size() != weights.size())
      throw std::invalid_argument(
          "The number of weighted edges is greater than the number of all "
          "edges in the graph!");
    for (int i = 0; i < edges.size(); i++) {
      graph.AddEdge(edges[i].first, edges[i].second);
      weighted_edges.push_back(
          WeightedEdge<T>(edges[i].first, edges[i].second, weights[i]));
    }
  }

  void PrintAdjList() {
    for (Vertex<T> vertex : graph.GetVertices()) {
      std::cout << "Adjacent vertices for '" << vertex.GetVertexId() << "': {";
      auto adj_verts = vertex.GetAdjVertices();
      for (int i = 0; i < adj_verts.size(); i++) {
        std::cout << "('" << adj_verts[i] << "', "
                  << GetEdgeWeight(vertex.GetVertexId(), adj_verts[i]) << ")";
        if (i != adj_verts.size() - 1) std::cout << ", ";
      }
      std::cout << "}\n";
    }
  }

  std::vector<WeightedEdge<T>> GetWeightedEdges() const {
    return weighted_edges;
  }

  std::vector<Vertex<T>> GetVertices() const { return graph.GetVertices(); }

  size_t GetVerticesCount() const { return graph.GetVerticesCount(); }

  size_t GetEdgesCount() const { return graph.GetEdgesCount(); }

  int GetEdgeWeight(const T& start, const T& end) const {
    for (WeightedEdge<T> w_edge : weighted_edges) {
      if (w_edge.start_vertex == start && w_edge.end_vertex == end)
        return w_edge.weight;
    }
    throw std::invalid_argument("Edge not found!");
  }

  bool ContainsVertex(const T& vertex) const {
    return graph.ContainsVertex(vertex);
  }

  bool ContainsEdge(const T& start, const T& end) const {
    return graph.ContainsEdge(start, end);
  }

  void AddVertex(const T& vertex) { graph.AddVertex(vertex); }

  void AddWeightedEdge(const T& start, const T& end, int weight = 0) {
    graph.AddEdge(start, end);
    weighted_edges.push_back(WeightedEdge<T>(start, end, weight));
  }

  void DeleteVertex(const T& vertex) {
    graph.DeleteVertex(vertex);

    int end = weighted_edges.size();
    for (int i = 0; i < end; i++) {
      WeightedEdge<T> w_edge = weighted_edges[i];
      if (!graph.ContainsEdge(w_edge.start_vertex, w_edge.end_vertex)) {
        weighted_edges.erase(weighted_edges.begin() + i);
        i--;
        end--;
      }
    }
  }

  void DeleteWeightedEdge(const T& start, const T& end) {
    graph.DeleteEdge(start, end);
  }

  void SetEdgeWeight(const T& start, const T& end, int w) {
    if (!graph.ContainsEdge(start, end))
      throw std::invalid_argument("Edge not found!");

    for (int i = 0; i < weighted_edges.size(); i++) {
      if (weighted_edges[i].start_vertex == start &&
          weighted_edges[i].end_vertex == end) {
        weighted_edges[i].weight = w;
        return;
      }
    }
  }

 private:
  Graph<T> graph;
  std::vector<WeightedEdge<T>> weighted_edges;
};