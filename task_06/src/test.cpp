#include <gtest/gtest.h>
#include "lca.h"

TEST(TEST, Simple) {
  std::vector<std::vector<int>> g = {{1, 2}, {3, 4}, {}, {}, {}};
  std::cout << "as";
  auto a = lca(g, {{3, 4}, {3, 5}});
  ASSERT_TRUE(a[0] = 1 && a[1] == 0);
}
TEST(TEST, Simple1) {
  std::vector<std::vector<int>> g = {{1}, {2}, {3}, {4}, {}};
  std::cout << "as";
  auto a = lca(g, {{3, 4}, {1, 4}, {4, 1}});
  ASSERT_TRUE(a[0] = 3 && a[1] == 1 && a[2] == 1) << a[1];
}
