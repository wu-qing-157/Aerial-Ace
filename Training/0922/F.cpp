#include <cstdio>
#include <vector>

#define maxn 35010
const int mod = 1e9 + 7;
std::vector<int> e[maxn];
int f[maxn][65][2], a[maxn];
void dfs(int x, int fa)
{
	int ret[6][2], prd[6], deg = 0;
	for (int to : e[x]) if (to != fa)
	{
		dfs(to, x);
		ret[deg][0] = 0;
		ret[deg][1] = 0;
		prd[deg] = 0;
		for (int S = 0, _ = 1 << (e[to].size() - 1); S < _; ++S)
		{
			bool flag = 1; int sum = 0;
			for (int i = 0, j = 0; i < e[to].size(); ++i)
				if (e[to][i] != x)
				{
					if (S & (1 << j)) sum += a[e[to][i]] > 0 ? a[e[to][i]] : 0;
					++j;
				}
			if (a[x] + a[to] + sum <= 0) (prd[deg] += f[to][S][1]) %= mod;
			(ret[deg][1] += f[to][S][1]) %= mod;
			(ret[deg][0] += f[to][S][0]) %= mod;
		}
		if (a[x] + a[to] > 0) prd[deg] = 0;
		++deg;
	}
	for (int S = 0, _ = 1 << deg; S < _; ++S)
	{
		f[x][S][0] = 1;
		f[x][S][1] = 1;
		int sum = 0, j = 0, p = 0, maxx = -mod;
		for (int it : e[x])
			if (it != fa)
			{
				if (S & (1 << j))
				{
					sum += a[it] > 0 ? a[it] : 0;
					maxx < a[it] ? maxx = a[it] : 0;
					++p;
				}
				++j;
			}
		if (((a[x] + maxx > 0) || (sum != 0 && a[x] + sum > 0)) && p) f[x][S][1] = 0;
		for (int i = 0; i < deg; ++i)
			if (S & (1 << i))
				f[x][S][0] = 1ll * f[x][S][0] * ret[i][1] % mod,
				f[x][S][1] = 1ll * f[x][S][1] * prd[i] % mod;
			else
				f[x][S][0] = 1ll * f[x][S][0] * ret[i][0] % mod,
				f[x][S][1] = 1ll * f[x][S][1] * ret[i][0] % mod;
	}
}
int main()
{
	int T; scanf("%d", &T);
	for (; T; --T)
	{
		int n, x; scanf("%d%d", &n, &x);
		for (int i = 1; i <= n; ++i) scanf("%d", a + i), a[i] -= x, e[i].clear();
		for (int i = 1; i < n; ++i)
		{
			int a, b; scanf("%d%d", &a, &b);
			e[a].push_back(b);
			e[b].push_back(a);
		}
		dfs(1, 0);
		int ans = 0;
		for (int S = 0, _ = 1 << e[1].size(); S < _; ++S)
			(ans += f[1][S][0]) %= mod,
			(ans += f[1][S][1]) %= mod;
		printf("%d\n", ans);
	}
	return 0;
}
