#pragma once

#include <vector>
#include <algorithm>
#include <set>

void weak_vertex(std::vector<std::vector<int>>& data, std::vector<bool>& visited, std::vector<int>& time_in, std::vector<int>& min_time_in,
                      std::vector<int>& cut_verts, int time, int v, int p = -1) {
  visited[v] = true;
  time_in[v] = min_time_in[v] = time++;
  int count = 0;
  for (int i = 0; i < data[v].size(); ++i) {
    if (data[v][i] == p) {
      continue;
    }
    if (visited[data[v][i] ]) {
      min_time_in[v] = std::min(min_time_in[v], time_in[data[v][i] ]);
    } else {
      weak_vertex(data, visited, time_in, min_time_in, cut_verts, time, data[v][i] , v);
      count++;
      min_time_in[v] = std::min(min_time_in[v], min_time_in[data[v][i] ]);
      if (min_time_in[data[v][i] ] >= time_in[v] && p != -1){
        cut_verts.push_back(v);
      }
    }
  }

  if (p == -1 && count >= 2) {
    cut_verts.push_back(v);
  }
}

std::vector<int> cutting_vertex(std::vector<std::vector<int>>& data) {
  int const time = 0;
  std::vector<int> time_in(data.size(), -1);
  std::vector<int> min_time_in(data.size(), -1);
  std::vector<int> cut_verts;
  std::vector<bool> visited(data.size(), false);
  for (int i = 1; i < data.size(); ++i)
    if (!visited[i]){
      weak_vertex(data, visited, time_in, min_time_in, cut_verts, time, i);
    }
  std::set<int> unique_elements(cut_verts.begin(), cut_verts.end());
  cut_verts.assign(unique_elements.begin(), unique_elements.end());
  return cut_verts;
}