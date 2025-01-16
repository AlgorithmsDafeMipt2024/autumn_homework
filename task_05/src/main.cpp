#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  int n;
  n = 17;  // cin >> n;
  vector<int> a(n);
  // for (int i = 0; i < n; i++) cin >> a[i];
  a = {1, 2, 3, 4, 5, 6, 0, 8, 10, 11, 2, 3, 4, 5, 7, 8, 6};
  int mx = (int)log2(n) + 1;
  vector<vector<int>> st(mx, vector<int>(n, 0));  // sparse_table
  st[0] = a;
  for (int lvl = 1; lvl < mx; lvl++) {
    int prevlvl = lvl - 1;
    for (int i = 0; i <= n - (1 << lvl); i++) {
      st[lvl][i] = min(st[prevlvl][i], st[prevlvl][i + (1 << prevlvl)]);
    }
  }
  int q;
  q = 1;  // cin >> q;
  int l, r;
  int n2;
  vector<int> log2_(n + 1);
  log2_[1] = 0;
  for (int i = 2; i <= n; i++) {
    log2_[i] = log2_[i >> 1] + 1;
  }

  for (; q; q--) {
    // cin >> l >> r;  // для 1-индексации нужно делать l-- r--
    l = 8;
    r = 16;
    n2 = log2_[r - l + 1];
    cout << min(st[n2][l], st[n2][r - (1 << n2) + 1]) << endl;
  }

  return 0;
}