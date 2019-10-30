#include <cmath>
#include <cstdio>
#include <algorithm>

struct point {
    double x, y;
    point() {}
    point(double x, double y) : x(x), y(y) {}
    friend point operator+(const point &a, const point &b) {
        return point(a.x + b.x, a.y + b.y);
    }
    friend point operator-(const point &a, const point &b) {
        return point(a.x - b.x, a.y - b.y);
    }
    friend point operator*(const point &a, const double &b) {
        return point(a.x * b, a.y * b);
    }
    friend double det(const point &a, const point &b) {
        return a.x * b.y - a.y * b.x;
    }
    friend double dot(const point &a, const point &b) {
        return a.x * b.x + a.y * b.y;
    }
    friend double dis(const point &a, const point &b) {
        return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    }
};

struct line {
    point a, b;
    line() {}
    line(point a, point b) : a(a), b(b) {}
};

const int N = 1e5 + 10;
const double eps = 1e-10;
int n, op[N];
point p[N], sl, sr, tl, tr;
double amax = -1e60, amin = 1e60, S, wh[N];

double calc(const point &s) {
    double l = 0, r = 1;
    for (int time = 1; time <= 100; time++) {
        double m = (l + r) / 2;
        point t = tl * (1 - m) + tr * m;
        if (det(s - sl, tl - sl) >= det(tl - s, t - s))
            l = m;
        else
            r = m;
    }
    point t = tl * (1 - l) + tr * l;
    return dis(s, t);
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%lf%lf", &p[i].x, &p[i].y);
    for (int i = 0; i < n; i++) p[i + 2 * n] = p[i + n] = p[i];
    for (int i = 1; i < n - 1; i++) S += det(p[i] - p[0], p[i + 1] - p[0]);
    for (int i = 0, j; i < n; i++) {
        double cur = 0;
        j = i + 1;
        while (cur + det(p[j] - p[i], p[j + 1] - p[i]) <= S / 2 + eps)
            cur += det(p[j] - p[i], p[j + 1] - p[i]), j++;
        double l = 0, r = 1;
        for (int time = 1; time <= 200; time++) {
            double m = (l + r) / 2;
            if (cur + det(p[j] - p[i], p[j] * (1 - m) + p[j + 1] * m - p[i]) <= S / 2)
                l = m;
            else
                r = m;
        }
        op[i] = j % n;
        wh[i] = l;
        amax = std::max(amax, dis(p[i], p[j] * (1 - l) + p[j + 1] * l));
    }
    for (int i = 0, j; i < n; i++) {
        j = op[i];
        sl = p[i], sr = p[i + 1];
        tl = p[j] * (1 - wh[i]) + p[j + 1] * wh[i], tr = p[j + 1];
        if (op[(j + 1) % n] == i)
            sr = p[i] * (1 - wh[(j + 1) % n]) + p[i + 1] * wh[(j + 1) % n];
        if (op[(i + 1) % n] == j)
            tr = p[j] * (1 - wh[(i + 1) % n]) + p[j + 1] * wh[(i + 1) % n];
        double ll = 0, rr = 1;
        for (int time0 = 1; time0 <= 200; time0++) {
            double m1 = (ll * 2 + rr) / 3, m2 = (m1 + rr) / 2;
            if (calc(sl * (1 - m1) + sr * m1) <= calc(sl * (1 - m2) + sr * m2))
                rr = m2;
            else
                ll = m1;
        }
        amin = std::min(amin, calc(sl * (1 - ll) + sr * ll));
    }
    printf("%.10f\n", amin);
    printf("%.10f\n", amax);
    return 0;
}
