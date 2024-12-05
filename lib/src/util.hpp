#pragma once

#include <vector>

#include "graph.hpp"

std::vector<int> FindWays(algo::Graph, int);

void Dijkstra(int, int, std::vector<int>&, std::vector<int>&,
              const AdjacencyList);