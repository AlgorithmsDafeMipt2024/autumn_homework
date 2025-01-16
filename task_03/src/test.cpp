#include <gtest/gtest.h>
#include <includes.h>

#include "JonsonAlgorithm.h"

bool operator==(const OrientedWeightedGraphWithZeroWeight& first,
                const OrientedWeightedGraphWithZeroWeight& second) {
  if (first.GetVerts() != second.GetVerts()) return false;
  for (int i = 0; i < first.GetVerts(); ++i)
    for (int j = 0; j < first.GetVerts(); ++j)
      if (first[i][j] != second[i][j] ||
          first.GetWeight(i, j) != second.GetWeight(i, j))
        return false;
  return true;
}

TEST(TopologicalSort, Simple) {
  WeightedOrientedGraph test_graph;
  test_graph.AddEdge(0, 1, 2);
  test_graph.AddEdge(0, 2, 3);
  test_graph.AddEdge(1, 0, -1);
  test_graph.AddEdge(1, 2, 4);
  test_graph.AddEdge(2, 0, -2);
  test_graph.AddEdge(2, 1, 1);
  auto jons_graph = JonsonAlgorithm(test_graph);

  OrientedWeightedGraphWithZeroWeight true_jons_graph;
  true_jons_graph.AddEdge(0, 1, 2);
  true_jons_graph.AddEdge(0, 2, 3);
  true_jons_graph.AddEdge(1, 0, -1);
  true_jons_graph.AddEdge(1, 2, 2);
  true_jons_graph.AddEdge(2, 0, -2);
  true_jons_graph.AddEdge(2, 1, 0);

  ASSERT_EQ(jons_graph, true_jons_graph);
}
