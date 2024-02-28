#ifndef DECOMP_H
#define DECOMP_H
#include <vector>

namespace dimkashelk {
    namespace details {
        int decomp(int n, int ndim,
                   double *a, double *cond,
                   int pivot[], int *flag);
    }

    class Decomp {
    public:
        explicit Decomp(const std::vector<std::vector<double> > &matrix);

    private:
        double cond_;
        const int size_;
        double *data_;
        int *pivot_;
        int flag_;
    };
}
#endif
