
#include <gtest/gtest.h>

#include "graph.hpp"
#include "stack.hpp"

using namespace algo;

TEST(StackTest, Simple) {
  Stack stack;
  stack.Push(1);              // Stack [1]
  ASSERT_EQ(stack.Pop(), 1);  // Stack []
  stack.Push(1);              // Stack [1]
  stack.Push(2);              // Stack [1, 2]
  ASSERT_EQ(stack.Pop(), 2);  // Stack [1]
  ASSERT_EQ(stack.Pop(), 1);  // Stack []
  stack.Push(1);              // Stack [1]
  stack.Push(2);              // Stack [1, 2]
  ASSERT_EQ(stack.Pop(), 2);  // Stack [1]
  stack.Push(3);              // Stack [1, 3]
  ASSERT_EQ(stack.Pop(), 3);  // Stack [1]
  ASSERT_EQ(stack.Pop(), 1);  // Stack []
}

TEST(MinStackTest, Simple) {
  MinStack stack;
  stack.Push(1);  // Stack [1]
  ASSERT_EQ(stack.GetMin(), 1);
  ASSERT_EQ(stack.Pop(), 1);  // Stack []
  stack.Push(1);              // Stack [1]
  stack.Push(2);              // Stack [1, 2]
  ASSERT_EQ(stack.GetMin(), 1);
  ASSERT_EQ(stack.Pop(), 2);  // Stack [1]
  ASSERT_EQ(stack.Pop(), 1);  // Stack []
  stack.Push(1);              // Stack [1]
  stack.Push(2);              // Stack [1, 2]
  ASSERT_EQ(stack.GetMin(), 1);
  ASSERT_EQ(stack.Pop(), 2);  // Stack [1]
  stack.Push(3);              // Stack [1, 3]
  ASSERT_EQ(stack.GetMin(), 1);
  ASSERT_EQ(stack.Pop(), 3);  // Stack [1]
  ASSERT_EQ(stack.Pop(), 1);  // Stack []
}

// МОСТЫ

// Тест для поиска мостов
TEST(GraphTest, getBridges) {
  Graph graph(5, 0, false);
  graph.addEdge(1, 2, 0);
  graph.addEdge(1, 3, 0);
  graph.addEdge(3, 4, 0);
  graph.addEdge(4, 5, 0);

  auto bridges = graph.getBridges();

  // Ожидаем следующие мосты
  std::vector<std::pair<int, int>> expectedBridges = {
      {1, 2}, {1, 3}, {3, 4}, {4, 5}};

  EXPECT_EQ(bridges.size(), expectedBridges.size());
  for (const auto& bridge : expectedBridges) {
    EXPECT_NE(std::find(bridges.begin(), bridges.end(), bridge), bridges.end());
  }
}

// Тест для поиска точек сочленения
TEST(GraphTest, getArticulationPoints) {
  Graph graph(5, 0, false);
  graph.addEdge(1, 2, 0);
  graph.addEdge(1, 3, 0);
  graph.addEdge(3, 4, 0);
  graph.addEdge(4, 5, 0);

  auto articulationPoints = graph.getArticulationPoints();

  // Ожидаем следующие точки сочленения
  std::vector<int> expectedPoints = {1, 3, 4};

  EXPECT_EQ(articulationPoints.size(), expectedPoints.size());
  for (int point : expectedPoints) {
    EXPECT_NE(
        std::find(articulationPoints.begin(), articulationPoints.end(), point),
        articulationPoints.end());
  }
}

// Тест для графа без мостов
TEST(GraphTest, NoBridges) {
  Graph graph(4, 0, false);
  graph.addEdge(1, 2, 0);
  graph.addEdge(2, 3, 0);
  graph.addEdge(3, 4, 0);
  graph.addEdge(4, 1, 0);

  auto bridges = graph.getBridges();

  EXPECT_TRUE(bridges.empty());
}

// Тест для графа без точек сочленения
TEST(GraphTest, NoArticulationPoints) {
  Graph graph(4, 0, false);
  graph.addEdge(1, 2, 0);
  graph.addEdge(2, 3, 0);
  graph.addEdge(3, 4, 0);
  graph.addEdge(4, 1, 0);

  auto articulationPoints = graph.getArticulationPoints();

  EXPECT_TRUE(articulationPoints.empty());
}
