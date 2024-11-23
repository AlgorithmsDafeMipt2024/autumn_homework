#include <gtest/gtest.h>

#include "edmonds_karp.hpp"

TEST(maxflow_problem, test1) {
  const int n = 6;
  const int m = 7;
  vector<vector<int>> const edges = {{1, 2, 10}, {1, 3, 10}, {2, 4, 25},
                                     {3, 4, 15}, {2, 5, 10}, {4, 5, 10},
                                     {5, 6, 10}};

  MaxFlow max_flow_solver(n, edges);
  const int source = 1;
  const int sink = 6;

  ASSERT_EQ(max_flow_solver.ComputeMaxFlow(source, sink), 10);
}

TEST(maxflow_problem, test2) {
  const int n = 5;
  const int m = 7;
  vector<vector<int>> const edges = {{1, 2, 10}, {1, 3, 20}, {2, 3, 5},
                                     {2, 4, 10}, {3, 4, 20}, {3, 5, 10},
                                     {4, 5, 20}};

  MaxFlow max_flow_solver(n, edges);
  const int source = 1;
  const int sink = 5;

  ASSERT_EQ(max_flow_solver.ComputeMaxFlow(source, sink), 30);
}

TEST(maxflow_problem, test3) {
  const int n = 4;
  const int m = 5;
  vector<vector<int>> const edges = {
      {1, 2, 100}, {1, 3, 50}, {2, 3, 50}, {2, 4, 50}, {3, 4, 100}};

  MaxFlow max_flow_solver(n, edges);
  const int source = 1;
  const int sink = 4;

  ASSERT_EQ(max_flow_solver.ComputeMaxFlow(source, sink), 150);
}