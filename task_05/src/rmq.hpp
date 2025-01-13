#pragma once

#include "lca.hpp"

template <AllowedVertType vert_t>
class RMQ {
 public:
  RMQ(const std::vector<vert_t>& arr)
      : arr_(arr), lca_(ImplicitTreap<vert_t, size_t>(arr)) {}

  vert_t Query(size_t left, size_t right) const {
    if (arr_.empty()) throw std::logic_error("RMQ: empty input array.");

    if (left >= arr_.size())
      throw std::invalid_argument("RMQ: left index is out of bound.");

    if (right >= arr_.size())
      throw std::invalid_argument("RMQ: right index is out of bound.");

    if (left > right) std::swap(left, right);

    return lca_.Ancestor(arr_[left], arr_[right]);
  }

  vert_t Query(const std::pair<size_t, size_t>& pair) const {
    return Query(pair.first, pair.second);
  }

 private:
  const std::vector<vert_t>& arr_;
  LCA<vert_t, size_t> lca_;
};

template <AllowedVertType vert_t>
inline vert_t CalculateRMQ(const std::vector<vert_t>& arr, size_t left,
                           size_t right) {
  return RMQ<vert_t>(arr).Query(left, right);
}

template <AllowedVertType vert_t>
inline vert_t CalculateRMQ(const std::vector<vert_t>& arr,
                           const std::pair<size_t, size_t>& pair) {
  return RMQ<vert_t>(arr).Query(pair);
}
