
#include <gtest/gtest.h>

#include "lca.hpp"

bool dfs_find(Graph& g, std::vector<bool>& visited, int v, int to_find) {
  visited[v] = true;

  for (auto child : g.adjacents[v]) {
    if (visited[child.name]) {
      continue;
    }
    if (child.name == to_find) {
      return true;
    }
    if (dfs_find(g, visited, child.name, to_find)) {
      return true;
    }
  }
  return false;
}

bool is_min_ancestor(Graph& g, int v, int u, int parent) {
  if (parent == v && parent == u) {
    return true;
  }
  bool v_found = (parent == v);
  bool u_found = (parent == u);
  int child_first_found = -1;
  std::vector<bool> visited(g.size(), false);

  for (auto child : g.adjacents[parent]) {
    if (!v_found && (child_first_found != child.name)) {
      if (dfs_find(g, visited, parent, v)) {
        child_first_found = child.name;
        v_found = true;
      }
    }
  }
  visited = std::vector<bool>(g.size(), false);

  for (auto child : g.adjacents[parent]) {
    if (!u_found && (child_first_found != child.name)) {
      if (dfs_find(g, visited, parent, u)) {
        child_first_found = child.name;
        u_found = true;
      }
    }
  }
  return (u_found && v_found);
}

TEST(native_ancestors_check, Test_1) {
  Graph g(10, {
                  {2, 0},
                  {2, 1},
                  {4, 2},
                  {8, 6},
                  {4, 8},
                  {4, 9},
                  {4, 3},
                  {3, 5},
                  {3, 7},
              });
  LCA lca(g, 4);

  for (int i = 0; i < g.size(); ++i) {
    for (int j = i; j < g.size(); ++j) {
      ASSERT_EQ(is_min_ancestor(g, i, j, lca.get_parent(i, j)), true);
    }
  }
}

TEST(native_ancestors_check, Test_2) {
  Graph g(9, {
                 {1, 0},
                 {1, 3},
                 {3, 2},
                 {3, 4},
                 {5, 1},
                 {5, 6},
                 {6, 8},
                 {8, 7},
                 {3, 7},
             });
  LCA lca(g, 5);

  for (int i = 0; i < g.size(); ++i) {
    for (int j = i; j < g.size(); ++j) {
      ASSERT_EQ(is_min_ancestor(g, i, j, lca.get_parent(i, j)), true);
    }
  }
}

TEST(native_ancestors_check, Test_3) {
  Graph g(14, {
                  {1, 0},
                  {1, 2},
                  {2, 3},
                  {3, 4},
                  {5, 1},
                  {5, 6},
                  {6, 9},
                  {9, 7},
                  {7, 8},
                  {9, 12},
                  {12, 10},
                  {10, 11},
                  {12, 13},
              });
  LCA lca(g, 5);

  for (int i = 0; i < g.size(); ++i) {
    for (int j = i; j < g.size(); ++j) {
      ASSERT_EQ(is_min_ancestor(g, i, j, lca.get_parent(i, j)), true);
    }
  }
}
