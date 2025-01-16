#include "dijkstra.hpp"

#include <limits>
#include <vector>

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

  return dists;
}
