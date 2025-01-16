#ifndef JOHNSON_H_
#define JOHNSON_H_

#include "../../lib/src/graph.h"

std::vector<int>* topological_sort_dfs_rec(Graph& g);

void dfs_mark_rec(Graph& g, std::vector<int>& marks, std::vector<int>& visited,
                  int vert);

std::vector<double> belllman_ford(Graph& g, int start_vert);

#endif