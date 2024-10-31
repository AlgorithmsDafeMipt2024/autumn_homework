#include "network.hpp"

void Network::TarjanVisit(size_t vertex_id, std::vector<int> &disc,
                          std::vector<int> &low, std::vector<int> &parent,
                          std::vector<std::pair<int, int>> &bridges,
                          std::vector<int> &cut_vertices, int &time) {
  // Visiting another vertex
  low[vertex_id] = disc[vertex_id] = time++;

  // Counter of child nodes DFS traversal tree (for cut vertices)
  int children = 0;

  // Iterate over all adjacent vertices
  for (auto &neighbor : vertices_[vertex_id]->adjacent) {
    size_t neighbor_id = Find(neighbor);

    if (disc[neighbor_id] == -1) {  // Vertex is not visited
      children++;
      parent[neighbor_id] = vertex_id;

      // DFS traversal
      TarjanVisit(neighbor_id, disc, low, parent, bridges, cut_vertices, time);

      // Update low value of current vertex
      low[vertex_id] = std::min(low[vertex_id], low[neighbor_id]);

      // Update bridges
      if (low[neighbor_id] > disc[vertex_id])
        bridges.emplace_back(vertex_id, neighbor_id);

      // Update cut vertices
      if ((low[neighbor_id] >= disc[vertex_id]) && (parent[vertex_id] != -1))
        cut_vertices.push_back(vertex_id);
    } else if (parent[vertex_id] != neighbor_id)  // Vertex is visited
      // Update low value of current vertex
      low[vertex_id] = std::min(low[vertex_id], disc[neighbor_id]);
  }
  // Update cut vertices
  if ((parent[vertex_id] == -1) && (children > 1))
    cut_vertices.push_back(vertex_id);
}

void Network::FindBridgesAndCutVertices() {
  std::vector<int> disc(Size(), -1);
  std::vector<int> low(Size(), -1);
  std::vector<int> parent(Size(), -1);
  std::vector<std::pair<int, int>> bridges;
  std::vector<int> cut_vertices;

  int time = 0;
  for (size_t vertex_id = 0; vertex_id < Size(); ++vertex_id)
    if (disc[vertex_id] == -1)
      TarjanVisit(vertex_id, disc, low, parent, bridges, cut_vertices, time);

  // Print bridges
  std::cout << "Bridges:" << std::endl;
  for (const auto &bridge : bridges)
    std::cout << bridge.first << " -- " << bridge.second << std::endl;

  // Print cut vertices
  std::cout << "Cut vertices:" << std::endl;
  for (const auto &cut_vertex : cut_vertices)
    std::cout << cut_vertex << std::endl;
}