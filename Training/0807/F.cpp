#include <cstdio>
#include <algorithm>

#define maxn 100010
typedef long long ll;
struct item {
	int a, b; ll c;
	inline bool operator < (const item &that) const {return a < that.a || (a == that.a && b < that.b);}
} p[maxn], pp[maxn];
int hash[maxn], hcnt;
ll f[maxn], tr[maxn];
#define cmax(_a, _b) (_a < (_b) ? _a = (_b) : 0)
ll query(int x)
{
	ll ret = 0;
	for (; x; x -= x & -x) cmax(ret, tr[x]);
	return ret;
}
void modify(int x, ll v)
{
	for (; x <= hcnt; x += x & -x) cmax(tr[x], v);
}
int main()
{
	int n, nn = 0; scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d%d%lld", &p[i].a, &p[i].b, &p[i].c), hash[++hcnt] = p[i].b;
	std::sort(hash + 1, hash + hcnt + 1);
	hcnt = std::unique(hash + 1, hash + hcnt + 1) - hash - 1;
	for (int i = 1; i <= n; ++i) p[i].b = std::lower_bound(hash + 1, hash + hcnt + 1, p[i].b) - hash;
	std::sort(p + 1, p + n + 1);
	pp[++nn] = p[1];
	for (int i = 2; i <= n; ++i)
		if (p[i].a == pp[nn].a && p[i].b == pp[nn].b)
			pp[nn].c += p[i].c;
		else pp[++nn] = p[i];
	for (int i = 1, j = 1; i <= nn; i = j)
	{
		while (j <= nn && pp[i].a == pp[j].a) ++j;
		for (int k = i; k < j; ++k)
			f[k] = query(pp[k].b - 1) + pp[k].c;
		for (int k = i; k < j; ++k)
			modify(pp[k].b, f[k]);
	}
	ll ans = 0;
	for (int i = 1; i <= n; ++i)
		cmax(ans, f[i]);
	printf("%lld\n", ans);
	return 0;
}
