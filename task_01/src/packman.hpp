#include <stack>
#include <string>

#include "graph.hpp"

/// @brief Graph of dependencies between libraries
/// The "parent" libraries should be installed before thier children
class DependencyGraph : public Graph<std::string> {};

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
  std::vector<std::string> FindDownloadingOrder(/*
      std::shared_ptr<Vertex<std::string>> target*/);

 private:
  void FindingOrderStep(std::shared_ptr<Vertex<std::string>> target);
  DependencyGraph& dependencies_;
  std::vector<bool> is_visited_;
  std::stack<std::string> reverse_order_;
};