
#include <gtest/gtest.h>

#include <graph.hpp>

TEST(JohnsonAlgorithmTest, PositiveWeights) {
  vector<vector<int>> graph = {{0, 3, INF, INF, INF},
                               {INF, 0, 1, INF, 10},
                               {4, INF, 0, 2, INF},
                               {INF, INF, INF, 0, 1},
                               {INF, INF, INF, INF, 0}};
  vector<vector<int>> expected_distances = {{0, 3, 4, 6, 7},
                                            {5, 0, 1, 3, 4},
                                            {4, 7, 0, 2, 3},
                                            {INF, INF, INF, 0, 1},
                                            {INF, INF, INF, INF, 0}};

  WeightedGraph wg(std::move(graph));
  ASSERT_EQ(wg.Johnson(), expected_distances);
}

TEST(JohnsonAlgorithmTest, NegativeWeights) {
  vector<vector<int>> graph = {{0, -1, 4, INF, INF},
                               {INF, 0, 3, 2, 2},
                               {INF, INF, 0, INF, INF},
                               {INF, 1, 5, 0, INF},
                               {INF, INF, INF, -3, 0}};
  vector<vector<int>> expected_distances = {{0, -1, 2, -2, 1},
                                            {INF, 0, 3, -1, 2},
                                            {INF, INF, 0, INF, INF},
                                            {INF, 1, 4, 0, 3},
                                            {INF, -2, 1, -3, 0}};
  WeightedGraph wg(std::move(graph));
  EXPECT_EQ(wg.Johnson(), expected_distances);
}

TEST(JohnsonAlgorithmTest, NegativeCycle) {
  vector<vector<int>> graph = {{0, 1, INF, INF},
                               {INF, 0, -1, INF},
                               {INF, INF, 0, -1},
                               {-1, INF, INF, 0}};

  WeightedGraph wg(std::move(graph));
  EXPECT_THROW(wg.Johnson();, std::logic_error);
}

TEST(JohnsonAlgorithmTest, PositiveWeightsLargerGraph) {
  vector<vector<int>> graph = {
      {0, 10, INF, INF, INF, 5},  {INF, 0, 1, INF, INF, 2},
      {INF, INF, 0, 4, INF, INF}, {7, INF, 6, 0, 3, INF},
      {INF, INF, 9, 2, 0, INF},   {INF, 3, INF, 9, 2, 0}};
  vector<vector<int>> expected_distances = {
      {0, 8, 9, 13, 7, 5}, {INF, 0, 1, 5, 3, 2}, {INF, INF, 0, 4, 6, 7},
      {7, 10, 6, 0, 3, 9}, {9, 12, 8, 2, 0, 10}, {5, 3, 4, 8, 2, 0}};

  WeightedGraph wg(std::move(graph));
  EXPECT_EQ(wg.Johnson(), expected_distances);
}

TEST(JohnsonAlgorithmTest, PositiveWeightsDisconnectedGraph) {
  vector<vector<int>> graph = {
      {0, 3, INF, INF}, {INF, 0, 7, INF}, {INF, INF, 0, 2}, {INF, INF, INF, 0}};
  vector<vector<int>> expected_distances = {
      {0, 3, 10, 12}, {INF, 0, 7, 9}, {INF, INF, 0, 2}, {INF, INF, INF, 0}};

  WeightedGraph wg(std::move(graph));
  EXPECT_EQ(wg.Johnson(), expected_distances);
}

TEST(JohnsonAlgorithmTest, NegativeWeightsComplexGraph) {
  vector<vector<int>> graph = {
      {0, 4, INF, INF, INF, INF},  {INF, 0, -2, INF, INF, INF},
      {INF, INF, 0, 3, INF, INF},  {INF, INF, INF, 0, 2, 3},
      {INF, INF, INF, INF, 0, -1}, {INF, INF, INF, INF, INF, 0}};
  vector<vector<int>> expected_distances = {
      {0, 4, 2, 5, 7, 6},          {INF, 0, -2, 1, 3, 2},
      {INF, INF, 0, 3, 5, 4},      {INF, INF, INF, 0, 2, 1},
      {INF, INF, INF, INF, 0, -1}, {INF, INF, INF, INF, INF, 0}};

  WeightedGraph wg(std::move(graph));
  EXPECT_EQ(wg.Johnson(), expected_distances);
}

TEST(JohnsonAlgorithmTest, NegativeAndPositiveWeightsMixed) {
  vector<vector<int>> graph = {{0, INF, INF, 1},
                               {INF, 0, -3, INF},
                               {INF, INF, 0, INF},
                               {10, INF, INF, 0}};
  vector<vector<int>> expected_distances = {
      {0, 11, 8, 1}, {7, 0, -3, 8}, {INF, INF, 0, INF}, {10, 21, 18, 0}};

  WeightedGraph wg(std::move(graph));
  EXPECT_EQ(wg.Johnson(), expected_distances);
}

TEST(JohnsonAlgorithmTest, SingleVertex) {
  vector<vector<int>> graph = {{0}};
  vector<vector<int>> expected_distances = {{0}};

  WeightedGraph wg(std::move(graph));
  EXPECT_EQ(wg.Johnson(), expected_distances);
}

TEST(JohnsonAlgorithmTest, EmptyGraph) {
  vector<vector<int>> graph;

  EXPECT_THROW(WeightedGraph wg(std::move(graph)), std::logic_error);
}