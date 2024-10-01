
#include <gtest/gtest.h>

#include <graph.hpp>

using std::pair;

TEST(StackTest, test1) {
  BridgeGraph<int> g(5);

  g.AddEdge(1, 2);
  g.AddEdge(1, 3);
  g.AddEdge(3, 4);
  g.AddEdge(3, 5);
  g.AddEdge(4, 5);

  g.FindBridgesAndArticulationPoints();

  vector<pair<int, int>> bridges({{1, 2}, {1, 3}});
  ASSERT_EQ(g.GiveBridges(), bridges);
  vector<int> articulation_points({3, 1});
  ASSERT_EQ(g.GivePoints(), articulation_points);
}

TEST(StackTest, test2) {
  BridgeGraph<int> g(5);

  g.AddEdge(1, 5);
  g.AddEdge(1, 2);
  g.AddEdge(1, 3);
  g.AddEdge(2, 4);
  g.AddEdge(2, 5);
  g.AddEdge(3, 5);

  g.FindBridgesAndArticulationPoints();

  vector<pair<int, int>> bridges({{2, 4}});
  ASSERT_EQ(g.GiveBridges(), bridges);
  vector<int> articulation_points({2});
  ASSERT_EQ(g.GivePoints(), articulation_points);
}

TEST(StackTest, test3) {
  BridgeGraph<int> g(8);

  g.AddEdge(1, 2);
  g.AddEdge(1, 8);
  g.AddEdge(2, 6);
  g.AddEdge(2, 8);
  g.AddEdge(3, 4);
  g.AddEdge(3, 5);
  g.AddEdge(3, 6);
  g.AddEdge(6, 7);
  g.AddEdge(7, 8);

  g.FindBridgesAndArticulationPoints();

  vector<pair<int, int>> bridges({{3, 4}, {3, 5}, {6, 3}});
  ASSERT_EQ(g.GiveBridges(), bridges);
  vector<int> articulation_points({3, 6});
  ASSERT_EQ(g.GivePoints(), articulation_points);
}

TEST(StackTest, test4) {
  EXPECT_THROW(BridgeGraph<int> g(-5), std::logic_error);
  EXPECT_THROW(BridgeGraph<int> g(0), std::logic_error);
}

TEST(StackTest, test5) {
  BridgeGraph<int> g(2);
  EXPECT_THROW(g.AddEdge(5, 6), std::logic_error);
  EXPECT_THROW(g.AddEdge(5, -4), std::logic_error);
}
