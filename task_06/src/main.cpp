#include "lca.h"
#include <iostream>
#include <vector>

int main() {
  std::vector<std::vector<int>> g = {{0, 1, 2}, {3, 4}, {}, {}, {}};
  std::cout << "as";
  auto a = lca(g, {{3, 4}, {3, 5}});
  std::cout << a[0] << " " << a[1];
  return 0;
}
