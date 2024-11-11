#include <bits/stdc++.h>

#include <Graph.hpp>

using namespace std;

void Jonson(int n, int m, vector<vector<int>>& arr_edges) {
  int s = n + 1;
  for (int i = 1; i <= n; i++) {
    arr_edges.push_back({s, i, 0});
  }
  int new_n = n + 1;
  int new_m = m + n;
  Graph graph;
  graph.ReadWDG(new_n, new_m, arr_edges);
}
