#include <iostream>
#include <limits>
#include <map>
#include <vector>

std::vector<double> Dijkstra(std::vector<std::map<int, double>> data, int source) {
    std::vector<double> ans(data.size(), std::numeric_limits<double>::infinity());
    std::vector<bool> counted(data.size(), false);
    ans[source] = 0;
    counted[source] = true;
    int pending = source;
    double min_lenght;
    for (int i = 0; i < data.size() - 1; ++i) {
        for (auto neighbour : data[pending]) {
            if (ans[neighbour.first] > neighbour.second + ans[pending]) {
                ans[neighbour.first] = neighbour.second + ans[pending];
            }
        }
        min_lenght = std::numeric_limits<double>::infinity();
        for (int j = 0; j < data.size(); j++) {
            if ((ans[j] < min_lenght)&& !counted[j]) {
                min_lenght = ans[j];
                pending = j;
            }
        }
        counted[pending] = true;
    }
    return ans;
}

int main() { 
    std::vector<std::map<int, double>> data = {{{1, 1}, {2, 8}, {3, 5}, {4, 6}, {5, 6}}, {{2, 1}, {3, 11}, {4, 1}, {5, 8}}, {{3, 2}}, {{4, 2}}, {{5, 4}}, {{2, 1}}};
    std::vector<double> ans = Dijkstra(data, 0);
    for (auto elem : ans){
        std::cout << elem << std::endl;
    }
    return 0; 
}