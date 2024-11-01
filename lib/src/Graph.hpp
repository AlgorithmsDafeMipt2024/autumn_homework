#include <bits/stdc++.h>

using namespace std;

struct Edge {
  int from, to, weight;
};

struct Graph {
  vector<vector<int>> gr;
  vector<vector<pair<int, int>>> directed_graph;
  vector<int> used;
  vector<int> color;
  vector<int> parents;
  vector<int> topsort;
  vector<vector<int>> comps;
  vector<int> dist;
  int cnt = 0;

  void read_WUG(int& n, int& m,
                vector<vector<int>>& vec) {// взвешенный неориентированный
    directed_graph.resize(n + 1);
    used.resize(n + 1, 0);
    color.resize(n + 1, 0);
    parents.resize(n + 1, -1);
    comps.resize(n + 1);
    for (int i = 0; i < m; i++) {
      int u, v, w;
      u = vec[i][0];
      v = vec[i][1];
      w = vec[i][2];
      directed_graph[u].push_back({v, w});
      directed_graph[v].push_back({u, w});
    }
  }

  void read_WDG(int& n, int& m,
                vector<vector<int>>& vec) {// взвешенный ориентированный
    directed_graph.resize(n + 1);
    used.resize(n + 1, 0);
    color.resize(n + 1, 0);
    parents.resize(n + 1, -1);
    comps.resize(n + 1);
    for (int i = 0; i < m; i++) {
      int u, v, w;
      u = vec[i][0];
      v = vec[i][1];
      w = vec[i][2];
      directed_graph[u].push_back({v, w});
    }
  }

  void read_UUG(int& n, int& m,
                vector<pair<int, int>>& vec) {// невзвешенный неориентированный
    gr.resize(n + 1);
    used.resize(n + 1, 0);
    comps.resize(n + 1);
    for (int i = 0; i < m; i++) {
      int u, v;
      u = vec[i].first;
      v = vec[i].second;
      gr[u].push_back(v);
      gr[v].push_back(u);
    }
  }

  void read_UDG(int& n, int& m,
                vector<pair<int, int>>& vec) {// невзвешенный ориентированный
    gr.resize(n + 1);
    used.resize(n + 1, 0);
    color.resize(n + 1, 0);
    parents.resize(n + 1, -1);
    comps.resize(n + 1);
    for (int i = 0; i < m; i++) {
      int u, v;
      u = vec[i].first;
      v = vec[i].second;
      gr[u].push_back(v);
    }
  }

  void dfs(int u, int count) {
    used[u] = 1;
    comps[count].push_back(u);
    for (auto it: gr[u]) {
      if (!used[it]) {
        dfs(it, count);
      }
    }
    topsort.push_back(u);
  }

  vector<vector<int>> components(int& n) {
    for (int i = 1; i <= n; i++) {
      if (!used[i]) {
        dfs(i, cnt++);
      }
    }
    return comps;
  }

  bool has_cycle_undirected(int& n) {
    for (int i = 1; i <= n; i++) {
      if (!used[i]) {
        if (dfs_cycle_undirected(i, -1)) {
          return true;
        }
      }
    }
    return false;
  }

  bool dfs_cycle_undirected(int v, int p) {
    used[v] = 1;
    for (int to: gr[v]) {
      if (!used[to]) {
        if (dfs_cycle_undirected(to, v)) {
          return true;
        };
      } else if (to != p) {
        return true;
      }
    }
    return false;
  }

  bool has_cycle_directed(int& n) {
    for (int i = 1; i <= n; i++) {
      if (!used[i]) {
        if (dfs_cycle_directed_W(i)) {
          return true;
        }
      }
    }
    return false;
  }

  bool dfs_cycle_directed_W(int v) {
    used[v] = 1;
    color[v] = 1;
    for (auto &edge: directed_graph[v]) {
      int to = edge.first;
      if (!used[to]) {
        if (dfs_cycle_directed_W(to)) {
          return true;
        }
      } else if (color[to] == 1) {
        return true;
      }
    }
    color[v] = 2;
    return false;
  }

  //Используется для нахождения Top_Sort и проверке на циклы
  bool dfs_cycle_directed_U(int v) {
    used[v] = 1;
    color[v] = 1;
    for (auto &edge: gr[v]) {
      int to = edge;
      if (!used[to]) {
        if (dfs_cycle_directed_U(to)) {
          return true;
        }
      } else if (color[to] == 1) {
        return true;
      }
    }
    color[v] = 2;
    topsort.push_back(v);
    return false;
  }
};