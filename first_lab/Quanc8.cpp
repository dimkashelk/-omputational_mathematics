#include "Quanc8.h"

#include <algorithm>

dimkashelk::Quanc8::Quanc8(std::function<double(double)> &fun, double a, double b, double abs_err,
                           double rel_err): fun_(fun),
                                            a_(a),
                                            b_(b),
                                            abs_err_(abs_err),
                                            rel_err_(rel_err),
                                            result_(0.0),
                                            error_(0.0),
                                            no_fun_(0),
                                            flag_(0.0) {
    double W0 = 3956.0 / 14175.0,
            W1 = 23552.0 / 14175.0,
            W2 = -3712.0 / 14175.0,
            W3 = 41984.0 / 14175.0,
            W4 = -18160.0 / 14175.0,
            COR11 = 0.0,
            AREA = 0.0,
            F0 = fun_(a_),
            STONE = (b_ - a_) / 16.0, STEP;
    double QPREV = 0.0, QNOW, QDIFF, QLEFT, ESTERR, TOLERR;
    double QRIGHT[31], F[16], X[16], FSAVE[8][30], XSAVE[8][30];

    int LEVMIN = 1,
            LEVMAX = 30,
            LEVOUT = 6,
            NOMAX = 5000,
            NOFIN = NOMAX - 8 * (LEVMAX - LEVOUT + (1 << (LEVOUT + 1))),
            LEV = 0,
            NIM = 1;

    if (a_ >= b_) {
        return;
    }

    X[15] = b_;
    X[7] = (a + X[15]) / 2.0;
    X[3] = (a + X[7]) / 2.0;
    X[11] = (X[7] + X[15]) / 2.0;
    X[1] = (a + X[3]) / 2.0;
    X[5] = (X[3] + X[7]) / 2.0;
    X[9] = (X[7] + X[11]) / 2.0;
    X[13] = (X[11] + X[15]) / 2.0;
    for (int j = 2; j <= 16; j += 2) {
        F[j - 1] = fun_(X[j - 1]);
    }
    no_fun_ = 9;

_30:;
    X[0] = (a + X[1]) / 2.0;
    F[0] = fun_(X[0]);
    for (int j = 3; j <= 15; j += 2) {
        X[j - 1] = (X[j - 2] + X[j]) / 2.0;
        F[j - 1] = fun_(X[j - 1]);
    }
    no_fun_ = no_fun_ + 8;
    STEP = (X[15] - a) / 16.0;
    QLEFT = (W0 * (F0 + F[7]) + W1 * (F[0] + F[6]) + W2 * (F[1] + F[5]) + W3 * (F[2] + F[4]) + W4 * F[3]) * STEP;
    QRIGHT[LEV] = (W0 * (F[7] + F[15]) + W1 * (F[8] + F[14]) + W2 * (F[9] + F[13]) + W3 * (F[10] + F[12]) + W4 * F[11])
                  * STEP;
    QNOW = QLEFT + QRIGHT[LEV];
    QDIFF = QNOW - QPREV;
    AREA = AREA + QDIFF;

    ESTERR = std::abs(QDIFF) / 1023.0;
    TOLERR = std::max(abs_err_, error_ * std::abs(AREA)) * (STEP / STONE);
    if (LEV < LEVMIN) {
        NIM = 2 * NIM;
        LEV = LEV + 1;
        for (int i = 1; i <= 8; i++) {
            FSAVE[i - 1][LEV - 1] = F[i + 7];
            XSAVE[i - 1][LEV - 1] = X[i + 7];
        }
        QPREV = QLEFT;
        for (int i = 1; i <= 8; i++) {
            int j = -i;
            F[2 * j + 17] = F[j + 8];
            X[2 * j + 17] = X[j + 8];
        }
        goto _30;
    }
    if (LEV >= LEVMAX) {
        flag_ = flag_ + 1.0;
        result_ = result_ + QNOW;
        error_ = error_ + ESTERR;
        COR11 = COR11 + QDIFF / 1023.0;
    _72:;
        if (NIM == 2 * (NIM / 2)) {
            NIM = NIM + 1;
            if (LEV <= 0)goto _80;
            QPREV = QRIGHT[LEV - 1];
            a = X[15];
            F0 = F[15];
            for (int i = 1; i <= 8; i++) {
                F[2 * i - 1] = FSAVE[i - 1][LEV - 1];
                X[2 * i - 1] = XSAVE[i - 1][LEV - 1];
            }
            goto _30;
        }
        NIM = NIM / 2;
        LEV = LEV - 1;
        goto _72;
    }
    if (no_fun_ > NOFIN) {
        NOFIN = 2 * NOFIN;
        LEVMAX = LEVOUT;
        flag_ = flag_ + (b_ - a) / (b_ - a_);
        result_ = result_ + QNOW;
        error_ = error_ + ESTERR;
        COR11 = COR11 + QDIFF / 1023.0;
        if (NIM == 2 * (NIM / 2)) {
            NIM = NIM + 1;
            if (LEV <= 0)goto _80;
            QPREV = QRIGHT[LEV - 1];
            a = X[15];
            F0 = F[15];
            for (int i = 1; i <= 8; i++) {
                F[2 * i - 1] = FSAVE[i - 1][LEV - 1];
                X[2 * i - 1] = XSAVE[i - 1][LEV - 1];
            }
            goto _30;
        }
        NIM = NIM / 2;
        LEV = LEV - 1;
        goto _72;
    }
    if (ESTERR <= TOLERR) {
        result_ = result_ + QNOW;
        error_ = error_ + ESTERR;
        COR11 = COR11 + QDIFF / 1023.0;
        if (NIM == 2 * (NIM / 2)) {
            NIM = NIM + 1;
            if (LEV <= 0) {
                result_ = result_ + COR11;
                if (error_ == 0.0) {
                    return;
                }
            }
            QPREV = QRIGHT[LEV - 1];
            a = X[15];
            F0 = F[15];
            for (int i = 1; i <= 8; i++) {
                F[2 * i - 1] = FSAVE[i - 1][LEV - 1];
                X[2 * i - 1] = XSAVE[i - 1][LEV - 1];
            }
            goto _30;
        }
        NIM = NIM / 2;
        LEV = LEV - 1;
        goto _72;
    }

_80:;
    result_ = result_ + COR11;
    if (error_ == 0.0) {
        return;
    }

_82:;
    double temp = std::abs(result_) + error_;
    if (temp != std::abs(result_))return; //?
    error_ = 2.0 * error_;
    goto _82;
}
