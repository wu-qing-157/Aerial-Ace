#include <cstdio>
#include <set>
#include <cstring>
#include <algorithm>

#define maxn 200010
const int moha = 19260817;
struct Hash {
	int next, sum, x, y;
} mem[maxn * 135];
int tot, last[moha];
int Hash_query(int o, int x)
{
	int key = (2ll * o * maxn + x) % moha;
	for (int it = last[key]; it; it = mem[it].next)
		if (mem[it].x == o && mem[it].y == x)
			return mem[it].sum;
	return 0;
}
void Hash_modify(int o, int x, int v)
{
	int key = (2ll * o * maxn + x) % moha;
	for (int it = last[key]; it; it = mem[it].next)
		if (mem[it].x == o && mem[it].y == x)
		{
			mem[it].sum += v;
			return ;
		}
	++tot; mem[tot] = (Hash) {last[key], v, o, x}; last[key] = tot;
}
std::set<std::pair<int, int> > s[maxn];
int a[maxn], n;
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
int seg_query(int o, int x, int dir, int type)
{
	int ret = 0;
	for (; x && x <= n; x += dir * (x & -x))
		ret += Hash_query(o, x << 1 | type);
	return ret;
}
void seg_modify(int o, int x, int v, int dir, int type)
{
	for (; x && x <= n; x += dir * (x & -x))
		Hash_modify(o, x << 1 | type, v);
}
int tr_query(int x, int l, int r)
{
	int ret = 0;
	for (; x; x -= x & -x)
		ret += seg_query(x, l - 1, -1, 1),
		ret += seg_query(x, r + 1, 1, 0);
	return ret;
}
void tr_modify(int x, int l, int r, int v)
{
	for (; x <= n; x += x & -x)
		seg_modify(x, l, v, -1, 0),
		seg_modify(x, r, v, 1, 1);
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
	fprintf(stderr, "%d\n", (sizeof (mem) + sizeof (last)) >> 20);
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
