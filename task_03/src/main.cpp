#include <iostream>
#include <includes.h>
#include "DeikstraAlgorithm.h"
#include "BellmanForlAlgorithm.h"
#include "JonsonAlgorithm.h"

int main()
{
	WeightedNonOrientedGraph graph;
	graph.AddEdge(0, 1, 10);
	graph.AddEdge(0, 2, 2);
	graph.AddEdge(0, 3, 7);
	graph.AddEdge(0, 4, 8);
	graph.AddEdge(1, 3, 1);
	graph.AddEdge(1, 5, 5);
	graph.AddEdge(2, 3, 3);
	graph.AddEdge(2, 4, 5);
	graph.AddEdge(3, 4, 1);
	graph.AddEdge(3, 5, 4);
	graph.AddEdge(4, 5, 2);

	auto bf = BellmanFordAlgorithm(graph, 0);
	auto deikstra = DeikstraPathAlgorithm(graph, 0, 5);

	graph.Print();
	std::cout << "Deikstra: " << deikstra.pathLength << std::endl;
	for (int i = 0; i < deikstra.path.size(); ++i)
		std::cout << deikstra.path[i] << ", ";
	std::cout << std::endl;
	std::cout << "Bellman Ford: ";
	for (int i = 0; i < bf.size(); ++i)
		std::cout << bf[i] << ", ";
	std::cout << std::endl;

	WeightedOrientedGraph secondGraph;
	secondGraph.AddEdge(0, 1, 2);
	secondGraph.AddEdge(0, 2, 3);
	secondGraph.AddEdge(1, 0, -1);
	secondGraph.AddEdge(1, 2, 4);
	secondGraph.AddEdge(2, 0, -2);
	secondGraph.AddEdge(2, 1, 1);

	bf = BellmanFordAlgorithm(secondGraph, 0);

	secondGraph.Print();
	std::cout << "Bellman Ford: ";
	for (int i = 0; i < bf.size(); ++i)
		std::cout << bf[i] << ", ";
	std::cout << std::endl;
	std::cout << "Jonson: " << std::endl;
	auto jons = JonsonAlgorithm(secondGraph);
	jons.Print();
	std::cout << std::endl;

	return 0;
}
