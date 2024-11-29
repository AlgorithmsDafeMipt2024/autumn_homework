#include "graph/graph.hpp"

#include <gtest/gtest.h>

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

  for (int i = 0; i < g1.GetVerticesCount(); i++) {
    ASSERT_TRUE(g2.ContainsVertex(g1.GetVertices()[i]));
  }
}

TEST(Test_NotOrientedGraph, Test_GetEdgesCount) {
  std::vector<std::pair<char, char>> edges = {
      {'A', 'B'}, {'A', 'D'}, {'B', 'C'}, {'D', 'B'}, {'E', 'C'}, {'D', 'C'}};

  Graph<char> g(edges, false);

  ASSERT_EQ(edges.size(), g.GetEdgesCount());
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

TEST(Test_NotOrientedGraph, Test_DeleteEdge) {
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

  g.DeleteEdge('A', 'B');

  ASSERT_FALSE(g.ContainsEdge('A', 'B'));
  ASSERT_FALSE(g.ContainsEdge('B', 'A'));
  ASSERT_TRUE(g.ContainsEdge('A', 'C'));
  ASSERT_TRUE(g.ContainsEdge('C', 'A'));

  ASSERT_THROW(g.DeleteEdge('A', 'B'), std::invalid_argument);
  ASSERT_THROW(g.DeleteEdge('E', 'G'), std::invalid_argument);
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

TEST(Test_OrientedGraph, Test_Constructors) {
  Vertex<char> v1('A', {'B', 'C'});
  Vertex<char> v2('B', {'D'});
  Vertex<char> v3('C', {'E'});
  Vertex<char> v4('D', {'A'});
  Vertex<char> v5('E', {'B'});

  Graph<char> g1({v1, v2, v3, v4, v5});

  std::vector<std::pair<char, char>> edges{{'A', 'B'}, {'A', 'C'}, {'B', 'D'},
                                           {'C', 'E'}, {'D', 'A'}, {'E', 'B'}};

  Graph<char> g2(edges);

  for (int i = 0; i < g1.GetVerticesCount(); i++) {
    ASSERT_TRUE(g2.ContainsVertex(g1.GetVertices()[i]));
  }
}

TEST(Test_OrientedGraph, Test_GetEdgesCount) {
  std::vector<std::pair<char, char>> edges = {
      {'A', 'B'}, {'B', 'A'}, {'C', 'B'}, {'D', 'A'}, {'C', 'D'}, {'B', 'D'}};

  Graph<char> g(edges);

  ASSERT_EQ(edges.size(), g.GetEdgesCount());
}

TEST(Test_OrientedGraph, Test_ContainsEdge) {
  Graph<char> g({
      {'A', 'B'},
      {'A', 'C'},
      {'A', 'D'},
      {'B', 'C'},
      {'B', 'E'},
      {'C', 'A'},
      {'C', 'D'},
      {'C', 'E'},
      {'D', 'B'},
      {'E', 'A'},
  });

  ASSERT_TRUE(g.ContainsEdge('A', 'C'));
  ASSERT_TRUE(g.ContainsEdge('C', 'A'));
  ASSERT_FALSE(g.ContainsEdge('C', 'F'));
  ASSERT_FALSE(g.ContainsEdge('E', 'C'));
  ASSERT_FALSE(g.ContainsEdge('D', 'C'));
  ASSERT_FALSE(g.ContainsEdge('B', 'D'));
}

TEST(Test_OrientedGraph, Test_ContainsVertex) {
  Vertex<char> v1('A', {'B', 'C', 'D', 'F'});
  Vertex<char> v2('B', {'C', 'E', 'F'});
  Vertex<char> v3('C', {'A', 'D', 'E', 'F'});
  Vertex<char> v4('D', {'B', 'F'});
  Vertex<char> v5('E', {'G'});
  Vertex<char> v6('F', {'A', 'C'});
  Vertex<char> v7('G', {'E'});

  Graph<char> g({v1, v2, v3, v4, v5, v6, v7});

  ASSERT_TRUE(g.ContainsVertex('A'));
  ASSERT_FALSE(g.ContainsVertex('T'));

  ASSERT_TRUE(g.ContainsVertex(Vertex<char>('G', {'E'})));
  ASSERT_TRUE(g.ContainsVertex(Vertex<char>('A', {'B', 'C', 'D', 'F'})));
  ASSERT_FALSE(g.ContainsVertex(Vertex<char>('Y', {'C', 'H', 'F'})));
  ASSERT_FALSE(g.ContainsVertex(Vertex<char>('A', {'B', 'C'})));
  ASSERT_FALSE(g.ContainsVertex(Vertex<char>('G', {'E', 'A'})));
}

TEST(Test_OrientedGraph, Test_DeleteVertex) {
  Vertex<char> v1('A', {'B', 'C', 'D', 'F'});
  Vertex<char> v2('B', {'C', 'E', 'F'});
  Vertex<char> v3('C', {'A', 'D', 'E', 'F'});
  Vertex<char> v4('D', {'B', 'F'});
  Vertex<char> v5('E', {'G'});
  Vertex<char> v6('F', {'A', 'C'});
  Vertex<char> v7('G', {'E'});

  Graph<char> g({v1, v2, v3, v4, v5, v6, v7});

  g.DeleteVertex('A');

  ASSERT_FALSE(g.ContainsEdge('A', 'B'));
  ASSERT_FALSE(g.ContainsEdge('B', 'A'));
  ASSERT_FALSE(g.ContainsEdge('A', 'C'));
  ASSERT_FALSE(g.ContainsEdge('C', 'A'));
  ASSERT_FALSE(g.ContainsVertex('A'));
  ASSERT_TRUE(g.ContainsEdge('B', 'C'));
  ASSERT_TRUE(g.ContainsEdge('C', 'D'));
  ASSERT_TRUE(g.ContainsEdge('G', 'E'));

  ASSERT_THROW(g.DeleteVertex('T'), std::invalid_argument);
}

TEST(Test_OrientedGraph, Test_DeleteEdge) {
  Vertex<char> v1('A', {'B', 'C', 'D', 'F'});
  Vertex<char> v2('B', {'C', 'E', 'F'});
  Vertex<char> v3('C', {'A', 'D', 'E', 'F'});
  Vertex<char> v4('D', {'B', 'F'});
  Vertex<char> v5('E', {'G'});
  Vertex<char> v6('F', {'A', 'C'});
  Vertex<char> v7('G', {'E'});

  Graph<char> g({v1, v2, v3, v4, v5, v6, v7});

  g.DeleteEdge('A', 'C');

  ASSERT_FALSE(g.ContainsEdge('A', 'C'));
  ASSERT_TRUE(g.ContainsEdge('C', 'A'));
  ASSERT_TRUE(g.ContainsEdge('A', 'B'));
  ASSERT_TRUE(g.ContainsEdge('A', 'D'));

  ASSERT_THROW(g.DeleteEdge('E', 'F'), std::invalid_argument);
}

TEST(Test_OrientedGraph, Test_AddVertex_AddEdge) {
  Graph<char> g(
      {{'A', 'B'}, {'A', 'C'}, {'B', 'A'}, {'B', 'D'}, {'C', 'D'}, {'D', 'A'}});

  g.AddVertex('F');

  ASSERT_TRUE(g.ContainsVertex('F'));

  g.AddEdge('F', 'B');
  g.AddEdge('A', 'F');

  ASSERT_TRUE(g.ContainsEdge('F', 'B'));
  ASSERT_FALSE(g.ContainsEdge('B', 'F'));
  ASSERT_FALSE(g.ContainsEdge('F', 'A'));
  ASSERT_TRUE(g.ContainsEdge('A', 'F'));
  ASSERT_FALSE(g.ContainsEdge('F', 'C'));
  ASSERT_FALSE(g.ContainsEdge('C', 'F'));

  g.AddVertex(Vertex<char>('G', {'A', 'F'}));

  ASSERT_TRUE(g.ContainsEdge('G', 'A'));
  ASSERT_FALSE(g.ContainsEdge('A', 'G'));
  ASSERT_FALSE(g.ContainsEdge('F', 'G'));
  ASSERT_TRUE(g.ContainsEdge('G', 'F'));
  ASSERT_FALSE(g.ContainsEdge('G', 'B'));
  ASSERT_FALSE(g.ContainsEdge('B', 'G'));
}