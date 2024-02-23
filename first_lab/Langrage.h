#ifndef COMPUTATIONAL_MATHEMATICS_LANGRAGE_H
#define COMPUTATIONAL_MATHEMATICS_LANGRAGE_H

#include <vector>

namespace dimkashelk {

    class Langrage {
    public:
        Langrage(std::vector<std::pair<double, double>> &points, size_t rank);
        double operator()(double x);
    private:
        std::vector<std::pair<double, double>> points_;
        size_t rank_;
    };

}
#endif
