#include <cmath>
#include <vector>

using std::vector;

/*
Алгоритм Фарака-Колтона и Бендера
Выдает запрос за O(1), предобработка структуры данных - O(n)
*/

class LCA {
 public:
  LCA(const vector<vector<int>>& tree, int root);
  int Query(int u, int v);

 private:
  vector<vector<int>> up;
  vector<int> depth;
  size_t n;

  void Dfs(const vector<vector<int>>& tree, int v, int p);
};
