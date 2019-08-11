#include <cstdio>
#include <cstring>
#pragma GCC optimize(3)

#define maxn 50010
#define cmax(_a, _b) (_a < (_b) ? _a = (_b), 1 : 0)
int f[maxn], g[maxn], a[maxn], b[maxn], tr[maxn], ans, n, anss[maxn];
bool vis[maxn], del[maxn];
inline int query(int x)
{
	int ret = 0;
	for (; x; x -= x & -x) cmax(ret, tr[x]);
	return ret;
}
inline void modify(int x, int v)
{
	for (; x <= n; x += x & -x) cmax(tr[x], v);
}
inline void build()
{
	memset(tr, 0, (n + 1) << 2);
	memset(f, 0, (n + 1) << 2);
	memset(vis, 0, n + 1);
	ans = 0;
	for (int i = 1; i <= n; ++i)
		if (!del[i])
		{
			f[i] = query(a[i]) + 1;
			cmax(ans, f[i]);
			modify(a[i], f[i]);
		}
	int lst = n + 1;
	for (int i = n, pos = ans; i && pos; --i)
		if (!del[i] && f[i] == pos && a[i] < lst)
			vis[i] = 1, --pos, lst = a[i];
}
int main()
{
	int T; scanf("%d", &T);
	for (; T; --T)
	{
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		memset(del, 0, n + 1);
		build();
		for (int i = 1; i <= n; ++i) scanf("%d", b + i);
		for (int i = n; i; --i)
		{
			anss[i] = ans;
			del[b[i]] = 1;
			if (vis[b[i]]) build();
		}
		for (int i = 1; i <= n; ++i) printf("%d%c", anss[i], " \n"[i == n]);
	}
	return 0;
}
