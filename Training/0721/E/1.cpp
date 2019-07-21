#include <cstdio>
#include <cmath>
#include <algorithm>

#define y1 yyyyyy

const double eps = 1e-10, pi = std::acos(-1);
double r, d, x1, y1, d1, r1, x2, y2, d2, r2, rm, the;

double atan2_(double y, double x) {
    if (fabs(x) < eps && fabs(y) < eps) return 0;
    return std::atan2(y, x);
}

double val(double r1, double r2, double d1, double d2, double phi) {
    return 2 * std::asin(std::sqrt(r1 * r1 - 2 * r1 * r2 * std::cos(phi) + r2 * r2 + (d1 - d2) * (d1 - d2)) / (2 * r)) * r;
}

double calc(double phi) {
    return val(r1, rm, d1, d / 2, phi) + val(r2, rm, d2, d / 2, the - phi);
}

int main() {
    freopen("path.in", "r", stdin);
    freopen("path.out", "w", stdout);
    scanf("%lf%lf", &r, &d);
    rm = std::sqrt(r * r - d * d / 4);
    scanf("%lf%lf%lf", &x1, &y1, &d1);
    scanf("%lf%lf%lf", &x2, &y2, &d2);
    r1 = std::sqrt(r * r - d1 * d1);
    r2 = std::sqrt(r * r - (d2 - d) * (d2 - d));
    the = atan2_(y1, x1) - atan2_(y2, x2);
    while (the < -eps) the += 2 * pi;
    while (the >= 2 * pi - eps) the -= 2 * pi;
    if (the < eps) the = 0;
    the = std::min(the, 2 * pi - the);
    double l = 0, r = the;
    for (int i = 1; i <= 1000; i++) {
        double m1 = (l * 2 + r) / 3, m2 = (m1 + r) / 2;
        if (calc(m1) <= calc(m2)) r = m2;
        else l = m1;
    }
    printf("%.10f\n", calc(l));
    return 0;
}
