
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
  std::vector<MinPath<char>> expected{};

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

  expected.push_back(MinPath<char>({'A'}, std::numeric_limits<int>::max()));
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