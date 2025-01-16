#include "lca.hpp"

#include <algorithm>
#include <cmath>
#include <limits>
#include <queue>

void dfs_mark_rec(Graph& g, std::vector<int>& marks, std::vector<int>& visited,
                  int vert) {
  visited[vert] = 1;

  for (auto child : g.adjacents[vert]) {
    if (visited[child.name] == 1) {
      throw std::runtime_error("Graph contains cycle!");
    } else if (visited[child.name] == 0) {
      dfs_mark_rec(g, marks, visited, child.name);
    }
  }

  visited[vert] = 2;
  for (int i = 0; i < marks.size(); ++i) {
    if (marks[marks.size() - 1 - i] == -1) {
      marks[marks.size() - 1 - i] = vert;
      break;
    }
  }
}

std::vector<int>* topological_sort_dfs_rec(Graph& g) {
  if (g.size() == 0) {
    return new std::vector<int>();
  }

  std::vector<int> visited(g.size(),
                           0);  // 0 not started verticle , 1 started verticle ,
                                // 2 - finished verticle
  std::vector<int>* sorted = new std::vector<int>(g.size(), -1);

  bool calculated;
  for (int i = 0; i < visited.size(); ++i) {
    calculated = true;
    for (int j = 0; j < visited.size(); ++j) {
      if (visited[j] == 0) {
        calculated = false;
        dfs_mark_rec(g, *sorted, visited, j);
        break;
      }
    }
    if (calculated) {
      break;
    };
  }

  return sorted;
}

std::vector<std::vector<double>> rmq_sparse_table(std::vector<double>& data) {
  std::vector<std::vector<double>> sparse_table(
      std::log2(data.size()) + 1,
      std::vector<double>(data.size(),
                          std::numeric_limits<double>::infinity()));

  int wide;
  auto start = data.end();
  auto end = data.begin();
  for (int i = 0; i < sparse_table.size(); ++i) {
    for (int j = data.size() - 1; j >= 0; --j) {
      wide = std::pow(2, i);
      end = data.begin() + j + 1;
      start = end - wide;
      if (start >= data.begin()) {
        sparse_table[i][j] = *std::min_element(start, end);
      }
    }
  }

  return sparse_table;
}

double get_min_from_sparse_table(std::vector<std::vector<double>>& sparse_table,
                                 std::vector<int>& top_sort, int start_ind,
                                 int end_ind) {
  int const smaller_log = std::floor(std::log2(end_ind - start_ind + 1));
  if (std::pow(2, smaller_log) == (end_ind - start_ind + 1)) {
    return top_sort[sparse_table[smaller_log][end_ind]];
  }

  return top_sort[std::min(
      sparse_table[smaller_log][start_ind + std::pow(2, smaller_log) - 1],
      sparse_table[smaller_log][end_ind])];
}

std::vector<std::vector<double>> lca_sparse_table(Graph& g,
                                                  std::vector<int>& top_sort) {
  int root = top_sort[0];
  std::vector<double> data_for_sparse_table(g.size(), -1);

  int depth = 0;
  std::queue<std::pair<int, int>> q;  // vert, parent
  std::pair<int, int> v;
  q.push({root, -1});
  std::cout << root << " ";
  data_for_sparse_table[root] = 0;

  while (!q.empty()) {
    v = q.front();
    q.pop();
    std::cout << v.first << " ";

    for (auto child : g.adjacents[v.first]) {
      if (v.second != child.name) {
        depth++;
        data_for_sparse_table[child.name] = depth;
        q.push({child.name, v.first});
      }
    }
  }

  return rmq_sparse_table(data_for_sparse_table);
}

LCA::LCA(const Graph& g, int root) {
  const int height = std::floor(log2(g.size()) + 1);
  sparse_table =
      std::vector<std::vector<int>>(g.size(), std::vector<int>(height, -1));
  depth = std::vector<int>(g.size(), -1);
  dfs_mark_depth(g, root, root);
  for (int i = 0; i < sparse_table.size(); ++i) {
    for (int j = 0; j < sparse_table[0].size(); ++j) {
      std::cout << sparse_table[i][j] << " \t";
    }
    std::cout << std::endl;
  }
}

int LCA::get_parent(int u, int v) {
  if (depth[u] < depth[v]) {
    int t = v;
    v = u;
    u = v;
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