#include <cstdio>

#define maxn 500010
int r[maxn], s[maxn], x[maxn], a[maxn], p[maxn];
const int mod = 1e9 + 7;
inline int qpow(int base, int power)
{
	int ret = 1;
	for (; power; power >>= 1, base = 1ll * base * base % mod)
		power & 1 ? ret = 1ll * ret * base % mod : 0;
	return ret;
}
int f[maxn], sum[maxn];
int main()
{
	int T; scanf("%d", &T);
	for (; T; --T)
	{
		int n, m; scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; ++i) scanf("%d%d%d%d", r + i, s + i, x + i, a + i), p[i] = 1ll * r[i] * qpow(s[i], mod - 2) % mod;
		for (int i = 1; i <= n; ++i)
		{
			f[i] = (a[i] + 1ll * (0ll + mod + a[i] + sum[i - 1] - sum[x[i] - 1]) * (mod + 1 - p[i]) % mod * qpow(p[i], mod - 2)) % mod;
			sum[i] = (sum[i - 1] + f[i]) % mod;
		}
		for (; m; --m)
		{
			int l, r; scanf("%d%d", &l, &r);
			printf("%d\n", (mod + sum[r - 1] - sum[l - 1]) % mod);
		}
	}
	return 0;
}
