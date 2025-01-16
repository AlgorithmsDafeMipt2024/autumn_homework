
#include <gtest/gtest.h>

#include "graph.tpp"

TEST(BridgeGraphTest, test1) {
  Graph<int> a(5);

  a.AddEdge(0, 1);
  a.AddEdge(1, 2);
  a.AddEdge(2, 3);
  a.AddEdge(2, 4);
  a.AddEdge(3, 4);

  a.UpdateBrAp();

  std::vector<std::pair<int, int>> bridges({{1, 2}, {0, 1}});
  EXPECT_EQ(a.GetBr(), bridges);
  std::vector<int> articulation_points({2, 1});
  EXPECT_EQ(a.GetAP(), articulation_points);
}

TEST(BridgeGraphTest, test2) {
  Graph<int> a(5);

  a.AddEdge(0, 1);
  a.AddEdge(1, 2);
  a.AddEdge(1, 3);
  a.AddEdge(2, 3);
  a.AddEdge(2, 4);

  a.UpdateBrAp();

  std::vector<std::pair<int, int>> bridges({{2, 4}, {0, 1}});
  EXPECT_EQ(a.GetBr(), bridges);
  std::vector<int> articulation_points({2, 1});
  EXPECT_EQ(a.GetAP(), articulation_points);
}

TEST(BridgeGraphTest, test3) {
  Graph<int> a(8);

  a.AddEdge(0, 1);
  a.AddEdge(0, 2);
  a.AddEdge(0, 3);
  a.AddEdge(3, 4);
  a.AddEdge(3, 5);
  a.AddEdge(4, 6);
  a.AddEdge(5, 6);
  a.AddEdge(5, 7);
  a.AddEdge(6, 7);

  a.UpdateBrAp();

  std::vector<std::pair<int, int>> bridges({{0, 1}, {0, 2}, {0, 3}});
  EXPECT_EQ(a.GetBr(), bridges);
  std::vector<int> articulation_points({3, 0});
  EXPECT_EQ(a.GetAP(), articulation_points);
}

TEST(BridgeGraphTest, test4) {
  Graph<int> a(3);

  a.AddEdge(0, 1);
  a.AddEdge(0, 2);
  a.AddEdge(2, 1);

  a.UpdateBrAp();

  std::vector<std::pair<int, int>> bridges({});
  EXPECT_EQ(a.GetBr(), bridges);
  std::vector<int> articulation_points({});
  EXPECT_EQ(a.GetAP(), articulation_points);
}

TEST(BridgeGraphTest, test5) {
  Graph<int> a(3);

  a.UpdateBrAp();

  std::vector<std::pair<int, int>> bridges({});
  EXPECT_EQ(a.GetBr(), bridges);
  std::vector<int> articulation_points({});
  EXPECT_EQ(a.GetAP(), articulation_points);
}

TEST(BridgeGraphTest, test6) {
  Graph<int> a(7);

  a.AddEdge(0, 1);
  a.AddEdge(0, 2);
  a.AddEdge(2, 1);
  a.AddEdge(3, 4);
  a.AddEdge(3, 5);
  a.AddEdge(3, 6);
  a.AddEdge(4, 5);

  a.UpdateBrAp();

  std::vector<std::pair<int, int>> bridges({{3, 6}});
  EXPECT_EQ(a.GetBr(), bridges);
  std::vector<int> articulation_points({3});
  EXPECT_EQ(a.GetAP(), articulation_points);
}

TEST(BridgeGraphTest, test7) {
  Graph<int> a(7);

  a.AddEdge(0, 1);
  a.AddEdge(0, 2);
  a.AddEdge(3, 4);
  a.AddEdge(3, 5);
  a.AddEdge(3, 6);
  a.AddEdge(4, 5);

  a.UpdateBrAp();

  std::vector<std::pair<int, int>> bridges({{0, 1}, {0, 2}, {3, 6}});
  EXPECT_EQ(a.GetBr(), bridges);
  std::vector<int> articulation_points({0, 3});
  EXPECT_EQ(a.GetAP(), articulation_points);
}

TEST(BridgeGraphTest, test8) {
  Graph<int> a(5);

  a.AddEdge(0, 1);
  a.AddEdge(1, 2);
  a.AddEdge(1, 3);
  a.AddEdge(2, 3);
  a.AddEdge(2, 4);
  a.AddEdge(3, 4);

  a.UpdateBrAp();

  std::vector<std::pair<int, int>> bridges({{0, 1}});
  EXPECT_EQ(a.GetBr(), bridges);
  std::vector<int> articulation_points({1});
  EXPECT_EQ(a.GetAP(), articulation_points);
}

TEST(BridgeGraphTest, test9) {
  Graph<int> a(2);

  a.AddEdge(0, 1);

  a.UpdateBrAp();

  std::vector<std::pair<int, int>> bridges({{0, 1}});
  EXPECT_EQ(a.GetBr(), bridges);
  std::vector<int> articulation_points({});
  EXPECT_EQ(a.GetAP(), articulation_points);
}