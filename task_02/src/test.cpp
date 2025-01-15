#include <gtest/gtest.h>

#include "task_02.hpp"

TEST(SimpleGraph1, Simple) {
  int const vertices = 6;
  int const edges = 6;
  std::vector<std::pair<int, int>> edge = {{1, 2}, {2, 3}, {3, 4},
                                           {3, 5}, {1, 5}, {2, 6}};

  std::pair<std::vector<std::pair<int, int>>, std::vector<int>> result =
      BridgesAndCutPoints(vertices, edges, edge);
  std::pair<std::vector<std::pair<int, int>>, std::vector<int>> expected = {
      {{4, 3}, {6, 2}}, {3, 2}};

  ASSERT_EQ(result, expected);
}

TEST(SimpleGraph2, Simple) {
  int const vertices = 3;
  int const edges = 2;
  std::vector<std::pair<int, int>> edge = {{3, 2}, {2, 1}};

  std::pair<std::vector<std::pair<int, int>>, std::vector<int>> result =
      BridgesAndCutPoints(vertices, edges, edge);
  std::pair<std::vector<std::pair<int, int>>, std::vector<int>> expected = {
      {{3, 2}, {2, 1}}, {2}};

  ASSERT_EQ(result, expected);
}