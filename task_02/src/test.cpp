#include <gtest/gtest.h>

#include <algorithm>
#include <set>

#include "network.hpp"

// Helper function to check if a bridge exists
bool BridgeExists(const std::vector<std::pair<int, int>>& bridges, int u,
                  int v) {
  return std::find_if(bridges.begin(), bridges.end(),
                      [u, v](const auto& bridge) {
                        return (bridge.first == u && bridge.second == v) ||
                               (bridge.first == v && bridge.second == u);
                      }) != bridges.end();
}

// Helper function to check if returned bridges are correct
void CheckBridges(const std::vector<std::pair<int, int>>& bridges,
                  const std::vector<std::pair<int, int>>& expected_bridges) {
  EXPECT_EQ(bridges.size(), expected_bridges.size());
  for (const auto& bridge : expected_bridges)
    EXPECT_TRUE(BridgeExists(bridges, bridge.first, bridge.second));
}

// Helper function to check if two sets of integers are equal
bool SetsEqual(const std::vector<int>& vec1, const std::vector<int>& vec2) {
  std::set<int> set1(vec1.begin(), vec1.end());
  std::set<int> set2(vec2.begin(), vec2.end());
  return set1 == set2;
}

//  Helper function to check if returned cut vertices are correct
void CheckCutVertices(const std::vector<int>& cut_vertices,
                      const std::vector<int>& expected_cut_vertices) {
  EXPECT_TRUE(SetsEqual(cut_vertices, expected_cut_vertices));
}

TEST(NetworkTest, SimpleTriangleWithBridge) {
  Network network;
  network.AddVertex(0);
  network.AddVertex(1);
  network.AddVertex(2);
  network.AddVertex(3);

  network.AddEdge(0, 1);
  network.AddEdge(1, 2);
  network.AddEdge(2, 0);
  network.AddEdge(2, 3);  // This is a bridge

  auto [bridges, cut_vertices] = network.FindBridgesAndCutVertices();

  std::vector<std::pair<int, int>> excepted_bridges = {{2, 3}};
  std::vector<int> excepted_cut_vertices = {2};

  CheckBridges(bridges, excepted_bridges);
  CheckCutVertices(cut_vertices, excepted_cut_vertices);
}

TEST(NetworkTest, NoBridgesOrCutVertices) {
  Network network;
  network.AddVertex(0);
  network.AddVertex(1);
  network.AddVertex(2);

  network.AddEdge(0, 1);
  network.AddEdge(1, 2);
  network.AddEdge(2, 0);

  auto [bridges, cut_vertices] = network.FindBridgesAndCutVertices();

  std::vector<std::pair<int, int>> excepted_bridges = {};
  std::vector<int> excepted_cut_vertices = {};

  CheckBridges(bridges, excepted_bridges);
  CheckCutVertices(cut_vertices, excepted_cut_vertices);
}

TEST(NetworkTest, LineGraph) {
  Network network;
  network.AddVertex(0);
  network.AddVertex(1);
  network.AddVertex(2);

  network.AddEdge(0, 1);
  network.AddEdge(1, 2);

  auto [bridges, cut_vertices] = network.FindBridgesAndCutVertices();

  std::vector<std::pair<int, int>> excepted_bridges = {{0, 1}, {1, 2}};
  std::vector<int> excepted_cut_vertices = {1};

  CheckBridges(bridges, excepted_bridges);
  CheckCutVertices(cut_vertices, excepted_cut_vertices);
}

TEST(NetworkTest, EmptyGraph) {
  Network network;
  auto [bridges, cut_vertices] = network.FindBridgesAndCutVertices();

  std::vector<std::pair<int, int>> excepted_bridges = {};
  std::vector<int> excepted_cut_vertices = {};

  CheckBridges(bridges, excepted_bridges);
  CheckCutVertices(cut_vertices, excepted_cut_vertices);
}

TEST(NetworkTest, CycleWithMultipleBridges) {
  Network network;
  network.AddVertex(0);
  network.AddVertex(1);
  network.AddVertex(2);
  network.AddVertex(3);
  network.AddVertex(4);

  network.AddEdge(0, 1);
  network.AddEdge(1, 2);
  network.AddEdge(2, 0);
  network.AddEdge(1, 3);  // Bridge to vertex 3
  network.AddEdge(3, 4);  // Bridge to vertex 4

  auto [bridges, cut_vertices] = network.FindBridgesAndCutVertices();

  std::vector<std::pair<int, int>> excepted_bridges = {{1, 3}, {3, 4}};
  std::vector<int> excepted_cut_vertices = {1, 3};

  CheckBridges(bridges, excepted_bridges);
  CheckCutVertices(cut_vertices, excepted_cut_vertices);
}