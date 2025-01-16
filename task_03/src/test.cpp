#include <gtest/gtest.h>

#include <vector>

#include "solution.h"

TEST(Deixtra, Simple) {
  std::vector<node> nodes;
  std::vector<int> edges = {0, 1, 1, 4, 0, 1, 2, 1, 0};
  int n = 3, start = 1, finish = 0, tmp;
  nodes.resize(n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i == j) {
        continue;
      }
      nodes[i].neighbours.push_back({j, edges[i * n + j]});
    }
  }
  deixtra(nodes, start - 1);

  ASSERT_TRUE(nodes[finish].len = 3);
}

TEST(Deixtra, Simple2) {
  std::vector<node> nodes;
  std::vector<int> edges = {0, 1, 1, 4, 0, 7, 2, 1, 0};
  int n = 3, start = 1, finish = 0, tmp;
  nodes.resize(n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i == j) {
        continue;
      }
      nodes[i].neighbours.push_back({j, edges[i * n + j]});
    }
  }
  deixtra(nodes, start - 1);

  ASSERT_TRUE(nodes[finish].len = 4);
}

TEST(Jonson, Simple) {
  std::vector<std::vector<int>> expected = {{0, -1, 2, -2, 1},
                                            {999, 0, 3, -1, 2},
                                            {1000, 998, 0, 997, 1000},
                                            {1000, 1, 4, 0, 3},
                                            {997, -2, 1, -3, 0}};
  std::vector<node> nodes;
  std::vector<int> edges = {0,    -1,   4,    1000, 1000, 1000, 0,    3, 2,
                            2,    1000, 1000, 0,    1000, 1000, 1000, 1, 5,
                            1000, 1000, 1000, 1000, 1000, -3,   1000};
  int n = 5, tmp;
  nodes.resize(n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i == j) {
        continue;
      }
      nodes[i].neighbours.push_back({j, edges[i * n + j]});
    }
  }
  auto ans = jonson(nodes);
  for (int i = 0; i < ans.size(); i++) {
    for (int j = 0; j < ans.size(); j++) {
      if (i == j) {
        continue;
      }
      ASSERT_TRUE(ans[i][j] == expected[i][j])
          << i << " " << j << " " << ans[i][j] << " " << expected[i][j];
    }
  }
}
