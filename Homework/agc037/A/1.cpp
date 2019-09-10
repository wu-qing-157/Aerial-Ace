#include <cstdio>
#include <cstring>
#include <algorithm>

const int N = 2e5 + 10;
char s[N];
int dp[N][2], n;

int main() {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    memset(dp, -1, sizeof dp);
    dp[1][0] = dp[2][1] = 1;
    for (int i = 1; i <= n; i++) {
        if (dp[i][0] != -1) {
            dp[i + 2][1] = std::max(dp[i + 2][1], dp[i][0] + 1);
            if (s[i + 1] != s[i]) dp[i + 1][0] = std::max(dp[i + 1][0], dp[i][0] + 1);
        }
        if (dp[i][1] != -1) {
            dp[i + 1][0] = std::max(dp[i + 1][0], dp[i][1] + 1);
            if (s[i + 2] != s[i] || s[i + 1] != s[i - 1]) dp[i + 2][1] = std::max(dp[i + 2][1], dp[i][1] + 1);
        }
    }
    printf("%d\n", std::max(dp[n][0], dp[n][1]));
    return 0;
}
