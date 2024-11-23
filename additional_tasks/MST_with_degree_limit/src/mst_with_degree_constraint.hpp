#ifndef MST_WITH_DEGREE_CONSTRAINT_H
#define MST_WITH_DEGREE_CONSTRAINT_H

#include <tuple>
#include <vector>

struct Edge {
  int u, v;
  int weight;

  Edge(int u, int v, int weight) : u(u), v(v), weight(weight) {}
};

class MSTWithDegreeConstraint {
 public:
  MSTWithDegreeConstraint(int n,
                          const std::vector<std::tuple<int, int, int>>& edges,
                          int max_degree)
      : n(n), max_degree(max_degree), edges_(edges) {}

  std::vector<Edge> solve();

 private:
  int n;
  int max_degree;
  std::vector<std::tuple<int, int, int>> edges_;

  bool is_valid(const std::vector<int>& degree, int u, int v);
  void kruskal(std::vector<Edge>& result, std::vector<int>& parent,
               std::vector<int>& rank);
  int find_parent(int v, const std::vector<int>& parent);
  void union_sets(int u, int v, std::vector<int>& parent,
                  std::vector<int>& rank);
};

#endif  // MST_WITH_DEGREE_CONSTRAINT_H
