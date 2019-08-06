#include <cstdio>

const int mod = 1e6 + 3;
int main()
{
	int n;
	while (scanf("%d", &n) != EOF)
	{
		int ans = 1;
		for (int i = 1; i <= n; ++i)
		{
			ans = 1ll * ans * i % mod;
			if (!ans) break;
		}
		printf("%d\n", ans);
	}
	return 0;
}
