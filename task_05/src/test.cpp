

#include <gtest/gtest.h>

#include <vector>

#include "rmq_array.tpp"

using namespace std;

// алгоритм не делает проверку на дурака! должны подаваться только валидные
// деревья

TEST(Rmq, test1) {
  vector<int> v{10, 3, 2, 17, 2, 1};
  RmqArray<int> r(v);
  EXPECT_EQ(r.rmq(0, 0), 10);
  EXPECT_EQ(r.rmq(0, 1), 3);
  EXPECT_EQ(r.rmq(0, 2), 2);
  EXPECT_EQ(r.rmq(0, 3), 2);
  EXPECT_EQ(r.rmq(0, 4), 2);
  EXPECT_EQ(r.rmq(0, 5), 1);
}

TEST(Rmq, test2) {
  vector<int> v{10, 3, 2, 17, 2, 1};
  RmqArray<int> r(v);
  EXPECT_EQ(r.rmq(0, 1), 3);
  EXPECT_EQ(r.rmq(2, 1), 2);
  EXPECT_EQ(r.rmq(3, 2), 2);
  EXPECT_EQ(r.rmq(4, 3), 2);
  EXPECT_EQ(r.rmq(5, 4), 1);
}

TEST(Rmq, test3) {
  vector<int> v{10, 3, 2, 17, 2, 1};
  RmqArray<int> r(v);
  EXPECT_EQ(r.rmq(3, 5), 1);
  EXPECT_EQ(r.rmq(4, 1), 2);
  EXPECT_EQ(r.rmq(0, 3), 2);
  EXPECT_EQ(r.rmq(2, 4), 2);
  EXPECT_EQ(r.rmq(5, 1), 1);
}

TEST(Rmq, test4) {
  vector<int> v{100, 0};
  RmqArray<int> r(v);
  EXPECT_EQ(r.rmq(0, 0), 100);
  EXPECT_EQ(r.rmq(1, 1), 0);
}

TEST(Rmq, test5) {
  vector<int> v{100};
  RmqArray<int> r(v);
  EXPECT_EQ(r.rmq(0, 0), 100);
}