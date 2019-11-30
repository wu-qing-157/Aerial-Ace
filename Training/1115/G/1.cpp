#include <cstdio>
#include <algorithm>

const double eps = 1e-9;

double simpson(double f(double), double a, double b) {
    double c = (a + b) / 2;
    return (f(a) + f(b) + 4 * f(c)) * (b - a) / 6;
}

double integral(double f(double), double a, double b, double eps) {
    double c = (a + b) / 2;
    double mid = simpson(f, a, b), l = simpson(f, a, c), r = simpson(f, c, b);
    if (std::abs(l + r - mid) <= 15 * eps)
        return l + r + (l + r - mid) / 15;
    else
        return integral(f, a, c, eps / 2) + integral(f, c, b, eps / 2);
}

double s, w[100], ans[100];
int a[100], p[100];

double f3(double x) {
    return 1;
}

double f2(double x) {
    return integral(f3, x, std::min(x + w[p[2]], s), eps);
}

double f1(double x) {
    return integral(f2, x, std::min(x + w[p[1]], s), eps);
}

std::vector<double> inter;

int main() {
    static int T;
    scanf("%d", &T);
    for (int i : {1, 2, 3}) p[i] = i;
    for (int cas = 1; cas <= T; cas++) {
        scanf("%lf%lf%lf%lf", &s, w + 1, w + 2, w + 3);
        do {
        } while (std::next_permutation(p + 1, p + 4));
        ans[cas] /= s * s * s;
    }
    for (int i = 1; i <= T; i++) a[i] = i;
    std::sort(a + 1, a + T + 1, [](int a, int b) {
        return std::abs(ans[a] - ans[b]) < eps * 10 ? a < b : ans[a] < ans[b];
    });
    for (int i = 1; i <= T; i++) printf("%d%c", a[i], " \n"[i == T]);
    return 0;
}
