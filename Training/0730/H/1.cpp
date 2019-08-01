#include <cstdio>
#include <cstdint>
#include <algorithm>
#include <utility>

struct point {
    int64_t x, y;
    friend int64_t det(const point &a, const point &b) {
        return a.x * b.y - a.y * b.x;
    }
    int sgn() const {
        if (y == 0) return x > 0 ? 1 : -1;
        else return y > 0 ? 1 : -1;
    }
};

int64_t det(const std::pair<point, int64_t> &a, const std::pair<point, int64_t> &b) {
    return det(a.first, b.first);
}

const int N = 2e5 + 10;
int n;
int64_t v[N], ans;
std::pair<point, int64_t> a[N];

int main() {
    static int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) scanf("%lld%lld%lld", &a[i].first.x, &a[i].first.y, &a[i].second);
        std::sort(a, a + n, [](const std::pair<point, int64_t> &a, const std::pair<point, int64_t> &b) {
            if (a.first.sgn() != b.first.sgn()) return a.first.sgn() > b.first.sgn();
            else return det(a, b) > 0;
        });
        for (int i = 0; i < n; i++)
            a[i + 2 * n] = a[i + n] = a[i];
        for (int i = n; i < (n << 1); i++) v[i] = 0;

        // puts("init");
        {
            int i = n + 1, j = n + 1;
            int64_t sum = 0;
            while (det(a[j - 1], a[i]) > 0) {
                j--;
                sum += a[j].second;
            }
            for (; true; i++) {
                while (j < i && det(a[j], a[i]) <= 0) {
                    sum -= a[j].second;
                    j++;
                }
                if (j > n) break;
                // printf("%d%d %lld %lld %lld\n", i, j, sum, a[i].second);
                v[n] += a[i].second * sum;
            }
        }
        // printf("%lld\n", v[n]);

        // puts("v");
        {
            int i = n + 1, j = n + 1, k = n + 1;
            int64_t sumj = 0, sumk = 0;
            sumk += a[i].second;
            while (det(a[j - 1], a[i]) > 0) {
                j--;
                sumj += a[j].second;
            }
            while (det(a[i], a[k + 1]) > 0) {
                k++;
                sumk += a[k].second;
            }
            for (; i < (n << 1); i++) {
                sumk -= a[i].second;
                while (j < i && det(a[j], a[i]) <= 0) {
                    sumj -= a[j].second;
                    j++;
                }
                while (k < i || det(a[i], a[k + 1]) > 0) {
                    k++;
                    sumk += a[k].second;
                }
                // printf("%d %d %d %lld %lld\n", i, j, k, sumj, sumk);
                v[i] = v[i - 1] - sumj * a[i].second + sumk * a[i].second;
                sumj += a[i].second;
            }
        }
        for (int i = n; i < (n << 1); i++) v[i - n] = v[i + n] = v[i];
        // for (int i = n; i < (n << 1); i++) printf("%lld\n", v[i]);

        ans = 0;
        // puts("ans");
        {
            int i = 0, j = 0;
            while (det(a[i], a[j + 1]) > 0) j++;
            for (; i < n; i++) {
                while (det(a[i], a[j + 1]) > 0) j++;
                // printf("%d %d\n", i, j);
                ans = std::max(ans, v[i] + v[j]);
            }
        }

        printf("%lld\n", ans);
        // puts("");
    }
    return 0;
}
