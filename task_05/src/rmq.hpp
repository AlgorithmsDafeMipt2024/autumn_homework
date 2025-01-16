#pragma once

#include <math.h>

#include <algorithm>
#include <cmath>
#include <limits>
#include <vector>
std::vector<std::vector<double>> sparse(std::vector<double> &data) {
  std::vector<std::vector<double>> sparse_table(
      log2(data.size()) + 1,
      std::vector<double>(data.size(),
                          std::numeric_limits<double>::infinity()));
  auto start = data.begin();
  auto end = data.end();
  int height;
  for (int i = 0; i < sparse_table.size(); ++i) {
    for (int j = data.size() - 1; j >= 0; --j) {
      start = data.begin() + j + 1;
      height = std::pow(2, i);
      end = start - height;
      if (end >= data.begin()) {
        sparse_table[i][j] = *std::min_element(end, start);
      }
    }
  }
  return sparse_table;
}

double inf(std::vector<std::vector<double>> &sparse_table, int u, int v) {
  int const width = log2(v - u + 1);
  if (std::pow(2, width) == (v - u + 1)) {
    return sparse_table[width][v];
  }
  return std::min(sparse_table[width][u + std::pow(2, width) - 1],
                  sparse_table[width][v]);
}