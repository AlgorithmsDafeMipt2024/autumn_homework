#include "util.hpp"

#include <algorithm>

namespace utils {

int Max(const std::list<int>& l) {
  return *std::max_element(l.begin(), l.end());
}

}  // namespace utils