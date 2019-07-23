#include <cstdio>
#include <cstdint>
#include <algorithm>
#include <initializer_list>

const int N = 50;

int n;
int64_t dp[N][N][3][N][2], ans;

inline int inc(int x, int n) {
    if (n <= x) return x + 1;
    return x;
}

int main() {
    // freopen("permutominoes.in", "r", stdin);
    // freopen("permutominoes.out", "w", stdout);
    scanf("%d", &n), n -= 2;
    if (n == 0) {
        puts("1");
        return 0;
    }
    dp[1][1][2][1][0] = dp[1][1][2][1][1] = 1;
    for (int i = 1; i < n; i++)
        for (int j = 1; j <= i; j++)
            for (int bj : { 0, 1, 2 })
                for (int k = 1; k <= i; k++)
                    for (int bk : { 0, 1 }) if (dp[i][j][bj][k][bk]) {
                        // printf("trans %d %d %d %d %d\n", i, j, bj, k, bk);
                        for (int jj = 1; jj <= i + 1; jj++) {
                            if (bj == 2) {
                                if (jj <= j) dp[i + 1][jj][0][inc(k, jj)][bk] += dp[i][j][bj][k][bk]; // ("%d %d %d %d %d\n", i + 1, jj, 0, inc(k, jj), bk);
                                if (jj <= k || bk == 0) dp[i + 1][jj][1][inc(k, jj)][bk] += dp[i][j][bj][k][bk]; // ("%d %d %d %d %d\n", i + 1, jj, 1, inc(k, jj), bk);
                            } else if (bj == 0) {
                                if (jj <= j && jj <= k) dp[i + 1][jj][0][inc(k, jj)][bk] += dp[i][j][bj][k][bk]; // ("%d %d %d %d %d\n", i + 1, jj, 0, inc(k, jj), bk);
                                if (bk == 0) {
                                    dp[i + 1][jj][1][inc(k, jj)][bk] += dp[i][j][bj][k][bk]; // ("%d %d %d %d %d\n", i + 1, jj, 1, inc(k, jj), bk);
                                } else {
                                    if (jj <= k) dp[i + 1][jj][1][inc(k, jj)][bk] += dp[i][j][bj][k][bk]; // ("%d %d %d %d %d\n", i + 1, jj, 1, inc(k, jj), bk);
                                }
                            } else {
                                if (jj <= j) continue;
                                if (bk == 0) {
                                    dp[i + 1][jj][1][inc(k, jj)][bk] += dp[i][j][bj][k][bk]; // ("%d %d %d %d %d\n", i + 1, jj, 1, inc(k, jj), bk);
                                } else {
                                    if (jj <= k) dp[i + 1][jj][1][inc(k, jj)][bk] += dp[i][j][bj][k][bk]; // ("%d %d %d %d %d\n", i + 1, jj, 1, inc(k, jj), bk);
                                }
                            }
                        }
                        for (int kk = 1; kk <= i + 1; kk++) {
                            if (bj == 2) {
                                if (bk == 0) {
                                    if (kk > k) dp[i + 1][std::min(inc(j, kk), kk)][2][kk][0] += dp[i][j][bj][k][bk]; // ("%d %d %d %d %d\n", i + 1, std::min(inc(j, kk), kk), 2, kk, 0);
                                    dp[i + 1][std::min(inc(j, kk), kk)][2][kk][1] += dp[i][j][bj][k][bk]; // ("%d %d %d %d %d\n", i + 1, std::min(inc(j, kk), kk), 2, kk, 1);
                                } else {
                                    if (kk > k) continue;
                                    dp[i + 1][std::min(inc(j, kk), kk)][2][kk][1] += dp[i][j][bj][k][bk]; // ("%d %d %d %d %d\n", i + 1, std::min(inc(j, kk), kk), 2, kk, 1);
                                }
                            } else {
                                if (bk == 0) {
                                    if (kk > k && kk > j) dp[i + 1][inc(j, kk)][bj][kk][0] += dp[i][j][bj][k][bk]; // ("%d %d %d %d %d\n", i + 1, inc(j, kk), bj, kk, 0);
                                    if (bj == 0) {
                                        dp[i + 1][inc(j, kk)][bj][kk][1] += dp[i][j][bj][k][bk]; // ("%d %d %d %d %d\n", i + 1, inc(j, kk), bj, kk, 1);
                                    } else {
                                        if (kk > j) dp[i + 1][inc(j, kk)][bj][kk][1] += dp[i][j][bj][k][bk]; // ("%d %d %d %d %d\n", i + 1, inc(j, kk), bj, kk, 1);
                                    }
                                } else {
                                    if (kk > k) continue;
                                    if (bj == 0) {
                                        dp[i + 1][inc(j, kk)][bj][kk][1] += dp[i][j][bj][k][bk]; // ("%d %d %d %d %d\n", i + 1, inc(j, kk), bj, kk, 1);
                                    } else {
                                        if (kk > j) dp[i + 1][inc(j, kk)][bj][kk][1] += dp[i][j][bj][k][bk]; // ("%d %d %d %d %d\n", i + 1, inc(j, kk), bj, kk, 1);
                                    }
                                }
                            }
                        }
                    }
    /*
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= i; j++)
            for (int bj : { 0, 1, 2 })
                for (int k = j; k <= i; k++)
                    for (int bk : { 0, 1 })
                        printf("%d %d %d %d %d    %ld\n", i, j, bj, k, bk, dp[i][j][bj][k][bk]);
    */
    for (int j = 1; j <= n; j++)
        for (int bj : { 0, 1, 2 })
            for (int k = 1; k <= n; k++)
                for (int bk : { 0, 1 })
                    ans += dp[n][j][bj][k][bk];
    ans <<= 1;
    // ans += 1ll << (n + 1);
    printf("%lld\n", ans);
    return 0;
}
