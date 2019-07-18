#include <cstdio>
#include <cmath>
#include <algorithm>

#define y1 yyyyyy1

const double pi = std::acos(-1);

double d, r, u, v, delta;

double sqr(double x) {
    return x * x;
}

double calc(double a1, double a2, bool same, double th1, double th2) {
    return r * (th1 - a1 + th2 - a2) / v +
        std::sqrt(sqr(d - r * (std::cos(a1) + std::cos(a2))) +
                sqr(r * (same ? std::sin(a1) - std::sin(a2) : std::sin(a1) + std::sin(a2)))) / u;
}

double solve(double a1, bool same, double th1, double th2) {
    double l = 0, r = same ? std::min(th2, pi / 2) : std::min(th2, delta);
    for (int i = 1; i <= 300; i++) {
        double m1 = (l * 2 + r) / 3, m2 = (m1 + r) / 2;
        if (calc(a1, m1, same, th1, th2) < calc(a1, m2, same, th1, th2)) r = m2;
        else l = m1;
    }
    return calc(a1, l, same, th1, th2);
}

double process(bool same, double th1, double th2) {
    double l = 0, r = same ? std::min(th1, pi / 2) : std::min(th1, delta);
    for (int i = 1; i <= 300; i++) {
        double m1 = (l * 2 + r) / 3, m2 = (m1 + r) / 2;
        if (solve(m1, same, th1, th2) < solve(m2, same, th1, th2)) r = m2;
        else l = m1;
    }
    return solve(l, same, th1, th2);
}

int main() {
    //freopen("bike.in", "r", stdin);
    //freopen("bike.out", "w", stdout);
    double x1, y1, x2, y2;
    scanf("%lf%lf%lf%lf%lf%lf%lf%lf", &d, &r, &x1, &y1, &x2, &y2, &v, &u);
    delta = std::acos(2 * r / d);
    double th1 = std::acos(y1 / r);
    double th2 = std::acos((d - y2) / r);
    bool same = (x1 >= 0) == (x2 >= 0);
    double ans = process(same, th1, th2);
    ans = std::min(ans, process(!same, 2 * pi - th1, th2));
    ans = std::min(ans, process(!same, th1, 2 * pi - th2));
    ans = std::min(ans, process(same, 2 * pi - th1, 2 * pi - th2));
    printf("%.10f\n", ans);
    return 0;
}
