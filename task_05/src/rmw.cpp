#include <algorithm>
#include <cmath>
#include <limits>

#include "rmq.hpp"

std::vector<std::vector<double>> rmq_sparse_table(std::vector<double>& data) {
  std::vector<std::vector<double>> sparse_table(
      std::log2(data.size()) + 1,
      std::vector<double>(data.size(),
                          std::numeric_limits<double>::infinity()));

  int wide;
  auto start = data.end();
  auto end = data.begin();
  for (int i = 0; i < sparse_table.size(); ++i) {
    for (int j = data.size() - 1; j >= 0; --j) {
      wide = std::pow(2, i);
      end = data.begin() + j + 1;
      start = end - wide;
      if (start >= data.begin()) {
        sparse_table[i][j] = *std::min_element(start, end);
      }
    }
  }

  return sparse_table;
}

double get_min_from_sparse_table(std::vector<std::vector<double>>& sparse_table,
                                 int start_ind, int end_ind) {
  int smaller_log = std::floor(std::log2(end_ind - start_ind + 1));
  if (std::pow(2, smaller_log) == (end_ind - start_ind + 1)) {
    return sparse_table[smaller_log][end_ind];
  }

  return std::min(
      sparse_table[smaller_log][start_ind + std::pow(2, smaller_log) - 1],
      sparse_table[smaller_log][end_ind]);
}