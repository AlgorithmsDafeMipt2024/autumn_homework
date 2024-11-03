#include "lca.hpp"

#include <algorithm>
#include <stdexcept>

LCA::LCA(const vector<vector<int>>& tree, int root) {
  if (tree.empty()) throw std::logic_error("the input vector is empty!");
  for (const auto& i : tree)
    if (i.empty()) throw std::logic_error("vertex vector is empty");
  n = tree.size();
  int log_n = log2(n) + 1;
  up.assign(n, vector<int>(log_n, -1));
  depth.resize(n);
  Dfs(tree, root, root);
}

int LCA::Query(int u, int v) {
  if (u < 0 || v >= n) throw std::out_of_range("incorrect boundaries!");
  if (depth[u] < depth[v]) std::swap(u, v);
  int log_n = up[0].size();
  for (int i = log_n - 1; i >= 0; i--) {
    if (depth[u] - (1 << i) >= depth[v]) u = up[u][i];
  }
  if (u == v) return u;
  for (int i = log_n - 1; i >= 0; i--) {
    if (up[u][i] != up[v][i]) {
      u = up[u][i];
      v = up[v][i];
    }
  }
  return up[u][0];
}

void LCA::Dfs(const vector<vector<int>>& tree, int v, int p) {
  up[v][0] = p;
  for (int i = 1; i < up[v].size(); i++) {
    if (up[v][i - 1] != -1) {
      up[v][i] = up[up[v][i - 1]][i - 1];
    }
  }
  for (int u : tree[v]) {
    if (u != p) {
      depth[u] = depth[v] + 1;
      Dfs(tree, u, v);
    }
  }
}
