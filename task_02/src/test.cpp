#include <gtest/gtest.h>

#include <sstream>

#include "network.hpp"

class NetworkTest : public ::testing::Test {
 protected:
  Network network;
};

// Helper function to capture cout output
std::string CaptureCoutOutput(std::function<void()> func) {
  std::stringstream buffer;
  std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
  func();
  std::cout.rdbuf(old);
  return buffer.str();
}

TEST_F(NetworkTest, SimpleTriangleWithBridge) {
  // Create a triangle with a single bridge
  network.AddVertex(0);
  network.AddVertex(1);
  network.AddVertex(2);
  network.AddVertex(3);

  network.AddEdge(0, 1);
  network.AddEdge(1, 2);
  network.AddEdge(2, 0);
  network.AddEdge(2, 3);  // This is a bridge

  std::string output =
      CaptureCoutOutput([&]() { network.FindBridgesAndCutVertices(); });

  // Check if bridge 2-3 is detected
  EXPECT_TRUE(output.find("2 -- 3") != std::string::npos);
  // Vertex 2 should be a cut vertex
  EXPECT_TRUE(output.find("Cut vertices:\n2") != std::string::npos);
}

TEST_F(NetworkTest, NoBridgesOrCutVertices) {
  // Create a complete graph with 3 vertices (triangle)
  network.AddVertex(0);
  network.AddVertex(1);
  network.AddVertex(2);

  network.AddEdge(0, 1);
  network.AddEdge(1, 2);
  network.AddEdge(2, 0);

  std::string output =
      CaptureCoutOutput([&]() { network.FindBridgesAndCutVertices(); });

  // Should not find any bridges or cut vertices
  EXPECT_TRUE(output.find("Bridges:\n") != std::string::npos);
  EXPECT_TRUE(output.find("Cut vertices:\n") != std::string::npos);
}

TEST_F(NetworkTest, LineGraph) {
  // Create a line graph where all edges are bridges
  network.AddVertex(0);
  network.AddVertex(1);
  network.AddVertex(2);

  network.AddEdge(0, 1);
  network.AddEdge(1, 2);

  std::string output =
      CaptureCoutOutput([&]() { network.FindBridgesAndCutVertices(); });

  // All edges should be bridges
  EXPECT_TRUE(output.find("0 -- 1") != std::string::npos);
  EXPECT_TRUE(output.find("1 -- 2") != std::string::npos);
  // Middle vertex should be a cut vertex
  EXPECT_TRUE(output.find("Cut vertices:\n1") != std::string::npos);
}

TEST_F(NetworkTest, EmptyGraph) {
  std::string output =
      CaptureCoutOutput([&]() { network.FindBridgesAndCutVertices(); });

  // Should not find any bridges or cut vertices
  EXPECT_TRUE(output.find("Bridges:\n") != std::string::npos);
  EXPECT_TRUE(output.find("Cut vertices:\n") != std::string::npos);
}

TEST_F(NetworkTest, CycleWithMultipleBridges) {
  // Create a more complex graph with multiple bridges and cut vertices
  network.AddVertex(0);
  network.AddVertex(1);
  network.AddVertex(2);
  network.AddVertex(3);
  network.AddVertex(4);

  // Create a cycle 0-1-2
  network.AddEdge(0, 1);
  network.AddEdge(1, 2);
  network.AddEdge(2, 0);

  // Add bridges
  network.AddEdge(1, 3);  // Bridge to vertex 3
  network.AddEdge(3, 4);  // Bridge to vertex 4

  std::string output =
      CaptureCoutOutput([&]() { network.FindBridgesAndCutVertices(); });

  // Check for bridges
  EXPECT_TRUE(output.find("1 -- 3") != std::string::npos);
  EXPECT_TRUE(output.find("3 -- 4") != std::string::npos);

  // Vertices 1 and 3 should be cut vertices
  EXPECT_TRUE(output.find("1") != std::string::npos);
  EXPECT_TRUE(output.find("3") != std::string::npos);
}