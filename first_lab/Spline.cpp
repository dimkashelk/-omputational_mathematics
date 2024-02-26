#include "Spline.h"

#include <stdexcept>

dimkashelk::Spline::Spline(const std::vector<std::pair<double, double> > &points) {
    std::vector<double> B(points.size());
    std::vector<double> C(points.size());
    std::vector<double> D(points.size());

    const size_t count_minus_1 = points.size() - 1;
    if (points.size() < 2) { throw std::logic_error("Check points"); }
    if (points.size() > 2) {
        D[0] = points[1].first - points[0].first;
        C[1] = (points[1].second - points[0].second) / D[0];
        for (size_t i = 2; i <= count_minus_1; i++) {
            D[i - 1] = points[i].first - points[i - 1].first;
            B[i - 1] = 2.0 * (D[i - 2] + D[i - 1]);
            C[i] = (points[i].second - points[i - 1].second) / D[i - 1];
            C[i - 1] = C[i] - C[i - 1];
        }
        B[0] = -D[0];
        B[points.size() - 1] = -D[points.size() - 2];
        C[0] = 0.0;
        C[points.size() - 1] = 0.0;
        if (points.size() != 3) {
            C[0] = C[2] / (points[3].first - points[1].first) - C[1] / (points[2].first - points[0].first);
            C[points.size() - 1] = C[points.size() - 2] /
                                   (points[points.size() - 1].first - points[points.size() - 3].first) -
                                   C[points.size() - 3] /
                                   (points[points.size() - 2].first - points[points.size() - 4].first);
            C[0] = C[0] * D[0] * D[0] / (points[3].first - points[0].first);
            C[points.size() - 1] = -C[points.size() - 1] * D[points.size() - 2] * D[points.size() - 2] /
                                   (points[points.size() - 1].first - points[points.size() - 4].first);
        }
        for (size_t i = 2; i <= points.size(); i++) {
            const double current = D[i - 2] / B[i - 2];
            B[i - 1] = B[i - 1] - current * D[i - 2];
            C[i - 1] = C[i - 1] - current * C[i - 2];
        }
        C[points.size() - 1] = C[points.size() - 1] / B[points.size() - 1];
        for (size_t i = 1; i <= count_minus_1; i++) {
            const size_t d = points.size() - i;
            C[d - 1] = (C[d - 1] - D[d - 1] * C[d]) / B[d - 1];
        }
        B[points.size() - 1] = (points[points.size() - 1].second - points[count_minus_1 - 1].second) /
                               D[count_minus_1 - 1] + D[count_minus_1 - 1] *
                               (C[count_minus_1 - 1] + 2. * C[points.size() - 1]);
        for (size_t i = 1; i <= count_minus_1; i++) {
            B[i - 1] = (points[i].second - points[i - 1].second) / D[i - 1] - D[i - 1] * (C[i] + 2. * C[i - 1]);
            D[i - 1] = (C[i] - C[i - 1]) / D[i - 1];
            C[i - 1] = 3.0 * C[i - 1];
        }
        C[points.size() - 1] = 3. * C[points.size() - 1];
        D[points.size() - 1] = D[points.size() - 2];
    } else {
        B[0] = (points[1].second - points[0].second) / (points[1].first - points[0].first);
        C[0] = 0.0;
        D[0] = 0.0;
        B[1] = B[0];
        C[1] = 0.0;
        D[1] = 0.0;
    }
    points_ = points;
    for (const auto &point: points) {
        a.push_back(point.second);
    }
    b = B;
    c = C;
    d = D;
}

double dimkashelk::Spline::operator()(const double number) const {
    size_t i = 1;
    size_t j = points_.size() + 1;
    do {
        const size_t k = (i + j) / 2;
        if (number < points_[k - 1].first) {
            j = k;
        }
        if (number >= points_[k - 1].first) {
            i = k;
        }
    } while (j > i + 1);
    const double DX = number - points_[i - 1].first;
    return a[i - 1] + DX * b[i - 1] + DX * DX * c[i - 1] + DX * DX * DX * d[i - 1];
}
