#include <graph.h>
#include <gtest/gtest.h>

TEST(TopologySort, Simple1) {
  std::vector<std::vector<int>> table = {
      {0, 4, 0, 0, 0, 0, 0, 8, 0},  {4, 0, 8, 0, 0, 0, 0, 11, 0},
      {0, 8, 0, 7, 0, 4, 0, 0, 2},  {0, 0, 7, 0, 9, 14, 0, 0, 0},
      {0, 0, 0, 9, 0, 10, 0, 0, 0}, {0, 0, 4, 14, 10, 0, 2, 0, 0},
      {0, 0, 0, 0, 0, 2, 0, 1, 6},  {8, 11, 0, 0, 0, 0, 1, 0, 7},
      {0, 0, 2, 0, 0, 0, 6, 7, 0}};
  Weighted_Graph graph(table);
  ASSERT_EQ(graph.Dijkstra_algo(1),
            std::vector<int>({0, 4, 12, 19, 21, 11, 9, 8, 14}));
  ASSERT_EQ(graph.Dijkstra_algo(3),
            std::vector<int>({12, 8, 0, 7, 14, 4, 6, 7, 2}));
}

TEST(TopologySort, Simple2) {
  std::vector<std::vector<int>> table = {
      {0, 7, 9, 0, 0, 14},  {7, 0, 10, 15, 0, 0}, {9, 10, 0, 11, 0, 2},
      {0, 15, 11, 0, 6, 0}, {0, 0, 0, 6, 0, 9},   {14, 0, 2, 0, 9, 0}};
  Weighted_Graph graph(table);
  ASSERT_EQ(graph.Dijkstra_algo(1), std::vector<int>({0, 7, 9, 20, 20, 11}));
  ASSERT_EQ(graph.Dijkstra_algo(5), std::vector<int>({20, 21, 11, 6, 0, 9}));
}

TEST(TopologySort, Simple3) {
  std::vector<std::vector<int>> table = {{1, 2, 3}, {1, 2, 3, 4}};
  EXPECT_THROW(Weighted_Graph graph(table), std::logic_error);
}

TEST(TopologySort, Simple4) {
  std::vector<std::vector<int>> table = {{}, {}, {}};
  EXPECT_THROW(Weighted_Graph graph(table), std::logic_error);
}

TEST(TopologySort, Simple5) {
  std::vector<std::vector<int>> table = {};
  EXPECT_THROW(Weighted_Graph graph(table), std::logic_error);
}