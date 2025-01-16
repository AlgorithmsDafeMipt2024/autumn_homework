#ifndef AUTUMN_HOMEWORK_TASK_06_LCA_TREE_TPP_
#define AUTUMN_HOMEWORK_TASK_06_LCA_TREE_TPP_
#include <cmath>
#include <cstddef>
#include <vector>

#include "rmq_1_array.tpp"

using namespace std;

template <typename T>
class LcaTree {
 public:
  size_t lca(size_t u, size_t v) {
    if (v_num_ > 1) return vtx_[rmq_.rmq1(I_[u], I_[v]).i];
    return 0;
  }
  T lca_value(size_t u, size_t v) { return values_[lca(u, v)]; }
  LcaTree(vector<vector<size_t>> adj_l, size_t start)
      : adj_l_{adj_l}, v_num_{adj_l.size()}, I_(v_num_, -1) {
    if (v_num_ > 1) {
      dfs(start, 0);
      rmq_ = Rmq_1_Array<size_t>{d_};
    }
    values_ = vector<T>(v_num_);
  }
  LcaTree(vector<vector<size_t>> adj_l, size_t start, vector<T> values)
      : adj_l_{adj_l}, v_num_{adj_l.size()}, I_(v_num_, -1), values_{values} {
    if (v_num_ > 1) {
      dfs(start, 0);
      rmq_ = Rmq_1_Array<size_t>{d_};
    }
  }
  void setValues(vector<T> values) { values_ = vector<T>(v_num_); }

 private:
  Rmq_1_Array<size_t> rmq_;
  vector<vector<size_t>> adj_l_;
  size_t v_num_;
  vector<size_t> d_;
  vector<size_t> vtx_;
  vector<size_t> I_;
  vector<T> values_;
  void dfs(size_t v, size_t cur_d) {
    d_.push_back(cur_d);
    vtx_.push_back(v);
    if (I_[v] == -1) I_[v] = d_.size() - 1;
    for (auto& u : adj_l_[v]) {
      dfs(u, cur_d + 1);
      d_.push_back(cur_d);
      vtx_.push_back(v);
    }
  }
};

#endif