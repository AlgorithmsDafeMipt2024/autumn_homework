#pragma once

#include <vector>

int partition(std::vector<int>& vec, int low, int high);
void quickSort(std::vector<int>& vec, int low, int high);

void bubbleSort(std::vector<int>& vec);

bool in(const std::vector<int>& vec, int value);

int sum(const std::vector<int>& vec);
