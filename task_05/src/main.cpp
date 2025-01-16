#include <RMQ.h>

int main() {
  std::vector<double> a = {1, 3, 2, 7, 9, 11, 5, 4, 6, 8};
  RMQ rmq(a);
  rmq.Print();
  return 0;
}
