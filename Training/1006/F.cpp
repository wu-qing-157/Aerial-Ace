#include <cstdio>

#define maxn 250010
struct Seg {
	Seg *ls, *rs;
	int size;
} mem[maxn * 60], *tot = mem, *rt[maxn];
struct Edge {
	Edge *next;
	int to;
} *last[maxn], e[maxn << 1], *ecnt = e;
inline void link(int a, int b)
{
	*++ecnt = (Edge) {last[a], b}; last[a] = ecnt;
	*++ecnt = (Edge) {last[b], a}; last[b] = ecnt;
}
int dfn[maxn], pos[maxn], timer, v[maxn];
int son[maxn], size[maxn], top[maxn], dep[maxn], fa[maxn];
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
			size[son[x]] < size[iter -> to] ? son[x] = iter -> to : 0;
		}
}
void dfs2(int x)
{
	vis[x] = 0; dfn[x] = ++timer; pos[timer] = x;
	top[x] = son[fa[x]] == x ? top[fa[x]] : x;
	for (Edge *iter = last[x]; iter; iter = iter -> next)
		if (vis[iter -> to]) dfs2(iter -> to);
}
int getlca(int a, int b)
{
	while (top[a] != top[b])
		dep[top[a]] < dep[top[b]]
			? b = fa[top[b]]
			: a = fa[top[a]];
	return dep[a] < dep[b] ? a : b;
}
Seg *insert(Seg *ls, int l, int r, int v)
{
	Seg *nw = ++tot; nw -> size = ls -> size + 1;
	if (l == r) return nw;
	int mid = l + r >> 1;
	if (v <= mid)
	{
		nw -> ls = insert(ls -> ls, l, mid, v);
		nw -> rs = ls -> rs;
	}
	else
	{
		nw -> ls = ls -> ls;
		nw -> rs = insert(ls -> rs, mid + 1, r, v);
	}
	return nw;
}
int main()
{
	int n, q; scanf("%d%d", &n, &q);
	rt[0] = mem; mem -> ls = mem -> rs = mem;
	for (int i = 1; i <= n; ++i) scanf("%d", v + i);
	for (int i = 1; i < n; ++i)
	{
		int a, b; scanf("%d%d", &a, &b);
		link(a, b);
	}
	dfs1(1);
	dfs2(1);
	for (int i = 1; i <= n; ++i)
		rt[pos[i]] = insert(rt[fa[pos[i]]], 1, n, v[pos[i]]);
	for (int i = 1; i <= q; ++i)
	{
		int s, e, lca; scanf("%d%d", &s, &e);
		lca = getlca(s, e);
		Seg *n1 = rt[s], *n2 = rt[e], *n3 = rt[lca], *n4 = rt[fa[lca]];
		int left = 1, right = n, num = dep[s] + dep[e] - dep[lca] - dep[fa[lca]];
		while (left < right)
		{
			int mid = left + right >> 1;
			if (n1 -> ls -> size + n2 -> ls -> size - n3 -> ls -> size - n4 -> ls -> size > num / 2)
			{
				right = mid;
				n1 = n1 -> ls;
				n2 = n2 -> ls;
				n3 = n3 -> ls;
				n4 = n4 -> ls;
			}
			else
			{
				left = mid + 1;
				n1 = n1 -> rs;
				n2 = n2 -> rs;
				n3 = n3 -> rs;
				n4 = n4 -> rs;
			}
		}
		if (n1 -> size + n2 -> size - n3 -> size - n4 -> size > num / 2) printf("%d\n", left);
		else puts("-1");
	}
	return 0;
}
