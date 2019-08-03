#include <cstdio>
#include <cstring>

#define maxn 100010
typedef long long ll;
int a[maxn], n;
ll tr[maxn << 2], trr[maxn];
void add(int x, int v)
{
	for (; x <= n; x += x & -x) trr[x] += v;
}
ll query(int x)
{
	ll ret = 0;
	for (; x; x -= x & -x) ret += trr[x];
	return ret;
}
void update(int o)
{
	tr[o] = tr[o << 1] + tr[o << 1 | 1];
}
void build(int o, int l, int r)
{
	if (l == r)
	{
		tr[o] = a[l] > 0 ? a[l] : 0;
		return ;
	}
	int mid = l + r >> 1;
	build(o << 1, l, mid);
	build(o << 1 | 1, mid + 1, r);
	update(o);
}
int ql, qr, qv;
void modify(int o, int l, int r)
{
	if (l == r)
	{
		a[l] += qv;
		tr[o] = a[l] > 0 ? a[l] : 0;
		return ;
	}
	int mid = l + r >> 1;
	if (ql <= mid) modify(o << 1, l, mid);
	else modify(o << 1 | 1, mid + 1, r);
	update(o);
}
ll query(int o, int l, int r)
{
	if (ql <= l && r <= qr) return tr[o];
	int mid = l + r >> 1; ll ret = 0;
	if (ql <= mid) ret += query(o << 1, l, mid);
	if (mid < qr) ret += query(o << 1 | 1, mid + 1, r);
	return ret;
}
int main()
{
	int T; scanf("%d", &T);
	for (; T; --T)
	{
		int m; scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		memset(trr, 0, (n + 1) << 3);
		for (int i = n; i; --i) a[i] -= a[i - 1], add(i, a[i]);
		build(1, 1, n);
		for (; m; --m)
		{
			int opt, l, r; scanf("%d%d%d", &opt, &l, &r);
			if (opt == 1)
			{
				scanf("%d", &qv);
				add(l, qv); add(r + 1, -qv);
				ql = l; modify(1, 1, n);
				ql = r + 1; qv = -qv; if (ql <= n) modify(1, 1, n);
			}
			else
			{
				ql = l + 1; qr = r;
				ll ret = query(l);
				if (ql <= qr) ret += query(1, 1, n);
				printf("%lld\n", ret);
			}
		}
	}
	return 0;
}
/*
1
5 4
1 3 1 4 5
2 1 5
1 3 4 2
2 2 4
2 1 5
*/
