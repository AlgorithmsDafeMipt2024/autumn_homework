#include <RMQ.h>

RMQ::RMQ(std::vector<double> vec) : vector(vec), lookup(vec.size()) {
  for (int i = 0; i < vec.size(); ++i)
    lookup[i] = std::vector<double>(vec.size());
  preprocess();
}

void RMQ::preprocess() {
  for (int i = 0; i < vector.size(); i++) lookup[i][i] = i;

  for (int i = 0; i < vector.size(); i++) {
    for (int j = i + 1; j < vector.size(); j++)
      if (vector[lookup[i][j - 1]] < vector[j])
        lookup[i][j] = lookup[i][j - 1];
      else
        lookup[i][j] = j;
  }
}

double RMQ::get_min(int i, int j) { return lookup[i][j]; }

void RMQ::Print() {
  for (int i = 0; i < vector.size(); ++i) {
    std::cout << vector[i] << ", ";
  }
  std::cout << std::endl;
  for (int i = 0; i < vector.size(); ++i) {
    for (int j = 0; j < vector.size(); ++j)
      std::cout << lookup[i][j] << '(' << vector[lookup[i][j]] << "), ";
    std::cout << '\n';
  }
}
