#pragma once

#include <vector>
#include <iostream>
#include <util.h>

class WeightedGraph
{
protected:
	std::vector<std::vector<int>> graph;

	bool IsCycled(int id_start, std::vector<int>& result, std::vector<bool>& visited) const;
	void DFS(int id_start, std::vector<int>& result, std::vector<bool>& visited, bool after = false);
	void BFS(int id_start, std::vector<int>& result, std::vector<bool>& visited);

public:
	const std::vector<int>& operator[](int i) const { return graph[i]; }
	std::vector<int>& operator[](int i) { return graph[i]; }
	int GetVerts() const { return graph.size(); }
	int GetEdges() const; 
	bool IsCycled() const;
	void Print() const;

	bool SwapIds(int id0, int id1);

	std::vector<int> DFS(int id_start, bool after = false);
	std::vector<int> DFS(bool after = false);
	std::vector<int> BFS(int id_start);
	std::vector<int> BFS();

};