#pragma once

#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

// UUG - undirected unweighted graph
// UWG - undirected weighted graph
// DUG - directed unweighted graph
// DWG - directed weighted graph

class UUGraph {
 public:
  std::vector<std::vector<int>> graph;  // невзвешенный
  std::vector<int> used;                // массив для обхода

  std::vector<int> cutPoints;                // мосты
  std::vector<std::pair<int, int>> bridges;  // точки сочленения

  std::vector<int> h,
      d;  // вспомогательные массивы для поиска мостов и точек сочленения

  std::vector<int> topSort;  // массив для топологической сортировки
  std::vector<int> color;  // массив для цветов вершин

  void UUGAddEdge(int u, int v) {
    if (0 < u && u <= graph.size() && 0 < v && v <= graph.size()) {
      graph[u].push_back(v);
      graph[v].push_back(u);
    } else {
      std::cerr << "Uncorrected values";
    }
  }

  void UUGReadGraph(int &vertices, int &edges,
                    std::vector<std::pair<int, int>> &vecEdges) {
    graph.resize(vertices + 1);
    used.resize(vertices + 1, 0);
    color.resize(vertices + 1, 0);
    d.resize(vertices + 1, 1e9);
    h.resize(vertices + 1, 0);
    for (int i = 0; i < edges; i++) {
      UUGAddEdge(vecEdges[i].first, vecEdges[i].second);
    }
  }

  void DFSBridgesAndCutPoints(int v, int parent = -1) {
    used[v] = true;
    d[v] = h[v] = (parent == -1 ? 0 : h[parent] + 1);
    int children = 0;
    for (int u : graph[v]) {
      if (u != parent) {
        if (used[u]) {
          d[v] = std::min(d[v], h[u]);
        } else {
          DFSBridgesAndCutPoints(u, v);
          d[v] = std::min(d[v], d[u]);
          if (h[v] < d[u]) {
            std::pair<int, int> bridge{u, v};
            bridges.push_back(bridge);
          }
          if (h[v] <= d[u] && parent != -1) {
            int cutPoint{v};
            cutPoints.push_back(cutPoint);
          }
          children++;
        }
      }
    }
    if (parent == -1 && children > 1) {
      int cutPoint{v};
      cutPoints.push_back(cutPoint);
    }

    std::set<int> tmp(cutPoints.begin(), cutPoints.end());
    cutPoints = std::vector<int>(tmp.begin(), tmp.end());
  }
};

class UWGraph {
 public:
  std::vector<std::vector<std::pair<int, double>>> edgeList;  // взвешенный

  void UWGAddEdge(int u, int v, double weight) {
    if (0 < u && u <= edgeList.size() && 0 < v && v <= edgeList.size()) {
      edgeList[u].push_back({v, weight});
      edgeList[v].push_back({u, weight});
    } else {
      std::cerr << "Uncorrected values";
    }
  }
};

class DUGraph {
 public:
  std::vector<std::vector<int>> graph;  // невзвешенный
  std::vector<int> used;                // массив для обхода

  std::vector<int> topSort;  // массив для топологической сортировки
  std::vector<int> color;  // массив для цветов вершин

  void DUGAddEdge(int u, int v) {
    if (0 < u && u <= graph.size() && 0 < v && v <= graph.size()) {
      graph[u].push_back(v);
    } else {
      std::cerr << "Uncorrected values";
    }
  }

  void DUGReadGraph(int &vertices, int &edges,
                    std::vector<std::pair<int, int>> &vecEdges) {
    graph.resize(vertices + 1);
    used.resize(vertices + 1, 0);
    color.resize(vertices + 1, 0);
    for (int i = 0; i < edges; i++) {
      DUGAddEdge(vecEdges[i].first, vecEdges[i].second);
    }
  }

  bool DUGDfsCycle(int v) {
    used[v] = 1;
    color[v] = 1;
    for (int edge : graph[v]) {
      int to = edge;
      if (!used[to]) {
        if (DUGDfsCycle(to)) {
          return true;
        }
      } else if (color[to] == 1) {
        return true;
      }
    }
    color[v] = 2;
    topSort.push_back(v);
    return false;
  }
};

class DWGraph {
  std::vector<std::vector<std::pair<int, double>>> edgeListW;  // взвешенный
  std::vector<int> visited;

  void DWGAddEdge(int u, int v, double weight) {
    if (0 < u && u <= edgeListW.size() && 0 < v && v <= edgeListW.size()) {
      edgeListW[u].push_back({v, weight});
    } else {
      std::cerr << "Uncorrected values";
    }
  }
};