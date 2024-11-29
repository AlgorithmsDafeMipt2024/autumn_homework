#pragma once

#include <queue>
#include <string>

#include "graph.hpp"

/// @brief Vertex representing single downloadable package
class Library : public Vertex<std::string> {
 public:
  std::set<std::shared_ptr<Library>> adjacent;
};

/// @brief Graph of dependencies between libraries
/// The "parent" libraries should be installed after thier children
class DependencyGraph : public Graph<Library, std::string> {};

/// @brief Packman basic algorithm
class PackageManager {
 public:
  PackageManager() = delete;
  PackageManager(DependencyGraph& dep_graph) : dependencies_{dep_graph} {}

  /**
   * @brief
   * Finds the right order to install libraries in
   * with respect to dependencies
   * @param target Needed library
   * @return std::vector<std::string>
   */
  std::vector<std::string> FindDownloadingOrder(std::string target);

 private:
  bool IsCyclicUtil(std::shared_ptr<Library> node, std::vector<bool>& visited,
                    std::vector<bool>& recStack);
  bool IsCyclic();
  void FindingOrderStep(std::shared_ptr<Library> target);
  DependencyGraph& dependencies_;
  std::vector<bool> is_visited_;
  std::queue<std::string> order_;
};