#include "Langrage.h"

#include <stdexcept>
#include <cstddef>

dimkashelk::Langrage::Langrage(const std::vector<std::pair<double, double> > &points):
    points_(points)
{}

double dimkashelk::Langrage::operator()(const double x) const {
    double res = 0.0;
    for (size_t i = 0; i < points_.size(); i++) {
        res += calculateFraction(i, x) * points_[i].second;
    }
    return res;
}

double dimkashelk::Langrage::calculateFraction(const std::size_t index, const double x) const {
    double res = 1.0;
    double x_cur = points_[index].first;
    for (size_t i = 0; i < points_.size(); i++) {
        if (i != index) {
            res *= (x - points_[i].first) / (x_cur - points_[i].first);
        }
    }
    return res;
}
