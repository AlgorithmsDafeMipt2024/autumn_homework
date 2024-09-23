#include "../../graph.hpp"

template class Graph<size_t, long>;

template <typename vert_t, typename weight_t>
Graph<vert_t, weight_t> Graph<vert_t, weight_t>::GraphFromAdjMatrix(
    const std::vector<std::vector<weight_t>>& adj_matrix, bool is_weighted) {
  std::vector<Edge> edges{};

  if (adj_matrix.empty()) return Graph();

  if (adj_matrix.size() != adj_matrix[0].size())
    raise std::invalid_argument(
        "GraphFromAdjMatrix: AdjacencyMatrix is not squared.");

  for (size_t row = 0; row < adj_matrix.size(); row++) {
    if (row != 0)
      if (adj_matrix[row].size() != adj_matrix[row - 1].size())
        raise std::invalid_argument(
            "GraphFromAdjMatrix: AdjacencyMatrix is not squared [row "
            "problem].");

    for (size_t col = 0; col < adj_matrix[row].size(); col++) {
      if (adj_matrix[row][col] == 0) continue;

      if (is_weighted)
        edges.push_back(Edge(col, row, adj_matrix[col][row]));
      else
        edges.push_back(Edge(col, row));
    }
  }

  return Graph(edges);
}

template <typename vert_t, typename weight_t>
Graph<vert_t, weight_t> Graph<vert_t, weight_t>::GraphFromAdjList(
    const std::vector<std::vector<vert_t>>& adj_list) {
  if (adj_list.empty()) return Graph();

  std::vector<Edge> edges{};

  for (size_t row = 0; row < adj_list.size(); row++)
    for (size_t col = 0; col < adj_list[row].size(); col++)
      edges.push_back(Edge(row, adj_list[row][col]));

  return Graph(edges);
}

template <typename vert_t, typename weight_t>
Graph<vert_t, weight_t> Graph<vert_t, weight_t>::GraphFromMap(
    const std::unordered_map<std::string, weight_t>& edges_dict) {
  if (edges_dict.empty()) return Graph();

  std::vector<Graph<vert_t, weight_t>::Edge> edges;

  for (const auto& [edge_str, weight] : edges_dict) {
    vert_t start_vert, end_vert;
    std::tie(start_vert, end_vert) = ParseEdgeString(edge_str);

    edges.emplace_back(start_vert, end_vert, weight);
  }

  return Graph(edges);
}

template <typename vert_t, typename weight_t>
Graph<vert_t, weight_t> Graph<vert_t, weight_t>::GraphFromStrs(
    const std::vector<std::string>& edges_strs) {
  if (edges_strs.empty()) return Graph();

  std::vector<Graph<vert_t, weight_t>::Edge> edges;

  for (const auto& edge_str : edges_strs) {
    vert_t start_vert, end_vert;
    std::tie(start_vert, end_vert) = ParseEdgeString(edge_str);

    edges.emplace_back(start_vert, end_vert);
  }

  return Graph(edges);
}

template <typename vert_t, typename weight_t>
Graph<vert_t, weight_t>::Graph(const std::vector<Edge>& edges)
    : edges_{edges}, verts_() {
  if (edges.empty()) return;

  // кол-во вершин = максимальная вершина среди ребер
  vert_t max_vert = 0;
  for (const auto& edge : edges_) {
    max_vert = std::max(max_vert, edge.StartVert());
    max_vert = std::max(max_vert, edge.EndVert());
  }

  verts_.resize(max_vert + 1);
  std::iota(verts_.begin(), verts_.end(), 0);

  if (!IsDirected()) MakeUndirected();
}