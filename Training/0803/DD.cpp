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
	while (ch = *_T++, ch < '0' || ch > '9') ;
	cnt = ch - '0';
	while (ch = *_T++, ch >= '0' && ch <= '9') cnt = cnt * 10 + ch - '0';
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
}/*
inline int getlca(int a, int b)
{
	while (top[a] != top[b])
		dep[top[a]] < dep[top[b]]
			? b = fa[top[b]]
			: a = fa[top[a]];
	return dep[a] < dep[b] ? a : b;
}*/
namespace LCA {
	std::vector<int>G[maxn];
	int dfn[maxn << 1], dep[maxn], pos[maxn], dfc;
	void clear(int n) {
		for (int i = 1; i <= n; i++) G[i].clear();
		dfc = 0;
	}	
	void link(int a, int b)
	{
		G[a].push_back(b);
		G[b].push_back(a);
	}
	void dfs(int u, int f) {
		dfn[++dfc] = u; pos[u] = dfc;
		for (int v : G[u]) 
			if (v == f) continue;
			else {
				dep[v] = dep[u] + 1;
				dfs(v, u);
				dfn[++dfc] = u;
			}
	}
	
	int st[23][maxn << 1], ln[maxn << 1];
	
	void build() {
		for (int i = 1; i <= dfc; i++) st[0][i] = dfn[i];
		for (int j = 1; j <= 20; j++) 
			for (int i = 1; i + (1 << j) - 1 <= dfc; i++)
				st[j][i] = dep[st[j - 1][i]] < dep[st[j - 1][i + (1 << (j - 1))]] ? 
							st[j - 1][i] : st[j - 1][i + (1 << (j - 1))];
		ln[0] = -1;
		for (int i = 1; i <= dfc; i++) ln[i] = ln[i >> 1] + 1;
	}
	int ask(int u, int v) {
		u = pos[u]; v = pos[v];
		if (u > v) std::swap(u, v);
		int k = ln[v - u + 1];
		u = st[k][u]; v = st[k][v - (1 << k) + 1];
		return dep[v] < dep[u] ? v : u;
	}
	
	
}
struct Opt {
	int type, u, v, w;
} op[maxn]; int opcnt;
int p[maxn], pcnt, st[maxn], lenw[maxn], val[maxn], sfa[maxn];
inline bool cmp(int a, int b)
{
	return dfn[a] < dfn[b];
}
void add_node(int x)
{
	if (!vis[x] && x) vis[p[++pcnt] = x] = 1, val[x] = 0;
}
inline bool isson(int a, int b)
{
	return dfn[a] <= dfn[b] && dfn[b] <= inv[a];
}
int cnt[1066], pp[maxn];
void my_sort()
{
	//std::sort(p + 1, p + pcnt + 1, cmp);
	//for (int i = 1; i <= pcnt; ++i) printf("%d ", dfn[p[i]]); puts("");
	memset(cnt, 0, 1024 << 2);
	for (int i = 1; i <= pcnt; ++i) cnt[dfn[p[i]] & 1023]++;
	for (int i = 1; i < 1024; ++i) cnt[i] += cnt[i - 1];
	for (int i = pcnt; i; --i) pp[cnt[dfn[p[i]] & 1023]--] = p[i];
	
	memset(cnt, 0, 1024 << 2);
	for (int i = 1; i <= pcnt; ++i) cnt[dfn[pp[i]] >> 10 & 1023]++;
	for (int i = 1; i < 1024; ++i) cnt[i] += cnt[i - 1];
	for (int i = pcnt; i; --i) p[cnt[dfn[pp[i]] >> 10 & 1023]--] = pp[i];
	
	//for (int i = 1; i <= pcnt; ++i) printf("%d ", dfn[p[i]]); puts("");
}
void build(int u, int v)
{
	pcnt = 0; int sttop = 0;
	add_node(u); add_node(v);
	for (int i = 1; i <= opcnt; ++i)
	{
		add_node(op[i].u);
		add_node(fa[op[i].u]);
		add_node(op[i].v);
		add_node(fa[op[i].v]);
	}
	my_sort();
	for (int i = 1; i < pcnt; ++i)
	{
		int lca = LCA::ask(p[i], p[i + 1]);
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
	for (int i = 1; i <= opcnt; ++i)
	{
		int opt = op[i].type, u = op[i].u, v = op[i].v, w = op[i].w;
		int lca = LCA::ask(u, v);
		if (opt == 1)
		{
			val[lca] += w;
			while (u != lca) val[u] += op[i].w, u = sfa[u];
			while (v != lca) val[v] += op[i].w, v = sfa[v];
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
}
void clear()
{
	for (int i = 1; i <= pcnt; ++i) vis[p[i]] = 0;
}
int main()
{
	fread(_S, 1, 1 << 25, stdin);
	int T = F();
	for (; T; --T)
	{
		int n = F(), m = F();
		memset(last, 0, (n + 1) * sizeof (Edge *)); ecnt = e;
		memset(son, 0, (n + 1) << 2); timer = 0; opcnt = 0;
		LCA::clear(n);
		for (int i = 1; i < n; ++i)
		{
			int a = F(), b = F();
			link(a, b); LCA::link(a, b);
		}
		dfs1(1); dfs2(1); LCA::dfs(1, 0);
		LCA::build();
		for (; m; --m)
		{
			int opt = F(), u = F(), v = F();
			if (opt <= 3)
			{
				int w = F();
				op[++opcnt] = (Opt) {opt, u, v, w};
			}
			else
			{
				build(u, v); ll ans = 0;
				int lca = LCA::ask(u, v);
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
					int k = F();
					ans = cabs(val[lca] - k);
					while (u != lca) cmin(ans, cabs(val[u] - k)), u = sfa[u];
					while (v != lca) cmin(ans, cabs(val[v] - k)), v = sfa[v];
				}
				printf("%d %lld\n", opt, ans);
				clear();
			}
		}
	}
	return 0;
}

