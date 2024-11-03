
#include <gtest/gtest.h>

#include "rmq.hpp"

TEST(RMQTest, test1) {
  vector<int> const data = {1,  3,  2,  7,  9,  11, 3,  2,  1,  5,
                            6,  8,  4,  0,  3,  6,  7,  2,  5,  9,
                            10, 12, 14, 13, 15, 18, 17, 16, 19, 20};
  RMQ<int> rmq(data);
  ASSERT_EQ(rmq.Query(0, 4), 1);
  ASSERT_EQ(rmq.Query(5, 10), 1);
  ASSERT_EQ(rmq.Query(10, 20), 0);
  ASSERT_EQ(rmq.Query(0, 29), 0);
  ASSERT_EQ(rmq.Query(15, 25), 2);
}

TEST(RMQTest, test2) {
  vector<int> const data = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0,
                            1,  2, 3, 4, 5, 6, 7, 8, 9, 10};
  RMQ<int> rmq(data);
  ASSERT_EQ(rmq.Query(0, 10), 0);
  ASSERT_EQ(rmq.Query(5, 15), 0);
  ASSERT_EQ(rmq.Query(10, 20), 0);
  ASSERT_EQ(rmq.Query(0, 20), 0);
  ASSERT_EQ(rmq.Query(3, 7), 3);
}

TEST(RMQTest, test3) {
  vector<int> const data = {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
                            5, 5, 5, 5, 5, 5, 5, 5, 5, 5};
  RMQ<int> rmq(data);
  ASSERT_EQ(rmq.Query(0, 10), 5);
  ASSERT_EQ(rmq.Query(5, 15), 5);
  ASSERT_EQ(rmq.Query(10, 20), 5);
  ASSERT_EQ(rmq.Query(0, 20), 5);
  ASSERT_EQ(rmq.Query(3, 7), 5);
}

TEST(RMQTest, test4) {
  vector<int> const data = {};
  RMQ<int> rmq(data);
  EXPECT_THROW(rmq.Query(1, 3), std::out_of_range);
}

TEST(RMQTest, test5) {
  vector<int> const data = {1, 2, 3};
  RMQ<int> rmq(data);
  EXPECT_THROW(rmq.Query(0, 3), std::out_of_range);
}

TEST(RMQTest, test6) {
  vector<int> const data = {1, 2, 3};
  RMQ<int> rmq(data);
  EXPECT_THROW(rmq.Query(-1, 2), std::out_of_range);
}