#include <cstdio>

#define maxn 1000010
int ans[11][maxn];
int main()
{
	for (int b = 2; b <= 10; ++b)
	{
		int *ansb = ans[b];
		for (int i = 1; i < maxn; ++i)
			ansb[i] = ansb[i / b] + i % b;
		for (int i = 1; i < maxn; ++i)
			ansb[i] += ansb[i - 1];
	}
	int T; scanf("%d", &T);
	for (int Cas = 1; Cas <= T; ++Cas)
	{
		int n, b; scanf("%d%d", &n, &b);
		printf("Case #%d: %d\n", Cas, ans[b][n]);
	}
	return 0;
}
