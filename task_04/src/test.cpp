#include <gtest/gtest.h>

#include "graph.hpp"

using namespace std;

TEST(Dijkstra, test1) {
  vector<vector<int>> adj_matr = {{0, 10, kInf, 30, 100},
                                  {kInf, 0, 50, kInf, kInf},
                                  {kInf, kInf, 0, kInf, 10},
                                  {kInf, kInf, 20, 0, 60},
                                  {kInf, kInf, kInf, kInf, 0}};
  vector<int> result = {0, 10, 50, 30, 60};

  Graph a(adj_matr);
  EXPECT_EQ(a.Dijkstra(0), result);
}

TEST(Dijkstra, test2) {
  vector<vector<int>> adj_matr = {{0}};
  vector<int> result = {0};

  Graph a(adj_matr);
  EXPECT_EQ(a.Dijkstra(0), result);
}

TEST(Dijkstra, test3) {
  vector<vector<int>> adj_matr = {
      {0, kInf, kInf}, {kInf, 0, kInf}, {kInf, kInf, 0}};
  vector<int> result = {0, kInf, kInf};

  Graph a(adj_matr);
  EXPECT_EQ(a.Dijkstra(0), result);
}

TEST(Dijkstra, test4) {
  vector<vector<int>> adj_matr = {{0, 1, 3}, {1, 0, -1}, {3, kInf, 0}};
  vector<int> result = {0, 1, 0};

  Graph a(adj_matr);
  EXPECT_EQ(a.Dijkstra(0), result);
}

TEST(Dijkstra, test5) {
  vector<vector<int>> adj_matr = {
      {0, 1, 1, kInf, kInf, kInf, kInf},   {1, 0, 1, kInf, kInf, kInf, kInf},
      {1, 1, 0, kInf, kInf, kInf, kInf},   {kInf, kInf, kInf, 0, 1, 1, 1},
      {kInf, kInf, kInf, 1, 0, 1, kInf},   {kInf, kInf, kInf, 1, 1, 0, kInf},
      {kInf, kInf, kInf, 1, kInf, kInf, 0}};
  vector<int> result = {0, 1, 1, kInf, kInf, kInf, kInf};

  Graph a(adj_matr);
  EXPECT_EQ(a.Dijkstra(0), result);
}
TEST(Dijkstra, test6) {
  vector<vector<int>> adj_matr = {
      {0, 1, 1, kInf, kInf, kInf, kInf},   {1, 0, 1, kInf, kInf, kInf, kInf},
      {1, 1, 0, kInf, kInf, kInf, kInf},   {kInf, kInf, kInf, 0, 1, 1, 1},
      {kInf, kInf, kInf, 1, 0, 1, kInf},   {kInf, kInf, kInf, 1, 1, 0, kInf},
      {kInf, kInf, kInf, 1, kInf, kInf, 0}};
  vector<int> result = {kInf, kInf, kInf, 1, 0, 1, 2};

  Graph a(adj_matr);
  EXPECT_EQ(a.Dijkstra(4), result);
}

TEST(Dijkstra, test7) {
  vector<vector<int>> adj_matr = {{0, 1, 3, kInf},
                                  {1, 0, -1, kInf},
                                  {3, kInf, 0, kInf},
                                  {kInf, kInf, kInf, 0}};
  vector<int> result = {kInf, kInf, kInf, 0};

  Graph a(adj_matr);
  EXPECT_EQ(a.Dijkstra(3), result);
}

TEST(Dijkstra, test8) {
  vector<vector<int>> adj_matr = {{0, 1, 2, kInf, kInf, kInf, kInf},
                                  {kInf, 0, kInf, 1, kInf, kInf, kInf},
                                  {kInf, kInf, 0, kInf, 1, 4, kInf},
                                  {kInf, kInf, kInf, 0, kInf, kInf, kInf},
                                  {kInf, kInf, kInf, kInf, 0, kInf, 3},
                                  {kInf, kInf, kInf, kInf, kInf, 0, kInf},
                                  {kInf, kInf, kInf, kInf, kInf, kInf, 0}};
  vector<int> result = {0, 1, 2, 2, 3, 6, 6};

  Graph a(adj_matr);
  EXPECT_EQ(a.Dijkstra(0), result);
}
