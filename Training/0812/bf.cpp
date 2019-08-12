#include <cstdio>

#define maxn 400010
int c[maxn], q[maxn];
int main()
{
	int n; scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
	{
		int cc, a; scanf("%d%d", &cc, &a);
		int p = i;
		for (int j = i - 1; j && j >= i - a - 1; --j)
			if (c[j] == cc) p = j;
		if (p == i - a - 1) ++p;
		for (int j = i; j > p; --j)
			c[j] = c[j - 1], q[j] = q[j - 1];
		c[p] = cc; q[p] = i;
	}
	for (int j = 1; j <= n; ++j) printf("%d ", q[j]); puts("");
	return 0;
}
