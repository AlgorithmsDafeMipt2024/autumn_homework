#pragma once
#include <algorithm>
#include <set>
#include <vector>

using namespace std;

void DfsCutPoint(int v, int p);
void Dfs_cit_bridges(int u, int p = -1);

set<int> Cut_point(int n, int m, const vector<vector<int>> gr);
vector<pair<int, int>> Cut_bridges(int& n, int& m,
                                   const vector<vector<int>> gr);

pair<set<int>, vector<pair<int, int>>> Answer(int n, int m,
                                              vector<pair<int, int>> vec);