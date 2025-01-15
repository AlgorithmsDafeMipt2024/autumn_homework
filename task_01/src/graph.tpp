#ifndef AUTUMN_HOMEWORK_TASK_01_GRAPH_GRAPH_TPP_
#define AUTUMN_HOMEWORK_TASK_01_GRAPH_GRAPH_TPP_

#include <list>
#include <vector>

template <class T>
class Graph {
 private:
  size_t v_num_;
  std::vector<std::vector<T>> adj_;

 public:
  Graph(size_t v_num) : v_num_{v_num}, adj_{v_num_} {}

  void AddEdge(size_t first_vertex, size_t second_vertex) {
    adj_[first_vertex].push_back(second_vertex);
  }

  void TopologicalSortVertex(int i, std::vector<bool>& visited,
                             std::list<T>& list) {
    for (auto neighbor : adj_[i]) {
      if (!visited[neighbor]) {
        TopologicalSortVertex(neighbor, visited, list);
      }
    }
    list.push_front(i);
    visited[i] = true;
  }

  std::list<T> TopologicalSort() {
    std::list<T> list;
    std::vector<bool> visited(v_num_ + 1, false);
    for (size_t i = 0; i < v_num_; i++) {
      if (visited[i] == false) {
        TopologicalSortVertex(i, visited, list);
      }
    }
    return list;
  }
};

#endif