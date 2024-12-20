#include "gtest/gtest.h"
#include "top_sort.hpp"

TEST(SimpleGraph, Simple) {
  int const vertices = 3;
  int const edges = 2;
  std::vector<std::pair<int, int>> edge = {{1, 2}, {2, 3}};

  std::vector<int> const result = TopSort(vertices, edges, edge);
  std::vector<int> const expected = {1, 2, 3};

  ASSERT_EQ(result, expected);
}

TEST(GraphWithCycle, Simple) {
  int const vertices = 3;
  int const edges = 3;
  std::vector<std::pair<int, int>> edge = {{1, 2}, {2, 3}, {3, 1}};

  EXPECT_THROW(TopSort(vertices, edges, edge);, CycleGraph);
}

TEST(DisconnectedGraph, Simple) {
  int const vertices = 4;
  int const edges = 2;
  std::vector<std::pair<int, int>> edge = {{1, 2}, {3, 4}};

  std::vector<int> const result = TopSort(vertices, edges, edge);
  std::vector<int> const expected = {3, 4, 1, 2};

  ASSERT_EQ(result, expected);
}

TEST(SingleVertex, Simple) {
  int const vertices = 1;
  int const edges = 0;
  std::vector<std::pair<int, int>> edge = {};

  std::vector<int> const result = TopSort(vertices, edges, edge);
  std::vector<int> const expected = {1};

  ASSERT_EQ(result, expected);
}

TEST(MultipleValidOrders, Simple) {
  int const vertices = 4;
  int const edges = 3;
  std::vector<std::pair<int, int>> edge = {{1, 2}, {1, 3}, {3, 4}};

  std::vector<int> const result = TopSort(vertices, edges, edge);
  std::vector<int> const expected1 = {1, 3, 4, 2};

  ASSERT_EQ(result, expected1);
}

TEST(AllVerticesConnected, Simple) {
  int const vertices = 5;
  int const edges = 4;
  std::vector<std::pair<int, int>> edge = {{1, 2}, {2, 3}, {3, 4}, {4, 5}};

  std::vector<int> const result = TopSort(vertices, edges, edge);
  std::vector<int> const expected = {1, 2, 3, 4, 5};

  ASSERT_EQ(result, expected);
}

TEST(ReverseOrder, Simple) {
  int const vertices = 3;
  int const edges = 2;
  std::vector<std::pair<int, int>> edge = {{3, 2}, {2, 1}};

  std::vector<int> const result = TopSort(vertices, edges, edge);
  std::vector<int> const expected = {3, 2, 1};

  ASSERT_EQ(result, expected);
}

TEST(ComplexGraph, Simple) {
  int const vertices = 6;
  int const edges = 6;
  std::vector<std::pair<int, int>> edge = {{5, 2}, {5, 0}, {4, 0},
                                           {4, 1}, {2, 3}, {3, 1}};

  std::vector<int> const result = TopSort(vertices, edges, edge);
  std::vector<int> const expected = {6, 5, 4, 0, 2, 3, 1};

  ASSERT_EQ(result, expected);
}

TEST(GraphWithMultipleCyclesm, Simple) {
  int const vertices = 4;
  int const edges = 5;
  std::vector<std::pair<int, int>> edge = {
      {1, 2}, {2, 3}, {3, 1}, {2, 4}, {4, 2}};

  EXPECT_THROW(TopSort(vertices, edges, edge), CycleGraph);
}

TEST(MediumGraph, Simple) {
  int const vertices = 6;
  int const edges = 6;
  std::vector<std::pair<int, int>> edge = {{5, 2}, {4, 2}, {3, 4},
                                           {6, 3}, {6, 1}, {5, 1}};
  std::vector<int> const result = TopSort(vertices, edges, edge);
  std::vector<int> const expected = {6, 5, 3, 4, 2, 1};

  ASSERT_EQ(result, expected);
}
