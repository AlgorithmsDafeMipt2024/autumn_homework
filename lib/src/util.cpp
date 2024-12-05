#include "util.hpp"

#include <climits>
#include <queue>
#include <utility>
#include <vector>

#include "graph.hpp"

using namespace std;

vector<int> FindWays(algo::Graph graph, int start) {
  vector<int> vis(graph.GetVertexesNum());
  vector<int> dst(graph.GetVertexesNum(), INT_MAX);

  dst[start - 1] = 0;

  Dijkstra(start - 1, -1, vis, dst, graph.GetAdjList());

  return dst;
}

void Dijkstra(int v, int from, vector<int>& vis, vector<int>& dst,
              const AdjacencyList adj) {
  priority_queue<pair<int, int>, vector<pair<int, int>>,
                 greater<pair<int, int>>>
      q;

  q.push({0, v});
  while (!q.empty()) {
    auto [cur_d, v] = q.top();
    q.pop();

    if (cur_d > dst[v]) continue;

    for (auto [u, w] : adj[v]) {
      if (dst[u] > dst[v] + w) {
        dst[u] = dst[v] + w;

        q.push({dst[u], u});
      }
    }
  }
}
