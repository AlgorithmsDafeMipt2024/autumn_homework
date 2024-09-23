#include "packman.hpp"

void PackageManager::FindingOrderStep(
    std::shared_ptr<Vertex<std::string>> target) {
  is_visited_[dependencies_.Find(target)] = true;
  reverse_order_.push(target->data);
  for (auto& neighbor : target->adjacent) {
    if (!is_visited_[dependencies_.Find(neighbor)]) {
      FindingOrderStep(neighbor);
    }
  }
}

std::vector<std::string> PackageManager::FindDownloadingOrder(
    std::shared_ptr<Vertex<std::string>> target) {
  is_visited_.resize(dependencies_.Size());
  for (size_t i = 0; i < is_visited_.size(); ++i) is_visited_[i] = false;

  FindingOrderStep(target);

  std::vector<std::string> order;

  std::cout << "Downloading Order is:" << std::endl;
  while (reverse_order_.size() > 0) {
    order.push_back(reverse_order_.top());
    std::cout << reverse_order_.top() << " ";
    reverse_order_.pop();
  }
  std::cout << std::endl;
  return order;
}