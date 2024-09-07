#pragma once

#include <list>
#include <stdexcept>

class Graph {
 private:
  int vertices_number;
  std::list<int>* adjacency_list;

 public:
  Graph(int number) {
    if (number <= 0) throw std::logic_error("number must be positive!");
    vertices_number = number;
    adjacency_list = new std::list<int>[vertices_number + 1];
  }
  void AddEdge(int first_verticle, int second_verticle) {
    if (first_verticle < 0 || first_verticle > vertices_number ||
        second_verticle < 0 || second_verticle > vertices_number)
      throw std::logic_error("such node does not exist");
    if (first_verticle == second_verticle)
      throw std::logic_error("graph must be acyclic!");
    adjacency_list[first_verticle].push_back(second_verticle);
  }
  void TopologySortStep(int current_vertice, bool visited_vertices[],
                        std::list<int>& list);
  std::list<int> TopologySort();
};