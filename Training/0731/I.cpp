#include <cstdio>
#include <cassert>

#define maxm 2000
struct edge {int a, b;} e[maxm];
int ans, c[233], k, n, m;
void dfs(int x)
{
	if (x > n)
	{
		bool ret = 1;
		for (int i = 1; i <= m; ++i)
			if (c[e[i].a] == c[e[i].b]) ret = 0;
		ans += ret;
		return ;
	}
	for (int i = 1; i <= k; ++i)
	{
		c[x] = i;
		dfs(x + 1);
	}
}
int main()
{
	scanf("%d%d", &n, &m);
	assert(n < 7);
	for (int i = 1; i <= m; ++i)
		scanf("%d%d", &e[i].a, &e[i].b);
	for (int i = 1; i <= n; ++i)
	{
		for (k = 1; k <= n; ++k)
		{
			ans = 0;
			dfs(1);
			printf("%d%c", ans, " \n"[k == n]);
		}
	}
	return 0;
}
