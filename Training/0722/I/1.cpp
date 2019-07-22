#include <cstdio>
#include <cstdint>
#include <algorithm>
#include <utility>
#include <vector>

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
};

const int N = 1e3 + 10;

int n, pos[N];
int64_t L, R, ans;
point a[N];

struct info {
    int i, j;
    point v;
    info(int i, int j) : i(i), j(j), v(a[j] - a[i]) {}
};

std::vector<info> vec;

int find(const point &v, const point &delta, int64_t target) {
    int l = 1, r = n + 1;
    while (l < r) {
        int m = (l + r) >> 1;
        if (det(v, a[m] - delta) >= target) r = m;
        else l = m + 1;
    }
    printf("find %lld -> %d\n", target, l);
    return l;
}

int main() {
    static int T;
    scanf("%d", &T);
    while (T--) {
        ans = 0;
        scanf("%d%lld%lld", &n, &L, &R);
        L <<= 1, R <<= 1;
        for (int i = 1; i <= n; i++) scanf("%lld%lld", &a[i].x, &a[i].y);
        std::sort(a + 1, a + n + 1, [](const auto &a, const auto &b) { return a.y == b.y ? a.x < b.x : a.y < b.y; });
        for (int i = 1; i <= n; i++) pos[i] = i;
        for (int i = 1; i <= n; i++) for (int j = i + 1; j <= n; j++) vec.emplace_back(i, j);
        std::sort(vec.begin(), vec.end(), [](const auto &a, const auto &b) { return det(a.v, b.v) > 0; });
        for (auto cas : vec) {
            printf("v  (%lld, %lld)\n", cas.v.x, cas.v.y);
            for (int i = 1; i <= n; i++)
                printf("(%lld, %lld)  %lld\n", a[i].x, a[i].y, det(cas.v, a[i] - a[cas.i]));
            puts("");
            ans += find(cas.v, a[cas.i], R) - find(cas.v, a[cas.i], L - 1);
            ans += find(cas.v, a[cas.i], -L) - find(cas.v, a[cas.i], -R - 1);
            std::swap(a[pos[cas.i]], a[pos[cas.j]]);
            std::swap(pos[cas.i], pos[cas.j]);
        }
        printf("%lld\n", ans);
    }
    return 0;
}
