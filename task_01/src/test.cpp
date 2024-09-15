#include <gtest/gtest.h>

#include <stdexcept>

#include "topological_sort.cpp"

template <typename T>
bool check_graph_sorted(Graph<T, int>& g) {
  for (auto i : g.nodes) {
    for (auto k : i->paths) {
      if (i->name >= k.first->name) {
        return false;
      }
    }
  }
  return true;
}

TEST(TopologySort, TestSimple1) {
  Graph<int, int> g({{1, 4}, {4, 2}, {3, 2}, {4, 3}});
  ASSERT_EQ(check_graph_sorted(topological_sort(g)), true);  // Stack []
}

TEST(TopologySort, TestSimple2) {
  Graph<int, int> g({{1, 2}, {3, 2}, {2, 5}, {4, 2}, {4, 6}, {6, 5}});
  ASSERT_EQ(check_graph_sorted(topological_sort(g)), true);  // Stack []
}

TEST(TopologySort, TestExtraSourcePoint1) {
  Graph<int, int> g({{1, 2}, {3, 2}, {2, 5}, {4, 2}, {4, 6}, {6, 5}, {8, 6}});
  ASSERT_EQ(check_graph_sorted(topological_sort(g)), true);  // Stack []
}

TEST(TopologySort, TestExtraSourcePoint2) {
  Graph<int, int> g({{1, 2}, {3, 2}, {8, 5}, {2, 5}, {4, 2}, {4, 6}, {6, 5}});
  ASSERT_EQ(check_graph_sorted(topological_sort(g)), true);  // Stack []
}

TEST(TopologySort, TestExtraSourcePoint3) {
  Graph<int, int> g({{1, 4}, {4, 2}, {3, 2}, {4, 3}, {9, 1}});
  ASSERT_EQ(check_graph_sorted(topological_sort(g)), true);  // Stack []
}

TEST(TopologySort, TestExtraSourcePoint4) {
  Graph<int, int> g({{1, 2}, {3, 2}, {6, 5}, {2, 5}, {4, 2}, {4, 6}, {6, 5}});
  ASSERT_EQ(check_graph_sorted(topological_sort(g)), true);  // Stack []
}

TEST(TopologySort, TestExtraLeafPoint) {
  Graph<int, int> g({{1, 2}, {3, 2}, {6, 9}, {2, 5}, {4, 2}, {4, 6}, {6, 5}});
  ASSERT_EQ(check_graph_sorted(topological_sort(g)), true);  // Stack []
}

TEST(TopologySort, TestLoopError1) {
  Graph<int, int> g({{1, 4}, {4, 2}, {3, 2}, {4, 3}, {3, 3}});
  EXPECT_THROW(topological_sort(g), std::runtime_error);  // Stack []
}

TEST(TopologySort, TestLoopError2) {
  Graph<int, int> g({{1, 2}, {1, 3}, {3, 2}, {2, 3}});
  EXPECT_THROW(topological_sort(g), std::runtime_error);  // Stack []
}

TEST(TopologySort, TestLoopError3) {
  Graph<int, int> g({{1, 4}, {4, 2}, {3, 2}, {4, 3}, {4, 1}});
  EXPECT_THROW(topological_sort(g),
               std::runtime_error);  // Stack []
}

TEST(TopologySort, TestLoopError4) {
  Graph<int, int> g({{1, 2}, {1, 3}, {3, 2}, {2, 3}, {2, 1}, {3, 1}});
  EXPECT_THROW(topological_sort(g), std::runtime_error);  // Stack []
}
