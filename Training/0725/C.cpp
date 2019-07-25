#include <cstdio>
#include <vector>

#define maxn 200010
struct Edge {
	Edge *next;
	int to;
} *last[maxn], e[maxn << 1], *ecnt = e;
inline void link(int a, int b)
{
	*++ecnt = (Edge) {last[a], b}; last[a] = ecnt;
	*++ecnt = (Edge) {last[b], a}; last[b] = ecnt;
}
long long ans;
int cnt[maxn], son[maxn], size[maxn], top[maxn], dep[maxn], inv[maxn];
int dfn[maxn], pos[maxn], timer;
bool vis[maxn];
std::vector<int> v[maxn];
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
	vis[x] = 0; top[x] = son[fa[x]] == x ? top[fa[x]] : x; dfn[x] = ++timer; pos[timer] = x;
	for (Edge *iter = last[x]; iter; iter = iter -> next)
		if (iter -> to != fa) dfs2(iter -> to);
	inv[x] = timer;
}
int getlca(int a, int b)
{
	while (top[a] != top[b])
		dep[top[a]] < dep[top[b]] ? b = fa[top[b]] : a = fa[top[a]];
	return dep[a] < dep[b] ? a : b;
}
inline int cmp(int x, int y) {return dfn[x] < dfn[y];}
int st[maxn], sttop, ssize[maxn];
bool vis[maxn], imp[maxn];
inline bool isson(int a, int b)
{
	return dfn[a] <= dfn[b] && dfn[b] <= inv[a];
}
int main()
{
	int n;
	while (scanf("%d", &n) != EOF)
	{
		int tot = 0;
		for (int i = 1; i <= n; ++i) scanf("%d", c + i), v[c[i]].push_back(i);
		for (int i = 1; i < n; ++i)
		{
			int a, b; scanf("%d%d", &a, &b);
			link(a, b);
		}
		ans = 0;
		dfs1(1);
		dfs2(1);
		for (int i = 1; i <= n; ++i)
			if (v[i].size())
			{
				ans += 1ll * n * (n - 1) / 2;
				std::sort(v[i].begin(), v[i].end(), cmp);
				for (int it : v[i]) vis[it] = imp[it] = 1;
				int p = v[i].size();
				for (int j = 0; j < p - 1; ++j)
				{
					int lca = getlca(v[i][j], v[i][j + 1]);
					if (!vis[lca])
					{
						vis[lca] = 1; v[i].push_back(lca);
					}
				}
				std::sort(v[i].begin(), v[i].end(), cmp);
				st[++top] = v[i][0];
				for (int j = 1; j < v[i].size(); ++j)
				{
					while (!isson(st[top], v[i][j])) --top;
					st[++top] = v[i][j]; ssize[v[i][j]] = size[v[i][j]];
				}
				int tot = n;
				for (int j = v[i].size() - 1; j; --j)
				{
					int now = v[i][j];
					if (imp[now])
					{
						tot -= ssize[now];
						ans -= 1ll * ssize[now] * (ssize[now])
					}
				}
				ans -= 1ll * tot * (tot - 1) / 2;
			}
		printf("Case #%d: %lld\n", ans);
	}
	return 0;
}
