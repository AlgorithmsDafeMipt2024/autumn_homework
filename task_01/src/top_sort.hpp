#pragma once
#include <algorithm>
#include <stdexcept>
#include <vector>
class CycleGraph : public std::logic_error {
  using std::logic_error::logic_error;
};

std::vector<int> TopSort(int vertices, int edges,
                         std::vector<std::pair<int, int>>& edge);