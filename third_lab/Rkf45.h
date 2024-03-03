#ifndef RKF45_H
#define RKF45_H
#include <vector>

namespace dimkashelk {
    class Rkf45 {
    public:
        explicit Rkf45(int count);
    private:
        std::vector<double> *F1, *F2, *F3, *F4, *F5, *SAVRE, *SAVAE;
        int *KOP, *INIT, *JFLAG, *KFLAG;
    };
}

#endif
