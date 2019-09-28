#include <cstdio>

const int N = 1e3 + 10, MOD = 1e9 + 7;
int n, k, cur = 1, a[N], dp[N][N], sum[N][N];
bool v[N];

int main() {
    freopen("monotonic.in", "r", stdin);
    freopen("monotonic.out", "w", stdout);
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= k; i++) {
        scanf("%d", a + i);
        cur += a[i];
        v[cur] = true;
    }
    dp[1][1] = sum[1][1] = 1;
    for (int i = 2; i <= n; i++)
        for (int j = 1; j <= i; j++) {
            if (v[i])
                dp[i][j] = (sum[i - 1][i - 1] - sum[i - 1][j - 1] + MOD) % MOD;
            else
                dp[i][j] = sum[i - 1][j - 1];
            sum[i][j] = (sum[i][j - 1] + dp[i][j]) % MOD;
        }
    printf("%d\n", sum[n][n]);
    return 0;
}
