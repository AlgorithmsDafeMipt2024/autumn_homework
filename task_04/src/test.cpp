#include <gtest/gtest.h>

#include <algorithm_Dijkstra.hpp>

TEST(TopologySort, Simple) {
  int n = 5;
  int m = 7;
  int s = 2;
  int t = 5;
  std::vector<vector<int>> vec = {{1, 2, 1}, {1, 3, 4}, {1, 5, 5}, {2, 3, 1},
                                  {3, 4, 2}, {3, 5, 3}, {4, 5, 7}};
  std::pair<std::pair<int, int>, std::vector<int>> expected = {{4, 3},
                                                               {2, 3, 5}};
  std::pair<std::pair<int, int>, std::vector<int>> result =
      Dijkstra(n, m, s, t, vec);
  ASSERT_EQ(result, expected);
}

TEST(DijkstraTest, BasicPath) {
  int n = 4;
  int m = 5;
  int s = 1;
  int t = 4;
  std::vector<std::vector<int>> vec = {
      {1, 2, 1}, {1, 3, 4}, {2, 3, 2}, {2, 4, 5}, {3, 4, 1}};
  std::pair<std::pair<int, int>, std::vector<int>> expected = {{4, 4},
                                                               {1, 2, 3, 4}};
  std::pair<std::pair<int, int>, std::vector<int>> result =
      Dijkstra(n, m, s, t, vec);
  ASSERT_EQ(result, expected);
}

TEST(DijkstraTest, NoPath) {
  int n = 3;
  int m = 2;
  int s = 1;
  int t = 3;
  std::vector<std::vector<int>> vec = {{1, 2, 2}, {2, 1, 2}};
  EXPECT_THROW(Dijkstra(n, m, s, t, vec), Nonexistent_way);
}

TEST(DijkstraTest, MultiplePaths) {
  int n = 6;
  int m = 8;
  int s = 1;
  int t = 5;
  std::vector<std::vector<int>> vec = {{1, 2, 1}, {1, 3, 2}, {2, 4, 3},
                                       {3, 4, 1}, {4, 5, 1}, {2, 5, 5},
                                       {3, 5, 3}, {1, 6, 10}};
  std::pair<std::pair<int, int>, std::vector<int>> expected = {{4, 4},
                                                               {1, 3, 4, 5}};
  std::pair<std::pair<int, int>, std::vector<int>> result =
      Dijkstra(n, m, s, t, vec);
  ASSERT_EQ(result, expected);
}

TEST(DijkstraTest, SingleNode) {
  int n = 1;
  int m = 0;
  int s = 1;
  int t = 1;
  std::vector<std::vector<int>> vec = {};
  std::pair<std::pair<int, int>, std::vector<int>> expected = {{0, 1}, {1}};
  std::pair<std::pair<int, int>, std::vector<int>> result =
      Dijkstra(n, m, s, t, vec);
  ASSERT_EQ(result, expected);
}

TEST(DijkstraTest, CyclePath) {
  int n = 4;
  int m = 4;
  int s = 1;
  int t = 3;
  std::vector<std::vector<int>> vec = {
      {1, 2, 1}, {2, 3, 2}, {3, 1, 2}, {2, 4, 1}, {4, 3, 1}};
  std::pair<std::pair<int, int>, std::vector<int>> expected = {{2, 2}, {1, 3}};
  std::pair<std::pair<int, int>, std::vector<int>> result =
      Dijkstra(n, m, s, t, vec);
  ASSERT_EQ(result, expected);
}

TEST(DijkstraTest, LargeWeights) {
  int n = 3;
  int m = 3;
  int s = 1;
  int t = 3;
  std::vector<std::vector<int>> vec = {
      {1, 2, 1000}, {2, 3, 2000}, {1, 3, 5000}};
  std::pair<std::pair<int, int>, std::vector<int>> expected = {{3000, 3},
                                                               {1, 2, 3}};
  std::pair<std::pair<int, int>, std::vector<int>> result =
      Dijkstra(n, m, s, t, vec);
  ASSERT_EQ(result, expected);
}

TEST(DijkstraTest, ManyEdges) {
  int n = 5;
  int m = 10;
  int s = 1;
  int t = 5;
  std::vector<std::vector<int>> vec = {
      {1, 2, 1}, {1, 3, 2}, {1, 4, 5}, {2, 3, 1}, {2, 4, 2},
      {2, 5, 4}, {3, 4, 1}, {3, 5, 3}, {4, 5, 1}, {1, 5, 10}};
  std::pair<std::pair<int, int>, std::vector<int>> expected = {{4, 4},
                                                               {1, 2, 4, 5}};
  std::pair<std::pair<int, int>, std::vector<int>> result =
      Dijkstra(n, m, s, t, vec);
  ASSERT_EQ(result, expected);
}

TEST(DijkstraTest, ComplexGraph) {
  int n = 6;
  int m = 15;
  int s = 1;
  int t = 6;
  std::vector<std::vector<int>> vec = {
      {1, 2, 1}, {1, 3, 4}, {1, 4, 2}, {2, 3, 1}, {2, 4, 5},
      {3, 5, 2}, {4, 5, 3}, {4, 6, 1}, {5, 6, 1}, {2, 6, 10},
      {3, 4, 2}, {1, 5, 7}, {2, 5, 3}, {4, 3, 1}, {5, 1, 8}};
  std::pair<std::pair<int, int>, std::vector<int>> expected = {{3, 3},
                                                               {1, 4, 6}};
  std::pair<std::pair<int, int>, std::vector<int>> result =
      Dijkstra(n, m, s, t, vec);
  ASSERT_EQ(result, expected);
}

TEST(DijkstraTest, DenseGraph) {
  int n = 7;
  int m = 21;
  int s = 1;
  int t = 7;
  std::vector<std::vector<int>> vec = {
      {1, 2, 1}, {1, 3, 2}, {1, 4, 3}, {1, 5, 4}, {1, 6, 5},
      {2, 3, 1}, {2, 4, 2}, {2, 5, 3}, {2, 6, 4}, {2, 7, 5},
      {3, 4, 1}, {3, 5, 2}, {3, 6, 3}, {3, 7, 4}, {4, 5, 1},
      {4, 6, 2}, {4, 7, 3}, {5, 6, 1}, {5, 7, 2}, {6, 7, 1}};
  std::pair<std::pair<int, int>, std::vector<int>> expected = {{5, 5},
                                                               {1, 2, 4, 7}};
  std::pair<std::pair<int, int>, std::vector<int>> result =
      Dijkstra(n, m, s, t, vec);
  ASSERT_EQ(result, expected);
}