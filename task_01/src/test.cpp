#include <gtest/gtest.h>

#include "../../lib/src/graph.h"
#include "main.cpp"

bool is_sorted(Graph& g, std::vector<int>& order) {
  bool found_parent;
  for (int i = 0; i < order.size(); ++i) {
    for (int j = i + 1; j < order.size(); ++j) {
      found_parent = false;
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