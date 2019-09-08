#include <cstdio>

int m;
int query(int n, int k, int rem = 0)
{
	if (k % m == rem)
	{
		return k / m + 1;
	}
	int num = (n - rem + m - 1) / m;
	return query(n - num, k - (k - rem + m) / m, m - 1 - (n - rem + m - 1) % m) + num;
}
int main()
{
	int T; scanf("%d", &T);
	for (; T; --T)
	{
		int n; scanf("%d%d", &n, &m); ++m;
		int q; scanf("%d", &q);
		for (; q; --q)
		{
			int k; scanf("%d", &k); --k;
			printf("%d\n", query(n, k));
		}
	}
	return 0;
}
