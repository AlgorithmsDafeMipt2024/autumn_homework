#ifndef FIND_BRIDGES_CUT_VERTS_H_
#define FIND_BRIDGES_CUT_VERTS_H_

#include <vector>
#include "../../lib/src/graph.h"


bool dfs_path_to_vert_exist(Graph& g, std::vector<int>& path_visited,
                            std::pair<int, int>& deleted_edge, int vert,
                            int target);

void dfs_check_edges_rec(Graph& g, std::vector<int>& visited,
                         std::vector<std::pair<int, int>>& bridges, int vert);

// my own algorithm
std::vector<std::pair<int, int>> get_bridges(Graph& g);

void dfs_taryan(Graph& g, std::vector<bool>& visited, std::vector<int>& tin,
                std::vector<int>& fup,
                std::vector<std::pair<int, int>>& bridges, int time, int v,
                int p);

// taryan algorithm
std::vector<std::pair<int, int>> get_bridges_taryan(Graph& g);

void dfs_taryan_verts(Graph& g, std::vector<bool>& visited,
                      std::vector<int>& tin, std::vector<int>& fup,
                      std::vector<int>& cut_verts, int time, int v,
                      int p);

std::vector<int> get_cut_verts_taryan(Graph& g);

#endif