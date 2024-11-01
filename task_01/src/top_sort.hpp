#pragma once
#include <bits/stdc++.h>
#define int long

class CycleGraph : public std::logic_error {
    using std::logic_error::logic_error;
};

std::vector<int> TopSort(int vertices, int edges, std::vector<std::pair<int, int>>& edge);