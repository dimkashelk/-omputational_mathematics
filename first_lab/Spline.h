#ifndef SPLINE_H
#define SPLINE_H

#include <vector>

namespace dimkashelk {
    class Spline {
    public:
        explicit Spline(const std::vector<std::pair<double, double> > &points);

        double operator()(double number) const;

    private:
        std::vector<std::pair<double, double>> points_;
        std::vector<double> a;
        std::vector<double> b;
        std::vector<double> c;
        std::vector<double> d;
    };
}
#endif
