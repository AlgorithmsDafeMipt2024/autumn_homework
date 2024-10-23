#pragma once

#include <vector>
#include <WeightedGraph.h>
#include <util.h>

class Graph : public WeightedGraph
{
	int GetEdges()
	{
		int result = 0;
		for (int i = 0; i < graph.size(); ++i)
			result += sum(graph[i]);
		return result;
	}
};