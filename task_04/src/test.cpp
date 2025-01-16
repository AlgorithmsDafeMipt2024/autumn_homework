#include <gtest/gtest.h>
#include "dijkstra.hpp"

TEST(DijkstraTest, Simple) {
  std::vector<std::map<int, double>> data = {{{1, 8}, {2, 2}}, {{3, 4}}, {{1, 3}}, {}};
  std::vector<double> ans = {0, 5, 2, 9};
  ASSERT_EQ(Dijkstra(data, 0), ans); 
}

TEST(DijkstraTest, Pyramid) {
  std::vector<std::map<int, double>> data = {{{1, 1}, {2, 8}, {3, 5}, {4, 6}, {5, 6}}, {{2, 1}, {3, 11}, {4, 1}, {5, 8}}, {{3, 2}}, {{4, 2}}, {{5, 4}}, {{2, 1}}};
  std::vector<double> ans = {0, 1, 2, 4, 2, 6};
  ASSERT_EQ(Dijkstra(data, 0), ans); 
}
TEST(DijkstraTest, Sophisticated) {
    std::vector<std::map<int, double>> data = {{{1, 1}, {2, 8}, {3, 3}, {4, 5}, {5, 9}}, {{2, 2}, {3, 3}, {4, 2}}, {{3, 3}, {5, 4}}, {{4, 4}, {5, 6}, {6, 15}}, {{6, 10}}, {{6, 4}}, {}};
  std::vector<double> ans = {0, 1, 3, 3, 3, 7, 11};
  ASSERT_EQ(Dijkstra(data, 0), ans);
}


TEST(DijkstraTest, SimpleCycle) {
    std::vector<std::map<int, double>> data = {{{1, 9}, {2, 8}, {3, 3}}, {{4, 1}}, {{1, 2}, {3, 1}}, {{4, 2}}, {{2, 1}}};
  std::vector<double> ans = {0, 8, 6, 3, 5};
  ASSERT_EQ(Dijkstra(data, 0), ans);
}