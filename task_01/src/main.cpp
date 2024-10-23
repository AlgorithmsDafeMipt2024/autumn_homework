#include <includes.h>
#include "topologicalSort.h"

std::ostream& operator<<(std::ostream& os, const std::vector<int>& vec)
{
	for (int i = 0; i < vec.size(); ++i)
		os << vec[i] << ", ";
	return os;
}

int main() 
{
	OrientedGraph graph;
	graph.AddEdge(0, 3);
	graph.AddEdge(3, 1);
	graph.AddEdge(3, 2);
	graph.AddEdge(2, 1);
	graph.Print();
	std::cout << std::endl;

	std::cout << "DFS ITERATION: ";
	for (auto iter = GraphDFSIterator(&graph, 0); !iter.IsEnd(); ++iter)
	{
		std::cout << iter() << ", ";
	}
	std::cout << std::endl;

	std::cout << "IsCycled: " << graph.IsCycled() << std::endl;

	std::cout << "DFS: " << graph.DFS() << std::endl;
	std::cout << "after DFS: " << graph.DFS(true) << std::endl;
	std::cout << "BFS: " << graph.BFS() << std::endl;

	auto top_graph = topologicalSort(graph);
	std::cout << "topological sort: " << top_graph << std::endl;
	topologicalSorted(graph);
	graph.Print();
}
