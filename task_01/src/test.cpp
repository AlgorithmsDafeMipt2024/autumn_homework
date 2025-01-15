#include <gtest/gtest.h>
#include "main.cpp"
#include <vector>

bool check_test(std::vector<std::vector<int>>& data, std::vector<int>& top_order){
  for (int i = 0; i < top_order.size(); ++i){
    for (int j = i+1; j < top_order.size(); ++j){
       auto result = std::find(data[top_order[j]].begin(), data[top_order[j]].end(), top_order[i]);
       if (result != data[top_order[j]].end()){
        return false;
       }
    }
  }
  return true;
}

TEST(TopologySort, Tree) {
  std::vector<std::vector<int>> data({{}, {}, {0, 1}, {5, 7}, {9, 2, 3, 8}, {}, {}, {}, {6}, {}});
  std::vector<int> top_order = topological_sort(data);
  ASSERT_EQ(check_test(data, top_order), true);  // Stack []
}

TEST(TopologySort, TwoRoot) {
  std::vector<std::vector<int>> data({{}, {4, 6}, {7}, {7, 4}, {5}, {}, {}, {0, 6, 5}});
  std::vector<int> top_order = topological_sort(data);
  ASSERT_EQ(check_test(data, top_order), true);  // Stack []
}

TEST(TopologySort, ThreeRoot){
  std::vector<std::vector<int>> data({{1, 4, 6}, {4}, {3}, {}, {2, 5}, {2}, {4}, {6, 4, 2, 3}, {1, 5}});
  std::vector<int> top_order = topological_sort(data);
  ASSERT_EQ(check_test(data, top_order), true);  // Stack []
}

TEST(TopologySort, OneRootOneLeaf){
  std::vector<std::vector<int>> data({{2, 3, 4}, {0, 2}, {3, 6}, {6}, {3, 6}, {0, 4}, {}, {1, 9}, {7, 9, 5}, {1, 0, 5}});
  std::vector<int> top_order = topological_sort(data);
  ASSERT_EQ(check_test(data, top_order), true);  // Stack []
}

TEST(TopologySort, Cycle) {
  bool error = false;
  std::vector<std::vector<int>> data({{1}, {2, 3}, {3, 0}, {}});
  try {
    std::vector<int> top_order = topological_sort(data);
  } catch (std::runtime_error) {
    error = true;
  }
  ASSERT_EQ(error, true);  // Stack []
}

TEST(TopologySort, Cycle2) {
  bool error = false;
  std::vector<std::vector<int>> data({{}, {4, 6}, {7}, {7, 4}, {5}, {}, {2}, {0, 6, 5}});
  try {
    std::vector<int> top_order = topological_sort(data);
  } catch (std::runtime_error) {
    error = true;
  }
  ASSERT_EQ(error, true);  // Stack []
}