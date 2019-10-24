#include <cstdio>
#include <vector>
#include <cstring>

#define maxn 100010
std::vector<int> e[maxn];
int fa[maxn][20], dep[maxn], dfn[maxn], inv[maxn], timer;
int size[maxn];
bool vis[maxn];
void dfs(int x)
{
	for (int i = 1; i <= 19; ++i)
		fa[x][i] = fa[fa[x][i - 1]][i - 1];
	vis[x] = 1; dfn[x] = ++timer; size[x] = 1;
	for (int it : e[x])
		if (!vis[it])
		{
			fa[it][0] = x;
			dep[it] = dep[x] + 1;
			dfs(it);
			size[x] += size[it];
		}
	inv[x] = timer;
}
inline int jump(int x, int d)
{
	for (int k; d; d -= 1 << k)
	{
		k = __builtin_ctz(d);
		x = fa[x][k];
	}
	return x;
}
int main()
{
	int T; scanf("%d", &T);
	for (int Cas = 1; Cas <= T; ++Cas)
	{
		int n, q, r; scanf("%d%d%d", &n, &q, &r);
		timer = 0;
		memset(vis, 0, (n + 1));
		for (int i = 1; i <= n; ++i) e[i].clear();
		for (int i = 1; i < n; ++i)
		{
			int a, b; scanf("%d%d", &a, &b);
			e[a].push_back(b);
			e[b].push_back(a);
		}
		dfs(1);
		printf("Case #%d:\n", Cas);
		for (; q; --q)
		{
			int op, x; scanf("%d%d", &op, &x);
			if (!op) r = x;
			else
			{
				if (dfn[x] <= dfn[r] && dfn[r] <= inv[x] && r != x)
				{
					int p = jump(r, dep[r] - dep[x] - 1);
					printf("%d\n", n - size[p]);
				}
				else if (r == x) printf("%d\n", n);
				else printf("%d\n", size[x]);
			}
		}
	}
	return 0;
}
