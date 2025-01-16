#include "lca.hpp"

#include <cmath>

LCA::LCA(const Graph& g, int root) {
  const int height = std::floor(std::log2(g.size()) + 1);
  sparse_table =
      std::vector<std::vector<int>>(g.size(), std::vector<int>(height, -1));
  depth = std::vector<int>(g.size(), -1);
  dfs_mark_depth(g, root, root);
}

int LCA::get_parent(int u, int v) {
  if (depth[u] < depth[v]) {
    int t = v;
    v = u;
    u = t;
  }
  int height = sparse_table[0].size();
  for (int i = height - 1; i >= 0; i--) {
    if (depth[u] - (1 << i) >= depth[v]) {
      u = sparse_table[u][i];
    }
  }
  if (u == v) {
    return v;
  }
  for (int i = height - 1; i >= 0; i--) {
    if (sparse_table[u][i] != sparse_table[v][i]) {
      u = sparse_table[u][i];
      v = sparse_table[v][i];
    }
  }
  return sparse_table[u][0];
}

void LCA::dfs_mark_depth(const Graph& g, int v, int p) {
  sparse_table[v][0] = p;
  for (int i = 1; i < sparse_table[v].size(); i++) {
    if (sparse_table[v][i - 1] != -1) {
      sparse_table[v][i] = sparse_table[sparse_table[v][i - 1]][i - 1];
    }
  }
  for (const auto u : g.adjacents[v]) {
    if (u.name != p) {
      depth[u.name] = depth[v] + 1;
      dfs_mark_depth(g, u.name, v);
    }
  }
}