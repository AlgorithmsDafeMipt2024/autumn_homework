#pragma once

#include <iostream>
#include <vector>

// UUG - undirected unweighted graph
// UWG - undirected weighted graph
// DUG - directed unweighted graph
// DWG - directed weighted graph

class UUGraph {
  std::vector<std::vector<int>> edgeList; // невзвешенный

  std::vector<int> visited; // массив для обхода

  void UUGAddEdge(int u, int v) {
    if (0 < u && u <= edgeList.size() && 0 < v && v <= edgeList.size()) {
      edgeList[u].push_back(v);
      edgeList[v].push_back(u);
    } else {
      std::cerr << "Uncorrected values";
    }
  }
};

class UWGraph {
  std::vector<std::vector<std::pair<int, double>>> edgeList; // взвешенный

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
  std::vector<std::vector<int>> graph; // невзвешенный
  std::vector<int> used;               // массив для обхода

  std::vector<int> topSort; // массив для топологической сортировки
  std::vector<int> color; // массив для цветов вершин

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
  std::vector<std::vector<std::pair<int, double>>> edgeListW; // взвешенный
  std::vector<int> visited;

  void DWGAddEdge(int u, int v, double weight) {
    if (0 < u && u <= edgeListW.size() && 0 < v && v <= edgeListW.size()) {
      edgeListW[u].push_back({v, weight});
    } else {
      std::cerr << "Uncorrected values";
    }
  }
};