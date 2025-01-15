#pragma once

#include <algorithm>

#include "RMQ.hpp"
#include "graph/graph.hpp"

template <typename T>
class LCA {
 public:
  LCA(T root, Graph<T> graph) : graph(graph) {
    // Проверка свойства дерева
    if (graph.GetVerticesCount() - 1 != graph.GetEdgesCount())
      throw std::invalid_argument("Graph is not tree!");

    std::map<T, int> vertices_depths;
    for (T v : graph.GetVerticesIds()) first_meet[v] = INF;
    std::vector<T> visited;

    EulerianCycle(vertices_depths, visited, 0, root);

    std::vector<int> rmq_data;
    for (T v : cycle) rmq_data.push_back(vertices_depths[v]);
    tree = SegmentMinTree(rmq_data);

    seg_graph_tree.resize(pow(2, ceil(log2(tree.Size()) + 1)));

    for (int i = 0; i < cycle.size(); i++)
      seg_graph_tree[i + seg_graph_tree.size() / 2] = cycle[i];

    for (int i = seg_graph_tree.size() - 1; i > 0; i -= 2) {
      int right_depth = graph.ContainsVertex(seg_graph_tree[i])
                            ? vertices_depths[seg_graph_tree[i]]
                            : INF;
      int left_depth = graph.ContainsVertex(seg_graph_tree[i - 1])
                           ? vertices_depths[seg_graph_tree[i - 1]]
                           : INF;
      if (right_depth < left_depth)
        seg_graph_tree[i / 2] = seg_graph_tree[i];
      else
        seg_graph_tree[i / 2] = seg_graph_tree[i - 1];
    }
  }

  T operator()(const T& vert_1, const T& vert_2) {
    if (!graph.ContainsVertex(vert_1) || !graph.ContainsVertex(vert_2))
      throw std::invalid_argument("Node not found!");

    size_t pos_1 = first_meet[vert_1];
    size_t pos_2 = first_meet[vert_2];

    size_t min_pos =
        tree.FindSegmentMinPos(std::min(pos_1, pos_2), std::max(pos_1, pos_2));

    return seg_graph_tree[min_pos];
  }

 private:
  Graph<T> graph;
  SegmentMinTree tree;
  std::vector<T> cycle;
  // Дерево отрезков с использованием вершин
  std::vector<T> seg_graph_tree;
  // Здесь находятся позиции первой встречи вершин в Эйлеровом цикле
  std::map<T, size_t> first_meet;

  void EulerianCycle(std::map<T, int>& vertices_depths, std::vector<T>& visited,
                     int curr_depth, T curr_vertex) {
    visited.push_back(curr_vertex);
    vertices_depths[curr_vertex] = curr_depth;
    cycle.push_back(curr_vertex);
    if (cycle.size() - 1 < first_meet[curr_vertex])
      first_meet[curr_vertex] = cycle.size() - 1;

    T parent = curr_vertex;
    if (cycle.size() > 1) parent = cycle[cycle.size() - 2];

    for (T child : graph.GetAdjVertices(curr_vertex)) {
      if (parent != child)
        EulerianCycle(vertices_depths, visited,
                      vertices_depths[curr_vertex] + 1, child);
    }

    if (parent == curr_vertex) {
      if (visited.size() != graph.GetVerticesCount())
        // Проверка на связности
        throw std::invalid_argument("Graph is not tree!");
      return;
    } else
      cycle.push_back(parent);
  }
};