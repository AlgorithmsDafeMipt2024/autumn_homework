#ifndef __DEIXTRA_H__
#define __DEIXTRA_H__

#include <queue>
#include <vector>

class node {
 public:
  std::vector<std::pair<int, int>> neighbours;  // {id, size}
  int id;
  int len;
  bool locked = false;  //
  bool wisited = false;
};

void deixtra(std::vector<node> &nodes, int start);

#endif  // !__DEIXTRA_H__
