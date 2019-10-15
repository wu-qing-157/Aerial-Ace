#include <cstdio>

#define maxn 100010
#define cmin(_a, _b) (_a > (_b) ? _a = (_b) : 0)
int d[maxn][2];
const int mod = 998244353;
int main()
{
	int T; scanf("%d", &T);
	for (; T; --T)
	{
		int n, m; scanf("%d%d", &n, &m);
		for (int i = 0; i <= n; ++i) d[i][0] = d[i][1] = 0;
		for (int i = 1; i <= m; ++i)
		{
			int l, r, t; scanf("%d%d%d", &l, &r, &t);
			d[l][t - 2] += 1;
			d[r + 1][t - 2] -= 1;
		}
		int ans = 1, p[2] = {0x7fffffff, 0x7fffffff};
		for (int i = 1; i <= n; ++i)
		{
			d[i][0] += d[i - 1][0];
			cmin(p[0], d[i][0]);
			d[i][1] += d[i - 1][1];
			cmin(p[1], d[i][1]);
		}
		for (int i = 1; i <= p[0]; ++i) ans = 1ll * ans * 2 % mod;
		for (int i = 1; i <= p[1]; ++i) ans = 3ll * ans % mod;
		printf("%d\n", ans);
	}
	return 0;
}
