
#include <gtest/gtest.h>

#include <graph.hpp>

TEST(JohnsonAlgorithm, test1) {
  vector<vector<int>> g = {
      {0, -5, 2, 3}, {0, 0, 4, 0}, {0, 0, 0, 1}, {0, 0, 0, 0}};

  Weighted_Graph wg(g);
  vector<vector<int>> shortest_paths(
      {{0, 0, 3, 3}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}});

  ASSERT_EQ(wg.JohnsonAlgorithm(), shortest_paths);
}

TEST(JohnsonAlgorithm, test2) {
  vector<vector<int>> g = {{0, 1, 0, 5, 1},
                           {0, 0, 0, 0, 0},
                           {0, 0, -3, 0, 5},
                           {0, 1, 7, 0, 1},
                           {1, 0, 0, 4, 0}};

  Weighted_Graph wg(g);
  vector<vector<int>> shortest_paths({{0, -3, 0, 2, 2},
                                      {0, 0, 0, 0, 0},
                                      {0, 0, -3, 0, 0},
                                      {0, 0, 16, 0, 5},
                                      {0, 0, 0, 0, 0}});

  ASSERT_EQ(wg.JohnsonAlgorithm(), shortest_paths);
}

TEST(JohnsonAlgorithm, test3) {
  vector<vector<int>> g = {{0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0}};

  Weighted_Graph wg(g);
  vector<vector<int>> shortest_paths({{0, 0, 0, 0, 0},
                                      {0, 0, 0, 0, 0},
                                      {0, 0, 0, 0, 0},
                                      {0, 0, 0, 0, 0},
                                      {0, 0, 0, 0, 0}});

  ASSERT_EQ(wg.JohnsonAlgorithm(), shortest_paths);
}

TEST(JohnsonAlgorithm, test4) {
  vector<vector<int>> g = {
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
  };

  EXPECT_THROW(Weighted_Graph wg(g), std::logic_error);
}

TEST(JohnsonAlgorithm, test5) {
  vector<vector<int>> g = {};

  EXPECT_THROW(Weighted_Graph wg(g), std::logic_error);
}

TEST(JohnsonAlgorithm, test6) {
  vector<vector<int>> g = {{}, {}, {1, 3, 4}};

  EXPECT_THROW(Weighted_Graph wg(g), std::logic_error);
}