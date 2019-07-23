#include <cstdio>
#include <cstdint>
#include <algorithm>

const int N = 50;

int n;
int64_t dp[N][N][2][N][2], ans;

int main() {
    scanf("%d", &n), n -= 2;
    dp[0][1][0][0][0] = 1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j <= i + 1; j++)
            for (int k = 0; k <= i + 1; k++) {
                for (int jj = 1; jj <= j; jj++)
                    dp[i + 1][jj][0][k + 1][0] += dp[i][j][0][k][0];
                for (int jj = 1; jj <= k; jj++)
                    dp[i + 1][jj][1][k + 1][0] += dp[i][j][0][k][0];
                for (int jj = k + 1; jj <= i + 1; jj++)
                    dp[i + 1][jj][1][k][0] += dp[i][j][0][k][0];
                for (int kk = j + 1; kk <= i + 1; kk++)
                    dp[i + 1][j][0][kk][1] += dp[i][j][0][k][0];
                for (int kk = 1; kk <= j; kk++)
                    dp[i + 1][j + 1][0][kk][1] += dp[i][j][0][k][0];

                for (int jj = j + 1; jj <= k; jj++)
                    dp[i + 1][jj][1][k + 1][0] += dp[i][j][1][k][0];
                for (int jj = std::max(j, k) + 1; jj <= i + 1; jj++)
                    dp[i + 1][jj][1][k][0] += dp[i][j][1][k][0];
                for (int kk = std::max(j, k) + 1; kk <= i + 1; kk++)
                    dp[i + 1][j][1][kk][0] += dp[i][j][1][k][0];
                for (int kk = j + 1; kk <= i + 1; kk++)
                    dp[i + 1][j][1][kk][1] += dp[i][j][1][k][0];

                for (int kk = j + 1; kk <= k; kk++)
                    dp[i + 1][j][0][kk][1] += dp[i][j][0][k][1];
                for (int kk = 1; kk <= std::min(j, k); kk++)
                    dp[i + 1][j + 1][0][kk][1] += dp[i][j][0][k][1];
                for (int jj = 1; jj <= std::min(j, k); jj++)
                    dp[i + 1][jj][0][k + 1][1] += dp[i][j][0][k][1];
                for (int jj = 1; jj <= k; jj++)
                    dp[i + 1][jj][1][k + 1][1] += dp[i][j][0][k][1];

                for (int jj = j + 1; jj <= k; jj++)
                    dp[i + 1][jj][1][k + 1][1] += dp[i][j][1][k][1];
                for (int kk = j + 1; kk <= k; kk++)
                    dp[i + 1][j][1][kk][1] += dp[i][j][1][k][1];
            }
    for (int j = 1; j <= n; j++) for (int k = 1; k <= n; k++) {
        ans += dp[n][j][0][k][0];
        ans += dp[n][j][0][k][1];
        ans += dp[n][j][1][k][0];
        ans += dp[n][j][1][k][1];
    }
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) for (int k = 1; k <= n; k++) {
        printf("%d %d %d %d %d      %lld\n", i, j, 0, k, 0, dp[i][j][0][k][0]);
        printf("%d %d %d %d %d      %lld\n", i, j, 0, k, 1, dp[i][j][0][k][1]);
        printf("%d %d %d %d %d      %lld\n", i, j, 1, k, 0, dp[i][j][1][k][0]);
        printf("%d %d %d %d %d      %lld\n", i, j, 1, k, 1, dp[i][j][1][k][1]);
        puts("");
    }
    printf("%lld\n", ans);
    return 0;
}
