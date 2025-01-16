#include <cmath>
#include <iostream>
#include <vector>

#include "solution.h"

/*
 ______________________
/ .                    \
| ├── main.cpp         |
| ├── solution.cpp     |
| ├── solution.h       |
| ├── stack.cpp        |
| ├── stack.hpp        |
| └── test.cpp         |
|                      |
\ 1 directory, 6 files /
 ----------------------
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
                ||----w |
                ||     ||
*/
int main() {
  std::vector<node> nodes;

  int n, k = 0, tmp, N;
  N = 4;
  tmp = 4;  // колич
  nodes.resize(N);
  // список ребер
  std::vector<std::pair<int, int>> loh = {{0, 1}, {1, 2}, {2, 3}, {0, 2}};
  while (k < tmp) {
    nodes[loh[k].first].neighbours.push_back(loh[k].second);
    nodes[loh[k].second].neighbours.push_back(loh[k].first);
    k++;
  }
  /*std::vector<node> nodes;*/
  /**/
  /*int n, k, tmp, N;*/
  /*std::cin >> N >> tmp; // колич*/
  /*nodes.resize(N);*/
  /*// список ребер*/
  /*while ((tmp--)>0) {*/
  /*  std::cin >> n >> k;*/
  /*  nodes[n].neighbours.push_back(k);*/
  /*  nodes[k].neighbours.push_back(n);*/
  /*}*/

  auto ans = solution(nodes);

  std::cout << "\n\n" << ans.first.size() << "\n";
  for (int i = 0; i < ans.first.size(); i++) {
    std::cout << ans.first[i].first << " " << ans.first[i].second << "\n";
  }
  std::cout << "~~~~~~~~~~~~~~\n";
  for (int i = 0; i < ans.second.size(); i++) {
    std::cout << ans.second[i] << " ";
  }

  return 0;
}
