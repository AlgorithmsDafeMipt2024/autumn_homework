#include <string>

#include "graph.hpp"

struct Library : public Vertex<std::string> {
  Library(const std::string& name) : Vertex<std::string>(name) {}
};

class DependencyGraph : public Graph<std::string> {};

class PackageManager {
 public:
  PackageManager(std::shared_ptr<DependencyGraph> dep_graph)
      : dependencies{dep_graph} {}

  std::vector<std::string> FindDownloadingOrder(
      std::shared_ptr<Library> target);

 private:
  std::shared_ptr<DependencyGraph> dependencies;
};