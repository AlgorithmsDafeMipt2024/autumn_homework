#include "utils.hpp"

int RecoverForest(const std::vector<std::vector<int>>& grid,
                  std::vector<std::pair<int, int>>& unrecovered) {
  // Number of rows and columns in the grid
  int n = grid.size();
  int m = grid[0].size();

  // Steps for rows & columns (up, right, down, left)
  std::vector<int> row_steps = {-1, 0, 1, 0};
  std::vector<int> col_steps = {0, 1, 0, -1};

  // Visited matrix
  std::vector<std::vector<bool>> visited(n, std::vector<bool>(m, false));

  // Queue for BFS
  std::queue<std::pair<std::pair<int, int>, int>> q;

  // Counter of all partially burnt chunks
  int part_burnt_count = 0;

  // Push all salvaged chunks into the queue
  // & count all partially burnt chunks
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      if (grid[i][j] == 2) {
        q.push({{i, j}, 0});
        visited[i][j] = true;
      } else if (grid[i][j] == 1)
        part_burnt_count++;

  // BFS
  int recovered_count = 0, time = 0;
  while (!q.empty()) {
    int row = q.front().first.first;
    int col = q.front().first.second;
    int chunk_time = q.front().second;
    q.pop();

    // Update time
    time = time < chunk_time ? chunk_time : time;

    // Try steping in all 4 directions
    for (int i = 0; i < 4; i++) {
      int nrow = row + row_steps[i];
      int ncol = col + col_steps[i];

      if (nrow >= 0 && nrow < n && ncol >= 0 && ncol < m &&
          grid[nrow][ncol] == 1 && !visited[nrow][ncol]) {
        visited[nrow][ncol] = true;
        q.push({{nrow, ncol}, time + 1});
        recovered_count++;
      }
    }
  }

  // Find and store unrecovered chunks
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      if (grid[i][j] == 1 && !visited[i][j]) unrecovered.push_back({i, j});

  // Return time
  return (recovered_count == part_burnt_count) ? time : -1;
}