#pragma once

#include "WeightedGraph.h"

class WeightedNonOrientedGraph : public WeightedGraph
{
public:
	bool AddVert(int id);
	bool AddEdge(int id0, int id1, double value);
	bool DeleteVert(int id);
	bool DeleteEdge(int id0, int id1);
};