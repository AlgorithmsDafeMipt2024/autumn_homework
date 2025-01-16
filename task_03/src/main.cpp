#include <iostream>
#include "solution.h"


int main() {
  std::vector<std::vector<int>> expected = {{0,-1,2,-2,1},{999,0,3,-1,2},{1000,998,0,997,1000},{1000,1,4,0,3},{997,-2,1,-3,0}};
  std::vector<node> nodes;
  std::vector<int> edges = {0, -1, 4, 1000, 1000,
                            1000, 0, 3, 2, 2,
                            1000, 1000, 0, 1000, 1000,
                            1000, 1, 5, 1000, 1000,
                            1000, 1000, 1000, -3, 1000};
  int n=5,tmp;
  nodes.resize(n);
  for(int i = 0; i<n; i++){
    for(int j=0;j<n;j++){
      if(i==j){
        continue;
      }
      nodes[i].neighbours.push_back({j, edges[i*n+j]});
    }
  }
  auto ans = jonson(nodes);
  for(int i = 0;i<ans.size();i++){
    for(int j = 0;j<ans.size();j++){
      if(i == j){
        continue;
      }
      if(ans[i][j]!=expected[i][j])
        std::cout<<" "<< i << " "<<j<<" "<<ans[i][j]<<" "<<expected[i][j]<<"\n";
    }
  }

return 0; }
