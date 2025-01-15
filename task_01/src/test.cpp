#include <gtest/gtest.h>

#include "graph.tpp"

TEST(TopologicalSort, test1) {
  Graph<int> g(1);

  EXPECT_EQ(g.TopologicalSort(), std::list<int>({0}));
}

TEST(TopologicalSort, test2) {
  Graph<int> g(2);

  g.AddEdge(0, 1);

  EXPECT_EQ(g.TopologicalSort(), std::list<int>({0, 1}));
}

TEST(TopologicalSort, test3) {
  Graph<int> g(3);

  g.AddEdge(0, 1);
  g.AddEdge(1, 2);

  EXPECT_EQ(g.TopologicalSort(), std::list<int>({0, 1, 2}));
}

TEST(TopologicalSort, test4) {
  Graph<int> g(6);

  g.AddEdge(0, 1);
  g.AddEdge(0, 3);
  g.AddEdge(1, 2);
  g.AddEdge(3, 1);
  g.AddEdge(3, 5);
  g.AddEdge(3, 4);
  g.AddEdge(4, 5);

  EXPECT_EQ(g.TopologicalSort(), std::list<int>({0, 3, 4, 5, 1, 2}));
}

TEST(TopologicalSort, test5) {
  Graph<int> g(7);

  g.AddEdge(0, 1);
  g.AddEdge(0, 2);
  g.AddEdge(1, 2);
  g.AddEdge(1, 5);
  g.AddEdge(2, 3);
  g.AddEdge(5, 3);
  g.AddEdge(5, 4);
  g.AddEdge(6, 1);
  g.AddEdge(6, 5);

  EXPECT_EQ(g.TopologicalSort(), std::list<int>({6, 0, 1, 5, 4, 2, 3}));
}