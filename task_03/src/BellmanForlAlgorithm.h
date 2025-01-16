#pragma once

#include <includes.h>

std::vector<double> BellmanFordAlgorithm(const WeightedGraph& graph,
                                         int start_id);
std::vector<double> BellmanFordAlgorithm(
    const OrientedWeightedGraphWithZeroWeight& graph, int start_id);
