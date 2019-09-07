#include <cstdio>
#include <cstring>

#define maxn 1000010
#define cmax(_a, _b) (_a < (_b) ? _a = (_b) : 0)
#define dmax(_a, _b) ((_a) > (_b) ? (_a) : (_b))
#define cmin(_a, _b) (_a > (_b) ? _a = (_b) : 0)
int s[maxn], t[maxn];
int f[maxn], tr[668];
void modify(int x, int v)
{
	for (; x; x -= x & -x) cmin(tr[x], v);
}
int query(int x)
{
	int ret = 0x7fffffff;
	for (; x <= 666; x += x & -x) cmin(ret, tr[x]);
	return ret;
}
int main()
{
	int n, m; scanf("%d%d\n", &n, &m);
	for (int i = 1; i <= n; ++i) s[i] = getchar() + 133; getchar();
	for (int i = 1; i <= m; ++i) t[i] = getchar() + 133;
	
	for (int i = 0; i <= 666; ++i) tr[i] = n + 1;
	int p = 0;
	for (int i = 1; i <= n; ++i)
	{
		if (p < m && s[i] == t[p + 1]) ++p;
		f[i] = p;
	}
	int anss = -1;
	for (int i = n; i; --i)
	{
		int ret = n - query(t[f[i] + 1] + 1) + 1;
		printf("%d %d\n", f[i], ret);
		cmax(anss, ret + f[i]);
		modify(s[i], i);
	}
	printf("%d\n", anss);
	return 0;
}
