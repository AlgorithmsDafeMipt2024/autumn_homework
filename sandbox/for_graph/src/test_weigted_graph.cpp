#include <gtest/gtest.h>

#include "graph/weighted_graph.hpp"

TEST(Test_WeightedGraph, Test_Constructors) {
  WeightedGraph<char> wg1({{{'A', 'B'}, 2},
                           {{'A', 'C'}, 5},
                           {{'B', 'D'}, 3},
                           {{'C', 'D'}, 7},
                           {{'D', 'A'}, 1}});

  WeightedGraph<char> wg2(
      {{'A', 'B'}, {'A', 'C'}, {'B', 'D'}, {'C', 'D'}, {'D', 'A'}},
      {2, 5, 3, 7, 1});

  ASSERT_EQ(wg1.GetVerticesCount(), wg2.GetVerticesCount());
  ASSERT_EQ(wg1.GetEdgesCount(), wg2.GetEdgesCount());

  auto edges = wg1.GetWeightedEdges();

  for (auto edge : edges) {
    ASSERT_TRUE(wg2.ContainsEdge(edge.start_vertex, edge.end_vertex));
  }
}

TEST(Test_WeightedGraph, Test_AddWeightedEdge) {
  WeightedGraph<char> wg;

  wg.AddWeightedEdge('A', 'B', 3);
  wg.AddWeightedEdge('A', 'C', 5);
  wg.AddWeightedEdge('A', 'D', 2);
  wg.AddWeightedEdge('B', 'C', 1);
  wg.AddWeightedEdge('B', 'E', 4);
  wg.AddWeightedEdge('C', 'E', 3);
  wg.AddWeightedEdge('D', 'E', 6);

  ASSERT_TRUE(wg.ContainsEdge('A', 'B'));
  ASSERT_TRUE(wg.ContainsEdge('A', 'C'));
  ASSERT_TRUE(wg.ContainsEdge('A', 'D'));
  ASSERT_TRUE(wg.ContainsEdge('B', 'C'));
  ASSERT_TRUE(wg.ContainsEdge('B', 'E'));
  ASSERT_TRUE(wg.ContainsEdge('C', 'E'));
  ASSERT_TRUE(wg.ContainsEdge('D', 'E'));

  ASSERT_EQ(wg.GetEdgeWeight('A', 'B'), 3);
  ASSERT_EQ(wg.GetEdgeWeight('A', 'C'), 5);
  ASSERT_EQ(wg.GetEdgeWeight('A', 'D'), 2);
  ASSERT_EQ(wg.GetEdgeWeight('B', 'C'), 1);
  ASSERT_EQ(wg.GetEdgeWeight('B', 'E'), 4);
  ASSERT_EQ(wg.GetEdgeWeight('C', 'E'), 3);
  ASSERT_EQ(wg.GetEdgeWeight('D', 'E'), 6);
}