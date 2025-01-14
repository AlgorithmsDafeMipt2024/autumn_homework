#include <gtest/gtest.h>

#include "graph.tpp"

TEST(TopologicalSort, test1) {
  Graph<int> g(5);
  g.AddEdge(4, 1);
  g.AddEdge(4, 0);
  g.AddEdge(3, 0);
  g.AddEdge(3, 4);
  g.AddEdge(1, 2);
  g.AddEdge(2, 0);
  ASSERT_EQ(g.TopologicalSort(), std::list<int>({3, 4, 1, 2, 0}));
}

TEST(TopologicalSort, test2) {
  Graph<int> g(12);
  g.AddEdge(0, 1);
  g.AddEdge(1, 2);
  g.AddEdge(2, 3);
  g.AddEdge(3, 4);
  g.AddEdge(4, 5);
  g.AddEdge(5, 6);
  g.AddEdge(6, 7);
  g.AddEdge(6, 7);
  g.AddEdge(6, 7);
  g.AddEdge(6, 7);

  ASSERT_EQ(g.TopologicalSort(),
            std::list<int>({11, 10, 9, 8, 0, 1, 2, 3, 4, 5, 6, 7}));
}

TEST(TopologicalSort, test3) {
  Graph<int> g(6);
  g.AddEdge(5, 2);
  g.AddEdge(5, 0);
  g.AddEdge(4, 0);
  g.AddEdge(4, 1);
  g.AddEdge(2, 3);
  g.AddEdge(3, 1);

  ASSERT_EQ(g.TopologicalSort(), std::list<int>({5, 4, 2, 3, 1, 0}));
}