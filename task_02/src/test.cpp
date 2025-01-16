#include <gtest/gtest.h>
#include <includes.h>

#include "SearchWeakVE.h"

TEST(TopologicalSort, Simple) {
  NonOrientedGraph graph;
  graph.AddEdge(0, 1);
  graph.AddEdge(0, 2);
  graph.AddEdge(1, 2);
  graph.AddEdge(2, 3);
  graph.AddEdge(3, 4);
  graph.AddEdge(0, 1);
  graph.AddEdge(1, 2);
  graph.AddEdge(0, 2);
  graph.AddEdge(2, 3);
  graph.AddEdge(3, 4);
  graph.AddEdge(3, 5);
  graph.AddEdge(4, 5);
  WeakVE result = SearchWeakVE(graph);
  WeakVE true_result = WeakVE({{3, 2, 0}, {{2, 3}}});
  ASSERT_EQ(result.first, true_result.first);
  ASSERT_EQ(result.second, true_result.second);
}
