#include <cstdio>
#include <set>
#include <cstring>
#include <algorithm>

#define maxn 200010
std::set<std::pair<int, int> > s[maxn];
int a[maxn], n;
struct Seg {
	int ls, rs;
	int sum;
} mem[maxn * 280];
inline void update(int o)
{
	mem[o].sum = (mem[o].ls ? mem[mem[o].ls].sum : 0)
			   + (mem[o].rs ? mem[mem[o].rs].sum : 0);
}
int tot, tr[2][maxn];
int tr_sum[maxn];
int sum_query(int x)
{
	int ret = 0;
	for (; x; x -= x & -x) ret += tr_sum[x];
	return ret;
}
void sum_modify(int x, int v)
{
	for (; x <= n; x += x & -x) tr_sum[x] += v;
}
int seg_query(int o, int ql, int qr, int l = 1, int r = n)
{
	if (!o) return 0;
	if (ql <= l && r <= qr) return mem[o].sum;
	int mid = l + r >> 1, ret = 0;
	if (ql <= mid) ret += seg_query(mem[o].ls, ql, qr, l, mid);
	if (mid < qr) ret += seg_query(mem[o].rs, ql, qr, mid + 1, r);
	return ret;
}
int seg_modify(int o, int ql, int v, int l = 1, int r = n)
{
	if (!o) o = ++tot;
	if (l == r)
	{
		mem[o].sum += v;
		return o;
	}
	int mid = l + r >> 1;
	if (ql <= mid) mem[o].ls = seg_modify(mem[o].ls, ql, v, l, mid);
	else mem[o].rs = seg_modify(mem[o].rs, ql, v, mid + 1, r);
	update(o);
	return o;
}
int tr_query(int x, int l, int r)
{
	int ret = 0;
	for (; x; x -= x & -x)
		ret += seg_query(tr[0][x], 1, l - 1),
		ret += seg_query(tr[1][x], r + 1, n);
	return ret;
}
void tr_modify(int x, int l, int r, int v)
{
	for (; x <= n; x += x & -x)
		tr[0][x] = seg_modify(tr[0][x], l, v),
		tr[1][x] = seg_modify(tr[1][x], r, v);
}
void my_insert(int col, int l, int r, int v)
{
	sum_modify(col, v);
	if (v > 0) s[col].insert(std::make_pair(r, l));
	else s[col].erase(std::make_pair(r, l));
	tr_modify(col, l, r, v);
}
int query(int l, int r, int x, int y)
{
	return sum_query(y) - sum_query(x - 1) - tr_query(y, l, r) + tr_query(x - 1, l, r);
}
int main()
{
	fprintf(stderr, "%d\n", sizeof (mem) >> 20);
	int m; scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) scanf("%d", a + i);
	int l = 1;
	for (int i = 2; i <= n; ++i)
		if (a[i] != a[i - 1])
		{
			my_insert(a[i - 1], l, i - 1, 1);
			l = i;
		}
	my_insert(a[n], l, n, 1);
	for (; m; --m)
	{
		int opt; scanf("%d", &opt);
		if (opt == 1)
		{
			int pos, v; scanf("%d%d", &pos, &v);
			auto pa = *s[a[pos]].lower_bound(std::make_pair(pos, 0));
			my_insert(a[pos], pa.first, pa.second, -1);
			a[pos] = v;
			int l = pos, r = pos;
			if (a[pos - 1] == v)
			{
				pa = *s[v].lower_bound(std::make_pair(pos - 1, 0));
				my_insert(v, pa.first, pa.second, -1);
				l = pa.second;
			}
			if (a[pos + 1] == v)
			{
				pa = *s[v].lower_bound(std::make_pair(pos + 1, 0));
				my_insert(v, pa.first, pa.second, -1);
				r = pa.first;
			}
			my_insert(v, l, r, 1);
		}
		else
		{
			int l, r, x, y; scanf("%d%d%d%d", &l, &r, &x, &y);
			printf("%d\n", query(l, r, x, y));
		}
	}
	return 0;
}
