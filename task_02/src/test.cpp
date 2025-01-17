#include <gtest/gtest.h>

#include "find_bridges.hpp"
#include "find_joint_vertices.hpp"

TEST(Test_FindBridges, Simple_Test_1) {
  Graph<int> graph(false);

  auto result = FindBridges(graph);
  std::vector<Edge<int>> expected;

  ASSERT_EQ(result, expected);
}

TEST(Test_FindBridges, Simple_Test_2) {
  Graph<char> graph(false);

  graph.AddVertex('A');

  auto result = FindBridges(graph);
  std::vector<Edge<char>> expected;

  ASSERT_EQ(result, expected);
}

TEST(Test_FindBridges, Simple_Test_3) {
  Graph<char> graph(false);

  graph.AddVertex('A');
  graph.AddVertex('B');

  graph.AddEdge('A', 'B');

  auto result = FindBridges(graph);
  std::vector<Edge<char>> expected{{'A', 'B'}};

  ASSERT_EQ(result, expected);
}

TEST(Test_FindBridges, Simple_Test_4) {
  Graph<char> graph(false);

  graph.AddVertex('A');
  graph.AddVertex('B');
  graph.AddVertex('C');

  graph.AddEdge('A', 'B');
  graph.AddEdge('A', 'C');
  graph.AddEdge('B', 'C');

  auto result = FindBridges(graph);
  std::vector<Edge<char>> expected;

  ASSERT_EQ(result, expected);
}

TEST(Test_FindBridges, Simple_Test_5) {
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

TEST(Test_FindBridges, Test_1) {
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

TEST(Test_FindBridges, Test_2) {
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
  std::vector<Edge<char>> expected;

  ASSERT_EQ(result, expected);
}

TEST(Test_FindBridges, Test_3) {
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

TEST(Test_FindBridges, Test_4) {
  Graph<char> graph(false);

  graph.AddVertex('A');
  graph.AddVertex('B');
  graph.AddVertex('C');
  graph.AddVertex('D');
  graph.AddVertex('E');

  graph.AddEdge('A', 'D');
  graph.AddEdge('A', 'C');
  graph.AddEdge('C', 'D');
  graph.AddEdge('E', 'D');
  graph.AddEdge('B', 'D');
  graph.AddEdge('E', 'B');

  auto result = FindBridges(graph);
  std::vector<Edge<char>> expected;

  ASSERT_EQ(result, expected);
}

TEST(Test_FindBridges, Test_5) {
  Graph<char> graph(false);

  graph.AddVertex('A');
  graph.AddVertex('B');
  graph.AddVertex('C');
  graph.AddVertex('D');
  graph.AddVertex('E');
  graph.AddVertex('F');

  graph.AddEdge('A', 'B');
  graph.AddEdge('A', 'C');
  graph.AddEdge('B', 'C');
  graph.AddEdge('C', 'D');
  graph.AddEdge('C', 'E');
  graph.AddEdge('E', 'F');

  auto result = FindBridges(graph);
  std::vector<Edge<char>> expected{{'C', 'D'}, {'E', 'F'}, {'C', 'E'}};

  ASSERT_EQ(result, expected);
}

TEST(Test_FindJointVertices, Simple_Test_1) {
  Graph<int> graph(false);

  auto result = FindJointVertices(graph);
  std::vector<int> expected;

  ASSERT_EQ(result, expected);
}

TEST(Test_FindJointVertices, Simple_Test_2) {
  Graph<char> graph(false);

  graph.AddVertex('A');

  auto result = FindJointVertices(graph);
  std::vector<char> expected;

  ASSERT_EQ(result, expected);
}

TEST(Test_FindJointVertices, Simple_Test_3) {
  Graph<char> graph(false);

  graph.AddVertex('A');
  graph.AddVertex('B');

  graph.AddEdge('A', 'B');

  auto result = FindJointVertices(graph);
  std::vector<char> expected;

  ASSERT_EQ(result, expected);
}

TEST(Test_FindJointVertices, Simple_Test_4) {
  Graph<char> graph(false);

  graph.AddVertex('A');
  graph.AddVertex('B');
  graph.AddVertex('C');

  graph.AddEdge('A', 'B');
  graph.AddEdge('A', 'C');
  graph.AddEdge('B', 'C');

  auto result = FindJointVertices(graph);
  std::vector<char> expected;

  ASSERT_EQ(result, expected);
}

TEST(Test_FindJointVertices, Simple_Test_5) {
  Graph<char> graph(false);

  graph.AddVertex('A');
  graph.AddVertex('B');
  graph.AddVertex('C');

  graph.AddEdge('A', 'B');
  graph.AddEdge('A', 'C');

  auto result = FindJointVertices(graph);
  std::vector<char> expected{'A'};

  ASSERT_EQ(result, expected);
}

TEST(Test_FindJointVertices, Test_1) {
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

  auto result = FindJointVertices(graph);
  std::vector<char> expected{'B', 'C', 'A'};

  ASSERT_EQ(result, expected);
}

TEST(Test_FindJointVertices, Test_2) {
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

  auto result = FindJointVertices(graph);
  std::vector<char> expected;

  ASSERT_EQ(result, expected);
}

TEST(Test_FindJointVertices, Test_3) {
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

  auto result = FindJointVertices(graph);
  std::vector<char> expected{'K', 'B', 'C', 'D', 'I', 'J'};

  ASSERT_EQ(result, expected);
}

TEST(Test_FindJointVertices, Test_4) {
  Graph<int> graph(false);

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

  graph.AddEdge(0, 1);
  graph.AddEdge(0, 2);
  graph.AddEdge(1, 2);
  graph.AddEdge(1, 3);
  graph.AddEdge(2, 4);
  graph.AddEdge(3, 4);
  graph.AddEdge(3, 5);
  graph.AddEdge(4, 6);
  graph.AddEdge(5, 7);
  graph.AddEdge(6, 8);
  graph.AddEdge(7, 8);
  graph.AddEdge(8, 9);

  auto result = FindJointVertices(graph);
  std::vector<int> expected{8};

  ASSERT_EQ(result, expected);
}

TEST(Test_FindJointVertices, Test_5) {
  Graph<char> graph(false);

  graph.AddVertex('A');
  graph.AddVertex('B');
  graph.AddVertex('C');
  graph.AddVertex('D');
  graph.AddVertex('E');

  graph.AddEdge('A', 'D');
  graph.AddEdge('A', 'C');
  graph.AddEdge('C', 'D');
  graph.AddEdge('E', 'D');
  graph.AddEdge('B', 'D');
  graph.AddEdge('E', 'B');

  auto result = FindJointVertices(graph);
  std::vector<char> expected{'D'};

  ASSERT_EQ(result, expected);
}