#include <cstdio>

using number = long double;

const int N = 1e2;
number dp[N];
int n, m;
number ans;

int main() {
    dp[1] = 0;
    for (int i = 2; i < N; i++) {
        dp[i] = 1;
        for (int j = 1; j < i; j++)
            dp[i] += dp[j];
        dp[i] /= i;
    }
    dp[1] = 1;
    static int T;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; cas++) {
        scanf("%d", &n);
        printf("Case #%d: %.6f ", cas, (double) dp[n]);
        scanf("%d", &m);
        ans = 0;
        for (int i = 1; i <= m; i++) ans += dp[i];
        ans /= m;
        printf("%.6f\n", (double) ans);
    }
    return 0;
}
