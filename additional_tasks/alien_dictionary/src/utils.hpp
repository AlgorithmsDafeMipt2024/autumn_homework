#pragma once

#include <stack>

#include "graph.hpp"

// Adds a directed edge between characters u and v
// Processes if this is the first occurrence for any of the characters
void ForceAddDirEdge(Graph<char>& graph, char u, char v);

// DFS, performing topological sort and detecting cycles
bool TopologicalSortStep(Graph<char>& graph, size_t v, std::set<char>& visited,
                         std::set<char>& recursion, std::stack<char>& stack);

// Function to process the words and find the character order
void FindAlphabeticOrder(const std::vector<std::string>& dictionary);