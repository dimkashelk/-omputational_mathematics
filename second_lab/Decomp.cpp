#include "Decomp.h"

#include <cmath>

namespace {
    void calculate(std::vector<std::vector<double> > &matrix_, double &cond_) {
        int N = static_cast<int>(matrix_.size());
        std::vector<int> IPVT(matrix_.size());
        std::vector<double> WORK(matrix_.size());

        double EK = 0.0,
                T = 0.0,
                ANORM = 0.0,
                YNORM = 0.0,
                ZNORM = 0.0;

        IPVT[N - 1] = 1;
        if (N == 1) {
            cond_ = 1.0;
            if (matrix_[0][0] != 0.0) {
                return;
            }
            cond_ = 1.0E+32;
            return;
        }
        N -= 1;

        ANORM = 0.0;
        for (int j = 1; j <= N; j++) {
            T = 0.0;
            for (int i = 1; i <= N; i++) {
                T = T + std::abs(matrix_[i - 1][j - 1]);
            }
            if (T > ANORM) {
                ANORM = T;
            }
        }

        for (int k = 1; k <= N; k++) {
            const int KP1 = k + 1;

            int m = k;
            for (int i = KP1; i <= N; i++) {
                if (std::abs(matrix_[i - 1][k - 1]) > std::abs(matrix_[m - 1][k - 1])) {
                    m = i;
                }
            }
            IPVT[k - 1] = m;
            if (m != k) {
                IPVT[N - 1] = -IPVT[N - 1];
            }
            T = matrix_[m - 1][k - 1];
            matrix_[m - 1][k - 1] = matrix_[k - 1][k - 1];
            matrix_[k - 1][k - 1] = T;

            if (T == 0.0) {
                continue;
            }

            for (int i = KP1; i <= N; i++) {
                matrix_[i - 1][k - 1] = -matrix_[i - 1][k - 1] / T;
            }

            for (int j = KP1; j <= N; j++) {
                T = matrix_[m - 1][j - 1];
                matrix_[m - 1][j - 1] = matrix_[k - 1][j - 1];
                matrix_[k - 1][j - 1] = T;
                if (T == 0.0) {
                    continue;
                }
                for (int i = KP1; i <= N; i++) {
                    matrix_[i - 1][j - 1] = matrix_[i - 1][j - 1] + matrix_[i - 1][k - 1] * T;
                }
            }
        }

        for (int k = 1; k <= N; k++) {
            T = 0.0;
            if (k != 1) {
                int KM1 = k - 1;
                for (int i = 1; i <= KM1; i++) {
                    T = T + matrix_[i - 1][k - 1] * WORK[i - 1];
                }
            }
            EK = 1.0;
            if (T < 0.0) {
                EK = -1.0;
            }
            if (matrix_[k - 1][k - 1] == 0.0) {
                cond_ = 1.0E+32;
                return;
            }
            WORK[k - 1] = -(EK + T) / matrix_[k - 1][k - 1];
        }
        for (int c = 1; c <= N; c++) {
            const int k = N - c;
            T = WORK[k - 1];
            const int KP1 = k + 1;
            for (int i = KP1; i <= N; i++) {
                T = T + matrix_[i - 1][k - 1] * WORK[i - 1];
            }
            WORK[k - 1] = T;
            const int m = IPVT[k - 1];
            if (m == k) {
                continue;
            }
            T = WORK[m - 1];
            WORK[m - 1] = WORK[k - 1];
            WORK[k - 1] = T;
        }

        YNORM = 0.0;
        for (int i = 1; i <= N; i++) {
            YNORM = YNORM + std::abs(WORK[i - 1]);
        }

        //     PE��T� C�CTEM� matrix_*Z=Y

        Solve(WORK);

        ZNORM = 0.0;
        for (int i = 1; i <= N; i++) {
            ZNORM = ZNORM + std::abs(WORK[i - 1]);
        }

        cond_ = ANORM * ZNORM / YNORM;
        if (cond_ < 1.0) {
            cond_ = 1.0;
        }
    }
}

dimkashelk::Decomp::Decomp(const std::vector<std::vector<double> > &matrix): matrix_(matrix),
                                                                             cond_(0.0) {
    calculate(matrix_, cond_);
}
