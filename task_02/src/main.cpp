#include <iostream>

#include "network.hpp"

int main() {
  // Create a graph to represent the network
  Network network;

  network.AddVertex(0);
  network.AddVertex(1);
  network.AddVertex(2);
  network.AddVertex(3);

  network.AddEdge(0, 1);
  network.AddEdge(1, 2);
  network.AddEdge(2, 0);
  network.AddEdge(2, 3);

  network.FindBridgesAndCutVertices();
}