#include <gtest/gtest.h>

#include "top_sort.hpp"

TEST(SimpleGraph, Simple) {
  int vertices = 3;
  int edges = 2;
  std::vector<std::pair<int, int>> edge = {{1, 2}, {2, 3}};

  std::vector<int> result = TopSort(vertices, edges, edge);
  std::vector<int> expected = {
      1, 2, 3};  

  ASSERT_EQ(result, expected);
}

TEST(GraphWithCycle, Simple) {
  int vertices = 3;
  int edges = 3;
  std::vector<std::pair<int, int>> edge = {{1, 2}, {2, 3}, {3, 1}};
  
  EXPECT_THROW(TopSort(vertices, edges, edge);, CycleGraph);
}

TEST(DisconnectedGraph, Simple) {
  int vertices = 4;
  int edges = 2;
  std::vector<std::pair<int, int>> edge = {{1, 2}, {3, 4}};

  std::vector<int> result = TopSort(vertices, edges, edge);
  std::vector<int> expected ={3, 4, 1, 2};

  ASSERT_EQ(result, expected);
}

TEST(SingleVertex, Simple) {
  int vertices = 1;
  int edges = 0;
  std::vector<std::pair<int, int>> edge = {};

  std::vector<int> result = TopSort(vertices, edges, edge);
  std::vector<int> expected = {1};

  ASSERT_EQ(result, expected);
}

TEST(MultipleValidOrders, Simple) {
    int vertices = 4;
    int edges = 3;
    std::vector<std::pair<int, int>> edge = {{1, 2}, {1, 3}, {3, 4}};
    
    std::vector<int> result = TopSort(vertices, edges, edge);
    std::vector<int> expected1 = {1, 3, 4, 2};
    
    ASSERT_EQ(result, expected1);
}

TEST(AllVerticesConnected, Simple) {
    int vertices = 5;
    int edges = 4;
    std::vector<std::pair<int, int>> edge = {{1, 2}, {2, 3}, {3, 4}, {4, 5}};
    
    std::vector<int> result = TopSort(vertices, edges, edge);
    std::vector<int> expected = {1, 2, 3, 4, 5};
    
    ASSERT_EQ(result, expected);
}

TEST(ReverseOrder, Simple) {
    int vertices = 3;
    int edges = 2;
    std::vector<std::pair<int, int>> edge = {{3, 2}, {2, 1}};
    
    std::vector<int> result = TopSort(vertices, edges, edge);
    std::vector<int> expected = {3, 2, 1};
    
    ASSERT_EQ(result, expected);
}

TEST(ComplexGraph, Simple) {
    int vertices = 6;
    int edges = 6;
    std::vector<std::pair<int, int>> edge = {{5, 2}, {5, 0}, {4, 0}, {4, 1}, {2, 3}, {3, 1}};
    
    std::vector<int> result = TopSort(vertices, edges, edge);
    std::vector<int> expected = {6, 5, 4, 0, 2, 3, 1};

    ASSERT_EQ(result, expected);
}

TEST(GraphWithMultipleCyclesm, Simple) {
    int vertices = 4;
    int edges = 5;
    std::vector<std::pair<int, int>> edge = {{1, 2}, {2, 3}, {3, 1}, {2, 4}, {4, 2}};
    
    EXPECT_THROW(TopSort(vertices, edges, edge), CycleGraph);
}

TEST(MediumGraph, Simple){
  int vertices = 6;
  int edges = 6;
  std::vector<std::pair<int, int>> edge = {{5, 2}, {4, 2}, {3, 4}, {6, 3}, {6, 1}, {5, 1}};
  std::vector<int> result = TopSort(vertices, edges, edge);
  std::vector<int> expected = {6, 5, 3, 4, 2, 1};

  ASSERT_EQ(result, expected);
}
