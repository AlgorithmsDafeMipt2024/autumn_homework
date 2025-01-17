#include <gtest/gtest.h>

#include "LCA.hpp"

TEST(Test_LCA, Simple_Test_1) {
  LCA<int> lca;

  ASSERT_THROW(lca(1, 2), std::invalid_argument);
}

TEST(Test_LCA, Simple_Test_2) {
  Graph<int> graph(false);

  graph.AddVertex(1);
  graph.AddVertex(2);

  graph.AddEdge(1, 2);

  LCA<int> lca(1, graph);

  ASSERT_EQ(lca(1, 2), 1);
}

TEST(Test_LCA, Simple_Test_3) {
  Graph<char> graph(false);

  graph.AddVertex('A');
  graph.AddVertex('B');
  graph.AddVertex('C');

  graph.AddEdge('A', 'B');
  graph.AddEdge('A', 'C');
  graph.AddEdge('B', 'C');

  ASSERT_THROW((LCA<char>('A', graph)), std::invalid_argument);
}

TEST(Test_LCA, Simple_Test_4) {
  Graph<char> graph(false);

  graph.AddVertex('A');
  graph.AddVertex('B');
  graph.AddVertex('C');
  graph.AddVertex('D');
  graph.AddVertex('E');

  graph.AddEdge('A', 'B');
  graph.AddEdge('A', 'C');
  graph.AddEdge('B', 'C');
  graph.AddEdge('D', 'E');

  ASSERT_THROW((LCA<char>('A', graph)), std::invalid_argument);
}

TEST(Test_LCA, Simple_Test_5) {
  Graph<char> graph(false);

  graph.AddVertex('A');
  graph.AddVertex('B');
  graph.AddVertex('C');
  graph.AddVertex('D');
  graph.AddVertex('E');

  graph.AddEdge('A', 'B');
  graph.AddEdge('A', 'C');
  graph.AddEdge('D', 'E');

  ASSERT_THROW((LCA<char>('A', graph)), std::invalid_argument);
}

TEST(Test_LCA, Simple_Test_6) {
  Graph<char> graph(false);

  graph.AddVertex('A');
  graph.AddVertex('B');

  ASSERT_THROW((LCA<char>('A', graph)), std::invalid_argument);
}

TEST(Test_LCA, Simple_Test_7) {
  Graph<char> graph(false);

  graph.AddVertex('A');
  graph.AddVertex('B');
  graph.AddVertex('C');

  graph.AddEdge('A', 'B');
  graph.AddEdge('A', 'C');

  LCA<char> lca('A', graph);

  ASSERT_THROW(lca('A', 'D'), std::invalid_argument);
  ASSERT_THROW(lca('D', 'A'), std::invalid_argument);
}

TEST(Test_LCA, Test_1) {
  Graph<char> graph(false);

  graph.AddVertex('A');
  graph.AddVertex('B');
  graph.AddVertex('C');
  graph.AddVertex('D');
  graph.AddVertex('E');
  graph.AddVertex('F');

  graph.AddEdge('A', 'B');
  graph.AddEdge('A', 'C');
  graph.AddEdge('B', 'D');
  graph.AddEdge('B', 'E');
  graph.AddEdge('C', 'F');

  LCA<char> lca('A', graph);

  std::vector<char> expected{'A', 'A', 'A', 'A', 'A', 'A', 'A', 'B', 'A',
                             'B', 'B', 'A', 'A', 'A', 'C', 'A', 'A', 'C',
                             'A', 'B', 'A', 'D', 'B', 'A', 'A', 'B', 'A',
                             'B', 'E', 'A', 'A', 'A', 'C', 'A', 'A', 'F'};

  int count = 0;
  for (auto v1 : graph.GetVerticesIds())
    for (auto v2 : graph.GetVerticesIds())
      ASSERT_EQ(lca(v1, v2), expected[count++]);
}

TEST(Test_LCA, Test_2) {
  Graph<char> graph(false);

  graph.AddVertex('A');
  graph.AddVertex('B');
  graph.AddVertex('C');
  graph.AddVertex('D');
  graph.AddVertex('E');
  graph.AddVertex('F');

  graph.AddEdge('A', 'B');
  graph.AddEdge('B', 'C');
  graph.AddEdge('C', 'D');
  graph.AddEdge('D', 'E');
  graph.AddEdge('E', 'F');

  LCA<char> lca('A', graph);

  std::vector<char> expected{'A', 'A', 'A', 'A', 'A', 'A', 'A', 'B', 'B',
                             'B', 'B', 'B', 'A', 'B', 'C', 'C', 'C', 'C',
                             'A', 'B', 'C', 'D', 'D', 'D', 'A', 'B', 'C',
                             'D', 'E', 'E', 'A', 'B', 'C', 'D', 'E', 'F'};

  int count = 0;
  for (auto v1 : graph.GetVerticesIds())
    for (auto v2 : graph.GetVerticesIds())
      ASSERT_EQ(lca(v1, v2), expected[count++]);
}

TEST(Test_LCA, Test_3) {
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

  graph.AddEdge('A', 'B');
  graph.AddEdge('A', 'C');
  graph.AddEdge('B', 'D');
  graph.AddEdge('B', 'G');
  graph.AddEdge('B', 'E');
  graph.AddEdge('G', 'H');
  graph.AddEdge('G', 'I');
  graph.AddEdge('C', 'F');
  graph.AddEdge('F', 'J');
  graph.AddEdge('F', 'K');

  LCA<char> lca('A', graph);

  std::vector<char> expected{
      'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'B', 'A',
      'B', 'B', 'A', 'B', 'B', 'B', 'A', 'A', 'A', 'A', 'C', 'A', 'A', 'C',
      'A', 'A', 'A', 'C', 'C', 'A', 'B', 'A', 'D', 'B', 'A', 'B', 'B', 'B',
      'A', 'A', 'A', 'B', 'A', 'B', 'E', 'A', 'B', 'B', 'B', 'A', 'A', 'A',
      'A', 'C', 'A', 'A', 'F', 'A', 'A', 'A', 'F', 'F', 'A', 'B', 'A', 'B',
      'B', 'A', 'G', 'G', 'G', 'A', 'A', 'A', 'B', 'A', 'B', 'B', 'A', 'G',
      'H', 'G', 'A', 'A', 'A', 'B', 'A', 'B', 'B', 'A', 'G', 'G', 'I', 'A',
      'A', 'A', 'A', 'C', 'A', 'A', 'F', 'A', 'A', 'A', 'J', 'F', 'A', 'A',
      'C', 'A', 'A', 'F', 'A', 'A', 'A', 'F', 'K'};

  int count = 0;
  for (auto v1 : graph.GetVerticesIds())
    for (auto v2 : graph.GetVerticesIds())
      ASSERT_EQ(lca(v1, v2), expected[count++]);
}