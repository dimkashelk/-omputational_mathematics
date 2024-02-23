#include "Langrage.h"

namespace {
    double calculateDenominator(std::vector<std::pair<double, double> > &points, size_t index) {
        double res = 1.0;
        double x = points[index].first;
        for (size_t i = 0; i < points.size(); i++) {
            if (i != index) {
                res *= (x - points[i].first);
            }
        }
        return res;
    }

    std::vector<double> calculateCoefficients(std::vector<std::pair<double, double> > &points, size_t rank) {
        std::vector<double> coeff(rank);
    }
}

dimkashelk::Langrage::Langrage(std::vector<std::pair<double, double> > &points, size_t rank):
    points_(points),
    rank_(rank)
{}
