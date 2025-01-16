#include "solution.h"
#include <cmath>
#include <limits>
#include <queue>
#include <vector>

void deixtra(std::vector<node> &nodes, int start) {
  std::priority_queue<std::pair<int, int>> qqe; // {len, id}
  node *current;
  int tmp;
  for (auto &i : nodes) {
    i.len = std::numeric_limits<int>::max();
  }
  nodes[start].len = 0;

  qqe.push({0, start});

  while (!qqe.empty()) {
    current = &nodes[qqe.top().second];
    int dst = qqe.top().first;
    qqe.pop();
    if (current->len < dst) {
      continue;
    }
    for (auto &i : current->neighbours) {
      int n_dst = dst + i.second;
      if (n_dst < nodes[i.first].len) {
        nodes[i.first].len = n_dst;
        qqe.push({n_dst, i.first});
      }
    }
  }
}

bool bellford(std::vector<node> &nodes /*, int start*/) {
  int tmp = 0;
  /*node s;*/
  bool flag = false;
  for (auto &i : nodes) {
    /*s.neighbours.push_back({i.id, 0});*/
    i.pot = 0;
  }
  while (nodes.size() >= (tmp++)) {
    for (auto &i : nodes) {
      for (auto &j : i.neighbours) {
        int n_dst = i.pot + j.second;
        if (n_dst < nodes[j.first].pot) {
          /*std::cout<<i.id<<" "<<(j.first)<<(" ") << j.first<< n_dst<<"\n";*/
          nodes[j.first].pot = n_dst;
          flag = true;
        }
      }
    }
    if (flag) {
      flag = false;
      continue;
    }
    return true;
  }
  return false;
}

std::vector<std::vector<int>> jonson(std::vector<node> nodes) {
  std::vector<std::vector<int>> ret(
      nodes.size(),
      std::vector<int>(nodes.size(), std::numeric_limits<int>::min()));
  if (!bellford(nodes)) {
    /*std::cout<<"wrong!";*/
    return ret;
  }
  for (auto &i : nodes) {
    for (auto &j : i.neighbours) {
      j.second = j.second + nodes[j.first].pot - i.pot;
    }
  }
  for (int i = 0; i < nodes.size(); i++) {
    deixtra(nodes, i);
    for (int j = 0; j < nodes.size(); j++) {
      ret[i][j] = nodes[j].len - nodes[j].pot + nodes[i].pot;
    }
  }
  return ret;
}
