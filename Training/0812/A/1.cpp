#include <cstdio>
#include <cstdint>
#include <algorithm>
#include <functional>

const int N = 12, NN = 100, M = 2e3 + 10, K = 60;
const int64_t INF = INT64_MAX;
int n, s, m, c1, c2, cnt[NN][N], a[NN];
int64_t dp[NN][M], p1[K], p2[K];

int main() {
    scanf("%d%d", &n, &s), m = 2 * n * (s + 1);
    for (int i = 0; i < m; i++) scanf("%d", a + i), a[i]--;
    for (int i = 1; i < m; i++) {
        for (int j = 0; j < 2 * n; j++)
            cnt[i][j] = cnt[i - 1][j];
        cnt[i][a[i - 1]]++;
    }
    scanf("%d", &c2);
    for (int i = 0; i < c2; i++) scanf("%lld", p2 + i);
    std::sort(p2, p2 + c2, std::greater<decltype(*p2)>());
    scanf("%d", &c1);
    for (int i = 0; i < c1; i++) scanf("%lld", p1 + i);
    std::sort(p1, p1 + c1, std::greater<decltype(*p1)>());

    dp[m][(1 << (2 * n)) - 1] = 0;
    for (int i = m - 1; i >= 0; i--)
        for (int j = 0; j < 1 << (2 * n); j++) {
            if (__builtin_popcount(j) > i) continue;
            if (a[i] < n) {
                dp[i][j] = -INF;
                if (cnt[i][a[i]] - ((j & (1 << a[i])) > 0) < s)
                    dp[i][j] = std::max(dp[i][j], dp[i + 1][j] + p2[i - __builtin_popcount(j)]);
                if ((j & (1 << a[i])) == 0)
                    dp[i][j] = std::max(dp[i][j], dp[i + 1][j | (1 << a[i])] + p1[__builtin_popcount(j)]);
            } else {
                dp[i][j] = INF;
                if (cnt[i][a[i]] - ((j & (1 << a[i])) > 0) < s)
                    dp[i][j] = std::min(dp[i][j], dp[i + 1][j] - p2[i - __builtin_popcount(j)]);
                if ((j & (1 << a[i])) == 0)
                    dp[i][j] = std::min(dp[i][j], dp[i + 1][j | (1 << a[i])] - p1[__builtin_popcount(j)]);
            }
        }

    /*
    for (int i = 0; i < m; i++)
        for (int j = 0; j < 1 << (2 * n); j++) {
            printf("%d ", i);
            for (int k = 0; k < n; k++) printf("%d", (j & (1 << k)) > 0);
            printf(" ");
            for (int k = n; k < 2 * n; k++) printf("%d", (j & (1 << k)) > 0);
            printf("   %lld\n", dp[i][j]);
        }
        */
    printf("%lld\n", dp[0][0]);
    return 0;
}
