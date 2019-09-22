#include <cstdint>
#include <cstdio>
#include <algorithm>

const int N = 2e5 + 10;
int x, y, a, b;
int64_t dp[2][N];

int lower(int64_t *array, int i, int l, int r) {
    r++;
    while (l < r) {
        int m = (l + r) >> 1;
        if (array[m - 1] + b >= dp[0][i + 1 - m] + a)
            r = m;
        else
            l = m + 1;
    }
    return l;
}

int main() {
    dp[0][0] = dp[1][0] = INT64_MIN / 4;
    dp[0][1] = 0;
    static int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d%d", &x, &y, &a, &b);
        dp[1][1] = a;
        for (int i = 2; i <= y - x + 1; i++) {
            int x = lower(dp[0], i, 1, i);
            dp[0][i] = x > i ? INT64_MAX : std::max(dp[0][x - 1] + b, dp[0][i + 1 - x] + a);
            if (--x > 1)
                dp[0][i] = std::min(dp[0][i], std::max(dp[0][x - 1] + b, dp[0][i + 1 - x] + a));
            x = lower(dp[1], i, 1, i);
            dp[1][i] = x > i ? INT64_MAX : std::max(dp[1][x - 1] + b, dp[0][i + 1 - x] + a);
            if (--x)
                dp[1][i] = std::min(dp[1][i], std::max(dp[1][x - 1] + b, dp[0][i + 1 - x] + a));
        }
        printf("%lld\n", dp[x > 0][y - x + 1]);
    }
    return 0;
}
