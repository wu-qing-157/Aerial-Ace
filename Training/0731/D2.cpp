#include <cstdio>
#include <algorithm>

#define maxn 300010
#define cmax(_a, _b) (_a < (_b) ? _a = (_b) : 0)
typedef long long ll;
struct Girl {
	int l, r, p;
	inline bool operator < (const Girl &that) const {return p > that.p;}
} g[maxn];
int r[maxn], a[maxn];
int main()
{
	int n, m; scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; ++i) scanf("%d", a + i);
	for (int i = 1; i <= n; ++i) scanf("%d%d%d", &g[i].l, &g[i].r, &g[i].p);
	std::sort(g + 1, g + n + 1);
	ll ans = 0;
	for (int i = 1; i <= n; ++i)
	{
		int maxr = g[i].r;
		for (int j = g[i].l; j <= maxr; ++j)
		{
			if (a[j])
			{
				ans += g[i].p;
				--a[j];
				cmax(r[j], g[i].r);
				break;
			}
			else cmax(maxr, r[j]);
		}
	}
	printf("%lld\n", ans);
	return 0;
}
