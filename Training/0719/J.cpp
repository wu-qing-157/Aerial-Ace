#include <cstdio>

#define maxn 510
typedef long long ll;
ll f[maxn];
int main()
{
	freopen("jacking.in", "r", stdin);
	int T; scanf("%d", &T);
	for (int Cas = 1; Cas <= T; ++Cas)
	{
		int N; scanf("%d", &N);
		for (int i = 1; i <= N; ++i) scanf("%lld", f + i);
		int Q; scanf("%d", &Q);
		printf("Case %d:\n", Cas);
		for (; Q; --Q)
		{
			int n, m; scanf("%d%d", &n, &m);
			int low = n / m, up = low + 1;
			int up_num = n % m, low_num = m - up_num;
			if (m > n) puts("impossible");
			else printf("%lld\n", f[low] * low_num + f[up] * up_num);
		}
	}
	return 0;
}
/*
2
3 1 1 1
2
3 1
2 1
6 15 12 10 13 19 28
5
1 1
1 4
4 3
4 4
6 6
*/
