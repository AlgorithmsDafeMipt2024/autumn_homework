#include "WeightedGraph.h"

int WeightedGraph::GetEdges() const
{
	int result = 0;
	for (int i = 0; i < graph.size(); ++i)
		for (int j = 0; j < graph.size(); ++j)
			if (graph[i][j])
				++result;
	return result - graph.size();
}

bool WeightedGraph::IsCycled(int id, std::vector<int>& result, std::vector<bool>& visited) const
{
	for (int i = 0; i < graph.size(); ++i)
	{
		if (graph[id][i] && !visited[i])
		{
			visited[i] = true;
			if (IsCycled(i, result, visited))
				return true;
			result.push_back(i);
		}
		else if (graph[id][i] && visited[i] && i != id)
		{
			if (!in(result, i))
				return true;
		}
	}
	return false;
}

bool WeightedGraph::IsCycled() const
{
	std::vector<int> result;
	std::vector<bool> visited(graph.size());
	visited[0] = true;
	return IsCycled(0, result, visited);
}

void WeightedGraph::Print() const 
{
	for (int i = 0; i < graph.size(); ++i)
	{
		for (int j = 0; j < graph.size(); ++j)
			std::cout << graph[i][j] << ", ";
		std::cout << '\n';
	}
}

bool WeightedGraph::SwapIds(int id0, int id1)
{
	if (std::max(id0, id1) >= graph.size() || id0 == id1)
		return true;
	if (id0 > id1)
		std::swap(id0, id1);

	for (int i = 0; i < graph.size(); ++i)
		std::swap(graph[i][id0], graph[i][id1]);
	std::swap(graph[id0], graph[id1]);
	return false;
}

void WeightedGraph::DFS(int id, std::vector<int>& result, std::vector<bool>& visited, bool before)
{
	for (int i = 0; i < graph.size(); ++i)
	{
		if (graph[id][i] && !visited[i])
		{
			visited[i] = true;
			if (!before)
				result.push_back(i);
			DFS(i, result, visited);
			if (before)
				result.push_back(i);
		}
	}
}

std::vector<int> WeightedGraph::DFS(int id, bool before)
{
	std::vector<bool> visited(graph.size());
	std::vector<int> result;
	visited[id] = true;
	if (!before)
		result.push_back(id);

	for (int i = 0; i < graph.size(); ++i)
	{
		if (graph[id][i] && !visited[i])
		{
			visited[i] = true;
			if (!before)
				result.push_back(i);
			DFS(i, result, visited);
			if (before)
				result.push_back(i);
		}
	}
	if (before)
		result.push_back(id);

	return result;
}

std::vector<int> WeightedGraph::DFS(bool before)
{
	return DFS(0, before);
}

void WeightedGraph::BFS(int id, std::vector<int>& result, std::vector<bool>& visited)
{
	std::vector<int> need_visit;
	for (int i = 0; i < graph.size(); ++i)
	{
		if (graph[id][i] && !visited[i])
		{
			visited[i] = true;
			result.push_back(i);
			need_visit.push_back(i);
		}
	}
	for (int i = 0; i < need_visit.size(); ++i)
	{
		if (!visited[need_visit[i]])
			BFS(need_visit[i], result, visited);
	}
}

std::vector<int> WeightedGraph::BFS(int id)
{
	std::vector<bool> visited(graph.size());
	std::vector<int> result;
	visited[id] = true;
	result.push_back(id);

	std::vector<int> need_visit;

	for (int i = 0; i < graph.size(); ++i)
	{
		if (graph[id][i] && !visited[i])
		{
			visited[i] = true;
			result.push_back(i);
			need_visit.push_back(i);
		}
	}
	for (int i = 0; i < need_visit.size(); ++i)
	{
		BFS(need_visit[i], result, visited);
	}
	return result;
}

std::vector<int> WeightedGraph::BFS()
{
	return BFS(0);
}