#include <gtest/gtest.h>

#include <graph.hpp>

TEST(DijkstraAlgorithmTest, PositiveWeights) {
  vector<vector<int>> graph = {{0, 10, INF, 30, 100},
                               {INF, 0, 50, INF, INF},
                               {INF, INF, 0, INF, 10},
                               {INF, INF, 20, 0, 60},
                               {INF, INF, INF, INF, 0}};
  vector<int> expected_distances = {0, 10, 50, 30, 60};

  WeightedGraph wg(std::move(graph));
  EXPECT_EQ(wg.Dijkstra(0), expected_distances);
}

TEST(DijkstraAlgorithmTest, DisconnectedGraph) {
  vector<vector<int>> graph = {{0, INF, INF, INF, INF},
                               {INF, 0, 15, INF, INF},
                               {INF, INF, 0, INF, INF},
                               {INF, INF, INF, 0, 5},
                               {INF, INF, INF, INF, 0}};
  vector<int> expected_distances = {0, INF, INF, INF, INF};

  WeightedGraph wg(std::move(graph));
  EXPECT_EQ(wg.Dijkstra(0), expected_distances);
}

TEST(DijkstraAlgorithmTest, SingleVertex) {
  vector<vector<int>> graph = {{0}};
  vector<int> expected_distances = {0};

  WeightedGraph wg(std::move(graph));
  EXPECT_EQ(wg.Dijkstra(0), expected_distances);
}

TEST(DijkstraAlgorithmTest, StartVertexDisconnected) {
  vector<vector<int>> graph = {{0, INF, INF, INF},
                               {INF, 0, 7, INF},
                               {INF, INF, 0, 3},
                               {INF, INF, INF, 0}};
  vector<int> expected_distances = {0, INF, INF, INF};

  WeightedGraph wg(std::move(graph));
  EXPECT_EQ(wg.Dijkstra(0), expected_distances);
}

TEST(DijkstraAlgorithmTest, MultiplePaths) {
  vector<vector<int>> graph = {{0, 1, 4, INF, INF},
                               {INF, 0, 4, 2, 7},
                               {INF, INF, 0, 3, INF},
                               {INF, INF, INF, 0, 1},
                               {INF, INF, INF, INF, 0}};
  vector<int> expected_distances = {0, 1, 4, 3, 4};

  WeightedGraph wg(std::move(graph));
  EXPECT_EQ(wg.Dijkstra(0), expected_distances);
}

TEST(DijkstraAlgorithmTest, GraphWithSelfLoops) {
  vector<vector<int>> graph = {
      {0, 10, INF, 5}, {INF, 0, 1, INF}, {INF, INF, 0, 4}, {7, INF, 2, 0}};
  vector<int> expected_distances = {0, 10, 7, 5};

  WeightedGraph wg(std::move(graph));
  EXPECT_EQ(wg.Dijkstra(0), expected_distances);
}

TEST(DijkstraAlgorithmTest, LargerGraph) {
  vector<vector<int>> graph = {
      {0, 3, 1, INF, INF, INF}, {3, 0, 7, 5, 1, INF},   {1, 7, 0, 2, INF, 3},
      {INF, 5, 2, 0, 7, 4},     {INF, 1, INF, 7, 0, 6}, {INF, INF, 3, 4, 6, 0}};
  vector<int> expected_distances = {0, 3, 1, 3, 4, 4};

  WeightedGraph wg(std::move(graph));
  EXPECT_EQ(wg.Dijkstra(0), expected_distances);
}

TEST(DijkstraAlgorithmTest, EvenLargerGraph) {
  vector<vector<int>> graph = {
      {0, 10, INF, INF, INF, 5, INF, INF}, {10, 0, 2, 1, INF, INF, INF, INF},
      {INF, 2, 0, 4, 8, INF, INF, INF},    {INF, 1, 4, 0, 2, INF, INF, INF},
      {INF, INF, 8, 2, 0, 3, 6, INF},      {5, INF, INF, INF, 3, 0, INF, 9},
      {INF, INF, INF, INF, 6, INF, 0, 1},  {INF, INF, INF, INF, INF, 9, 1, 0}};
  vector<int> expected_distances = {0, 10, 12, 10, 8, 5, 14, 14};

  WeightedGraph wg(std::move(graph));
  EXPECT_EQ(wg.Dijkstra(0), expected_distances);
}