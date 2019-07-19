#include <cstdio>

const int N = 51, K = 3001;
int n, x, y, k;
double p, sing, dp[K][N][N];

int main() {
    freopen("assessment.in", "r", stdin);
    static int T;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; cas++) {
        scanf("%d%lf%d%d%d", &n, &p, &x, &y, &k);
        sing = p / (n - 1), x++, y++;
        if (n == 1) {
            printf("Case %d: %.5f\n", cas, 1.);
            continue;
        }
        if (x == y) {
            for (int i = 0; i <= k; i++)
                for (int j = 1; j <= n; j++)
                    dp[i][j][j] = i == 0 && j == x;
            for (int i = 0; i < k; i++)
                for (int j = 1; j <= n; j++) {
                    double pro = dp[i][j][j], s = sing * dp[i][j][j];
                    if (j != 1) dp[i + 1][j - 1][j - 1] += s, pro -= s;
                    if (j != n) dp[i + 1][j + 1][j + 1] += s, pro -= s;
                    dp[i + 1][j][j] += pro;
                }
            printf("Case %d: %.5f\n", cas, (double) dp[k][x][x]);
        } else {
            for (int i = 0; i <= k; i++)
                for (int x1 = 1; x1 <= n; x1++)
                    for (int x2 = 1; x2 <= n; x2++)
                        dp[i][x1][x2] = 0;
            dp[0][x][y] = 1;
            for (int i = 0; i < k; i++)
                for (int x1 = 1; x1 <= n; x1++)
                    for (int y1 = 1; y1 <= n; y1++) if (x1 != y1) {
                        double pro = dp[i][x1][y1], s = sing * dp[i][x1][y1];
                        bool b1 = x1 == y1 + 1, b2 = y1 == x1 + 1;
                        if (!b1) {
                            if (x1 != 1) dp[i + 1][x1 - 1][y1] += s, pro -= s;
                            if (y1 != n) dp[i + 1][x1][y1 + 1] += s, pro -= s;
                        }
                        if (!b2) {
                            if (x1 != n) dp[i + 1][x1 + 1][y1] += s, pro -= s;
                            if (y1 != 1) dp[i + 1][x1][y1 - 1] += s, pro -= s;
                        }
                        if (b1 || b2) dp[i + 1][y1][x1] += s, pro -= s;
                        dp[i + 1][x1][y1] += pro;
                    }
            /*
            for (int i = 0; i <= k; i++)
                for (int x1 = 1; x1 <= n; x1++)
                    for (int x2 = 1; x2 <= n; x2++)
                        printf("%d %d %d     %f\n", i, x1, x2, dp[i][x1][x2]);
                        */
            printf("Case %d: %.5f\n", cas, (double) dp[k][y][x]);
        }
    }
    return 0;
}
