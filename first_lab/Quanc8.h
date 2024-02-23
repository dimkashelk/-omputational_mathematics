#ifndef QUANC8_H
#define QUANC8_H
#include <functional>

namespace dimkashelk {
    class Quanc8 {
    public:
        Quanc8(std::function<double (double)> &fun, double a, double b, double abs_err, double rel_err);
        double getResult() const;
        double getError() const;
        int getNoFun() const;
        double getFlag() const;
    private:
        std::function<double (double)> fun_{};
        const double a_;
        const double b_;
        const double abs_err_;
        const double rel_err_;
        double result_;
        double error_;
        int no_fun_;
        double flag_;
    };
}
#endif
