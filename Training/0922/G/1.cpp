#include <cmath>
#include <cstdio>
#include <cstdint>
#include <algorithm>

#pragma GCC optimize(3)

const double pi = std::acos(-1), theta = 0.2812;

double sqr(double x) {
    return x * x;
}

struct point {
    double x, y;
    point() {}
    point(double x, double y) : x(x), y(y) {}
    friend point operator-(const point &a, const point &b) {
        return point(a.x - b.x, a.y - b.y);
    }
    friend double dot(const point &a, const point &b) {
        return a.x * b.x + a.y * b.y;
    }
    friend double det(const point &a, const point &b) {
        return a.x * b.y - a.y * b.x;
    }
    double len2() const {
        return x * x + y * y;
    }
    point rotate(double angle = theta) const {
        return point(x * std::cos(angle) + y * std::sin(angle),
                -x * std::sin(angle) + y * std::cos(angle));
    }
};

struct line {
    point a, b, v;
    double d2, max;
    line() {}
    line(const point &a, const point &b) : a(a), b(b), v(a - b), d2(v.len2()), max(std::max(a.y, b.y {}
};

const int N = 1e4 + 10;
int n;
double ans;
point p[N << 1];
line l[N];

void f() {
    for (int i = 0, s = 0, t = 0; i <= 2 * n; i++) {
        while (std::max(l[t].a.y, l[t].b.y) <= p[i].y - 1e-8) t++;
        while (s <= t && p[i].y - std::max(l[s].a.y, l[s].b.y) >= ans) s++;
        for (int j = s; j < t; j++) {
            ans = std::min(ans, std::min((p[i] - l[j].a).len2(), (p[i] - l[j].b).len2()));
            if (dot(p[i] - l[j].a, l[j].v) > 0 && dot(p[i] - l[j].b, l[j].v) < 0)
                ans = std::min(ans, sqr(det(p[i] - l[j].a, l[j].v)) / l[j].d2);
        }
    }
}

int main() {
    static int T;
    scanf("%d", &T);
    while (T--) {
        ans = 1e60;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            static int x1, y1, x2, y2;
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            l[i] = line(p[i << 1] = point(x1, y1).rotate(), p[i << 1 | 1] = point(x2, y2).rotate());
        }
        std::sort(p, p + n * 2, [](const point &a, const point &b) {
            return a.y < b.y;
        });
        std::sort(l, l + n, [](const line &a, const line &b) {
            return std::max(a.a.y, a.b.y) < std::max(b.a.y, b.b.y);
        });
        f();
        std::sort(p, p + n * 2, [](const point &a, const point &b) {
            return a.y > b.y;
        });
        std::sort(l, l + n, [](const line &a, const line &b) {
            return std::max(a.a.y, a.b.y) > std::max(b.a.y, b.b.y);
        });
        f();
        printf("%.10f\n", std::sqrt(ans));
    }
    return 0;
}
