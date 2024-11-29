
#include <gtest/gtest.h>

#include "bellman_ford.hpp"
#include "johnson.hpp"

template <typename T, typename Y>
bool operator==(std::map<T, Y> lhs, std::map<T, Y> rhs) {
  if (lhs.size() != rhs.size()) return false;

  for (auto [v, verts] : lhs)
    if (lhs[v] != rhs[v]) return false;

  return true;
}

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

TEST(Test_Johnson, Simple_Test_1) {
  WeightedGraph<char> graph;

  auto result = Johnson(graph);
  std::map<char, std::map<char, int>> expected;

  ASSERT_EQ(result, expected);
}

TEST(Test_Johnson, Simple_Test_2) {
  WeightedGraph<char> graph;

  graph.AddVertex('A');

  auto result = Johnson(graph);
  std::map<char, std::map<char, int>> expected;

  expected['A']['A'] = 0;

  ASSERT_EQ(result, expected);
}

TEST(Test_Johnson, Simple_Test_3) {
  WeightedGraph<char> graph;

  graph.AddVertex('A');
  graph.AddVertex('B');

  auto result = Johnson(graph);
  std::map<char, std::map<char, int>> expected;

  expected['A']['A'] = 0;
  expected['A']['B'] = INF;
  expected['B']['A'] = INF;
  expected['B']['B'] = 0;

  ASSERT_EQ(result, expected);
}

TEST(Test_Johnson, Simple_Test_4) {
  WeightedGraph<char> graph;

  graph.AddVertex('A');
  graph.AddVertex('B');

  graph.AddWeightedEdge('A', 'B', -1);
  graph.AddWeightedEdge('B', 'A', 2);

  auto result = Johnson(graph);
  std::map<char, std::map<char, int>> expected;

  expected['A']['A'] = 0;
  expected['A']['B'] = -1;
  expected['B']['A'] = 2;
  expected['B']['B'] = 0;

  ASSERT_EQ(result, expected);
}

TEST(Test_Johnson, Simple_Test_5) {
  WeightedGraph<char> graph;

  graph.AddVertex('A');
  graph.AddVertex('B');

  graph.AddWeightedEdge('A', 'B', -2);
  graph.AddWeightedEdge('B', 'A', 1);

  ASSERT_THROW(Johnson(graph), std::invalid_argument);
}

TEST(Test_Johnson, Test_1) {
  WeightedGraph<int> graph;

  graph.AddVertex(0);
  graph.AddVertex(1);
  graph.AddVertex(2);
  graph.AddVertex(3);

  graph.AddWeightedEdge(0, 1, 1);
  graph.AddWeightedEdge(1, 2, 2);
  graph.AddWeightedEdge(2, 3, 1);
  graph.AddWeightedEdge(0, 2, 4);

  auto result = Johnson(graph);
  std::map<int, std::map<int, int>> expected;

  expected[0][0] = 0;
  expected[0][1] = 1;
  expected[0][2] = 3;
  expected[0][3] = 4;

  expected[1][0] = INF;
  expected[1][1] = 0;
  expected[1][2] = 2;
  expected[1][3] = 3;

  expected[2][0] = INF;
  expected[2][1] = INF;
  expected[2][2] = 0;
  expected[2][3] = 1;

  expected[3][0] = INF;
  expected[3][1] = INF;
  expected[3][2] = INF;
  expected[3][3] = 0;

  ASSERT_EQ(result, expected);
}

TEST(Test_Johnson, Test_2) {
  WeightedGraph<char> graph;

  graph.AddVertex('A');
  graph.AddVertex('B');
  graph.AddVertex('C');
  graph.AddVertex('D');

  graph.AddWeightedEdge('A', 'B', -2);
  graph.AddWeightedEdge('A', 'D', 5);
  graph.AddWeightedEdge('A', 'C', 7);
  graph.AddWeightedEdge('B', 'C', 8);
  graph.AddWeightedEdge('B', 'D', 6);
  graph.AddWeightedEdge('C', 'B', 3);
  graph.AddWeightedEdge('C', 'D', -4);
  graph.AddWeightedEdge('D', 'A', -1);

  auto result = Johnson(graph);
  std::map<char, std::map<char, int>> expected;

  expected['A']['A'] = 0;
  expected['A']['B'] = -2;
  expected['A']['C'] = 6;
  expected['A']['D'] = 2;

  expected['B']['A'] = 3;
  expected['B']['B'] = 0;
  expected['B']['C'] = 8;
  expected['B']['D'] = 4;

  expected['C']['A'] = -5;
  expected['C']['B'] = -7;
  expected['C']['C'] = 0;
  expected['C']['D'] = -4;

  expected['D']['A'] = -1;
  expected['D']['B'] = -3;
  expected['D']['C'] = 5;
  expected['D']['D'] = 0;

  ASSERT_EQ(result, expected);
}

TEST(Test_Johnson, Test_3) {
  WeightedGraph<int> graph;

  graph.AddVertex(1);
  graph.AddVertex(2);
  graph.AddVertex(3);
  graph.AddVertex(4);
  graph.AddVertex(5);

  graph.AddWeightedEdge(1, 2, -4);
  graph.AddWeightedEdge(2, 3, 5);
  graph.AddWeightedEdge(3, 1, 2);
  graph.AddWeightedEdge(1, 4, 1);
  graph.AddWeightedEdge(1, 5, -2);
  graph.AddWeightedEdge(4, 5, 3);

  auto result = Johnson(graph);
  std::map<int, std::map<int, int>> expected;

  expected[1][1] = 0;
  expected[1][2] = -4;
  expected[1][3] = 1;
  expected[1][4] = 1;
  expected[1][5] = -2;

  expected[2][1] = 7;
  expected[2][2] = 0;
  expected[2][3] = 5;
  expected[2][4] = 8;
  expected[2][5] = 5;

  expected[3][1] = 2;
  expected[3][2] = -2;
  expected[3][3] = 0;
  expected[3][4] = 3;
  expected[3][5] = 0;

  expected[4][1] = INF;
  expected[4][2] = INF;
  expected[4][3] = INF;
  expected[4][4] = 0;
  expected[4][5] = 3;

  expected[5][1] = INF;
  expected[5][2] = INF;
  expected[5][3] = INF;
  expected[5][4] = INF;
  expected[5][5] = 0;

  ASSERT_EQ(result, expected);
}

TEST(Test_Johnson, Test_4) {
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

  ASSERT_THROW(Johnson(graph), std::invalid_argument);
}

TEST(Test_Johnson, Test_5) {
  WeightedGraph<std::string> graph;

  graph.AddVertex("A");
  graph.AddVertex("B");
  graph.AddVertex("C");
  graph.AddVertex("D");
  graph.AddVertex("E");
  graph.AddVertex("F");

  graph.AddWeightedEdge("A", "B", 2);
  graph.AddWeightedEdge("A", "C", 1);
  graph.AddWeightedEdge("A", "F", 8);
  graph.AddWeightedEdge("B", "D", 4);
  graph.AddWeightedEdge("B", "E", -3);
  graph.AddWeightedEdge("C", "B", 5);
  graph.AddWeightedEdge("C", "E", 5);
  graph.AddWeightedEdge("C", "F", 6);
  graph.AddWeightedEdge("D", "A", -1);
  graph.AddWeightedEdge("D", "F", -3);
  graph.AddWeightedEdge("E", "C", -2);
  graph.AddWeightedEdge("E", "F", -2);
  graph.AddWeightedEdge("E", "D", 3);

  auto result = Johnson(graph);
  std::map<std::string, std::map<std::string, int>> expected;

  expected["A"]["A"] = 0;
  expected["A"]["B"] = 2;
  expected["A"]["C"] = -3;
  expected["A"]["D"] = 2;
  expected["A"]["E"] = -1;
  expected["A"]["F"] = -3;

  expected["B"]["A"] = -1;
  expected["B"]["B"] = 0;
  expected["B"]["C"] = -5;
  expected["B"]["D"] = 0;
  expected["B"]["E"] = -3;
  expected["B"]["F"] = -5;

  expected["C"]["A"] = 4;
  expected["C"]["B"] = 5;
  expected["C"]["C"] = 0;
  expected["C"]["D"] = 5;
  expected["C"]["E"] = 2;
  expected["C"]["F"] = 0;

  expected["D"]["A"] = -1;
  expected["D"]["B"] = 1;
  expected["D"]["C"] = -4;
  expected["D"]["D"] = 0;
  expected["D"]["E"] = -2;
  expected["D"]["F"] = -4;

  expected["E"]["A"] = 2;
  expected["E"]["B"] = 3;
  expected["E"]["C"] = -2;
  expected["E"]["D"] = 3;
  expected["E"]["E"] = 0;
  expected["E"]["F"] = -2;

  expected["F"]["A"] = INF;
  expected["F"]["B"] = INF;
  expected["F"]["C"] = INF;
  expected["F"]["D"] = INF;
  expected["F"]["E"] = INF;
  expected["F"]["F"] = 0;

  ASSERT_EQ(result, expected);
}