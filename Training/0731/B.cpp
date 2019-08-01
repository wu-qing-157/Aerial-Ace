#include <cstdio>
#include <algorithm>
#include <cstring>

#define maxn 200010
#define cmax(_a, _b) (_a < (_b) ? _a = (_b) : 0)
typedef long long ll;
int a[maxn], n, k, b[maxn], dp[maxn];
int hash[maxn], hcnt;
int tr[maxn];
void add(int x, int v)
{
	for (; x <= hcnt; x += x & -x) cmax(tr[x], v);
}
int query(int x)
{
	int ret = 0;
	for (; x; x -= x & -x) cmax(ret, tr[x]);
	return ret;
}
int check(int x)
{
	int minp = -1, minn = 0x7fffffff;
	for (int i = 1; i <= n; ++i)
		if (minn > a[i]) minp = i, minn = a[i];
	for (int i = 1, j = minp; i <= n; ++i, j = j % n + 1)
		b[i] = a[j];
	memset(tr, 0, (hcnt + 1) << 2);
	add(1, 1);
	for (int i = 2; i <= n; ++i)
	{
		int p = std::upper_bound(hash + 1, hash + hcnt + 1, x - hash[b[i]]) - hash - 1;
		dp[i] = query(p) + 1;
		add(b[i], dp[i]);
	}
	//for (int i = 1; i <= n; ++i) printf("%d ", dp[i]); puts("");
	for (int i = 2; i <= n; ++i)
		if (hash[b[i]] + hash[b[1]] <= x && dp[i] >= k) return 1;
	return 0;
}
int main()
{
	scanf("%d%d", &n, &k);
	ll left = 0, right = 0;
	for (int i = 1; i <= n; ++i) scanf("%d", a + i), right < a[i] ? right = a[i] : 0, hash[++hcnt] = a[i];
	right <<= 1;
	std::sort(hash + 1, hash + hcnt + 1);
	hcnt = std::unique(hash + 1, hash + hcnt + 1) - hash - 1;
	for (int i = 1; i <= n; ++i) a[i] = std::lower_bound(hash + 1, hash + hcnt + 1, a[i]) - hash;
	while (left < right)
	{
		ll mid = left + right >> 1;
		if (check(mid)) right = mid;
		else left = mid + 1;
	}
	printf("%lld\n", left);
	return 0;
}
/*
5 3
17 18 17 30 35

*/
