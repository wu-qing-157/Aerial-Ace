#include <cstdio>
#include <cstring>

#define maxn 100010
const int mod = 1e9 + 7;
const int oo = 1e5;
inline int qpow(int base, int power)
{
	int ret = 1;
	for (; power; power >>= 1, base = 1ll * base * base % mod)
		power & 1 ? ret = 1ll * ret * base % mod : 0;
	return ret;
}
int sum[maxn], a[maxn];
int main()
{
freopen("lcm.in", "r", stdin);
	int T; scanf("%d", &T);
	for (; T; --T)
	{
		memset(sum, 0, sizeof (sum));
		int n; scanf("%d", &n);
		for (int i = 1; i <= n; ++i) scanf("%d", a + i), (sum[a[i]] += a[i]) %= mod;
		for (int i = 1; i <= oo; ++i)
		{
			for (int j = 2 * i; j <= oo; j += i) (sum[i] += sum[j]) %= mod;
			sum[i] = 1ll * sum[i] * sum[i] % mod;
//			if (i <= 20) printf("%d ", sum[i]);
		}
		for (int i = oo; i; --i)
			for (int j = 2 * i; j <= oo; j += i)
				(sum[i] += mod - sum[j]) %= mod;
		int ans = 0 ;
		for (int i = 1; i <= oo; ++i)
			ans = (ans + 1ll * sum[i] * qpow(i, mod - 2)) % mod;
		printf("%d\n", ans);
	}
	return 0;
}
/*
2
4 2 6 12 15
5 2 3 7 11 12
*/
