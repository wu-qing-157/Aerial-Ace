#include <cstdio>

int n, ans;
void dfs(int step, int maxx, int fact, int sum)
{
	if (n - step + sum < fact) return ;
	if (n - step + sum == fact)
	{
		++ans; return ;
	}
	for (int i = maxx; i >= 2; --i)
		dfs(step + 1, i, fact * i, sum + i);
}
int main()
{
	freopen("sump.in", "r", stdin);
	freopen("sump.out", "w", stdout);
	scanf("%d", &n);
	dfs(0, n, 1, 0);
	printf("%d\n", ans);
	return 0;
}
