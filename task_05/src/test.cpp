#include <gtest/gtest.h>

#include "rmq.hpp"

TEST(RMQ, Simple) {
  std::vector<double> data = {1, 4, 7, 9, 4, 4, 3, 2, 7, 9, 5};
  std::vector<std::vector<double>> table = Sparse(data);
  double answer = Infinum(table, 1, 5);
  double correct = 4;
  ASSERT_EQ(answer, correct);
}

TEST(RMQ, Simple2) {
  std::vector<double> data = {1, 4, 7, 9, 4, 4, 3, 2, 7, 9, 5};
  std::vector<std::vector<double>> table = Sparse(data);
  double answer = Infinum(table, 3, 8);
  double correct = 2;
  ASSERT_EQ(answer, correct);
}

TEST(RMQ, Whole) {
  std::vector<double> data = {1, 4, 7, 9, 4, 4, 3, 2, 7, 9, 5};
  std::vector<std::vector<double>> table = Sparse(data);
  double answer = Infinum(table, 0, 10);
  double correct = 1;
  ASSERT_EQ(answer, correct);
}

TEST(RMQ, Big) {
  std::vector<double> data = {
      1,  2,  3,  1,  4, 8, 3, 6, 8, 3, 7, 8, 9, 5,  3,  4,  8, 34, 8, 6,
      12, 8,  4,  8,  5, 9, 7, 8, 5, 7, 9, 7, 8, 4,  8,  12, 5, 7,  9, 6,
      8,  14, 13, 12, 8, 7, 6, 9, 8, 3, 6, 8, 6, 11, 10, 9,  8, 11, 2};
  std::vector<std::vector<double>> table = Sparse(data);
  double answer = Infinum(table, 15, 54);
  double correct = 3;
  ASSERT_EQ(answer, correct);
}