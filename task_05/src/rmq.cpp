#include "rmq.h"

#include <algorithm>
#include <cmath>
#include <limits>
#include <vector>

const int powers[] = {1,     2,     4,     8,      16,    32,   64,
                      128,   256,   512,   1024,   2048,  4096, 8192,
                      16384, 32768, 65536, 131072, 262144};

std::vector<int> rmq(int *A, int sz, std::vector<std::pair<int, int>> brd) {
  std::vector<std::vector<int>> minn;
  std::vector<int> ret;
  minn.push_back({});
  minn[0].assign(A, A + sz);
  int tmp = 1;
  while (minn[tmp - 1].size() > 2) {
    minn.push_back({});
    for (int i = 1; i < minn[tmp - 1].size(); i += 2) {
      minn[tmp].push_back(std::min(minn[tmp - 1][i - 1], minn[tmp - 1][i]));
    }
    minn[tmp].push_back(std::numeric_limits<int>::max());
    tmp++;
  }

  for (auto &i : brd) {
    tmp = i.second - i.first;
    int minC = std::numeric_limits<int>::max();
    if (tmp < 8) {
      for (int j = i.first; j <= i.second; j++) {
        minC = std::min(minC, A[j]);
      }
      ret.push_back(minC);
      continue;
    }
    int j = minn.size();
    while (powers[j] > tmp) {
      j--;
    }
    j--;
    int start = i.first / powers[j], stop = i.second / powers[j];

    for (int k = start + 1; k < stop; k++) {
      minC = std::min(minC, minn[j][k]);
    }
    int k = j;
    if (minC > minn[k][stop] && k > 0) {
      stop = stop * powers[j];
      while (k > 0) {
        k--;
        for (; stop + powers[k] <= i.second; stop += powers[k]) {
          minC = std::min(minC, minn[k][stop / powers[k]]);
        }
      }
    }
    k = j;
    if (minC > minn[k][start] && k > 0) {
      start = (start + 1) * powers[j];
      while ((--k) >= 0) {
        for (; start >= i.first; start -= powers[k]) {
          minC = std::min(minC, minn[k][start / powers[k]]);
        }
      }
    }
    minC = std::min(minC, A[i.first]);
    minC = std::min(minC, A[i.second]);
    ret.push_back(minC);
  }
  return ret;
}
