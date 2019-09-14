#include <cstdio>
#include <cstring>
#include <algorithm>

#define maxn 110
typedef long long ll;
const int mod = 1e9 + 7;
int a[maxn << 1], aa[maxn][maxn], p[maxn];
inline int qpow(int base, int power)
{
	int ret = 1;
	for (; power; power >>= 1, base = 1ll * base * base % mod)
		power & 1 ? ret = 1ll * ret * base % mod : 0;
	return ret;
}
struct Matrix {
	int a[maxn][maxn], n;
	inline Matrix operator * (const Matrix &that) const
	{
		Matrix c; memset(c.a, 0, sizeof (c.a)); c.n = n;
		for (int k = 1; k <= n; ++k)
			for (int i = 1; i <= n; ++i)
				for (int j = 1; j <= n; ++j)
					c.a[i][j] = (c.a[i][j] + 1ll * a[i][k] * that.a[k][j]) % mod;
		return c;
	}
} base, ret;
void mpow(ll power)
{
	for (; power; power >>= 1, base = base * base)
		power & 1 ? ret = ret * base, 1 : 0;
}
int b[maxn];
int main()
{
	int T; scanf("%d", &T);
	for (; T; --T)
	{
		int k; ll n; scanf("%d%lld", &k, &n);
		for (int i = 1; i <= 2 * k; ++i) scanf("%d", a + i);
		if (n <= 2 * k) {printf("%d\n", a[n]); continue;}
		for (int i = 1; i <= k; ++i)
		{
			for (int j = 1; j <= k; ++j)
				aa[i][j] = a[i - j + k];
			aa[i][k + 1] = a[i + k];
		}
		for (int i = 1; i <= k; ++i)
		{
			if (!aa[i][i])
			{
				for (int j = i + 1; j <= k; ++j)
					if (aa[j][i])
					{
						for (int ii = i; ii <= k + 1; ++ii)
							std::swap(aa[i][ii], aa[j][ii]);
						break;
					}
			}
//			if (!aa[i][i]) continue;
			for (int j = i + 1; j <= k; ++j)
			{
				int tmp = 1ll * aa[j][i] * qpow(aa[i][i], mod - 2) % mod;
				for (int kk = i + 1; kk <= k + 1; ++kk)
				{
					aa[j][kk] = (aa[j][kk] - 1ll * tmp * aa[i][kk] % mod + mod) % mod;
				}
			}
		}
		p[k] = 1ll * aa[k][k + 1] * qpow(aa[k][k], mod - 2) % mod;
		for (int i = k - 1; i; --i)
		{
			for (int j = i + 1; j <= k; ++j)
				aa[i][k + 1] = (aa[i][k + 1] - 1ll * p[j] * aa[i][j] % mod + mod) % mod;
			p[i] = 1ll * aa[i][k + 1] * qpow(aa[i][i], mod - 2) % mod;
		}
//		for (int i = 1; i <= k; ++i) printf("%d ", p[i]); puts("");
		
		memset(base.a, 0, sizeof (base.a));
		memset(ret.a, 0, sizeof (ret.a));
		ret.n = k + 1;
		for (int i = 1; i <= k + 1; ++i) ret.a[i][i] = 1;
		base.n = k + 1;
		for (int i = 1; i < k; ++i)
			base.a[i][i + 1] = 1;
		for (int i = 1; i <= k; ++i)
			base.a[k][i] = base.a[k + 1][i] = p[k - i + 1];
		base.a[k + 1][k + 1] = 1;

		mpow(n - k); b[k + 1] = 0;
		for (int i = 1; i <= k; ++i)
			b[i] = a[i], (b[k + 1] += a[i]) %= mod;
			
			
		int sum = 0;
		for (int i = 1; i <= k + 1; ++i)
			sum = (sum + 1ll * b[i] * ret.a[k + 1][i]) % mod;
		printf("%d\n", sum);
	}
	return 0;
}
