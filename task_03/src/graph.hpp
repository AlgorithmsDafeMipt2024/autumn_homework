#ifndef AUTUMN_HOMEWORK_TASK_03_GRAPH_HPP_
#define AUTUMN_HOMEWORK_TASK_03_GRAPH_HPP_

#include <cmath>
#include <limits>
#include <queue>
#include <vector>

const int kInf = std::numeric_limits<int>::max();

class Graph {
 public:
  Graph(const std::vector<std::vector<int>>& adj_matr);

  std::vector<int> Dijkstra(size_t s);

  std::vector<std::vector<int>> Johnson();

 private:
  std::vector<std::vector<int>> adj_matr_;
  size_t v_num_;

  bool HasNegativeCycle(const std::vector<int>& distances);

  void RelaxEdges(std::vector<int>& distances);

  bool BellmanFord(std::vector<int>& h);
};

#endif