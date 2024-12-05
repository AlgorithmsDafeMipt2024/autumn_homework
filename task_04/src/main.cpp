#include <climits>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

#include "graph.hpp"

using namespace algo;
using namespace std;

void dijkstra(int v, int from, vector<int>& vis, vector<int>& dst,
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

int main() {
  int vertexes_num, edges_num;
  cin >> vertexes_num >> edges_num;

  algo::Graph graph(vertexes_num, edges_num, true);

  for (int i = 0; i < edges_num; i++) {
    int a, b, w;

    cin >> a >> b >> w;

    graph.addEdge(a, b, w);
  }

  vector<int> vis(vertexes_num);
  vector<int> dst(vertexes_num, INT_MAX);

  int start;
  cin >> start;

  start--;
  dst[start] = 0;
  dijkstra(start, -1, vis, dst, graph.getAdjList());

  for (int i = 0; i < dst.size(); i++) {
    cout << i + 1 << ": " << dst[i] << endl;
  }
}
