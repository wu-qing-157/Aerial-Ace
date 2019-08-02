#include <cstdio>

int main()
{
	int n; scanf("%d", &n);
	int ans = 0;
	for (int i = 1; i <= n; ++i)
	{
		int x; scanf("%d", &x);
		if (x <= 35) ++ans;
	}
	printf("%d\n", ans);
	return 0;
}
