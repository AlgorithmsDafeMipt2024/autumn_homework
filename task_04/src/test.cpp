
#include <gtest/gtest.h>

#include "graph.hpp"
#include "util.hpp"

using namespace algo;

TEST(TopologySort, Simple) {
  ASSERT_EQ(1, 1);  // Stack []
}

void CheckDistances(const std::vector<int>& actual,
                    const std::vector<int>& expected) {
  EXPECT_EQ(actual.size(), expected.size());
  for (size_t i = 0; i < expected.size(); ++i) {
    EXPECT_EQ(actual[i], expected[i]);
  }
}

// Тест: стандартный граф с положительными весами
TEST(DijkstraTest, StandardGraph) {
  Graph graph(6, 0, false);
  graph.AddEdge(1, 2, 7);
  graph.AddEdge(1, 3, 9);
  graph.AddEdge(1, 6, 14);
  graph.AddEdge(2, 3, 10);
  graph.AddEdge(2, 4, 15);
  graph.AddEdge(3, 4, 11);
  graph.AddEdge(3, 6, 2);
  graph.AddEdge(4, 5, 6);
  graph.AddEdge(5, 6, 9);

  auto distances = FindWays(graph, 1);

  // Ожидаемые минимальные расстояния от вершины 1
  std::vector<int> expected = {0, 7, 9, 20, 20, 11};
  CheckDistances(distances, expected);
}

// Тест: граф с недостижимыми вершинами
TEST(DijkstraTest, GraphWithUnreachableNodes) {
  Graph graph(4, 0, false);
  graph.AddEdge(1, 2, 5);
  graph.AddEdge(2, 3, 10);
  // Вершина 4 изолирована

  auto distances = FindWays(graph, 1);

  // Ожидаемые минимальные расстояния от вершины 1
  std::vector<int> expected = {0, 5, 15, std::numeric_limits<int>::max()};
  CheckDistances(distances, expected);
}

// Тест: граф с петлями
TEST(DijkstraTest, GraphWithSelfLoops) {
  Graph graph(3, 0, false);
  graph.AddEdge(1, 1, 10);  // Петля на вершине 1
  graph.AddEdge(1, 2, 5);
  graph.AddEdge(2, 3, 10);

  auto distances = FindWays(graph, 1);

  // Ожидаемые минимальные расстояния от вершины 1
  std::vector<int> expected = {0, 5, 15};
  CheckDistances(distances, expected);
}

// Тест: граф с одной вершиной
TEST(DijkstraTest, SingleNodeGraph) {
  Graph graph(1, 0, false);

  auto distances = FindWays(graph, 1);

  // Ожидаемые минимальные расстояния от вершины 1
  std::vector<int> expected = {0};
  CheckDistances(distances, expected);
}

// Тест: граф без рёбер
TEST(DijkstraTest, GraphWithoutEdges) {
  Graph graph(4, 0, false);

  auto distances = FindWays(graph, 1);

  // Ожидаемые минимальные расстояния от вершины 1
  std::vector<int> expected = {0, std::numeric_limits<int>::max(),
                               std::numeric_limits<int>::max(),
                               std::numeric_limits<int>::max()};
  CheckDistances(distances, expected);
}