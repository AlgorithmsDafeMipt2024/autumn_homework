#include "packman.hpp"

void PackageManager::FindingOrderStep(std::shared_ptr<Library> target) {
  is_visited_[dependencies_.Find(target->data)] = true;

  for (auto& neighbor : target->adjacent)
    if (!is_visited_[dependencies_.Find(neighbor->data)])
      FindingOrderStep(neighbor);

  order_.push(target->data);
}

std::vector<std::string> PackageManager::FindDownloadingOrder(
    std::string target) {
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