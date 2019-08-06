#include <cstdio>
#include <algorithm>
#include <cstring>

#define maxn 100010
typedef long long ll;
int a[maxn], tr[maxn << 2][65], size[maxn << 2];
void update(int o)
{
	int tot = size[o << 1] + size[o << 1 | 1], i = 1, j = 1;
	tot > 45 ? tot = 45 : 0;
	for (int k = 1; k <= tot; ++k)
		if (i <= size[o << 1] && (j > size[o << 1 | 1] || tr[o << 1][i] > tr[o << 1 | 1][j])) tr[o][k] = tr[o << 1][i++];
		else tr[o][k] = tr[o << 1 | 1][j++];
	size[o] = tot;
}
void build(int o, int l, int r)
{
	if (l == r)
	{
		size[o] = 1;
		tr[o][1] = a[l];
		return ;
	}
	int mid = l + r >> 1;
	build(o << 1, l, mid);
	build(o << 1 | 1, mid + 1, r);
	update(o);
}
int cnt, anss[110];
int ql, qr;
void query(int o, int l, int r)
{
	if (ql <= l && r <= qr)
	{
		int tot = size[o] + cnt, i = 1, j = 1;
		tot > 45 ? tot = 45 : 0;
		int tmp[110];
		for (int k = 1; k <= tot; ++k)
			if (i <= size[o] && (j > cnt || tr[o][i] > anss[j])) tmp[k] = tr[o][i++];
			else tmp[k] = anss[j++];
		cnt = tot;
		memcpy(anss + 1, tmp + 1, tot << 2);
		return ;
	}
	int mid = l + r >> 1;
	if (ql <= mid) query(o << 1, l, mid);
	if (mid < qr) query(o << 1 | 1, mid + 1, r);
}
int main()
{
//	printf("%d\n", sizeof (tr) >> 20);
	int n, m;
	while (scanf("%d%d", &n, &m) != EOF)
	{
		for (int i = 1; i <= n; ++i)
			scanf("%d", a + i);
		build(1, 1, n);
		for (int i = 1; i <= m; ++i)
		{
			scanf("%d%d", &ql, &qr);
			cnt = 0;
			query(1, 1, n);
			ll ans = -1;
			for (int i = 1; i + 2 <= cnt; ++i)
				if (anss[i] < anss[i + 1] + anss[i + 2])
					ans < 0ll + anss[i] + anss[i + 1] + anss[i + 2]
						? ans = 0ll + anss[i] + anss[i + 1] + anss[i + 2]
						: 0;
			printf("%lld\n", ans);
		}
	}
	return 0;
}
