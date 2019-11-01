#include <cstdio>
#include <cstring>
#include <algorithm>

#define maxn 100010
struct Edge {
	Edge *next;
	int to, w;
} *last[maxn], e[maxn << 1], *ecnt = e;
inline void link(int a, int b, int w)
{
	*++ecnt = (Edge) {last[a], b, w}; last[a] = ecnt;
	*++ecnt = (Edge) {last[b], a, w}; last[b] = ecnt;
}
int fa[maxn], size[maxn], son[maxn], top[maxn], dep[maxn], dis[maxn];
int dfn[maxn], inv[maxn], timer, pos[maxn];
bool vis[maxn];
void dfs1(int x)
{
	size[x] = 1; vis[x] = 1; dep[x] = dep[fa[x]] + 1;
	pos[dfn[x] = ++timer] = x;
	for (Edge *iter = last[x]; iter; iter = iter -> next)
		if (!vis[iter -> to])
		{
			fa[iter -> to] = x;
			dis[iter -> to] = dis[x] + iter -> w;
			dfs1(iter -> to);
			size[x] += size[iter -> to];
			size[iter -> to] > size[son[x]] ? son[x] = iter -> to : 0;
		}
	inv[x] = timer;
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
	return dis[a] + dis[b] - dis[lca] * 2;
}
struct Seg {
	int a, b, len;
	inline bool operator < (const Seg &that) const {return len > that.len;}
	inline Seg operator + (const Seg &that) const
	{
		if (len < 0) return that;
		if (that.len < 0) return *this;
		Seg p[6];
		p[0] = *this; p[1] = that;
		p[2] = (Seg) {a, that.a, getdis(a, that.a)};
		p[3] = (Seg) {a, that.b, getdis(a, that.b)};
		p[4] = (Seg) {b, that.a, getdis(b, that.a)};
		p[5] = (Seg) {b, that.b, getdis(b, that.b)};
		std::sort(p, p + 6);
		return p[0];
	}
} tr[20][maxn];
int Log[maxn];
void build(int n)
{
	Log[0] = -1;
	for (int i = 1; i <= n; ++i)
	{
		Log[i] = Log[i >> 1] + 1;
		tr[0][i] = (Seg) {pos[i], pos[i], 0};
	}
	for (int j = 1; (1 << j) <= n; ++j)
		for (int i = 1; i + (1 << j) - 1 <= n; ++i)
			tr[j][i] = tr[j - 1][i] + tr[j - 1][i + (1 << (j - 1))];
}
struct edge {int a, b;} ee[maxn];
Seg ret; int ql, qr;
void query(int l, int r)
{
	int k = Log[r - l + 1];
	ret = tr[k][l] + tr[k][r - (1 << k) + 1];
}
int main()
{
	int T; scanf("%d", &T);
	for (; T; --T)
	{
		int n, m; scanf("%d%d", &n, &m);
		timer = 0;
		memset(last, 0, sizeof (Edge *) * (n + 1)); ecnt = e;
		memset(son, 0, (n + 1) << 2);
		for (int i = 1; i < n; ++i)
		{
			int a, b, w; scanf("%d%d%d", &a, &b, &w);
			link(a, b, w);
			ee[i] = (edge) {a, b};
		}
		dfs1(1); dfs2(1);
		for (int i = 1; i < n; ++i) if (dep[ee[i].a] < dep[ee[i].b]) std::swap(ee[i].a, ee[i].b);
		build(n);
		for (int i = 1; i <= m; ++i)
		{
			int u, v; scanf("%d%d", &u, &v);
			int a = ee[u].a, b = ee[v].a;
			if (dfn[a] > dfn[b]) std::swap(a, b);
			Seg col[3]; int ans = 0;
			if (dfn[a] <= dfn[b] && dfn[b] <= inv[a])
			{
				ql = 1; qr = dfn[a] - 1; ret.len = -0x7fffffff;
				if (ql <= qr) query(ql, qr);
				col[0] = ret;

				ql = dfn[a]; qr = dfn[b] - 1; ret.len = -0x7fffffff;
				if (ql <= qr) query(ql, qr);
				col[1] = ret;
				
				ql = dfn[b]; qr = inv[b]; ret.len = -0x7fffffff;
				if (ql <= qr) query(ql, qr);
				col[2] = ret;
				
				ql = inv[b] + 1; qr = inv[a]; ret.len = -0x7fffffff;
				if (ql <= qr) query(ql, qr);
				col[1] = col[1] + ret;
				
				ql = inv[a] + 1; qr = n; ret.len = -0x7fffffff;
				if (ql <= qr) query(ql, qr);
				col[0] = col[0] + ret;
			}
			else
			{
				ql = 1; qr = dfn[a] - 1; ret.len = -0x7fffffff;
				if (ql <= qr) query(ql, qr);
				col[0] = ret;

				ql = dfn[a]; qr = inv[a]; ret.len = -0x7fffffff;
				if (ql <= qr) query(ql, qr);
				col[1] = ret;
				
				ql = inv[a] + 1; qr = dfn[b] - 1; ret.len = -0x7fffffff;
				if (ql <= qr) query(ql, qr);
				col[0] = col[0] + ret;
				
				ql = dfn[b]; qr = inv[b]; ret.len = -0x7fffffff;
				if (ql <= qr) query(ql, qr);
				col[2] = ret;
				
				ql = inv[b] + 1; qr = n; ret.len = -0x7fffffff;
				if (ql <= qr) query(ql, qr);
				col[0] = col[0] + ret;
			}
			ans = std::max({col[0].len, col[1].len, col[2].len});
			printf("%d\n", ans);
		}
	}
	return 0;
}
