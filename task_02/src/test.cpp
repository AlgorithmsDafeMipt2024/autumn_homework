
#include <gtest/gtest.h>

#include <initializer_list>

#include "find_bridges_cut_verts.hpp"

bool vector_int_equal(std::vector<int>& v1, std::initializer_list<int>& v2) {
  if (v1.size() != v2.size()) {
    return false;
  }

  for (auto elem : v1) {
    if (std::find(v2.begin(), v2.end(), elem) == v2.end()) {
      return false;
    }
  }
  return true;
}

bool vector_pair_equal(std::vector<std::pair<int, int>>& v1,
                       std::initializer_list<std::pair<int, int>>& v2) {
  if (v1.size() != v2.size()) {
    return false;
  }

  for (auto elem : v1) {
    if (std::find(v2.begin(), v2.end(), elem) == v2.end() &&
        std::find(v2.begin(), v2.end(),
                  std::pair<int, int>({elem.second, elem.first})) == v2.end()) {
      return false;
    }
  }
  return true;
}

TEST(get_bridges, Test_1) {
  Graph g(9, {{0, 1}, {0, 2}, {1, 2}, {2, 3}, {3, 4}, {5, 6}, {1, 6}, {2, 6},
              {3, 7}, {7, 8}, {4, 8}, {1, 0}, {2, 0}, {2, 1}, {3, 2}, {4, 3},
              {6, 5}, {6, 1}, {6, 2}, {7, 3}, {8, 7}, {8, 4}});
  std::vector<std::pair<int, int>> bridges = get_bridges(g);
  std::initializer_list<std::pair<int, int>> true_bridges = {{2, 3}, {5, 6}};

  ASSERT_EQ(vector_pair_equal(bridges, true_bridges), true);
}

TEST(get_bridges_taryan, Test_1) {
  Graph g(9, {{0, 1}, {0, 2}, {1, 2}, {2, 3}, {3, 4}, {5, 6}, {1, 6}, {2, 6},
              {3, 7}, {7, 8}, {4, 8}, {1, 0}, {2, 0}, {2, 1}, {3, 2}, {4, 3},
              {6, 5}, {6, 1}, {6, 2}, {7, 3}, {8, 7}, {8, 4}});
  std::vector<std::pair<int, int>> bridges = get_bridges_taryan(g);
  std::initializer_list<std::pair<int, int>> true_bridges = {{2, 3}, {5, 6}};

  ASSERT_EQ(vector_pair_equal(bridges, true_bridges), true);
}

TEST(get_cut_verts_taryan, Test_1) {
  Graph g(9, {{0, 1}, {0, 2}, {1, 2}, {2, 3}, {3, 4}, {5, 6}, {1, 6}, {2, 6},
              {3, 7}, {7, 8}, {4, 8}, {1, 0}, {2, 0}, {2, 1}, {3, 2}, {4, 3},
              {6, 5}, {6, 1}, {6, 2}, {7, 3}, {8, 7}, {8, 4}});
  std::vector<int> bridges = get_cut_verts_taryan(g);
  std::initializer_list<int> true_bridges = {2, 3, 6};

  ASSERT_EQ(vector_int_equal(bridges, true_bridges), true);
}

TEST(get_bridges, Test_2) {
  Graph g(3, {{0, 1}, {1, 0}, {0, 2}, {2, 0}, {1, 2}, {2, 1}});
  std::vector<std::pair<int, int>> bridges = get_bridges(g);
  std::initializer_list<std::pair<int, int>> true_bridges = {};

  ASSERT_EQ(vector_pair_equal(bridges, true_bridges), true);
}

TEST(get_bridges_taryan, Test_2) {
  Graph g(3, {{0, 1}, {1, 0}, {0, 2}, {2, 0}, {1, 2}, {2, 1}});
  std::vector<std::pair<int, int>> bridges = get_bridges_taryan(g);
  std::initializer_list<std::pair<int, int>> true_bridges = {};

  ASSERT_EQ(vector_pair_equal(bridges, true_bridges), true);
}

TEST(get_cut_verts_taryan, Test_2) {
  Graph g(3, {{0, 1}, {1, 0}, {0, 2}, {2, 0}, {1, 2}, {2, 1}});
  std::vector<int> bridges = get_cut_verts_taryan(g);
  std::initializer_list<int> true_bridges = {};

  ASSERT_EQ(vector_int_equal(bridges, true_bridges), true);
}

TEST(get_bridges, Test_3) {
  Graph g(4, {{0, 1}, {1, 0}, {0, 2}, {2, 0}, {1, 2}, {2, 1}, {0, 3}, {3, 0}});
  std::vector<std::pair<int, int>> bridges = get_bridges(g);
  std::initializer_list<std::pair<int, int>> true_bridges = {{0, 3}};

  ASSERT_EQ(vector_pair_equal(bridges, true_bridges), true);
}

TEST(get_bridges_taryan, Test_3) {
  Graph g(4, {{0, 1}, {1, 0}, {0, 2}, {2, 0}, {1, 2}, {2, 1}, {0, 3}, {3, 0}});
  std::vector<std::pair<int, int>> bridges = get_bridges_taryan(g);
  std::initializer_list<std::pair<int, int>> true_bridges = {{0, 3}};

  ASSERT_EQ(vector_pair_equal(bridges, true_bridges), true);
}

TEST(get_cut_verts_taryan, Test_3) {
  Graph g(4, {{0, 1}, {1, 0}, {0, 2}, {2, 0}, {1, 2}, {2, 1}, {0, 3}, {3, 0}});
  std::vector<int> bridges = get_cut_verts_taryan(g);
  std::initializer_list<int> true_bridges = {0};

  ASSERT_EQ(vector_int_equal(bridges, true_bridges), true);
}