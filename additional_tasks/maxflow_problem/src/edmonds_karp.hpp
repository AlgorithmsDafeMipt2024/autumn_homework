#include <climits>
#include <queue>
#include <vector>

using namespace std;

class MaxFlow {
 public:
  MaxFlow(int n, const vector<vector<int>>& edges) {
    capacity.resize(n + 1, vector<int>(n + 1, 0));
    adj.resize(n + 1);

    for (const auto& edge : edges) {
      const int u = edge[0], v = edge[1], c = edge[2];
      capacity[u][v] = c;
      adj[u].push_back(v);
      adj[v].push_back(u);
    }
  }

  int ComputeMaxFlow(int source, int sink) {
    int max_flow = 0;
    vector<int> parent(capacity.size());

    while (Bfs(source, sink, parent)) {
      int path_flow = INT_MAX;

      for (int v = sink; v != source; v = parent[v]) {
        const int u = parent[v];
        path_flow = min(path_flow, capacity[u][v]);
      }

      for (int v = sink; v != source; v = parent[v]) {
        const int u = parent[v];
        capacity[u][v] -= path_flow;
        capacity[v][u] += path_flow;
      }

      max_flow += path_flow;
    }

    return max_flow;
  }

 private:
  vector<vector<int>> capacity;
  vector<vector<int>> adj;

  bool Bfs(int source, int sink, vector<int>& parent) {
    const size_t n = capacity.size();
    vector<bool> visited(n, false);
    queue<int> q;
    q.push(source);
    visited[source] = true;
    parent[source] = -1;

    while (!q.empty()) {
      const int u = q.front();
      q.pop();

      for (const int v : adj[u]) {
        if (!visited[v] && capacity[u][v] > 0) {
          q.push(v);
          parent[v] = u;
          visited[v] = true;
          if (v == sink) {
            return true;
          }
        }
      }
    }

    return false;
  }
};
