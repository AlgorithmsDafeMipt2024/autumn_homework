#include "topologicalSort.h"

std::vector<int> topologicalSort(WeightedGraph& graph)
{
	if (graph.IsCycled())
		return std::vector<int>{-1};

	auto dfs = graph.DFS(true);
	std::vector<int> rdfs(dfs.size());
	for (int i = 0; i < dfs.size(); ++i)
		rdfs[graph.GetVerts() - 1 - i] = dfs[i];
	return rdfs;
}

bool topologicalSorted(WeightedGraph& graph)
{
	auto rdfs = topologicalSort(graph);
	if (rdfs.size() == 1 && rdfs[0] == -1)
		return true;
	std::vector<int> positions(graph.GetVerts());
	for (int i = 0; i < graph.GetVerts(); ++i)
		positions[i] = i;
	for (int i = 0; i < graph.GetVerts(); ++i)
	{
		int finded_id = -1;
		for (int j = i; j < positions.size(); ++j)
			if (positions[j] == rdfs[i])
			{
				finded_id = j;
				break;
			}
		graph.SwapIds(i, finded_id);
		std::swap(positions[i], positions[finded_id]);
	}
	return false;
}

WeightedGraph* topologicalSorting(WeightedGraph& graph)
{
	WeightedGraph* new_graph = new WeightedGraph(graph);
	if (topologicalSorted(*new_graph))
		return nullptr;
	return new_graph;
}