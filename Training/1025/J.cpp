#include <cstdio>
#include <set>

#define maxn 100010
struct Edge {
	Edge *next;
	int to;
} *last[maxn], e[maxn << 1], *ecnt = e;
inline void link(int a, int b)
{
	*++ecnt = (Edge) {last[a], b}; last[a] = ecnt;
	*++ecnt = (Edge) {last[b], a}; last[b] = ecnt;
}
int c[maxn];
int top[maxn], son[maxn], size[maxn], fa[maxn], dep[maxn], dfn[maxn], timer;
bool vis[maxn];
struct cmp {
	inline bool operator () (const int &a, const int &b) const
	{
		return dfn[a] < dfn[b];
	}
};
std::set<int, cmp> s[maxn];
void dfs1(int x)
{
	vis[x] = 1; size[x] = 1; dep[x] = dep[fa[x]] + 1; dfn[x] = ++timer;
	for (Edge *iter = last[x]; iter; iter = iter -> next)
		if (!vis[iter -> to])
		{
			fa[iter -> to] = x;
			dfs1(iter -> to);
			size[x] += size[iter -> to];
			size[son[x]] < size[iter -> to] ? son[x] = iter -> to : 0;
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
inline int getdis(int a, int b)
{
	int lca = getlca(a, b);
	return dep[a] + dep[b] - dep[lca] * 2;
}
int ans[maxn];
inline void insert(int col, int x)
{
	auto par = s[col].insert(x);
	auto iter = par.first;
	int pv = 0, nx = 0, l1 = 0, l2 = 0;
	if (iter != s[col].begin())
	{
		--iter;
		pv = *iter;
		++iter;
	}
	else pv = *--s[col].end();
	if (++iter != s[col].end()) nx = *iter;
	else nx = *s[col].begin();

	ans[col] -= getdis(pv, nx);
	ans[col] += getdis(pv, x);
	ans[col] += getdis(x, nx);
}
inline void remove(int col, int x)
{
	auto iter = s[col].find(x);
	int pv = 0, nx = 0, l1 = 0, l2 = 0;
	if (iter != s[col].begin())
	{
		--iter;
		pv = *iter;
		++iter;
	}
	else pv = *--s[col].end();
	if (++iter != s[col].end()) nx = *iter;
	else nx = *s[col].begin();

	ans[col] += getdis(pv, nx);
	ans[col] -= getdis(pv, x);
	ans[col] -= getdis(x, nx);
	s[col].erase(x);
}
int main()
{
	int n; scanf("%d", &n);
	for (int i = 1; i < n; ++i)
	{
		int a, b; scanf("%d%d", &a, &b);
		link(a, b);
	}
	dfs1(1); dfs2(1);
	for (int i = 1; i <= n; ++i)
	{
		scanf("%d", c + i);
		insert(c[i], i);
	}
	int m; scanf("%d", &m);
	for (; m; --m)
	{
		char opt[2]; scanf("%s", opt + 1);
		if (opt[1] == 'U')
		{
			int x, y; scanf("%d%d", &x, &y);
			remove(c[x], x);
			c[x] = y;
			insert(c[x], x);
		}
		else
		{
			int x; scanf("%d", &x);
			printf("%d\n", !s[x].size() ? -1 : ans[x] / 2);
		}
	}
	return 0;
}
/*
5
1 2
2 3
3 4
2 5
1 2 1 2 3
11
Q 1
Q 2
Q 3
Q 4
U 5 1
Q 1
U 3 2
Q 1
Q 2
U 5 4
Q 1
*/
