#ifndef RMQ_H_
#define RMQ_H_

#include <math.h>

#include <vector>

std::vector<std::vector<double>> rmq_sparse_table(std::vector<double>& data);

double get_min_from_sparse_table(std::vector<std::vector<double>>& sparse_table,
                                 int start_ind, int end_ind);

class RMQ {
public:
    RMQ(std::vector<double> data);

    double get_min(int first_ind, int last_ind);
private:
    std::vector<std::vector<double>> sparse_table;
};

#endif