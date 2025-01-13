#include <iostream>
#include <limits>
#include <map>
#include <vector>

#include "../../lib/src/graph.h"

std::map<int, double> dijkstra(Graph& g, int start_vert) {
  std::map<int, double> dists;
  std::vector<bool> finished(g.size(), false);

  for (int i = 0; i < g.size(); ++i) {
    dists[i] = std::numeric_limits<double>::infinity();
  }
  dists[start_vert] = 0;
  finished[start_vert] = true;

  int active_vert = start_vert;
  double min_lenght = std::numeric_limits<double>::infinity();
  for (int i = 0; i < g.size() - 1; ++i) {
    for (auto child : g.adjacents[active_vert]) {
      if (dists[child.name] > child.lenght + dists[active_vert]) {
        dists[child.name] = child.lenght + dists[active_vert];
      }
    }

    min_lenght = std::numeric_limits<double>::infinity();
    for (int j = 0; j < g.size(); j++) {
      if (!finished[j] && (dists[j] < min_lenght)) {
        min_lenght = dists[j];
        active_vert = j;
      }
    }
    finished[active_vert] = true;
  }

  std::map<int, double> answer;
  for (int i = 0; i < dists.size(); i++) {
    answer[i] = dists[i];
  }
  return answer;
}

int main() {
  Graph g(6, {
                 {{0, 1}, 7},
                 {{1, 0}, 7},
                 {{0, 2}, 9},
                 {{2, 0}, 9},
                 {{1, 2}, 10},
                 {{2, 1}, 10},
                 {{0, 5}, 14},
                 {{5, 0}, 14},
                 {{2, 5}, 2},
                 {{5, 2}, 2},
                 {{2, 3}, 11},
                 {{3, 2}, 11},
                 {{1, 3}, 15},
                 {{3, 1}, 15},
                 {{3, 4}, 6},
                 {{4, 3}, 6},
                 {{5, 4}, 9},
                 {{4, 5}, 9},
             });
  // std::cout << g << std::endl << std::endl;
  // g.see_vertical();
  // std::cout << (t_inf<double>(7) < Inf()) << (t_inf<double>(0) < Inf());
  std::cout << std::endl;
  std::map<int, double> sorted = dijkstra(g, 0);
  for (int i = 0; i < sorted.size(); ++i) {
    std::cout << sorted[i] << " ";
  }
  std::cout << std::endl;
}
