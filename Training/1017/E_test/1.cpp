#include <cstdint>
#include <cstdio>
#include <algorithm>

const int N = 1e5 + 10, INF = INT32_MAX;
int n, m, l[N], r[N], c[N], dp[N], ans;

int main() {
    static int T;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; cas++) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++) scanf("%d%d", l + i, r + i);
        for (int i = 1; i <= m; i++) scanf("%d", c + i);
        std::sort(c + 1, c + m + 1);
        c[0] = -INF;
        dp[0] = 0;
        ans = 0;
        for (int i = 1; i <= m; i++) {
            dp[i] = INF;
            for (int j = 0; j < i; j++) {
                int cnt = 0;
                for (int k = 1; k <= n; k++)
                    cnt += l[k] > c[j] && l[k] <= c[i] && r[k] >= c[i];
                dp[i] = std::min(dp[i], dp[j] + cnt - 1);
            }
            ans = std::max(ans, n - dp[i]);
            //printf("%d ", dp[i]);
        }
        //puts("");
        if (ans > n) printf("Case #%d: IMPOSSIBLE!\n", cas);
        else printf("Case #%d: %d\n", cas, ans);
    }
    return 0;
}
