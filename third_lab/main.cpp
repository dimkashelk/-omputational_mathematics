#include <iostream>
#include <iomanip>
#include <cmath>
#include "Rkf45.h"

int func(int n, double t, double *valVector, double *derivVector) {
    derivVector[0] = -71 * valVector[0] - 70 * valVector[1] + std::exp(1 - t * t);
    derivVector[1] = valVector[0] + std::sin(1 - t);
    return 0;
}

int main() {
    double data[2]{0.0, 1.0};
    dimkashelk::Rkf45::calculate(func, data, 0, 4);
    return 0;
}
