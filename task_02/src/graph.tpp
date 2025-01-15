#ifndef AUTUMN_HOMEWORK_TASK_01_GRAPH_GRAPH_TPP_
#define AUTUMN_HOMEWORK_TASK_01_GRAPH_GRAPH_TPP_

#include <vector>

template <typename T>
class Graph {
 private:
  size_t v_num_;
  std::vector<std::vector<T>> adj_;
  std::vector<int> disc_,
      least_;  // discovery time and least_[i] is node with least disc_ that can
               // be reached from i node
  std::vector<std::pair<int, int>> br_;  // bridges
  std::vector<int> a_p_;                 // articulation points

  void dfs(int u, int p, int& timer) {
    disc_[u] = least_[u] = timer++;
    int subgraph_count = 0;

    for (int v : adj_[u]) {
      if (v == p) continue;
      if (disc_[v]) {
        least_[u] = std::min(least_[u], disc_[v]);
      } else {
        ++subgraph_count;
        dfs(v, u, timer);
        least_[u] = std::min(least_[u], least_[v]);

        if (disc_[u] <= least_[v] && p != -1) {
          if (a_p_.empty() || a_p_.back() != u) {
            a_p_.push_back(u);
          }
        }
        if (disc_[u] < least_[v]) br_.push_back({u, v});
      }
    }

    if (subgraph_count > 1 && p == -1) a_p_.push_back(u);
  }

 public:
  Graph(size_t number) {
    v_num_ = number;
    adj_ = std::vector<std::vector<T>>(v_num_);
  }

  void AddEdge(size_t first_verticle, size_t second_verticle) {
    adj_[first_verticle].push_back(second_verticle);
    adj_[second_verticle].push_back(first_verticle);
  }

  void UpdateBrAp() {
    int timer = 1;
    disc_.assign(v_num_, 0);
    least_.assign(v_num_, 0);
    br_.clear();
    a_p_.clear();

    for (size_t i = 0; i < v_num_; ++i) {
      if (!disc_[i]) dfs(i, -1, timer);
    }
  }

  std::vector<std::pair<int, int>> GetBr() { return br_; }
  std::vector<int> GetAP() { return a_p_; }
};
#endif