#pragma GCC optimize("-O3")
#include <cstdio>
#include <algorithm>
#include <cmath>

#define maxn 100010
typedef long long ll;
int size, a[maxn];
struct Query {
	int l, r, id;
	inline bool operator < (const Query &that) const {return l / size != that.l / size ? l < that.l : ((l / size) & 1 ? r < that.r : r > that.r);}
} q[maxn];
#define maxx 10000010
int pr[maxx / 10], prcnt, mp[maxx];
bool vis[maxx];
unsigned tot, ans[maxn], sum[maxx];
int tp[233], tpcnt, pnum[233];
void dfs(int step, int x, int v, int mi)
{
	if (step > tpcnt)
	{
		unsigned v1 = mi * ((unsigned) v / x) * (sum[x] + v + sum[x]);
		sum[x] += v;
		tot += v1;
		return ;
	}
	dfs(step + 1, x, v, mi);
	dfs(step + 1, x * tp[step], v, -mi);
}
void add(int ps, int v)
{
	int now = a[ps];
	tpcnt = 0;
	for (; now != 1; )
	{
		int np = mp[now]; tp[++tpcnt] = np;
		while (now % np == 0) now /= np, ++pnum[tpcnt];
	}
	dfs(1, 1, v * a[ps], 1);
}
int main()
{
	int T; scanf("%d", &T);
	for (int i = 2; i < maxx; ++i)
	{
		if (!vis[i]) pr[++prcnt] = i, mp[i] = i;
		for (int j = 1; j <= prcnt && 1ll * i * pr[j] < maxx; ++j)
		{
			vis[i * pr[j]] = 1;
			mp[i * pr[j]] = pr[j];
			if (i % pr[j] == 0) break;
		}
	}
	for (; T; --T)
	{
		int n, m; scanf("%d%d", &n, &m); size = sqrt(n * 3.0);
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		for (int i = 1; i <= m; ++i) scanf("%d%d", &q[i].l, &q[i].r), q[i].id = i;
		std::sort(q + 1, q + m + 1);
		int l = 1, r = 0; tot = 0;
		for (int i = 1; i <= m; ++i)
		{
			for (; r < q[i].r; ) add(++r, 1);
			for (; r > q[i].r; ) add(r--, -1);
			for (; l < q[i].l; ) add(l++, -1);
			for (; l > q[i].l; ) add(--l, 1);
			ans[q[i].id] = tot;
		}
		for (int i = 1; i <= m; ++i) printf("%u\n", ans[i]);
		for (int i = l; i <= r; ++i) add(i, -1);
	}
	return 0;
}
