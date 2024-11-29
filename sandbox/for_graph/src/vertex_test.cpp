#include <gtest/gtest.h>

#include <stdexcept>

#include "graph/vertex.hpp"

TEST(TestVertex, Test_Constructors_1) {
  Vertex<size_t> v1(0, {1, 5, 3, 7, 4, 8});
  Vertex<size_t> v2(0, std::vector<size_t>{1, 5, 3, 7, 4, 8});

  ASSERT_EQ(v1.GetVertexId(), v2.GetVertexId());

  ASSERT_EQ(v1.GetAdjVertices().size(), v2.GetAdjVertices().size());

  for (int i = 0; i < v1.GetAdjVertices().size(); i++) {
    ASSERT_EQ(v1.GetAdjVertices()[i], v2.GetAdjVertices()[i]);
  }
}

TEST(TestVertex, Test_Constructors_2) {
  Vertex<char> v1('A', {'B', 'C', 'E', 'D', 'G'});
  Vertex<char> v2('A', std::vector<char>{'B', 'C', 'E', 'D', 'G'});

  ASSERT_EQ(v1.GetVertexId(), v2.GetVertexId());

  ASSERT_EQ(v1.GetAdjVertices().size(), v2.GetAdjVertices().size());

  for (int i = 0; i < v1.GetAdjVertices().size(); i++) {
    ASSERT_EQ(v1.GetAdjVertices()[i], v2.GetAdjVertices()[i]);
  }
}

TEST(TestVertex, Test_Constructors_3) {
  Vertex<std::string> v1("A", {"B", "C", "E", "D", "G"});
  Vertex<std::string> v2("A",
                         std::vector<std::string>{"B", "C", "E", "D", "G"});

  ASSERT_EQ(v1.GetVertexId(), v2.GetVertexId());

  ASSERT_EQ(v1.GetAdjVertices().size(), v2.GetAdjVertices().size());

  for (int i = 0; i < v1.GetAdjVertices().size(); i++) {
    ASSERT_EQ(v1.GetAdjVertices()[i], v2.GetAdjVertices()[i]);
  }
}

TEST(TestVertex, Test_AddAdjVertex) {
  Vertex<std::string> v1("A", {"B", "C", "E"});
  v1.AddAdjVertex("D");

  std::vector<std::string> expected_vertices{"B", "C", "E", "D"};

  ASSERT_EQ(v1.GetAdjVertices(), expected_vertices);
}

TEST(TestVertex, Test_DeleteAdjVertex) {
  Vertex<std::string> v1("A", {"B", "C", "E"});
  v1.DeleteAdjVertex("C");

  std::vector<std::string> expected_vertices{"B", "E"};

  ASSERT_EQ(v1.GetAdjVertices(), expected_vertices);

  ASSERT_THROW(v1.DeleteAdjVertex("D"), std::invalid_argument);
}

TEST(TestVertex, Test_ContainsAdjVertex) {
  Vertex<std::string> v1("A", {"B", "C", "E"});

  ASSERT_EQ(v1.ContainsAdjVertex("C"), true);

  v1.DeleteAdjVertex("C");
  ASSERT_EQ(v1.ContainsAdjVertex("C"), false);

  v1.AddAdjVertex("F");
  ASSERT_EQ(v1.ContainsAdjVertex("F"), true);
}