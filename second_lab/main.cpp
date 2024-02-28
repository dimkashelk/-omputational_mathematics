#include <iostream>

#include "Solve.h"

void gaussian_elimination(std::vector<std::vector<double> > &matrix) {
    const int n = static_cast<int>(matrix.size());
    for (int i = 0; i < n; ++i) {
        int maxRow = i;
        for (int k = i + 1; k < n; ++k) {
            if (std::abs(matrix[k][i]) > std::abs(matrix[maxRow][i])) {
                maxRow = k;
            }
        }
        if (maxRow != i) {
            std::swap(matrix[i], matrix[maxRow]);
        }

        for (int k = i + 1; k < n; ++k) {
            const double factor = matrix[k][i] / matrix[i][i];
            for (int j = i; j < n + 1; ++j) {
                matrix[k][j] -= factor * matrix[i][j];
            }
        }
    }

    for (int i = n - 1; i >= 0; --i) {
        for (int j = i + 1; j < n; ++j) {
            matrix[i][n] -= matrix[i][j] * matrix[j][n];
        }
        matrix[i][n] /= matrix[i][i];
    }
}

std::vector<std::vector<double> > multiply_matrices(const std::vector<std::vector<double> > &matrix1,
                                                    const std::vector<std::vector<double> > &matrix2) {
    const int rows1 = static_cast<int>(matrix1.size());
    const int cols1 = static_cast<int>(matrix1[0].size());
    const int cols2 = static_cast<int>(matrix2[0].size());

    std::vector result(rows1, std::vector(cols2, 0.0));

    for (int i = 0; i < rows1; ++i) {
        for (int j = 0; j < cols2; ++j) {
            for (int k = 0; k < cols1; ++k) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    return result;
}

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
