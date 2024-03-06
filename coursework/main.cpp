#include <iostream>
#include <cmath>
#include <functional>
#include "../common/Quanc8.h"
#include "zeroin.h"

double integrand(double y, double alpha) {
    return 1.0 / sqrt(2 * (alpha + pow(y, 3) / 3 - y));
}

double to_solve(double alpha) {
    double a = 0, b = 1;
    double abserr = 1e-6, relerr = 1e-6;
    auto func = std::bind(integrand, std::placeholders::_1, alpha);
    dimkashelk::Quanc8 quanc8(func, a, b, abserr, relerr);
    return 1 - quanc8.getResult();
}

double find_alpha(double a, double b) {
    double tol = 1e-12;
    int flag = 0;
    double res = zeroin(a, b, to_solve, tol, &flag);
    return res;
}

int main() {
    double a = 2.0/3+0.000001, b = 300;
    double alpha = find_alpha(a, b);
    std::cout << "a = " << a << ", b = " << b << "\nFind alpha: " << alpha << "\nSolve value = " << to_solve(alpha) << "\n\n";
    return 0;
}
