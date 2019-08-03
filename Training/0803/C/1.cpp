#include <cstdio>
#include <cstdint>
#include <algorithm>

struct point {
    int64_t x, y;
    point() {}
    point(int64_t x, int64_t y) : x(x), y(y) {}
    friend point operator-(const point &a, const point &b) {
        return point(a.x - b.x, a.y - b.y);
    }
    friend int64_t det(const point &a, const point &b) {
        return a.x * b.y - a.y * b.x;
    }
    bool sgn() const {
        return y == 0 ? x > 0 : y > 0;
    }
};

struct line {
    point a, b;
    line() {}
    line(point _a, point _b) : a(_a), b(_b) {
        if (!(b - a).sgn()) std::swap(a, b);
    }
    point v() const {
        return b - a;
    }
};

bool line_cmp(const line &a, const line &b) {
    if (det(a.v(), b.v()) != 0) return det(a.v(), b.v()) > 0;
    return det(b.b - a.a, a.b - a.a) < 0;
}

bool equal1(const line &a, const line &b) {
    return det(a.v(), b.v()) == 0;
}

bool equal2(const line &a, const line &b) {
    return det(b.b - a.a, a.b - a.a) == 0;
}

const int N = 1e5 + 10;
int n;
int64_t ans;
line a[N];

int main() {
    static int T;
    scanf("%d", &T);
    while (T--) {
        ans = 0;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            static int64_t sx, sy, tx, ty;
            scanf("%lld%lld%lld%lld", &sx, &sy, &tx, &ty);
            a[i] = line(point(sx, sy), point(tx, ty));
        }
        std::sort(a, a + n, line_cmp);
        int cnt1 = 0, cnt2 = 0;
        for (int i = 0; i < n; i++) {
            if (i == 0 || equal1(a[i - 1], a[i])) {
                if (i == 0 || equal2(a[i - 1], a[i])) {
                    cnt2++;
                } else {
                    ans += 1ll * cnt2 * (cnt2 - 1) / 2;
                    cnt2 = 1;
                }
                cnt1++;
            } else {
                ans += 1ll * cnt1 * (i - cnt1);
                ans += 1ll * cnt2 * (cnt2 - 1) / 2;
                cnt1 = cnt2 = 1;
            }
        }
        ans += 1ll * cnt2 * (cnt2 - 1) / 2;
        ans += 1ll * cnt1 * (n - cnt1);
        printf("%lld\n", ans);
    }
    return 0;
}
