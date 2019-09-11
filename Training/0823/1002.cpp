#include <cstdio>
#include <set>

#define maxn 100010
#define dmax(_a, _b) ((_a) > (_b) ? (_a) : (_b))
#define cmin(_a, _b) (_a > (_b) ? _a = (_b) : 0)
int tr[maxn << 2];
std::set<int> s[maxn];
int a[maxn];
inline void update(int o)
{
	tr[o] = dmax(tr[o << 1], tr[o << 1 | 1]);
}
void build(int o, int l, int r)
{
	if (l == r)
	{
		tr[o] = *s[l].begin();
		return ;
	}
	int mid = l + r >> 1;
	build(o << 1, l, mid);
	build(o << 1 | 1, mid + 1, r);
	update(o);
}
int ql, qr, ret;
void modify(int o, int l, int r)
{
	if (l == r)
	{
		tr[o] = *s[l].begin();
		return ;
	}
	int mid = l + r >> 1;
	if (ql <= mid) modify(o << 1, l, mid);
	else modify(o << 1 | 1, mid + 1, r);
	update(o);
}
int ans;
void query(int o, int l, int r)
{
	if (l == r)
	{
		if (tr[o] > ql)
			cmin(ans, l);
		return ;
	}
	int mid = l + r >> 1;
	if (mid < qr || tr[o << 1] <= ql) return (void) query(o << 1 | 1, mid + 1, r);
	query(o << 1, l, mid);
	if (ans <= r) return ;
	query(o << 1 | 1, mid + 1, r);
}
int main()
{
	int T; scanf("%d", &T);
	for (; T; --T)
	{
		int n, m; scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; ++i) s[i].clear();
		for (int i = 1; i <= n; ++i) scanf("%d", a + i), s[i].insert(n + 1), s[a[i]].insert(i);
		build(1, 1, n);
		ans = 0;
		for (int i = 1; i <= m; ++i)
		{
			int opt; scanf("%d", &opt);
			if (opt == 1)
			{
				int pos; scanf("%d", &pos); pos ^= ans;
				s[a[pos]].erase(pos);
				ql = a[pos]; modify(1, 1, n);
			}
			else
			{
				int r, k; scanf("%d%d", &r, &k); r ^= ans; k ^= ans;
				ql = r; qr = k;
				ans = n + 1;
				query(1, 1, n);
				printf("%d\n", ans);
			}
		}
	}
	return 0;
}
