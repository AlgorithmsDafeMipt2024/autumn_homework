#include "deixtra.h"
#include <cmath>
#include <queue>
#include <vector>

void deixtra(std::vector<node> &nodes, int start) {
  std::priority_queue<std::pair<int, int>> qqe; // {len, id}
  node *current;
  int tmp;
  for (auto &i : nodes) {
    i.len = std::numeric_limits<int>::max();
  }
  nodes[start].len = 0;

  qqe.push({0, start});

  while (!qqe.empty()) {
    current = &nodes[qqe.top().second];
    int dst = qqe.top().first;
    qqe.pop();
    if (current->len < dst) {
      continue;
    }
    for (auto &i : current->neighbours) {
      int n_dst = dst + i.second;
      if (n_dst < nodes[i.first].len) {
        nodes[i.first].len = n_dst;
        qqe.push({n_dst, i.first});
      }
    }
  }
}
