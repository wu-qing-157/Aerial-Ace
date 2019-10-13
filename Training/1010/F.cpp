#include <cstdio>
#include <vector>
#include <cstring>

#define maxn 300010
const int mod = 998244353;
bool vis[maxn];
int rem, pw[maxn << 1], ans, dep[maxn];
std::vector<int> e[maxn];
inline void link(int a, int b)
{
	e[a].push_back(b);
	e[b].push_back(a);
}
void dfs(int x, int fa)
{
	vis[x] = 1; dep[x] = dep[fa] + 1;
	for (int it : e[x])
		if (it != fa)
		{
			if (!vis[it]) dfs(it, x);
			else if (dep[x] > dep[it])
			{
				int len = dep[x] - dep[it] + 1;
				// printf("%d\n", len);
				ans = 1ll * ans * (pw[len] + mod - 1) % mod;
				rem -= len;
			}
		}
}
int main()
{
	int n, m; pw[0] = 1;
	for (int i = 1; i < (maxn << 1); ++i) pw[i] = pw[i - 1] * 2 % mod;
	while (scanf("%d%d", &n, &m) != EOF)
	{
		for (int i = 1; i <= n; ++i) e[i].clear();
		for (int i = 1; i <= m; ++i)
		{
			int a, b; scanf("%d%d", &a, &b);
			link(a, b);
		}
		memset(vis, 0, (n + 1) );
		rem = m; ans = 1;
		for (int i = 1; i <= n; ++i)
			if (!vis[i])
				dfs(i, 0);
		ans = 1ll * ans * pw[rem] % mod;
		printf("%d\n", ans);
	}
	return 0;
}
