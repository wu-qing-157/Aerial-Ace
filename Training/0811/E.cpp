#include <cstdio>
#include <algorithm>
#include <cstring>

#define maxn 20010
#define cmax(_a, _b) (_a < (_b) ? _a = (_b) : 0)
typedef long long ll;
struct Seg {
	ll lsum, rsum, sum, ret;
	inline Seg operator + (const Seg &that) const
	{
		return (Seg)
		{
			std::max(lsum, sum + that.lsum),
			std::max(that.rsum, that.sum + rsum),
			sum + that.sum,
			std::max({ret, that.ret, rsum + that.lsum})
		};
	}
} tr[maxn << 2];
struct poi {
	int x, y, v;
	inline bool operator < (const poi &that) const {return x < that.x;}
} p[maxn];
int hash[maxn], hcnt;
void build(int o, int l, int r)
{
	tr[o] = (Seg) {0ll, 0ll, 0ll, 0ll};
	if (l == r) return ;
	int mid = l + r >> 1;
	build(o << 1, l, mid);
	build(o << 1 | 1, mid + 1, r);
}
int ql, qv;
void modify(int o, int l, int r)
{
	if (l == r)
	{
		tr[o].lsum += qv;
		tr[o].rsum += qv;
		tr[o].sum += qv;
		tr[o].ret += qv;
		return ;
	}
	int mid = l + r >> 1;
	if (ql <= mid) modify(o << 1, l, mid);
	else modify(o << 1 | 1, mid + 1, r);
	tr[o] = tr[o << 1] + tr[o << 1 | 1];
}
int main()
{
	int T; scanf("%d", &T);
	for (; T; --T)
	{
		int n; scanf("%d", &n);
		hcnt = 0;
		for (int i = 1; i <= n; ++i) scanf("%d%d%d", &p[i].x, &p[i].y, &p[i].v), hash[++hcnt] = p[i].y;
		std::sort(p + 1, p + n + 1);
		std::sort(hash + 1, hash + hcnt + 1);
		hcnt = std::unique(hash + 1, hash + hcnt + 1) - hash - 1;
		ll ans = 0;
		for (int i = 1; i <= n; ++i) p[i].y = std::lower_bound(hash + 1, hash + hcnt + 1, p[i].y) - hash;
		for (int i = 1, j = 1; i <= n; i = j)
		{
			for (; j <= n && p[i].x == p[j].x; ++j) ;
			build(1, 1, hcnt);
			for (int ii = i, jj = i; ii <= n; ii = jj)
			{
				for (; jj <= n && p[ii].x == p[jj].x; ++jj)
				{
					ql = p[jj].y; qv = p[jj].v;
					modify(1, 1, hcnt);
				}
				cmax(ans, tr[1].ret);
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}
