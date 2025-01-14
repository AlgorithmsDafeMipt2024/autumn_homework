#pragma once

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

#define INF std::numeric_limits<int>::max()

class SegmentMinTree {
 public:
  SegmentMinTree(std::vector<int> nums) : size(nums.size()) {
    int sz = pow(2, ceil(std::log2(nums.size())));
    while (nums.size() != sz) nums.push_back(INF);

    tree.resize(2 * sz);
    for (int i = 0; i < sz; i++) {
      tree[i + sz] = nums[i];
    }

    for (int i = 2 * sz - 1; i > 0; i -= 2) {
      size_t r = i;
      size_t l = i - 1;
      tree[i / 2] = std::min(tree[l], tree[r]);
    }
  }

  void Set(int value, size_t pos) {
    if (pos >= size) throw std::invalid_argument("Invalid value position!");

    size_t tree_pos = pos + pow(2, log2(tree.size()) - 1);
    tree[tree_pos] = value;

    for (int i = tree_pos / 2; i > 0; i /= 2)
      tree[i] = std::min(tree[i * 2], tree[i * 2 + 1]);
  }

  int FindSegmentMin(size_t a, size_t b) const {
    if (!(a >= 0 && b < size && a <= b))
      throw std::invalid_argument("Invalid segment limits!");

    return SegmentMin(a, b, 1, 0, tree.size() / 2 - 1);
  }

  void PrintTree() const {
    std::cout << "Tree: ";
    for (int i = 0; i < tree.size(); i++) {
      if (tree[i] != INF)
        std::cout << tree[i] << ' ';
      else
        std::cout << "inf ";
    }
    std::cout << '\n';
  }

  size_t Size() const { return size; }

 private:
  std::vector<int> tree;
  size_t size;

  int SegmentMin(size_t a, size_t b, size_t min_pos, size_t l_min,
                 size_t r_min) const {
    if (l_min > b || a > r_min) {
      return INF;
    }
    if (a <= l_min && b >= r_min)
      return tree[min_pos];
    else {
      int mid = (l_min + r_min) / 2;
      return std::min(SegmentMin(a, b, 2 * min_pos, l_min, mid),
                      SegmentMin(a, b, 2 * min_pos + 1, mid + 1, r_min));
    }
  }
};

class RMQ {
 public:
  RMQ(std::vector<int> nums) : tree(nums) {}

  void Set(int value, size_t pos) { tree.Set(value, pos); }

  size_t Size() const { return tree.Size(); }

  int operator()(int a, int b) const { return tree.FindSegmentMin(a, b); }

 private:
  SegmentMinTree tree;
};
