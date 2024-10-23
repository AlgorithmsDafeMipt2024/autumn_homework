#include <iostream>

#include <includes.h>
#include "SearchWeakVE.h"

int main()
{
	NonOrientedGraph graph;
	graph.AddEdge(0, 1);
	graph.AddEdge(0, 2);
	graph.AddEdge(1, 2);
	graph.AddEdge(2, 3);
	graph.AddEdge(3, 4);

	//graph.AddEdge(0, 1);
	//graph.AddEdge(1, 2);
	//graph.AddEdge(2, 3);
	//graph.AddEdge(1, 3);
	//graph.AddEdge(3, 4);
	//graph.AddEdge(4, 5);
	//graph.AddEdge(5, 6);
	//graph.AddEdge(6, 7);
	//graph.AddEdge(7, 4);
	graph.AddEdge(0, 1);
	graph.AddEdge(1, 2);
	graph.AddEdge(0, 2);
	graph.AddEdge(2, 3);
	graph.AddEdge(3, 4);
	graph.AddEdge(3, 5);
	graph.AddEdge(4, 5);
	graph.Print();
	WeakVE result = SearchWeakVE(graph);
	std::cout << "Weak Points: ";
	for (int i = 0; i < result.first.size(); ++i)
		std::cout << result.first[i] << ", ";
	std::cout << "\nWeak Edges: ";
	for (int i = 0; i < result.second.size(); ++i)
		std::cout << "(" << result.second[i].first << ", " << result.second[i].second << "); ";
	std::cout << std::endl;
	return 0;
}
