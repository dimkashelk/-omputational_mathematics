#ifndef DECOMP_H
#define DECOMP_H
#include <vector>

namespace dimkashelk {
    class Decomp {
    public:
        explicit Decomp(const std::vector<std::vector<double>> &matrix);
    private:
        std::vector<std::vector<double>> matrix_;
        double cond_;

    };
}
#endif
