#include <cstdio>
#include <cstring>

#define maxn 100010
int tr[maxn * 32][2], tot, a[maxn];
int main()
{
	int T; scanf("%d", &T);
	for (; T; --T)
	{
		int n, ans = 0; scanf("%d", &n);
		tot = 1;
		int now = 1;
		for (int i = 31; ~i; --i)
		{
			int d = 0;
			if (!tr[now][d]) tr[now][d] = ++tot;
			now = tr[now][d];
		}
		for (int i = 1; i <= n; ++i)
		{
			scanf("%d", a + i);
			a[i] ^= a[i - 1];
			now = 1; int ret = 0;
			for (int j = 31; ~j; --j)
			{
				int d = a[i] >> j & 1;
				if (!tr[now][d ^ 1]) now = tr[now][d];
				else now = tr[now][d ^ 1], ret += 1 << j;
			}
			now = 1;
			for (int j = 31; ~j; --j)
			{
				int d = a[i] >> j & 1;
				if (!tr[now][d]) tr[now][d] = ++tot;
				now = tr[now][d];
			}
			ans < ret ? ans = ret : 0;
		}
		printf("%d\n", ans);
		memset(tr, 0, sizeof (tr));
	}
	return 0;
}
/*
2
5
3 7 7 7 0
5
3 8 2 6 4
*/
