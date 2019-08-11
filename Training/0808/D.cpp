#include <cstdio>
#include <algorithm>
#include <cstring>

#define maxn 200010
#define cmax(_a, _b) (_a < (_b) ? _a = (_b) : 0)
typedef long long ll;
int tr[maxn], a[maxn], hcnt, n, m, dp[maxn];
ll sum[maxn], hash[maxn];
const int oo = 2e9;
inline int query(int x)
{
	int ret = -0x3f3f3f3f;
	for (; x <= hcnt; x += x & -x) cmax(ret, tr[x]);
	return ret;
}
inline void modify(int x, int v)
{
	for (; x; x -= x & -x) cmax(tr[x], v);
}
inline bool check(ll w)
{
	memset(tr, -63, (hcnt + 1) << 2);
	for (int i = 0; i <= n; ++i)
	{
		if (i)
		{
			int pos = std::lower_bound(hash + 1, hash + hcnt + 1, hash[sum[i]] - w) - hash;
			dp[i] = query(pos) + 1;
		}
		else dp[i] = 0;
		if (dp[i] >= m) return true;
		modify(sum[i], dp[i]);
	}
	return false;
}
int main()
{
	int T; scanf("%d", &T);
	for (; T; --T)
	{
		scanf("%d%d", &n, &m);
		hcnt = 0; hash[++hcnt] = 0; sum[0] = 0;
		for (int i = 1; i <= n; ++i)
		{
			scanf("%d", a + i); sum[i] = sum[i - 1] + a[i];
			hash[++hcnt] = sum[i];
		}
		std::sort(hash + 1, hash + hcnt + 1);
		hcnt = std::unique(hash + 1, hash + hcnt + 1) - hash - 1;
		for (int i = 0; i <= n; ++i) sum[i] = std::lower_bound(hash + 1, hash + hcnt + 1, sum[i]) - hash;
		ll left = 1ll * n * -oo, right = 1ll * n * oo;
		while (left < right)
		{
			ll mid = left + right >> 1;
			if (check(mid)) right = mid;
			else left = mid + 1;
		}
		printf("%lld\n", left);
	}
	return 0;
}
/*

*/
