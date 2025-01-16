

#include <gtest/gtest.h>

#include "lca_tree.tpp"

using namespace std;

// алгоритм не делает проверку на дурака! должны подаваться только валидные
// деревья

TEST(Lca, test1) {
  vector<vector<size_t>> list = {{1, 2}, {3, 4}, {5, 6}, {}, {7, 8},
                                 {},     {},     {},     {}};
  LcaTree<int> t(list, 0);

  EXPECT_EQ(t.lca(6, 2), 2);
  EXPECT_EQ(t.lca(0, 1), 0);
  EXPECT_EQ(t.lca(3, 8), 1);
  EXPECT_EQ(t.lca(7, 5), 0);
}

TEST(Lca, test2) {
  vector<vector<size_t>> list = {{1}, {2, 4}, {3}, {}, {5, 6}, {}, {}};
  LcaTree<int> t(list, 0);

  EXPECT_EQ(t.lca(0, 3), 0);
  EXPECT_EQ(t.lca(1, 2), 1);
  EXPECT_EQ(t.lca(3, 4), 1);
  EXPECT_EQ(t.lca(6, 5), 4);
  EXPECT_EQ(t.lca(3, 5), 1);
}

TEST(Lca, test3) {
  vector<vector<size_t>> list = {{3}, {}, {}, {1, 2, 4}, {5}, {}};
  LcaTree<int> t(list, 0);

  EXPECT_EQ(t.lca(4, 2), 3);
  EXPECT_EQ(t.lca(0, 5), 0);
  EXPECT_EQ(t.lca(1, 2), 3);
  EXPECT_EQ(t.lca(5, 1), 3);
  EXPECT_EQ(t.lca(5, 0), 0);
}