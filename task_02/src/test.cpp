
#include <gtest/gtest.h>
#include <vector>

#include "solution.h"

TEST(StackTest, Simple) {
  std::vector<node> nodes;

  int n, k = 0, tmp, N;
  N = 4;
  tmp = 4;  // колич
  nodes.resize(N);
  // список ребер
  std::vector<std::pair<int, int>> loh = {{0, 1}, {1, 2}, {2, 3}, {0, 2}};
  while (k < tmp) {
    nodes[loh[k].first].neighbours.push_back(loh[k].second);
    nodes[loh[k].second].neighbours.push_back(loh[k].first);
    k++;
  }

  auto ans = solution(nodes);

  bool flag = true;
  ans = solution(nodes);
  std::vector<std::pair<int, int>> assertionb = {{2, 3}};
  ASSERT_TRUE(assertionb.size() == ans.first.size());
  for (int i = 0; i < ans.first.size(); i++) {
    flag = flag && (ans.first[i].first == assertionb[i].first) &&
           (ans.first[i].second == assertionb[i].second);
  }
  std::vector<int> assertionn = {2};
  ASSERT_TRUE(assertionn.size() == ans.second.size());
  for (int i = 0; i < ans.first.size(); i++) {
    flag = flag && (ans.second[i] == assertionn[i]);
  }
  ASSERT_TRUE(flag);
}

TEST(MinStackTest, SimpleNoBriges) {
  std::vector<node> nodes;

  int n, k = 0, tmp, N;
  N = 4;
  nodes.resize(N);
  // список ребер
  std::vector<std::pair<int, int>> loh = {
      {0, 1}, {1, 2}, {2, 3}, {0, 2}, {0, 3}};
  tmp = loh.size();  // колич
  while (k < tmp) {
    nodes[loh[k].first].neighbours.push_back(loh[k].second);
    nodes[loh[k].second].neighbours.push_back(loh[k].first);
    k++;
  }

  auto ans = solution(nodes);

  bool flag = true;
  ans = solution(nodes);
  std::vector<std::pair<int, int>> assertionb = {};
  ASSERT_TRUE(assertionb.size() == ans.first.size());
  for (int i = 0; i < ans.first.size(); i++) {
    flag = flag && (ans.first[i].first == assertionb[i].first) &&
           (ans.first[i].second == assertionb[i].second);
  }
  std::vector<int> assertionn = {};
  ASSERT_TRUE(assertionn.size() == ans.second.size());
  for (int i = 0; i < ans.first.size(); i++) {
    flag = flag && (ans.second[i] == assertionn[i]);
  }
  ASSERT_TRUE(flag);
}
