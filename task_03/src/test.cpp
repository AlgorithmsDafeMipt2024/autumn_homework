#include <gtest/gtest.h>

#include "johnson.hpp"

TEST(JohnsonAlgorithmTest, SimpleGraph) {
  WeightedGraph<Vertex<int>, int> graph;
  for (int i = 0; i < 4; ++i) graph.AddVertex(i);
  graph.AddDirEdge(0, 1, 1);
  graph.AddDirEdge(1, 2, 2);
  graph.AddDirEdge(2, 3, 1);
  graph.AddDirEdge(0, 2, 4);

  std::vector<std::vector<int>> expected = {
      {0, 1, 3, 4}, {INF, 0, 2, 3}, {INF, INF, 0, 1}, {INF, INF, INF, 0}};

  std::vector<std::vector<int>> result = Johnson(graph);
  EXPECT_EQ(result, expected);
}

TEST(JohnsonAlgorithmTest, GraphWithNegativeWeights) {
  WeightedGraph<Vertex<int>, int> graph;
  for (int i = 0; i < 4; ++i) graph.AddVertex(i);
  graph.AddDirEdge(0, 1, -2);
  graph.AddDirEdge(1, 2, -3);
  graph.AddDirEdge(2, 3, 1);
  graph.AddDirEdge(0, 2, 4);

  std::vector<std::vector<int>> expected = {
      {0, -2, -5, -4}, {INF, 0, -3, -2}, {INF, INF, 0, 1}, {INF, INF, INF, 0}};

  std::vector<std::vector<int>> result = Johnson(graph);
  EXPECT_EQ(result, expected);
}

TEST(JohnsonAlgorithmTest, NegativeCycle) {
  WeightedGraph<Vertex<int>, int> graph;
  for (int i = 0; i < 4; ++i) graph.AddVertex(i);
  graph.AddDirEdge(0, 1, 1);
  graph.AddDirEdge(1, 2, 2);
  graph.AddDirEdge(2, 0, -4);
  graph.AddDirEdge(1, 3, 5);

  std::vector<std::vector<int>> result = Johnson(graph);
  EXPECT_TRUE(result.empty());
}

TEST(JohnsonAlgorithmTest, DisconnectedGraph) {
  WeightedGraph<Vertex<int>, int> graph;
  for (int i = 0; i < 4; ++i) graph.AddVertex(i);
  graph.AddDirEdge(0, 1, 1);
  graph.AddDirEdge(1, 2, 2);
  // Vertex 3 and 4 are disconnected

  std::vector<std::vector<int>> expected = {
      {0, 1, 3, INF}, {INF, 0, 2, INF}, {INF, INF, 0, INF}, {INF, INF, INF, 0}};

  std::vector<std::vector<int>> result = Johnson(graph);
  EXPECT_EQ(result, expected);
}

TEST(JohnsonAlgorithmTest, EmptyGraph) {
  WeightedGraph<Vertex<int>, int> graph;
  // No edges or vertices

  std::vector<std::vector<int>> result = Johnson(graph);
  EXPECT_TRUE(result.empty());
}