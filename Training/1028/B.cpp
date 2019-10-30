#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

#define maxn 100010
const int inf = 0x7fffffff;
std::vector<int> e[maxn];
int size[maxn], top[maxn], son[maxn], fa[maxn], dep[maxn], dfn[maxn], inv[maxn], timer, pos[maxn];
int n;
bool vis[maxn];
void dfs1(int x)
{
	vis[x] = 1; size[x] = 1; dep[x] = dep[fa[x]] + 1;
	for (int to : e[x])
		if (!vis[to])
		{
			fa[to] = x;
			dfs1(to);
			size[x] += size[to];
			size[to] > size[son[x]] ? son[x] = to : 0;
		}
}
void dfs2(int x)
{
	vis[x] = 0; top[x] = son[fa[x]] == x ? top[fa[x]] : x;
	pos[dfn[x] = ++timer] = x;
	if (son[x]) dfs2(son[x]);
	for (int to : e[x]) if (vis[to]) dfs2(to);
	inv[x] = timer;
}
int tr[maxn << 2], sum[maxn << 2];
void build(int o, int l, int r)
{
	if (l == r)
	{
		tr[o] = inf;
		return ;
	}
	int mid = l + r >> 1;
	build(o << 1, l, mid);
	build(o << 1 | 1, mid + 1, r);
}
int ql, qr, qv;
inline void update(int o)
{
	tr[o] = std::min(tr[o << 1], tr[o << 1 | 1]);
}
void modify(int o, int l, int r)
{
	if (l == r)
	{
		tr[o] = qv;
		return ;
	}
	int mid = l + r >> 1;
	if (ql <= mid) modify(o << 1, l, mid);
	else modify(o << 1 | 1, mid + 1, r);
	update(o);
}
int query(int o, int l, int r)
{
	if (l == r) return sum[o];
	int mid = l + r >> 1;
	if (ql <= mid) return (sum[o] + query(o << 1, l, mid)) % 360;
	else return (sum[o] + query(o << 1 | 1, mid + 1, r)) % 360;
}
void modify_inv(int o, int l, int r)
{
	if (ql <= l && r <= qr)
	{
		(sum[o] += qv) %= 360;
		return ;
	}
	int mid = l + r >> 1;
	if (ql <= mid) modify_inv(o << 1, l, mid);
	if (mid < qr) modify_inv(o << 1 | 1, mid + 1, r);
}
int cur[maxn];
int cover[maxn << 2], len[maxn << 2];
inline void upd(int o, int l, int r)
{
	cover[o] ? len[o] = r - l + 1 : len[o] = len[o << 1] + len[o << 1 | 1];
}
void modify_size(int o, int l, int r)
{
	if (ql <= l && r <= qr)
	{
		cover[o] += qv;
		upd(o, l, r);
		return ;
	}
	int mid = l + r >> 1;
	if (ql <= mid) modify_size(o << 1, l, mid);
	if (mid < qr) modify_size(o << 1 | 1, mid + 1, r);
	upd(o, l, r);
}
int query_size(int o, int l, int r)
{
	if (ql <= l && r <= qr) return len[o];
	int mid = l + r >> 1, ret = 0;
	if (ql <= mid) ret += query_size(o << 1, l, mid);
	if (mid < qr) ret += query_size(o << 1 | 1, mid + 1, r);
	return ret;
}
int query_col(int o, int l, int r)
{
	if (ql <= l && r <= qr) return tr[o];
	int mid = l + r >> 1, ret = 0x7fffffff;
	if (ql <= mid) ret = std::min(ret, query_col(o << 1, l, mid));
	if (mid < qr) ret = std::min(ret, query_col(o << 1 | 1, mid + 1, r));
	return ret;
}
int tr_query(int x)
{
	int rt = 0, xx = x;
	while (x)
	{
		ql = dfn[top[x]]; qr = dfn[x];
		int ret = query_col(1, 1, n);
		if (ret <= timer)
		{
			rt = pos[ret];
			break;
		}
		x = fa[top[x]];
	}
	if (!rt) return 1;
	x = xx;
	int det = dep[x] - dep[rt] - 1;
	while (x)
	{
		if (dep[x] - dep[top[x]] >= det) return pos[dfn[x] - det];
		det -= dep[x] - dep[top[x]];
		x = fa[top[x]];
	}
	return 0;
}
int main()
{
	scanf("%d", &n);
	for (int i = 1; i < n; ++i)
	{
		int a, b; scanf("%d%d", &a, &b);
		e[a].push_back(b);
		e[b].push_back(a);
	}
	dfs1(1); dfs2(1);
	int q; scanf("%d", &q);
	build(1, 1, n);
	for (; q; --q)
	{
		int opt; scanf("%d", &opt);
		if (opt == 1)
		{
			int x; scanf("%d", &x); ql = dfn[x]; qr = inv[x]; qv = dfn[x];
			modify(1, 1, n);
			cur[x] = query(1, 1, n);
			qv = 1; modify_size(1, 1, n);
			vis[x] = 1;
		}
		else if (opt == 2)
		{
			int x; scanf("%d", &x); ql = dfn[x]; qv = inf;
			modify(1, 1, n);
			qv = cur[x] - query(1, 1, n);
			qr = inv[x];
			vis[x] = 0;
			modify_inv(1, 1, n);
			qv = -1; modify_size(1, 1, n);
		}
		else
		{
			int x, v, vv; scanf("%d%d", &x, &v); vv = v; dep[x] % 2 == 0 ? v = 360 - v : 0;
			int mtop = tr_query(x);

			ql = dfn[mtop]; qr = inv[mtop]; qv = v;
			if (!mtop) ql = 1, qr = n;
			
			modify_inv(1, 1, n);
			int sss = mtop ? size[mtop] : n;
			
			printf("sss %d mtop %d %d %d %d\n", sss, mtop, query_size(1, 1, n), ql, qr);
			printf("%d\n", vv * (sss - query_size(1, 1, n)));
		}
		
		// puts("OK");
		// for (ql = 1; ql <= n; ++ql) printf("%d ", query(1, 1, n)); puts("");
	}
	int ans = 0;
	for (int i = 1, x; i <= n; ++i)
		if (vis[x = pos[i]])
		{
			ans += dep[x] % 2 == 0 ? (360 - cur[x]) % 360 :  cur[x];
			// printf("val[%d] = %d\n", x, dep[x] % 2 == 0 ? 360 - cur[x] :  cur[x]);
			
			ql = dfn[x]; qr = inv[x];
			qv = cur[x] - query(1, 1, n);
			modify_inv(1, 1, n);
		}
		else
		{
			ql = i;
			int p = query(1, 1, n);
			ans += dep[x] % 2 == 0 ? (360 - p) % 360 : p;
			// printf("val[%d] = %d\n", x, dep[x] % 2 == 0 ? 360 - p : p);
		}
	printf("%d\n", ans);
	return 0;
}
/*
4
1 2
2 3
2 4
8
3 2 160
1 2
3 1 10
3 4 10
3 3 10
2 2
1 1
3 3 15
*/
