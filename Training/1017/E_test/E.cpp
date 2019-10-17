#include <cstdio>
#include <algorithm>
#include <cstring>

#define maxn 100010
#define dmin(_a, _b) ((_a) < (_b) ? (_a) : (_b))
#define cmax(_a, _b) (_a < (_b) ? _a = (_b) : 0)
struct Seg {
	int l, r;
} s[maxn], ss[maxn];
int tr[maxn << 2], tag[maxn << 2], c[maxn];
inline void pushdown(int o)
{
	if (tag[o])
	{
		tr[o << 1] += tag[o];
		tr[o << 1 | 1] += tag[o];
		tag[o << 1] += tag[o];
		tag[o << 1 | 1] += tag[o];
        tag[o] = 0;
    }
}
inline void update(int o)
{
	tr[o] = dmin(tr[o << 1], tr[o << 1 | 1]);
}
void build(int o, int l, int r)
{
	tr[o] = tag[o] = 0;
	if (l == r) return ;
	int mid = l + r >> 1;
	build(o << 1, l, mid);
	build(o << 1 | 1, mid + 1, r);
}
int ql, qr, qv;
void modify(int o, int l, int r)
{
	if (l == r)
	{
		tr[o] = qv;
		return ;
	}
	int mid = l + r >> 1;
	pushdown(o);
	if (ql <= mid) modify(o << 1, l, mid);
	else modify(o << 1 | 1, mid + 1, r);
	update(o);
}
void modify_inv(int o, int l, int r)
{
	if (ql <= l && r <= qr)
	{
		tag[o] += qv;
		tr[o] += qv;
		return ;
	}
	int mid = l + r >> 1;
	pushdown(o);
	if (ql <= mid) modify_inv(o << 1, l, mid);
	if (mid < qr) modify_inv(o << 1 | 1, mid + 1, r);
	update(o);
}
int query(int o, int l, int r)
{
	if (l == r) return tr[o];
	pushdown(o);
	int mid = l + r >> 1;
	if (ql <= mid) return query(o << 1, l, mid);
	else return std::min(query(o << 1 | 1, mid + 1, r), tr[o << 1]);
}
int main()
{
	int T; scanf("%d", &T);
	for (int Cas = 1; Cas <= T; ++Cas)
	{
		int n, m; scanf("%d%d", &n, &m);
		build(1, 0, m);
		for (int i = 1; i <= n; ++i)
			scanf("%d%d", &s[i].l, &s[i].r);
		for (int i = 1; i <= m; ++i) scanf("%d", c + i);
		std::sort(c + 1, c + m + 1);
		for (int i = 1; i <= n; i++) ss[i] = s[i];
		std::sort(s + 1, s + n + 1, [](const auto &a, const auto &b) {return a.r < b.r;});
		std::sort(ss + 1, ss + n + 1, [](const auto &a, const auto &b) {return a.l < b.l;});
		int nw = 1, nw2 = 1, ans = 0;
		for (int i = 1; i <= m; ++i)
		{
			while (nw <= n && s[nw].r < c[i])
			{
				ql = 0; qr = std::lower_bound(c + 1, c + m + 1, s[nw].l) - c - 1; qv = -1;
				if (ql <= qr) modify_inv(1, 0, m);
				//printf("-modi (%d %d) (%d %d)\n", s[nw].l, s[nw].r, ql, qr);
				++nw;
			}
			while (nw2 <= n && ss[nw2].l <= c[i])
			{
				ql = 0; qr = std::lower_bound(c + 1, c + m + 1, ss[nw2].l) - c - 1; qv = 1;
				if (ql <= qr) modify_inv(1, 0, m);
				//printf("+modi (%d %d) (%d %d)\n", ss[nw2].l, ss[nw2].r, ql, qr);
				++nw2;
			}
			ql = i - 1; qv = query(1, 0, m) - 1;
			//printf("dp[%d] = %d\n", i, qv);
			ql = i; modify(1, 0, m);
			cmax(ans, n - qv);
		}
        //puts("");
		printf("Case #%d: ", Cas);
		if (ans > n) puts("IMPOSSIBLE!");
		else printf("%d\n", ans);
	}
	return 0;
}
/*
3
3 1
1 4
2 3
5 6
3
3 2
1 10
3 4
7 9
4 8
3 3
1 2
5 6
8 9
1 5 10

*/
