#include <cstdint>
#include <cstdio>
#include <algorithm>

const int INF = INT32_MAX / 4;
int E, P, n, e[10], p[10];
int ans, dp[256][101][101];

void inc(int &x, int y) {
    //printf("           %d %d\n", x, y);
    if (x < y) x = y;
    if (ans < y) ans = y;
}

int main() {
    static int T;
    scanf("%d", &T);
    while (T--) {
        ans = 0;
        scanf("%d%d%d", &E, &P, &n);
        for (int i = 0; i < n; i++) scanf("%d", e + i);
        for (int i = 0; i < n; i++) scanf("%d", p + i);
        for (int i = 0; i < (1 << n); i++)
            for (int j = 0; j <= 100; j++)
                for (int k = 0; k <= 100; k++)
                    dp[i][j][k] = -INF;
        dp[0][100][0] = 0;
        for (int i = 0; i < (1 << n); i++)
            for (int j = 100; j >= 0; j--)
                for (int k = 100; k >= 0; k--) {
                    if (dp[i][j][k] == -INF) continue;
                    if (j <= E) continue;
                    //printf("%d %d %d    %d\n", i, j, k, dp[i][j][k]);
                    //printf("     %d %d %d\n", i, j - E, std::max(k - P, 0));
                    inc(dp[i][j - E][std::max(k - P, 0)], dp[i][j][k] + 1);
                    for (int ii = 0; ii < n; ii++) if ((i & (1 << ii)) == 0 && std::max(k - P, 0) + p[ii] < 100)
                        inc(dp[i | (1 << ii)][std::min(j - E + e[ii], 100)][std::max(k - P, 0) + p[ii]], dp[i][j][k] + 1);
                }
        printf("%d\n", ans);
    }
    return 0;
}
