#include <gtest/gtest.h>

#include "graph/vertex.hpp"

TEST(TestVertex, Test_Constructors_1) {
  Vertex<size_t> v1(0, {1, 5, 3, 7, 4, 8});
  Vertex<size_t> v2(0, std::vector<size_t>{1, 5, 3, 7, 4, 8});

  ASSERT_EQ(v1.GetVertexId(), v2.GetVertexId());

  ASSERT_EQ(v1.GetAdjacentVertices().size(), v2.GetAdjacentVertices().size());

  for (int i = 0; i < v1.GetAdjacentVertices().size(); i++) {
    ASSERT_EQ(v1.GetAdjacentVertices()[i], v2.GetAdjacentVertices()[i]);
  }
}

TEST(TestVertex, Test_Constructors_2) {
  Vertex<char> v1('A', {'B', 'C', 'E', 'D', 'G'});
  Vertex<char> v2('A', std::vector<char>{'B', 'C', 'E', 'D', 'G'});

  ASSERT_EQ(v1.GetVertexId(), v2.GetVertexId());

  ASSERT_EQ(v1.GetAdjacentVertices().size(), v2.GetAdjacentVertices().size());

  for (int i = 0; i < v1.GetAdjacentVertices().size(); i++) {
    ASSERT_EQ(v1.GetAdjacentVertices()[i], v2.GetAdjacentVertices()[i]);
  }
}

TEST(TestVertex, Test_Constructors_3) {
  Vertex<std::string> v1("A", {"B", "C", "E", "D", "G"});
  Vertex<std::string> v2("A",
                         std::vector<std::string>{"B", "C", "E", "D", "G"});

  ASSERT_EQ(v1.GetVertexId(), v2.GetVertexId());

  ASSERT_EQ(v1.GetAdjacentVertices().size(), v2.GetAdjacentVertices().size());

  for (int i = 0; i < v1.GetAdjacentVertices().size(); i++) {
    ASSERT_EQ(v1.GetAdjacentVertices()[i], v2.GetAdjacentVertices()[i]);
  }
}

TEST(TestVertex, Test_AddAdjacentVertex) {
  Vertex<std::string> v1("A", {"B", "C", "E"});
  v1.AddAdjacentVertex("D");

  std::vector<std::string> expected_vertices{"B", "C", "E", "D"};

  ASSERT_EQ(v1.GetAdjacentVertices(), expected_vertices);
}
