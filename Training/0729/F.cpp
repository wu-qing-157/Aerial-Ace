#include <cstdio>
#include <algorithm>
#include <cstring>

#define maxn 210
#define cmin(_a, _b) (_a > (_b) ? _a = (_b) : 0)
int d[maxn][maxn], f[maxn][maxn][maxn];
int w[maxn], ww[maxn], r[maxn];
inline bool cmp(int a, int b) {return w[a] < w[b];}
int main()
{
	int T; scanf("%d", &T);
	for (int Cas = 1; Cas <= T; ++Cas)
	{
		int n, q; scanf("%d%d", &n, &q);
		for (int i = 1; i <= n; ++i) scanf("%d", w + i), r[i] = i, ww[i] = w[i];
		memset(f, 63, sizeof (f));
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				scanf("%d", &d[i][j]), f[0][i][j] = d[i][j];
		std::sort(r + 1, r + n + 1, cmp);
		std::sort(ww + 1, ww + n + 1);
		for (int k = 1; k <= n; ++k)
		{
			int kk = r[k]; //printf("r %d\n", r[k]);
			memcpy(f[k], f[k - 1], sizeof (f[k]));
			for (int i = 1; i <= n; ++i)
				for (int j = 1; j <= n; ++j)
					cmin(f[k][i][j], f[k - 1][i][kk] + f[k - 1][kk][j]);
		}
		printf("Case #%d:\n", Cas);
		for (; q; --q)
		{
			int u, v, _w; scanf("%d%d%d", &u, &v, &_w);
			int nk = std::upper_bound(ww + 1, ww + n + 1, _w) - ww - 1;
			//printf("nk %d ", nk);
			printf("%d\n", f[nk][u][v]);
		}
	}
	return 0;
}
