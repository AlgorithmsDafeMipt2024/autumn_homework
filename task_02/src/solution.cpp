#include "solution.h"

#include <utility>
#include <vector>

static std::vector<int> h, d;
static std::vector<bool> used;
static std::vector<int> lockers;
static std::vector<std::pair<int, int>> bridges;

void dfs_lockers(std::vector<node> &nodes, int v = 0, int p = -1) {
  used[v] = 1;
  d[v] = h[v] = (p == -1 ? 0 : h[p] + 1);
  int children = 0;
  for (auto u : nodes[v].neighbours) {
    if (u != p) {
      if (used[u])
        d[v] = std::min(d[v], h[u]);
      else {
        dfs_lockers(nodes, u, v);
        d[v] = std::min(d[v], d[u]);
        if (h[v] <= d[u]) {  // корень (p == -1) обрабатываем отдельно
          if (h[v] != d[u]) bridges.push_back(std::pair<int, int>(v, u));
          if (p != -1) lockers.push_back(v);
        }
        children++;
      }
    }
  }
  if (p == -1 && children > 1) {
    lockers.push_back(v);
  }
}
void dfs_bridges(std::vector<node> &nodes, int v = 0, int p = -1) {
  used[v] = true;
  d[v] = h[v] = (p == -1 ? 0 : h[p] + 1);
  for (auto u : nodes[v].neighbours) {
    if (u != p) {
      if (used[u])  // если ребро обратное
        d[v] = std::min(d[v], h[u]);
      else {  // если ребро прямое
        dfs_bridges(nodes, u, v);
        d[v] = std::min(d[v], d[u]);
        if (h[v] < d[u]) {
          bridges.push_back(std::pair<int, int>(v, u));
        }
      }
    }
  }
}

std::pair<std::vector<std::pair<int, int>>, std::vector<int>> solution(
    std::vector<node> nodes) {
  used.resize(nodes.size());
  h.resize(nodes.size());
  d.resize(nodes.size());
  lockers.clear();
  bridges.clear();
  for (int i = 0; i < nodes.size(); i++) {
    used[i] = 0;
    h[i] = d[i] = 0;
  }

  std::vector<node> nc = nodes;
  dfs_lockers(nodes);

  return std::pair<std::vector<std::pair<int, int>>, std::vector<int>>(bridges,
                                                                       lockers);
}
