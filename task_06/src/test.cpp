#include <gtest/gtest.h>

#include "algo.hpp"

TEST(TopologySort, test1) {
  vector<vector<int>> tree(10);
  tree[0] = {1, 2};
  tree[1] = {0, 3, 4};
  tree[2] = {0, 5, 6};
  tree[3] = {1, 7};
  tree[4] = {1, 8, 9};
  tree[5] = {2};
  tree[6] = {2};
  tree[7] = {3};
  tree[8] = {4};
  tree[9] = {4};

  LCA lca(tree, 0);

  ASSERT_EQ(lca.Query(3, 4), 1);
  ASSERT_EQ(lca.Query(7, 8), 1);
  ASSERT_EQ(lca.Query(5, 6), 2);
  ASSERT_EQ(lca.Query(7, 9), 1);
  ASSERT_EQ(lca.Query(8, 9), 4);
}

TEST(TopologySort, test2) {
  vector<vector<int>> tree(7);
  tree[0] = {1, 2};
  tree[1] = {0, 3, 4};
  tree[2] = {0, 5, 6};
  tree[3] = {1};
  tree[4] = {1};
  tree[5] = {2};
  tree[6] = {2};

  LCA lca(tree, 0);

  ASSERT_EQ(lca.Query(3, 4), 1);
  ASSERT_EQ(lca.Query(3, 5), 0);
  ASSERT_EQ(lca.Query(4, 6), 0);
  ASSERT_EQ(lca.Query(5, 6), 2);
  ASSERT_EQ(lca.Query(1, 2), 0);
}

TEST(TopologySort, test3) {
  vector<vector<int>> tree(9);
  tree[0] = {1, 2};
  tree[1] = {0, 3, 4};
  tree[2] = {0, 5, 6};
  tree[3] = {1, 7};
  tree[4] = {1, 8};
  tree[5] = {2};
  tree[6] = {2};
  tree[7] = {3};
  tree[8] = {4};

  LCA lca(tree, 0);

  ASSERT_EQ(lca.Query(3, 4), 1);
  ASSERT_EQ(lca.Query(7, 8), 1);
  ASSERT_EQ(lca.Query(5, 6), 2);
  ASSERT_EQ(lca.Query(7, 3), 3);
  ASSERT_EQ(lca.Query(8, 4), 4);
}

TEST(TopologySort, test4) {
  vector<vector<int>> tree(4);
  tree[0] = {1, 2};
  tree[1] = {0, 3};
  tree[2] = {0};
  tree[3] = {1};

  LCA lca(tree, 0);

  EXPECT_THROW(lca.Query(-1, 2), std::out_of_range);
}

TEST(TopologySort, test5) {
  vector<vector<int>> tree(4);
  tree[0] = {1, 2};
  tree[1] = {0, 3};
  tree[2] = {0};
  tree[3] = {1};

  LCA lca(tree, 0);

  EXPECT_THROW(lca.Query(0, 4), std::out_of_range);
}

TEST(TopologySort, test6) {
  vector<vector<int>> tree(4);
  tree[0] = {1, 2};
  tree[1] = {0, 3};
  tree[2] = {0};

  EXPECT_THROW(LCA lca(tree, 0), std::logic_error);
}

TEST(TopologySort, test7) {
  vector<vector<int>> tree;

  EXPECT_THROW(LCA lca(tree, 0), std::logic_error);
}