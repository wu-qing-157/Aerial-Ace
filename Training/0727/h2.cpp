#include <cstdio>
#include <cstring>

const int oo = 1e6;
int vis[1000010];
int a[233];
int main()
{
	int T; scanf("%d", &T);
	for (; T; --T)
	{
		int k, n; scanf("%d%d", &k, &n);
		memset(vis, 0, sizeof (vis));
		for (int i = 1; i <= k; ++i) scanf("%d", a + i);
		for (int i = 1; i <= k; ++i)
		{
			for (int j = a[i]; j <= oo; j += a[i])
				++vis[j];
		}
		int ans = 0;
		for (int j = 1; j <= oo; ++j) if (vis[j] == 1) --n == 0 ? ans = j : 0;
		printf("%d\n", ans);
	}
	return 0;
}
