
#include <gtest/gtest.h>

#include "lca.hpp"

TEST(LCA, Itself) {
  std::vector<std::vector<int>> data = {{}, {}, {0, 1}, {5, 7}, {2, 3, 8, 9},
                                        {}, {}, {},     {6},    {}};
  LCA graph(data, 4);
  ASSERT_EQ(graph.LeastAncestor(2, 2), 2);
}

TEST(LCA, WithParent) {
  std::vector<std::vector<int>> data = {{}, {}, {0, 1}, {5, 7}, {2, 3, 8, 9},
                                        {}, {}, {},     {6},    {}};
  LCA graph(data, 4);
  ASSERT_EQ(graph.LeastAncestor(6, 8), 8);
}

TEST(LCA, Cousins) {
  std::vector<std::vector<int>> data = {{}, {}, {0, 1}, {5, 7}, {2, 3, 8, 9},
                                        {}, {}, {},     {6},    {}};
  LCA graph(data, 4);
  ASSERT_EQ(graph.LeastAncestor(2, 5), 4);
}

TEST(LCA, Line) {
  std::vector<std::vector<int>> data = {{},  {0}, {1}, {2}, {3},  {4}, {5},
                                        {6}, {7}, {8}, {9}, {10}, {11}};
  LCA graph(data, 12);
  ASSERT_EQ(graph.LeastAncestor(3, 8), 8);
}

TEST(LCA, BigGraph) {
  std::vector<std::vector<int>> data = {
      {},           {},       {},       {},   {},          {},     {},
      {},           {},       {},       {},   {0},         {1, 2}, {3, 4, 5},
      {6, 7, 8, 9}, {10, 11}, {12, 13}, {14}, {15, 16, 17}};
  LCA graph(data, 18);
  ASSERT_EQ(graph.LeastAncestor(1, 5), 16);
}
