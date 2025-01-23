#include <vector>
#include <queue>
#include <map>
#include "util.hpp"

struct FirstGreater {
    bool operator()(std::pair<double, int> const& lhs,
                    std::pair<double, int> const& rhs) const;
};


std::vector<double> dijkstra(OrientedWeightedGraph graph, int from_key);