#include <cstdio>
#include <vector>
#include <cmath>

#define maxn 400010
#define dmax(_a, _b) ((_a) > (_b) ? (_a) : (_b))
#define cmax(_a, _b) (_a < (_b) ? _a = (_b) : 0)
std::vector<int> e[maxn][2];
int rr[maxn], dfn[maxn], inv1[maxn], inv2[maxn], fat[maxn], omi[maxn], timer;
int pos[maxn], root[maxn];
inline void link(int a, int b, int type)
{
	e[a][type].push_back(b);
	e[b][type].push_back(a);
}
int Log(int x)
{
	int ans = -1;
	while (x) ++ans, x >>= 1;
	return ans;
}
void dfs(int x, int ty)
{
	fat[x] = ty; dfn[x] = ++timer;
	pos[timer] = x;
	for (int it : e[x][1])
		if (!dfn[it])
	{
		omi[it] = omi[x];
		root[it] = root[x];
		dfs(it, 1);
	}
	inv1[x] = timer;
	for (int it : e[x][0])
		if (!dfn[it])
	{
		omi[it] = omi[x] + rr[x] - rr[it];
		root[it] = root[x];
		dfs(it, 0);
	}
	inv2[x] = timer;
}
int tr[maxn], tag[maxn], ql, qr, qv;
void update(int o)
{
	tr[o] = dmax(tr[o << 1], tr[o << 1 | 1]);
}
void pushdown(int o)
{
	tr[o << 1] += tag[o];
	tag[o << 1] += tag[o];
	tr[o << 1 | 1] += tag[o];
	tag[o << 1 | 1] += tag[o];
	tag[o] = 0;
}
void build(int o, int l, int r)
{
	tag[o] = 0;
	if (l == r)
	{
		tr[o] = omi[pos[l]];
		return ;
	}
	int mid = l + r >> 1;
	build(o << 1, l, mid);
	build(o << 1 | 1, mid + 1, r);
	update(o);
}
void modify(int o, int l, int r)
{
	if (ql <= l && r <= qr)
	{
		tr[o] += qv; tag[o] += qv;
		return ;
	}
	int mid = l + r >> 1;
	pushdown(o);
	if (ql <= mid) modify(o << 1, l, mid);
	if (mid < qr) modify(o << 1 | 1, mid + 1, r);
	update(o);
}
int ret;
void query(int o, int l, int r)
{
	if (ql <= l && r <= qr) {cmax(ret, tr[o]); return ;}
	pushdown(o);
	int mid = l + r >> 1;
	if (ql <= mid) query(o << 1, l, mid);
	if (mid < qr) query(o << 1 | 1, mid + 1, r);
}
int main()
{
	int n, m, q, Cas = 0;
	while (scanf("%d%d%d", &n, &m, &q) != EOF)
	{
		printf("Case #%d:\n", ++Cas);
		for (int i = 1; i <= n; ++i) scanf("%d", rr + i), rr[i] = Log(rr[i]);
		for (int i = 1; i <= n; ++i) e[i][0].clear(), e[i][1].clear(), dfn[i] = 0; timer = 0;
		for (int i = 1; i <= n; ++i) root[i] = 0, omi[i] = 0, fat[i] = 0, inv1[i] = 0, inv2[i] = 0;
		for (int i = 1; i <= m; ++i)
		{
			int a, x, y; scanf("%d%d%d", &a, &x, &y);
			link(x, y, a - 1);
		}
		//for (int i = 1; i <= n; ++i) printf("%d ", rr[i]); puts("");
		for (int i = 1; i <= n; ++i)
			if (!dfn[i]) root[i] = i, omi[i] = 0, dfs(i, 0);
		build(1, 1, n);
		for (int i = 1; i <= q; ++i)
		{
			int a, x, y; scanf("%d%d%d", &a, &x, &y); y = Log(y);
			/*for (int i = 1; i <= n; ++i)
			{
				ql = dfn[i]; qr = dfn[i]; ret = -0x7fffffff; query(1, 1, n);
				printf("%d ", ret);
			} puts("");*/
			if (a == 1)
			{
				if (fat[x])
				{
					ql = inv1[x] + 1; qr = inv2[x]; qv = y - rr[x];
					modify(1, 1, n);
				}
				else
				{
					ql = dfn[x]; qr = inv1[x]; qv = rr[x] - y;
					modify(1, 1, n);
				}
				rr[x] = y;
			}
			else
			{
				ql = dfn[root[x]]; qr = inv2[root[x]]; ret = -0x7fffffff;
				query(1, 1, n);
				int omi_mx = ret;
				ql = dfn[x]; qr = dfn[x]; ret = -0x7fffffff;
				query(1, 1, n);
				//printf("\n%d %d %d\n", ret, omi_mx, y);
				printf("%.3f\n", (y + omi_mx - ret) * log(2));
			}
			/*for (int i = 1; i <= n; ++i)
			{
				ql = dfn[i]; qr = dfn[i]; ret = -0x7fffffff; query(1, 1, n);
				printf("%d ", ret);
			} puts("");*/
		}
	}
	return 0;
}
/*
4 3 4
1 4 16 2
1 2 4
1 2 3
2 1 4
1 1 16
1 2 4
2 4 4
1 4 16

4 3 5
2 16 4 8
2 1 2
1 2 3
1 1 4
2 1 4
1 3 8
2 1 16
1 4 1
2 1 8
*/
