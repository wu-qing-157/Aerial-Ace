#include <cstdio>
#include <cstring>
#pragma GCC optimize(3)

#define maxn 50010
#define cmax(_a, _b) (_a < (_b) ? _a = (_b), 1 : 0)
int next[maxn], prev[maxn];
int f[maxn], g[maxn], a[maxn], b[maxn];

int main()
{
	int T; scanf("%d", &T);
	for (; T; --T)
	{
		int n; scanf("%d", &n);
		next[0] = n + 1;
		prev[n + 1] = 0;
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		memset(f, 0, (n + 1) << 2);
		int ans = 0;
		for (int i = 1; i <= n; ++i)
		{
			int x; scanf("%d", &x);
			for (int p = next[0]; ; p = next[p])
			{
				if (p > x)
				{
					next[prev[p]] = x;
					prev[x] = prev[p];
					next[x] = p;
					prev[p] = x;
					break;
				}
			}
			for (int p = prev[x]; p; p = prev[p])
				if (a[p] < a[x]) cmax(f[x], f[p] + 1) || (f[x] == f[p] + 1 && p > g[x]) ? g[x] = p : 0;
			cmax(ans, f[x]);
			for (int p = next[x]; p <= n; p = next[p])
			{
				if (a[p] > a[x]) cmax(f[p], f[x] + 1) || (f[p] == f[x] + 1 && x > g[p]) ? g[p] = x : 0;
				cmax(f[p], f[g[p]] + 1);
				cmax(ans, f[p]);
			}
			printf("%d%c", ans + 1, " \n"[i == n]);
		}
	}
	return 0;
}
