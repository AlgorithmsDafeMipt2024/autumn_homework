#ifndef AUTUMN_HOMEWORK_TASK_06_RMQ_1_ARRAY_TPP_
#define AUTUMN_HOMEWORK_TASK_06_RMQ_1_ARRAY_TPP_
#include <cmath>
#include <cstddef>
#include <vector>

using namespace std;
// rmq+-1 -- rmq для массива, в котором все соседи отличаются на +-1
// сложность получения O(1) и сложность построения O(n)
template <typename T>
class Rmq_1_Array {
 public:
  struct MinIndexPair {
    size_t i;
    T min;
    MinIndexPair() = default;
    MinIndexPair(std::size_t i, const vector<T>& arr) {
      this->i = i;
      min = arr[i];
    }
  };
  Rmq_1_Array(vector<T> arr) : arr_{arr}, n_{arr.size()} { precalc(); }
  Rmq_1_Array(){};
  Rmq_1_Array& operator=(const Rmq_1_Array& other) {
    n_ = other.n_;
    arr_ = other.arr_;
    block_min_ = other.block_min_;
    b_ = other.b_;
    sparce_table_b_ = other.sparce_table_b_;
    type_ = other.type_;
    block_size_ = other.block_size_;
    return *this;
  }
  MinIndexPair rmq1(size_t l, size_t r) {
    if (l > r) swap(l, r);
    size_t bl = l / block_size_;
    size_t br = r / block_size_;
    if (bl == br)  // < если оба индекса внутри одного блока

      return MinIndexPair(blockRmq(bl, l % block_size_, r % block_size_), arr_);

    MinIndexPair ans_l(blockRmq(bl, l % block_size_, block_size_ - 1), arr_);
    // ^^^ найдем минимум на отрезке от l до конца блока, содержащего l
    MinIndexPair ans_r(blockRmq(br, 0, r % block_size_), arr_);
    // ^^^ найдем минимум от начала блока, содержащего r, до r
    MinIndexPair min_lr = ans_l.min < ans_r.min ? ans_l : ans_r;
    // vvv найдем минимум на блоках между крайними, если таковые есть
    if (bl + 1 < br) {
      size_t power = log(br - bl - 1);

      MinIndexPair ans_b;
      if (arr_[sparce_table_b_[bl + 1llu][power]] <
          arr_[sparce_table_b_[br - (1llu << power)][power]])
        ans_b = MinIndexPair(sparce_table_b_[bl + 1llu][power], arr_);
      else
        ans_b =
            MinIndexPair(sparce_table_b_[br - (1llu << power)][power], arr_);

      return ans_b.min < min_lr.min ? ans_b : min_lr;
    }
    return min_lr;
  }

 private:
  size_t n_;
  vector<T> arr_;
  vector<vector<vector<T>>> block_min_;
  vector<T> b_;
  vector<vector<T>> sparce_table_b_;
  vector<size_t> type_;
  size_t block_size_;
  void precalc() {
    block_size_ = log(n_);  // размеры блоков
    if (block_size_ == 0) exit(-1);
    size_t k = n_ % block_size_ == 0 ? n_ / block_size_ : n_ / block_size_ + 1;
    // ^^^ количество блоков
    // vvv подсчет позиций минимумов в каждом блоке
    T cur_block = -1;
    b_ = vector<T>(k, -1);
    for (size_t i = 0; i < n_; ++i) {
      if (i % block_size_ == 0) cur_block++;
      if (b_[cur_block] == -1 || arr_[b_[cur_block]] > arr_[i])
        b_[cur_block] = i;
    }
    // vvv построение разреженной таблицы на b_
    sparce_table_b_ = vector<vector<T>>(k, vector<T>(log(n_) + 1));
    for (size_t i = 0; i < k; ++i) sparce_table_b_[i][0] = b_[i];
    for (size_t j = 1; j <= log(n_); ++j)
      for (size_t i = 0; i < k; ++i) {
        size_t ind = (1 << (j - 1)) + i;
        if (ind >= k)
          sparce_table_b_[i][j] = sparce_table_b_[i][j - 1];
        else if (arr_[sparce_table_b_[i][j - 1]] >
                 arr_[sparce_table_b_[ind][j - 1]])
          sparce_table_b_[i][j] = sparce_table_b_[ind][j - 1];
        else
          sparce_table_b_[i][j] = sparce_table_b_[i][j - 1];
      }
    // vvv подсчет типов каждого блока
    type_ = vector<size_t>(k, 0);
    cur_block = 0;
    for (size_t j = 0, i = 0; i < n_ or j < block_size_; ++j, ++i) {
      if (j >= block_size_) {
        j = 0;
        cur_block++;
      }
      if (j > 0 and (i >= n_ or arr_[i - 1] < arr_[i]))
        type_[cur_block] += (1 << (j - 1));
    }
    // vvv подсчет позиций минимумов на всех подотрезках для каждого блока
    block_min_ = vector<vector<vector<T>>>(
        k, vector<vector<T>>(block_size_, vector<T>(block_size_, -1)));
    for (size_t i = 0; i < k; ++i) {
      size_t t = type_[i];
      if (block_min_[t][0][0] == -1)
        // ^^^ если там записано, что-то отличное от -1, то значит, мы уже
        // ^   посчитали ответ для такого типа отрезков
        for (size_t l = 0; l < block_size_; ++l) {
          block_min_[t][l][l] = l;
          for (size_t r = l + 1; r < block_size_; ++r) {
            block_min_[t][l][r] = block_min_[t][l][r - 1];
            if (i * block_size_ + r <= n_ and
                arr_[i * block_size_ + block_min_[t][l][r]] >
                    arr_[i * block_size_ + r])
              block_min_[t][l][r] = r;
          }
        }
    }
  }
  T blockRmq(size_t block_num, size_t l, size_t r) {
    return block_min_[type_[block_num]][l][r] + block_num * block_size_;
  }
};

#endif