#include <gtest/gtest.h>

#include "topological_sort.hpp"

TEST(Test_TopologicalSort, Simple_Test_1) {
  Graph<int> graph;

  auto result = TopologicalSort(graph);
  std::vector<int> expected;

  ASSERT_EQ(result, expected);
}

TEST(Test_TopologicalSort, Simple_Test_2) {
  Graph<char> graph;

  graph.AddVertex('A');

  auto result = TopologicalSort(graph);
  std::vector<char> expected{'A'};

  ASSERT_EQ(result, expected);
}

TEST(Test_TopologicalSort, Simple_Test_3) {
  Graph<char> graph;

  graph.AddVertex('A');
  graph.AddVertex('B');
  graph.AddVertex('C');

  graph.AddEdge('A', 'B');
  graph.AddEdge('A', 'C');

  auto result = TopologicalSort(graph);
  std::vector<char> expected{'A', 'C', 'B'};

  ASSERT_EQ(result, expected);
}

TEST(Test_TopologicalSort, Simple_Test_4) {
  Graph<char> graph;

  graph.AddVertex('A');
  graph.AddVertex('B');
  graph.AddVertex('C');

  graph.AddEdge('A', 'C');
  graph.AddEdge('A', 'B');

  auto result = TopologicalSort(graph);
  std::vector<char> expected{'A', 'B', 'C'};

  ASSERT_EQ(result, expected);
}

TEST(Test_TopologicalSort, Simple_Test_5) {
  Graph<char> graph;

  graph.AddVertex('A');
  graph.AddVertex('B');
  graph.AddVertex('C');

  graph.AddEdge('A', 'B');
  graph.AddEdge('A', 'C');
  graph.AddEdge('C', 'B');

  auto result = TopologicalSort(graph);
  std::vector<char> expected{'A', 'C', 'B'};

  ASSERT_EQ(result, expected);
}

TEST(Test_TopologicalSort, Test_1) {
  Graph<char> graph;

  graph.AddVertex('A');
  graph.AddVertex('B');
  graph.AddVertex('C');
  graph.AddVertex('D');
  graph.AddVertex('E');

  graph.AddEdge('A', 'B');
  graph.AddEdge('A', 'C');
  graph.AddEdge('B', 'D');
  graph.AddEdge('C', 'E');

  auto result = TopologicalSort(graph);
  std::vector<char> expected{'A', 'C', 'E', 'B', 'D'};

  ASSERT_EQ(result, expected);
}

TEST(Test_TopologicalSort, Test_2) {
  Graph<char> graph;

  graph.AddVertex('A');
  graph.AddVertex('B');
  graph.AddVertex('C');
  graph.AddVertex('D');
  graph.AddVertex('E');
  graph.AddVertex('F');
  graph.AddVertex('G');
  graph.AddVertex('H');
  graph.AddVertex('I');

  graph.AddEdge('A', 'B');
  graph.AddEdge('A', 'C');
  graph.AddEdge('B', 'D');
  graph.AddEdge('C', 'E');

  auto result = TopologicalSort(graph);
  std::vector<char> expected{'I', 'H', 'G', 'F', 'A', 'C', 'E', 'B', 'D'};

  ASSERT_EQ(result, expected);
}

TEST(Test_TopologicalSort, Test_3) {
  Graph<std::string> graph;

  graph.AddVertex("shirt");
  graph.AddVertex("coat");
  graph.AddVertex("blazer");
  graph.AddVertex("glasses");
  graph.AddVertex("pants");
  graph.AddVertex("shoes");
  graph.AddVertex("socks");

  graph.AddEdge("shirt", "blazer");
  graph.AddEdge("shirt", "pants");
  graph.AddEdge("pants", "coat");
  graph.AddEdge("pants", "blazer");
  graph.AddEdge("blazer", "coat");
  graph.AddEdge("pants", "shoes");
  graph.AddEdge("socks", "shoes");

  auto result = TopologicalSort(graph);
  std::vector<std::string> expected{"socks", "glasses", "shirt", "pants",
                                    "shoes", "blazer",  "coat"};

  ASSERT_EQ(result, expected);
}

TEST(Test_TopologicalSort, Test_4) {
  Graph<int> graph;

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

  graph.AddEdge(1, 10);
  graph.AddEdge(1, 6);
  graph.AddEdge(10, 3);
  graph.AddEdge(10, 5);
  graph.AddEdge(6, 5);
  graph.AddEdge(6, 2);
  graph.AddEdge(3, 8);
  graph.AddEdge(3, 5);
  graph.AddEdge(5, 8);
  graph.AddEdge(5, 4);
  graph.AddEdge(5, 2);
  graph.AddEdge(2, 4);
  graph.AddEdge(2, 7);
  graph.AddEdge(4, 8);
  graph.AddEdge(9, 8);

  auto result = TopologicalSort(graph);
  std::vector<int> expected{9, 1, 6, 10, 3, 5, 2, 7, 4, 8};

  ASSERT_EQ(result, expected);
}

TEST(Test_TopologicalSort, Test_5) {
  Graph<char> graph;

  graph.AddVertex('H');
  graph.AddVertex('E');
  graph.AddVertex('F');
  graph.AddVertex('C');
  graph.AddVertex('G');
  graph.AddVertex('A');
  graph.AddVertex('B');
  graph.AddVertex('D');

  graph.AddEdge('H', 'F');
  graph.AddEdge('F', 'C');
  graph.AddEdge('G', 'A');
  graph.AddEdge('H', 'D');
  graph.AddEdge('A', 'H');
  graph.AddEdge('F', 'B');
  graph.AddEdge('A', 'F');
  graph.AddEdge('D', 'F');

  auto result = TopologicalSort(graph);
  std::vector<char> expected{'G', 'A', 'E', 'H', 'D', 'F', 'B', 'C'};

  ASSERT_EQ(result, expected);
}

TEST(Test_TopologicalSort, Test_6) {
  Graph<std::string> graph;
  graph.AddVertex("A");
  graph.AddVertex("B");
  graph.AddVertex("C");
  graph.AddVertex("D");
  graph.AddVertex("E");

  graph.AddEdge("A", "C");
  graph.AddEdge("B", "C");
  graph.AddEdge("C", "D");
  graph.AddEdge("C", "E");

  auto result = TopologicalSort(graph);
  std::vector<std::string> expected = {"B", "A", "C", "E", "D"};

  ASSERT_EQ(result, expected);
}

TEST(Test_TopologicalSort, Test_7) {
  Graph<std::string> graph;
  graph.AddVertex("A");
  graph.AddVertex("B");
  graph.AddVertex("C");
  graph.AddVertex("D");
  graph.AddVertex("E");

  graph.AddEdge("A", "B");
  graph.AddEdge("C", "D");

  auto result = TopologicalSort(graph);
  std::vector<std::string> expected = {"E", "C", "D", "A", "B"};

  ASSERT_EQ(result, expected);
}

TEST(Test_TopologicalSort, Test_NotAcyclic_1) {
  Graph<int> graph;

  graph.AddVertex(1);
  graph.AddVertex(2);
  graph.AddVertex(3);

  graph.AddEdge(1, 2);
  graph.AddEdge(2, 3);
  graph.AddEdge(3, 1);

  ASSERT_THROW(TopologicalSort(graph), std::invalid_argument);
}

TEST(Test_TopologicalSort, Test_NotAcyclic_2) {
  Graph<char> graph;

  graph.AddVertex('G');
  graph.AddVertex('D');
  graph.AddVertex('B');
  graph.AddVertex('C');
  graph.AddVertex('F');
  graph.AddVertex('E');
  graph.AddVertex('H');
  graph.AddVertex('A');

  graph.AddEdge('E', 'B');
  graph.AddEdge('A', 'G');
  graph.AddEdge('G', 'F');
  graph.AddEdge('D', 'H');
  graph.AddEdge('H', 'G');
  graph.AddEdge('B', 'F');
  graph.AddEdge('G', 'E');
  graph.AddEdge('F', 'D');

  ASSERT_THROW(TopologicalSort(graph), std::invalid_argument);
}

TEST(Test_TopologicalSort, Test_NotAcyclic_3) {
  Graph<size_t> graph;

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

  graph.AddEdge(1, 10);
  graph.AddEdge(10, 11);
  graph.AddEdge(5, 1);
  graph.AddEdge(5, 6);
  graph.AddEdge(4, 8);
  graph.AddEdge(2, 3);
  graph.AddEdge(10, 9);
  graph.AddEdge(4, 5);
  graph.AddEdge(5, 7);
  graph.AddEdge(4, 7);
  graph.AddEdge(1, 2);
  graph.AddEdge(3, 4);
  graph.AddEdge(1, 6);

  ASSERT_THROW(TopologicalSort(graph), std::invalid_argument);
}