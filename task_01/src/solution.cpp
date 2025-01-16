#include "solution.h"



std::vector<int> solution(std::vector<node> nodes){
  std::deque<int> gray;
  std::vector<int> ans;
  int N = nodes.size(),tmp=0;
  for(int i =0; i<N;i++){
    nodes[i].id = i;
    std::sort(nodes[i].neighbours.begin(), nodes[i].neighbours.end());
  }

  /*gray.push_back(0);*/
  node *current;

  tmp=0;
  int i = 0;
  while(true){
    if(i>=N){
      break;
    }
    if(nodes[i].flag==false){
      i++;
      continue;
    }
    gray.push_back(i);
    current = &nodes[i];

    while(gray.size()){
      current = &nodes[gray.back()];
      if(!current->flag){
        gray.pop_back();
        continue;
      }
      if(current->neighbours.size()<=current->last){
        ans.push_back(current->id);
        current->flag = false;
        gray.pop_back();
        continue;
      }
      tmp = current->neighbours[current->last];
      gray.push_back(tmp);
      current->last++;
    }
    i++;
  }
  return ans;

}


