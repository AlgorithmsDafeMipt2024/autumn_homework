#pragma once

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

class NotMST : public logic_error {
  using logic_error::logic_error;
};

class DSU {
 public:
  DSU(int n);
  int find(int x);
  void unite(int x, int y);

 private:
  vector<int> parent;
  vector<int> rank;
};

struct Edge {
  int u, v, weight;
  bool operator<(const Edge& other) const;
};

int kruskalMST(int n, vector<Edge>& edges);

int main_part(int& n, int& m, vector<vector<int>>& vec);