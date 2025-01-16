#include "rmq.h"
#include <iostream>

int main() {
  int a[] = {1, 2, 3, -1, 5, 6};
  auto ans = rmq(a, 6, {{0, 2}});
  std::cout << ans[0];
}
