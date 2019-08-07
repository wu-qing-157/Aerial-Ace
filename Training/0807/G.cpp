#include <cstdio>

#define maxn 100010
const int mod = 1e9 + 7;
int ch[maxn][2], ty[maxn];
int dp[maxn][2][2];
void dfs(int x)
{
	if (!x) return ;
	dfs(ch[x][0]);
	dfs(ch[x][1]);
	for (int a1 = 0; a1 < 2; ++a1)
		for (int a2 = 0; a2 < 2; ++a2)
			for (int b1 = 0; b1 < 2; ++b1)
				for (int b2 = 0; b2 < 2; ++b2)
				{
					int c1 = !(a1 & b1), c2 = !(a2 & b2);
					if (ty[x] != -1) c2 = ty[x];
					dp[x][c1][c2] = (dp[x][c1][c2] + 1ll * dp[ch[x][0]][a1][a2] * dp[ch[x][1]][b1][b2]) % mod;
				}
}
int main()
{
	int n; scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		scanf("%d%d%d", &ch[i][0], &ch[i][1], &ty[i]);
	dp[0][0][0] = dp[0][1][1] = 1;
	dfs(1);
	int ans = (dp[1][0][1] + dp[1][1][0]) % mod;
	printf("%d\n", ans);
	return 0;
}
