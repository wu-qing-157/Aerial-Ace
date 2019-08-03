#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

#define maxn 500010
#define cabs(_x) ((_x) < 0 ? (-(_x)) : (_x))
#define cmin(_a, _b) (_a > (_b) ? _a = (_b) : 0)
#define cmax(_a, _b) (_a < (_b) ? _a = (_b) : 0)
typedef long long ll;
struct Edge {
	Edge *next;
	int to;
} *last[maxn], e[maxn << 1], *ecnt = e;
inline void link(int a, int b)
{
	*++ecnt = (Edge) {last[a], b}; last[a] = ecnt;
	*++ecnt = (Edge) {last[b], a}; last[b] = ecnt;
}
char _S[1 << 25], *_T = _S;
inline int F()
{
	char ch; int cnt = 0;
	while (ch = getchar(), ch < '0' || ch > '9') ;
	cnt = ch - '0';
	while (ch = getchar(), ch >= '0' && ch <= '9') cnt = cnt * 10 + ch - '0';
	return cnt;
}
bool vis[maxn];
int top[maxn], son[maxn], size[maxn], fa[maxn], dep[maxn], dfn[maxn], pos[maxn], timer, inv[maxn];
void dfs1(int x)
{
	vis[x] = 1; size[x] = 1; dep[x] = dep[fa[x]] + 1;
	dfn[x] = ++timer; pos[timer] = x;
	for (Edge *iter = last[x]; iter; iter = iter -> next)
		if (!vis[iter -> to])
		{
			fa[iter -> to] = x;
			dfs1(iter -> to);
			size[x] += size[iter -> to];
			size[son[x]] < size[iter -> to] ? son[x] = iter -> to : 0;
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
struct Opt {
	int type, u, v, w;
} op[maxn]; int opcnt;
int p[maxn], pcnt, st[maxn], lenw[maxn];
ll val[maxn];
int sfa[maxn];
inline bool cmp(int a, int b)
{
	return dfn[a] < dfn[b];
}
void add_node(int x)
{
	if (!vis[x] && x) vis[p[++pcnt] = x] = 1;
}
inline bool isson(int a, int b)
{
	return dfn[a] <= dfn[b] && dfn[b] <= inv[a];
}
int cnt[1066], pp[maxn];
void my_sort()
{
	std::sort(p + 1, p + pcnt + 1, cmp);
}
void build()
{
	int sttop = 0;
	my_sort();
	for (int i = 1; i < pcnt; ++i)
	{
		int lca = getlca(p[i], p[i + 1]);
		add_node(lca);
	}
	my_sort();
	sfa[st[++sttop] = p[1]] = 0;
	lenw[p[1]] = 0;
	for (int i = 2; i <= pcnt; ++i)
	{
		while (!isson(st[sttop], p[i])) --sttop;
		lenw[p[i]] = dep[p[i]] - dep[st[sttop]];
		sfa[p[i]] = st[sttop];
		st[++sttop] = p[i];
	}
}
void clear()
{
	for (int i = 1; i <= pcnt; ++i) vis[p[i]] = 0;
}
int main()
{
	//fread(_S, 1, 1 << 25, stdin);
	int T = F();
	for (; T; --T)
	{
		int n = F(), m = F();
		memset(last, 0, (n + 1) * sizeof (Edge *)); ecnt = e;
		memset(son, 0, (n + 1) << 2); timer = 0; opcnt = 0;
		memset(val, 0, (n + 1) << 3); pcnt = 0;
		memset(lenw, 0, (n + 1) << 2);
		for (int i = 1; i < n; ++i)
		{
			int a = F(), b = F();
			link(a, b);
		}
		dfs1(1); dfs2(1);
		for (int i = 1; i <= m; ++i)
		{
			int opt = F(), u = F(), v = F(), w = 0, lca;
			if (opt <= 3 || opt == 7) w = F();
			op[i] = (Opt) {opt, u, v, w};
			add_node(u); add_node(v);
			add_node(fa[u]); add_node(fa[v]);
			lca = getlca(u, v);
			add_node(lca); add_node(fa[lca]);
		}
		build();
		for (int i = 1; i <= m; ++i)
		{
			int opt = op[i].type, u = op[i].u, v = op[i].v, w = op[i].w;
			if (opt <= 3)
			{
				int lca = getlca(u, v);
				if (opt == 1)
				{
					val[lca] += w;
					while (u != lca) val[u] += w, u = sfa[u];
					while (v != lca) val[v] += w, v = sfa[v];
				}
				if (opt == 2)
				{
					val[lca] ^= w;
					while (u != lca) val[u] ^= w, u = sfa[u];
					while (v != lca) val[v] ^= w, v = sfa[v];
				}
				if (opt == 3)
				{
					val[lca] >= w ? val[lca] -= w : 0;
					while (u != lca) val[u] >= w ? val[u] -= w : 0, u = sfa[u];
					while (v != lca) val[v] >= w ? val[v] -= w : 0, v = sfa[v];
				}
			}
			else
			{
				ll ans = 0;
				int lca = getlca(u, v);
				if (opt == 4)
				{
					ans = val[lca];
					while (u != lca) ans += 1ll * val[u] * lenw[u], u = sfa[u];
					while (v != lca) ans += 1ll * val[v] * lenw[v], v = sfa[v];
				}
				if (opt == 5)
				{
					ans = val[lca];
					while (u != lca) ans ^= val[u] * (lenw[u] % 2), u = sfa[u];
					while (v != lca) ans ^= val[v] * (lenw[v] % 2), v = sfa[v];
				}
				if (opt == 6)
				{
					int maxx = val[lca], minn = val[lca];
					while (u != lca) cmax(maxx, val[u]), cmin(minn, val[u]), u = sfa[u];
					while (v != lca) cmax(maxx, val[v]), cmin(minn, val[v]), v = sfa[v];
					ans = maxx - minn;
				}
				if (opt == 7)
				{
					ans = cabs(val[lca] - w);
					while (u != lca) cmin(ans, cabs(val[u] - w)), u = sfa[u];
					while (v != lca) cmin(ans, cabs(val[v] - w)), v = sfa[v];
				}
				printf("%d %lld\n", opt, ans);
			}
		}
		clear();
	}
	return 0;
}
