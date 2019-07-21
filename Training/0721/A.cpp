#include <cstdio>
#include <algorithm>
#include <cassert>

#define maxn 110
#define cmin(_a, _b) (_a > (_b) ? _a = (_b) , 1 : 0)
typedef long double db;
int p[maxn], q[maxn], s[maxn];
int main()
{
freopen("academy.in", "r", stdin);
freopen("academy.out", "w", stdout);
	int n, a, b; scanf("%d%d%d", &n, &a, &b);
	for (int i = 1; i <= n; ++i)
		scanf("%d%d%d", p + i, q + i, s + i);
	db ans = 1.0 / 0.0, ansx = 0.0;
	for (int i = 1; i <= n; ++i)
	{
		db x = (db) p[i] / (db) s[i], sum = b * x;
		assert(s[i] != 0);
		assert(q[i] != 0);
		for (int j = 1; j <= n; ++j)
			sum += a * std::max<db>(0.0, (p[j] - x * s[j]) / (db) q[j]);
		cmin(ans, sum) ? ansx = x : 0;
	}
	db sum = 0.0;
	for (int j = 1; j <= n; ++j)
		sum += a * std::max<db>(0.0, (db) p[j] / (db) q[j]);
	cmin(ans, sum) ? ansx = 0.0 : 0;
	printf("%.20Lf\n", ans);
	printf("%.20Lf\n", ansx);
	for (int i = 1; i <= n; ++i)
		printf("%.20Lf%c", std::max<db>(0.0, (p[i] - ansx * s[i]) / q[i]), " \n"[i == n]);
	return 0;
}
