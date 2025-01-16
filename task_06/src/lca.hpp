#ifndef LCA_H_
#define LCA_H_

#include "../../lib/src/graph.h"

std::vector<int>* topological_sort_dfs_rec(Graph& g);

double get_min_from_sparse_table(std::vector<std::vector<double>>& sparse_table,
                                 std::vector<int>& top_sort, int start_ind,
                                 int end_ind);

std::vector<std::vector<double>> lca_sparse_table(Graph& g,
                                                  std::vector<int>& top_sort);

class LCA {
 public:
  LCA(const Graph& g, int root);

  int get_parent(int u, int v);

 private:
  std::vector<std::vector<int>> sparse_table;
  std::vector<int> depth;

  void dfs_mark_depth(const Graph& g, int v, int p);
};

#endif