#include <gtest/gtest.h>

#include "djikstra.hpp"
#include "weighted_graph.hpp"

void CheckDistances(std::vector<int>& dist, std::vector<int>& exp_dist) {
  EXPECT_EQ(dist.size(), exp_dist.size());
  for (size_t i = 0; i < dist.size(); ++i) EXPECT_EQ(dist[i], exp_dist[i]);
}

void CheckPaths(std::vector<int>& prev,
                std::vector<std::vector<int>>& exp_paths, size_t source) {
  for (size_t i = 0; i < prev.size(); ++i) {
    std::vector<int> path = GetPath<int>(prev, source, i);
    EXPECT_EQ(path, exp_paths[i]);
  }
}

TEST(DijkstraTest, SimpleUndirectedGraph) {
  WeightedGraph<int> graph;

  // Add vertices
  for (int i = 0; i < 5; i++) graph.AddVertex(i);

  // Add edges
  graph.AddEdge(0, 1, 4);
  graph.AddEdge(0, 2, 2);
  graph.AddEdge(1, 2, 1);
  graph.AddEdge(1, 3, 5);
  graph.AddEdge(2, 3, 8);
  graph.AddEdge(2, 4, 10);
  graph.AddEdge(3, 4, 2);

  size_t source = 0;

  auto [distances, previous] = Dijkstra(graph, source);

  std::vector<int> expected_distances = {0, 3, 2, 8, 10};

  CheckDistances(distances, expected_distances);

  std::vector<std::vector<int>> expected_paths = {
      {0}, {0, 2, 1}, {0, 2}, {0, 2, 1, 3}, {0, 2, 1, 3, 4}};

  CheckPaths(previous, expected_paths, source);
}

TEST(DijkstraTest, SimpleDirectedGraph) {
  WeightedGraph<int> graph;

  // Add vertices
  for (int i = 0; i < 5; i++) graph.AddVertex(i);

  // Add edges
  graph.AddDirEdge(0, 1, 4);
  graph.AddDirEdge(0, 2, 2);
  graph.AddDirEdge(1, 2, 1);
  graph.AddDirEdge(1, 3, 5);
  graph.AddDirEdge(2, 3, 8);
  graph.AddDirEdge(2, 4, 10);
  graph.AddDirEdge(3, 4, 2);

  size_t source = 0;

  auto [distances, previous] = Dijkstra(graph, source);

  std::vector<int> expected_distances = {0, 4, 2, 9, 11};

  CheckDistances(distances, expected_distances);

  std::vector<std::vector<int>> expected_paths = {
      {0}, {0, 1}, {0, 2}, {0, 1, 3}, {0, 1, 3, 4}};

  CheckPaths(previous, expected_paths, source);
}

TEST(DijkstraTest, DisconnectedGraph) {
  WeightedGraph<int> graph;

  // Add vertices
  for (int i = 0; i < 3; i++) graph.AddVertex(i);

  // Add single edge
  graph.AddDirEdge(0, 1, 5);

  size_t source = 0;

  auto [distances, previous] = Dijkstra(graph, source);

  std::vector<int> expected_distances = {0, 5, std::numeric_limits<int>::max()};

  CheckDistances(distances, expected_distances);

  std::vector<std::vector<int>> expected_paths = {{0}, {0, 1}, {}};

  CheckPaths(previous, expected_paths, source);
}