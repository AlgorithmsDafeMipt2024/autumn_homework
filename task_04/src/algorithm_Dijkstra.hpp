#pragma once
#include <bits/stdc++.h>

using namespace std;

class Nonexistent_way : public std::logic_error {
  using std::logic_error::logic_error;
};

pair<pair<int, int>, vector<int>> Dijkstra(int& n, int& m, int& s, int& t,
                                           vector<vector<int>>& vec);