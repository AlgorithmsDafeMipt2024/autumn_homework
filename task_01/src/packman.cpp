#include "packman.hpp"

bool PackageManager::IsCyclicUtil(std::shared_ptr<Library> node,
                                  std::vector<bool>& visited,
                                  std::vector<bool>& recStack) {
  if (!visited[dependencies_.Find(node->data)]) {
    visited[dependencies_.Find(node->data)] = true;
    recStack[dependencies_.Find(node->data)] = true;

    for (auto& neighbor : node->adjacent)
      if (!visited[dependencies_.Find(neighbor->data)] &&
          IsCyclicUtil(neighbor, visited, recStack))
        return true;
      else if (recStack[dependencies_.Find(neighbor->data)])
        return true;
  }
  recStack[dependencies_.Find(node->data)] = false;
  return false;
}

bool PackageManager::IsCyclic() {
  std::vector<bool> visited(dependencies_.Size(), false);
  std::vector<bool> recStack(dependencies_.Size(), false);

  for (std::size_t i = 0; i < dependencies_.Size(); ++i)
    if (IsCyclicUtil(dependencies_[i], visited, recStack)) return true;

  return false;
}

void PackageManager::FindingOrderStep(std::shared_ptr<Library> target) {
  is_visited_[dependencies_.Find(target->data)] = true;

  for (auto& neighbor : target->adjacent)
    if (!is_visited_[dependencies_.Find(neighbor->data)])
      FindingOrderStep(neighbor);

  order_.push(target->data);
}

std::vector<std::string> PackageManager::FindDownloadingOrder(
    std::string target) {
  if (IsCyclic()) {
    std::cout << "The graph is cyclic. Downloading order is undetermined."
              << std::endl;
    return {};
  }

  std::size_t target_id = dependencies_.Find(target);
  if (target_id == dependencies_.Size()) {
    std::cout << "No such package : " << target << std::endl;
    return {};
  }

  is_visited_.resize(dependencies_.Size());
  for (size_t i = 0; i < is_visited_.size(); ++i) is_visited_[i] = false;

  FindingOrderStep(dependencies_[target_id]);

  std::vector<std::string> order;

  std::cout << "Downloading Order for " << target << " is :" << std::endl;
  while (order_.size() > 0) {
    order.push_back(order_.front());
    std::cout << order_.front() << " ";
    order_.pop();
  }
  std::cout << std::endl;
  return order;
}