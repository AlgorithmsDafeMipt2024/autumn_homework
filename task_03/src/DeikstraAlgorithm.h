#pragma once

#include <includes.h>

struct DeikstraReturn
{
	std::vector<int> path;
	double pathLength;
};

double DeikstraAlgorithm(const WeightedGraph& graph, int start_id, int end_id);
double DeikstraAlgorithm(const OrientedWeightedGraphWithZeroWeight& graph, int start_id, int end_id);
DeikstraReturn DeikstraPathAlgorithm(const WeightedGraph& graph, int start_id, int end_id);
DeikstraReturn DeikstraPathAlgorithm(const OrientedWeightedGraphWithZeroWeight& graph, int start_id, int end_id);
