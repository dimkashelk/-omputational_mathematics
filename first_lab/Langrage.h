#ifndef COMPUTATIONAL_MATHEMATICS_LANGRAGE_H
#define COMPUTATIONAL_MATHEMATICS_LANGRAGE_H

#include <vector>

namespace dimkashelk {

    class Langrage {
    public:
        explicit Langrage(const std::vector<std::pair<double, double>> &points);
        double operator()(double x) const;
    private:
        const std::vector<std::pair<double, double>> points_;
        double calculateFraction(size_t index, double x) const;
    };

}
#endif
