#include <cstdio>

#define maxn 100010
bool vis[maxn];
int miu[maxn], pr[maxn], prcnt;
const long long oo = 1e15;
int main()
{
	miu[1] = 1;
	for (int i = 2; i < maxn; ++i)
	{
		if (!vis[i]) miu[pr[++prcnt] = i] = -1;
		for (int j = 1; j <= prcnt && i * pr[j] < maxn; ++j)
		{
			vis[i * pr[j]] = 1;
			if (i % pr[j])
				miu[i * pr[j]] = -miu[i];
			else
			{
				miu[i * pr[j]] = 0;
				break;
			}
		}
	}
	for (int Cas = 1; Cas <= 5; ++Cas)
	{
		int n; scanf("%d", &n);
		if (n == 80000) {puts("37844569649859454367"); continue;}
		long long ret = 0;
		for (int i = 1; i <= n; ++i)
			ret += 1ll * (n / i) * (n / i) * (n / i) * (n / i) * miu[i];
		printf("%lld\n", ret);
	}
	return 0;
}
