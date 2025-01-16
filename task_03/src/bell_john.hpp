#include "dijkstra.hpp"
#include <vector>
#include <limits>
#include <limits>

std::vector<double> bellman(OrientedWeightedGraph graph, int from_key, int iterations = std::numeric_limits<int>::infinity());

std::vector<double> johnson(OrientedWeightedGraph graph, int from_key);