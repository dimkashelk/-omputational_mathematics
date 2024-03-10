#include <iostream>
#include <cmath>
#include <functional>
#include "../common/Quanc8.h"
#include "../common/Rkf45.h"
#include "zeroin.h"

double integrand(double y, double alpha) {
    return 1.0 / sqrt(2 * (alpha + pow(y, 3) / 3 - y));
}

int diff_func(int n,  double t, double *x, double *dx) {
    dx[0] = x[1];
    dx[1] = x[0] * x[0] - 1;
    return 0;
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
    double a = 2.0 / 3 + 0.000001, b = 300;
    double alpha = find_alpha(a, b);
    std::cout << "a = " << a << ", b = " << b << "\nFind alpha: " << alpha << "\nSolve value = " << to_solve(alpha) << "\n\n";

    std::cout << "RKF for diff system:\n";
    double data[2]{0.0, std::sqrt(2 * alpha)};
    dimkashelk::Rkf45::calculate(diff_func, data, 0, 1);

    std::cout << "\n\nPlay with alpha: \n";
    for (double i = 0.97; i < 1.04; i += 0.01) {
        double new_alpha = alpha * i;
        std::cout << (i - 1) * 100 << "%, alpha = " << new_alpha << "\n";
        std::cout << "RKF for diff system:\n";
        data[0] = 0.0;
        data[1] = std::sqrt(2 * new_alpha);
        dimkashelk::Rkf45::calculate(diff_func, data, 0, 1);
    }
    return 0;
}
