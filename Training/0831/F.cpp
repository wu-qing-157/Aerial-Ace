#include <cstdio>
#include <algorithm>

#define maxn 210
int a[maxn][maxn], f[maxn][maxn][maxn];
int r[maxn], ra[maxn];
inline bool cmp(int a, int b)
{
	return r[a] < r[b];
}
int main()
{
	int T; scanf("%d", &T);
	for (int Cas = 1; Cas <= T; ++Cas)
	{
		int n, m; scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				scanf("%d", &a[i][j]);
		for (int i = 1; i <= n; ++i) scanf("%d", r + i), ra[i] = i;
		std::sort(ra + 1, ra + n + 1, cmp);
		for ()
	}
	return 0;
}
