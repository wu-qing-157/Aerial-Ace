#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

#define maxn 50010
const int oo = 1e6;
struct Edge {
	Edge *next;
	int to, w;
} *last[maxn], e[maxn << 1], *ecnt = e;
inline void link(int a, int b, int w)
{
	*++ecnt = (Edge) {last[a], b, w}; last[a] = ecnt;
	*++ecnt = (Edge) {last[b], a, w}; last[b] = ecnt;
}
struct Seg {
	Seg *ls, *rs;
	int size;
	inline void update()
	{
		size = ls -> size + rs -> size;
	}
} mem[maxn * 60], *rt[maxn], *tot = mem, *null = mem;
inline Seg *new_node()
{
	*++tot = (Seg) {null, null, 0};
	return tot;
}
int size[maxn], fa[maxn], top[maxn], son[maxn], dep[maxn];
bool vis[maxn];
Seg *insert(Seg *x, int l, int r, int w)
{
	// printf("%d %d %d\n", l, r, w);
	Seg *nw = new_node();
	nw -> size = x -> size + 1;
	if (l == r) return nw;
	int mid = l + r >> 1;
	if (w <= mid)
	{
		nw -> ls = insert(x -> ls, l, mid, w);
		nw -> rs = x -> rs;
	}
	else
	{
		nw -> ls = x -> ls;
		nw -> rs = insert(x -> rs, mid + 1, r, w);
	}
	nw -> update();
	return nw;
}
void dfs1(int x)
{
	vis[x] = 1; size[x] = 1; dep[x] = dep[fa[x]] + 1;
	for (Edge *iter = last[x]; iter; iter = iter -> next)
		if (!vis[iter -> to])
		{
			fa[iter -> to] = x;
			rt[iter -> to] = insert(rt[x], 1, oo, iter -> w);
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
inline int query(int a, int b, int k)
{
	int lca = getlca(a, b);
	Seg *ra = rt[a], *rb = rt[b], *rc = rt[lca];
	int l = 1, r = oo;
	while (l < r)
	{
		int mid = l + r >> 1;
		// printf("%d %d %d\n", l, r, k);
		if (k > ra -> ls -> size + rb -> ls -> size - rc -> ls -> size * 2)
		{
			l = mid + 1;
			k -= ra -> ls -> size + rb -> ls -> size - rc -> ls -> size * 2;
			ra = ra -> rs;
			rb = rb -> rs;
			rc = rc -> rs;
		}
		else r = mid, ra = ra -> ls, rb = rb -> ls, rc = rc -> ls;
	}
	return l;
}
int main()
{
	int T; scanf("%d", &T);
	null -> ls = null -> rs = null;
	for (; T; --T)
	{
		int n; scanf("%d", &n); tot = mem; ecnt = e;
		for (int i = 1; i <= n; ++i) last[i] = 0;
		for (int i = 1; i < n; ++i)
		{
			int a, b, w; scanf("%d%d%d", &a, &b, &w);
			link(a, b, w);
		}
		rt[1] = null;
		dfs1(1); dfs2(1);
		int q; scanf("%d", &q);
		for (; q; --q)
		{
			int a, b, lca; scanf("%d%d", &a, &b);
			lca = getlca(a, b);
			int len = dep[a] + dep[b] - dep[lca] * 2;
			if (len & 1)
			{
				printf("%d.0\n", query(a, b, (len + 1) / 2));
			}
			else
			{
				int aa = query(a, b, len / 2), bb = query(a, b, len / 2 + 1);
				printf("%d.%d\n", (aa + bb) / 2, (aa + bb) % 2 == 0 ? 0 : 5);
			}
		}
	}
	return 0;
}
