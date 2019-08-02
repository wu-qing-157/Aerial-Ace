#include <cstdio>
#include <cstring>
#include <algorithm>

#define maxn 300010
#define cmin(_a, _b) (_a > (_b) ? _a = (_b) : 0)
struct Edge {
	Edge *next;
	int to;
} *last[maxn], e[maxn << 1], *ecnt = e;
inline void link(int a, int b)
{
	*++ecnt = (Edge) {last[a], b}; last[a] = ecnt;
	*++ecnt = (Edge) {last[b], a}; last[b] = ecnt;
}
int dp[maxn << 2], dmn[maxn << 2];
int n, k, p[maxn];
#define id(_x, _y) ((_x) * (k + 1) + (_y))
int fa[maxn], top[maxn], size[maxn], son[maxn], dep[maxn];
bool vis[maxn];
void dfs1(int x)
{
	vis[x] = 1; size[x] = 1; dep[x] = dep[fa[x]] + 1;
	for (Edge *iter = last[x]; iter; iter = iter -> next)
		if (!vis[iter -> to])
		{
			fa[iter -> to] = x;
			dfs1(iter -> to);
			size[x] += size[iter -> to];
			size[iter -> to] > size[son[x]] ? son[x] = iter -> to : 0;
		}
}
void dfs2(int x)
{
	vis[x] = 0; top[x] = son[fa[x]] == x ? top[fa[x]] : x;
	for (Edge *iter = last[x]; iter; iter = iter -> next)
		if (vis[iter -> to]) dfs2(iter -> to);
}
inline int getlca(int a, int b)
{
	while (top[a] != top[b])
		dep[top[a]] < dep[top[b]]
			? b = fa[top[b]]
			: a = fa[top[a]];
	return dep[a] < dep[b] ? a : b;
}
int main()
{
	while (scanf("%d%d", &n, &k) != EOF)
	{
		for (int i = 1; i <= n; ++i) scanf("%d", p + i);
		memset(son, 0, (n + 1) << 2);
		memset(last, 0, sizeof (last)); ecnt = e;
		for (int i = 1; i < n; ++i)
		{
			int a, b; scanf("%d%d", &a, &b);
			link(a, b);
		}
		dfs1(1); dfs2(1);
		memset(dp, 63, sizeof (dp));
		memset(dmn, 63, sizeof (dmn));
		dp[id(0, 0)] = 0;
		dmn[id(0, 0)] = 0;
		for (int i = 1; i <= n; ++i)
		{
			for (int j = 1; j <= k; ++j)
			{
				int t1 = dmn[id(i - 1, j - 1)] + dep[p[i]];
				int t2 = i > 1 ? dmn[id(i - 2, j - 1)] + dep[getlca(p[i - 1], p[i])] : 0x3f3f3f3f;
				dp[id(i, j)] = std::min(t1, t2);
			}
			for (int j = 0; j <= k; ++j)
				dmn[id(i, j)] = std::min(dmn[id(i - 1, j)], dp[id(i, j)]);
		}
		int ans = 0x7fffffff;
		for (int i = 1; i <= n; ++i)
			cmin(ans, dp[id(i, k)]);
		printf("%d\n", ans);
	}
	return 0;
}
/*
6 3
4 6 2 5 1 3
1 2
2 3
3 4
4 5
4 6
*/
