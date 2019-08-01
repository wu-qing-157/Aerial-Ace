#include <cstdio>

#define maxn 200010
int C[210][210];
int f[32][maxn], ans[maxn];
int main()
{
	/*for (int i = 0; i <= 100; ++i)
	{
		C[i][0] = 1;
		for (int j = 1; j <= i; ++j)
			C[i][j] = C[i - 1][j] ^ C[i - 1][j - 1];
	}
	for (int i = 0; i <= 31; ++i, puts(""))
	{
		printf("m = %2d: ", i);
		for (int j = 0; j <= 31; ++j) printf("%d ", C[i + j - 1][j]);
	}*/
	int T; scanf("%d", &T);
	for (; T; --T)
	{
		int n, m; scanf("%d%d", &n, &m); --m;
		for (int i = 1; i <= n; ++i) scanf("%d", &f[0][i]);
		for (int j = 0; j <= 30; ++j)
		{
			for (int i = 1, lst = 0; i <= n; ++i)
			{
				if (i <= (1 << j)) lst = 0;
				else lst = f[j][i - (1 << j)];
				if (!(m & (1 << j)))
				f[j + 1][i] = f[j][i] ^ lst;
				else f[j + 1][i] = f[j][i];
			}
		}
		for (int i = 1; i <= n; ++i) printf("%d%c", f[31][i], " \n"[i == n]);
	}
	return 0;
}
