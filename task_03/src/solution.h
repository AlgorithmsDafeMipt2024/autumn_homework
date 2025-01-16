#ifndef __SOLUTION_H__
#define __SOLUTION_H__
#include <queue>
#include <vector>

class node {
 public:
  std::vector<std::pair<int, int>> neighbours;  // {id, size}
  int id;
  int len = 0;
  int pot = 0;
  bool locked = false;  //
  bool wisited = false;
};

void deixtra(std::vector<node>& nodes, int start);

bool bellford(std::vector<node>& nodes /*, int start*/);

std::vector<std::vector<int>> jonson(std::vector<node> nodes);

#endif  // !__DEIXTRA_H__
