#pragma once

#include <vector>
#include <algorithm>
#include "Graph.h"
#include "util.h"

class NonOrientedGraph : public Graph
{
private:
	bool IsCycled(int parent, int id, std::vector<int>& result, std::vector<bool>& visited) const;

public:
	int GetEdges()
	{
		int result = 0;
		for (int i = 0; i < graph.size(); ++i)
			result += sum(graph[i]);
		return result / 2;
	}
	bool AddVert(int id);
	bool AddEdge(int id0, int id1);
	bool DeleteVert(int id);
	bool DeleteEdge(int id0, int id1);

	bool IsCycled() const;
};