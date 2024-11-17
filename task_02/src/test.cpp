#include <gtest/gtest.h>

#include "find_bridges.hpp"
#include "find_joint_vertices.hpp"

TEST(Test_FindingBridges, Simple_Test_1) {
  Graph<int> graph(false);

  auto result = FindBridges(graph);
  std::vector<Edge<int>> expected{};

  ASSERT_EQ(result, expected);
}

TEST(Test_FindingBridges, Simple_Test_2) {
  Graph<char> graph(false);

  graph.AddVertex('A');

  auto result = FindBridges(graph);
  std::vector<Edge<char>> expected{};

  ASSERT_EQ(result, expected);
}

TEST(Test_FindingBridges, Simple_Test_3) {
  Graph<char> graph(false);

  graph.AddVertex('A');
  graph.AddVertex('B');

  graph.AddEdge('A', 'B');

  auto result = FindBridges(graph);
  std::vector<Edge<char>> expected{{'A', 'B'}};

  ASSERT_EQ(result, expected);
}

TEST(Test_FindingBridges, Simple_Test_4) {
  Graph<char> graph(false);

  graph.AddVertex('A');
  graph.AddVertex('B');
  graph.AddVertex('C');

  graph.AddEdge('A', 'B');
  graph.AddEdge('A', 'C');
  graph.AddEdge('B', 'C');

  auto result = FindBridges(graph);
  std::vector<Edge<char>> expected{};

  ASSERT_EQ(result, expected);
}

TEST(Test_FindingBridges, Simple_Test_5) {
  Graph<char> graph(false);

  graph.AddVertex('A');
  graph.AddVertex('B');
  graph.AddVertex('C');

  graph.AddEdge('A', 'B');
  graph.AddEdge('A', 'C');

  auto result = FindBridges(graph);
  std::vector<Edge<char>> expected{{'A', 'B'}, {'A', 'C'}};

  ASSERT_EQ(result, expected);
}

TEST(Test_FindingBridges, Test_1) {
  Graph<char> graph(false);

  graph.AddVertex('A');
  graph.AddVertex('B');
  graph.AddVertex('C');
  graph.AddVertex('D');
  graph.AddVertex('E');
  graph.AddVertex('F');
  graph.AddVertex('G');

  graph.AddEdge('A', 'B');
  graph.AddEdge('A', 'C');
  graph.AddEdge('C', 'D');
  graph.AddEdge('C', 'E');
  graph.AddEdge('D', 'E');
  graph.AddEdge('B', 'G');
  graph.AddEdge('B', 'F');

  auto result = FindBridges(graph);
  std::vector<Edge<char>> expected{
      {'B', 'G'}, {'B', 'F'}, {'A', 'B'}, {'A', 'C'}};

  ASSERT_EQ(result, expected);
}

TEST(Test_FindingBridges, Test_2) {
  Graph<char> graph(false);

  graph.AddVertex('A');
  graph.AddVertex('B');
  graph.AddVertex('C');
  graph.AddVertex('D');
  graph.AddVertex('E');
  graph.AddVertex('F');
  graph.AddVertex('G');

  graph.AddEdge('A', 'B');
  graph.AddEdge('A', 'C');
  graph.AddEdge('C', 'D');
  graph.AddEdge('C', 'E');
  graph.AddEdge('D', 'E');
  graph.AddEdge('B', 'G');
  graph.AddEdge('B', 'F');
  graph.AddEdge('G', 'F');
  graph.AddEdge('D', 'F');

  auto result = FindBridges(graph);
  std::vector<Edge<char>> expected{};

  ASSERT_EQ(result, expected);
}

TEST(Test_FindingBridges, Test_3) {
  Graph<char> graph(false);

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
  graph.AddVertex('K');
  graph.AddVertex('L');
  graph.AddVertex('M');

  graph.AddEdge('F', 'J');
  graph.AddEdge('F', 'D');
  graph.AddEdge('J', 'I');
  graph.AddEdge('J', 'A');
  graph.AddEdge('J', 'K');
  graph.AddEdge('I', 'M');
  graph.AddEdge('I', 'E');
  graph.AddEdge('A', 'H');
  graph.AddEdge('K', 'H');
  graph.AddEdge('K', 'G');
  graph.AddEdge('K', 'D');
  graph.AddEdge('D', 'C');
  graph.AddEdge('C', 'B');
  graph.AddEdge('B', 'L');

  auto result = FindBridges(graph);
  std::vector<Edge<char>> expected{
      {'K', 'G'}, {'B', 'L'}, {'C', 'B'}, {'D', 'C'},
      {'I', 'M'}, {'I', 'E'}, {'J', 'I'},
  };

  ASSERT_EQ(result, expected);
}