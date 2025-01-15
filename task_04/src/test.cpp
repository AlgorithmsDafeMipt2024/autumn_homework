#include <gtest/gtest.h>

#include "dijkstra.hpp"

TEST(Test_Dijkstra, Simple_Test_1) {
  WeightedGraph<int> graph;

  ASSERT_THROW(Dijkstra(4, graph), std::invalid_argument);
}

TEST(Test_Dijkstra, Simple_Test_2) {
  WeightedGraph<char> graph;

  graph.AddVertex('A');

  auto result = Dijkstra('A', graph);
  std::vector<MinPath<char>> expected;

  ASSERT_EQ(result, expected);
}

TEST(Test_Dijkstra, Simple_Test_3) {
  WeightedGraph<char> graph;

  graph.AddVertex('A');
  graph.AddVertex('B');
  graph.AddVertex('C');

  graph.AddWeightedEdge('A', 'B', 1);
  graph.AddWeightedEdge('A', 'C', 2);
  graph.AddWeightedEdge('B', 'C', -3);

  ASSERT_THROW(Dijkstra('B', graph), std::invalid_argument);
}

TEST(Test_Dijkstra, Simple_Test_4) {
  WeightedGraph<char> graph;

  graph.AddVertex('A');
  graph.AddVertex('B');

  graph.AddWeightedEdge('A', 'B', 1);

  auto result = Dijkstra('A', graph);
  std::vector<MinPath<char>> expected;

  expected.push_back(MinPath<char>({'A', 'B'}, 1));

  ASSERT_EQ(result, expected);
}

TEST(Test_Dijkstra, Simple_Test_5) {
  WeightedGraph<char> graph;

  graph.AddVertex('A');
  graph.AddVertex('B');
  graph.AddVertex('C');

  graph.AddWeightedEdge('A', 'B', 2);
  graph.AddWeightedEdge('A', 'C', 6);
  graph.AddWeightedEdge('B', 'C', 3);

  auto result = Dijkstra('A', graph);
  std::vector<MinPath<char>> expected;

  expected.push_back(MinPath<char>({'A', 'B'}, 2));
  expected.push_back(MinPath<char>({'A', 'B', 'C'}, 5));

  ASSERT_EQ(result, expected);
}

TEST(Test_Dijkstra, Simple_Test_6) {
  WeightedGraph<char> graph;

  graph.AddVertex('A');
  graph.AddVertex('B');
  graph.AddVertex('C');

  graph.AddWeightedEdge('A', 'B', 2);
  graph.AddWeightedEdge('A', 'C', 6);
  graph.AddWeightedEdge('B', 'C', 3);

  auto result = Dijkstra('B', graph);
  std::vector<MinPath<char>> expected;

  expected.push_back(MinPath<char>({'A'}, INF));
  expected.push_back(MinPath<char>({'B', 'C'}, 3));

  ASSERT_EQ(result, expected);
}

TEST(Test_Dijkstra, Simple_Test_7) {
  WeightedGraph<char> graph(false);

  graph.AddVertex('A');
  graph.AddVertex('B');
  graph.AddVertex('C');

  graph.AddWeightedEdge('A', 'B', 2);
  graph.AddWeightedEdge('A', 'C', 6);
  graph.AddWeightedEdge('B', 'C', 3);

  auto result = Dijkstra('B', graph);
  std::vector<MinPath<char>> expected;

  expected.push_back(MinPath<char>({'B', 'A'}, 2));
  expected.push_back(MinPath<char>({'B', 'C'}, 3));

  ASSERT_EQ(result, expected);
}

TEST(Test_Dijkstra, Simple_Test_8) {
  WeightedGraph<char> graph;

  graph.AddVertex('A');
  graph.AddVertex('B');
  graph.AddVertex('C');

  graph.AddWeightedEdge('A', 'B', 2);
  graph.AddWeightedEdge('A', 'C', 6);
  graph.AddWeightedEdge('B', 'C', 3);

  graph.AddVertex('D');
  graph.AddVertex('E');

  graph.AddWeightedEdge('D', 'E', 4);

  auto result = Dijkstra('A', graph);
  std::vector<MinPath<char>> expected;

  expected.push_back(MinPath<char>({'A', 'B'}, 2));
  expected.push_back(MinPath<char>({'A', 'B', 'C'}, 5));
  expected.push_back(MinPath<char>({'D'}, INF));
  expected.push_back(MinPath<char>({'E'}, INF));

  ASSERT_EQ(result, expected);
}

TEST(Test_Dijkstra, Simple_Test_9) {
  WeightedGraph<char> graph(false);

  graph.AddVertex('A');
  graph.AddVertex('B');
  graph.AddVertex('C');

  graph.AddWeightedEdge('A', 'B', 2);
  graph.AddWeightedEdge('A', 'C', 6);
  graph.AddWeightedEdge('B', 'C', 3);

  graph.AddVertex('D');
  graph.AddVertex('E');
  graph.AddVertex('F');

  graph.AddWeightedEdge('D', 'E', 1);
  graph.AddWeightedEdge('D', 'F', 9);
  graph.AddWeightedEdge('F', 'E', 3);

  auto result = Dijkstra('B', graph);
  std::vector<MinPath<char>> expected;

  expected.push_back(MinPath<char>({'B', 'A'}, 2));
  expected.push_back(MinPath<char>({'B', 'C'}, 3));
  expected.push_back(MinPath<char>({'D'}, INF));
  expected.push_back(MinPath<char>({'E'}, INF));
  expected.push_back(MinPath<char>({'F'}, INF));

  ASSERT_EQ(result, expected);
}

TEST(Test_Dijkstra, Test_1) {
  WeightedGraph<char> graph(false);

  graph.AddVertex('A');
  graph.AddVertex('B');
  graph.AddVertex('C');
  graph.AddVertex('D');
  graph.AddVertex('E');
  graph.AddVertex('F');

  graph.AddWeightedEdge('A', 'B', 6);
  graph.AddWeightedEdge('A', 'C', 3);
  graph.AddWeightedEdge('A', 'D', 2);
  graph.AddWeightedEdge('B', 'C', 3);
  graph.AddWeightedEdge('B', 'F', 4);
  graph.AddWeightedEdge('C', 'E', 2);
  graph.AddWeightedEdge('D', 'E', 5);
  graph.AddWeightedEdge('F', 'E', 1);

  auto result = Dijkstra('A', graph);
  std::vector<MinPath<char>> expected;

  expected.push_back(MinPath<char>({'A', 'C', 'B'}, 6));
  expected.push_back(MinPath<char>({'A', 'C'}, 3));
  expected.push_back(MinPath<char>({'A', 'D'}, 2));
  expected.push_back(MinPath<char>({'A', 'C', 'E'}, 5));
  expected.push_back(MinPath<char>({'A', 'C', 'E', 'F'}, 6));

  ASSERT_EQ(result, expected);
}

TEST(Test_Dijkstra, Test_2) {
  WeightedGraph<char> graph(false);

  graph.AddVertex('A');
  graph.AddVertex('B');
  graph.AddVertex('C');
  graph.AddVertex('D');
  graph.AddVertex('E');
  graph.AddVertex('F');
  graph.AddVertex('G');
  graph.AddVertex('H');
  graph.AddVertex('I');

  graph.AddWeightedEdge('E', 'B', 8);
  graph.AddWeightedEdge('C', 'D', 3);
  graph.AddWeightedEdge('E', 'G', 8);
  graph.AddWeightedEdge('C', 'F', 1);
  graph.AddWeightedEdge('E', 'D', 7);
  graph.AddWeightedEdge('A', 'C', 12);
  graph.AddWeightedEdge('G', 'H', 9);
  graph.AddWeightedEdge('G', 'I', 2);
  graph.AddWeightedEdge('H', 'I', 11);
  graph.AddWeightedEdge('D', 'F', 3);
  graph.AddWeightedEdge('F', 'H', 6);
  graph.AddWeightedEdge('A', 'B', 10);
  graph.AddWeightedEdge('E', 'H', 5);
  graph.AddWeightedEdge('C', 'B', 9);

  auto result = Dijkstra('A', graph);
  std::vector<MinPath<char>> expected;

  expected.push_back(MinPath<char>({'A', 'B'}, 10));
  expected.push_back(MinPath<char>({'A', 'C'}, 12));
  expected.push_back(MinPath<char>({'A', 'C', 'D'}, 15));
  expected.push_back(MinPath<char>({'A', 'B', 'E'}, 18));
  expected.push_back(MinPath<char>({'A', 'C', 'F'}, 13));
  expected.push_back(MinPath<char>({'A', 'B', 'E', 'G'}, 26));
  expected.push_back(MinPath<char>({'A', 'C', 'F', 'H'}, 19));
  expected.push_back(MinPath<char>({'A', 'B', 'E', 'G', 'I'}, 28));

  ASSERT_EQ(result, expected);
}

TEST(Test_Dijkstra, Test_3) {
  WeightedGraph<char> graph;

  graph.AddVertex('A');
  graph.AddVertex('B');
  graph.AddVertex('C');
  graph.AddVertex('D');
  graph.AddVertex('E');
  graph.AddVertex('F');
  graph.AddVertex('G');
  graph.AddVertex('H');
  graph.AddVertex('I');
  graph.AddVertex('J');

  graph.AddWeightedEdge('A', 'B', 12);
  graph.AddWeightedEdge('A', 'C', 7);
  graph.AddWeightedEdge('A', 'D', 10);
  graph.AddWeightedEdge('B', 'E', 6);
  graph.AddWeightedEdge('B', 'F', 10);
  graph.AddWeightedEdge('B', 'C', 9);
  graph.AddWeightedEdge('C', 'E', 8);
  graph.AddWeightedEdge('C', 'F', 13);
  graph.AddWeightedEdge('C', 'G', 15);
  graph.AddWeightedEdge('D', 'C', 2);
  graph.AddWeightedEdge('D', 'G', 13);
  graph.AddWeightedEdge('G', 'F', 5);
  graph.AddWeightedEdge('G', 'I', 6);
  graph.AddWeightedEdge('E', 'H', 14);
  graph.AddWeightedEdge('F', 'E', 16);
  graph.AddWeightedEdge('F', 'H', 4);
  graph.AddWeightedEdge('F', 'I', 11);
  graph.AddWeightedEdge('H', 'I', 7);
  graph.AddWeightedEdge('H', 'J', 13);
  graph.AddWeightedEdge('I', 'J', 8);

  auto result = Dijkstra('A', graph);
  std::vector<MinPath<char>> expected;

  expected.push_back(MinPath<char>({'A', 'B'}, 12));
  expected.push_back(MinPath<char>({'A', 'C'}, 7));
  expected.push_back(MinPath<char>({'A', 'D'}, 10));
  expected.push_back(MinPath<char>({'A', 'C', 'E'}, 15));
  expected.push_back(MinPath<char>({'A', 'C', 'F'}, 20));
  expected.push_back(MinPath<char>({'A', 'C', 'G'}, 22));
  expected.push_back(MinPath<char>({'A', 'C', 'F', 'H'}, 24));
  expected.push_back(MinPath<char>({'A', 'C', 'G', 'I'}, 28));
  expected.push_back(MinPath<char>({'A', 'C', 'G', 'I', 'J'}, 36));

  ASSERT_EQ(result, expected);
}

TEST(Test_Dijkstra, Test_4) {
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

  graph.AddWeightedEdge(0, 1, 7);
  graph.AddWeightedEdge(0, 2, 2);
  graph.AddWeightedEdge(0, 3, 5);
  graph.AddWeightedEdge(1, 2, 3);
  graph.AddWeightedEdge(1, 4, 6);
  graph.AddWeightedEdge(2, 3, 1);
  graph.AddWeightedEdge(2, 5, 8);
  graph.AddWeightedEdge(3, 4, 4);
  graph.AddWeightedEdge(3, 6, 9);
  graph.AddWeightedEdge(4, 5, 2);
  graph.AddWeightedEdge(4, 7, 1);
  graph.AddWeightedEdge(5, 6, 7);
  graph.AddWeightedEdge(5, 8, 3);
  graph.AddWeightedEdge(6, 7, 5);
  graph.AddWeightedEdge(6, 9, 4);
  graph.AddWeightedEdge(7, 8, 6);
  graph.AddWeightedEdge(8, 9, 10);

  auto result = Dijkstra(0, graph);
  std::vector<MinPath<int>> expected;

  expected.push_back(MinPath<int>({0, 1}, 7));
  expected.push_back(MinPath<int>({0, 2}, 2));
  expected.push_back(MinPath<int>({0, 2, 3}, 3));
  expected.push_back(MinPath<int>({0, 2, 3, 4}, 7));
  expected.push_back(MinPath<int>({0, 2, 3, 4, 5}, 9));
  expected.push_back(MinPath<int>({0, 2, 3, 6}, 12));
  expected.push_back(MinPath<int>({0, 2, 3, 4, 7}, 8));
  expected.push_back(MinPath<int>({0, 2, 3, 4, 5, 8}, 12));
  expected.push_back(MinPath<int>({0, 2, 3, 6, 9}, 16));

  ASSERT_EQ(result, expected);
}

TEST(Test_Dijkstra, Test_5) {
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

  graph.AddWeightedEdge(0, 1, 4);
  graph.AddWeightedEdge(0, 2, 2);
  graph.AddWeightedEdge(1, 3, 5);
  graph.AddWeightedEdge(2, 3, 1);
  graph.AddWeightedEdge(1, 2, 3);
  graph.AddWeightedEdge(3, 0, 6);
  graph.AddWeightedEdge(2, 0, 7);
  graph.AddWeightedEdge(4, 5, 7);
  graph.AddWeightedEdge(5, 6, 3);
  graph.AddWeightedEdge(6, 7, 2);
  graph.AddWeightedEdge(7, 8, 9);
  graph.AddWeightedEdge(8, 9, 6);
  graph.AddWeightedEdge(4, 6, 1);
  graph.AddWeightedEdge(5, 8, 4);
  graph.AddWeightedEdge(7, 5, 5);
  graph.AddWeightedEdge(9, 4, 8);

  auto result = Dijkstra(0, graph);
  std::vector<MinPath<int>> expected;

  expected.push_back(MinPath<int>({0, 1}, 4));
  expected.push_back(MinPath<int>({0, 2}, 2));
  expected.push_back(MinPath<int>({0, 2, 3}, 3));
  expected.push_back(MinPath<int>({4}, INF));
  expected.push_back(MinPath<int>({5}, INF));
  expected.push_back(MinPath<int>({6}, INF));
  expected.push_back(MinPath<int>({7}, INF));
  expected.push_back(MinPath<int>({8}, INF));
  expected.push_back(MinPath<int>({9}, INF));

  ASSERT_EQ(result, expected);
}

TEST(Test_Dijkstra, Test_6) {
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

  graph.AddWeightedEdge(0, 1, 4);
  graph.AddWeightedEdge(0, 2, 2);
  graph.AddWeightedEdge(1, 3, 5);
  graph.AddWeightedEdge(2, 3, 1);
  graph.AddWeightedEdge(1, 2, 3);
  graph.AddWeightedEdge(3, 0, 6);
  graph.AddWeightedEdge(2, 0, 7);
  graph.AddWeightedEdge(4, 5, 7);
  graph.AddWeightedEdge(5, 6, 3);
  graph.AddWeightedEdge(6, 7, 2);
  graph.AddWeightedEdge(7, 8, 9);
  graph.AddWeightedEdge(8, 9, 6);
  graph.AddWeightedEdge(4, 6, 1);
  graph.AddWeightedEdge(5, 8, 4);
  graph.AddWeightedEdge(7, 5, 5);
  graph.AddWeightedEdge(9, 4, 8);

  auto result = Dijkstra(4, graph);
  std::vector<MinPath<int>> expected;

  expected.push_back(MinPath<int>({0}, INF));
  expected.push_back(MinPath<int>({1}, INF));
  expected.push_back(MinPath<int>({2}, INF));
  expected.push_back(MinPath<int>({3}, INF));
  expected.push_back(MinPath<int>({4, 5}, 7));
  expected.push_back(MinPath<int>({4, 6}, 1));
  expected.push_back(MinPath<int>({4, 6, 7}, 3));
  expected.push_back(MinPath<int>({4, 5, 8}, 11));
  expected.push_back(MinPath<int>({4, 5, 8, 9}, 17));

  ASSERT_EQ(result, expected);
}