
#include <cstdio>
typedef long long ll;
typedef __int128 lll;
int k;
int a[233];
int C[20][20];
int f[233];
lll gcd(lll a, lll b) {return !b ? a : gcd(b, a % b);}
lll gg[1 << 15];
ll check(ll x)
{
	__int128 ret = 0;
	for (int S = 1; S < (1 << k); ++S)
	{
		__int128 tmp = 1; int minus = -1, num = 0;
		bool flag = 1;
		for (int i = 1; i <= k; ++i)
			if (S >> (i - 1) & 1)
			{
				minus = -minus;
				++num;
			}
		if (gg[S] > x) flag = 0;
		if (!flag) continue;
		ret += x / gg[S] * minus * num;
	}
	return (ll) ret;
}
int main()
{
	int T; scanf("%d", &T);
	for (; T; --T)
	{
		ll n; scanf("%d%lld", &k, &n);
		for (int i = 1; i <= k; ++i) scanf("%d", a + i);
		for (int S = 1; S < (1 << k); ++S)
		{
			lll tmp = 1;
			for (int i = 1; i <= k; ++i)
			if (S >> (i - 1) & 1)
			{
				tmp = tmp * a[i] / gcd(tmp, a[i]);
				if (tmp > 1e18) tmp = 1e18;
			}
			gg[S] = tmp;
		}
		ll left = 0, right = 1e15 + 1;
		while (left < right)
		{
			ll mid = left + right >> 1;
			if (check(mid) >= n) right = mid;
			else left = mid + 1;
		}
		printf("%lld\n", left);
	}
	return 0;
}
/*
2
2 4
2 3
3 10
6 11 20

4 1
2 3 5 7
*/
