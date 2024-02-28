#ifndef SOLVE_H
#define SOLVE_H
#include <vector>

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

        void operator()(const std::vector<std::vector<double> > &matrix_left, const std::vector<double> &matrix_right);

        [[nodiscard]] std::vector<double> get_result() const;
        [[nodiscard]] double get_cond() const;

        ~Solve();

    private:
        int size_;
        double *data_right_;
        double cond_;

        void free() const;
    };
}

#endif
