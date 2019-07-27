#include <cstdio>

int miu[110];
bool vis[110];
int pr[110], prcnt;
int main()
{
	int T; scanf("%d", &T);
	miu[1] = 1;
	for (int i = 2; i <= 100; ++i)
	{
		if (!vis[i]) pr[++prcnt] = i, miu[i] = -1;
		for (int j = 1; j <= prcnt && i * pr[j] <= 100; ++j)
		{
			vis[i * pr[j]] = 1;
			miu[i * pr[j]] = -miu[i];
			if (i % pr[j] == 0)
			{
				miu[i * pr[j]] = 0;
				break;
			}
		}
	}
	for (; T; --T)
	{
		int n; scanf("%d", &n);
		int ans = 0;
		for (int i = 1; i <= n; ++i)
			ans += miu[i] * ((n / i + 1) * (n / i + 1) * (n / i + 1) - 1);
		printf("%d\n", ans);
	}
	return 0;
}
