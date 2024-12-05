#include <gtest/gtest.h>

#include "graph.hpp"

using namespace algo;

TEST(GraphTest, TopSort) {
  Graph graph(6, 5);

  graph.AddEdge(1, 2, 1);
  graph.AddEdge(1, 3, 2);
  graph.AddEdge(2, 4, 3);
  graph.AddEdge(3, 5, 4);
  graph.AddEdge(4, 6, 5);

  std::vector<int> expected = {0, 1, 3, 5, 2, 4};  // Индексы вершин

  auto calc = graph.TopologicalSort(0);

  ASSERT_EQ(expected, calc);
}

TEST(GraphTest, TopSortEmpty) {
  EXPECT_THROW(
      {
        try {
          Graph graph(0, 0);
          graph.TopologicalSort(0);
        } catch (const std::invalid_argument& e) {
          ASSERT_STREQ(e.what(),
                       "Number of vertices must be greater than zero.");
          throw;
        }
      },
      std::invalid_argument);
}

TEST(GraphTest, TopologicalSort_Disconnected) {
  Graph graph(5, 2);

  graph.AddEdge(1, 2, 1);
  graph.AddEdge(3, 4, 2);

  EXPECT_THROW(
      {
        try {
          graph.TopologicalSort(0);
        } catch (const std::invalid_argument& e) {
          ASSERT_STREQ(e.what(), "Graph is disconnected.");
          throw;
        }
      },
      std::invalid_argument);
}

TEST(GraphTest, TopologicalSort_LinearChain) {
  Graph graph(5, 4);

  graph.AddEdge(1, 2, 1);
  graph.AddEdge(2, 3, 2);
  graph.AddEdge(3, 4, 3);
  graph.AddEdge(4, 5, 4);

  std::vector<int> expected_order = {0, 1, 2, 3,
                                     4};  // Ожидаемый линейный порядок

  auto actual_order = graph.TopologicalSort(0);

  ASSERT_EQ(expected_order, actual_order);
}

TEST(GraphTest, TopologicalSort_EmptyEdgeList) {
  Graph graph(3, 0);  // Граф без рёбер

  EXPECT_THROW(
      {
        try {
          graph.TopologicalSort(0);
        } catch (const std::invalid_argument& e) {
          ASSERT_STREQ(e.what(), "Graph is disconnected.");
          throw;
        }
      },
      std::invalid_argument);
}
