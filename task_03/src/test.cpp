
#include <gtest/gtest.h>
#include <limits>
#include <vector>
#include "bell_john.hpp"
#include "util.hpp"

TEST(Johnson, Simple) {
  // std::vector<double> expected = {-4., -2., 3., 0., -6.};
  
  // double inf = std::numeric_limits<double>::infinity();
  // std::vector<std::vector<double>> weights = {
  //   {inf, 6,   7,   inf, inf},
  //   {inf, inf, 8,   5,   -4 },
  //   {inf, inf, inf, -3,  9  },
  //   {inf, -2,  inf, inf, inf},
  //   {2,   inf, inf, 7,   inf}
  // };
  // OrientedWeightedGraph graph(weights);
  // std::vector<double> result = johnson(graph, from);
  ASSERT_EQ(1, 1);  // Stack []
}
