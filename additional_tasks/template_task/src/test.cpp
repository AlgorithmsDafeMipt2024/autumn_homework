#include <gtest/gtest.h>

#include "DCU.hpp"

using namespace std;

TEST(Template, Simple) {
  int vertices = 3;
  int edge = 3;
  vector<vector<int>> edges = {{1, 2, 4}, {2, 3, 5}, {1, 3, 3}};

  int result = main_part(vertices, edge, edges);
  int expected = 7;
  ASSERT_EQ(result, expected);
}

TEST(Error, Simple) {
  int vertices = 3;
  int edge = 1;
  vector<vector<int>> edges = {{1, 2, 4}};

  EXPECT_THROW(main_part(vertices, edge, edges), NotMST);
}

TEST(Template, NoEdges) {
  int vertices = 5;
  int edge = 0;
  vector<vector<int>> edges = {};

  EXPECT_THROW(main_part(vertices, edge, edges), NotMST);
}

TEST(Template, MultipleEdgesSameWeight) {
  int vertices = 4;
  int edge = 5;
  vector<vector<int>> edges = {
      {1, 2, 1}, {2, 3, 1}, {3, 4, 1}, {1, 4, 1}, {2, 4, 1}};

  int result = main_part(vertices, edge, edges);
  int expected = 3;  // MST can include edges with weight 1
  ASSERT_EQ(result, expected);
}

TEST(Template, DisconnectedGraph) {
  int vertices = 4;
  int edge = 2;
  vector<vector<int>> edges = {{1, 2, 1}, {3, 4, 1}};

  EXPECT_THROW(main_part(vertices, edge, edges), NotMST);
}

TEST(Template, LargerGraph) {
  int vertices = 6;
  int edge = 8;
  vector<vector<int>> edges = {{1, 2, 4}, {1, 3, 1}, {2, 3, 2}, {2, 4, 5},
                               {3, 4, 8}, {4, 5, 3}, {5, 6, 7}, {4, 6, 6}};

  int result = main_part(vertices, edge, edges);
  int expected = 17;  // Minimum spanning tree weight
  ASSERT_EQ(result, expected);
}
