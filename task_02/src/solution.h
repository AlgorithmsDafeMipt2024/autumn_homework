#ifndef __SOLUTION_H__
#define __SOLUTION_H__

#include <algorithm>
#include <deque>
#include <list>
#include <unordered_set>
#include <vector>

class node {
public:
  std::vector<int> neighbours;
  int id;
  bool locked = false; //
  bool flag = false;   // белая
};

std::pair<std::vector<std::pair<int, int>>, std::vector<int>>
solution(std::vector<node> nodes);

#endif // __SOLUTION_H__
