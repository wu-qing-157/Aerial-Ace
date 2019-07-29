#include <cstdio>
#include <cmath>
#include <algorithm>

using number = long double;

number _acos(number x) {
    return std::acos(std::max<number>(std::min<number>(x, 1), -1));
}

number _sqrt(number x) {
    return std::sqrt(std::max<number>(x, 0));
}

struct point {
    number x, y;
    point() {}
    point(number x, number y) : x(x), y(y) {}

    friend point operator-(const point &a, const point &b) {
        return point(a.x - b.x, a.y - b.y);
    }
    friend number dot(const point &a, const point &b) {
        return a.x * b.x + a.y * b.y;
    }

    number len2() const {
        return x * x + y * y;
    }
};

number angle(const point &a, const point &b, const point &c) {
    return _acos(-dot(b - a, c - a) / _sqrt((b - a).len2() * (c - a).len2()));
}

const int N = 110;
int n;
point p[N], q;
number ans;

int main() {
    static int T;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; cas++) {
        ans = 0;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            static int tx, ty;
            scanf("%d%d", &tx, &ty);
            p[i] = point(tx, ty);
        }
        p[0] = p[n], p[n + 1] = p[1];
        static int tx, ty;
        scanf("%d%d", &tx, &ty);
        q = point(tx, ty);
        for (int i = 1; i <= n; i++)
            ans += angle(p[i], p[i - 1], p[i + 1]) * _sqrt((q - p[i]).len2());
        printf("Case #%d: %.3f\n", cas, (double) ans);
    }
    return 0;
}
