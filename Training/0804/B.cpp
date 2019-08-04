#include <cstdio>
#include <cstring>
#include <algorithm>

#define maxn 1000010
int ret[33];
int tr[1048577 << 1][30];
int ql, qr, qv;
void clear(int o, int l, int r)
{
	memset(tr[o], 0, sizeof (tr[o]));
	if (l == r) return ;
	int mid = l + r >> 1;
	clear(o << 1, l, mid);
	clear(o << 1 | 1, mid + 1, r);
}
void insert(int *base, int x)
{
	for (; x; )
	{
		int tmp = __builtin_ctz(x);
		if (!base[tmp])
		{
			base[tmp] = x;
			break;
		}
		x ^= base[tmp];
	}
}
void insert(int o, int l, int r)
{
	insert(tr[o], qv);
	if (l == r) return ;
	int mid = l + r >> 1;
	if (ql <= mid) insert(o << 1, l, mid);
	else insert(o << 1 | 1, mid + 1, r);
}
int *st[200];
int cnt;
void query(int o, int l, int r)
{
	if (ql <= l && r <= qr)
	{
		st[++cnt] = tr[o];
		return ;
	}
	int mid = l + r >> 1;
	if (ql <= mid) query(o << 1, l, mid);
	if (mid < qr) query(o << 1 | 1, mid + 1, r);
}
int main()
{
	int T; scanf("%d", &T);
	for (; T; --T)
	{
		int n, m, ans = 0; scanf("%d%d", &n, &m);
		int ll = n + m;
		clear(1, 1, ll);
		for (int i = 1; i <= n; ++i)
		{
			int x; scanf("%d", &x);
			ql = i; qv = x;
			insert(1, 1, ll);
		}
		for (; m; --m)
		{
			int opt; scanf("%d", &opt);
			if (opt == 0)
			{
				scanf("%d%d", &ql, &qr); ql ^= ans; qr ^= ans;
				ql %= n; ++ql; qr %= n; ++qr;
				if (ql > qr) std::swap(ql, qr);
				cnt = 0; ans = 0;
				query(1, 1, ll);
				for (int i = 29; ~i; --i)
					for (int j = 1; j <= cnt; ++j)
					{
						if (ans ^ st[j][i] > ans)
							ans = ans ^ st[j][i];
					}
				printf("%d\n", ans);
			}
			else
			{
				scanf("%d", &qv); ql = ++n; qv ^= ans;
				insert(1, 1, ll);
			}
		}
	}
	return 0;
}
/*

*/
