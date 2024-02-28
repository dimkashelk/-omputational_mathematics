#ifndef DECOMP_H
#define DECOMP_H
#include <vector>

namespace dimkashelk {
    class Decomp {
    public:
        explicit Decomp(const std::vector<std::vector<double>> &matrix);
    private:
        double cond_;
        const int size_;
        double *data_;
        int *pivot_;
        int flag_;
    };
}
#endif
