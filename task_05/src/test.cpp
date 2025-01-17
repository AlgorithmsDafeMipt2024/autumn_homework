#include <gtest/gtest.h>

#include "RMQ.hpp"

TEST(Test_RMQ, Simple_Test_1) {
  RMQ rmq;

  ASSERT_THROW(rmq(0, 0), std::invalid_argument);
}

TEST(Test_RMQ, Simple_Test_2) {
  RMQ rmq({1});

  ASSERT_EQ(rmq(0, 0), 1);
}

TEST(Test_RMQ, Simple_Test_3) {
  RMQ rmq({1, 2, 3});

  ASSERT_EQ(rmq(0, 2), 1);
}

TEST(Test_RMQ, Simple_Test_4) {
  RMQ rmq({1, 2, 3});

  ASSERT_EQ(rmq(1, 2), 2);
}

TEST(Test_RMQ, Simple_Test_5) {
  RMQ rmq({1, 2, 3});

  ASSERT_THROW(rmq(1, 4), std::invalid_argument);
}

TEST(Test_RMQ, Test_1) {
  RMQ rmq({7, 23, 1, 56, 14});

  std::vector<int> expected{7, 7, 1, 1, 1, 23, 1, 1, 1, 1, 1, 1, 56, 14, 14};

  int count = 0;
  for (int i = 0; i < rmq.Size(); i++) {
    for (int j = i; j < rmq.Size(); j++)
      ASSERT_EQ(rmq(i, j), expected[count++]);
  }
}

TEST(Test_RMQ, Test_2) {
  RMQ rmq({15, 18, 87, 22, 39, 41, 13, 63, 93, 85, 54, 6, 48});

  std::vector<int> expected{15, 15, 15, 15, 15, 15, 13, 13, 13, 13, 13, 6,  6,
                            18, 18, 18, 18, 18, 13, 13, 13, 13, 13, 6,  6,  87,
                            22, 22, 22, 13, 13, 13, 13, 13, 6,  6,  22, 22, 22,
                            13, 13, 13, 13, 13, 6,  6,  39, 39, 13, 13, 13, 13,
                            13, 6,  6,  41, 13, 13, 13, 13, 13, 6,  6,  13, 13,
                            13, 13, 13, 6,  6,  63, 63, 63, 54, 6,  6,  93, 85,
                            54, 6,  6,  85, 54, 6,  6,  54, 6,  6,  6,  6,  48};

  int count = 0;
  for (int i = 0; i < rmq.Size(); i++) {
    for (int j = i; j < rmq.Size(); j++)
      ASSERT_EQ(rmq(i, j), expected[count++]);
  }
}

TEST(Test_RMQ, Test_3) {
  RMQ rmq({1, 1, 2, 2, 2, 1, 1, 2, 4});

  std::vector<int> expected{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                            1, 1, 2, 2, 2, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1,
                            2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 4};

  int count = 0;
  for (int i = 0; i < rmq.Size(); i++) {
    for (int j = i; j < rmq.Size(); j++)
      ASSERT_EQ(rmq(i, j), expected[count++]);
  }
}