#include "gtest/gtest.h"

#include "bridges_and_point.hpp"

TEST(SimpleTest, Simple) {
  int const vertices = 6;
  int const edge = 6;
  std::vector<std::pair<int, int>> const edges = {{1, 3}, {2, 3}, {3, 4},
                                                  {3, 5}, {4, 5}, {4, 6}};

  pair<set<int>, vector<pair<int, int>>> const result =
      Answer(vertices, edge, edges);
  pair<set<int>, vector<pair<int, int>>> const expected = {
      {3, 4}, {{1, 3}, {3, 2}, {4, 6}}};
  ASSERT_EQ(result, expected);
}

TEST(CutPointsAndBridgesTest, BasicFunctionality) {
  int const vertices = 5;
  int const edges = 5;
  std::vector<std::pair<int, int>> const edgeList = {
      {1, 2}, {2, 3}, {3, 4}, {4, 5}, {2, 5}};

  pair<set<int>, vector<pair<int, int>>> const result =
      Answer(vertices, edges, edgeList);
  set<int> expectedCutPoints = {2};
  vector<pair<int, int>> const expectedBridges = {{1, 2}};

  ASSERT_EQ(result.first, expectedCutPoints);
  ASSERT_EQ(result.second, expectedBridges);
}

TEST(CutPointsAndBridgesTest, NoCutPoints) {
  int const vertices = 4;
  int const edges = 4;
  std::vector<std::pair<int, int>> const edgeList = {
      {1, 2}, {2, 3}, {3, 4}, {4, 1}};

  pair<set<int>, vector<pair<int, int>>> const result =
      Answer(vertices, edges, edgeList);
  set<int> expectedCutPoints = {};
  vector<pair<int, int>> const expectedBridges = {};

  ASSERT_EQ(result.first, expectedCutPoints);
  ASSERT_EQ(result.second, expectedBridges);
}

TEST(CutPointsAndBridgesTest, ComplexGraph) {
  int const vertices = 7;
  int const edges = 7;
  std::vector<std::pair<int, int>> const edgeList = {
      {1, 2}, {1, 3}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}};

  pair<set<int>, vector<pair<int, int>>> const result =
      Answer(vertices, edges, edgeList);
  set<int> expectedCutPoints = {3, 4, 5, 6};
  vector<pair<int, int>> const expectedBridges = {
      {3, 4}, {4, 5}, {5, 6}, {6, 7}};

  ASSERT_EQ(result.first, expectedCutPoints);
  ASSERT_EQ(result.second, expectedBridges);
}

TEST(CutPointsAndBridgesTest, TwoDisconnectedComponents) {
  int const vertices = 6;
  int const edges = 4;
  std::vector<std::pair<int, int>> const edgeList = {
      {1, 2}, {2, 3}, {4, 5}, {5, 6}};

  pair<set<int>, vector<pair<int, int>>> const result =
      Answer(vertices, edges, edgeList);
  set<int> const expectedCutPoints = {2, 5};
  vector<pair<int, int>> const expectedBridges = {
      {1, 2}, {2, 3}, {4, 5}, {5, 6}};

  ASSERT_EQ(result.first, expectedCutPoints);
  ASSERT_EQ(result.second, expectedBridges);
}

TEST(CutPointsAndBridgesTest, StarTopology) {
  int const vertices = 5;
  int const edges = 4;
  std::vector<std::pair<int, int>> const edgeList = {
      {1, 2}, {1, 3}, {1, 4}, {1, 5}};

  pair<set<int>, vector<pair<int, int>>> const result =
      Answer(vertices, edges, edgeList);
  set<int> const expectedCutPoints = {1};
  vector<pair<int, int>> const expectedBridges = {
      {1, 2}, {1, 3}, {1, 4}, {1, 5}};

  ASSERT_EQ(result.first, expectedCutPoints);
  ASSERT_EQ(result.second, expectedBridges);
}

TEST(CutPointsAndBridgesTest, CycleGraph) {
  int const vertices = 5;
  int const edges = 5;
  std::vector<std::pair<int, int>> const edgeList = {
      {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 1}};

  pair<set<int>, vector<pair<int, int>>> const result =
      Answer(vertices, edges, edgeList);
  set<int> const expectedCutPoints = {};
  vector<pair<int, int>> const expectedBridges = {};

  ASSERT_EQ(result.first, expectedCutPoints);
  ASSERT_EQ(result.second, expectedBridges);
}

TEST(CutPointsAndBridgesTest, SingleBridgeInComplexGraph) {
  int const vertices = 8;
  int const edges = 8;
  std::vector<std::pair<int, int>> const edgeList = {
      {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}, {7, 8}, {5, 8}};

  pair<set<int>, vector<pair<int, int>>> const result =
      Answer(vertices, edges, edgeList);
  set<int> const expectedCutPoints = {2, 3, 4, 5};
  vector<pair<int, int>> const expectedBridges = {
      {1, 2}, {2, 3}, {3, 4}, {4, 5}};

  ASSERT_EQ(result.first, expectedCutPoints);
  ASSERT_EQ(result.second, expectedBridges);
}

TEST(CutPointsAndBridgesTest, LargeGraph) {
  int const vertices = 10;
  int const edges = 9;
  std::vector<std::pair<int, int>> const edgeList = {
      {1, 2}, {1, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}, {7, 8}, {8, 9}, {9, 10}};

  pair<set<int>, vector<pair<int, int>>> const result =
      Answer(vertices, edges, edgeList);
  set<int> const expectedCutPoints = {1, 3, 4, 5, 6, 7, 8, 9};
  vector<pair<int, int>> const expectedBridges = {
      {1, 2}, {1, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}, {7, 8}, {8, 9}, {9, 10}};

  ASSERT_EQ(result.first, expectedCutPoints);
  ASSERT_EQ(result.second, expectedBridges);
}