#include <gtest/gtest.h>

#include <stdexcept>

#include "../../lib/src/graph.h"
#include "main.cpp"

bool is_sorted(Graph& g, std::vector<int>& order) {
  for (int i = 0; i < order.size(); ++i) {
    for (int j = i + 1; j < order.size(); ++j) {
      for (auto child : g.adjacents[j]) {
        if (child.name == order[i]) {
          return false;
        }
      }
    }
  }
  return true;
}

TEST(non_recursive_topological_sort, Test_1) {
  Graph g(8, {
                 {{1, 4}, 4},
                 {{1, 6}, 5},
                 {{2, 7}, 9},
                 {{3, 4}, 1},
                 {{3, 7}, 5.5},
                 {{4, 5}, 3.14},
                 {{7, 0}, 0.2},
                 {{7, 5}, 1.3},
                 {{7, 6}, 2.6},
             });

  ASSERT_EQ(is_sorted(g, *topological_sort_dfs_non_rec(g)), true);
}

TEST(non_recursive_topological_sort, Test_2) {
  Graph g(8, {{{1, 4}, 4},
              {{1, 6}, 5},
              {{2, 7}, 9},
              {{3, 4}, 1},
              {{3, 7}, 5.5},
              {{4, 5}, 3.14},
              {{7, 0}, 0.2},
              {{7, 5}, 1.3},
              {{7, 6}, 2.6},
              {{2, 3}, 1}});

  ASSERT_EQ(is_sorted(g, *topological_sort_dfs_non_rec(g)), true);
}

TEST(non_recursive_topological_sort, Test_3) {
  Graph g(8, {{{1, 4}, 4},
              {{1, 6}, 5},
              {{2, 7}, 9},
              {{3, 4}, 1},
              {{3, 7}, 5.5},
              {{4, 5}, 3.14},
              {{7, 0}, 0.2},
              {{7, 5}, 1.3},
              {{7, 6}, 2.6},
              {{2, 3}, 1},
              {{1, 2}, 1}});

  ASSERT_EQ(is_sorted(g, *topological_sort_dfs_non_rec(g)), true);
}

TEST(non_recursive_topological_sort, Test_4) {
  Graph g(9, {{{1, 4}, 4},
              {{1, 6}, 5},
              {{2, 7}, 9},
              {{3, 4}, 1},
              {{3, 7}, 5.5},
              {{4, 5}, 3.14},
              {{7, 0}, 0.2},
              {{7, 5}, 1.3},
              {{7, 6}, 2.6},
              {{8, 0}, 1},
              {{0, 5}, 1},
              {{5, 6}, 1}});

  ASSERT_EQ(is_sorted(g, *topological_sort_dfs_non_rec(g)), true);
}

TEST(non_recursive_topological_sort, Test_cycles_1) {
  Graph g(8, {{{1, 4}, 4},
              {{1, 6}, 5},
              {{2, 7}, 9},
              {{3, 4}, 1},
              {{3, 7}, 5.5},
              {{4, 5}, 3.14},
              {{7, 0}, 0.2},
              {{7, 5}, 1.3},
              {{7, 6}, 2.6},
              {{5, 2}, 1}});

  bool error_occured = false;

  try {
    topological_sort_dfs_non_rec(g);
  } catch (std::runtime_error) {
    error_occured = true;
  }

  ASSERT_EQ(error_occured, true);
}

TEST(non_recursive_topological_sort, Test_cycles_2) {
  Graph g(9, {{{1, 4}, 4},
              {{1, 6}, 5},
              {{2, 7}, 9},
              {{3, 4}, 1},
              {{3, 7}, 5.5},
              {{4, 5}, 3.14},
              {{7, 0}, 0.2},
              {{7, 5}, 1.3},
              {{7, 6}, 2.6},
              {{6, 8}, 1},
              {{4, 8}, 1},
              {{8, 3}, 1}});

  bool error_occured = false;

  try {
    topological_sort_dfs_non_rec(g);
  } catch (std::runtime_error) {
    error_occured = true;
  }

  ASSERT_EQ(error_occured, true);
}

TEST(recursive_topological_sort, Test_1) {
  Graph g(8, {
                 {{1, 4}, 4},
                 {{1, 6}, 5},
                 {{2, 7}, 9},
                 {{3, 4}, 1},
                 {{3, 7}, 5.5},
                 {{4, 5}, 3.14},
                 {{7, 0}, 0.2},
                 {{7, 5}, 1.3},
                 {{7, 6}, 2.6},
             });

  ASSERT_EQ(is_sorted(g, *topological_sort_dfs_rec(g)), true);
}

TEST(recursive_topological_sort, Test_2) {
  Graph g(8, {{{1, 4}, 4},
              {{1, 6}, 5},
              {{2, 7}, 9},
              {{3, 4}, 1},
              {{3, 7}, 5.5},
              {{4, 5}, 3.14},
              {{7, 0}, 0.2},
              {{7, 5}, 1.3},
              {{7, 6}, 2.6},
              {{2, 3}, 1}});

  ASSERT_EQ(is_sorted(g, *topological_sort_dfs_rec(g)), true);
}

TEST(recursive_topological_sort, Test_3) {
  Graph g(8, {{{1, 4}, 4},
              {{1, 6}, 5},
              {{2, 7}, 9},
              {{3, 4}, 1},
              {{3, 7}, 5.5},
              {{4, 5}, 3.14},
              {{7, 0}, 0.2},
              {{7, 5}, 1.3},
              {{7, 6}, 2.6},
              {{2, 3}, 1},
              {{1, 2}, 1}});

  ASSERT_EQ(is_sorted(g, *topological_sort_dfs_rec(g)), true);
}

TEST(recursive_topological_sort, Test_4) {
  Graph g(9, {{{1, 4}, 4},
              {{1, 6}, 5},
              {{2, 7}, 9},
              {{3, 4}, 1},
              {{3, 7}, 5.5},
              {{4, 5}, 3.14},
              {{7, 0}, 0.2},
              {{7, 5}, 1.3},
              {{7, 6}, 2.6},
              {{8, 0}, 1},
              {{0, 5}, 1},
              {{5, 6}, 1}});

  ASSERT_EQ(is_sorted(g, *topological_sort_dfs_rec(g)), true);
}

TEST(recursive_topological_sort, Test_cycles_1) {
  Graph g(8, {{{1, 4}, 4},
              {{1, 6}, 5},
              {{2, 7}, 9},
              {{3, 4}, 1},
              {{3, 7}, 5.5},
              {{4, 5}, 3.14},
              {{7, 0}, 0.2},
              {{7, 5}, 1.3},
              {{7, 6}, 2.6},
              {{5, 2}, 1}});

  bool error_occured = false;

  try {
    topological_sort_dfs_rec(g);
  } catch (std::runtime_error) {
    error_occured = true;
  }

  ASSERT_EQ(error_occured, true);
}

TEST(recursive_topological_sort, Test_cycles_2) {
  Graph g(9, {{{1, 4}, 4},
              {{1, 6}, 5},
              {{2, 7}, 9},
              {{3, 4}, 1},
              {{3, 7}, 5.5},
              {{4, 5}, 3.14},
              {{7, 0}, 0.2},
              {{7, 5}, 1.3},
              {{7, 6}, 2.6},
              {{6, 8}, 1},
              {{4, 8}, 1},
              {{8, 3}, 1}});

  bool error_occured = false;

  try {
    topological_sort_dfs_rec(g);
  } catch (std::runtime_error) {
    error_occured = true;
  }

  ASSERT_EQ(error_occured, true);
}