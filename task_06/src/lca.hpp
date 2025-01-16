#include <cmath>
#include <vector>

class LCA {
 public:
  LCA(const std::vector<std::vector<int>>& data, int root) {
    n = data.size();
    const int height = static_cast<int>(log2(static_cast<double>(n)) + 1);
    sparse_table.assign(n, std::vector<int>(height, -1));
    depth.resize(n);
    DFS(data, root, root);
  }

  int LeastAncestor(int u, int v) {
    if (depth[u] < depth[v]) {
      u, v = v, u;
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

 private:
  std::vector<std::vector<int>> sparse_table;
  std::vector<int> depth;
  int n;

  void DFS(const std::vector<std::vector<int>>& data, int v, int p) {
    sparse_table[v][0] = p;
    for (int i = 1; i < sparse_table[v].size(); i++) {
      if (sparse_table[v][i - 1] != -1) {
        sparse_table[v][i] = sparse_table[sparse_table[v][i - 1]][i - 1];
      }
    }
    for (const int u : data[v]) {
      if (u != p) {
        depth[u] = depth[v] + 1;
        DFS(data, u, v);
      }
    }
  }
};
