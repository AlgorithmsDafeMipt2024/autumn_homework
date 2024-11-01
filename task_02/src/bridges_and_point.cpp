#include <bridges_and_point.hpp>

#include "Graph.hpp"

using namespace std;

vector<vector<int>> gr;
vector<int> ret, h;
vector<int> u;

int one = 0;
set<int> ans;

void dfs(int v, int p) {
  if (p == -1)
    h[v] = 0;
  else
    h[v] = h[p] + 1;
  ret[v] = h[v];
  u[v] = true;
  for (auto& to : gr[v]) {
    if (to == p) continue;
    if (u[to]) {
      ret[v] = min(ret[v], h[to]);
    } else {
      if (p == -1) one++;
      dfs(to, v);
      ret[v] = min(ret[v], ret[to]);
      if (ret[to] >= h[v]) ans.insert(v);
    }
  }
}

set<int> cut_point(int& n, int& m, vector<pair<int, int>>& vec){
  Graph graph;
  graph.read_UUG(n, m, vec);
  u.resize(n + 1, 0);
  ret.resize(n + 1, 1e9);
  h.resize(n + 1, 1e9);
  gr = graph.gr;
  u = graph.used;
  for (int i = 1; i <= n; i++) {
    if (u[i] == 0) {
      one = 0;
      dfs(i, -1);
      if (one <= 1) {
        ans.erase(i);
      }
    }
  }
  return ans;
}
