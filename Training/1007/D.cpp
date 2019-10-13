#include <cstdio>
#include <algorithm>

#define maxn 300010
long long a[maxn], b[maxn];
int n, k;
inline bool check(int x)
{
	for (int i = 1; i <= x; ++i) b[i] = a[i];
	for (int i = 2, p = x + 1; i <= k; ++i)
		for (int j = 1; j <= x; ++j)
		{
			while (p <= n && a[p] < b[j] * 2) ++p;
			if (p > n) return 0;
			b[j] = a[p++];
		}
	return 1;
}
int main()
{
	int T; scanf("%d", &T);
	for (int Cas = 1; Cas <= T; ++Cas)
	{
		scanf("%d%d", &n, &k);
		for (int i = 1; i <= n; ++i) scanf("%lld", a + i);
		std::sort(a + 1, a + n + 1);
		int left = 0, right = n / k;
		// for (int i = 0; i <= right; ++i) printf("%d", check(i)); puts("");
		while (left < right)
		{
			int mid = left + right + 1 >> 1;
			if (check(mid)) left = mid;
			else right = mid - 1;
		}
		printf("Case #%d: %d\n", Cas, left);
	}
	return 0;
}
/*
3
4 2
1 2 3 4
6 3
1 1 2 2 4 4
6 3
1 1 2 2 3 4
*/
