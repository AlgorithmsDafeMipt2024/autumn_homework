#include <vector>
#include <cmath>

template<class Comparator>
std::vector<std::vector<double>> sparse_table(std::vector<double> vals, Comparator comp) {
    int K = static_cast<int>(std::log2(vals.size()))+1;
    std::vector<std::vector<double>> sparse_table;
    sparse_table.push_back(vals);
    int power = 1;

    for(int i=1; i<K; ++i) {
        std::vector<double> vali = {};
        for(int j = 0; j < sparse_table[i-1].size()-power; ++j) {
            (comp(sparse_table[i-1][j], sparse_table[i-1][j+power])) ? 
                vali.push_back(sparse_table[i-1][j]) : vali.push_back(sparse_table[i-1][j+power]);
        }
        sparse_table.push_back(vali);
        power*=2;
    }
    return sparse_table;
}

template<class Comparator>
double rmq(int start, int finish, std::vector<std::vector<double>> sparse_table, Comparator comp) {
    int K = static_cast<int>(std::log2(finish - start + 1));
    int power = 1;
    for(int p=0; p<K; ++p) 
        power *= 2;
    double result = (comp(sparse_table[K][start], sparse_table[K][finish-power+1])) ?
        sparse_table[K][start] : sparse_table[K][finish-power+1];
    return result;
}