#include "johnson.hpp"

#include <limits>
#include <vector>

void dfs_mark_rec(Graph& g, std::vector<int>& marks, std::vector<int>& visited,
                  int vert) {
  visited[vert] = 1;

  for (auto child : g.adjacents[vert]) {
    if (visited[child.name] == 0) {
      dfs_mark_rec(g, marks, visited, child.name);
    }
  }

  visited[vert] = 2;
  for (int i = 0; i < marks.size(); ++i) {
    if (marks[marks.size() - 1 - i] == -1) {
      marks[marks.size() - 1 - i] = vert;
      break;
    }
  }
}

std::vector<int>* topological_sort_dfs_rec(Graph& g) {
  if (g.size() == 0) {
    return new std::vector<int>();
  }

  std::vector<int> visited(g.size(),
                           0);  // 0 not started verticle , 1 started verticle ,
                                // 2 - finished verticle
  std::vector<int>* sorted = new std::vector<int>(g.size(), -1);

  bool calculated;
  for (int i = 0; i < visited.size(); ++i) {
    calculated = true;
    for (int j = 0; j < visited.size(); ++j) {
      if (visited[j] == 0) {
        calculated = false;
        dfs_mark_rec(g, *sorted, visited, j);
        break;
      }
    }
    if (calculated) {
      break;
    };
  }

  return sorted;
}

std::vector<double> belllman_ford(Graph& g, int start_vert) {
  std::vector<double> dists(g.size(), std::numeric_limits<double>::max());
  std::vector<int> top_order = *topological_sort_dfs_rec(g);
  dists[start_vert] = 0;

  for (int i = 0; i < g.size() - 1; ++i) {
    for (int v : top_order) {
      for (auto child : g.adjacents[v]) {
        if (dists[v] > dists[child.name] + child.lenght) {
          dists[v] = dists[child.name] + child.lenght;
        }
      }
    }
  }

  for (int v : top_order) {
    for (auto child : g.adjacents[v]) {
      if (dists[start_vert] > dists[child.name] + child.lenght) {
        throw std::runtime_error("Graph contains negative cycles!");
      }
    }
  }
  return dists;
}