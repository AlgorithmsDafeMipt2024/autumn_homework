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
  Graph<int> g(5);
  g.AddEdge(5, 2);
  g.AddEdge(5, 1);
  g.AddEdge(4, 1);
  g.AddEdge(4, 5);
  g.AddEdge(2, 3);
  g.AddEdge(3, 1);
  ASSERT_EQ(g.TopologySort(), std::list<int>({4, 5, 2, 3, 1}));
}

TEST(TopologySort, test5) {
  Graph<int> g(12);
    g.AddEdge(1, 2);
    g.AddEdge(2, 3);
    g.AddEdge(3, 4);
    g.AddEdge(4, 5);
    g.AddEdge(5, 6);
    g.AddEdge(6, 7);
    g.AddEdge(7, 8);
    g.AddEdge(7, 8);
    g.AddEdge(7, 8);
    g.AddEdge(7, 8);

  ASSERT_EQ(g.TopologySort(), std::list<int>({12, 11, 10, 9, 1, 2, 3, 4, 5, 6, 7, 8 }));
}