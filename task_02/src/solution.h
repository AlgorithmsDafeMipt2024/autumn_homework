#ifndef __SOLUTION_H__
#define __SOLUTION_H__

#include <list>
#include <algorithm>
#include <vector>
#include <deque>
#include <unordered_set>

class node {
public:
  std::vector<int> neighbours;
  int id;
  bool locked = false; //
  bool flag = false; // белая
};


std::pair<std::vector<std::pair<int,int>>,std::vector<int>> solution(std::vector<node> nodes);

#endif // __SOLUTION_H__
