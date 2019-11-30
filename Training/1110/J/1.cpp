#include <cstdio>
#include <algorithm>

const int N = 1e5 + 10, K = 60;
int n, k, g1, g2, g3, dp[K][K][K][2], m, x[K], ret[K][K], ans;
char str[N];

int main() {
    scanf("%d%d%d%d%d%s", &n, &k, &g1, &g2, &g3, str + 1);
    for (int i = 1; i <= n; i++)
        if (str[i] == '#')
            x[++m] = i;
    if (m == 0) {
        ret[0][n & 1] = 1;
    } else {
        dp[1][0][!(x[1] & 1)][0] = 1;
        if (x[1] >= 2) dp[1][1][x[1] & 1][1] = 1;
        for (int i = 1; i < m; i++)
            for (int j = 0; j <= i; j++)
                for (int k = 0; k <= i; k++) {
                    if (dp[i][j][k][0]) {
                        dp[i + 1][j][k + !((x[i + 1] ^ x[i]) & 1)][0] = 1;
                        if (x[i + 1] - x[i] >= 2) dp[i + 1][j + 1][k + ((x[i + 1] ^ x[i]) & 1)][1] = 1;
                    }
                    if (dp[i][j][k][1]) {
                        if (x[i + 1] - x[i] >= 2) dp[i + 1][j][k + ((x[i + 1] ^ x[i]) & 1)][0] = 1;
                        if (x[i + 1] - x[i] >= 3) dp[i + 1][j + 1][k + !((x[i + 1] ^ x[i]) & 1)][1] = 1;
                    }
                }
        for (int j = 0; j <= m; j++)
            for (int k = 0; k <= m; k++) {
                if (dp[m][j][k][0]) ret[j][k + ((n ^ x[m]) & 1)] = 1;
                if (dp[m][j][k][1] && x[m] < n) ret[j][k + !((n ^ x[m]) & 1)] = 1;
            }
    }
    for (int j = 0; j <= m; j++)
        for (int kk = 0; kk <= m + 1; kk++)
            if (ret[j][kk]) {
                static int s, t;
                s = n - m - 2 * j;
                t = kk;
                if (g2 >= 2 * g1)
                    ans = std::max(ans, (s - t) / 2 * g2 + std::min(k, t) * g1 + j * g3);
                else if (k <= t)
                    ans = std::max(ans, (s - t) / 2 * g2 + k * g1 + j * g3);
                else if (k >= s)
                    ans = std::max(ans, s * g1 + j * g3);
                else if (!((s - k) & 1))
                    ans = std::max(ans, (s - k) / 2 * g2 + k * g1 + j * g3);
                else
                    ans = std::max(ans, (s - k) / 2 * g2 + (k - 1) * g1 + std::max(g1, g2) + j * g3);
            }
    printf("%d\n", ans);
    return 0;
}
