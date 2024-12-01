#pragma once

#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <string>
#include <vector>

#include "graph.hpp"

/// @brief Type of user data
enum Type { Name, Email };

/// @brief User data
struct UserData {
  UserData(const std::string& data, Type type) : data(data), type(type) {}
  std::string data;
  Type type;
};

inline std::ostream& operator<<(std::ostream& os, const UserData& u_data) {
  os << u_data.data;
  return os;
}

/// @brief User with a name and email
struct User {
  User(const std::string& name, const std::set<std::string>& emails)
      : name(name), emails(emails) {}
  std::string name;
  std::set<std::string> emails;  // set to avoid duplicates
};

inline std::ostream& operator<<(std::ostream& os, const User& u) {
  os << u.name << " -> ";
  for (const std::string& email : u.emails) os << email << " ";
  return os;
}

inline bool operator==(const User& fu, const User& su) {
  return fu.name == su.name && fu.emails == su.emails;
}

/// @brief Perform Depth-First Search (DFS) to find connected components
/// @param graph : The graph to search
/// @param node_index : Quick access form data to index
/// @return Contatiner of merged users
std::vector<User> DFSMergeUtil(const Graph<Vertex<UserData>, UserData>& graph,
                               std::map<std::string, std::size_t>& node_index);

/// @brief Merge users with matching emails
/// @param users : The list of users to merge
/// @return Merged users
std::vector<User> MergeUsers(std::vector<User>& users);