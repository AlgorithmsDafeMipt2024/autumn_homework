#include "topology_sort.h"

void Graph::TopologySortStep(int current_vertice, bool visited_vertices[],
                             std::list<int>& list) {
  visited_vertices[current_vertice] = true;
  for (std::list<int>::iterator i = adjacency_list[current_vertice].begin();
       i != adjacency_list[current_vertice].end(); i++) {
    if (!visited_vertices[*i]) TopologySortStep(*i, visited_vertices, list);
  }
  list.push_front(current_vertice);
}

std::list<int> Graph::TopologySort() {
  std::list<int> list;
  bool* visited_vertices = new bool[vertices_number];
  for (int i = 0; i < vertices_number; i++) {
    if (!visited_vertices[i]) TopologySortStep(i, visited_vertices, list);
  }
  return list;
}