#pragma once

#include <limits>
#include <map>
#include <vector>

std::vector<double> Dijkstra(std::vector<std::map<int, double>> data,
                             int source);