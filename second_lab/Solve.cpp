#include "Solve.h"

#include <stdexcept>

#include "Decomp.h"

int dimkashelk::details::solve(int n, int ndim,
                               double *a, double b[],
                               int pivot[])

/* Purpose :
   -------
   Solution of linear system, a * x = b.
   Do not use if decomp() has detected singularity.

   Input..
   -----
   n     = order of matrix
   ndim  = row dimension of a
   a     = triangularized matrix obtained from decomp()
   b     = right hand side vector
   pivot = pivot vector obtained from decomp()

   Output..
   ------
   b = solution vector, x

*/

{
    /* --- begin function solve() --- */

    int i, j, k, m;
    double t;

    if (n == 1) {
        /* trivial */
        b[0] /= a[0];
    } else {
        /* Forward elimination: apply multipliers. */
        for (k = 0; k < n - 1; k++) {
            m = pivot[k];
            t = b[m];
            b[m] = b[k];
            b[k] = t;
            for (i = k + 1; i < n; ++i) b[i] += a[(i * ndim + k)] * t;
        }

        /* Back substitution. */
        for (k = n - 1; k >= 0; --k) {
            t = b[k];
            for (j = k + 1; j < n; ++j) t -= a[(k * ndim + j)] * b[j];
            b[k] = t / a[(k * ndim + k)];
        }
    }

    return (0);
} /* --- end function solve() --- */

dimkashelk::Solve::Solve(): size_(0),
                            data_right_(nullptr),
                            cond_(0.0) {
}

void dimkashelk::Solve::operator()(const std::vector<std::vector<double> > &matrix_left,
                                   const std::vector<double> &matrix_right) {
    if (matrix_left.size() != matrix_right.size()) {
        throw std::logic_error("Check data");
    }
    free();

    size_ = static_cast<int>(matrix_right.size());
    data_right_ = new double[size_];
    for (int i = 0; i < size_; i++) {
        data_right_[i] = matrix_right[i];
    }
    Decomp dec;
    dec(matrix_left);
    cond_ = dec.cond_;
    const int size = static_cast<int>(matrix_left.size());
    details::solve(size, size, dec.data_, data_right_, dec.pivot_);
}

std::vector<double> dimkashelk::Solve::get_result() const {
    std::vector<double> res(size_);
    for (int i = 0; i < size_; i++) {
        res[i] = data_right_[i];
    }
    return res;
}

double dimkashelk::Solve::get_cond() const {
    return cond_;
}

dimkashelk::Solve::~Solve() {
    free();
}

void dimkashelk::Solve::free() const {
    if (data_right_ != nullptr) {
        delete[] data_right_;
    }
}
