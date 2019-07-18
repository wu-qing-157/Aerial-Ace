#include <cstdio>

#define maxn 200010
#define dmin(_a, _b) ((_a) < (_b) ? (_a) : (_b))
#define dmax(_a, _b) ((_a) > (_b) ? (_a) : (_b))
#define cmin(_a, _b) (_a > (_b) ? _a = (_b) : 0)
#define cmax(_a, _b) (_a < (_b) ? _a = (_b) : 0)
int trmn[maxn << 2], trmx[maxn << 2], a[maxn];
void update(int o)
{
	trmn[o] = dmin(trmn[o << 1], trmn[o << 1 | 1]);
	trmx[o] = dmax(trmx[o << 1], trmx[o << 1 | 1]);
}
int ql, qr;
void modify(int o, int l, int r)
{
	if (l == r)
	{
		++trmn[o];
		++trmx[o];
		return ;
	}
	int mid = l + r >> 1;
	if (ql <= mid) modify(o << 1, l, mid);
	else modify(o << 1 | 1, mid + 1, r);
	update(o);
}
int mn, mx;
void query_mn(int o, int l, int r)
{
	if (ql <= l && r <= qr)
	{
		cmin(mn, trmn[o]);
		return ;
	}
	int mid = l + r >> 1;
	if (ql <= mid) query_mn(o << 1, l, mid);
	if (mid < qr) query_mn(o << 1 | 1, mid + 1, r);
}
void query_mx(int o, int l, int r)
{
	if (ql <= l && r <= qr)
	{
		cmax(mx, trmx[o]);
		return ;
	}
	int mid = l + r >> 1;
	if (ql <= mid) query_mx(o << 1, l, mid);
	if (mid < qr) query_mx(o << 1 | 1, mid + 1, r);
}
int c[maxn];
int main()
{
	freopen("nice.in", "r", stdin);
	freopen("nice.out", "w", stdout);
	int n, k; scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; ++i) scanf("%d", a + i), ++a[i];
	int ans = 0;
	for (int i = 1; i <= n; ++i)
	{
		ql = a[i]; ++c[a[i]];
		modify(1, 1, n + 1);
		ql = 1; qr = a[i] - 1; mn = n + 1;
		if (ql <= qr) query_mn(1, 1, n + 1);
		ql = a[i] + 1; qr = n + 1; mx = 0;
		if (ql <= qr) query_mx(1, 1, n + 1);
		if (mn < c[a[i]] - k || c[a[i]] < mx - k) {printf("%d\n", i - 1); return 0;}
	}
	printf("%d\n", n);
	return 0;
}
/*
10 1
0 1 1 0 2 2 1 2 2 3

2 0
1 0
*/
