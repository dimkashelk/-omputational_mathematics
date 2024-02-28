#include "Decomp.h"

#include <stdexcept>

#include "cmath.h"

dimkashelk::Decomp::Decomp(const std::vector<std::vector<double> > &matrix): cond_(0.0),
                                                                             size_(static_cast<int>(matrix.size())),
                                                                             data_(nullptr),
                                                                             pivot_(nullptr),
                                                                             flag_(0) {
    if (matrix.empty()) {
        throw std::logic_error("Check matrix");
    }
    if (matrix.size() != matrix[0].size()) {
        throw std::logic_error("Check size of matrix");
    }
    data_ = new double[matrix.size() * matrix[0].size()];
    try {
        pivot_ = new int[matrix.size()];
    } catch (...) {
        delete[] data_;
        throw;
    }
    int ind = 0;
    for (auto &i: matrix) {
        for (int j = 0; j < matrix[0].size(); j++, ind++) {
            data_[ind] = i[j];
        }
    }
    decomp(size_, size_, data_, std::addressof(cond_), pivot_, std::addressof(flag_));
}
