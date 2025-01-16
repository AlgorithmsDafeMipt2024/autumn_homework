
#include <algorithm>
#include <deque>
#include <vector>

class node {
 public:
  std::vector<int> neighbours;
  int last = 0;
  int id;
  bool flag = true;  // белая
};

std::vector<int> solution(std::vector<node> nodes);
