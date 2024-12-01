#include "merge_users.hpp"

std::vector<User> DFSMergeUtil(const Graph<Vertex<UserData>, UserData>& graph,
                               std::map<std::string, std::size_t>& node_index) {
  std::vector<bool> visited(graph.Size(), false);
  std::vector<User> merged_users;

  for (std::size_t i = 0; i < graph.Size(); ++i)
    if (!visited[i]) {
      std::set<std::string> names;
      std::set<std::string> emails;
      std::stack<std::size_t> stack;
      stack.push(i);
      visited[i] = true;

      while (!stack.empty()) {
        std::size_t u = stack.top();
        stack.pop();
        UserData node = graph[u]->data;

        if (node.type == Type::Name)
          names.insert(node.data);
        else
          emails.insert(node.data);

        for (const auto& neighbor : graph[u]->adjacent) {
          int v = node_index[neighbor->data.data];
          if (!visited[v]) {
            visited[v] = true;
            stack.push(v);
          }
        }
      }
      // Take the first user as representative
      if (!names.empty()) merged_users.push_back(User(*names.cbegin(), emails));
    }
  return merged_users;
}

std::vector<User> MergeUsers(std::vector<User>& users) {
  // Create a graph
  Graph<Vertex<UserData>, UserData> graph;

  // Create a map to store the index of each node (string to integer)
  std::map<std::string, std::size_t> node_index;

  // Add vertices to the graph
  for (const auto& user : users) {
    if (node_index.find(user.name) == node_index.end()) {
      node_index[user.name] = graph.Size();
      graph.AddVertex(UserData(user.name, Type::Name));
    }
    for (const std::string& email : user.emails) {
      if (node_index.find(email) == node_index.end()) {
        node_index[email] = graph.Size();
        graph.AddVertex(UserData(email, Type::Email));
      }
      graph.AddEdge(node_index[user.name], node_index[email]);
    }
  }
  std::vector<User> merged_users = DFSMergeUtil(graph, node_index);
  return merged_users;
}
