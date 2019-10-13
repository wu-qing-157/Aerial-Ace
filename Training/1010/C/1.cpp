#include <cstdio>

const int N = 5e3 + 10, M = 5e3 + 10, MOD = 998244353;
int n, m, a[N], b[M], jie[N], inv[N];
int dp[N][M][2][2], ans;

int c(int n, int m) {
    return int(1ll * jie[n] * inv[m] % MOD * inv[n - m] % MOD);
}

int main() {
    jie[0] = jie[1] = inv[0] = inv[1] = 1;
    for (int i = 2; i < N; i++) jie[i] = int(1ll * jie[i - 1] * i % MOD);
    for (int i = 2; i < N; i++) inv[i] = int(1ll * inv[MOD % i] * (MOD - MOD / i) % MOD);
    for (int i = 2; i < N; i++) inv[i] = int(1ll * inv[i - 1] * inv[i] % MOD);
    while (scanf("%d%d", &n, &m) != EOF) {
        for (int i = 1; i <= n; i++) scanf("%d", a + i);
        for (int j = 1; j <= m; j++) scanf("%d", b + j);
        ans = 0;
        for (int i = 1; i <= n; i++) for (int j = 1; j < i; j++)
            (ans += c(n, i) * c(m, j)) %= MOD;
        printf("%d\n", ans);
        dp[0][0][0][0] = 1;
        for (int i = 1; i <= n; i++) dp[i][0][0][0] = 1;
        for (int j = 1; j <= m; j++) dp[0][j][1][0] = 1;
        for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
            dp[i][j][0][0] = dp[i - 1][j][0][0];
            dp[i][j][1][0] = (dp[i][j - 1][0][0] + dp[i][j - 1][1][0]) % MOD;
            dp[i][j][0][1] = dp[i - 1][j][0][1];
            dp[i][j][1][1] = (dp[i][j - 1][0][0] + dp[i][j - 1][1][0]) % MOD;
            if (a[i] == b[j])
                (dp[i][j][0][0] += (dp[i - 1][j - 1][0][0] + dp[i - 1][j - 1][1][0]) % MOD) %= MOD;
            if (a[i] > b[j])
                (dp[i][j][0][1] += (dp[i - 1][j - 1][0][0] + dp[i - 1][j - 1][1][0]) % MOD) %= MOD;
            (dp[i][j][0][1] += (dp[i - 1][j - 1][0][1] + dp[i - 1][j - 1][1][1]) % MOD) %= MOD;
        }
        (ans += dp[n][m][0][1]) %= MOD;
        (ans += dp[n][m][1][1]) %= MOD;
        printf("%d\n", ans);
    }
    return 0;
}
