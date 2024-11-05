#include <gtest/gtest.h>

#include "graph/graph.hpp"

TEST(Test_NotOrientedGraph, Test_Constructors) {
  Vertex<size_t> v1(1, {2, 4, 3});
  Vertex<size_t> v2(2, {1, 3, 4});
  Vertex<size_t> v3(3, {1, 2, 4, 5});
  Vertex<size_t> v4(4, {3, 5, 2, 1});
  Vertex<size_t> v5(5, {4, 3});

  Graph<size_t> g1({v1, v2, v3, v4, v5});

  std::vector<std::pair<size_t, size_t>> edges{{1, 2}, {1, 4}, {1, 3}, {2, 3},
                                               {2, 4}, {3, 4}, {3, 5}, {5, 4}};

  Graph<size_t> g2(edges, false);

  g1.PrintAdjList();
  g2.PrintAdjList();

  for (int i = 0; i < g1.GetVerticesCount(); i++) {
    ASSERT_TRUE(g2.ContainsVertex(g1.GetVertices()[i]));
  }
}

TEST(Test_NotOrientedGraph, Test_ContainsEdge) {
  Graph<char> g(
      {{'A', 'B'}, {'A', 'C'}, {'A', 'D'}, {'B', 'D'}, {'B', 'C'}, {'B', 'D'}},
      false);

  ASSERT_TRUE(g.ContainsEdge('A', 'C'));
  ASSERT_TRUE(g.ContainsEdge('C', 'A'));
  ASSERT_FALSE(g.ContainsEdge('C', 'D'));
  ASSERT_FALSE(g.ContainsEdge('D', 'C'));
}

TEST(Test_NotOrientedGraph, Test_ContainsVertex) {
  Graph<char> g({{'A', 'B'},
                 {'A', 'C'},
                 {'A', 'D'},
                 {'B', 'C'},
                 {'B', 'E'},
                 {'C', 'F'},
                 {'D', 'E'},
                 {'E', 'F'},
                 {'F', 'G'}},
                false);

  ASSERT_TRUE(g.ContainsVertex('A'));
  ASSERT_FALSE(g.ContainsVertex('T'));

  ASSERT_TRUE(g.ContainsVertex(Vertex<char>('G', {'F'})));
  ASSERT_TRUE(g.ContainsVertex(Vertex<char>('A', {'C', 'D', 'B'})));
  ASSERT_FALSE(g.ContainsVertex(Vertex<char>('Y', {'C', 'H', 'F'})));
  ASSERT_FALSE(g.ContainsVertex(Vertex<char>('A', {'B', 'C'})));
}

TEST(Test_NotOrientedGraph, Test_DeleteVertex) {
  Graph<char> g({{'A', 'B'},
                 {'A', 'C'},
                 {'A', 'D'},
                 {'B', 'C'},
                 {'B', 'E'},
                 {'C', 'F'},
                 {'D', 'E'},
                 {'E', 'F'},
                 {'F', 'G'},
                 {'A', 'F'},
                 {'B', 'G'}},
                false);

  g.DeleteVertex('A');

  ASSERT_FALSE(g.ContainsEdge('A', 'B'));
  ASSERT_FALSE(g.ContainsEdge('B', 'A'));
  ASSERT_FALSE(g.ContainsEdge('A', 'C'));
  ASSERT_FALSE(g.ContainsVertex('A'));
  ASSERT_TRUE(g.ContainsEdge('B', 'C'));

  ASSERT_THROW(g.DeleteVertex('T'), std::invalid_argument);
}

TEST(Test_NotOrientedGraph, Test_AddVertex_AddEdge) {
  Graph<char> g({{'A', 'B'}, {'A', 'C'}, {'B', 'C'}, {'B', 'D'}, {'C', 'D'}},
                false);

  g.AddVertex('F');

  ASSERT_TRUE(g.ContainsVertex('F'));

  g.AddEdge('F', 'B');
  g.AddEdge('A', 'F');

  ASSERT_TRUE(g.ContainsEdge('F', 'B'));
  ASSERT_TRUE(g.ContainsEdge('B', 'F'));
  ASSERT_TRUE(g.ContainsEdge('F', 'A'));
  ASSERT_TRUE(g.ContainsEdge('A', 'F'));
  ASSERT_FALSE(g.ContainsEdge('F', 'C'));
  ASSERT_FALSE(g.ContainsEdge('C', 'F'));

  g.AddVertex(Vertex<char>('G', {'A', 'F'}));

  ASSERT_TRUE(g.ContainsEdge('G', 'A'));
  ASSERT_TRUE(g.ContainsEdge('A', 'G'));
  ASSERT_TRUE(g.ContainsEdge('F', 'G'));
  ASSERT_TRUE(g.ContainsEdge('G', 'F'));
  ASSERT_FALSE(g.ContainsEdge('G', 'B'));
  ASSERT_FALSE(g.ContainsEdge('B', 'G'));
}