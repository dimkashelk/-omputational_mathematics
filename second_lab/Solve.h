#ifndef SOLVE_H
#define SOLVE_H
#define AINDEX(i,j) (i * ndim + j)
#include <vector>

namespace dimkashelk {
    namespace details {
        int solve(int n, int ndim,
              double *a, double b[],
              int pivot[]);
    }
    class Solve {
    public:
        Solve(std::vector<std::vector<double>> &matrix_left, std::vector<double> &matrix_right);
    private:
        int size_left_;
        int size_right_;
        double *data_;
        int *pivot_;
    };
}

#endif
