#pragma once

#include <vector>
#include <WeightedGraph.h>
#include <util.h>

class WeightedGraph;

class GraphDFSIterator
{
	const WeightedGraph* graph;
	int start_id;
	int this_id;
	bool is_end;
	std::vector<bool> visited;
	std::vector<int> parent;

	int Next();

public:
	GraphDFSIterator() = delete;
	GraphDFSIterator(const WeightedGraph* const graph, int start_id);

	int operator++() { return Next(); }
	int operator()() { return this_id; }
	bool IsEnd();
};