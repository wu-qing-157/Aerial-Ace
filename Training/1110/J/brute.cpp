#include <cstdio>
#include <algorithm>

char s[1100];
int n, k, g1, g2, g3, dp[1100][1100], ans;

int main() {
    scanf("%d%d%d%d%d%s", &n, &k, &g1, &g2, &g3, s + 1);
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= k; j++)
            dp[i][j] = dp[i - 1][j];
        if (s[i] == '.') {
            for (int j = 1; j <= k; j++)
                dp[i][j] = std::max(dp[i][j], dp[i - 1][j - 1] + g1);
        }
        if (i >= 2 && s[i] == '.' && s[i - 1] == '.') {
            for (int j = 0; j <= k; j++)
                dp[i][j] = std::max(dp[i][j], dp[i - 2][j] + g2);
        }
        if (i >= 3 && s[i] == '.' && s[i - 1] == '#' && s[i - 2] == '.') {
            for (int j = 0; j <= k; j++)
                dp[i][j] = std::max(dp[i][j], dp[i - 3][k] + g3);
        }
    }
    for (int j = 0; j <= k; j++) ans = std::max(ans, dp[n][k]]);
    printf("%d\n", ans);
    return 0;
}
