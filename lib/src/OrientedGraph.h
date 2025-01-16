#pragma once

#include "Graph.h"

class OrientedGraph : public Graph {
 public:
  bool AddVert(int id);
  bool AddEdge(int id0, int id1);
  bool DeleteVert(int id);
  bool DeleteEdge(int id0, int id1);
};
