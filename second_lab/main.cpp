#include <iostream>

#include "Solve.h"

std::vector<std::vector<double> > get_left_matrix(double p) {
    return {
        {p - 29, 6, -6, -4, -3, -8, -5, 5},
        {6, -13, -3, 5, 4, 3, 1, 7},
        {5, -5, -1, 7, 2, 0, 7, 1},
        {5, -5, 5, 6, 4, -7, 4, 0},
        {4, 4, 7, -4, 9, -8, -8, -4},
        {-4, 5, -4, 1, 0, 12, 0, 6},
        {-3, -2, -4, 2, -8, -3, 16, 4},
        {7, 5, 0, 2, 0, -6, 8, -12}
    };
}

std::vector<double> get_right_matrix(double p) {
    return {
        4 * p - 175,
        133,
        110,
        112,
        17,
        32,
        13,
        -18
    };
}

int main() {
    dimkashelk::Solve solve;

    const auto numbers = {1.0, 0.1, 0.01, 0.0001, 0.000001};
    for (const auto number: numbers) {
        auto left = get_left_matrix(number);
        auto right = get_right_matrix(number);
        solve(left, right);
        auto res = solve.get_result();
        std::cout << "p = " << number << ": \n";
        for (int i = 0; i < res.size(); i++) {
            std::cout << "\tx" << i << ": " << res[i] << '\n';
        }
        std::cout << "\n";
    }
    return 0;
}
