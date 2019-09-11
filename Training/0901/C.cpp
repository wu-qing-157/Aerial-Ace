#include <cstdio>

#define maxn 100010
const int mod = 998244353;
bool vis[maxn];
int phi[maxn], pr[maxn], prcnt;
inline int qpow(int base, int power)
{
	int ret = 1;
	for (; power; power >>= 1, base = 1ll * base * base % mod)
		power & 1 ? ret = 1ll * ret * base % mod : 0;
	return ret;
}
int main()
{
	phi[1] = 1; int n = 1e5;
	for (int i = 2; i <= n; ++i)
	{
		if (!vis[i]) phi[pr[++prcnt] = i] = i - 1;
		for (int j = 1; j <= prcnt && i * pr[j] <= n; ++j)
		{
			vis[i * pr[j]] = 1;
			if (i % pr[j])
				phi[i * pr[j]] = phi[i] * (pr[j] - 1);
			else
			{
				phi[i * pr[j]] = phi[i] * pr[j];
				break;
			}
		}
	}
	//for (int i = 1; i <= n; ++i) printf("%d ", phi[i]);puts("");
	int ans = 0;
	FILE *out = fopen("out", "w");
	FILE *fans = fopen("ans", "w");
	printf("{");
	fprintf(out, "{");
	for (int nn = 1; nn <= n; ++nn)
	{
		for (int i = 1; i <= nn; ++i)
			ans = (ans + (1ll + (i != nn)) * phi[i] * phi[nn] % mod * qpow(2, 1ll * phi[i] * phi[nn] % (mod - 1))) % mod;
		/*ans = 0;
		for (int i = 1; i <= nn; ++i)
			for (int j = 1; j <= nn; ++j)
				ans = (ans + 1ll * phi[i] * phi[j] * qpow(2, phi[i] * phi[j])) % mod;*/
		fprintf(fans, "ans[%d] = %d\n", nn, ans);
		if (nn % 300 == 0) fprintf(out, "%d,",ans);
	}
	printf("}");
	fprintf(out, "}");
	return 0;
}
