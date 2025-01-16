#include <cmath>
#include <iostream>
#include <vector>

#include "solution.h"

int main() {
  std::vector<node> nodes;
  std::vector<int> ans;

  int N = 5;
  nodes.resize(N);
  // список ребер
  /*nodes[1 2);*/
  nodes[0].neighbours.push_back(1);
  nodes[0].neighbours.push_back(4);
  nodes[1].neighbours.push_back(2);
  nodes[3].neighbours.push_back(0);
  nodes[3].neighbours.push_back(4);
  nodes[4].neighbours.push_back(1);
  nodes[4].neighbours.push_back(2);
  for (int i = 0; i < N; i++) {
    nodes[i].id = i;
  }

  for (int i = 0; i < ans.size(); i++) {
    std::cout << ans[i] << "\n";
  }

  bool flag = true;
  ans = solution(nodes);

  /*std::vector<node> nodes;*/
  /*std::vector<int> ans;*/
  /**/
  /*int n, k, tmp, N;*/
  /*std::cin >> N >> tmp; // колич*/
  /*nodes.resize(N);*/
  /*// список ребер*/
  /*while ((tmp--)>0) {*/
  /*  std::cin >> n >> k;*/
  /*  nodes[n].neighbours.push_back(k);*/
  /*}*/
  /*for(int i =0; i<N;i++){*/
  /*  nodes[i].id = i;*/
  /*}*/
  /**/
  /*ans = solution(nodes);*/

  for (int i = ans.size() - 1; i >= 0; i--) {
    std::cout << ans[i] << " ";
  }

  return 0;
}
