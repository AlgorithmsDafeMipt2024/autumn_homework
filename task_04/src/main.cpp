#include <iostream>
#include <vector>

#include "deixtra.h"

int main() {
  std::vector<node> nodes;
  int n, start, finish, tmp;
  std::cin >> n >> start >> finish;
  nodes.resize(n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      std::cin >> tmp;
      if (i == j) {
        continue;
      }
      nodes[i].neighbours.push_back({j, tmp});
    }
  }
  deixtra(nodes, start - 1);

  std::cout << nodes[finish - 1].len << std::endl;

  return 0;
}
