#include "DSU.hpp"

#include <bits/stdc++.h>

using namespace std;

DSU::DSU(int n) : parent(n), rank(n, 0) {
  for (int i = 0; i < n; i++) parent[i] = i;
}

int DSU::find(int x) {
  if (parent[x] != x) {
    parent[x] = find(parent[x]);  // Path compression
  }
  return parent[x];
}

void DSU::unite(int x, int y) {
  int rootX = find(x);
  int rootY = find(y);
  if (rootX != rootY) {
    if (rank[rootX] > rank[rootY]) {
      parent[rootY] = rootX;
    } else if (rank[rootX] < rank[rootY]) {
      parent[rootX] = rootY;
    } else {
      parent[rootY] = rootX;
      rank[rootX]++;
    }
  }
}

bool Edge::operator<(const Edge& other) const { return weight < other.weight; }

int kruskalMST(int n, vector<Edge>& edges) {
  sort(edges.begin(), edges.end());
  DSU dsu(n);
  int mstWeight = 0, edgesUsed = 0;

  for (const Edge& edge : edges) {
    if (dsu.find(edge.u) != dsu.find(edge.v)) {
      dsu.unite(edge.u, edge.v);
      mstWeight += edge.weight;
      edgesUsed++;
      if (edgesUsed == n - 1) break;
    }
  }

  return (edgesUsed == n - 1) ? mstWeight : -1;  // -1 if MST is not possible
}

int main_part(int& n, int& m, vector<vector<int>>& vec) {
  vector<Edge> edges(m);
  for (int i = 0; i < m; i++) {
    edges[i].u = vec[i][0] - 1;  // Уменьшаем на 1 для 0-индексации
    edges[i].v = vec[i][1] - 1;  // Уменьшаем на 1 для 0-индексации
    edges[i].weight = vec[i][2];
  }

  int result = kruskalMST(n, edges);
  if (result != -1) {
    return result;
  } else {
    throw NotMST("MST does not exist");
  }
  return 0;
}
