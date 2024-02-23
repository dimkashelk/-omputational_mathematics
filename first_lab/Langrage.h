#ifndef COMPUTATIONAL_MATHEMATICS_LANGRAGE_H
#define COMPUTATIONAL_MATHEMATICS_LANGRAGE_H

#include <vector>

namespace dimkashelk {

    class Langrage {
    public:
        Langrage(std::vector<std::pair<double, double>> &points, size_t rank);
        double getValueFunc(double x);
    private:
        std::vector<std::pair<double, double>> points_;
        std::vector<double> coeff_;
    };

}
#endif
