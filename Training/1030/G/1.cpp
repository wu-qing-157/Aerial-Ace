#include <cmath>
#include <cstdio>
#include <algorithm>

const double pi = std::acos(-1);

double s(double x, double h) {
    x *= h / 2;
    return 2 * std::sqrt(2 * x - x * x);
}

double v(double x, double h) {
    x *= h / 2;
    double th = 2 * std::acos(x - 1);
    return pi - th / 2 + std::sin(th) / 2;
}

template <typename T>
double simpson(T f, double x, double a, double b) {
    double c = (a + b) / 2;
    return (f(x, a) + f(x, b) + 4 * f(x, c)) * (b - a) / 6;
}

template <typename T>
double integral(T f, double x, double a, double b, double eps) {
    double c = (a + b) / 2;
    double mid = simpson(f, x, a, b), l = simpson(f, x, a, c), r = simpson(f, x, c, b);
    if (std::abs(l + r - mid) <= 15 * eps)
        return l + r + (l + r - mid) / 15;
    else
        return integral(f, x, a, c, eps / 2) + integral(f, x, c, b, eps / 2);
}

template <typename T>
double calc(T f, double x) {
    return integral(f, x, 0, 2, 1e-8);
}

double d, V;

int main() {
    static int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%lf", &d);
        if (d >= 1) {
            printf("%.5f\n", pi * std::sqrt(1 * 1 + (2 - d) * (2 - d)));
        } else {
            V = pi * d;
            double l = 0, r = 2;
            for (int i = 1; i <= 100; i++) {
                double m = (l + r) / 2;
                (calc(v, m) <= V ? l : r) = m;
            }
            printf("%f\n", l);
            printf("%.5f\n", calc(s, l) * std::sqrt(l * l + 4) / 2);
        }
    }
    return 0;
}
