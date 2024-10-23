#include "util.h"

int partition(std::vector<int>& vec, int low, int high)
{
    int pivot = vec[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (vec[j] <= pivot) {
            i++;
            std::swap(vec[i], vec[j]);
        }
    }
    std::swap(vec[i + 1], vec[high]);
    return (i + 1);
}

void quickSort(std::vector<int>& vec, int low, int high)
{
    if (low < high) {
        int pi = partition(vec, low, high);
        quickSort(vec, low, pi - 1);
        quickSort(vec, pi + 1, high);
    }
}

void bubbleSort(std::vector<int>& vec) {
    int n = vec.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (vec[j] > vec[j + 1])
                std::swap(vec[j], vec[j + 1]);
        }
    }
}

bool in(const std::vector<int>& vec, int value)
{
    for (int i = 0; i < vec.size(); ++i)
        if (vec[i] == value)
            return true;
    return false;
}

int sum(const std::vector<int>& vec)
{
    int result = 0;
    for (auto value : vec)
        result += value;
    return result;
}