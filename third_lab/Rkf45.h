#ifndef RKF45_H
#define RKF45_H

namespace dimkashelk {
    class Rkf45 {
    public:
        static void calculate(int (*F)(int n, double t, double y[], double yp[]),
                              double Y[],
                              double T,
                              double TOUT);
    };
}
#endif
