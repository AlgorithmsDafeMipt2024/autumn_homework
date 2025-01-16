#include "bridge.hpp"
#include "router.hpp"
#include <gtest/gtest.h>
#include <iostream>

bool same_edges(std::vector<std::pair<int, int>> &a,
                std::vector<std::pair<int, int>> &b) {
  for (auto elem : a) {
    if ((std::find(b.begin(), b.end(), elem) == b.end()) &&
        (std::find(b.begin(), b.end(),
                   std::pair<int, int>({elem.second, elem.first})) ==
         b.end())) {
      return false;
    }
  }
  return true;
}

TEST(LocalNetwork, Line) {
  std::vector<std::vector<int>> data(
      {{1}, {0, 2}, {1, 3}, {2, 4}, {3, 5}, {4, 6}, {5, 7}, {6, 8}, {7}});
  std::vector<std::pair<int, int>> weak_edges = cutting_edge(data);
  std::vector<int> weak_vertexes = cutting_vertex(data);
  std::vector<std::pair<int, int>> ans_edge = {{2, 1}, {2, 3}, {3, 4}, {4, 5},
                                               {5, 6}, {6, 7}, {7, 8}};
  std::vector<int> ans_vert = {1, 2, 3, 4, 5, 6, 7};
  ASSERT_EQ(same_edges(ans_edge, weak_edges), true);
  ASSERT_EQ(weak_vertexes, ans_vert);
}

TEST(LocalNetwork, Tree) {
  std::vector<std::vector<int>> data({{2},
                                      {2},
                                      {0, 1, 4},
                                      {5, 7, 4},
                                      {9, 2, 3, 8},
                                      {3},
                                      {8},
                                      {3},
                                      {6, 4},
                                      {4}});
  std::vector<std::pair<int, int>> weak_edges = cutting_edge(data);
  std::vector<int> weak_vertexes = cutting_vertex(data);
  std::vector<std::pair<int, int>> ans_edge = {
      {2, 1}, {4, 9}, {3, 5}, {3, 7}, {4, 3}, {8, 6}, {4, 8}, {2, 4}, {0, 2}};
  std::vector<int> ans_vert = {2, 3, 4, 8};
  ASSERT_EQ(same_edges(ans_edge, weak_edges), true);
  ASSERT_EQ(weak_vertexes, ans_vert);
}

TEST(LocalNetwork, Circle) {
  std::vector<std::vector<int>> data(
      {{1, 8}, {0, 2}, {1, 3}, {2, 4}, {3, 5}, {4, 6}, {5, 7}, {6, 8}, {7, 0}});
  std::vector<std::pair<int, int>> weak_edges = cutting_edge(data);
  std::vector<int> weak_vertexes = cutting_vertex(data);
  std::vector<std::pair<int, int>> ans_edge = {};
  std::vector<int> ans_vert = {};
  ASSERT_EQ(same_edges(ans_edge, weak_edges), true);
  ASSERT_EQ(weak_vertexes, ans_vert);
}

TEST(LocalNetwork, Two_Circles) {
  std::vector<std::vector<int>> data(
      {{1, 3}, {0, 2}, {1, 3}, {2, 4}, {3, 5}, {4, 6}, {5, 7}, {6, 8}, {4, 7}});
  std::vector<std::pair<int, int>> weak_edges = cutting_edge(data);
  std::vector<int> weak_vertexes = cutting_vertex(data);
  std::vector<std::pair<int, int>> ans_edge = {{3, 4}};
  std::vector<int> ans_vert = {3, 4};
  std::cout << std::endl;
  ASSERT_EQ(same_edges(ans_edge, weak_edges), true);
  ASSERT_EQ(weak_vertexes, ans_vert);
}

TEST(LocalNetwork, Three_Circles) {
  std::vector<std::vector<int>> data({{1, 2},
                                      {0, 2},
                                      {1, 0, 3},
                                      {5, 4, 6},
                                      {3, 5},
                                      {4, 3},
                                      {3, 8, 7},
                                      {6, 8},
                                      {6, 7}});
  std::vector<std::pair<int, int>> weak_edges = cutting_edge(data);
  std::vector<int> weak_vertexes = cutting_vertex(data);
  std::vector<std::pair<int, int>> ans_edge = {{3, 2}, {3, 6}};
  std::vector<int> ans_vert = {2, 3, 6};
  ASSERT_EQ(same_edges(ans_edge, weak_edges), true);
  ASSERT_EQ(weak_vertexes, ans_vert);
}