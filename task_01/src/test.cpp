#include <gtest/gtest.h>
#include <vector>

#include "solution.h"

TEST(Test, Simple) {
  std::vector<node> nodes;
  std::vector<int> ans;

  int N=3;
  nodes.resize(N);
  // список ребер
  nodes[1].neighbours.push_back(2);
  nodes[0].neighbours.push_back(2);
  nodes[0].neighbours.push_back(1);
  for(int i =0; i<N;i++){
    nodes[i].id = i;
  }

  bool flag = true;
  ans = solution(nodes);
  std::vector<int> assertion = {0,1,2};
  ASSERT_TRUE(assertion.size() == ans.size());
  for(int i = 0;i<ans.size();i++){
    flag = flag&&(ans[N-i-1]==assertion[i]);
  }
  ASSERT_TRUE(flag)<<ans[0]<<" УЭЭЭЭЭЭ";

}

TEST(Test, Simple2) {
  std::vector<node> nodes;
  std::vector<int> ans;

  int N=5;
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
  for(int i =0; i<N;i++){
    nodes[i].id = i;
  }

  for(int i = 0;i<ans.size();i++){
    std::cout<<ans[i]<<"\n";
  }

  bool flag = true;
  ans = solution(nodes);
  std::vector<int> assertion = {3, 0, 4, 1, 2};
  ASSERT_TRUE(assertion.size() == ans.size());
  for(int i = 0;i<ans.size();i++){
    flag = flag&&(ans[N-i-1]==assertion[i]);
  }
  ASSERT_TRUE(flag)<<ans[0]<<" УЭЭЭЭЭЭ";

}


TEST(Test, Simpl3) {
  std::vector<node> nodes;
  std::vector<int> ans;

  int N=6;
  nodes.resize(N);
  // список ребер
  // 0 -> 1
  // V    Δ
  // 3 -> 4
  // 5 -> 2
  nodes[0].neighbours.push_back(1);
  nodes[5].neighbours.push_back(2);
  nodes[3].neighbours.push_back(4);
  nodes[0].neighbours.push_back(3);
  nodes[4].neighbours.push_back(1);
  for(int i =0; i<N;i++){
    nodes[i].id = i;
  }
  bool flag = true;
  ans = solution(nodes);
  std::vector<int> assertion = {5, 2, 0, 3, 4, 1};
  ASSERT_TRUE(assertion.size() == ans.size());
  for(int i = 0;i<ans.size();i++){
    flag = flag&&(ans[N-i-1]==assertion[i]);
  }
  ASSERT_TRUE(flag)<<ans[2]<<" УЭЭЭЭЭЭ";

}


