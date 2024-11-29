
#include <gtest/gtest.h>

#include "bellman_ford.hpp"

TEST(Test_BellmanFord, Simple_Test_1) {
  WeightedGraph<char> graph;

  ASSERT_THROW(BellmanFord('A', graph), std::invalid_argument);
}

TEST(Test_BellmanFord, Simple_Test_2) {
  WeightedGraph<char> graph;

  graph.AddVertex('A');

  auto result = BellmanFord('A', graph);
  std::vector<MinPath<char>> expected;

  ASSERT_EQ(result, expected);
}

TEST(Test_BellmanFord, Simple_Test_3) {
  WeightedGraph<char> graph;

  graph.AddVertex('A');
  graph.AddVertex('B');

  graph.AddWeightedEdge('A', 'B', -1);
  graph.AddWeightedEdge('B', 'A', -1);

  ASSERT_THROW(BellmanFord('A', graph), std::invalid_argument);
}

TEST(Test_BellmanFord, Simple_Test_4) {
  WeightedGraph<char> graph;

  graph.AddVertex('A');
  graph.AddVertex('B');
  graph.AddVertex('C');

  graph.AddWeightedEdge('A', 'B', -1);
  graph.AddWeightedEdge('A', 'C', 2);
  graph.AddWeightedEdge('B', 'C', 2);

  auto result = BellmanFord('A', graph);
  std::vector<MinPath<char>> expected;

  expected.push_back(MinPath<char>({'A', 'B'}, -1));
  expected.push_back(MinPath<char>({'A', 'B', 'C'}, 1));

  ASSERT_EQ(result, expected);
}

TEST(Test_BellmanFord, Simple_Test_5) {
  WeightedGraph<char> graph(false);

  graph.AddVertex('A');
  graph.AddVertex('B');
  graph.AddVertex('C');

  graph.AddWeightedEdge('A', 'B', 1);
  graph.AddWeightedEdge('A', 'C', 4);
  graph.AddWeightedEdge('B', 'C', 2);

  auto result = BellmanFord('A', graph);
  std::vector<MinPath<char>> expected;

  expected.push_back(MinPath<char>({'A', 'B'}, 1));
  expected.push_back(MinPath<char>({'A', 'B', 'C'}, 3));

  ASSERT_EQ(result, expected);
}

TEST(Test_BellmanFord, Simple_Test_6) {
  WeightedGraph<char> graph(false);

  graph.AddVertex('A');
  graph.AddVertex('B');
  graph.AddVertex('C');

  graph.AddWeightedEdge('A', 'B', -1);
  graph.AddWeightedEdge('A', 'C', 2);
  graph.AddWeightedEdge('B', 'C', 2);

  ASSERT_THROW(BellmanFord('A', graph), std::invalid_argument);
}

TEST(Test_BellmanFord, Simple_Test_7) {
  WeightedGraph<char> graph;

  graph.AddVertex('A');
  graph.AddVertex('B');
  graph.AddVertex('S');

  graph.AddWeightedEdge('A', 'B', -1);
  graph.AddWeightedEdge('B', 'A', 2);
  graph.AddWeightedEdge('S', 'A', 0);
  graph.AddWeightedEdge('S', 'B', 0);

  auto result = BellmanFord('S', graph);
  std::vector<MinPath<char>> expected;

  expected.push_back(MinPath<char>({'S', 'A'}, 0));
  expected.push_back(MinPath<char>({'S', 'A', 'B'}, -1));

  ASSERT_EQ(result, expected);
}

TEST(Test_BellmanFord, Test_1) {
  WeightedGraph<char> graph;

  graph.AddVertex('A');
  graph.AddVertex('B');
  graph.AddVertex('C');
  graph.AddVertex('D');
  graph.AddVertex('E');

  graph.AddWeightedEdge('A', 'B', 2);
  graph.AddWeightedEdge('A', 'C', -1);
  graph.AddWeightedEdge('B', 'C', 1);
  graph.AddWeightedEdge('B', 'D', 3);
  graph.AddWeightedEdge('C', 'D', 4);
  graph.AddWeightedEdge('C', 'E', 2);
  graph.AddWeightedEdge('D', 'E', -3);

  auto result = BellmanFord('A', graph);
  std::vector<MinPath<char>> expected;

  expected.push_back(MinPath<char>({'A', 'B'}, 2));
  expected.push_back(MinPath<char>({'A', 'C'}, -1));
  expected.push_back(MinPath<char>({'A', 'C', 'D'}, 3));
  expected.push_back(MinPath<char>({'A', 'C', 'D', 'E'}, 0));

  ASSERT_EQ(result, expected);
}

TEST(Test_BellmanFord, Test_2) {
  WeightedGraph<char> graph;

  graph.AddVertex('A');
  graph.AddVertex('B');
  graph.AddVertex('C');
  graph.AddVertex('D');
  graph.AddVertex('E');
  graph.AddVertex('F');
  graph.AddVertex('G');

  graph.AddWeightedEdge('A', 'B', 5);
  graph.AddWeightedEdge('A', 'C', 2);
  graph.AddWeightedEdge('B', 'C', 1);
  graph.AddWeightedEdge('B', 'D', 3);
  graph.AddWeightedEdge('C', 'E', -2);
  graph.AddWeightedEdge('C', 'F', 4);
  graph.AddWeightedEdge('D', 'E', 2);
  graph.AddWeightedEdge('D', 'G', 6);
  graph.AddWeightedEdge('E', 'F', 3);
  graph.AddWeightedEdge('E', 'G', -4);
  graph.AddWeightedEdge('F', 'G', 1);
  graph.AddWeightedEdge('F', 'C', -7);
  graph.AddWeightedEdge('G', 'A', 8);

  ASSERT_THROW(BellmanFord('A', graph), std::invalid_argument);
}

TEST(Test_BellmanFord, Test_3) {
  WeightedGraph<int> graph;

  graph.AddVertex(0);
  graph.AddVertex(1);
  graph.AddVertex(2);
  graph.AddVertex(3);
  graph.AddVertex(4);
  graph.AddVertex(5);
  graph.AddVertex(6);
  graph.AddVertex(7);
  graph.AddVertex(8);
  graph.AddVertex(9);
  graph.AddVertex(10);
  graph.AddVertex(11);

  graph.AddWeightedEdge(0, 1, 1);
  graph.AddWeightedEdge(1, 2, 4);
  graph.AddWeightedEdge(2, 3, 5);
  graph.AddWeightedEdge(4, 0, 7);
  graph.AddWeightedEdge(5, 1, 2);
  graph.AddWeightedEdge(6, 2, 3);
  graph.AddWeightedEdge(3, 7, -3);
  graph.AddWeightedEdge(5, 4, 5);
  graph.AddWeightedEdge(5, 6, -2);
  graph.AddWeightedEdge(6, 7, 7);
  graph.AddWeightedEdge(8, 4, -6);
  graph.AddWeightedEdge(5, 9, 4);
  graph.AddWeightedEdge(6, 10, 6);
  graph.AddWeightedEdge(7, 11, 4);
  graph.AddWeightedEdge(9, 8, 3);
  graph.AddWeightedEdge(9, 10, 1);
  graph.AddWeightedEdge(10, 11, 2);

  auto result = BellmanFord(5, graph);
  std::vector<MinPath<int>> expected;

  expected.push_back(MinPath<int>({5, 9, 8, 4, 0}, 8));
  expected.push_back(MinPath<int>({5, 1}, 2));
  expected.push_back(MinPath<int>({5, 6, 2}, 1));
  expected.push_back(MinPath<int>({5, 6, 2, 3}, 6));
  expected.push_back(MinPath<int>({5, 9, 8, 4}, 1));
  expected.push_back(MinPath<int>({5, 6}, -2));
  expected.push_back(MinPath<int>({5, 6, 2, 3, 7}, 3));
  expected.push_back(MinPath<int>({5, 9, 8}, 7));
  expected.push_back(MinPath<int>({5, 9}, 4));
  expected.push_back(MinPath<int>({5, 6, 10}, 4));
  expected.push_back(MinPath<int>({5, 6, 10, 11}, 6));

  ASSERT_EQ(result, expected);
}

TEST(Test_BellmanFord, Test_4) {
  WeightedGraph<char> graph;

  graph.AddVertex('A');
  graph.AddVertex('B');
  graph.AddVertex('C');
  graph.AddVertex('D');
  graph.AddVertex('E');
  graph.AddVertex('F');
  graph.AddVertex('G');
  graph.AddVertex('H');

  graph.AddWeightedEdge('A', 'B', 3);
  graph.AddWeightedEdge('B', 'C', -2);
  graph.AddWeightedEdge('A', 'C', 2);
  graph.AddWeightedEdge('D', 'E', 5);
  graph.AddWeightedEdge('D', 'F', 4);
  graph.AddWeightedEdge('E', 'F', -4);
  graph.AddWeightedEdge('E', 'G', -3);
  graph.AddWeightedEdge('G', 'F', -2);
  graph.AddWeightedEdge('F', 'G', 5);

  auto result = BellmanFord('A', graph);
  std::vector<MinPath<char>> expected;

  expected.push_back(MinPath<char>({'A', 'B'}, 3));
  expected.push_back(MinPath<char>({'A', 'B', 'C'}, 1));
  expected.push_back(MinPath<char>({'D'}, INF));
  expected.push_back(MinPath<char>({'E'}, INF));
  expected.push_back(MinPath<char>({'F'}, INF));
  expected.push_back(MinPath<char>({'G'}, INF));
  expected.push_back(MinPath<char>({'H'}, INF));

  ASSERT_EQ(result, expected);
}

TEST(Test_BellmanFord, Test_5) {
  WeightedGraph<char> graph;

  graph.AddVertex('A');
  graph.AddVertex('B');
  graph.AddVertex('C');
  graph.AddVertex('D');
  graph.AddVertex('E');
  graph.AddVertex('F');
  graph.AddVertex('G');
  graph.AddVertex('H');

  graph.AddWeightedEdge('A', 'B', 3);
  graph.AddWeightedEdge('B', 'C', -2);
  graph.AddWeightedEdge('A', 'C', 2);
  graph.AddWeightedEdge('D', 'E', 5);
  graph.AddWeightedEdge('D', 'F', 4);
  graph.AddWeightedEdge('E', 'F', -4);
  graph.AddWeightedEdge('E', 'G', -3);
  graph.AddWeightedEdge('G', 'F', -2);
  graph.AddWeightedEdge('F', 'G', 5);

  auto result = BellmanFord('D', graph);
  std::vector<MinPath<char>> expected;

  expected.push_back(MinPath<char>({'A'}, INF));
  expected.push_back(MinPath<char>({'B'}, INF));
  expected.push_back(MinPath<char>({'C'}, INF));
  expected.push_back(MinPath<char>({'D', 'E'}, 5));
  expected.push_back(MinPath<char>({'D', 'E', 'G', 'F'}, 0));
  expected.push_back(MinPath<char>({'D', 'E', 'G'}, 2));
  expected.push_back(MinPath<char>({'H'}, INF));

  ASSERT_EQ(result, expected);
}
