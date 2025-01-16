#include <iostream>
#include <utility>
#include <vector>

static int l;
static std::vector<int> tin, tout;
static int timer;
static std::vector<std::vector<int>> up;

void dfs(int v, std::vector<std::vector<int>>& g, int p = 0) {
  tin[v] = ++timer;
  up[v][0] = p;
  for (int i = 1; i <= l; ++i)
    up[v][i] = up[up[v][i - 1]][i - 1];
  for (size_t i = 0; i < g[v].size(); ++i) {
    int to = g[v][i];
    if (to != p)
      dfs(to, g, v);
  }
  tout[v] = ++timer;
}

bool upper(int a, int b) {
  return tin[a] <= tin[b] && tout[a] >= tout[b];
}

std::vector<int> lca(std::vector<std::vector<int>>& g,
                     std::vector<std::pair<int, int>> dd) {
  tin.clear(), tout.clear(), up.clear();
  l = 0;
  tin.resize(g.size()), tout.resize(g.size()), up.resize(g.size());
  std::vector<int> ret = {};
  l = 0;
  while ((1 << l) <= g.size())
    ++l;
  for (int i = 0; i < g.size(); ++i)
    up[i].resize(l + 1);
  dfs(0, g);
  for (auto& dds : dd) {
    int a = dds.first, b = dds.second;
    std::cout << "as" << std::endl;
    if (upper(a, b)) {
      ret.push_back(a);
      continue;
    }
    if (upper(b, a)) {
      ret.push_back(b);
      continue;
    }
    for (int i = l; i >= 0; --i)
      if (!upper(up[a][i], b))
        a = up[a][i];
    ret.push_back(up[a][0]);
  }
  return ret;
}
