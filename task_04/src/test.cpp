
#include <gtest/gtest.h>
#include <limits>
#include <vector>
#include "dijkstra.hpp"
#include "util.hpp"

TEST(Dijkstra, Simple) {
  std::vector<double> expected = {0., 7., 9., 20., 20., 11.};

  double inf = std::numeric_limits<double>::infinity();
  std::vector<std::vector<double>> weights = {
    {inf, 7,   9,   inf, inf, 14},
    {7,   inf, 10,  inf, inf, inf},
    {9,   10,  inf, 11,  inf, 2},
    {inf, inf, 11,  inf, 6,   inf},
    {inf, inf, inf, 6,   inf, 9},
    {14,  inf, 2,   inf, 9,   inf}
  };
  OrientedWeightedGraph graph(weights);
  std::vector<double> result = dijkstra_alg(graph, 0);
  ASSERT_EQ(result, expected);  // Stack []
}
