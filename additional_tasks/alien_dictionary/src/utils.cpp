#include "utils.hpp"

void ForceAddDirEdge(Graph<Vertex<char>, char>& graph, char u, char v) {
  // Add vertices if they do not exist
  if (graph.Size() == 0 || graph.Find(u) == graph.Size()) {
    graph.AddVertex(u);
  }
  if (graph.Find(v) == graph.Size()) {
    graph.AddVertex(v);
  }
  // Add directed edge from u to v
  graph.AddDirEdge(graph.Find(u), graph.Find(v));
}

bool TopologicalSortStep(Graph<Vertex<char>, char>& graph, size_t v,
                         std::set<char>& visited, std::set<char>& recursion,
                         std::stack<char>& stack) {
  // Mark the current node as visited and add it to the recursion stack
  visited.insert(graph[v]->data);
  recursion.insert(graph[v]->data);

  // Recur for all the vertices adjacent to this vertex
  for (const auto& neighbor : graph[v]->adjacent) {
    if (recursion.find(neighbor->data) != recursion.end()) {
      // If the neighbor is in the recursion stack, we found a cycle
      return true;
    }
    if (visited.find(neighbor->data) == visited.end()) {
      if (TopologicalSortStep(graph, graph.Find(neighbor->data), visited,
                              recursion, stack)) {
        return true;  // Cycle detected in the recursive call
      }
    }
  }

  // Remove the vertex from recursion and add it to the result
  recursion.erase(graph[v]->data);
  stack.push(graph[v]->data);
  return false;  // No cycle detected
}

void FindAlphabeticOrder(const std::vector<std::string>& words) {
  if (words.empty()) return;  // No words to sort

  // Only one word, thus it contains the only character
  if (words.size() == 1) {
    std::cout << words[0] << std::endl;
    return;
  }

  Graph<Vertex<char>, char> graph;

  // Build the graph by iterating through adjacent words
  for (size_t i = 0; i < words.size() - 1; ++i) {
    std::string curr_word = words[i];
    std::string next_word = words[i + 1];
    size_t minLength = std::min(curr_word.length(), next_word.length());

    for (size_t j = 0; j < minLength; ++j) {
      if (curr_word[j] != next_word[j]) {
        ForceAddDirEdge(graph, curr_word[j], next_word[j]);
        break;  // Only the first different character matters
      }
    }
  }

  // Perform topological sorting and check for cycles
  std::set<char> visited;
  std::set<char> recursion;  // To keep track of the recursion
  std::stack<char> result;

  for (size_t i = 0; i < graph.Size(); ++i) {
    if (visited.find(graph[i]->data) == visited.end()) {
      if (TopologicalSortStep(graph, i, visited, recursion, result)) {
        std::cout << "The graph contains a cycle. Topological sorting is not "
                     "determined."
                  << std::endl;
        return;  // Cycle detected
      }
    }
  }

  // Print the characters in reverse order
  while (!result.empty()) {
    std::cout << result.top();
    result.pop();
  }
  std::cout << std::endl;
}
