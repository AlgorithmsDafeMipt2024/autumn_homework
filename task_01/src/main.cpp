#include <iostream>
#include <stack>
#include <stdexcept>
#include <vector>

#include "../lib/src/graph.h"

void dfs_mark_non_rec(Graph& g, std::vector<int>& marks,
                      std::vector<int>& visited, int start_name) {
  std::stack<int> st;
  st.push(start_name);

  while (!st.empty()) {
    int v = st.top();

    if (visited[v] == 2) {
      st.pop();
      for (int i = 0; i < marks.size(); ++i) {
        if (marks[marks.size() - 1 - i] == -1) {
          marks[marks.size() - 1 - i] = v;
          break;
        }
      }
      visited[v] = 3;
      continue;
    } else if (visited[v] == 3) {
      st.pop();
      continue;
    }

    visited[v] = 1;

    int finished_children = 0;
    for (auto child : g.adjacents[v]) {
      if (visited[child.name] == 1) {
        throw std::runtime_error("Graph contains cycle!");
      } else if (visited[child.name] == 0) {
        st.push(child.name);
      } else {
        finished_children++;
      }
    }

    if (finished_children == g.adjacents[v].size()) {
      visited[v] = 2;
    }
  }
}

std::vector<int>* topological_sort_dfs_non_rec(Graph& g) {
  if (g.size() == 0) {
    return new std::vector<int>();
  }

  std::vector<int> visited(
      g.size(),
      0);  // 0 not started verticle , 1 started verticle, 2 - finished
           // verticle, 3 - added and finished verticle
  std::vector<int>* sorted = new std::vector<int>(g.size(), -1);

  bool calculated;
  for (int i = 0; i < visited.size(); ++i) {
    calculated = true;
    for (int j = 0; j < visited.size(); ++j) {
      if (visited[j] == 0) {
        calculated = false;
        dfs_mark_non_rec(g, *sorted, visited, j);
        break;
      }
    }
    if (calculated) {
      break;
    };
  }

  return sorted;
}

void dfs_mark_rec(Graph& g, std::vector<int>& marks, std::vector<int>& visited,
                  int vert) {
  visited[vert] = 1;

  for (auto child : g.adjacents[vert]) {
    if (visited[child.name] == 1) {
      throw std::runtime_error("Graph contains cycle!");
    } else if (visited[child.name] == 0) {
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

int main() { return 0; }
