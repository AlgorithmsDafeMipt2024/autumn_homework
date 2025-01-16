#include <algorithm>
#include <gtest/gtest.h>
#include <vector>

void recursive_dfs(std::vector<std::vector<int>> &data, int root,
                   std::vector<int> &status, std::vector<int> &top_order) {
  status[root] = 1;
  for (int i = 0; i < data[root].size(); ++i) {
    if (status[data[root][i]] == 0) {
      recursive_dfs(data, data[root][i], status, top_order);
    } else if (status[data[root][i]] == 1) {
      throw std::runtime_error("cycle found");
    }
  }
  status[root] = 2;
  top_order.push_back(root);
}

std::vector<int> topological_sort(std::vector<std::vector<int>> &data) {
  int lenth = data.size();
  std::vector<int> status(lenth, 0);
  std::vector<int> top_order;
  int flag = 1;
  while (flag) {
    flag = 0;
    for (int i = 0; i < lenth; ++i) {
      if (status[i] != 2) {
        flag = 1;
        recursive_dfs(data, i, status, top_order);
        break;
      }
    }
  }
  std::reverse(top_order.begin(), top_order.end());
  return top_order;
}

bool check_test(std::vector<std::vector<int>> &data,
                std::vector<int> &top_order) {
  for (int i = 0; i < top_order.size(); ++i) {
    for (int j = i + 1; j < top_order.size(); ++j) {
      auto result = std::find(data[top_order[j]].begin(),
                              data[top_order[j]].end(), top_order[i]);
      if (result != data[top_order[j]].end()) {
        return false;
      }
    }
  }
  return true;
}

TEST(TopologySort, Tree) {
  std::vector<std::vector<int>> data(
      {{}, {}, {0, 1}, {5, 7}, {9, 2, 3, 8}, {}, {}, {}, {6}, {}});
  std::vector<int> top_order = topological_sort(data);
  ASSERT_EQ(check_test(data, top_order), true); // Stack []
}

TEST(TopologySort, TwoRoot) {
  std::vector<std::vector<int>> data(
      {{}, {4, 6}, {7}, {7, 4}, {5}, {}, {}, {0, 6, 5}});
  std::vector<int> top_order = topological_sort(data);
  ASSERT_EQ(check_test(data, top_order), true); // Stack []
}

TEST(TopologySort, ThreeRoot) {
  std::vector<std::vector<int>> data(
      {{1, 4, 6}, {4}, {3}, {}, {2, 5}, {2}, {4}, {6, 4, 2, 3}, {1, 5}});
  std::vector<int> top_order = topological_sort(data);
  ASSERT_EQ(check_test(data, top_order), true); // Stack []
}

TEST(TopologySort, OneRootOneLeaf) {
  std::vector<std::vector<int>> data({{2, 3, 4},
                                      {0, 2},
                                      {3, 6},
                                      {6},
                                      {3, 6},
                                      {0, 4},
                                      {},
                                      {1, 9},
                                      {7, 9, 5},
                                      {1, 0, 5}});
  std::vector<int> top_order = topological_sort(data);
  ASSERT_EQ(check_test(data, top_order), true); // Stack []
}

TEST(TopologySort, Cycle) {
  bool error = false;
  std::vector<std::vector<int>> data({{1}, {2, 3}, {3, 0}, {}});
  try {
    std::vector<int> top_order = topological_sort(data);
  } catch (std::runtime_error) {
    error = true;
  }
  ASSERT_EQ(error, true); // Stack []
}

TEST(TopologySort, Cycle2) {
  bool error = false;
  std::vector<std::vector<int>> data(
      {{}, {4, 6}, {7}, {7, 4}, {5}, {}, {2}, {0, 6, 5}});
  try {
    std::vector<int> top_order = topological_sort(data);
  } catch (std::runtime_error) {
    error = true;
  }
  ASSERT_EQ(error, true); // Stack []
}