#include <iostream>
#include <vector>

class RMQ {
  std::vector<double> vector;
  std::vector<std::vector<double>> lookup;

  void preprocess();

 public:
  RMQ(std::vector<double> vec);
  RMQ() = delete;

  double get_min(int i, int j);
  void Print();
};
