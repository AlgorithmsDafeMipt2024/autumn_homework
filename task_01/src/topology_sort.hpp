#ifndef TOPOLOGY_SORT_H_
#define TOPOLOGY_SORT_H_

#include <vector>

#include "../../lib/src/graph.h"

void dfs_mark_non_rec(Graph& g, std::vector<int>& marks,
                      std::vector<int>& visited, int start_name);

std::vector<int>* topological_sort_dfs_non_rec(Graph& g);

void dfs_mark_rec(Graph& g, std::vector<int>& marks, std::vector<int>& visited,
                  int vert);

std::vector<int>* topological_sort_dfs_rec(Graph& g);

#endif