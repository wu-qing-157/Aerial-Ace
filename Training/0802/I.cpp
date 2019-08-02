#include <cstdio>
#include <algorithm>
#include <cstring>

#define maxn 410
const int mod = 998244353;
int deg[maxn], pw[maxn * 510], a[maxn][maxn];
inline int qpow(int base, int power)
{
	int ret = 1;
	for (; power; power >>= 1, base = 1ll * base * base % mod)
		power & 1 ? ret = 1ll * ret * base % mod : 0;
	return ret;
}
int main()
{
	int n; pw[0] = 1;
	for (int i = 1; i < 510 * 410; ++i) pw[i] = 1ll * pw[i - 1] * i % mod;
	while (scanf("%d", &n) != EOF)
	{
		memset(deg, 0, (n + 1) << 2);
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				scanf("%d", &a[i][j]), a[i][j] = -a[i][j];
		int ret = 1;
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				deg[j] += a[i][j];
		for (int i = 1; i <= n; ++i)
		{
			a[i][i] -= deg[i];
			ret = 1ll * ret * pw[-deg[i] - 1] % mod;
			printf("%d ", deg[i]);
		} puts("");
		for (int i = 1; i <= n; ++i, puts(""))
			for (int j = 1; j <= n; ++j)
				printf("%d ", a[i][j]);
		for (int i = 1; i < n; ++i)
		{
			if (a[i][i] == 0)
			{
				for (int j = i + 1; j < n; ++j)
					if (a[j][i] != 0)
					{
						ret = mod - ret;
						for (int k = i; k < n; ++k)
							std::swap(a[i][k], a[j][k]);
						break;
					}
			}
			if (a[i][i] == 0)
			{
				ret = 0;
				break;
			}
			ret = 1ll * ret * a[i][i] % mod;
			for (int j = i + 1; j < n; ++j)
			{
				int temp = 1ll * a[j][i] * qpow(a[i][i], mod - 2) % mod;
				for (int k = i; k < n; ++k)
					a[j][k] = (a[j][k] - a[i][k] * temp % mod + mod) % mod;
			}
		}
		printf("%d\n", ret);
	}
	return 0;
}
/*
2
1 2
2 1
4
1 0 0 2
0 3 0 1
2 1 0 0
0 0 3 1
4
0 1 0 0
1 0 0 0
0 0 0 1
0 0 1 0

2
1 2
2 1
-3 -3 
2 -2 
-2 2 
8
4
1 0 0 2
0 3 0 1
2 1 0 0
0 0 3 1
-3 -4 -3 -4 
2 0 0 -2 
0 1 0 -1 
-2 -1 3 0 
0 0 -3 3 
864
4
0 1 0 0
1 0 0 0
0 0 0 1
0 0 1 0
-1 -1 -1 -1 
1 -1 0 0 
-1 1 0 0 
0 0 1 -1 
0 0 -1 1 
0

*/
