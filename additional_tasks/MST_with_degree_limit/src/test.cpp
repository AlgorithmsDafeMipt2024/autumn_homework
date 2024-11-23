#include <gtest/gtest.h>

#include "mst_with_degree_constraint.hpp"

TEST(MSTWithDegreeConstraintTest, BasicTest) {
  const int n = 5;
  std::vector<std::tuple<int, int, int>> const edges = {
      {0, 1, 10}, {0, 2, 6}, {0, 3, 5}, {1, 3, 15},
      {2, 3, 4},  {3, 4, 8}, {1, 4, 7}};
  const int max_degree = 3;

  MSTWithDegreeConstraint mst(n, edges, max_degree);
  std::vector<Edge> const result = mst.solve();

  ASSERT_EQ(result.size(), 6);

  std::vector<int> degree(n, 0);
  int total_weight = 0;
  for (const auto& edge : result) {
    degree[edge.u]++;
    degree[edge.v]++;
    total_weight += edge.weight;
  }

  for (const int d : degree) {
    ASSERT_LE(d, max_degree);
  }

  ASSERT_EQ(total_weight, 40);
}

TEST(MSTWithDegreeConstraintTest, DegreeConstraintTest) {
  const int n = 5;
  std::vector<std::tuple<int, int, int>> const edges = {
      {0, 1, 10}, {0, 2, 6}, {0, 3, 5}, {1, 3, 15},
      {2, 3, 4},  {3, 4, 8}, {1, 4, 7}};
  const int max_degree = 2;

  MSTWithDegreeConstraint mst(n, edges, max_degree);
  std::vector<Edge> const result = mst.solve();

  ASSERT_EQ(result.size(), 4);

  std::vector<int> degree(n, 0);
  int total_weight = 0;
  for (const auto& edge : result) {
    degree[edge.u]++;
    degree[edge.v]++;
    total_weight += edge.weight;
  }

  for (const int d : degree) {
    ASSERT_LE(d, max_degree);
  }

  ASSERT_EQ(total_weight, 22);
}

TEST(MSTWithDegreeConstraintTest, MinimalGraphTest) {
  const int n = 1;
  std::vector<std::tuple<int, int, int>> const edges = {};
  const int max_degree = 1;

  MSTWithDegreeConstraint mst(n, edges, max_degree);
  std::vector<Edge> const result = mst.solve();

  ASSERT_EQ(result.size(), 0);
}

TEST(MSTWithDegreeConstraintTest, DegreeExceedsLimitTest) {
  const int n = 4;
  std::vector<std::tuple<int, int, int>> const edges = {
      {0, 1, 10}, {0, 2, 6}, {1, 2, 5}, {1, 3, 7}, {2, 3, 4}};
  const int max_degree = 1;

  MSTWithDegreeConstraint mst(n, edges, max_degree);
  std::vector<Edge> const result = mst.solve();

  ASSERT_EQ(result.size(), 2);
}
