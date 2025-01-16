#include "find_bridges_cut_verts.hpp"

#include <algorithm>

bool dfs_path_to_vert_exist(Graph& g, std::vector<int>& path_visited,
                            std::pair<int, int>& deleted_edge, int vert,
                            int target) {
  path_visited[vert] = 1;
  for (auto child : g.adjacents[vert]) {
    if (child.name == target &&
        (std::pair<int, int>({vert, child.name}) != deleted_edge)) {
      return true;
    }
    if (path_visited[child.name] != 0 ||
        (std::pair<int, int>({vert, child.name}) == deleted_edge)) {
      continue;
    }
    if (dfs_path_to_vert_exist(g, path_visited, deleted_edge, child.name,
                               target)) {
      return true;
    }
  }
  path_visited[vert] = 2;
  return false;
}

void dfs_check_edges_rec(Graph& g, std::vector<int>& visited,
                         std::vector<std::pair<int, int>>& bridges, int vert) {
  visited[vert] = 1;

  for (auto child : g.adjacents[vert]) {
    std::vector<int> path_visited(g.size(), 0);
    std::pair<int, int> deleted_edge({child.name, vert});
    if (visited[child.name] != 1 &&
        (std::find(bridges.begin(), bridges.end(),
                   std::pair<int, int>({vert, child.name})) == bridges.end()) &&
        (std::find(bridges.begin(), bridges.end(),
                   std::pair<int, int>({child.name, vert})) == bridges.end())) {
      if (!dfs_path_to_vert_exist(g, path_visited, deleted_edge, child.name,
                                  vert)) {
        bridges.push_back({vert, child.name});
      }
      dfs_check_edges_rec(g, visited, bridges, child.name);
    }
  }

  visited[vert] = 2;
}

std::vector<std::pair<int, int>> get_bridges(Graph& g) {
  std::vector<int> visited(g.size(), 0);
  std::vector<std::pair<int, int>> bridges;

  bool all_verts_calculated;
  for (int i = 0; i < g.size(); ++i) {
    all_verts_calculated = true;
    for (int j = 0; j < g.size(); ++j) {
      if (visited[j] == 0) {
        all_verts_calculated = false;
        dfs_check_edges_rec(g, visited, bridges, j);
      }
    }
    if (all_verts_calculated) {
      break;
    }
  }
  return bridges;
}

void dfs_taryan(Graph& g, std::vector<bool>& visited, std::vector<int>& tin,
                std::vector<int>& fup,
                std::vector<std::pair<int, int>>& bridges, int time, int v,
                int p = -1) {
  visited[v] = true;
  tin[v] = fup[v] = time++;
  for (size_t i = 0; i < g.adjacents[v].size(); ++i) {
    int to = g.adjacents[v][i].name;
    if (to == p) continue;
    if (visited[to])
      fup[v] = std::min(fup[v], tin[to]);
    else {
      dfs_taryan(g, visited, tin, fup, bridges, time, to, v);
      fup[v] = std::min(fup[v], fup[to]);
      if (fup[to] > tin[v]) bridges.push_back(std::pair<int, int>({v, to}));
    }
  }
}

std::vector<std::pair<int, int>> get_bridges_taryan(Graph& g) {
  int time = 0;
  std::vector<int> tin(g.size(), -1);
  std::vector<int> fup(g.size(), -1);
  std::vector<std::pair<int, int>> bridges;

  std::vector<bool> visited(g.size(), false);
  for (int i = 0; i < g.size(); ++i)
    if (!visited[i]) dfs_taryan(g, visited, tin, fup, bridges, time, i);
  return bridges;
}

void dfs_taryan_verts(Graph& g, std::vector<bool>& visited,
                      std::vector<int>& tin, std::vector<int>& fup,
                      std::vector<int>& cut_verts, int time, int v,
                      int p = -1) {
  visited[v] = true;
  tin[v] = fup[v] = time++;
  int count = 0;
  for (auto child : g.adjacents[v]) {
    if (child.name == p) {
      continue;
    }
    if (visited[child.name]) {
      fup[v] = std::min(fup[v], tin[child.name]);
    } else {
      dfs_taryan_verts(g, visited, tin, fup, cut_verts, time, child.name, v);
      count++;
      fup[v] = std::min(fup[v], fup[child.name]);
      if (fup[child.name] >= tin[v] && p != -1) cut_verts.push_back(v);
    }
  }

  if (p == -1 && count >= 2) {
    cut_verts.push_back(v);
  }
}

std::vector<int> get_cut_verts_taryan(Graph& g) {
  int time = 0;
  std::vector<int> tin(g.size(), -1);
  std::vector<int> fup(g.size(), -1);
  std::vector<int> cut_verts;

  std::vector<bool> visited(g.size(), false);
  for (int i = 1; i < g.size(); ++i)
    if (!visited[i]) dfs_taryan_verts(g, visited, tin, fup, cut_verts, time, i);
  return cut_verts;
}