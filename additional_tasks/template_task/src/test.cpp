#include <gtest/gtest.h>

#include "utils.hpp"

// Test Case 1: Single Row with Mixed States
TEST(RecoverForestTests, SingleRowMixedStates) {
  std::vector<std::vector<int>> forest = {{2, 1, 0, 1, 2}};
  std::vector<std::pair<int, int>> unrecovered;
  int result = RecoverForest(forest, unrecovered);
  EXPECT_EQ(result, 1);
}

// Test Case 2: Single Column with All Preserved
TEST(RecoverForestTests, SingleColumnAllPreserved) {
  std::vector<std::vector<int>> forest = {{2}, {2}, {2}, {2}};
  std::vector<std::pair<int, int>> unrecovered;
  int result = RecoverForest(forest, unrecovered);
  EXPECT_EQ(result, 0);
}

// Test Case 3: Large Grid with Multiple Isolated Parts
TEST(RecoverForestTests, LargeGridMultipleIsolatedParts) {
  std::vector<std::vector<int>> forest = {{0, 0, 2, 0, 0},
                                          {0, 1, 0, 1, 0},
                                          {0, 0, 0, 0, 0},
                                          {2, 0, 0, 1, 0},
                                          {0, 0, 0, 0, 2}};
  std::vector<std::pair<int, int>> unrecovered;
  int result = RecoverForest(forest, unrecovered);
  EXPECT_EQ(result, -1);
  EXPECT_EQ(unrecovered.size(), 3);
  EXPECT_EQ(unrecovered[0], std::make_pair(1, 1));
  EXPECT_EQ(unrecovered[1], std::make_pair(1, 3));
  EXPECT_EQ(unrecovered[2], std::make_pair(3, 3));
}

// Test Case 4: All Burned Except One
TEST(RecoverForestTests, AllBurnedExceptOne) {
  std::vector<std::vector<int>> forest = {{0, 0, 0}, {0, 2, 0}, {0, 0, 0}};
  std::vector<std::pair<int, int>> unrecovered;
  int result = RecoverForest(forest, unrecovered);
  EXPECT_EQ(result, 0);
  EXPECT_EQ(unrecovered.size(), 0);
}

// Test Case 5: Large Grid with All Preserved and One Isolated Partially Burned
TEST(RecoverForestTests, LargeGridAllPreservedOneIsolated) {
  std::vector<std::vector<int>> forest = {
      {2, 2, 2, 2}, {2, 1, 2, 2}, {2, 2, 2, 2}};
  std::vector<std::pair<int, int>> unrecovered;
  int result = RecoverForest(forest, unrecovered);
  EXPECT_EQ(result, 1);
  EXPECT_EQ(unrecovered.size(), 0);
}

// Test Case 6: Circular Recovery
TEST(RecoverForestTests, CircularRecovery) {
  std::vector<std::vector<int>> forest = {{2, 1, 2}, {1, 0, 1}, {2, 1, 2}};
  std::vector<std::pair<int, int>> unrecovered;
  int result = RecoverForest(forest, unrecovered);
  EXPECT_EQ(result, 1);
}

// Test Case 7: Large Sparse Grid
TEST(RecoverForestTests, LargeSparseGrid) {
  std::vector<std::vector<int>> forest = {{0, 0, 0, 0, 0, 0, 0},
                                          {0, 2, 0, 0, 1, 0, 0},
                                          {0, 0, 0, 0, 0, 0, 0},
                                          {0, 0, 0, 2, 0, 0, 0},
                                          {0, 0, 1, 0, 0, 0, 0}};
  std::vector<std::pair<int, int>> unrecovered;
  int result = RecoverForest(forest, unrecovered);
  EXPECT_EQ(result, -1);
  EXPECT_EQ(unrecovered.size(), 2);
  EXPECT_EQ(unrecovered[0], std::make_pair(1, 4));
  EXPECT_EQ(unrecovered[1], std::make_pair(4, 2));
}

// Test Case 8: Edge Case with One Chunk
TEST(RecoverForestTests, EdgeCaseOneChunk) {
  std::vector<std::vector<int>> forest = {{1}};
  std::vector<std::pair<int, int>> unrecovered;
  int result = RecoverForest(forest, unrecovered);
  EXPECT_EQ(result, -1);
  EXPECT_EQ(unrecovered.size(), 1);
  EXPECT_EQ(unrecovered[0], std::make_pair(0, 0));
}