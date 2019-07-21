#include <cstdio>

#define maxn 60
const int mod = 10003;
int dp[maxn][maxn][maxn];
int c2(int x) {
	return 1ll * x * (x - 1) / 2 % mod;
}
int main()
{
freopen("rooks.in", "r", stdin);
freopen("rooks.out", "w", stdout);
	int m, n, K, ans = 0; scanf("%d%d%d", &n, &m, &K);
	if (K > 2 * m || K > 2 * n) {
		puts("0");
		return 0;
	}
	dp[0][0][0] = 1;
	for (int i = 0; i < n; ++i)
			for (int k = 0; k <= m; k++)
				for (int l = 0; k + l <= m; l++) {
					(dp[i + 1][k][l] += dp[i][k][l]) %= mod;
					if (m - k - l > 0) (dp[i + 1][k][l + 1] += 1ll * dp[i][k][l] * (m - k - l)) %= mod;
					if (l > 0) (dp[i + 1][k + 1][l - 1] += 1ll * dp[i][k][l] * l) %= mod;
					if (m - k - l >= 2) (dp[i + 1][k][l + 2] += 1ll * dp[i][k][l] * c2(m - k - l)) %= mod;
					if (m - k - l > 0 && l > 0) (dp[i + 1][k + 1][l] += 1ll * dp[i][k][l] * l * (m - k - l)) %= mod;
					if (l >= 2) (dp[i + 1][k + 2][l - 2] += 1ll * dp[i][k][l] * c2(l)) %= mod;
				}
	for (int k = 0; k <= m; k++) for (int l = 0; k + l <= m; l++) if (2 * k + l == K) (ans += dp[n][k][l]) %= mod;
	printf("%d\n", ans);
	return 0;
}
