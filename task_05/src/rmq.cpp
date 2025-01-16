#include "rmq.hpp"

#include <algorithm>
#include <cmath>
#include <limits>

RMQ::RMQ(std::vector<double> data) {
  sparse_table = std::vector<std::vector<double>>(
      std::log2(data.size()) + 1,
      std::vector<double>(data.size(),
                          std::numeric_limits<double>::infinity()));
  int wide;
  auto start = data.end();
  auto end = data.begin();
  for (int i = 0; i < sparse_table.size(); ++i) {
    for (int j = data.size() - 1; j >= 0; --j) {
      wide = (1 << i);
      end = data.begin() + j + 1;
      start = end - wide;
      if (start >= data.begin()) {
        sparse_table[i][j] = *std::min_element(start, end);
      }
    }
  }
}

double RMQ::get_min(int first_ind, int last_ind) {
  int const smaller_log = std::floor(std::log2(last_ind - first_ind + 1));
  if (std::pow(2, smaller_log) == (last_ind - first_ind + 1)) {
    return sparse_table[smaller_log][last_ind];
  }

  return std::min(
      sparse_table[smaller_log][first_ind + std::pow(2, smaller_log) - 1],
      sparse_table[smaller_log][last_ind]);
}
