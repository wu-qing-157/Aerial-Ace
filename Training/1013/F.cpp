#include <cstdio>
#include <cstring>

#define maxn 110
#define cmax(_a, _b) (_a < (_b) ? _a = (_b) : 0)
#define cmin(_a, _b) (_a > (_b) ? _a = (_b) : 0)
int a[maxn];
bool f[40];
int ret, maxx, n;
const int p[3] = {1, 2, 5};
void dfs(int step, int lim, int sum)
{
	if (step == 3)
	{
		bool flag = 1;
		for (int i = 1; i <= n; ++i)
			if (a[i] / 10 == maxx && lim == 20)
				flag &= f[a[i] % 10 + 10];
			else if (lim == 10)
				flag &= f[a[i] % 10];
			else flag &= f[a[i] % 10] | f[a[i] % 10 + 10];
		// for (int i = 0; i < 10; ++i) printf("%d", f[i]); puts("");
		// if (!sum) {for (int i = 0; i < 10; ++i) printf("%d", f[i]); puts("");}
		if (flag) cmin(ret, sum);
		return ;
	}
	bool g[40];
	memcpy(g, f, sizeof (g));
	dfs(step + 1, lim, sum);
	memcpy(f, g, sizeof (f));
	for (int i = 1; i * p[step] <= lim; ++i)
	{
		for (int j = lim - 1; j >= p[step]; --j)
			f[j] |= f[j - p[step]];
		memcpy(g, f, sizeof (g));
		dfs(step + 1, lim, sum + i);
		memcpy(f, g, sizeof (f));
	}
}
int main()
{
	int T; scanf("%d", &T);
	for (; T; --T)
	{
		scanf("%d", &n);
		bool flag = 0;
		int ans = 0x7fffffff; maxx = 0;
		for (int i = 1; i <= n; ++i)
		{
			scanf("%d", a + i);
			flag |= a[i] % 10 != 0;
			cmax(maxx, a[i] / 100);
			a[i] /= 10;
		}
		if (flag) puts("-1");
		else
		{
			ret = 0x7fffffff;
			memset(f, 0, sizeof (f)); f[0] = 1;
			dfs(0, 10, 0);
			cmin(ans, maxx + ret);

			if (maxx)
			{
				ret = 0x7fffffff;
				memset(f, 0, sizeof (f)); f[0] = 1;
				dfs(0, 20, 0);
				cmin(ans, maxx - 1 + ret);
			}
			
			printf("%d\n", ans);
		}
	}
	return 0;
}
