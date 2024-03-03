#include "Rkf45.h"
#include "rkf.h"
#include <cmath>
#include <iostream>

void dimkashelk::Rkf45::calculate(int (*F)(int n, double t, double y[], double yp[]),
                                  double valueArray[],
                                  double t, double tout) {
    int flag = 0;
    int NEQN = 2;
    rkfinit(NEQN, &flag);
    double dop[2]{0.0, 0.0};
    flag = 1;
    double ABS = 0.0001, REL = 0.0001;
    double H[NEQN];
    double STEP = 0.2;
    int NFE = 0;
    int MAXNFE = 100000;
    while (t <= tout) {
        std::cout << t << " " << valueArray[0] << " " << valueArray[1] << "\n";
        rkf45(F, NEQN, valueArray, dop, &t, t + STEP, &REL, ABS, H, &NFE, MAXNFE, &flag);
    }
    std::cout << t << " " << valueArray[0] << " " << valueArray[1] << "\n";
    rkfend();
}
