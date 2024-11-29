#include "graph/weighted_graph.hpp"

#include <gtest/gtest.h>

TEST(Test_OrientedWeightedGraph, Test_Constructors) {
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

TEST(Test_OrientedWeightedGraph, Test_AddWeightedEdge) {
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

TEST(Test_OrientedWeightedGraph, Test_DeleteVertex) {
  WeightedGraph<char> wg;

  wg.AddWeightedEdge('A', 'B', 3);
  wg.AddWeightedEdge('A', 'C', 5);
  wg.AddWeightedEdge('A', 'D', 2);
  wg.AddWeightedEdge('B', 'C', 1);
  wg.AddWeightedEdge('B', 'E', 4);
  wg.AddWeightedEdge('C', 'E', 3);
  wg.AddWeightedEdge('D', 'E', 6);

  wg.DeleteVertex('A');

  ASSERT_FALSE(wg.ContainsEdge('A', 'B'));
  ASSERT_FALSE(wg.ContainsEdge('A', 'C'));
  ASSERT_FALSE(wg.ContainsEdge('A', 'D'));
}

TEST(Test_OrientedWeightedGraph, Test_DeleteWeightedEdge) {
  WeightedGraph<char> wg;

  wg.AddWeightedEdge('A', 'B', 3);
  wg.AddWeightedEdge('A', 'C', 5);
  wg.AddWeightedEdge('A', 'D', 2);
  wg.AddWeightedEdge('B', 'C', 1);
  wg.AddWeightedEdge('B', 'E', 4);
  wg.AddWeightedEdge('C', 'E', 3);
  wg.AddWeightedEdge('D', 'E', 6);

  wg.DeleteWeightedEdge('A', 'B');

  ASSERT_FALSE(wg.ContainsEdge('A', 'B'));
  ASSERT_TRUE(wg.ContainsEdge('A', 'C'));

  ASSERT_THROW(wg.DeleteWeightedEdge('A', 'B'), std::invalid_argument);
}

TEST(Test_OrientedWeightedGraph, Test_SetEdgeWeight) {
  WeightedGraph<char> wg;

  wg.AddWeightedEdge('A', 'B', 3);
  wg.AddWeightedEdge('A', 'C', 5);
  wg.AddWeightedEdge('A', 'D', 2);
  wg.AddWeightedEdge('B', 'C', 1);
  wg.AddWeightedEdge('B', 'E', 4);
  wg.AddWeightedEdge('C', 'E', 3);
  wg.AddWeightedEdge('D', 'E', 6);

  wg.SetEdgeWeight('A', 'B', 5);

  ASSERT_EQ(wg.GetEdgeWeight('A', 'B'), 5);

  ASSERT_THROW(wg.GetEdgeWeight('B', 'D'), std::invalid_argument);
}

TEST(Test_NotOrientedWeightedGraph, Test_Constructors) {
  WeightedGraph<char> wg1({{{'A', 'B'}, 2},
                           {{'A', 'C'}, 5},
                           {{'B', 'D'}, 3},
                           {{'C', 'D'}, 7},
                           {{'D', 'A'}, 1}},
                          false);

  WeightedGraph<char> wg2(
      {{'A', 'B'}, {'A', 'C'}, {'B', 'D'}, {'C', 'D'}, {'D', 'A'}},
      {2, 5, 3, 7, 1}, false);

  ASSERT_EQ(wg1.GetVerticesCount(), wg2.GetVerticesCount());
  ASSERT_EQ(wg1.GetEdgesCount(), wg2.GetEdgesCount());

  auto edges = wg1.GetWeightedEdges();

  for (auto edge : edges) {
    ASSERT_TRUE(wg2.ContainsEdge(edge.start_vertex, edge.end_vertex));
  }
}

TEST(Test_NotOrientedWeightedGraph, Test_AddWeightedEdge) {
  WeightedGraph<char> wg(false);

  wg.AddWeightedEdge('A', 'B', 3);
  wg.AddWeightedEdge('A', 'C', 5);
  wg.AddWeightedEdge('A', 'D', 2);
  wg.AddWeightedEdge('B', 'C', 1);
  wg.AddWeightedEdge('B', 'E', 4);
  wg.AddWeightedEdge('C', 'E', 3);
  wg.AddWeightedEdge('D', 'E', 6);

  ASSERT_TRUE(wg.ContainsEdge('A', 'B'));
  ASSERT_TRUE(wg.ContainsEdge('B', 'A'));
  ASSERT_TRUE(wg.ContainsEdge('A', 'C'));
  ASSERT_TRUE(wg.ContainsEdge('C', 'A'));
  ASSERT_TRUE(wg.ContainsEdge('A', 'D'));
  ASSERT_TRUE(wg.ContainsEdge('D', 'A'));
  ASSERT_TRUE(wg.ContainsEdge('B', 'C'));
  ASSERT_TRUE(wg.ContainsEdge('C', 'B'));
  ASSERT_TRUE(wg.ContainsEdge('B', 'E'));
  ASSERT_TRUE(wg.ContainsEdge('E', 'B'));
  ASSERT_TRUE(wg.ContainsEdge('C', 'E'));
  ASSERT_TRUE(wg.ContainsEdge('E', 'C'));
  ASSERT_TRUE(wg.ContainsEdge('D', 'E'));
  ASSERT_TRUE(wg.ContainsEdge('E', 'D'));

  ASSERT_EQ(wg.GetEdgeWeight('A', 'B'), 3);
  ASSERT_EQ(wg.GetEdgeWeight('B', 'A'), 3);
  ASSERT_EQ(wg.GetEdgeWeight('A', 'C'), 5);
  ASSERT_EQ(wg.GetEdgeWeight('C', 'A'), 5);
  ASSERT_EQ(wg.GetEdgeWeight('A', 'D'), 2);
  ASSERT_EQ(wg.GetEdgeWeight('D', 'A'), 2);
  ASSERT_EQ(wg.GetEdgeWeight('B', 'C'), 1);
  ASSERT_EQ(wg.GetEdgeWeight('C', 'B'), 1);
  ASSERT_EQ(wg.GetEdgeWeight('B', 'E'), 4);
  ASSERT_EQ(wg.GetEdgeWeight('E', 'B'), 4);
  ASSERT_EQ(wg.GetEdgeWeight('C', 'E'), 3);
  ASSERT_EQ(wg.GetEdgeWeight('E', 'C'), 3);
  ASSERT_EQ(wg.GetEdgeWeight('D', 'E'), 6);
  ASSERT_EQ(wg.GetEdgeWeight('E', 'D'), 6);
}

TEST(Test_NotOrientedWeightedGraph, Test_DeleteVertex) {
  WeightedGraph<char> wg(false);

  wg.AddWeightedEdge('A', 'B', 3);
  wg.AddWeightedEdge('A', 'C', 5);
  wg.AddWeightedEdge('A', 'D', 2);
  wg.AddWeightedEdge('B', 'C', 1);
  wg.AddWeightedEdge('B', 'E', 4);
  wg.AddWeightedEdge('C', 'E', 3);
  wg.AddWeightedEdge('D', 'E', 6);

  wg.DeleteVertex('A');

  ASSERT_FALSE(wg.ContainsEdge('A', 'B'));
  ASSERT_FALSE(wg.ContainsEdge('B', 'A'));
  ASSERT_FALSE(wg.ContainsEdge('A', 'C'));
  ASSERT_FALSE(wg.ContainsEdge('C', 'A'));
  ASSERT_FALSE(wg.ContainsEdge('A', 'D'));
  ASSERT_FALSE(wg.ContainsEdge('D', 'A'));
}

TEST(Test_NotOrientedWeightedGraph, Test_DeleteWeightedEdge) {
  WeightedGraph<char> wg(false);

  wg.AddWeightedEdge('A', 'B', 3);
  wg.AddWeightedEdge('A', 'C', 5);
  wg.AddWeightedEdge('A', 'D', 2);
  wg.AddWeightedEdge('B', 'C', 1);
  wg.AddWeightedEdge('B', 'E', 4);
  wg.AddWeightedEdge('C', 'E', 3);
  wg.AddWeightedEdge('D', 'E', 6);

  wg.DeleteWeightedEdge('A', 'B');

  ASSERT_FALSE(wg.ContainsEdge('A', 'B'));
  ASSERT_FALSE(wg.ContainsEdge('B', 'A'));
  ASSERT_TRUE(wg.ContainsEdge('A', 'C'));

  ASSERT_THROW(wg.DeleteWeightedEdge('A', 'B'), std::invalid_argument);
  ASSERT_THROW(wg.DeleteWeightedEdge('B', 'A'), std::invalid_argument);
}

TEST(Test_NotOrientedWeightedGraph, Test_SetEdgeWeight) {
  WeightedGraph<char> wg(false);

  wg.AddWeightedEdge('A', 'B', 3);
  wg.AddWeightedEdge('A', 'C', 5);
  wg.AddWeightedEdge('A', 'D', 2);
  wg.AddWeightedEdge('B', 'C', 1);
  wg.AddWeightedEdge('B', 'E', 4);
  wg.AddWeightedEdge('C', 'E', 3);
  wg.AddWeightedEdge('D', 'E', 6);

  wg.SetEdgeWeight('A', 'B', 5);

  ASSERT_EQ(wg.GetEdgeWeight('A', 'B'), 5);
  ASSERT_EQ(wg.GetEdgeWeight('B', 'A'), 5);

  ASSERT_THROW(wg.GetEdgeWeight('B', 'D'), std::invalid_argument);
}