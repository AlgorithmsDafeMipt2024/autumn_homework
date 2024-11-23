#include "mst_with_degree_constraint.h"

#include <algorithm>
#include <numeric>
#include <tuple>
#include <vector>

using std::get;
using std::tuple;
using std::vector;

int MSTWithDegreeConstraint::find_parent(int v, const vector<int>& parent) {
  if (parent[v] != v) {
    return find_parent(parent[v], parent);
  }
  return v;
}

void MSTWithDegreeConstraint::union_sets(int u, int v, vector<int>& parent,
                                         vector<int>& rank) {
  u = find_parent(u, parent);
  v = find_parent(v, parent);

  if (u != v) {
    if (rank[u] < rank[v]) {
      std::swap(u, v);
    }
    parent[v] = u;
    if (rank[u] == rank[v]) {
      rank[u]++;
    }
  }
}

bool MSTWithDegreeConstraint::is_valid(const vector<int>& degree, int u,
                                       int v) {
  return degree[u] < max_degree && degree[v] < max_degree;
}

void MSTWithDegreeConstraint::kruskal(vector<Edge>& result, vector<int>& parent,
                                      vector<int>& rank) {
  sort(edges_.begin(), edges_.end(),
       [](const tuple<int, int, int>& a, const tuple<int, int, int>& b) {
         return get<2>(a) < get<2>(b);
       });

  vector<int> degree(n, 0);

  for (auto& edge : edges_) {
    int u = get<0>(edge);
    int v = get<1>(edge);
    int weight = get<2>(edge);

    if (is_valid(degree, u, v)) {
      result.push_back(Edge(u, v, weight));
      degree[u]++;
      degree[v]++;
      union_sets(u, v, parent, rank);
    }
  }
}

vector<Edge> MSTWithDegreeConstraint::solve() {
  vector<Edge> result;
  vector<int> parent(n), rank(n, 0);

  iota(parent.begin(), parent.end(), 0);

  kruskal(result, parent, rank);

  return result;
}
