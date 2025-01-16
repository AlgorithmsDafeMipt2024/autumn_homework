#include <iostream>

#include "dectree.tpp"
#include "rmq_array.tpp"

int main() {
  vector<int> v{17, 0, 36, 16, 23, 15, 42, 18, 20};
  DecTree<int> d(v);
  auto data = d.GetAdj();
  for (auto i : data) {
    for (auto j : i) std::cout << j << " ";
    std::cout << std::endl;
  }
  RmqArray<int> rmq(v);
  std::cout << "------------------" << std::endl;
  std::cout << rmq.rmq(4, 6) << std::endl;
  return 0;
}