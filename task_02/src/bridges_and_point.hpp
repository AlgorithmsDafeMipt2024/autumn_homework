#pragma once
#include <bits/stdc++.h>
using namespace std;

void dfs(int v, int p);

set<int> cut_point(int& n, int& m, vector<pair<int, int>>& vec);