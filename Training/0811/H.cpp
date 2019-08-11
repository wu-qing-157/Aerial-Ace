#include <cstdio>

#define cmin(_a, _b) (_a > (_b) ? _a = (_b) : 0)
typedef unsigned long long ll;
ll gcd(ll a, ll b) {return !b ? a : gcd(b, a % b);}
int main()
{
	int T; scanf("%d", &T);
	for (; T; --T)
	{
		ll k; int m; scanf("%lld%d", &k, &m);
		ll ans = -1;
		for (int i = 1; i <= 10 * m; ++i)
		{
			ll n = k ^ i;
			if (gcd(n + i, n) == 1)
			{
				int cnt = 0;
				for (int j = 1; j < i; ++j)
					cnt += gcd(n + j, n) == 1;
				if (cnt == m - 1) cmin(ans, n);
			}
		}
		printf("%lld\n", (long long) ans);
	}
	return 0;
}
