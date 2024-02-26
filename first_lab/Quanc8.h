#ifndef QUANC8_H
#define QUANC8_H
#include <functional>

namespace dimkashelk {
    class Quanc8 {
    public:
        /**
         * \brief 
         * \param fun user functions with one double argument
         * \param a lower bound of integration
         * \param b upper bound of integration
         * \param abs_err absolute error
         * \param rel_err intermediate error
         */
        Quanc8(const std::function<double (double)> &fun, double a, double b, double abs_err, double rel_err);
        double getResult() const;
        double getError() const;
        int getNoFun() const;
        double getFlag() const;
    private:
        std::function<double (double)> fun_;
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
