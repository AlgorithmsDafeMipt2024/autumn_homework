#include <gtest/gtest.h>

#include <graph.hpp>

TEST(TopologySort, test1) {
  Graph<int> g(6);
  EXPECT_THROW(g.AddEdge(5, 5), std::logic_error);
}

TEST(TopologySort, test2) {
  EXPECT_THROW(Graph<int> g(-5), std::logic_error);
  EXPECT_THROW(Graph<int> g(0), std::logic_error);
}

TEST(TopologySort, test3) {
  Graph<int> g(2);
  EXPECT_THROW(g.AddEdge(5, 6), std::logic_error);
}

TEST(TopologySort, test4) {
  Graph<int> g(6);
  g.AddEdge(5, 2);
  g.AddEdge(5, 0);
  g.AddEdge(4, 0);
  g.AddEdge(4, 1);
  g.AddEdge(2, 3);
  g.AddEdge(3, 1);
  ASSERT_EQ(g.TopologySort(), std::list<int>({5, 4, 2, 3, 1, 0}));
}

TEST(TopologySort, test5) {
  Graph<int> g(15);
  g.AddEdge(10, 3);
  g.AddEdge(3, 10);
  g.AddEdge(10, 14);
  g.AddEdge(14, 2);
  g.AddEdge(5, 3);
  g.AddEdge(3, 5);
  g.AddEdge(1, 2);
  g.AddEdge(2, 14);
  g.AddEdge(14, 1);
  g.AddEdge(1, 4);
  g.AddEdge(11, 15);
  g.AddEdge(15, 5);

  ASSERT_EQ(g.TopologySort(), std::list<int>({13, 12, 11, 15, 9, 8, 7, 6, 3, 5,
                                              10, 1, 4, 2, 14, 0}));
}