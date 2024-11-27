#include <Graph.hpp>
#include <algorithm_Dijkstra.hpp>

using namespace std;

pair<pair<int, int>, vector<int>> Dijkstra(int& n, int& m, int& s, int& t,
                                           vector<vector<int>>& vec) {
  Graph graph;
  graph.ReadWUG(n, m, vec);
  vector<vector<pair<int, int>>> gr = graph.directed_graph;
  vector<int> put(n + 1, -1);
  set<pair<int, int>> dist;
  vector<int> visited(n + 1, 0);
  vector<int> ans(n + 1, 1e9);
  dist.emplace(0, s);
  ans[s] = 0;
  while (!dist.empty()) {
    auto [d, u] = *dist.begin();
    visited[u] = 1;
    dist.erase(dist.find(*dist.begin()));
    ans[u] = d;
    if (u == t) {
      break;
    }
    for (auto [v, d1] : gr[u]) {
      if (visited[v]) {
        continue;
      }
      int new_d = d + d1;
      if (new_d < ans[v]) {
        if (dist.find({ans[v], v}) != dist.end()) {
          dist.erase(dist.find({ans[v], v}));
        }
        ans[v] = new_d;
        put[v] = u;
        dist.emplace(new_d, v);
      }
    }
  }
  if (ans[t] == 1e9) {
    throw Nonexistent_way("There is no path from point s to point t");
  }
  vector<int> way;
  int tu = t;
  while (put[t] != -1) {
    way.push_back(t);
    t = put[t];
  }
  way.push_back(s);
  reverse(way.begin(), way.end());
  return make_pair(make_pair(ans[tu], way.size()), way);
}