#include "graph.hpp"

#include <gtest/gtest.h>

TEST(GraphTest, EmptyGraph) {
  EXPECT_THROW(Graph graph(0, 0), std::invalid_argument);
}

TEST(GraphTest, InvalidNumberOfVertices) {
  EXPECT_THROW(Graph graph(-1, 5), std::invalid_argument);
}

TEST(GraphTest, AddEdgeOutOfBounds) {
  Graph graph(3, 3);

  EXPECT_THROW(graph.addEdge(0, 1, 1), std::out_of_range);
  EXPECT_THROW(graph.addEdge(1, 4, 1), std::out_of_range);
  EXPECT_THROW(graph.addEdge(4, 1, 1), std::out_of_range);
}

TEST(GraphTest, AddEdgeValid) {
  Graph graph(3, 3);

  EXPECT_NO_THROW(graph.addEdge(1, 2, 1));
  EXPECT_NO_THROW(graph.addEdge(2, 3, 2));
  EXPECT_NO_THROW(graph.addEdge(3, 1, 3));
}

TEST(GraphTest, GetNeighboursValid) {
  Graph graph(3, 3);

  graph.addEdge(1, 2, 1);
  graph.addEdge(2, 3, 2);
  graph.addEdge(3, 1, 3);

  std::vector<std::pair<int, int>> neighbours = graph.getNeighbours(1);

  ASSERT_EQ(neighbours.size(), 1);
  ASSERT_EQ(neighbours[0].first, 1);
  ASSERT_EQ(neighbours[0].second, 1);

  neighbours = graph.getNeighbours(2);
  ASSERT_EQ(neighbours.size(), 1);
  ASSERT_EQ(neighbours[0].first, 2);
  ASSERT_EQ(neighbours[0].second, 2);
}

TEST(GraphTest, GetNeighboursOutOfBounds) {
  Graph graph(3, 3);

  graph.addEdge(1, 2, 1);
  graph.addEdge(2, 3, 2);

  EXPECT_THROW(graph.getNeighbours(5), std::out_of_range);
}

TEST(GraphTest, TopologicalSortValid) {
  Graph graph(6, 6);

  graph.addEdge(1, 2, 1);
  graph.addEdge(1, 3, 2);
  graph.addEdge(2, 4, 3);
  graph.addEdge(3, 5, 4);
  graph.addEdge(4, 6, 5);
  graph.addEdge(5, 6, 6);

  std::vector<int> expected_order = {0, 2, 1, 4, 3, 5};
  auto actual_order = graph.topological_sort(0);

  ASSERT_EQ(expected_order, actual_order);
}

TEST(GraphTest, TopologicalSortEmptyGraph) {
  Graph graph(0, 0);

  auto order = graph.topological_sort(0);
  ASSERT_TRUE(order.empty());
}

TEST(GraphTest, TopologicalSortSingleVertex) {
  Graph graph(1, 0);

  std::vector<int> expected_order = {0};
  auto actual_order = graph.topological_sort(0);

  ASSERT_EQ(expected_order, actual_order);
}

TEST(GraphTest, TopologicalSortEmptyGraphError) {
  Graph graph(0, 0);

  EXPECT_NO_THROW({ auto order = graph.topological_sort(0); });
}
