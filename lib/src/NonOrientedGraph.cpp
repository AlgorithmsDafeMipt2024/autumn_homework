#include "NonOrientedGraph.h"

bool NonOrientedGraph::IsCycled(int parent, int id, std::vector<int>& result, std::vector<bool>& visited) const
{
	for (int i = 0; i < graph.size(); ++i)
	{
		if (graph[id][i] && !visited[i] && i != parent)
		{
			visited[i] = true;
			if (IsCycled(id, i, result, visited))
				return true;
			result.push_back(i);
		}
		else if (graph[id][i] && visited[i] && i != id && i != parent)
		{
			if (!in(result, i))
				return true;
		}
	}
	return false;
}

bool NonOrientedGraph::IsCycled() const
{
	std::vector<int> result;
	std::vector<bool> visited(graph.size());
	visited[0] = true;
	return IsCycled(0, 0, result, visited);
}

bool NonOrientedGraph::AddVert(int id)
{
	if (id >= graph.size())
	{
		graph.resize(id + 1);
		for (int i = 0; i < graph.size(); ++i)
		{
			graph[i].resize(id + 1);
			graph[i][i] = 1;
		}
	}
	return false;
}

bool NonOrientedGraph::AddEdge(int id0, int id1)
{
	if (id0 == id1)
		return true;
	AddVert(std::max(id0, id1));
	graph[id0][id1] = 1;
	graph[id1][id0] = 1;
	return false;
}

bool NonOrientedGraph::DeleteVert(int id)
{
	if (id >= graph.size())
		return true;
	graph.resize(id + 1);
	for (int i = 0; i < graph.size(); ++i)
		graph[i].resize(id + 1);
	return false;
}

bool NonOrientedGraph::DeleteEdge(int id0, int id1)
{
	if (id0 == id1 || std::max(id0, id1) >= graph.size())
		return true;
	graph[id0][id1] = 0;
	graph[id1][id0] = 0;
	return false;
}