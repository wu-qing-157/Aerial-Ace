#include <cstdio>
#include <cstdint>
#include <algorithm>
#include <utility>
#include <vector>

int sgn(int64_t x) {
    return (x > 0) - (x < 0);
}

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
    friend int64_t dot(const point &a, const point &b) {
        return a.x * b.x + a.y * b.y;
    }
    bool sign() const {
        if (y == 0) return x >= 0;
        return y > 0;
    }
};

const int N = 1e3 + 10;

int n, m;
int64_t L, R, ans;
point p[N];
std::vector<point> a;

struct info {
    int i, j;
    point v;
    info(int i, int j) : i(i), j(j), v(a[j] - a[i]) {}
};

int find(const point &v, int l, int r, int64_t target) {
    if (det(v, a[r]) < target) return r + 1;
    while (l < r) {
        int m = (l + r) >> 1;
        if (det(v, a[m]) >= target) r = m;
        else l = m + 1;
    }
    // printf("find %lld -> %d\n", target, l);
    return l;
}

bool point_cmp(const point &a, const point &b) {
    if (a.sign() != b.sign()) return a.sign() > b.sign();
    if (det(a, b) != 0) return det(a, b) > 0;
    return llabs(a.x) < llabs(b.x) || llabs(a.y) < llabs(b.y);
}

int cmp90(const point &a, const point &b) {
    if (det(a, b) < 0) return 1;
    return -sgn(dot(a, b));
}

int main() {
    freopen("points.in", "r", stdin);
    static int T;
    scanf("%d", &T);
    while (T--) {
        ans = 0;
        scanf("%d%lld%lld", &n, &L, &R);
        m = n - 1, L <<= 1, R <<= 1;
        for (int i = 1; i <= n; i++) scanf("%lld%lld", &p[i].x, &p[i].y);
        bool flag = false;
        for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) if (det(p[i], p[j]) != 0) flag = true;
        if (!flag) {
            puts("0");
            continue;
        }
        for (int i = 1; i <= n; i++) {
            a.clear();
            for (int j = 1; j <= n; j++) if (i != j) a.push_back(p[j] - p[i]);
            std::sort(a.begin(), a.end(), point_cmp);
            for (int j = 0; j < m; j++) a.push_back(a[j]);
            for (int j = 0, k = 0, l; j < m; j++) {
                while (k < j + m && cmp90(a[j], a[k]) < 0) k++;
                // puts("~");
                if (cmp90(a[j], a[k]) != 0) continue;
                l = k;
                while (l < j + m && cmp90(a[j], a[l + 1]) == 0) l++;
                // printf("%d -> %d     %d %d\n", i, j, k, l);
                ans += find(a[j], k, l, R + 1) - find(a[j], k, l, L);
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}
