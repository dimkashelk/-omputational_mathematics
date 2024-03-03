#include <iostream>
#include <iomanip>
#include <cmath>
#include "Rkf45.h"

int func(int n, double t, double *value, double *res) {
    res[0] = -71 * value[0] - 70 * value[1] + std::exp(1 - t * t);
    res[1] = value[0] + std::sin(1 - t);
    return 0;
}

int main() {
    double data[2]{0.0, 1.0};
    dimkashelk::Rkf45::calculate(func, data, 0, 4);
    return 0;
}
