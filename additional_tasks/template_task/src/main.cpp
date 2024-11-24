#include "utils.hpp"

void PrintResult(int result,
                 const std::vector<std::pair<int, int>>& unrecovered) {
  std::cout << "Time: " << result << std::endl;
  if (result == -1) {
    std::cout << "Unrecovered chunks at indices:" << std::endl;
    for (const auto& p : unrecovered)
      std::cout << "(" << p.first << ", " << p.second << ") ";
    std::cout << std::endl;
  }
}

int main() {
  std::vector<std::vector<int>> forest_1 = {{2, 1, 0}, {1, 1, 1}, {0, 1, 2}};
  std::vector<std::pair<int, int>> unrecovered_1;
  int result_1 = RecoverForest(forest_1, unrecovered_1);
  PrintResult(result_1, unrecovered_1);

  std::vector<std::vector<int>> forest_2 = {{2, 0, 0}, {0, 1, 0}, {0, 0, 0}};
  std::vector<std::pair<int, int>> unrecovered_2;
  int result_2 = RecoverForest(forest_2, unrecovered_2);
  PrintResult(result_2, unrecovered_2);

  std::vector<std::vector<int>> forest_3 = {{2, 1, 2}, {1, 0, 1}};
  std::vector<std::pair<int, int>> unrecovered_3;
  int result_3 = RecoverForest(forest_3, unrecovered_3);
  PrintResult(result_3, unrecovered_3);

  return 0;
}