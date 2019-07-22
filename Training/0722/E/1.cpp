#include <cstdio>
#include <cstdint>

const int64_t MOD = 1000000007;
#define _ % MOD
#define __ %= MOD

const int N = 210;
int n, k;
int64_t dp[N][N][N], sum[N];

int64_t solve(int L) {
    if (L == 0) return 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= L; j++)
            for (int k = 1; k <= n; k++)
                dp[i][j][k] = 0;
    dp[1][1][1] = 1;
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= L; j++) {
            sum[n + 1] = 0;
            for (int k = n; k; k--)
                sum[k] = (sum[k + 1] + dp[i - 1][j][k])_;
            for (int kk = 1; kk <= i; kk++)
                (dp[i][1][kk] += sum[kk])__;
        }
        for (int j = 2; j <= L; j++) {
            sum[0] = 0;
            for (int k = 1; k <= n; k++)
                sum[k] = (sum[k - 1] + dp[i - 1][j - 1][k])_;
            for (int kk = 1; kk <= i; kk++)
                dp[i][j][kk] = sum[kk - 1];
        }
    }
    /*
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= L; j++)
            for (int k = 1; k <= n; k++)
                printf("%d %d %d      %ld\n", i, j, k, dp[i][j][k]);
                */
    int64_t ans = 0;
    for (int j = 1; j <= L; j++)
        for (int k = 1; k <= n; k++)
            (ans += dp[n][j][k])__;
    return ans;
}

int main() {
    freopen("permutations.in", "r", stdin);
    static int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &k);
        printf("%lld\n", (solve(k) - solve(k - 1) + MOD)_);
    }
    return 0;
}
