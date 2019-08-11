#include <cstdio>
#include <algorithm>

#define maxn 200010
typedef long long ll;
int tr_cnt[maxn << 2], a[maxn], hash[maxn], hcnt;
ll tr_sum[maxn << 2];
void build(int o, int l, int r)
{
	tr_cnt[o] = tr_sum[o] = 0;
	if (l == r) return ;
	int mid = l + r >> 1;
	build(o << 1, l, mid);
	build(o << 1 | 1, mid + 1, r);
}
void update(int o)
{
	tr_cnt[o] = tr_cnt[o << 1] + tr_cnt[o << 1 | 1];
	tr_sum[o] = tr_sum[o << 1] + tr_sum[o << 1 | 1];
}
int ql, qv, ret;
void modify(int o, int l, int r)
{
	if (l == r)
	{
		++tr_cnt[o];
		tr_sum[o] += hash[l];
		return ;
	}
	int mid = l + r >> 1;
	if (ql <= mid) modify(o << 1, l, mid);
	else modify(o << 1 | 1, mid + 1, r);
	update(o);
}
void query(int o, int l, int r)
{
	if (l == r)
	{
		ret += std::min(qv / hash[l], tr_cnt[o]);
		return ;
	}
	int mid = l + r >> 1;
	if (tr_sum[o << 1] < qv) qv -= tr_sum[o << 1], ret += tr_cnt[o << 1], query(o << 1 | 1, mid + 1, r);
	else query(o << 1, l, mid);
}
int main()
{
	int T; scanf("%d", &T);
	for (; T; --T)
	{
		int n, m; scanf("%d%d", &n, &m);
		hcnt = 0;
		for (int i = 1; i <= n; ++i)
		{
			scanf("%d", a + i);
			hash[++hcnt] = a[i];
		}
		std::sort(hash + 1, hash + hcnt + 1);
		hcnt = std::unique(hash + 1, hash + hcnt + 1) - hash - 1;
		for (int i = 1; i <= n; ++i) a[i] = std::lower_bound(hash + 1, hash + hcnt + 1, a[i]) - hash;
		build(1, 1, hcnt);
		for (int i = 1; i <= n; ++i)
		{
			qv = m - hash[a[i]]; ret = 0;
			query(1, 1, hcnt);
			printf("%d%c", i - 1 - ret, " \n"[i == n]);
			ql = a[i]; modify(1, 1, hcnt);
		}
	}
	return 0;
}
/*

*/
