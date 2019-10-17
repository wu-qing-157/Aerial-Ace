#include <cstdio>

#define maxn 210
typedef long long ll;
ll ex_gcd(ll a, ll b, ll &x, ll &y)
{
	if (b == 0)
	{
		x = 1; y = 0;
		return a;
	}
	ll res = ex_gcd(b, a % b, x, y);
	ll t = y;
	y = x - a / b * y;
	x = t;
	return res;
}
ll mul(ll x, ll y, ll p) {
	ll t = (x * y - (ll) ((long double) x / p * y + 1e-3) * p) % p;
	return t < 0 ? t + p : t;
}
struct CRT {
	ll r, m;
	friend CRT operator + (const CRT &a, const CRT &b)
	{
		if (a.r == -1 || b.r == -1) return (CRT) {-1ll, -1ll};
		ll x, y, g = ex_gcd(a.m, b.m, x, y);
		if ((b.r - a.r) % g != 0) return (CRT) {-1ll, -1ll};
		ll temp = (b.r - a.r) % b.m;
		if (temp < 0) temp += b.m;
		x = mul(temp, x, b.m) / g;
		return (CRT) {a.r + a.m * x, a.m / g * b.m};
	}
} ;
CRT tr[maxn][maxn][10][10];
int a[maxn][maxn], b[maxn][maxn];
int Log[maxn], n, m;
inline void build()
{
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			tr[i][j][0][0] = (CRT) {ll(a[i][j]), ll(b[i][j])};
	for (int kn = 1; kn <= Log[n]; ++kn)
		for (int i = 1; i + (1 << kn) - 1 <= n; ++i)
			for (int j = 1; j <= m; ++j)
				tr[i][j][kn][0] = tr[i][j][kn - 1][0] + tr[i + (1 << (kn - 1))][j][kn - 1][0];
	for (int km = 1; km <= Log[m]; ++km)
		for (int kn = 0; kn <= Log[n]; ++kn)
			for (int i = 1; i + (1 << kn) - 1 <= n; ++i)
				for (int j = 1; j + (1 << km) - 1 <= m; ++j)
					tr[i][j][kn][km] = tr[i][j][kn][km - 1] + tr[i][j + (1 << (km - 1))][kn][km - 1];
}
inline CRT query(int lx, int rx, int ly, int ry)
{
	int kn = Log[rx - lx + 1];
	int km = Log[ry - ly + 1];
	return tr[lx][ly][kn][km] + tr[rx - (1 << kn) + 1][ly][kn][km] + tr[lx][ry - (1 << km) + 1][kn][km]
	+ tr[rx - (1 << kn) + 1][ry - (1 << km) + 1][kn][km];
}
int main()
{
	int T; scanf("%d", &T);
	Log[0] = -1;
	for (int i = 1; i < maxn; ++i) Log[i] = Log[i >> 1] + 1;
	for (int Cas = 1; Cas <= T; ++Cas)
	{
		printf("Case #%d:\n", Cas);
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
				scanf("%d", &a[i][j]);
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
				scanf("%d", &b[i][j]);
		build();
		int Q; scanf("%d", &Q);
		for (; Q; --Q)
		{
			int lx, rx, ly, ry;
			scanf("%d%d%d%d", &lx, &ly, &rx, &ry);
			CRT ret = query(lx, rx, ly, ry);
			printf("%lld\n", ret.r);
		}
	}
	return 0;
}
/*
2
3 4
3 1 1 2
1 1 2 1
1 0 5 5
5 4 2 3
2 2 3 2
4 2 6 6
5
2 2 2 2
1 1 3 4
1 4 2 4
1 1 1 2
2 2 3 4
1 2
0 1
2 2
1
1 1 1 2
*/
