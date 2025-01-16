#include <includes.h>
#include <gtest/gtest.h>
#include "topologicalSort.h"

TEST(TopologicalSort, Simple) {
	OrientedGraph graph;
	graph.AddEdge(0, 3);
	graph.AddEdge(3, 1);
	graph.AddEdge(3, 2);
	graph.AddEdge(2, 1);
	ASSERT_EQ(topologicalSort(graph), std::vector<int>({0, 3, 2, 1}));  // Stack []
}