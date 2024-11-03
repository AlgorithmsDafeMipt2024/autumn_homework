#include <climits>
#include <stdexcept>
#include <vector>

using std::vector;

/*
Один из самых быстрых реализаций алгоритма RMQ
Выдает запрос за O(1), предобработка структуры данных - O(n)
*/

template <typename T>
struct RMQ {
  vector<T> data;
  size_t size;
  static const size_t block_size = 30;
  vector<int> masks;
  vector<int> table;

  int Operation(int x, int y) { return data[x] < data[y] ? x : y; }
  int LeastSignificantBit(int x) { return x & -x; }
  int MostSignificantBitIndex(int x) { return 31 - __builtin_clz(x); }
  int Small(int r, int size = block_size) {
    int dist_from_r = MostSignificantBitIndex(masks[r] & ((1 << size) - 1));
    return r - dist_from_r;
  }

  RMQ(const vector<T>& v)
      : data(v),
        size(data.size()),
        masks(size),
        table((static_cast<size_t>(size / block_size) * 32)) {
    int current_mask = 0;
    for (size_t i = 0; i < size; i++) {
      current_mask = (current_mask << 1) & ((1 << block_size) - 1);
      while (current_mask > 0 &&
             Operation(i, i - MostSignificantBitIndex(
                                  LeastSignificantBit(current_mask))) == i) {
        current_mask ^= LeastSignificantBit(current_mask);
      }
      current_mask |= 1;
      masks[i] = current_mask;
    }
    for (int i = 0; i < size / block_size; i++)
      table[i] = Small(block_size * i + block_size - 1);
    for (int j = 1; (1 << j) <= size / block_size; j++)
      for (int i = 0; i + (1 << j) <= size / block_size; i++)
        table[size / block_size * j + i] =
            Operation(table[size / block_size * (j - 1) + i],
                      table[size / block_size * (j - 1) + i + (1 << (j - 1))]);
  }

  T Query(int l, int r) {
    if (l < 0 || r >= data.size())
      throw std::out_of_range("incorrect boundaries!");
    if (r - l + 1 <= block_size) return data[Small(r, r - l + 1)];
    int ans = Operation(Small(l + block_size - 1), Small(r));
    const int x = l / block_size + 1;
    const int y = r / block_size - 1;
    if (x <= y) {
      int j = MostSignificantBitIndex(y - x + 1);
      ans = Operation(
          ans, Operation(table[size / block_size * j + x],
                         table[size / block_size * j + y - (1 << j) + 1]));
    }
    return data[ans];
  }
};
