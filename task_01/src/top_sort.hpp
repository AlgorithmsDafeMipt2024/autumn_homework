#pragma once
#include <graph.hpp>

class CycleDetectedException : public std::logic_error {
  using std::logic_error::logic_error;
};

std::vector<int> TopologySort(int vertices, int edges,
                              std::vector<std::pair<int, int>> &vecEdges);