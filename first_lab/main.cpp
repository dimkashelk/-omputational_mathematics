#include <iostream>
#include <vector>
#include "Langrage.h"

double f(const double x) {
    return 1 / (1 + x);
}

int main() {
    std::vector<std::pair<double, double>> function;
    function.reserve(11);
    for (int i = 0; i < 11; i++) {
        function.emplace_back(0.1 * i, f(0.1 * i));
    }
    dimkashelk::Langrage langrage(function);
    std::cout << "X   | Langrage | F(x)\n";
    for (int i = 0; i < 10; i++) {
        double x = 0.05 + 0.1 * i;
        std::cout << x << " " << langrage(x) << " " << f(x) << std::endl;
    }
    return 0;
}
