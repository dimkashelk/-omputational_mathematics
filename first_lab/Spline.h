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
        std::vector<double> a_;
        std::vector<double> b_;
        std::vector<double> c_;
        std::vector<double> d_;
    };
}
#endif
