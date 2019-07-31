#include <cstdio>
#include <algorithm>

#define maxn 300010
typedef long long ll;
const int inf = 0x7fffffff;
int a[maxn];
ll sum[maxn];
int tr[maxn << 2], tag[maxn << 2];
std::pair<int, int> mn[maxn << 2];
void update(int o)
{
	mn[o] = std::min(mn[o << 1], mn[o << 1 | 1]);
	tr[o] = std::min(tr[o << 1], tr[o << 1 | 1]);
}
int ql, qr, qv1, qv2;
void pushdown(int o)
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
void build(int o, int l, int r)
{
	tr[o] = inf; mn[o] = std::make_pair(inf, inf);
	tag[o] = 0;
	if (l == r) return ;
	int mid = l + r >> 1;
	build(o << 1, l, mid);
	build(o << 1 | 1, mid + 1, r);
}
void modify(int o, int l, int r)
{
	if (l == r)
	{
		tr[o] = qv1;
		mn[o] = std::make_pair(qv2, l);
		return ;
	}
	pushdown(o);
	int mid = l + r >> 1;
	if (ql <= mid) modify(o << 1, l, mid);
	else modify(o << 1 | 1, mid + 1, r);
	update(o);
}
void modify_inv(int o, int l, int r)
{
	if (ql <= l && r <= qr)
	{
		tag[o] += qv1;
		tr[o] += qv1;
		return ;
	}
	pushdown(o);
	int mid = l + r >> 1;
	if (ql <= mid) modify_inv(o << 1, l, mid);
	if (mid < qr) modify_inv(o << 1 | 1, mid + 1, r);
	update(o);
}
int query_zero(int o, int l, int r)
{
	if (l == r) return l;
	pushdown(o);
	int mid = l + r >> 1;
	if (tr[o << 1 | 1] == 0) return query_zero(o << 1 | 1, mid + 1, r);
	else return query_zero(o << 1, l, mid);
}
std::pair<int, int> query_min(int o, int l, int r)
{
	if (ql <= l && r <= qr) return mn[o];
	pushdown(o);
	int mid = l + r >> 1; std::pair<int, int> tmp = std::make_pair(inf, inf);
	if (ql <= mid) tmp = std::min(tmp, query_min(o << 1, l, mid));
	if (mid < qr) tmp = std::min(tmp, query_min(o << 1 | 1, mid + 1, r));
	return tmp;
}
int main()
{
	int n, m; scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; ++i) scanf("%d", a + i), sum[i] = sum[i - 1] + a[i];
	build(1, 1, n);
	ll ans = 0; ll lst = 0;
	for (int i = 1; i <= n; ++i)
	{
		ll l, r; int p; scanf("%lld%lld%d", &l, &r, &p);
		l = sum[l - 1] + 1; r = sum[r];
		if (l > r)
		{
			ql = i; qv1 = qv2 = inf;
			modify(1, 1, n);
			continue;
		}
		//printf("%lld %lld\n", l, r);
		if (l > lst + 1)
		{
			//printf("case 1: %d\n", i);
			ql = i; qv1 = 0; qv2 = p;
			ans += p;
			modify(1, 1, n);
			lst = l;
		}
		else if (r >= lst + 1)
		{
			//printf("case 2: %d\n", i);
			ql = i; qv1 = lst + 1 - l; qv2 = p;
			ans += p;
			modify(1, 1, n);
			++lst;
		}
		else
		{
			//printf("case 3: %d\n", i);
			int pos = query_zero(1, 1, n);
			//printf("%d\n", pos);
			ql = pos; qr = i - 1;
			std::pair<int, int> mm = query_min(1, 1, n);
			if (mm.first >= p)
			{
				ql = i; qv1 = qv2 = inf;
				modify(1, 1, n);
				continue;
			}
			ans += p - mm.first;
			ql = mm.second; qv1 = inf; qv2 = inf;
			modify(1, 1, n);
			ql = mm.second + 1; qr = i - 1; qv1 = -1;
			if (ql <= qr) modify_inv(1, 1, n);
			ql = i; qv1 = r - l; qv2 = p;
			modify(1, 1, n);
			lst = r;
		}
	}
	printf("%lld\n", ans);
	return 0;
}
/*
3 5
0 1 0 1 0
1 2 2
2 4 1
3 5 5
*/ 
  
