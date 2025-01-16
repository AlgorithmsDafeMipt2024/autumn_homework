#ifndef GRAPH_H_
#define GRAPH_H_

#include <iostream>
#include <vector>

class Graph {
  struct vert_neigh {
    int name;
    double lenght;

    vert_neigh(int name, double lenght) : name{name}, lenght{lenght} {}
    vert_neigh(std::pair<int, double> p) : name{p.first}, lenght{p.second} {}
  };

 public:
  // { {0, 1}, {1, 0}, {2, 3}, {2, 4}, {2, 5} }
  Graph(int verts_num, std::initializer_list<std::pair<int, int>> links) {
    adjacents = std::vector<std::vector<vert_neigh>>(verts_num,
                                                     std::vector<vert_neigh>());
    for (auto pair : links) {
      adjacents[pair.first].push_back(vert_neigh(pair.second, 1.));
    }
  }

  // { {{0, 1}, lenght1}, {{1, 0}, lenght2}, ... }
  Graph(int verts_num,
        std::initializer_list<std::pair<std::pair<int, int>, double>> links) {
    adjacents = std::vector<std::vector<vert_neigh>>(verts_num,
                                                     std::vector<vert_neigh>());
    for (auto pair : links) {
      adjacents[pair.first.first].push_back(
          vert_neigh(pair.first.second, pair.second));
    }
  }

  int size() const { return adjacents.size(); }

  void add_vert() { adjacents.push_back({}); }

  friend std::ostream& operator<<(std::ostream& os, const Graph& g) {
    os << " { ";
    for (int i = 0; i < g.adjacents.size(); ++i) {
      for (auto p : g.adjacents[i]) {
        os << "{ {" << i << ", " << p.name << "}, " << p.lenght;
        os << "}, ";
      }
    }
    os << "}";
    return os;
  }

  void see_vertical() {
    int vert_name = -1;
    for (auto vert : adjacents) {
      vert_name++;
      if (vert.size() == 0) {
        std::cout << vert_name << std::endl;
        continue;
      }
      for (auto link_to : vert) {
        std::cout << vert_name << " -> " << link_to.name
                  << ", lenght:" << link_to.lenght << std::endl;
      }
    }
  }
  std::vector<std::vector<vert_neigh>> adjacents;
};

#endif
