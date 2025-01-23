#include <limits>
#include <vector>
#include <queue>
#include <map>
#include "util.hpp"

struct FirstGreater {
    bool operator()(std::pair<double, int> const& lhs,
                    std::pair<double, int> const& rhs) const;
};

std::vector<double> dijkstra(OrientedWeightedGraph graph, int from_key);

std::vector<double> bellman(OrientedWeightedGraph graph, int from_key, int iterations = std::numeric_limits<int>::infinity());

std::vector<double> johnson(OrientedWeightedGraph graph, int from_key);