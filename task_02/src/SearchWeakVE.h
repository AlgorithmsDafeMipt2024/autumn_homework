#pragma once

#include <includes.h>

#define WeakVE std::pair<std::vector<int>, std::vector<std::pair<int, int>>>

WeakVE SearchWeakVE(const WeightedGraph& graph);