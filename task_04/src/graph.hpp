#ifndef AUTUMN_HOMEWORK_TASK_04_GRAPH_HPP_
#define AUTUMN_HOMEWORK_TASK_04_GRAPH_HPP_

#include <cmath>
#include <limits>
#include <queue>
#include <vector>

const int kInf = std::numeric_limits<int>::max();

class Graph {
 private:
  std::vector<std::vector<int>> adj_matr_;
  size_t v_num_;

 public:
  Graph(const std::vector<std::vector<int>>& adj_matr);

  std::vector<int> Dijkstra(size_t s);
};

#endif