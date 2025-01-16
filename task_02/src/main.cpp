#include <iostream>
#include <vector>

using namespace std;

void dfs(vector<vector<int>> &gr, int v, vector<bool> &b) {
  b[v] = 1;
  for (int i = 0; i < gr.size(); ++i) {
    if (gr[v][i] != 0)
      if (!b[i]) dfs(gr, i, b);
  }
}

bool link_graph(vector<vector<int>> &gr, vector<bool> &s) {
  int V = gr.size();
  if (s[0] == 1)
    dfs(gr, 1, s);
  else
    dfs(gr, 0, s);
  for (int i = 0; i < V; i++) {
    if (!s[i]) return 0;
  }

  return 1;
}

int main() {
  vector<vector<int>> graph = {{0, 1, 1, 0, 0, 0}, {1, 0, 1, 0, 0, 0},
                               {1, 1, 0, 1, 0, 0}, {0, 0, 1, 0, 1, 0},
                               {0, 0, 0, 1, 0, 1}, {0, 0, 0, 0, 1, 0}};

  vector<vector<int>> new_graph(0);

  int V = graph.size();
  vector<bool> s(V);
  vector<bool> krit_v(V);
  vector<vector<int>> krit_most(0);

  for (int i = 0; i < V; ++i) {
    krit_v[i] = 0;
  }

  for (int i = 0; i < V; i++) {
    new_graph = graph;
    for (int h = 0; h < V; ++h) s[h] = 0;

    s[i] = 1;

    for (int k = 0; k < V; k++) {
      for (int l = 0; l < V; l++) {
        if (k == i) {
          new_graph[k][l] = 0;
        }
        if (l == i) {
          new_graph[k][l] = 0;
        }
      }
    }

    if (!link_graph(new_graph, s)) krit_v[i] = 1;
  }

  for (int i = 0; i < V; i++) {
    if (krit_v[i] == 1) {
      new_graph = graph;
      for (int h = 0; h < V; ++h) s[h] = 0;

      for (int k = 0; k < V; k++) {
        if (new_graph[i][k] != 0) {
          new_graph[i][k] = 0;
          new_graph[k][i] = 0;

          if (!link_graph(new_graph, s)) {
            krit_most.push_back({i, k});
          }
        }
      }
    }
  }

  cout << "Krit ver: ";
  for (int i = 0; i < V; i++) {
    if (krit_v[i] == 1) cout << i << " ";
  }
  cout << endl;

  cout << "Krit most:";
  for (int i = 0; i < krit_most.size(); i++) {
    cout << "[" << krit_most[i][0] << ", " << krit_most[i][1] << "], ";
  }
  cout << endl;

  return 0;
}