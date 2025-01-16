#include <vector>
#include <stack>
#include "util.hpp"

void topo_recr(EdgeOrientedGraph& graph, std::stack<int>& vstack, std::vector<int>& vcolor, int current);

std::vector<int> topo_sort(EdgeOrientedGraph graph, int from_key);