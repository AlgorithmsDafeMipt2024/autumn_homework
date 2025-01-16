#include <iostream>
#include <limits>
#include <vector>

#define INF numeric_limits<int>::max()
using namespace std;

int min_dist(const vector<int> &dist, const vector<bool> &visited) {
  int min = INF, min_index;
  for (int v = 0; v < dist.size(); ++v) {
    if (!visited[v] && dist[v] <= min) {
      min = dist[v];
      min_index = v;
    }
  }
  return min_index;
}

void Dijkstra_Algorithm(const vector<vector<int>> &graph, int source) {
  int V = graph.size();
  vector<int> dist(V, INF);
  vector<bool> visited(V, false);
  dist[source] = 0;

  for (int count = 0; count < V - 1; ++count) {
    int u = min_dist(dist, visited);
    visited[u] = true;

    for (int v = 0; v < V; ++v) {
      if (!visited[v] && graph[u][v] != 0 && dist[u] != INF &&
          dist[u] + graph[u][v] < dist[v]) {
        dist[v] = dist[u] + graph[u][v];
      }
    }
  }

  cout << "Shortest distance from a vertex " << source << ":\n";
  for (int i = 0; i < V; ++i) {
    cout << "Vertex " << i << ": "
         << (dist[i] == INF ? "INF" : to_string(dist[i])) << endl;
  }
}

int main() {
  vector<vector<int>> graph = {{0, 7, 9, 0, 0, 14},  {7, 0, 10, 15, 0, 0},
                               {9, 10, 0, 11, 0, 2}, {0, 15, 11, 0, 6, 0},
                               {0, 0, 0, 6, 0, 9},   {14, 0, 2, 0, 9, 0}};

  int V = graph.size();

  for (int source = 0; source < V; ++source) {
    Dijkstra_Algorithm(graph, source);
  }

  return 0;
}