#include <cstdlib>
#include <gtest/gtest.h>
#include <limits>
#include <utility>
#include <vector>

#include "rmq.h"

int ROFLS_KATKA(int *A, int start, int stop) {
  int mn = std::numeric_limits<int>::max();
  for (int i = start; i <= stop; i++) {
    mn = std::min(A[i], mn);
  }
  return mn;
}

TEST(Test, Simple) {
  int a[] = {1, 2, 3, -1, 5, 6};
  auto ans = rmq(a, 6, {{0, 2}});
  ASSERT_TRUE(ans[0] == ROFLS_KATKA(a, 0, 2));
}

TEST(Test, Rand) {
  int a[50], tmp = 0;
  srand(22848);
  std::vector<std::pair<int, int>> dd;
  for (int i = 0; i <= 40; i++) {
    for (int j = i; j <= 40; j++) {
      dd.push_back({i, j});
    }
    a[i] = rand();
  }
  auto ans = rmq(a, 50, dd);

  for (int i = 0; i < 40; i++) {
    for (int j = i; j <= 40; j++) {
      ASSERT_TRUE(ans[tmp] == ROFLS_KATKA(a, i, j)) << i << " " << j;
      tmp++;
    }
  }
}
