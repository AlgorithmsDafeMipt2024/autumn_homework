#ifndef AUTUMN_HOMEWORK_TASK_05_DECTREE_TPP_
#define AUTUMN_HOMEWORK_TASK_05_DECTREE_TPP_

#include <set>
#include <vector>

using namespace std;

// для реализации rmq через lca надо использовать
// декартово дерево по неявному ключу
// требуется только построение дерева

template <typename T>
class DecTree {
  size_t n_;
  vector<T> values_;
  vector<set<size_t>> adj_l_;
  vector<size_t> parents;

 public:
  DecTree(vector<T> arr) : n_{arr.size()}, values_{arr}, adj_l_(n_) {
    parents = vector<size_t>(n_, -1);
    for (size_t i = 1; i < n_; ++i) {
      if (values_[i - 1] > arr[i]) {
        // поднимаем наверх
        size_t ptr_r = -1;
        size_t ptr = i - 1;
        for (; parents[ptr] != -1 && values_[ptr] > arr[i];
             ptr_r = ptr, ptr = parents[ptr]);
        if (values_[ptr] <= arr[i]) {
          adj_l_[ptr].erase(ptr_r);
          adj_l_[ptr].insert(i);
          adj_l_[i].insert(ptr_r);
          parents[ptr_r] = i;
          parents[i] = ptr;
        } else {
          parents[ptr] = i;
          adj_l_[i].insert(ptr);
        }
      } else {
        // пробуем записать в сыны
        adj_l_[i - 1].insert(i);
        parents[i] = i - 1;
      }
    }
  }
  vector<vector<size_t>> GetAdj() {
    vector<vector<size_t>> adj = vector<vector<size_t>>(n_, vector<size_t>());
    for (size_t i = 0; i < n_; ++i)
      adj[i] = vector<size_t>(adj_l_[i].begin(), adj_l_[i].end());
    return adj;
  }

  size_t GetStart() {
    for (size_t i = 0; i < n_; ++i)
      if (parents[i] == -1) return i;
    return -1;
  }
  vector<T> GetValues() { return values_; }
};

#endif