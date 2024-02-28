#ifndef SOLVE_H
#define SOLVE_H
#include <vector>
#include "Decomp.h"

namespace dimkashelk {
    namespace details {
        int solve(int n, int ndim,
                  double *a, double b[],
                  int pivot[]);
    }

    class Decomp;

    class Solve {
        friend class Decomp;

    public:
        Solve();

        void operator()(const std::vector<std::vector<double> > &matrix_left, std::vector<double> &matrix_right);

        ~Solve();

    private:
        double *data_right_;

        void free() const;
    };
}

#endif
