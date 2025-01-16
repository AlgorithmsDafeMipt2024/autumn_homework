#include <gtest/gtest.h>
#include <vector>
#include "topo.hpp"
#include "util.hpp"

TEST(Topa, Simple) {
  std::vector<int> expected = {0, 3, 2, 1};

  std::vector<std::vector<int>> edges = {{0, 3}, {3, 1}, {3, 2}, {2, 1}};
  OrientedGraph gr(4, edges);
  std::vector<int> result = topo_sort(gr);
  ASSERT_EQ(result, expected);  // Stack []
}