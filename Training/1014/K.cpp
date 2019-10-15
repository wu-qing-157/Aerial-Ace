#include <cstdio>
#include <cstring>

#define maxn 100010
#define maxm 1010
typedef long long ll;
int cnt[maxm][maxm], cn[maxm];
ll c[maxm];
void add(int a, int b, int v)
{
	c[a] += (b / a) * v;
	cn[a] += v;
	for (int x = b % a + 1; x <= a; x += x & -x)
		cnt[a][x] += v;
}
ll check(ll x)
{
	ll ret = 0;
	for (int i = 1; i <= 1000; ++i)
	{
		ret += x / i * cn[i] - c[i];
		ret -= cn[i];
		for (int p = x % i + 1; p; p -= p & -p)
			ret += cnt[i][p];
	}
	return ret;
}
int a[maxn], b[maxn];
int main()
{
	int T; scanf("%d", &T);
	for (; T; --T)
	{
		int n, m; scanf("%d%d", &n, &m);
		memset(cnt, 0, sizeof (cnt)); memset(cn, 0, sizeof (cn)); memset(c, 0, sizeof (c));
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		for (int i = 1; i <= n; ++i) scanf("%d", b + i);
		for (int i = 1; i <= n; ++i) add(a[i], b[i], 1);
		for (; m; --m)
		{
			int opt; scanf("%d", &opt);
			if (opt == 1)
			{
				int x, y; scanf("%d%d", &x, &y);
				add(a[x], b[x], -1);
				a[x] = y;
				add(a[x], b[x], 1);
			}
			else if (opt == 2)
			{
				int x, y; scanf("%d%d", &x, &y);
				add(a[x], b[x], -1);
				b[x] = y;
				add(a[x], b[x], 1);
			}
			else
			{
				int k; scanf("%d", &k);
				ll left = 0, right = 1e14;
				while (left < right)
				{
					ll mid = left + right >> 1;
					if (check(mid) < k) left = mid + 1;
					else right = mid;
				}
				printf("%lld\n", left);
			}
		}
	}
	return 0;
}
