#include "SearchWeakVE.h"

void dfs(WeakVE& result, const WeightedGraph& graph, int id, int parent, std::vector<int>& disc, std::vector<int>& low, std::vector<int>& visited, int& time)
{
	disc[id] = time;
	low[id] = time;
	++time;
	visited[id] = true;
	for (int i = 0; i < graph.GetVerts(); ++i)
	{
		if (graph[id][i] && !visited[i])
		{
			dfs(result, graph, i, id, disc, low, visited, time);
			low[id] = std::min(low[id], low[i]);
			if (low[i] > disc[id])
				result.second.push_back(std::make_pair(id, i));
			if (parent != -1 && low[i] >= disc[id])
				result.first.push_back(id);
		}
		else if (graph[id][i] && i != parent)
			low[id] = std::min(low[id], low[i]);
	}
}

WeakVE SearchWeakVE(const WeightedGraph& graph)
{
	WeakVE result;
	std::vector<int> disc(graph.GetVerts());
	std::vector<int> low(graph.GetVerts());
	std::vector<int> visited(graph.GetVerts());
	int time = 0;
	int start_id = 0;
	dfs(result, graph, start_id, -1, disc, low, visited, time);
	int num_start_id_daughters = 0;
	for (int i = 0; i < graph.GetVerts(); ++i)
	{
		if (graph[start_id][i] != 0)
			++num_start_id_daughters;
	}
	if (num_start_id_daughters > 1)
		result.first.push_back(start_id);
	return result;
}