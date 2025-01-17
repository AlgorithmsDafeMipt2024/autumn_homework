#include <gtest/gtest.h>

#include "top_sort.hpp"

TEST(SimpleGraph, Simple) {
  int const vertices = 3;
  int const edges = 2;
  std::vector<std::pair<int, int>> edge = {{1, 2}, {2, 3}};

  std::vector<int> result = TopologySort(vertices, edges, edge);
  std::vector<int> expected = {1, 2, 3};

  ASSERT_EQ(result, expected);
}

TEST(DisconnectedGraph, Simple) {
  int const vertices = 5;
  int const edges = 3;
  std::vector<std::pair<int, int>> edge = {{1, 2}, {3, 4}, {3, 5}};

  std::vector<int> result = TopologySort(vertices, edges, edge);
  std::vector<int> expected = {3, 5, 4, 1, 2};

  ASSERT_EQ(result, expected);
}

TEST(GraphWithCycle, Simple) {
  int vertices = 3;
  int edges = 3;
  std::vector<std::pair<int, int>> edge = {{1, 3}, {3, 2}, {2, 1}};

  EXPECT_THROW(TopologySort(vertices, edges, edge);, CycleDetectedException);
}
