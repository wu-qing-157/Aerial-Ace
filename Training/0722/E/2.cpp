#include <cstdio>
#include <algorithm>

const int MOD = 1000000007;

const int N = 210;
int n, k;
int dp[N][N][N], sum[N];

inline int inc(int x) {
    return x >= MOD ? x - MOD : x;
}

int solve(int L) {
    if (L == 0) return 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= L; j++)
            for (int k = 1; k <= n; k++)
                dp[i][j][k] = 0;
    dp[1][1][1] = 1;
    for (int i = 2; i <= n; i++) {
        for (int j = 1, up = std::min(i - 1, L); j <= up; j++) {
            sum[i + 1] = 0;
            for (int k = i; k; k--)
                sum[k] = inc(sum[k + 1] + dp[i - 1][j][k]);
            for (int kk = 1; kk <= i; kk++)
                dp[i][1][kk] = inc(dp[i][1][kk] + sum[kk]);
        }
        for (int j = 2, up = std::min(i, L); j <= up; j++) {
            sum[0] = 0;
            for (int k = 1; k < i; k++)
                sum[k] = inc(sum[k - 1] + dp[i - 1][j - 1][k]);
            for (int kk = 1; kk <= i; kk++)
                dp[i][j][kk] = sum[kk - 1];
        }
    }
    int ans = 0;
    for (int j = 1; j <= L; j++)
        for (int k = 1; k <= n; k++)
            ans = inc(ans + dp[n][j][k]);
    return ans;
}

int main() {
    freopen("permutations.in", "r", stdin);
    static int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &k);
        int ans = solve(k) - solve(k - 1);
        if (ans < 0) ans += MOD;
        printf("%d\n", ans);
    }
    return 0;
}
