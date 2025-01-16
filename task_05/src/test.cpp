#include <RMQ.h>
#include <gtest/gtest.h>

TEST(RMQTest, Simple) {
  std::vector<double> testArray = {1, 3, 2, 7, 9, 11, 5, 4, 6, 8};
  RMQ testRMQ(testArray);
  ASSERT_EQ(testRMQ.get_min(0, 5), 0);
  ASSERT_EQ(testRMQ.get_min(3, 7), 7);
  ASSERT_EQ(testRMQ.get_min(7, 8), 7);
  ASSERT_EQ(testRMQ.get_min(2, 2), 2);
  ASSERT_EQ(testRMQ.get_min(3, 5), 3);
  ASSERT_EQ(testRMQ.get_min(5, 9), 7);
}
