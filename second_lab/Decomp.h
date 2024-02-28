#ifndef DECOMP_H
#define DECOMP_H
#include <vector>

namespace dimkashelk {
    namespace details {
        int decomp(int n, int ndim,
                   double *a, double *cond,
                   int pivot[], int *flag);
    }

    class Solve;

    class Decomp {
        friend class Solve;

    public:
        Decomp();

        void operator()(const std::vector<std::vector<double> > &matrix);

        ~Decomp();

    private:
        double cond_;
        int size_;
        double *data_;
        int *pivot_;
        int flag_;
    };
}
#endif
