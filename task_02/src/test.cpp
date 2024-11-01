#include <gtest/gtest.h>

#include "bridges_and_point.hpp"

TEST(SimpleTest, Simple){
    int vertices = 6;
    int edge = 7;
    std::vector<std::pair<int, int>> edges = {{1, 2}, {2, 3}, {2, 4}, {2, 5}, {4, 5}, {1, 3}, {3, 6}};

    set<int> result = cut_point(vertices, edge, edges);
    set<int> expected = {2, 3};
    ASSERT_EQ(result, expected);
}