#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <set>

#define maxn 100010
#define dmax(_a, _b) ((_a) > (_b) ? (_a) : (_b))
#define cmax(_a, _b) (_a < (_b) ? _a = (_b) : 0)
typedef long long ll;
struct Edge {
	Edge *next;
	int to, w, id;
} *last[maxn], e[maxn << 1], *ecnt = e;
inline void link(int a, int b, int w, int id)
{
	*++ecnt = (Edge) {last[a], b, w, id}; last[a] = ecnt;
	*++ecnt = (Edge) {last[b], a, w, id}; last[b] = ecnt;
}
int son[maxn], size[maxn], top[maxn], dep[maxn], ww[maxn], fa[maxn];
int dfn[maxn], pos[maxn], timer, rig[maxn], mp[maxn], tow[maxn], inv[maxn];
ll dis[maxn], tr[maxn];
std::multiset<ll> lig_son[maxn];
bool vis[maxn];
inline void add(int x, int v)
{
	for (; x <= timer; x += x & -x) tr[x] += v;
}
inline ll query_dis(int x)
{
	ll ret = 0;
	for (; x; x -= x & -x) ret += tr[x];
	return ret;
}
struct Seg {
	Seg *ls, *rs;
	ll lmax, rmax, tag1, tag2;
	inline void pushdown()
	{
		if (tag1)
		{
			ls -> tag1 += tag1;
			rs -> tag1 += tag1;
			ls -> lmax += tag1;
			rs -> lmax += tag1;
			tag1 = 0;
		}
		if (tag2)
		{
			ls -> tag2 += tag2;
			rs -> tag2 += tag2;
			ls -> rmax += tag2;
			rs -> rmax += tag2;
			tag2 = 0;
		}
	}
	inline void update()
	{
		lmax = dmax(ls -> lmax, rs -> lmax);
		rmax = dmax(ls -> rmax, rs -> rmax);
	}
} ssegg[maxn << 4], *scnt = ssegg, *rt[maxn];
void dfs1(int x)
{
	vis[x] = 1; dep[x] = dep[fa[x]] + 1; size[x] = 1;
	for (Edge *iter = last[x]; iter; iter = iter -> next)
		if (!vis[iter -> to])
		{
			fa[iter -> to] = x;
			dis[iter -> to] = dis[x] + iter -> w;
			mp[iter -> id] = iter -> to;
			tow[iter -> to] = iter -> w;
			dfs1(iter -> to);
			size[x] += size[iter -> to];
			size[son[x]] < size[iter -> to] ? son[x] = iter -> to : 0;
		}
}
void dfs2(int x)
{
	vis[x] = 0; top[x] = son[fa[x]] == x ? top[fa[x]] : x;
	dfn[x] = ++timer; pos[timer] = x;
	if (son[x]) dfs2(son[x]);
	for (Edge *iter = last[x]; iter; iter = iter -> next)
		if (vis[iter -> to]) dfs2(iter -> to);
	cmax(rig[top[x]], dfn[x]);
	inv[x] = timer;
}
ll max_dis[maxn];
void build(int l, int r)
{
	Seg *o = scnt;
	if (l == r)
	{
		o -> lmax = query_dis(l) - query_dis(dfn[top[pos[l]]]) + (lig_son[pos[l]].size() ? *lig_son[pos[l]].rbegin() : 0);
		o -> rmax = query_dis(rig[top[pos[l]]]) - query_dis(l) + (lig_son[pos[l]].size() ? *lig_son[pos[l]].rbegin() : 0);
		return ;
	}
	int mid = l + r >> 1;
	o -> ls = ++scnt; build(l, mid);
	o -> rs = ++scnt; build(mid + 1, r);
	o -> update();
}
void dfs3(int x)
{
	vis[x] = 1;
	for (Edge *iter = last[x]; iter; iter = iter -> next)
		if (!vis[iter -> to])
		{
			dfs3(iter -> to);
			if (iter -> to != son[x])
				lig_son[x].insert(max_dis[iter -> to] + iter -> w);
			cmax(max_dis[x], max_dis[iter -> to] + iter -> w);
		}
	if (top[x] == x)
	{
		rt[x] = ++scnt;
		build(dfn[x], rig[x]);
	}
}
int ql, qr, tag1, tag2;
ll ret;
void query_l(Seg *o, int l, int r)
{
	if (ql <= l && r <= qr) {cmax(ret, o -> lmax); return ;}
	int mid = l + r >> 1;
	o -> pushdown();
	if (ql <= mid) query_l(o -> ls, l, mid);
	if (mid < qr) query_l(o -> rs, mid + 1, r);
}
void query_r(Seg *o, int l, int r)
{
	if (ql <= l && r <= qr) {cmax(ret, o -> rmax); return ;}
	int mid = l + r >> 1;
	o -> pushdown();
	if (ql <= mid) query_r(o -> ls, l, mid);
	if (mid < qr) query_r(o -> rs, mid + 1, r);
}
void modify_v(Seg *o, int l, int r)
{
	if (l == r)
	{
		o -> lmax = query_dis(l) - query_dis(dfn[top[pos[l]]]) + (lig_son[pos[l]].size() ? *lig_son[pos[l]].rbegin() : 0);
		o -> rmax = query_dis(rig[top[pos[l]]]) - query_dis(l) + (lig_son[pos[l]].size() ? *lig_son[pos[l]].rbegin() : 0);
		return ;
	}
	int mid = l + r >> 1;
	o -> pushdown();
	if (ql <= mid) modify_v(o -> ls, l, mid);
	else modify_v(o -> rs, mid + 1, r);
	o -> update();
}
void modify_in(Seg *o, int l, int r)
{
	if (ql <= l && r <= qr)
	{
		o -> tag1 += tag1;
		o -> tag2 += tag2;
		o -> lmax += tag1;
		o -> rmax += tag2;
		return ;
	}
	int mid = l + r >> 1;
	o -> pushdown();
	if (ql <= mid) modify_in(o -> ls, l, mid);
	if (mid < qr) modify_in(o -> rs, mid + 1, r);
	o -> update();
}
int main()
{
	int n; scanf("%d", &n);
	for (int i = 1; i < n; ++i)
	{
		int a, b, w; scanf("%d%d%d", &a, &b, &w);
		link(a, b, w, i);
		ww[i] = w;
	}
	dfs1(1); dfs2(1);
	for (int i = 1; i <= n; ++i)
		add(dfn[i], tow[i]), add(inv[i] + 1, -tow[i]);
	dfs3(1);
	int q; scanf("%d", &q);
	for (; q; --q)
	{
		char opt[2]; scanf("%s", opt);
		if (opt[0] == 'Q')
		{
			int x; scanf("%d", &x);
			ll ans = lig_son[x].size() ? *lig_son[x].rbegin() : 0, sum = 0;
			while (x)
			{
				ll llen = query_dis(dfn[x]) - query_dis(dfn[top[x]]);
				ll rlen = query_dis(rig[top[x]]) - query_dis(dfn[x]);

				ql = dfn[x] + 1; qr = rig[top[x]];
				ret = 0;
				if (ql <= qr)
				{
					query_l(rt[top[x]], dfn[top[x]], rig[top[x]]);
					cmax(ans, sum + ret - llen);
				}
				
				ql = dfn[top[x]]; qr = dfn[x] - 1;
				ret = 0;
				if (ql <= qr)
				{
					query_r(rt[top[x]], dfn[top[x]], rig[top[x]]);
					cmax(ans, sum + ret - rlen);
				}
				
				sum += query_dis(dfn[x]) - query_dis(dfn[fa[top[x]]]);
				if (lig_son[fa[top[x]]].size() > 1)
				{
					auto tmp = lig_son[fa[top[x]]].rbegin();
					if (*tmp == rt[top[x]] -> lmax + tow[top[x]]) ++tmp;
					cmax(ans, sum + *tmp);
				}

				x = fa[top[x]];
			}
			printf("%lld\n", ans);
		}
		else
		{
			int e, w; scanf("%d%d", &e, &w);
			int x = mp[e];
			if (son[fa[x]] == x)
			{
				if (fa[top[x]]) lig_son[fa[top[x]]].erase(lig_son[fa[top[x]]].find(rt[top[x]] -> lmax + tow[top[x]]));
				ql = dfn[x]; qr = rig[top[x]]; tag1 = w - ww[e]; tag2 = 0;
				if (ql <= qr) modify_in(rt[top[x]], dfn[top[x]], rig[top[x]]);
				
				ql = dfn[top[x]]; qr = dfn[x] - 1; tag1 = 0; tag2 = w - ww[e];
				if (ql <= qr) modify_in(rt[top[x]], dfn[top[x]], rig[top[x]]);
				if (fa[top[x]]) lig_son[fa[top[x]]].insert(rt[top[x]] -> lmax + tow[top[x]]);
			}
			else if (fa[x])
			{
				lig_son[fa[x]].erase(lig_son[fa[x]].find(rt[x] -> lmax + ww[e]));
				lig_son[fa[x]].insert(rt[x] -> lmax + w);
			}
			x = fa[top[x]];
			while (x)
			{
				if (fa[top[x]]) lig_son[fa[top[x]]].erase(lig_son[fa[top[x]]].find(rt[top[x]] -> lmax + tow[top[x]]));

				ql = dfn[x];
				modify_v(rt[top[x]], dfn[top[x]], rig[top[x]]);				

				if (fa[top[x]]) lig_son[fa[top[x]]].insert(rt[top[x]] -> lmax + tow[top[x]]);
				x = fa[top[x]];
			}
			add(dfn[mp[e]], w - ww[e]);
			add(inv[mp[e]] + 1, ww[e] - w);
			ww[e] = w;
			tow[mp[e]] = w;
		}
	}
	return 0;
}
