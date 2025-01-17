#pragma once
#include <graph.hpp>

std::pair<std::vector<std::pair<int, int>>, std::vector<int>>
BridgesAndCutPoints(int vertices, int edges,
                    std::vector<std::pair<int, int>> &vecEdges);