#include <iostream>
#include <vector>
#include <algorithm>

void recursive_dfs(std::vector<std::vector<int>> &data, int root, std::vector<int> &status, std::vector<int> &top_order){
    status[root] = 1;
    for (int i = 0; i < data[root].size(); ++i){
        if (status[data[root][i]] == 0){
            recursive_dfs(data, data[root][i], status, top_order);
        } else if (status[data[root][i]] == 1) {
            throw std::runtime_error("cycle found");
        }
    }
    status[root] = 2;
    top_order.push_back(root);
}

std::vector<int> topological_sort(std::vector<std::vector<int>>& data){
    int lenth = data.size();
    std::vector<int> status(lenth, 0);
    std::vector<int> top_order;
    int flag = 1; 
    while (flag){
        flag = 0;
        for (int i = 0; i < lenth; ++i){
            if (status[i] != 2){
                flag = 1;
                recursive_dfs(data, i, status, top_order);
                break;
            }
        }
    }
    std::reverse(top_order.begin(), top_order.end());
    return top_order;
}

int main() { 
    return 0;
}
