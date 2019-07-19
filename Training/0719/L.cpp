#include <cstdio>

int main()
{
	//freopen("lazy.in", "r", stdin);
	int T; scanf("%d", &T);
	for (int Cas = 1; Cas <= T; ++Cas)
	{
		int n; scanf("%d", &n);
		printf("Case %d: %d\n", Cas, n - 1);
	}
	return 0;
}
