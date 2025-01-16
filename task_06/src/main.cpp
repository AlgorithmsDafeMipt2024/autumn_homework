#include <iostream>

#include "lca_tree.tpp"

int main() {
  vector<vector<size_t>> list = {{1, 2}, {3, 4}, {5, 6}, {}, {7, 8},
                                 {},     {},     {},     {}};
  LcaTree<int> t(list, 0);
  cout << t.lca(6, 2) << std::endl;
  return 0;
}