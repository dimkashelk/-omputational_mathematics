#include <cmath>
#include <iostream>
#include <vector>
#include <functional>
#include "Langrage.h"
#include "Quanc8.h"
#include "Spline.h"

double f(const double x) {
    return 1 / (1 + x);
}

double func(const double x, const double m) {
    return std::pow(std::abs(x - std::tan(x)), m);
}

int main() {
    std::vector<std::pair<double, double>> function;
    function.reserve(11);
    for (int i = 0; i < 11; i++) {
        function.emplace_back(0.1 * i, f(0.1 * i));
    }
    dimkashelk::Langrage langrage(function);
    dimkashelk::Spline spline(function);
    std::cout << "X   | Langrage | spline | F(x)\n";
    for (int i = 0; i < 10; i++) {
        double x = 0.05 + 0.1 * i;
        std::cout << x << " | " << langrage(x) << " | " << spline(x) << " | " << f(x) << std::endl;
    }

    std::cout << "\n\n\n";

    auto f1 = std::bind(func, std::placeholders::_1, -1);
    dimkashelk::Quanc8 func1(f1, 2, 5, 0.0001, 0.00001);
    std::cout << "Result for m = -1: " << func1.getResult() << "\n"
              << "Error: " << func1.getError() << "\n"
              << "NoFun: " << func1.getNoFun() << "\n"
              << "Flag: " << func1.getFlag() << "\n\n\n";

    auto f2 = std::bind(func, std::placeholders::_1, -0.5);
    dimkashelk::Quanc8 func2(f2, 2, 5, 0.00001, 0.00001);
    std::cout << "Result for m = -0.5: " << func2.getResult() << "\n"
              << "Error: " << func2.getError() << "\n"
              << "NoFun: " << func2.getNoFun() << "\n"
              << "Flag: " << func2.getFlag() << "\n";
    return 0;
}
