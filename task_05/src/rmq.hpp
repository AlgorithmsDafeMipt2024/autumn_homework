#ifndef RMW_H_
#define RMW_H_

#include <math.h>

#include <vector>

std::vector<std::vector<double>> rmq_sparse_table(std::vector<double>& data);

double get_min_from_sparse_table(std::vector<std::vector<double>>& sparse_table,
                                 int start_ind, int end_ind);

#endif