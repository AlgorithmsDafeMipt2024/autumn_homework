#include <gtest/gtest.h>
#include <includes.h>

#include "DeikstraAlgorithm.h"

bool operator==(const DeikstraReturn& first, const DeikstraReturn& second) {
  if (first.path != second.path || first.pathLength != second.pathLength)
    return false;
  return true;
}

TEST(DeikstraAlgorithmTest, Simple) {
  WeightedNonOrientedGraph graph;
  graph.AddEdge(0, 1, 10);
  graph.AddEdge(0, 2, 2);
  graph.AddEdge(0, 3, 7);
  graph.AddEdge(0, 4, 8);
  graph.AddEdge(1, 3, 1);
  graph.AddEdge(1, 5, 5);
  graph.AddEdge(2, 3, 3);
  graph.AddEdge(2, 4, 5);
  graph.AddEdge(3, 4, 1);
  graph.AddEdge(3, 5, 4);
  graph.AddEdge(4, 5, 2);

  auto deikstra = DeikstraPathAlgorithm(graph, 0, 5);
  DeikstraReturn true_deikstra({0, 2, 3, 4}, 8);
  ASSERT_EQ(deikstra, true_deikstra);
}
