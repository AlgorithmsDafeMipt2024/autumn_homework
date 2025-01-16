#ifndef DIJKSTRA_H_
#define DIJKSTRA_H_

#include <map>

#include "../../lib/src/graph.h"

std::map<int, double> dijkstra(Graph& g, int start_vert);
#endif