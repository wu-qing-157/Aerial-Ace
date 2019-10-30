#include <cstdint>
#include <cstdio>
#include <algorithm>

const int N = 5e3 + 10;
int n, k;
int64_t a[N], dp[N][N];

int64_t calc(int i, int j) {
    return a[i] + a[j] - a[(i + j) / 2] - a[(i + j + 1) / 2];
}

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) scanf("%lld", a + i), a[i] += a[i - 1];
    for (int i = 0; i <= n; i++) for (int j = 0; j <= k; j++) dp[i][j] = INT32_MAX;
    dp[0][0] = 0;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= k; j++)
        for (int ii = 0; ii < i; ii++) dp[i][j] = std::min(dp[i][j], dp[ii][j - 1] + calc(i, ii));
    for (int i = 1; i <= k; i++) printf("%lld%c", dp[n][i], " \n"[i == k]);
    printf("%lld\n", dp[n][k]);
    return 0;
}
