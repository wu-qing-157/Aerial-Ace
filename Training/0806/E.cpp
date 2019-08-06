#include <cstdio>

#define maxn 3010
const int mod = 998244353;
int C[maxn][maxn], f[maxn];
inline int qpow(int base, int power)
{
	int ret = 1;
	for (; power; power >>= 1, base = 1ll * base * base % mod)
		power & 1 ? ret = 1ll * ret * base % mod : 0;
	return ret;
}
int main()
{
	for (int i = 0; i <= 3000; ++i)
	{
		C[i][0] = 1;
		for (int j = 1; j <= i; ++j)
			C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
	}
	f[0] = 0;
	for (int i = 1; i <= 3000; ++i)
	{
		int qp = qpow(2, i), inp = qpow(qp - 1, mod - 2), inp2 = qpow(2, mod - 2);
		int inpp = qpow(qp, mod - 2);
		int ret = 1ll * i * (i - 1) % mod * inp2 % mod * inp2 % mod;
		for (int j = 0; j <= i - 1; ++j)
			ret = (ret + 1ll * C[i][j] * f[j] % mod * inpp) % mod;
		ret = 1ll * ret * qp % mod * inp % mod;
		f[i] = ret;
		//if (i <= 10) printf("f[%d] = %d\n", i, f[i]);
	}
	int n;
	while (scanf("%d", &n) != EOF)
	{
		int inv = qpow(n, mod - 2);
		int ans = 0;
		for (int i = 1; i <= n; ++i)
			ans = (ans + 1ll * inv * f[i]) % mod;
		printf("%d\n", ans);
	}
	return 0;
}
