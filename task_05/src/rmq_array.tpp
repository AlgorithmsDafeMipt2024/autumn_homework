#ifndef AUTUMN_HOMEWORK_TASK_05_RMQ_ARRAY_TPP_
#define AUTUMN_HOMEWORK_TASK_05_RMQ_ARRAY_TPP_

#include <vector>

#include "dectree.tpp"
#include "lca_tree.tpp"
using namespace std;

template <typename T>
struct RmqArray {
  vector<T> arr_;
  size_t n_;
  LcaTree<T> lca_tree_;
  RmqArray(vector<T> arr) : arr_{arr}, n_{arr.size()} {
    if (n_ > 1) {
      DecTree<T> dec_tree(arr_);
      lca_tree_ = LcaTree<T>(dec_tree.GetAdj(), dec_tree.GetStart(), arr_);
    }
  }

  T rmq(size_t l, size_t r) {
    if (n_ > 1) return lca_tree_.lca_value(l, r);
    return arr_[0];
  }
};

#endif