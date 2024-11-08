#include <bridges_and_point.hpp>

#include "Graph.hpp"

using namespace std;

vector<vector<int>> gr;
vector<int> ret, h;
vector<int> u;
vector<int> used, tin, fup, used_br;
vector<pair<int, int>> answer;
int timer = 1;

int one = 0;
set<int> ans;

void Dfs_cut_point(int v, int p) {
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
      Dfs_cut_point(to, v);
      ret[v] = min(ret[v], ret[to]);
      if (ret[to] >= h[v]) ans.insert(v);
    }
  }
}

set<int> Cut_point(int n, int m, Graph graph) {
  u.resize(n + 1, 0);
  ret.resize(n + 1, 1e9);
  h.resize(n + 1, 1e9);
  gr = graph.gr;
  u = graph.used;
  for (int i = 1; i <= n; i++) {
    if (u[i] == 0) {
      one = 0;
      Dfs_cut_point(i, -1);
      if (one <= 1) {
        ans.erase(i);
      }
    }
  }
  return ans;
}

void Dfs_cut_bridges(int u, int p = -1) {
  used_br[u] = 1;
  tin[u] = fup[u] = timer++;
  for (auto it : gr[u]) {
    if (it == p) {
      continue;
    }
    if (used_br[it]) {
      fup[u] = min(fup[u], tin[it]);
    } else {
      Dfs_cut_bridges(it, u);
      fup[u] = min(fup[u], fup[it]);
      if (fup[it] > tin[u]) {
        answer.push_back({u, it});
      }
    }
  }
}

vector<pair<int, int>> Cut_bridges(int n, int m, Graph graph) {
  tin.resize(n + 1, 0);
  fup.resize(n + 1, 1e9);
  used_br.resize(n + 1, 0);
  gr = graph.gr;
  used_br = graph.used;
  for (int i = 1; i <= n; i++) {
    if (!used_br[i]) {
      Dfs_cut_bridges(i);
    }
  }

  sort(answer.begin(), answer.end(), [](pair<int, int> u, pair<int, int> v) {
    return u.first + u.second < v.first + v.second;
  });

  return answer;
}

pair<set<int>, vector<pair<int, int>>> Answer(int n, int m,
                                              vector<pair<int, int>> vec) {
  Graph graph;
  graph.read_UUG(n, m, vec);
  vector<pair<int, int>> answer_bridges = Cut_bridges(n, m, graph);
  set<int> answer_point = Cut_point(n, m, graph);
  u.clear();
  ret.clear();
  h.clear();
  used_br.clear();
  tin.clear();
  fup.clear();
  answer.clear();
  ans.clear();
  return {answer_point, answer_bridges};
}