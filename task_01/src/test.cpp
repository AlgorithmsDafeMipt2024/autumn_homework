#include <gtest/gtest.h>

#include "graph.tpp"

TEST(TopologicalSort, test1) {
  Graph<int> a(1);

  EXPECT_EQ(a.TopologicalSort(), std::list<int>({0}));
}

TEST(TopologicalSort, test2) {
  Graph<int> a(2);

  a.AddEdge(0, 1);

  EXPECT_EQ(a.TopologicalSort(), std::list<int>({0, 1}));
}

TEST(TopologicalSort, test3) {
  Graph<int> a(3);

  a.AddEdge(0, 1);
  a.AddEdge(1, 2);

  EXPECT_EQ(a.TopologicalSort(), std::list<int>({0, 1, 2}));
}

TEST(TopologicalSort, test4) {
  Graph<int> a(6);

  a.AddEdge(0, 1);
  a.AddEdge(0, 3);
  a.AddEdge(1, 2);
  a.AddEdge(3, 1);
  a.AddEdge(3, 5);
  a.AddEdge(3, 4);
  a.AddEdge(4, 5);

  EXPECT_EQ(a.TopologicalSort(), std::list<int>({0, 3, 4, 5, 1, 2}));
}

TEST(TopologicalSort, test5) {
  Graph<int> a(7);

  a.AddEdge(0, 1);
  a.AddEdge(0, 2);
  a.AddEdge(1, 2);
  a.AddEdge(1, 5);
  a.AddEdge(2, 3);
  a.AddEdge(5, 3);
  a.AddEdge(5, 4);
  a.AddEdge(6, 1);
  a.AddEdge(6, 5);

  EXPECT_EQ(a.TopologicalSort(), std::list<int>({6, 0, 1, 5, 4, 2, 3}));
}